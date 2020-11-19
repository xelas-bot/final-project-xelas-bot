//
// Created by Shrey Patel on 11/19/2020.
//

#include "visualizer/player.h"

namespace naivebayes {

namespace visualizer {

    void player::Draw() {
        ci::gl::drawSolidCircle(centerPos, radius_);
    }

    void player::Update() {

        if (IsAirBorne()){
            velocity+=accel_;
            centerPos+=velocity;
        }else {
            centerPos.y = (float )window_height_- radius_;
        }

    }

    bool player::IsAirBorne() {
        if (centerPos.y < window_height_- radius_){
            return true;
        }
        return false;
    }

    void player::MoveLeft() {
        if (!IsAirBorne()){
            centerPos.x += -15.f;
            velocity.x = -15.f;
        }

    }

    void player::MoveRight() {
        if (!IsAirBorne()){
            centerPos.x += 15.f;
            velocity.x = 15.f;
        }
    }

    void player::Jump() {
        if (!IsAirBorne()){
            centerPos.y -= 15.f;
            velocity.y = -25.f;
        }


    }






}
}
