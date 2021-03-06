#include "kmint/pigisland/shark/shark_state_roaming.hpp"

#include "kmint/random.hpp"
#include "kmint/pigisland/boat.hpp"
#include "kmint/pigisland/node_algorithm.hpp"
#include "kmint/pigisland/pig.hpp"
#include "kmint/pigisland/shark/shark_state_fleeing.hpp"
#include "kmint/pigisland/shark/shark_state_hunting.hpp"
#include "kmint/pigisland/shark/shark_state_resting.hpp"

namespace kmint {
	namespace pigisland {

		void SharkStateRoaming::onEnter()
		{

		}

		void SharkStateRoaming::onUpdate(delta_time dt)
		{
			t_passed_ += dt;

			if (to_seconds(t_passed_) >= waiting_time(actor.node()))
			{
				// pick random edge
				actor.node(random_adjacent_node(actor.node()));

				// increase fatigue
				actor.increaseFatigue();

				t_passed_ = from_seconds(0);
				return;
			}


			// Shark resting mechanic
			if (actor.getFatigue() >= 100)
			{
				std::unique_ptr<SharkStateResting> state = std::make_unique<SharkStateResting>(this->context, actor);
				this->context.changeState(std::move(state));
				return;
			}
			
			// Shark hunting & fleeing mechanic
			for (auto i = actor.begin_perceived(); i != actor.end_perceived(); ++i)
			{
				auto const &a = *i;

				// Shark gets spooked
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

				// Shark smells piggy
				if (typeid(a).name() == typeid(pig).name()) {
					std::cout << "Smelled a pig at " << a.location().x() << ", " << a.location().y() << "\n";
					map::map_node* node = &find_without_const_closest_node_to(actor.graph, a.location());
					actor.setTarget(node);

					std::unique_ptr<SharkStateHunting> state = std::make_unique<SharkStateHunting>(this->context, actor);
					this->context.changeState(std::move(state));
					return;
				}
			}
		}

		void SharkStateRoaming::onExit()
		{
			
		}
	}
}
