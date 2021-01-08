#ifndef KMINT_PIGISLAND_REST_HPP
#define KMINT_PIGISLAND_REST_HPP

#include <vector>

#include "kmint/play.hpp"
#include "kmint/map/map.hpp"

namespace kmint {
	namespace pigisland {

		class Rest : public play::map_bound_actor
		{
		public:
			Rest(play::stage& s, map::map_graph& g, map::map_node& initial_node, int heal);
			bool must_draw() const override { return false; };
			ui::drawable const& drawable() const override { return drawable_; }

			void act(delta_time dt) override;

			void setHeal(int amount) { heal_ = amount; }
			int getHeal() { return heal_; }

			play::stage& stage;

		private:
			play::image_drawable drawable_;
			delta_time t_passed_{};

			int heal_;
		};

	} // namespace pigisland
} // namespace kmint

#endif /* KMINT_PIGISLAND_DOCK_HPP */
