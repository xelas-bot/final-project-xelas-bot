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

namespace engine {
    namespace visualizer {
        class Player {

        public:

            // Public Default Physics Variables for Particle handler
            glm::vec2 centerPos;
            glm::vec2 velocity;
            glm::vec2 center_pos_leg;
            float radius_ = (float) 45.f;
            glm::vec2 tangential_vel_ = {angular_vel_ * radial_arm_ * sin(theta_),
                                         angular_vel_ * radial_arm_ * cos(theta_)};
            float leg_radius_ = 20.0f;
            bool lefty_ = false;
            bool righty_ = false;

            /**
             * Main Constructor
             *
             * @param windowHeight height of container
             * @param windowWidth width of container
             */
            Player(int32_t windowHeight, int32_t windowWidth);

            Player() {}

            /**
             * Moves Player right
             *
             */
            void MoveRight();

            /**
             * Move Player left
             *
             */
            void MoveLeft();

            /**
             * Initiates kick leg sequence
             *
             */
            void KickLeg();

            /**
             * Sends next move to AI Player
             *
             * @param particle object to get location and speed
             */
            void NextMove(Particle particle);

            /**
             * Initiates jump sequence
             *
             * @return velocity pre-jump
             */
            glm::vec2 Jump();

            /**
             * Idenitifies if Player is airborne
             *
             * @return true if Player is airborne, false otherwise
             */
            bool IsAirBorne();

            /**
             * Updates Player position and velocity
             *
             */
            void Update();

            /**
             * Draws Player and leg
             *
             */
            void const Draw();

            /**
             * Allows Player to move in midair
             *
             * @param currentVel of Player
             */
            void MidAirStrafeRight(glm::vec2 currentVel);

            /**
             * Allows Player to move in midair
             *
             * @param currentVel of Player
             */
            void MidAirStrafeLeft(glm::vec2 currentVel);

        private:


            glm::vec2 accel_ = {0, 0.75};


            // Leg Physics Variables
            float height;
            float theta_ = (float) (1) * (float) M_PI * (8.0f / 4.0f);
            float radial_arm_ = 80.0f;
            float angular_vel_ = 0;
            bool leg_kicked_ = false;


            // Container Data
            int32_t window_height_;
            int32_t window_width_;

            // Image Data
            ci::gl::Texture2dRef head_image_;


            // RGB Channels
            int r = rand() % 255;
            int g = rand() % 255;
            int b = rand() % 255;
            float re = (float) r / 255.f;
            float gr = (float) g / 255.f;
            float bl = (float) b / 255.f;


        };
    }
}


#endif //NAIVE_BAYES_PLAYER_H
