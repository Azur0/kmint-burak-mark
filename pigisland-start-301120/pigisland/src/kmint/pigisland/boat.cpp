#include "kmint/pigisland/boat.hpp"
#include "kmint/pigisland/node_algorithm.hpp"
#include "kmint/pigisland/a_star_algorithm.hpp"
#include "kmint/pigisland/resources.hpp"
#include "kmint/random.hpp"

namespace kmint {
	namespace pigisland {
		boat::boat(map::map_graph& g, map::map_node& initial_node)
			: play::map_bound_actor{ initial_node },
			drawable_{ *this, graphics::image{boat_image()} } {}


		void boat::act(delta_time dt)
		{
		    t_passed_ += dt;
			if (to_seconds(t_passed_) >= 1)
			{
				if(!isInvulnerable) damage += 1;
				if(damage == 100) isInvulnerable = true;

				std::cout << damage << "\n";
				
				std::vector<std::pair<const map::map_node&, const map::map_node&>> routes;

				const map::map_node& boat = node();
				const map::map_node& moor = find_random_mooring_place(map().graph());
				
				routes.emplace_back(boat, moor);
				
				auto x = getShortestPath(map().graph(), routes);
				
				// pick random edge
				int next_index = random_int(0, node().num_edges());
				this->node(node()[next_index].to());
				t_passed_ = from_seconds(0);
			}
		}

	} // namespace pigisland
} // namespace kmint
