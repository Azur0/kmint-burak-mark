#include "kmint/pigisland/a_star_algorithm.hpp"

#include <iostream>
#include <stack>

namespace kmint {
    namespace pigisland {

    	// Approximation Heuristics - Manhattan Distance
        std::vector<map::map_node> aStarSearch(map::map_graph const& map, std::vector<std::pair<const map::map_node&, const map::map_node&>> const& routes)
        {
            std::vector<map::map_node> empty;
        	
            const int MAP_HEIGHT = 24;
            const int MAP_WIDTH = 32;
        	
            for (auto it = routes.begin(); it != routes.end(); ++it)
            {
                // G cost = distance from start node
                // H cost (heuristic) = distance from end node
                // F cost = G cost + H cost

                const map::map_node& source = it->first;
                const map::map_node& target = it->second;
                bool closed[MAP_WIDTH][MAP_HEIGHT];

            	// source.node_info().f_cost
            }

            return empty;
        }
    	
    	float calculateHeuristic(const map::map_node& source, const map::map_node& target)
        {
            const float heuristic = abs(source.location().x() - target.location().x()) + abs(source.location().y() - target.location().y());
        	
            return heuristic;
        }
    } // namespace pigisland
} // namespace kmint
