#include "kmint/pigisland/a_star_algorithm.hpp"

#include <iostream>
#include <stack>

namespace kmint {
    namespace pigisland {

    	// Approximation Heuristics - Manhattan Distance
        // G cost = distance from start node
		// H cost (heuristic) = distance from end node
		// F cost = G cost + H cost
        std::vector<map::map_node*> aStarSearch(map::map_graph& map, std::vector<std::pair<map::map_node&, map::map_node&>> const& routes, const std::vector<char>& walkableLayers = {})
        {
            std::vector<map::map_node*> empty;
            std::vector<std::pair<std::vector<map::map_node*>, float>> found_paths;
            //TODO:: save shortest route
            const int MAP_HEIGHT = 24;
            const int MAP_WIDTH = 32;
        	
            for (const auto& route : routes)
            {
                // Locate source and target nodes
                map::map_node& source = route.first;
                map::map_node& target = route.second;

                if (!isValid(map, target.location().x(), target.location().y(), walkableLayers)) {
                    continue;
                }

                if (isDestination(source, target.location().x(), target.location().y())) {
                    continue;
                }

            	//// Closed / open list
                //bool closed[MAP_WIDTH][MAP_HEIGHT];
                std::vector<map::map_node*> open;
                std::vector<map::map_node*> closed_;

            	// Initialize starting values of map nodes
                //int i = 0;
                //for(auto& node : map)
                //{
                //    map::map_node* pNode = &node;
                //    const int x = pNode->location().x() / MAP_WIDTH;
                //    const int y = pNode->location().y() / MAP_HEIGHT;

                //    closed[x][y] = false;

                //    // Initialize start node position
                //	if(node == source)
                //	{
                //        pNode->node_info().parent = pNode;
                //        open.push_back(pNode);
                //	}
                //    i++;
                //}
                int x = 0;
            	while(!open.empty())
            	{
                    map::map_node* currentNode = open.at(0);

            		for(int i = 1; i < open.size(); i++)
            		{
                        map::map_node& otherNode = *open.at(i);
            			if(otherNode.node_info().f_cost() < currentNode->node_info().f_cost() || otherNode.node_info().f_cost() == currentNode->node_info().f_cost() /*&& otherNode.node_info().h_cost < currentNode->node_info().h_cost*/)
            			{
                            currentNode = open.at(i);
            			}
            		}

                    open.pop_back();
                    closed_.push_back(currentNode);

            		// Found path
                    if(currentNode->node_id() == target.node_id())
                    {
                        std::vector<map::map_node*> found_path = retracePath(source, target);
                        float weight = 0;
                        std::for_each(found_path.begin(), found_path.end(), [&](map::map_node* node) {
                                weight += node->node_info().t_cost();
                            });
                        found_paths.push_back(std::make_pair(found_path, weight));
                        continue;
                    }

                    for (auto it = currentNode->begin(); it != currentNode->end(); ++it) {
                        map::map_node* neighbour = &it->to();
                        const int x = neighbour->location().x() / MAP_WIDTH;
                        const int y = neighbour->location().y() / MAP_HEIGHT;
                        if (std::find(walkableLayers.begin(), walkableLayers.end(), neighbour->node_info().kind) == walkableLayers.end() || std::find(closed_.begin(), closed_.end(), neighbour) != closed_.end()) {
                            continue;
                        }

                        int newMovementCostToNeighbour = currentNode->node_info().g_cost + getDistance(*currentNode, *neighbour);
                        if (newMovementCostToNeighbour < neighbour->node_info().g_cost || !std::count(open.begin(), open.end(), neighbour))
                        {
                            neighbour->node_info().g_cost = newMovementCostToNeighbour;
                            neighbour->node_info().h_cost = getDistance(*neighbour, target);
                            neighbour->node_info().parent = currentNode;
                            neighbour->node_info().weight = it->weight();

                            if (std::find(open.begin(), open.end(), neighbour) == open.end()) {
                                open.push_back(neighbour);
                            }
                        }
                    }
            	}
            }

            return empty;
        }

        std::vector<map::map_node*> retracePath(const map::map_node& source, map::map_node& target)
        {
            std::vector<map::map_node*> path;
            map::map_node* currentNode = &target;

            while (currentNode != &source)
            {
                path.push_back(currentNode);
                currentNode = currentNode->node_info().parent;
            }

            std::reverse(path.begin(), path.end());

            return path;
        }
    	
    	float getDistance(const map::map_node& source, const map::map_node& target)
        {
            const float heuristic = abs(source.location().x() - target.location().x()) +
									abs(source.location().y() - target.location().y());
        	
            return heuristic;
        }

    	bool isValid(map::map_graph const& map, float x, float y, const std::vector<char>& walkableLayers)
        {
	        for(const auto& node : map)
	        {
		        if(std::find(walkableLayers.begin(), walkableLayers.end(), node.node_info().kind) == walkableLayers.end())
		        {
			        if(node.location().x() == x && node.location().y() == y)
			        {
                        return false;
			        }
		        }
	        }

            return true;
        }

        bool isDestination(const map::map_node& source, const int x, const int y)
        {
        	if(source.location().x() == x && source.location().y() == y)
        	{
                return true;
        	}

            return false;
        }
    } // namespace pigisland
} // namespace kmint
