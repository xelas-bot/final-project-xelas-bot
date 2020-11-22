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
        void Jump();
        bool IsAirBorne();
        void Update();
        void Draw();

    private:


        glm::vec2 accel_ = {0,1};
        float height;
        float radius_ = (float ) 50.f;
        int32_t window_height_;
        int32_t window_width_;



    };
}}


#endif //NAIVE_BAYES_PLAYER_H
