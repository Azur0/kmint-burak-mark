#include "kmint/pigisland/shark/shark_state_resting.hpp"

#include "kmint/pigisland/a_star_algorithm.hpp"
#include "kmint/pigisland/node_algorithm.hpp"
#include "kmint/pigisland/rest.hpp"
#include "kmint/pigisland/shark/shark_state_roaming.hpp"

namespace kmint {
	namespace pigisland {

		void SharkStateResting::onEnter()
		{
			std::vector<std::pair<map::map_node&, map::map_node&>> route;
			
			std::unique_ptr<Rest>* restingPlace = actor.stage.getActor<Rest>();

			// Push shark <-> resting place nodes to route
			route.push_back(std::pair<map::map_node&, map::map_node&>(actor.node(), restingPlace->get()->node()));
			path = aStarSearch(actor.graph, route, { 'W', 'R', 'K', '1', '2', '3' });
			path_index = 0;

			// Render path colors
			for (auto node : path)
			{
				node->tag(graph::node_tag::path);
			}
		}

		void SharkStateResting::onUpdate(delta_time dt)
		{
			// Shark resting mechanic
			if(actor.isRested() == true)
			{
				std::unique_ptr<SharkStateRoaming> state = std::make_unique<SharkStateRoaming>(this->context, actor);
				this->context.changeState(std::move(state));
				return;
			}

			// Shark moving mechanic
			if (path_index < path.size()) {
				actor.node().tag(graph::node_tag::normal);
				map::map_node& node = *path.at(path_index);
				actor.node(node);
				path_index++;

				return;
			}
		}

		void SharkStateResting::onExit()
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
