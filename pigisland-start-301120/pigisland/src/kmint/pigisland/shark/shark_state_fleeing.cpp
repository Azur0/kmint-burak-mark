#include "kmint/pigisland/shark/shark_state_fleeing.hpp"

#include "kmint/random.hpp"
#include "kmint/pigisland/shark/shark_state_resting.hpp"
#include "kmint/pigisland/shark/shark_state_roaming.hpp"

namespace kmint {
	namespace pigisland {

		void SharkStateFleeing::onEnter()
		{

		}

		void SharkStateFleeing::onUpdate(delta_time dt)
		{
			// increase fatigue
			actor.increaseFatigue();
			
			// Shark resting mechanic
			if (actor.getFatigue() >= 100)
			{
				std::unique_ptr<SharkStateResting> state = std::make_unique<SharkStateResting>(this->context, actor);
				this->context.changeState(std::move(state));
				return;
			}
			
			if(spookedCounter < 10)
			{
				int next_index = random_int(0, actor.node().num_edges());
				actor.node(actor.node()[next_index].to());
				spookedCounter++;
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
