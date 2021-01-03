#ifndef PIGISLAND_A_STAR_ALGORITHM_HPP
#define PIGISLAND_A_STAR_ALGORITHM_HPP

#include "kmint/map/map.hpp"

namespace kmint {
	namespace pigisland {

		static bool getShortestPath(map::map_graph const &map, std::vector<map::map_node&, map::map_node&> const& routes);
		
	}
}

#endif /* PIGISLAND_A_STAR_ALGORITHM_HPP */