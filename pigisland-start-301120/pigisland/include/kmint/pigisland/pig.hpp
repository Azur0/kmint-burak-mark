#ifndef KMINT_PIGISLAND_PIG_HPP
#define KMINT_PIGISLAND_PIG_HPP

class flocking;
#include "kmint/play.hpp"
#include "kmint/random.hpp"
#include <tuple>
#include <vector>
#include "kmint/pigisland/force_driven_entity.hpp"

namespace kmint {
namespace pigisland {
struct flock_attributes {
	float f_attraction_k_ = 0.0f;
	float f_attraction_pv_ = 1.0f;
	float f_cohesion_ = 1.0f;
	float f_separation_ = 1.0f;
	float f_alignment_ = 1.0f;
	float f_collision_ = 1.0f;

	math::vector2d attraction_k_;
	math::vector2d attraction_pv_;
	math::vector2d cohesion_;
	math::vector2d alignment_;
	math::vector2d separation_;
	math::vector2d collision_;

	flock_attributes() {
		f_attraction_k_ = random_scalar(-1.0f, 1.0f);
		f_attraction_pv_ = random_scalar(-1.0f, 1.0f);
		f_cohesion_ = random_scalar(0.0f, 1.0f);
		f_separation_ = random_scalar(0.0f, 1.0f);
		f_alignment_ = random_scalar(0.0f, 1.0f);
		f_collision_ = 7.5f;
	}

	math::vector2d calculate() {
		math::vector2d steering_force;
		steering_force += attraction_k_ * f_attraction_k_;
		steering_force += attraction_pv_ * f_attraction_pv_;
		steering_force += cohesion_ * f_cohesion_;
		steering_force += separation_ * f_separation_;
		steering_force += alignment_ * f_alignment_;
		steering_force += collision_ * f_collision_;
		return steering_force;
	}
};

class pig : public ForceDrivenEntity {
public:
  pig(math::vector2d location);
  const ui::drawable &drawable() const override { return drawable_; }
  void act(delta_time dt) override;

  bool incorporeal() const override { return false; }
  scalar collision_range() const override { return 16.0; }
  bool perceptive() const override { return true; }
  scalar perception_range() const override { return perception_range_; }
  flock_attributes flocking();
private:
  play::image_drawable drawable_;			

  float perception_range_;
  math::vector2d seek(math::vector2d target_pos);
  math::vector2d pig::flee(math::vector2d target_pos);
};

} // namespace pigisland
} // namespace kmint

#endif /* KMINT_PIGISLAND_PIG_HPP */
