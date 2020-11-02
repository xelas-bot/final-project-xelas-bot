//
// Created by Shrey Patel on 11/1/2020.
//

#include "visualizer/particle.h"

namespace naivebayes{

namespace visualizer{
    void particle::draw() {
        ci::gl::color(re,gr,bl);
        ci::gl::drawSolidCircle(position_,kRadius);

    }


    void particle::update() {
        position_ += velocity_;

    }


    void particle::vert_collision() {
        velocity_.x = (-1) * velocity_.x;

    }

    void particle::hor_collision() {
        velocity_.y = (-1) * velocity_.y;
    }


    void particle::particle_collision() {

    }

}
}
