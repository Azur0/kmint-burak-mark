#include "kmint/pigisland/pig.hpp"
#include "kmint/pigisland/resources.hpp"
#include "kmint/random.hpp"

namespace kmint {
namespace pigisland {


    pig::pig(play::stage& s, map::map_graph& g, math::vector2d location) : ForceDrivenEntity{location}, drawable_{*this, pig_image()}, stage(s), graph(g) 
	{
		perception_range_ = random_int(50.0f, 70.0f);
		mass_ = 0;
		max_speed_ = 1.0f;
		max_force_ = 0.1f;
		force(math::vector2d(1, 1));

		math::vector2d v(random_scalar(-0.5f, 0.5f), random_scalar(-0.5f, 0.5f));
		v = mag(v, random_scalar(12.0f, 12.5f));
		velocity(v);
    }

    void pig::act(delta_time dt) 
	{
		math::vector2d acc = align();
		accelerate(acc);
        ForceDrivenEntity::act(dt);
		//TODO: get nearest node
		//TODO: if colliding with do nothing
		//TODO: set heading to random edge of nearest node
    }

	math::vector2d pig::align()
	{
		math::vector2d desired_velocity;
		int percieved = 0;
		for (auto i = begin_perceived(); i != end_perceived(); ++i) {
			actor& act = *i;

			if (typeid(act).name() == typeid(pig).name()) {
				pig& neighbour = dynamic_cast<pig&>(act);

				float d = distance(location(),neighbour.location());

				if (d < perception_range()) {
					desired_velocity += neighbour.velocity();
					percieved++;
				}
			}
		}

		if (percieved > 0) {
			desired_velocity = desired_velocity / percieved;
			desired_velocity = desired_velocity - velocity();
			return desired_velocity;
		}
		return velocity();
	}

} // namespace pigisland

} // namespace kmint
