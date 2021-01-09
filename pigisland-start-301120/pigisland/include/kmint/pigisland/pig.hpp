#ifndef KMINT_PIGISLAND_PIG_HPP
#define KMINT_PIGISLAND_PIG_HPP

#include "kmint/play.hpp"
#include <tuple>
#include <vector>
#include "kmint/pigisland/force_driven_entity.hpp"

namespace kmint {
namespace pigisland {

class pig : public ForceDrivenEntity {
public:
  pig(play::stage& s, map::map_graph& g, math::vector2d location);
  const ui::drawable &drawable() const override { return drawable_; }
  void act(delta_time dt) override;

  scalar collision_range() const override { return 16.0; }
  bool perceptive() const override { return true; }
  scalar perception_range() const override { return perception_range_; }

  play::stage& stage;
  map::map_graph& graph;

  const float attraction_k() { return attraction_k_; }
  void attraction_k(float attraction_k) { attraction_k_ = attraction_k; }

  const float attraction_pv() { return attraction_pv_; }
  void attraction_pv(float attraction_pv) { attraction_pv_ = attraction_pv; }

  const float cohesion() { return cohesion_; }
  void cohesion(float cohesion) { cohesion_ = cohesion; }

  const float separation() { return separation_; }
  void separation(float separation) { separation_ = separation; }

  const float alignment() { return alignment_; }
  void alignment(float alignment) { alignment_ = alignment; }

  math::vector2d calculateForce() override;
private:
  play::image_drawable drawable_;			

  float perception_range_ = 0.0f;
  float attraction_k_ = 0.0f;
  float attraction_pv_ = 0.0f;
  float cohesion_ = 0.0f;
  float separation_ = 0.0f;
  float alignment_ = 0.0f;
  math::vector2d align();
};

} // namespace pigisland
} // namespace kmint

#endif /* KMINT_PIGISLAND_PIG_HPP */
