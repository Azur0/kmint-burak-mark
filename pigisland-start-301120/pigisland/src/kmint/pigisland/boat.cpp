#include "kmint/pigisland/boat.hpp"
#include "kmint/pigisland/node_algorithm.hpp"
#include "kmint/pigisland/a_star_algorithm.hpp"
#include "kmint/pigisland/resources.hpp"
#include "kmint/random.hpp"
#include "kmint/pigisland/boat/boat_state_roaming.hpp"
#include "kmint/pigisland/shark.hpp"
#include "kmint/pigisland/dock.hpp"

namespace kmint {
	namespace pigisland {
		
		boat::boat(play::stage& s, map::map_graph& g, map::map_node& initial_node) : play::map_bound_actor{ initial_node }, drawable_{ *this, graphics::image{boat_image()} }, stage(s), graph(g)
		{
			std::unique_ptr<BoatStateRoaming> state = std::make_unique<BoatStateRoaming>(this->stateContext, *this);
			this->stateContext.changeState(std::move(state));
		}

		void boat::act(delta_time dt)
		{
		    t_passed_ += dt;
			if (to_seconds(t_passed_) >= 1)
			{
				stateContext.onUpdate(dt);
				
				std::vector<std::pair<map::map_node&, map::map_node&>> routes;

				map::map_node& boat = node();
				std::unique_ptr<shark>* shark_actor = stage.getActor<shark>();
				std::vector<std::unique_ptr<Dock>*> docks = stage.getActors<Dock>();
				for (auto dockie : docks) {
					routes.push_back(std::pair<map::map_node&, map::map_node&>(boat, dockie->get()->node()));
				}
				auto x = aStarSearch(graph, routes, {'W', 'R', 'K', '1', '2', '3'});
				
				// pick random edge
				int next_index = random_int(0, node().num_edges());
				this->node(node()[next_index].to());
				t_passed_ = from_seconds(0);
			}
		}
	} // namespace pigisland
} // namespace kmint
