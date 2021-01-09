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
			velocity_ += acceleration_;
		}

		math::vector2d ForceDrivenEntity::calculateForce() {
			math::vector2d force(random_int(0.0f, max_force_), random_int(0.0f, max_force_));
			return force;
		}

	} // namespace pigisland
} // namespace kmint