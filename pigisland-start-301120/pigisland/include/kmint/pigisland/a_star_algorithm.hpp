#ifndef PIGISLAND_A_STAR_ALGORITHM_HPP
#define PIGISLAND_A_STAR_ALGORITHM_HPP

#include "kmint/map/map.hpp"

namespace kmint {
	namespace pigisland {

		bool getShortestPath(map::map_graph const &map,
			std::vector<std::pair<const graph::basic_node<map::map_node_info>&, const graph::basic_node<map::map_node_info>&>> const& routes);
		
	}
}

#endif /* PIGISLAND_A_STAR_ALGORITHM_HPP */