#ifndef KMINT_PIGISLAND_OBSTACLE_HPP
#define KMINT_PIGISLAND_OBSTACLE_HPP

#include <vector>

#include "kmint/play.hpp"
#include "kmint/map/map.hpp"

namespace kmint {
	namespace pigisland {

		class Obstacle : public play::static_actor
		{
		public:
			Obstacle(math::vector2d location) : play::static_actor{location}, drawable_{ *this, graphics::image{ "" } } {}
			bool must_draw() const override { return false; };
			bool perceivable() const override { return true; };
			ui::drawable const& drawable() const override { return drawable_; }
		private:
			play::image_drawable drawable_;
		};

	} // namespace pigisland
} // namespace kmint

#endif /* KMINT_PIGISLAND_DOCK_HPP */
