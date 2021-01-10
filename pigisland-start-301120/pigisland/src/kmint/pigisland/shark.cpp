#include "kmint/pigisland/shark.hpp"
#include "kmint/pigisland/node_algorithm.hpp"
#include "kmint/pigisland/resources.hpp"
#include "kmint/random.hpp"
#include <iostream>

#include "kmint/pigisland/shark/shark_state_roaming.hpp"

namespace kmint {
	namespace pigisland
	{
		
		shark::shark(play::stage& s, map::map_graph &g, map::map_node &initial_node) : play::map_bound_actor{initial_node}, drawable_{*this, graphics::image{ shark_image() }}, stage(s), graph(g)
		{
			std::unique_ptr<SharkStateRoaming> state = std::make_unique<SharkStateRoaming>(this->stateContext, *this);
			this->stateContext.changeState(std::move(state));
		}

		void shark::act(delta_time dt)
		{
			stateContext.onUpdate(dt);
		}

	} // namespace pigisland
} // namespace kmint
