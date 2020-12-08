//
// Created by Shrey Patel on 11/1/2020.
//

#include "visualizer/particle.h"

namespace naivebayes {

    namespace visualizer {

        Particle::Particle(glm::vec2 position, glm::vec2 velocity) {

            position_ = position;
            velocity_ = velocity;
            auto img = loadImage(ci::app::loadAsset("ball.png"));
            ball_img_ = ci::gl::Texture2d::create(img);
        }

        Particle::Particle(glm::vec2 position, glm::vec2 velocity, int mass, int radius) {
            position_ = position;
            velocity_ = velocity;
            mass_ = mass;
            radius_ = radius;
            auto img = loadImage(ci::app::loadAsset("ball.png"));
            ball_img_ = ci::gl::Texture2d::create(img);
        }


        void Particle::Draw() {

            ci::gl::pushModelMatrix();
            ci::gl::translate(position_ - glm::vec2(radius_,radius_));
            ci::gl::scale(2.0f*radius_/ball_img_->getWidth(), 2.0f*radius_/ball_img_->getHeight());
            ci::gl::color(1,1,1);
            ci::gl::draw(ball_img_);
            ci::gl::popModelMatrix();



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