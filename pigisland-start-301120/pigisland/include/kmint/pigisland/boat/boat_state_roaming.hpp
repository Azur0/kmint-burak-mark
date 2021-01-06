#ifndef KMINT_PIGISLAND_BOAT_STATE_ROAMING_HPP
#define KMINT_PIGISLAND_BOAT_STATE_ROAMING_HPP

#include "kmint/pigisland/boat.hpp"
#include "kmint/pigisland/interfaces/base_state.hpp"

namespace kmint {
	namespace pigisland {

		class BoatStateRoaming : public BaseState
		{
		public:
			BoatStateRoaming(StateContext& stateContext, play::map_bound_actor& stateActor) : BaseState(stateContext, stateActor), actor(dynamic_cast<boat&>(stateActor)) {}
			void onEnter() override;
			void onUpdate(delta_time dt) override;
			void onExit() override;
		private:
			boat& actor;
		};

	}
}

#endif /* KMINT_PIGISLAND_BOAT_STATE_ROAMING_HPP */