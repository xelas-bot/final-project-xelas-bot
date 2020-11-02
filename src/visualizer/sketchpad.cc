#include <visualizer/sketchpad.h>

namespace naivebayes {

namespace visualizer {

using glm::vec2;

Sketchpad::Sketchpad(const vec2& top_left_corner, size_t num_pixels_per_side,
                     double sketchpad_size, double brush_radius)
    : top_left_corner_(top_left_corner),
      num_pixels_per_side_(num_pixels_per_side),
      pixel_side_length_(sketchpad_size / num_pixels_per_side),
      brush_radius_(brush_radius) {}

void Sketchpad::Draw() const {
  vec2 pixel_bottom_right =
      top_left_corner_ + vec2(28*pixel_side_length_, 28*pixel_side_length_);

  ci::gl::color(ci::Color("white"));
  ci::Rectf pixel_bounding_box(top_left_corner_, pixel_bottom_right );
  ci::gl::drawStrokedRect(pixel_bounding_box);

}

void Sketchpad::HandleBrush(const vec2& brush_screen_coords) {
  vec2 brush_sketchpad_coords =
      (brush_screen_coords - top_left_corner_) / (float)pixel_side_length_;

  for (size_t row = 0; row < num_pixels_per_side_; ++row) {
    for (size_t col = 0; col < num_pixels_per_side_; ++col) {
      vec2 pixel_center = {col + 0.5, row + 0.5};

      if (glm::distance(brush_sketchpad_coords, pixel_center) <=
          brush_radius_) {
        // TODO: Add code to shade in the pixel at (row, col)
      }
    }
  }
}

void Sketchpad::Clear() {
  particles_.clear();
}

}  // namespace visualizer

}  // namespace naivebayes
