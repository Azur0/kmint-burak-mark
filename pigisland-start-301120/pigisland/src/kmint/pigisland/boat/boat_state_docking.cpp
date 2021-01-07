#include "kmint/pigisland/boat/boat_state_docking.hpp"
#include "kmint/pigisland/dock.hpp"
#include "kmint/pigisland/a_star_algorithm.hpp"
#include "kmint/map/map.hpp"

namespace kmint {
	namespace pigisland {
		
		void BoatStateDocking::onEnter()
		{
			std::vector<std::pair<map::map_node&, map::map_node&>> routes;

			std::vector<std::unique_ptr<Dock>*> docks = actor.stage.getActors<Dock>();
			for (auto dockie : docks) {
				routes.push_back(std::pair<map::map_node&, map::map_node&>(actor.node(), dockie->get()->node()));
			}
			path = aStarSearch(actor.graph, routes, { 'W', 'R', 'K', '1', '2', '3' });
			path_index = 0;

		}

		void BoatStateDocking::onUpdate(delta_time dt)
		{
			if (path_index < path.size()) {
				map::map_node& node = *path.at(path_index);
				actor.node(node);
				path_index++;
			}
		}

		void BoatStateDocking::onExit()
		{
			path.clear();
			path_index = 0;
		}
	}
}