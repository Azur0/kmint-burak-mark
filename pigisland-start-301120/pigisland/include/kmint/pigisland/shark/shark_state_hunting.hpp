#ifndef KMINT_PIGISLAND_SHARK_STATE_HUNTING_HPP
#define KMINT_PIGISLAND_SHARK_STATE_HUNTING_HPP

#include "kmint/pigisland/shark.hpp"
#include "kmint/pigisland/interfaces/base_state.hpp"

namespace kmint {
	namespace pigisland {

		class SharkStateHunting : public BaseState
		{
		public:
			SharkStateHunting(StateContext& stateContext, play::map_bound_actor& stateActor) : BaseState(stateContext, stateActor), actor(dynamic_cast<shark&>(stateActor)) {}
			void onEnter() override;
			void onUpdate(delta_time dt) override;
			void onExit() override;
			std::string getIdentifier() override { return "sharkStateHunting"; }
		private:
			shark& actor;
			std::vector<map::map_node*> path;
			int path_index;
		};

	}
}

#endif /* KMINT_PIGISLAND_SHARK_STATE_HUNTING_HPP */