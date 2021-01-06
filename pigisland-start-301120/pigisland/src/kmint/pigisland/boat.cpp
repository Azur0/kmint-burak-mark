#include "kmint/pigisland/boat.hpp"
#include "kmint/pigisland/node_algorithm.hpp"
#include "kmint/pigisland/a_star_algorithm.hpp"
#include "kmint/pigisland/resources.hpp"
#include "kmint/random.hpp"
#include "kmint/pigisland/boat/boat_state_roaming.hpp"

namespace kmint {
	namespace pigisland {
		
		boat::boat(map::map_graph& g, map::map_node& initial_node) : play::map_bound_actor{ initial_node }, drawable_{ *this, graphics::image{boat_image()} }
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
				
				/*std::vector<std::pair<const map::map_node&, const map::map_node&>> routes;

				const map::map_node& boat = node();
				const map::map_node& moor = find_random_mooring_place(map().graph());
				
				routes.emplace_back(boat, moor);
				
				auto x = aStarSearch(map().graph(), routes);*/
				
				// pick random edge
				int next_index = random_int(0, node().num_edges());
				this->node(node()[next_index].to());
				t_passed_ = from_seconds(0);
			}
		}
	} // namespace pigisland
} // namespace kmint
