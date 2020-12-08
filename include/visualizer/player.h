//
// Created by Shrey Patel on 11/19/2020.
//

#ifndef NAIVE_BAYES_PLAYER_H
#define NAIVE_BAYES_PLAYER_H
#pragma once

#include <cinder/app/AppBase.h>
#include "cinder/gl/gl.h"
#include "random"
#include "math.h"
#include "particle.h"

namespace naivebayes {


namespace visualizer {
    class player {

    public:
        player(int32_t windowHeight, int32_t windowWidth){
            window_height_=windowHeight;
            window_width_ = windowWidth;
            centerPos = {windowWidth/2,windowHeight/2};
            center_pos_leg = {centerPos.x +  (cos(theta_) * radial_arm_), centerPos.y + (sin(theta_) * radial_arm_)};
            auto img = loadImage(ci::app::loadAsset("head.png"));
            head_image_ = ci::gl::Texture2d::create(img);

        }
        glm::vec2 centerPos;
        glm::vec2 velocity;
        glm::vec2 center_pos_leg;

        player(){

        }

        void MoveRight();
        void MoveLeft();
        void KickLeg();
        void NextMove(Particle particle);
        glm::vec2 Jump();
        bool IsAirBorne();
        void Update();
        void Draw();
        void MidAirStrafeRight(glm::vec2 currentVel);
        void MidAirStrafeLeft(glm::vec2 currentVel);
        float radius_ = (float ) 45.f;
        glm::vec2 tangential_vel_ = {angular_vel_* radial_arm_ * sin(theta_),angular_vel_* radial_arm_ * cos(theta_) };
        float leg_radius_ = 20.0f;
        bool lefty_ = false;
        bool righty_ = false;

    private:


        glm::vec2 accel_ = {0,0.75};
        float height;
        float theta_ = (float )(1)*(float )M_PI * (8.0f/4.0f);

        float radial_arm_ = 80.0f;

        ci::gl::Texture2dRef head_image_;
        float angular_vel_ =0;
        int32_t window_height_;
        int32_t window_width_;
        bool leg_kicked_ = false;



        int r = rand() % 255;
        int g = rand() % 255;
        int b = rand() % 255;
        float re = (float) r / 255.f;
        float gr = (float) g / 255.f;
        float bl = (float) b / 255.f;



    };
}}


#endif //NAIVE_BAYES_PLAYER_H
