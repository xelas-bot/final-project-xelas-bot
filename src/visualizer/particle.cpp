//
// Created by Shrey Patel on 11/1/2020.
//

#include "visualizer/particle.h"

namespace naivebayes {

    namespace visualizer {

        Particle::Particle(glm::vec2 position, glm::vec2 velocity) {

            position_ = position;
            velocity_ = velocity;
        }

        Particle::Particle(glm::vec2 position, glm::vec2 velocity, int mass, int radius) {
            position_ = position;
            velocity_ = velocity;
            mass_ = mass;
            radius_ = radius;
        }


        void Particle::Draw() {
            ci::gl::color(re, gr, bl);
            ci::gl::drawSolidCircle(position_, (float )radius_);

        }


        void Particle::Update() {
            velocity_ += accel_;
            position_ += velocity_;



        }
        void Particle::FallCollision() {
            position_ += velocity_;
            velocity_ += accel_;

        }


        void Particle::VertCollision() {


            velocity_.x = (-1) * velocity_.x;

        }

        void Particle::HorCollision() {
            velocity_.y = (-1) * velocity_.y;
        }


    }
}