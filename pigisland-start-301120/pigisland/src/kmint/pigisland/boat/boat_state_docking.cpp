#include "kmint/pigisland/boat/boat_state_docking.hpp"

#include "kmint/random.hpp"
#include "kmint/pigisland/dock.hpp"
#include "kmint/pigisland/a_star_algorithm.hpp"
#include "kmint/map/map.hpp"
#include "kmint/pigisland/boat/boat_state_roaming.hpp"
#include "kmint/pigisland/node_algorithm.hpp"

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

			// Render path colors
			for(auto node : path)
			{
				node->tag(graph::node_tag::path);
			}
		}

		void BoatStateDocking::onUpdate(delta_time dt)
		{
			t_passed_ += dt;
			// Boat damage check
			if (actor.getRepaired() == true)
			{	
				std::unique_ptr<BoatStateRoaming> state = std::make_unique<BoatStateRoaming>(this->context, actor);
				this->context.changeState(std::move(state));
				return;
			}

			if (to_seconds(t_passed_) >= waiting_time(actor.node()))
			{
				// Boat moving mechanic
				if (path_index < path.size()) {
					actor.node().tag(graph::node_tag::normal);
					map::map_node& node = *path.at(path_index);
					actor.node(node);
					path_index++;
				}
				t_passed_ = from_seconds(0);
			}

		}

		void BoatStateDocking::onExit()
		{
			// Reset path colors
			for (auto node : path)
			{
				node->tag(graph::node_tag::normal);
			}
			
			path.clear();
			path_index = 0;
		}
	}
}
