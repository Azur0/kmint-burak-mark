#include "kmint/pigisland/dock.hpp"

#include "kmint/pigisland/resources.hpp"

namespace kmint {
	namespace pigisland {

		Dock::Dock(play::stage& s, map::map_graph& g, map::map_node& initial_node, int minimumHeal, int maximumHeal) : play::map_bound_actor{ initial_node }, drawable_{ *this, graphics::image{boat_image()} }, minHeal(minimumHeal), maxHeal(maximumHeal)
		{
			auto x = 5;
		}
	} // namespace pigisland
} // namespace kmint
