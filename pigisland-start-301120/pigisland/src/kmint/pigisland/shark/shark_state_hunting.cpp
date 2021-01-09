#include "kmint/pigisland/shark/shark_state_hunting.hpp"

#include "kmint/pigisland/a_star_algorithm.hpp"
#include "kmint/pigisland/shark/shark_state_roaming.hpp"

namespace kmint {
	namespace pigisland {

		void SharkStateHunting::onEnter()
		{
			std::vector<std::pair<map::map_node&, map::map_node&>> route;

			route.push_back(std::pair<map::map_node&, map::map_node&>(actor.node(), *actor.getTarget()));
			path = aStarSearch(actor.graph, route, { 'W', 'R', 'K', '1', '2', '3' });
			path_index = 0;

			// Render path colors
			for (auto node : path)
			{
				node->tag(graph::node_tag::path);
			}
		}

		void SharkStateHunting::onUpdate(delta_time dt)
		{
			// Shark moving mechanic
			int x = path.size();
			if (path_index < path.size()) {
				actor.node().tag(graph::node_tag::normal);
				map::map_node& node = *path.at(path_index);
				actor.node(node);
				path_index++;

				return;
			}

			if (path_index == path.size())
			{
				std::unique_ptr<SharkStateRoaming> state = std::make_unique<SharkStateRoaming>(this->context, actor);
				this->context.changeState(std::move(state));
				return;
			}
		}

		void SharkStateHunting::onExit()
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
