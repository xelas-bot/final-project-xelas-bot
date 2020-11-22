//
// Created by Shrey Patel on 11/19/2020.
//

#include "visualizer/player.h"

namespace naivebayes {

namespace visualizer {

    void player::Draw() {
        ci::gl::color(ci::Color("white"));
        ci::gl::drawSolidCircle(centerPos, radius_);

        ci::gl::color(re, gr, bl);
        ci::gl::drawSolidCircle({centerPos.x-20,centerPos.y-10}, 10);
        ci::gl::drawSolidCircle({centerPos.x+20,centerPos.y-10}, 10);

    }

    void player::Update() {

        if (IsAirBorne()){
            velocity+=accel_;
            centerPos+=velocity;
        }else {
            velocity.y=0;
            centerPos.y = (float )window_height_- radius_ + 5;
            centerPos.x += velocity.x;
        }

    }

    bool player::IsAirBorne() {
        if (centerPos.y <= window_height_- radius_){
            return true;
        }
        return false;
    }

    void player::MoveLeft() {
        if (!IsAirBorne()){
            velocity.x = -15.f;
        }

    }

    void player::MoveRight() {
        if (!IsAirBorne()){
            velocity.x = 15.f;
        }
    }

    glm::vec2 player::Jump() {
        if (!IsAirBorne()){
            centerPos.y -= 10.f;
            velocity.y = -20.f;
        }
        return velocity;

    }

    void player::MidAirStrafeRight(glm::vec2 currentVel) {
        velocity.x = currentVel.x + 10;
    }

    void player::MidAirStrafeLeft(glm::vec2 currentVel) {
        velocity.x = currentVel.x - 10;
    }


}
}
