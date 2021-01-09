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
			void act(delta_time dt) override;

			math::vector2d heading() { return heading_; }
			void heading(math::vector2d heading) { heading_ = heading; }

			const math::vector2d velocity() { return velocity_; }
			const math::vector2d acceleration() { return acceleration_; }
			void accelerate(math::vector2d acceleration) { acceleration_ += acceleration; }

			virtual math::vector2d calculateForce();
		private:
			math::vector2d velocity_;
			math::vector2d acceleration_;
		protected:
			math::vector2d heading_ { 1, 0 };
			float mass_ = 70.0f;
			float max_speed_ = 0.5f;
			float max_force_ = 50.0f;
		};

	} // namespace pigisland
} // namespace kmint

#endif /* KMINT_PIGISLAND_FORCE_DRIVEN_ENTITY_HPP */