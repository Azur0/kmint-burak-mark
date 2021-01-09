#include "kmint\pigisland\force_driven_entity.hpp"
#include "kmint/random.hpp"

namespace kmint {
	namespace pigisland {
		ForceDrivenEntity::ForceDrivenEntity(math::vector2d location) : play::free_roaming_actor{ location }
		{
	
		}

		math::vector2d ForceDrivenEntity::initialVelocity() const {
			float force = max_force_ / mass_;
			return { force, force };
		}

	} // namespace pigisland
} // namespace kmint