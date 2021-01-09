#ifndef KMINT_PIGISLAND_SHARK_STATE_FLEEING_HPP
#define KMINT_PIGISLAND_SHARK_STATE_FLEEING_HPP

#include "kmint/pigisland/shark.hpp"
#include "kmint/pigisland/interfaces/base_state.hpp"

namespace kmint {
	namespace pigisland {

		class SharkStateFleeing : public BaseState
		{
		public:
			SharkStateFleeing(StateContext& stateContext, play::map_bound_actor& stateActor) : BaseState(stateContext, stateActor), actor(dynamic_cast<shark&>(stateActor)) {}
			void onEnter() override;
			void onUpdate(delta_time dt) override;
			void onExit() override;
			std::string getIdentifier() override { return "sharkStateFleeing"; }
		private:
			shark& actor;
		};

	}
}

#endif /* KMINT_PIGISLAND_SHARK_STATE_FLEEING_HPP */