#include "kmint/pigisland/shark/shark_state_resting.hpp"

#include "kmint/pigisland/a_star_algorithm.hpp"
#include "kmint/pigisland/node_algorithm.hpp"
#include "kmint/pigisland/rest.hpp"
#include "kmint/pigisland/shark/shark_state_roaming.hpp"
#include "kmint/pigisland/resources.hpp"
#include "kmint/pigisland/pig.hpp"

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
			t_passed_ += dt;
			// Shark resting mechanic
			if(actor.isRested() == true)
			{
				std::vector<std::unique_ptr<pig>*> pigs = actor.stage.getActors<pig>();
				for (std::unique_ptr<pig>* piggy : pigs) {
					piggy->get()->remove();
				}

				// spawn new pigs
				auto locs = random_pig_locations(100);
				for (auto loc : locs) {
					auto& act = actor.stage.queue_build_actor<pig>(loc);
				}

				std::unique_ptr<SharkStateRoaming> state = std::make_unique<SharkStateRoaming>(this->context, actor);
				this->context.changeState(std::move(state));
				return;
			}

			if (to_seconds(t_passed_) >= waiting_time(actor.node()))
			{
				// Shark moving mechanic
				if (path_index < path.size()) {
					actor.node().tag(graph::node_tag::normal);
					map::map_node& node = *path.at(path_index);
					actor.node(node);
					path_index++;
				}
				t_passed_ = from_seconds(0);
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
