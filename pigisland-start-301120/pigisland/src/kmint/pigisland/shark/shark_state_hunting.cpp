#include "kmint/pigisland/shark/shark_state_hunting.hpp"

#include "kmint/pigisland/a_star_algorithm.hpp"
#include "kmint/pigisland/shark/shark_state_roaming.hpp"
#include <kmint\pigisland\pig.hpp>


#include "kmint/pigisland/boat.hpp"
#include "kmint/pigisland/shark/shark_state_fleeing.hpp"

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
			// Shark fleeing mechanic
			for (auto i = actor.begin_perceived(); i != actor.end_perceived(); ++i)
			{
				auto const& a = *i;

				if (typeid(a).name() == typeid(boat).name()) {
					std::cout << math::distance(actor.location(), actor.stage.getActor<boat>()->get()->location()) << "\n";

					// TODO: Change 100 -> 50
					if (math::distance(actor.location(), a.location()) <= 100)
					{
						std::unique_ptr<SharkStateFleeing> state = std::make_unique<SharkStateFleeing>(this->context, actor);
						this->context.changeState(std::move(state));
						return;
					}
				}
			}
			
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
				// Eat pig(s) on target node
				for (auto i = actor.begin_collision(); i != actor.end_collision(); ++i) {
					auto& currentActor = *i;

					if (typeid(currentActor).name() == typeid(pig).name()) {
						pig& piggy = dynamic_cast<pig&>(currentActor);
						currentActor.remove();
					}
				}
				
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
