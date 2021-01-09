#include "kmint/pigisland/pig.hpp"
#include "kmint/pigisland/resources.hpp"
#include "kmint/random.hpp"

namespace kmint {
namespace pigisland {


    pig::pig(play::stage& s, map::map_graph& g, math::vector2d location) : ForceDrivenEntity{location}, drawable_{*this, pig_image()}, stage(s), graph(g) 
	{
		perception_range_ = 70.0f;// random_scalar(150.f, 250.0f);
		mass_ = 0.25f;//random_scalar(5.0f, 10.0f);
		//max_speed_ = random_scalar(0.5f, 1.0f);
		max_force_ = 100.0f;
		max_speed_ = 1.0f;
		math::vector2d v(random_scalar(-100.0f, 100.0f), random_scalar(-100.0f, 100.0f));
		//v = setLength(v, 1.0f);
		velocity(v);
    }

    void pig::act(delta_time dt) 
	{
		flock_attributes flock = flocking();
		math::vector2d steering_force = flock.calculate();
		math::vector2d acceleration = steering_force / mass_;

		////TODO: get nearest node
		////TODO: if colliding with do nothing
		////TODO: set heading to random edge of nearest node

		math::vector2d new_velocity = velocity() + (acceleration * to_seconds(dt));
		math::vector2d truncated_velocity = truncate(new_velocity, max_force_ * to_seconds(dt));
		velocity(truncated_velocity);

		math::vector2d new_loc = location() + (velocity());

		if (new_loc.x() < 0) {
			new_loc.x(1024);
		}
		else if(new_loc.x() > 1024) {
			new_loc.x(0);
		}

		if (new_loc.y() < 0) {
			new_loc.y(768);
		}
		else if (new_loc.y() > 768) {
			new_loc.y(0);
		}
		location(new_loc);

		if (norm(velocity()) > 0.00000001)
		{
			heading(normalize(velocity()));
			//m_vSide = m_vHeading.Perp();
		}
    }

	flock_attributes pig::flocking() {
		math::vector2d average_heading;
		flock_attributes flock;

		int percieved_nieghbours = 0;
		for (auto i = begin_perceived(); i != end_perceived(); ++i) {
			play::actor& act = *i;
			

			// check nearby piggies
			if (typeid(act).name() == typeid(pig).name()) {
				pig& neighbour = dynamic_cast<pig&>(act);
				if (sees(*this, neighbour)) {
					average_heading += neighbour.heading();
					percieved_nieghbours++;
				}
			}
		}

		if (percieved_nieghbours > 0) {
			flock.alignment_ = average_heading / percieved_nieghbours;
			flock.alignment_ = average_heading - heading();
		}
		return flock;
	}
} // namespace pigisland

} // namespace kmint
