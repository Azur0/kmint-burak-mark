#include "kmint/pigisland/rest.hpp"
#include "kmint/random.hpp"
#include "kmint/pigisland/shark.hpp"
#include "kmint/pigisland/resources.hpp"

namespace kmint {
	namespace pigisland {

		Rest::Rest(play::stage& s, map::map_graph& g, map::map_node& initial_node, int heal) : play::map_bound_actor{ initial_node }, drawable_{ *this, graphics::image{boat_image()} }, stage(s), heal_(heal) {}

		void Rest::act(delta_time dt)
		{
			t_passed_ += dt;

			if (to_seconds(t_passed_) >= 1)
			{
				shark* actor = stage.getActor<shark>()->get();
				std::string currentSharkState = actor->getCurrentState();

				if (currentSharkState == "sharkStateResting" && this->location().x() == actor->location().x() && this->location().y() == actor->location().y())
				{
					if(actor->isRested() == false)
					{
						actor->decreaseFatigue(100);
					}
				}
			}
		}

	} // namespace pigisland
} // namespace kmint
