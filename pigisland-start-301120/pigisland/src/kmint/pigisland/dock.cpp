#include "kmint/pigisland/dock.hpp"
#include "kmint/random.hpp"
#include "kmint/pigisland/boat.hpp"
#include "kmint/pigisland/resources.hpp"

namespace kmint {
	namespace pigisland {

		Dock::Dock(play::stage& s, map::map_graph& g, map::map_node& initial_node, int minimumHeal, int maximumHeal) : play::map_bound_actor{ initial_node }, drawable_{ *this, graphics::image{""} }, minHeal(minimumHeal), maxHeal(maximumHeal), stage(s) {}

		void Dock::act(delta_time dt)
		{
			t_passed_ += dt;

			if (to_seconds(t_passed_) >= 1)
			{
				boat* actor = stage.getActor<boat>()->get();
				std::string currentBoatState = actor->getCurrentState();
				
				if(currentBoatState == "boatStateDocking" && this->location().x() == actor->location().x() && this->location().y() == actor->location().y())
				{
					if(actor->getRepaired() == false)
					{
						if (getMinimumHeal() == getMaximumHeal())
						{
							actor->decreaseDamage(getMinimumHeal());
						}
						else
						{
							actor->decreaseDamage(random_int(getMinimumHeal(), getMaximumHeal()));
						}
					}
				}
			}
		}

	} // namespace pigisland
} // namespace kmint
