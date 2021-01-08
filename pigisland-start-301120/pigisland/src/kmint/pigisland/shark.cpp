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
			t_passed_ += dt;
			
			if (to_seconds(t_passed_) >= waiting_time(this->node()))
			{
				std::cout << "SHARK FATIGUE: " << fatigue << "\n";
				
				stateContext.onUpdate(dt);
				t_passed_ = from_seconds(0);
			}
			
			// laat ook even zien welke varkentjes hij ruikt
			//for (auto i = begin_perceived(); i != end_perceived(); ++i)
			//{
			//	auto const &a = *i;
			//	std::cout << "Smelled a pig at " << a.location().x() << ", " << a.location().y() << "\n";
			//}
		}

	} // namespace pigisland
} // namespace kmint
