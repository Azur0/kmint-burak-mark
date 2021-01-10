#include "kmint/pigisland/shark/shark_state_fleeing.hpp"

#include "kmint/random.hpp"
#include "kmint/pigisland/shark/shark_state_resting.hpp"
#include "kmint/pigisland/shark/shark_state_roaming.hpp"
#include "kmint/pigisland/node_algorithm.hpp"

namespace kmint {
	namespace pigisland {

		void SharkStateFleeing::onEnter()
		{

		}

		void SharkStateFleeing::onUpdate(delta_time dt)
		{
			t_passed_ += dt;

			if (to_seconds(t_passed_) >= waiting_time(actor.node()))
			{

				if (spookedCounter < 10)
				{
					actor.node(random_adjacent_node(actor.node()));
					spookedCounter++;

					// increase fatigue
					actor.increaseFatigue();
					t_passed_ = from_seconds(0);
					return;
				}
				t_passed_ = from_seconds(0);
			}


			// Shark resting mechanic
			if (actor.getFatigue() >= 100)
			{
				std::unique_ptr<SharkStateResting> state = std::make_unique<SharkStateResting>(this->context, actor);
				this->context.changeState(std::move(state));
				return;
			}

			std::unique_ptr<SharkStateRoaming> state = std::make_unique<SharkStateRoaming>(this->context, actor);
			this->context.changeState(std::move(state));
			return;
		}

		void SharkStateFleeing::onExit()
		{
			spookedCounter = 0;
		}
	}
}
