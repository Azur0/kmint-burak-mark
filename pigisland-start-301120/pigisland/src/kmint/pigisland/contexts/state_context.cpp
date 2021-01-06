#include "kmint/pigisland/contexts/state_context.hpp"

namespace kmint {
	namespace pigisland {

		void StateContext::onUpdate(delta_time dt)
		{
			this->currentState->onUpdate(dt);
		}

		void StateContext::changeState(std::unique_ptr<BaseState> newState)
		{
			if(this->currentState != nullptr) {
				this->currentState->onExit();	
			}
			this->currentState = std::move(newState);
			this->currentState->onEnter();
		}
		
	}
}