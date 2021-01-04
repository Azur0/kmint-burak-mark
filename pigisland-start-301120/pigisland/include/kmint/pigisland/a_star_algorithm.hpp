#ifndef PIGISLAND_A_STAR_ALGORITHM_HPP
#define PIGISLAND_A_STAR_ALGORITHM_HPP

#include "kmint/map/map.hpp"

namespace kmint {
	namespace pigisland {

		std::vector<map::map_node> aStarSearch(map::map_graph const& map, std::vector<std::pair<const map::map_node&, const map::map_node&>> const& routes);
		float calculateHeuristic(const map::map_node& source, const map::map_node& target);
	}
}

#endif /* PIGISLAND_A_STAR_ALGORITHM_HPP */