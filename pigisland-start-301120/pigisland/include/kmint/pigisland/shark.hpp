#ifndef KMINT_PIGISLAND_SHARK_HPP
#define KMINT_PIGISLAND_SHARK_HPP

#include "contexts/state_context.hpp"
#include "kmint/map/map.hpp"
#include "kmint/play.hpp"
#include "kmint/primitives.hpp"

namespace kmint {
	namespace pigisland
	{

		class shark : public play::map_bound_actor {
		public:
			shark(play::stage& s, map::map_graph &g, map::map_node &initial_node);
			// wordt elke game tick aangeroepen
			void act(delta_time dt) override;
			ui::drawable const &drawable() const override { return drawable_; }
			// als incorporeal false is, doet de actor mee aan collision detection
			bool incorporeal() const override { return false; }
			// geeft de lengte van een zijde van de collision box van deze actor terug.
			// Belangrijk voor collision detection
			scalar collision_range() const override { return 16.0; }
			// geeft aan dat de haai andere actors kan zien
			bool perceptive() const override { return true; }
			// geeft het bereik aan waarbinnen een haai
			// andere actors kan waarnemen.
			scalar perception_range() const override { return 200.f; }

			std::string getCurrentState() { return stateContext.getCurrentState(); }

			play::stage& stage;
			map::map_graph& graph;
			
			int getFatigue() const { return fatigue; }
			void increaseFatigue() { increaseFatigue(1); }
			void decreaseFatigue() { decreaseFatigue(1); }
			void increaseFatigue(int amount) { fatigue += amount; isRested_ = false; }
			void decreaseFatigue(int amount) { fatigue -= amount; isRested_ = true; }
			bool isRested() { return isRested_; }

		private:
			// hoeveel tijd is verstreken sinds de laatste beweging
			delta_time t_passed_{};
			// weet hoe de koe getekend moet worden
			play::image_drawable drawable_;

			int fatigue = 0;
			StateContext stateContext;
			bool isRested_;
		};

	} // namespace pigisland
} // namespace kmint

#endif /* KMINT_PIGISLAND_SHARK_HPP */
