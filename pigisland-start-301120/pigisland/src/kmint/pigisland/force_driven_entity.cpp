#include "kmint\pigisland\force_driven_entity.hpp"
#include "kmint/random.hpp"

namespace kmint {
	namespace pigisland {
		ForceDrivenEntity::ForceDrivenEntity(math::vector2d location) : play::free_roaming_actor{ location }
		{
			location.x(20);
			location.y(760);
		}

		void ForceDrivenEntity::act(delta_time dt) {
			/*math::vector2d force = calculateForce();

			math::vector2d acceleration;
			acceleration.x(std::clamp(force.x(), 0.0f, max_force_) / mass_);
			acceleration.y(std::clamp(force.y(), 0.0f, max_force_) / mass_);

			velocity_.x(velocity_.x() + -std::clamp(acceleration.x(), 0.0f, max_speed_));
			velocity_.y(velocity_.y() + std::clamp(acceleration.y(), 0.0f, max_speed_));

			math::vector2d newLoc = location() + (velocity_ * to_seconds(dt));
			location(newLoc);*/


			math::vector2d newLoc = location() + (velocity_ * to_seconds(dt));
			location(newLoc); 
		}

		math::vector2d ForceDrivenEntity::calculateAcceleration() {
			return math::vector2d((force_.x() / mass_), (force_.y() / mass_));
		}

		void ForceDrivenEntity::force(math::vector2d force) {
			force_.x(std::clamp(force.x(), 0.0f, max_force_));
			force_.y(std::clamp(force.y(), 0.0f, max_force_));
		}

		void ForceDrivenEntity::accelerate(math::vector2d acceleration) 
		{ 
			acceleration_ += acceleration;
			limit(acceleration, max_force_);
			mag(acceleration, max_speed_);
		}

	} // namespace pigisland
} // namespace kmint