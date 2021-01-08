#include "kmint/pigisland/boat/boat_state_docking.hpp"

#include "kmint/random.hpp"
#include "kmint/pigisland/dock.hpp"
#include "kmint/pigisland/a_star_algorithm.hpp"
#include "kmint/map/map.hpp"
#include "kmint/pigisland/boat/boat_state_roaming.hpp"

namespace kmint {
	namespace pigisland {
		
		void BoatStateDocking::onEnter()
		{
			std::vector<std::pair<map::map_node&, map::map_node&>> routes;

			// Push all docks to routes
			std::vector<std::unique_ptr<Dock>*> docks = actor.stage.getActors<Dock>();
			for (auto dockie : docks) {
				routes.push_back(std::pair<map::map_node&, map::map_node&>(actor.node(), dockie->get()->node()));
			}
			path = aStarSearch(actor.graph, routes, { 'W', 'R', 'K', '1', '2', '3' });
			path_index = 0;

			// Get target dock id
			size_t dockId = path.back()->node_id();

			// Set target dock
			for(auto dock : docks)
			{
				if(dock->get()->node().node_id() == dockId)
				{
					currentDock = dock;
				}
			}

			// Render path colors
			for(auto node : path)
			{
				node->tag(graph::node_tag::path);
			}
		}

		void BoatStateDocking::onUpdate(delta_time dt)
		{
			// Boat healing mechanic
			if (actor.node() == currentDock->get()->node())
			{
				int heal = 0;
				
				if(currentDock->get()->getMinimumHeal() == currentDock->get()->getMaximumHeal())
				{
					heal = currentDock->get()->getMinimumHeal();
				}
				else
				{
					heal = random_int(currentDock->get()->getMinimumHeal(), currentDock->get()->getMaximumHeal());
				}
				
				actor.decreaseDamage(heal);
				
				std::unique_ptr<BoatStateRoaming> state = std::make_unique<BoatStateRoaming>(this->context, actor);
				this->context.changeState(std::move(state));
				return;
			}

			// Boat moving mechanic
			if (path_index < path.size()) {
				actor.node().tag(graph::node_tag::normal);
				map::map_node& node = *path.at(path_index);
				actor.node(node);
				path_index++;
			}
		}

		void BoatStateDocking::onExit()
		{
			// Reset path color
			for (auto node : path)
			{
				node->tag(graph::node_tag::normal);
			}
			
			path.clear();
			path_index = 0;
		}
	}
}
