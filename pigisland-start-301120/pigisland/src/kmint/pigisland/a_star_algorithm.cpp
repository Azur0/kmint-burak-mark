#include "kmint/pigisland/a_star_algorithm.hpp"

namespace kmint {
    namespace pigisland {

    	// Approximation Heuristics - Manhattan Distance
        bool getShortestPath(map::map_graph const& map,
            std::vector<std::pair<const graph::basic_node<map::map_node_info>&, const graph::basic_node<map::map_node_info>&>> const& routes)
        {
            for(auto it = routes.begin(); it != routes.end(); ++it)
            {
                const map::map_node& source = it->first;
                const map::map_node& target = it->second;
                const float heuristic = abs(source.location().x() - target.location().x()) +
					abs(source.location().y() - target.location().y());

                auto test = 5;
            }
        	
            return false;
        }

    } // namespace pigisland
} // namespace kmint
