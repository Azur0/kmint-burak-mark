#ifndef PIGISLAND_A_STAR_ALGORITHM_HPP
#define PIGISLAND_A_STAR_ALGORITHM_HPP

#include "kmint/map/map.hpp"

namespace kmint {
	namespace pigisland {

		std::vector<map::map_node*> aStarSearch(map::map_graph& map, std::vector<std::pair<map::map_node&, map::map_node&>> const& routes, const std::vector<char>& walkableLayers);
		std::vector<map::map_node*> retracePath(const map::map_node& source, map::map_node& target);
		float getDistance(const map::map_node& source, const map::map_node& target);
		bool isValid(const map::map_graph& map, float x, float y, const std::vector<char>& walkableLayers);
		bool isDestination(const map::map_node& source, const int x, const int y);
	}
}

#endif /* PIGISLAND_A_STAR_ALGORITHM_HPP */