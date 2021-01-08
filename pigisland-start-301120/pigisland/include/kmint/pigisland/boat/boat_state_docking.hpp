#ifndef KMINT_PIGISLAND_BOAT_STATE_DOCKING_HPP
#define KMINT_PIGISLAND_BOAT_STATE_DOCKING_HPP

#include "kmint/pigisland/boat.hpp"
#include "kmint/pigisland/dock.hpp"
#include "kmint/pigisland/interfaces/base_state.hpp"

namespace kmint {
	namespace pigisland {

		class BoatStateDocking : public BaseState
		{
		public:
			BoatStateDocking(StateContext& stateContext, play::map_bound_actor& stateActor) : BaseState(stateContext, stateActor), actor(dynamic_cast<boat&>(stateActor)) {}
			void onEnter() override;
			void onUpdate(delta_time dt) override;
			void onExit() override;
		private:
			boat& actor;
			std::vector<map::map_node*> path;
			int path_index;
			std::unique_ptr<Dock>* currentDock;
		};

	}
}

#endif /* KMINT_PIGISLAND_BOAT_STATE_DOCKING_HPP */