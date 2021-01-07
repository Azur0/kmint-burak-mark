#include "kmint/pigisland/pig.hpp"
#include "kmint/pigisland/resources.hpp"
#include "kmint/random.hpp"

namespace kmint {
namespace pigisland {


pig::pig(play::stage& s, math::vector2d location)
  : play::free_roaming_actor{location},
    drawable_{*this, pig_image()}, stage(s) {
}


} // namespace pigisland

} // namespace kmint
