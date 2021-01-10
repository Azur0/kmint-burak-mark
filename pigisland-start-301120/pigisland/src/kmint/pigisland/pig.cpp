#include "kmint/pigisland/pig.hpp"
#include "kmint/pigisland/resources.hpp"
#include "kmint/random.hpp"
#include "kmint/pigisland/node_algorithm.hpp"
#include "kmint/pigisland/obstacle.hpp"

namespace kmint {
namespace pigisland {
	pig::pig(math::vector2d location) : ForceDrivenEntity{ location }, drawable_{ *this, pig_image() }
	{
		perception_range_ = 70.0f;
		mass_ = 0.25f;
		max_force_ = 5.0f;
		max_speed_ = 1.0f;
		math::vector2d v(random_scalar(-100.0f, 100.0f), random_scalar(-100.0f, 100.0f));
		v = setLength(v, 1.0f);
		velocity(v);
    }

    void pig::act(delta_time dt) 
	{
		math::vector2d current_location = location();
		math::vector2d current_heading = heading();
		math::vector2d current_velocity = velocity();

		flock_attributes flock = flocking();
		math::vector2d steering_force = flock.calculate();
		math::vector2d acceleration = steering_force / mass_;

		math::vector2d new_velocity = current_velocity + (acceleration * to_seconds(dt));
		math::vector2d truncated_velocity = truncate(new_velocity, max_force_ * to_seconds(dt));

		if (norm(truncated_velocity) > 0.00000001)
		{
			heading(normalize(velocity()));
		}
		location(current_location + truncated_velocity);
		velocity(truncated_velocity);
    }

	flock_attributes pig::flocking() {
		math::vector2d steering_force;			// Seperation
		math::vector2d average_heading;			// Alignment
		math::vector2d center_of_mass;			// Cohesion
		math::vector2d steering_force_2_electric_boogalo;
    	
		flock_attributes flock;

		int percieved_nieghbours = 0;
		int percieved_obstacles = 0;
		for (auto i = begin_perceived(); i != end_perceived(); ++i) {
			play::actor& act = *i;

			
			if (typeid(act).name() == typeid(Obstacle).name()) {
				// check obstacles
				if(distance(location(), act.location()) < 75)
				{
					percieved_obstacles++;
					steering_force_2_electric_boogalo += act.location();
				}
			}
			
			// check nearby piggies
			if (typeid(act).name() == typeid(pig).name()) {
				pig& neighbour = dynamic_cast<pig&>(act);
				if (sees(*this, neighbour)) {
					math::vector2d to_agent = location() - neighbour.location();	// Seperation
					steering_force += normalize(to_agent) / length(to_agent);		// Seperation
					average_heading += neighbour.heading();							// Alignment
					center_of_mass += neighbour.location();							// Cohesion
					
					percieved_nieghbours++;
				}
			}
		}

		if (percieved_nieghbours > 0) {
			flock.separation_ = steering_force;								// Seperation
			flock.alignment_ = average_heading / percieved_nieghbours;		// Alignment
			flock.alignment_ = average_heading - heading();					// Alignment
			
			center_of_mass = center_of_mass / percieved_nieghbours;			// Cohesion
			flock.cohesion_ = seek(center_of_mass);							// Cohesion
		}

		if (percieved_obstacles > 0)
		{
			steering_force_2_electric_boogalo = steering_force_2_electric_boogalo / percieved_obstacles;
			flock.collision_ = flee(steering_force_2_electric_boogalo);
		}
    	
		return flock;
	}

	math::vector2d pig::seek(math::vector2d target_pos)
	{
		math::vector2d desired_velocity = normalize(target_pos - location()) * max_speed_;

		return (desired_velocity - velocity());
	}

	math::vector2d pig::flee(math::vector2d target_pos)
    {
		math::vector2d desired_velocity = normalize(location() - target_pos) * max_speed_;

		return (desired_velocity - velocity());
    }
} // namespace pigisland

} // namespace kmint
