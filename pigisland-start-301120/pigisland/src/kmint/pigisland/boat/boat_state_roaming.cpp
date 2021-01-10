#include "kmint/pigisland/boat/boat_state_roaming.hpp"
#include "kmint/pigisland/boat/boat_state_docking.hpp"
#include "kmint/random.hpp"
#include "kmint/pigisland/node_algorithm.hpp"
#include <kmint/pigisland/pig.hpp>

namespace kmint {
	namespace pigisland {
			
		void BoatStateRoaming::onEnter()
		{

		}

		void BoatStateRoaming::onUpdate(delta_time dt)
		{
			t_passed_ += dt;

			if (to_seconds(t_passed_) >= waiting_time(actor.node()))
			{
				// pick random edge
				actor.node(random_adjacent_node(actor.node()));

				// increase damage
				actor.increaseDamage();
				t_passed_ = from_seconds(0);
			}

			// change to dock state if damage reaches >= 100
			if(actor.getDamage() >= 100)
			{
				std::unique_ptr<BoatStateDocking> state = std::make_unique<BoatStateDocking>(this->context, actor);
				this->context.changeState(std::move(state));
				return;
			}

			// Rescue pig(s) on target node
			for (auto i = actor.begin_collision(); i != actor.end_collision(); ++i) {
				auto& currentActor = *i;

				if (typeid(currentActor).name() == typeid(pig).name()) {
					currentActor.remove();
				}
			}
		}

		void BoatStateRoaming::onExit()
		{
			
		}
	}
}
