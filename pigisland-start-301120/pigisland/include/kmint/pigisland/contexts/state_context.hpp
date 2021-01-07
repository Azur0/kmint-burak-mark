#ifndef KMINT_PIGISLAND_STATE_CONTEXT_HPP
#define KMINT_PIGISLAND_STATE_CONTEXT_HPP

#include <memory>
#include "kmint/pigisland/interfaces/base_state.hpp"
#include "kmint/primitives.hpp"
#include "kmint/play/stage.hpp"

namespace kmint {
	namespace pigisland {
		class BaseState;
		
		class StateContext
		{
		private:
			std::unique_ptr<BaseState> currentState;
		public:
			void onUpdate(delta_time dt);
			void changeState(std::unique_ptr<BaseState> newState);
		};
		
	}
}

#endif /* KMINT_PIGISLAND_STATE_CONTEXT_HPP */