//
// Created by Shrey Patel on 11/19/2020.
//

#ifndef NAIVE_BAYES_PLAYER_H
#define NAIVE_BAYES_PLAYER_H
#pragma once
#include "cinder/gl/gl.h"
#include "random"
#include "math.h"

namespace naivebayes {


namespace visualizer {
    class player {

    public:
        player(int32_t windowHeight, int32_t windowWidth){
            window_height_=windowHeight;
            window_width_ = windowWidth;
            centerPos = {windowWidth/2,windowHeight/2};

        }
        glm::vec2 centerPos;
        glm::vec2 velocity;

        player(){

        }

        void MoveRight();
        void MoveLeft();
        glm::vec2 Jump();
        bool IsAirBorne();
        void Update();
        void Draw();
        void MidAirStrafeRight(glm::vec2 currentVel);
        void MidAirStrafeLeft(glm::vec2 currentVel);
        float radius_ = (float ) 50.f;

    private:


        glm::vec2 accel_ = {0,1};
        float height;

        int32_t window_height_;
        int32_t window_width_;

        int r = rand() % 255;
        int g = rand() % 255;
        int b = rand() % 255;
        float re = (float) r / 255.f;
        float gr = (float) g / 255.f;
        float bl = (float) b / 255.f;



    };
}}


#endif //NAIVE_BAYES_PLAYER_H
