#include "kmint/pigisland/pig.hpp"
#include "kmint/pigisland/resources.hpp"
#include "kmint/random.hpp"

namespace kmint {
namespace pigisland {


    pig::pig(play::stage& s, map::map_graph& g, math::vector2d location) : ForceDrivenEntity{location}, drawable_{*this, pig_image()}, stage(s), graph(g) 
	{
		perception_range_ = random_int(50.0f, 70.0f);
    }

    void pig::act(delta_time dt) 
	{
		math::vector2d acc = calculateForce();
		accelerate(acc);
        ForceDrivenEntity::act(dt);
    }

	math::vector2d pig::calculateForce() {
		math::vector2d base_force = align();
		return base_force;
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
	}

} // namespace pigisland

} // namespace kmint
