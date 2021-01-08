#ifndef KMINT_PIGISLAND_SHARK_STATE_ROAMING_HPP
#define KMINT_PIGISLAND_SHARK_STATE_ROAMING_HPP

#include "kmint/pigisland/shark.hpp"
#include "kmint/pigisland/interfaces/base_state.hpp"

namespace kmint {
	namespace pigisland {

		class SharkStateRoaming : public BaseState
		{
		public:
			SharkStateRoaming(StateContext& stateContext, play::map_bound_actor& stateActor) : BaseState(stateContext, stateActor), actor(dynamic_cast<shark&>(stateActor)) {}
			void onEnter() override;
			void onUpdate(delta_time dt) override;
			void onExit() override;
			std::string getIdentifier() override { return "sharkStateRoaming"; }
		private:
			shark& actor;
		};

	}
}

#endif /* KMINT_PIGISLAND_SHARK_STATE_ROAMING_HPP */