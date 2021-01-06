#include "kmint/pigisland/boat/boat_state_roaming.hpp"
#include "kmint/pigisland/boat/boat_state_docking.hpp"

namespace kmint {
	namespace pigisland {
			
		void BoatStateRoaming::onEnter()
		{
			
		}

		void BoatStateRoaming::onUpdate(delta_time dt)
		{
			actor.increaseDamage(50);

			if(actor.getDamage() == 100)
			{
				std::unique_ptr<BoatStateDocking> state = std::make_unique<BoatStateDocking>(this->context, actor);
				this->context.changeState(std::move(state));
			}
		}

		void BoatStateRoaming::onExit()
		{
			
		}
	}
}
