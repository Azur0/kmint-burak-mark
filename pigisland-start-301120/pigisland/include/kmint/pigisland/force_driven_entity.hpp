#ifndef KMINT_PIGISLAND_FORCE_DRIVEN_ENTITY_HPP
#define KMINT_PIGISLAND_FORCE_DRIVEN_ENTITY_HPP

#include "kmint/map/map.hpp"
#include "kmint/play.hpp"
#include "kmint/primitives.hpp"
#include "contexts/state_context.hpp"

namespace kmint {
	namespace pigisland {

		class ForceDrivenEntity : public play::free_roaming_actor {
		public:
			ForceDrivenEntity(math::vector2d location);

			math::vector2d heading() { return heading_; }
			void heading(math::vector2d heading) { heading_ = heading; }

			void velocity(math::vector2d velocity) { velocity_ = velocity; }
			const math::vector2d velocity() { return velocity_; }

			math::vector2d initialVelocity() const;
		private:
			math::vector2d velocity_;
			math::vector2d heading_;
		protected:
			float mass_ = 1;
			float max_speed_ = 1.0f;
			float max_force_ = 1.0f;
		};

	} // namespace pigisland
} // namespace kmint

#endif /* KMINT_PIGISLAND_FORCE_DRIVEN_ENTITY_HPP */