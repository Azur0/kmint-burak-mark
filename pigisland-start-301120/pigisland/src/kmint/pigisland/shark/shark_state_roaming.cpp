#include "kmint/pigisland/shark/shark_state_roaming.hpp"

#include "kmint/random.hpp"
#include "kmint/pigisland/node_algorithm.hpp"
#include "kmint/pigisland/shark/shark_state_hunting.hpp"
#include "kmint/pigisland/shark/shark_state_resting.hpp"

namespace kmint {
	namespace pigisland {

		void SharkStateRoaming::onEnter()
		{

		}

		void SharkStateRoaming::onUpdate(delta_time dt)
		{
			// pick random edge
			actor.node(random_adjacent_node(actor.node()));

			// increase fatigue
			actor.increaseFatigue();

			// change to resting state if fatigue reaches >= 100
			if (actor.getFatigue() >= 100)
			{
				std::unique_ptr<SharkStateResting> state = std::make_unique<SharkStateResting>(this->context, actor);
				this->context.changeState(std::move(state));
				return;
			}

			// laat ook even zien welke varkentjes hij ruikt
			for (auto i = actor.begin_perceived(); i != actor.end_perceived(); ++i)
			{
				auto const &a = *i;
				std::cout << "Smelled a pig at " << a.location().x() << ", " << a.location().y() << "\n";
				
				map::map_node* node = &find_without_const_closest_node_to(actor.graph, a.location());

				// Set shark target
				actor.setTarget(node);

				std::unique_ptr<SharkStateHunting> state = std::make_unique<SharkStateHunting>(this->context, actor);
				this->context.changeState(std::move(state));
				return;
			}
		}

		void SharkStateRoaming::onExit()
		{
			
		}
	}
}
