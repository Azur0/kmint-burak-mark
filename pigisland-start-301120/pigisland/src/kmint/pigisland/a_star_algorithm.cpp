#include "kmint/pigisland/a_star_algorithm.hpp"

namespace kmint {
    namespace pigisland {

    	// Approximation Heuristics - Manhattan Distance
        bool getShortestPath(map::map_graph const& map,
            std::vector<std::pair<const graph::basic_node<map::map_node_info>&, const graph::basic_node<map::map_node_info>&>> const& routes)
        {
            for(auto it = routes.begin(); it != routes.end(); ++it)
            {
                // G cost = distance from starting node
            	// H cost (heuristic) = distance from end node
            	// F cost = G cost + H cost
            	
                const map::map_node& source = it->first;
                const map::map_node& target = it->second;
                bool closedList[32][24];
            }
        	
            return false;
        }

        bool isValid(map::map_graph const& map, int x, int y)
        {
	        for(const auto& node : map)
	        {
	        	if(node.location().x() == x && node.location().y() == y)
	        	{
	        		if(node.node_info().kind == 'L' || node.node_info().kind == 'S')
	        		{
                        return false;
	        		}
	        	}
	        }

            return true;
        }

    	bool isDestination(graph::basic_node<map::map_node_info>& source, graph::basic_node<map::map_node_info>& target)
        {
	        if(source.location().x() == target.location().x() &&
                source.location().y() == target.location().y())
	        {
                return true;
	        }

            return false;
        }

    	float calculateHeuristic(graph::basic_node<map::map_node_info>& source, graph::basic_node<map::map_node_info>& target)
        {
            const float heuristic = abs(source.location().x() - target.location().x()) +
									abs(source.location().y() - target.location().y());
        	
            return heuristic;
        }
    } // namespace pigisland
} // namespace kmint
