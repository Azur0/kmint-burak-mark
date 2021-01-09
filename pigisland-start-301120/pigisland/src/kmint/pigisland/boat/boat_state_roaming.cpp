#include "kmint/pigisland/boat/boat_state_roaming.hpp"
#include "kmint/pigisland/boat/boat_state_docking.hpp"
#include "kmint/random.hpp"

namespace kmint {
	namespace pigisland {
			
		void BoatStateRoaming::onEnter()
		{

		}

		void BoatStateRoaming::onUpdate(delta_time dt)
		{
			// pick random edge
			int next_index = random_int(0, actor.node().num_edges());
			actor.node(actor.node()[next_index].to());

			// increase damage
			actor.increaseDamage();

			// change to dock state if damage reaches >= 100
			if(actor.getDamage() >= 100)
			{
				std::unique_ptr<BoatStateDocking> state = std::make_unique<BoatStateDocking>(this->context, actor);
				this->context.changeState(std::move(state));
				return;
			}
		}

		void BoatStateRoaming::onExit()
		{
			
		}
	}
}
