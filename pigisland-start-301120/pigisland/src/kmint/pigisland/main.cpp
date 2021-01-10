#include "kmint/main.hpp" // voor de main loop
#include "kmint/math/intersection.hpp"
#include "kmint/math/rectangle.hpp"
#include "kmint/pigisland/boat.hpp"
#include "kmint/pigisland/obstacle.hpp"
#include "kmint/pigisland/dock.hpp"
#include "kmint/pigisland/node_algorithm.hpp"
#include "kmint/pigisland/pig.hpp"
#include "kmint/pigisland/resources.hpp"
#include "kmint/pigisland/shark.hpp"
#include "kmint/play.hpp"
#include "kmint/ui.hpp"
#include <algorithm>
#include <array>
#include <iostream>
#include <random>
#include <vector>

#include "kmint/pigisland/rest.hpp"

using namespace kmint;

int main() {
  // een app object is nodig om
  ui::app app{};

  //  maak een venster aan
  ui::window window{app.create_window({1024, 768}, "pigisland", 1.0)};

  // maak een podium aan
  play::stage s{{1024, 768}};

  auto map = pigisland::map();
  auto &graph = map.graph();
  s.build_actor<play::background>(math::size(1024, 768), graphics::image{map.background_image()});
  s.build_actor<play::map_actor>(math::vector2d{0.f, 0.f}, map.graph());
  s.build_actor<pigisland::boat>(s, graph, pigisland::find_node_of_kind(graph, 'B'));          // Bootvarken
  s.build_actor<pigisland::shark>(s, graph, pigisland::find_node_of_kind(graph, 'K'));         // Haai
  s.build_actor<pigisland::Rest>(s, graph, pigisland::find_node_of_kind(graph, 'K'), 100);      // Haai
	
  s.build_actor<pigisland::Dock>(s, graph, pigisland::find_node_of_kind(graph, '1'), 30, 50);  // Graaneiland
  s.build_actor<pigisland::Dock>(s, graph, pigisland::find_node_of_kind(graph, '2'), 20, 100); // Graseiland
  s.build_actor<pigisland::Dock>(s, graph, pigisland::find_node_of_kind(graph, '3'), 50, 50);  // Boomeiland

  int xCount = 1024;
  int yCount = 16;
	for(int i = 0; i < 24; i++)
	{
        std::cout << "{" << xCount << ", " << yCount << "}," << "\n";
        yCount += 32;
	}
	
  std::vector<math::vector2d> lands = {
    {16, 16},
{48, 16},
{80, 16},
{112, 16},
{144, 16},
{176, 16},
{912, 16},
{944, 16},
{976, 16},
{1008, 16},
{16, 48},
{48, 48},
{80, 48},
{112, 48},
{144, 48},
{176, 48},
{208, 48},
{240, 48},
{272, 48},
{912, 48},
{944, 48},
{976, 48},
{1008, 48},
{16, 80},
{48, 80},
{80, 80},
{112, 80},
{144, 80},
{176, 80},
{1008, 80},
{1008, 112},
{80, 560},
{112, 560},
{144, 560},
{176, 560},
{208, 560},
{912, 560},
{80, 592},
{112, 592},
{144, 592},
{176, 592},
{208, 592},
{912, 592},
{976, 592},
{1008, 592},
{80, 624},
{112, 624},
{144, 624},
{176, 624},
{208, 624},
{848, 624},
{880, 624},
{912, 624},
{944, 624},
{976, 624},
{1008, 624},
{80, 656},
{112, 656},
{144, 656},
{176, 656},
{816, 656},
{848, 656},
{880, 656},
{912, 656},
{944, 656},
{976, 656},
{1008, 656},
{80, 688},
{112, 688},
{144, 688},
{176, 688},
{816, 688},
{848, 688},
{880, 688},
{912, 688},
{944, 688},
{976, 688},
{1008, 688},
{816, 720},
{848, 720},
{880, 720},
{912, 720},
{944, 720},
{976, 720},
{1008, 720},
{816, 752},
{848, 752},
{880, 752},
{912, 752},
{944, 752},
{976, 752},
{1008, 752}, // END ISLANDS
    {16, 0},
{48, 0},
{80, 0},
{112, 0},
{144, 0},
{176, 0},
{208, 0},
{240, 0},
{272, 0},
{304, 0},
{336, 0},
{368, 0},
{400, 0},
{432, 0},
{464, 0},
{496, 0},
{528, 0},
{560, 0},
{592, 0},
{624, 0},
{656, 0},
{688, 0},
{720, 0},
{752, 0},
{784, 0},
{816, 0},
{848, 0},
{880, 0},
{912, 0},
{944, 0},
{976, 0},
{1008, 0}, // END TOP BORDER
{ 16, 752 },
{ 48, 752 },
{ 80, 752 },
{ 112, 752 },
{ 144, 752 },
{ 176, 752 },
{ 208, 752 },
{ 240, 752 },
{ 272, 752 },
{ 304, 752 },
{ 336, 752 },
{ 368, 752 },
{ 400, 752 },
{ 432, 752 },
{ 464, 752 },
{ 496, 752 },
{ 528, 752 },
{ 560, 752 },
{ 592, 752 },
{ 624, 752 },
{ 656, 752 },
{ 688, 752 },
{ 720, 752 },
{ 752, 752 },
{ 784, 752 },
{ 816, 752 },
{ 848, 752 },
{ 880, 752 },
{ 912, 752 },
{ 944, 752 },
{ 976, 752 }, // END BOTTOM BORDER
{ 0, 16 },
{ 0, 48 },
{ 0, 80 },
{ 0, 112 },
{ 0, 144 },
{ 0, 176 },
{ 0, 208 },
{ 0, 240 },
{ 0, 272 },
{ 0, 304 },
{ 0, 336 },
{ 0, 368 },
{ 0, 400 },
{ 0, 432 },
{ 0, 464 },
{ 0, 496 },
{ 0, 528 },
{ 0, 560 },
{ 0, 592 },
{ 0, 624 },
{ 0, 656 },
{ 0, 688 },
{ 0, 720 },
{ 0, 752 }, // END LEFT BORDER
{ 1008, 16 },
{ 1008, 48 },
{ 1008, 80 },
{ 1008, 112 },
{ 1008, 144 },
{ 1008, 176 },
{ 1008, 208 },
{ 1008, 240 },
{ 1008, 272 },
{ 1008, 304 },
{ 1008, 336 },
{ 1008, 368 },
{ 1008, 400 },
{ 1008, 432 },
{ 1008, 464 },
{ 1008, 496 },
{ 1008, 528 },
{ 1008, 560 },
{ 1008, 592 },
{ 1008, 624 },
{ 1008, 656 },
{ 1008, 688 },
{ 1008, 720 },
{ 1008, 752 } // END RIGHT BORDER
  };

	for(auto land : lands)
	{
        s.build_actor<pigisland::Obstacle>(land);
	}
	
  auto locs = pigisland::random_pig_locations(100);
  for (auto loc : locs) {
    s.build_actor<pigisland::pig>(s, graph, loc);
  }

  // Maak een event_source aan (hieruit kun je alle events halen, zoals
  // toetsaanslagen)
  ui::events::event_source event_source{};

  // main_loop stuurt alle actors aan.
  main_loop(s, window, [&](delta_time dt, loop_controls &ctl) {
    // gebruik dt om te kijken hoeveel tijd versterken is
    // sinds de vorige keer dat deze lambda werd aangeroepen
    // loop controls is een object met eigenschappen die je kunt gebruiken om de
    // main-loop aan te sturen.

    for (ui::events::event &e : event_source) {
      // event heeft een methode handle_quit die controleert
      // of de gebruiker de applicatie wilt sluiten, en zo ja
      // de meegegeven functie (of lambda) aanroept om met het
      // bijbehorende quit_event
      //
      e.handle_quit([&ctl](ui::events::quit_event qe) { ctl.quit = true; });
      e.handle_key_up([&](auto ke) {
        switch (ke.key) {
        case ui::events::key::p:
          ctl.pause = !ctl.pause;
          break;
        case ui::events::key::r:
          ctl.render = !ctl.render;
          break;
        case ui::events::key::opening_bracket:
          ctl.time_scale /= 2.0;
          break;
        case ui::events::key::closing_bracket:
          ctl.time_scale *= 2.0;
          break;
        case ui::events::key::d:
          ctl.debug_overlay = !ctl.debug_overlay;
        default:
          break;
        }
      });
    }
  });
}
