//
// Created by Shrey Patel on 11/1/2020.
//
#pragma once
#include <cinder/app/AppBase.h>
#include "cinder/gl/gl.h"
#include "random"

#ifndef NAIVE_BAYES_PARTICLE_H
#define NAIVE_BAYES_PARTICLE_H
namespace naivebayes {
    namespace visualizer {

        class Particle {
        public:
            // Data Fields

            glm::vec2 position_ = {0, 0};
            glm::vec2 velocity_ = {1, 1};
            glm::vec2 accel_ = {0, 0.5};
            int radius_ = 40;
            int mass_ = 2;
            bool is_leg = false;
            bool is_player = false;

            void FallCollision();

            /**
             * Main Constructor
             *
             * @param position vector of position coords
             * @param velocity vector of velocity
             */
            Particle(glm::vec2 position, glm::vec2 velocity);


            Particle(glm::vec2 position, glm::vec2 velocity, int mass, int radius);

            /**
             * Default empty constructor
             */
            Particle() {

            }

            /**
             * Draws the Particle with its current values
             */
            void Draw();

            /**
             * updates the Particle using current position and velocity values
             */
            void Update();

            /**
             * Simulates a verticle wall collision
             */
            void VertCollision();

            /**
             * Simulates a horizontal wall collision
             */
            void HorCollision();



        private:
            int r = rand() % 255;
            int g = rand() % 255;
            int b = rand() % 255;
            float re = (float) r / 255.f;
            float gr = (float) g / 255.f;
            float bl = (float) b / 255.f;
            ci::gl::Texture2dRef ball_img_;


        };


    }
}

#endif  // NAIVE_BAYES_PARTICLE_H
