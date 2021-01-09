#ifndef KMINT_PIGISLAND_BASE_STATE_HPP
#define KMINT_PIGISLAND_BASE_STATE_HPP

#include "kmint/pigisland/contexts/state_context.hpp"
#include "kmint/primitives.hpp"
#include "kmint/play.hpp"

namespace kmint {
	namespace pigisland {

		class StateContext;
		class BaseState
		{
		protected:
			StateContext& context;
			play::map_bound_actor& actor;
		public:
			BaseState(StateContext& stateContext, play::map_bound_actor& stateActor) : context(stateContext), actor(stateActor) { };
			virtual void onEnter() = 0;
			virtual void onUpdate(delta_time dt) = 0;
			virtual void onExit() = 0;
			virtual std::string getIdentifier() = 0;
		};
		
	}
}

#endif /* KMINT_PIGISLAND_BASE_STATE_HPP */