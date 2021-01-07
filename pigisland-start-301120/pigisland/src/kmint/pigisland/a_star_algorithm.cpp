#include "kmint/pigisland/a_star_algorithm.hpp"

#include <iostream>
#include <stack>

namespace kmint {
    namespace pigisland {

    	// Approximation Heuristics - Manhattan Distance
        // G cost = distance from start node
		// H cost (heuristic) = distance from end node
		// F cost = G cost + H cost
        std::vector<map::map_node> aStarSearch(map::map_graph const& map, std::vector<std::pair<const map::map_node&, const map::map_node&>> const& routes)
        {
            std::vector<map::map_node> empty;
        	
            const int MAP_HEIGHT = 24;
            const int MAP_WIDTH = 32;
        	
            for (const auto& route : routes)
            {
                std::vector<map::map_node> tempMap;

                for (auto& node : map)
                {
                    tempMap.push_back(node);
                }
            	
                const map::map_node& source = route.first;
                const map::map_node& target = route.second;

            	// Closed / Open list
                bool closed[MAP_WIDTH][MAP_HEIGHT];
                std::vector<map::map_node> open;

            	// Initialize starting values of map nodes
                for(auto& node : tempMap)
                {
                    const int x = node.location().x();
                    const int y = node.location().y();

                    closed[x][y] = false;

                	if(node == source)
                	{
                        node.node_info().parent_x = node.location().x();
                        node.node_info().parent_y = node.location().y();

                        open.push_back(node);
                	}
                }
            }

            return empty;
        }
    	
    	float calculateHeuristic(const map::map_node& source, const map::map_node& target)
        {
            const float heuristic = abs(source.location().x() - target.location().x()) +
									abs(source.location().y() - target.location().y());
        	
            return heuristic;
        }

    	bool isValid(map::map_graph const& map, float x, float y)
        {
	        for(const auto& node : map)
	        {
		        if(node.node_info().kind == 'L' || node.node_info().kind == 'S')
		        {
			        if(node.location().x() == x && node.location().y() == y)
			        {
                        return false;
			        }
		        }
	        }

            return true;
        }

        bool isDestination(const map::map_node& source, const map::map_node& target)
        {
        	if(source.location().x() == target.location().x() &&
                source.location().y() == target.location().y())
        	{
                return true;
        	}

            return false;
        }
    } // namespace pigisland
} // namespace kmint
