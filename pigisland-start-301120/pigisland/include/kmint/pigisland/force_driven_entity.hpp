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

			void velocity(math::vector2d velocity) { velocity_ = velocity; }
			const math::vector2d velocity() { return velocity_; }
			const math::vector2d acceleration() { return acceleration_; }
			void accelerate(math::vector2d acceleration);

			void force(math::vector2d force);
			math::vector2d calculateAcceleration();
		private:
			math::vector2d velocity_;
			math::vector2d acceleration_;
			math::vector2d force_;
			math::vector2d heading_;
		protected:
			float mass_;
			float max_speed_;
			float max_force_;
		};

	} // namespace pigisland
} // namespace kmint

#endif /* KMINT_PIGISLAND_FORCE_DRIVEN_ENTITY_HPP */