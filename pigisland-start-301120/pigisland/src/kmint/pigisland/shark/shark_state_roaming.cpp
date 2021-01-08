#include "kmint/pigisland/shark/shark_state_roaming.hpp"

#include "kmint/random.hpp"
#include "kmint/pigisland/shark/shark_state_resting.hpp"

namespace kmint {
	namespace pigisland {

		void SharkStateRoaming::onEnter()
		{

		}

		void SharkStateRoaming::onUpdate(delta_time dt)
		{
			// pick random edge
			int next_index = random_int(0, actor.node().num_edges());
			actor.node(actor.node()[next_index].to());

			// increase fatigue
			actor.increaseFatigue();

			// change to resting state if fatigue reaches >= 100
			if (actor.getFatigue() >= 100)
			{
				std::unique_ptr<SharkStateResting> state = std::make_unique<SharkStateResting>(this->context, actor);
				this->context.changeState(std::move(state));
				return;
			}
		}

		void SharkStateRoaming::onExit()
		{
			
		}
	}
}
