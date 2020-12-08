//
// Created by Shrey Patel on 11/19/2020.
//

#include "visualizer/player.h"


namespace naivebayes {

namespace visualizer {

    void player::Draw() {



        //ci::gl::color(ci::Color("white"));
        //ci::gl::drawSolidCircle(centerPos, radius_);

        ci::gl::pushModelMatrix();
        ci::gl::translate(centerPos - glm::vec2(radius_,radius_));
        ci::gl::scale(2.0f*radius_/head_image_->getWidth(), 2.0f*radius_/head_image_->getHeight());
        ci::gl::color(1,1,1);
        ci::gl::draw(head_image_);
        ci::gl::popModelMatrix();



        //ci::gl::color(re, gr, bl);
        //ci::gl::drawSolidCircle({centerPos.x-20,centerPos.y-10}, 10);
        //ci::gl::drawSolidCircle({centerPos.x+20,centerPos.y-10}, 10);

        if (lefty_){
            ci::gl::color(ci::Color("red"));
        }else {
            ci::gl::color(ci::Color("blue"));
        }

        ci::gl::drawSolidCircle(center_pos_leg,leg_radius_);

    }
    void player::NextMove(Particle particle) {
        glm::vec2 vel = particle.velocity_;
        glm::vec2 ball_center_pos = particle.position_;

        float xDiff = centerPos.x - ball_center_pos.x;
        float yDiff = centerPos.y - ball_center_pos.y;

        if (ball_center_pos.x < (ci::app::getWindowWidth()/2)-200){
            MoveRight();
            KickLeg();
            if (centerPos.x == ci::app::getWindowWidth()-200){
                velocity.x=0;
            }
        }else{
            if (xDiff >= 0 && xDiff <= 25 && yDiff <=175 ){
                velocity.x=0;
                KickLeg();
                Jump();
                MoveLeft();
            }else{

                if (centerPos.x <= ball_center_pos.x){
                    if (!(xDiff >= 0 && xDiff <= 25)){
                        MoveRight();
                    }else{
                        velocity.x=0;
                    }

                }else {
                    if (!(xDiff >= 0 && xDiff <= 25)){
                        MoveLeft();
                    }else {
                        velocity.x=0;
                    }
                }

            }

        }








    }

    void player::Update() {

        tangential_vel_ = {velocity.x - (angular_vel_* radial_arm_ * sin(theta_)),velocity.y - (angular_vel_* radial_arm_ * cos(theta_)) };
        if (centerPos.x <= radius_+2){
            velocity.x = 0;
            centerPos.x += 2;
        }else if (centerPos.x >= window_width_-radius_-2){
            velocity.x = 0;
            centerPos.x -= 2;
        }
        if (IsAirBorne()){
            velocity+=accel_;
            centerPos+=velocity;
        }else {
            velocity.y=0;
            centerPos.y = (float )window_height_- radius_ + 2;
            centerPos.x += velocity.x;

        }
        if (righty_){
            if (leg_kicked_){
                angular_vel_ = 0.2f;
                tangential_vel_ = {velocity.x - (angular_vel_* radial_arm_ * sin(theta_)),velocity.y - (angular_vel_* radial_arm_ * cos(theta_)) };
                float end = (float )(1)*(float )M_PI * (10.0f/4.0f);
                if (theta_ < end ){
                    theta_ = theta_ + angular_vel_;
                }else {
                    theta_ = (float )(1)*(float )M_PI * (7.0f/4.0f);
                    leg_kicked_ = false;
                    angular_vel_ = 0;
                }
            }
        }
        if (lefty_){
            if (leg_kicked_){
                angular_vel_ = -0.2f;
                tangential_vel_ = {velocity.x - (angular_vel_* radial_arm_ * sin(theta_)),velocity.y - (angular_vel_* radial_arm_ * cos(theta_)) };
                float end = (float )(1)*(float )M_PI * (2.0f/3.0f);
                if (theta_ > end ){
                    theta_ = theta_ + angular_vel_;
                }else {
                    theta_ = (float )(1)*(float )M_PI * (5.0f/4.0f);
                    leg_kicked_ = false;
                    angular_vel_ = 0;
                }
            }
        }



        center_pos_leg = {centerPos.x +  (cos(theta_) * radial_arm_), centerPos.y - ((sin(theta_)) * radial_arm_)};





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

    void player::KickLeg() {
        leg_kicked_ = true;

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
