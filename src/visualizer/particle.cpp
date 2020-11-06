//
// Created by Shrey Patel on 11/1/2020.
//

#include "visualizer/particle.h"

namespace naivebayes {

    namespace visualizer {

        particle::particle(glm::vec2 position, glm::vec2 velocity) {

            position_ = position;
            velocity_ = velocity;
        }

        void particle::Draw() {
            ci::gl::color(re, gr, bl);
            ci::gl::drawSolidCircle(position_, kRadius);

        }


        void particle::Update() {
            position_ += velocity_;

        }


        void particle::VertCollision() {
            velocity_.x = (-1) * velocity_.x;

        }

        void particle::HorCollision() {
            velocity_.y = (-1) * velocity_.y;
        }


    }
}
