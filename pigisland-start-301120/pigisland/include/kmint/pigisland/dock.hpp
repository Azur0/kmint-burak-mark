#ifndef KMINT_PIGISLAND_DOCK_HPP
#define KMINT_PIGISLAND_DOCK_HPP

#include <vector>
#include "kmint/play.hpp"
#include "kmint/map/map.hpp"

namespace kmint {
	namespace pigisland {

		class Dock : public play::map_bound_actor
		{
		public:
			Dock(play::stage& s, map::map_graph& g, map::map_node& initial_node, int minimumHeal, int maximumHeal);
			bool must_draw() const override { return false; };
			ui::drawable const& drawable() const override { return drawable_; }

			void act(delta_time dt) override;
			bool perceivable() const override { return false; }
			
			void setMinimumHeal(int amount) { minHeal = amount; }
			int getMinimumHeal() { return minHeal; }
			
			void setMaximumHeal(int amount) { maxHeal = amount; }
			int getMaximumHeal() { return maxHeal; }

			void heal();

			play::stage& stage;
			
		private:
			play::image_drawable drawable_;
			delta_time t_passed_{};
			
			int minHeal;
			int maxHeal;
		};

	} // namespace pigisland
} // namespace kmint

#endif /* KMINT_PIGISLAND_DOCK_HPP */
