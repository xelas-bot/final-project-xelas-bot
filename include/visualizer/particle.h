//
// Created by Shrey Patel on 11/1/2020.
//
#pragma once
#include <cinder/app/AppBase.h>
#include "cinder/gl/gl.h"
#include "random"

#ifndef NAIVE_BAYES_PARTICLE_H
#define NAIVE_BAYES_PARTICLE_H
namespace engine {
    namespace visualizer {

        class Particle {
        public:
            // Data Fields made public within scope of particle handler

            glm::vec2 position_ = {0, 0};
            glm::vec2 velocity_ = {1, 1};

            // Default values if not specified

            glm::vec2 k_accel_ = {0, 0.5};
            int radius_ = 40;
            int mass_ = 2;
            bool is_leg = false;
            bool is_player = false;

            /**
             * Simulates a gravity fall collision
             *
             */

            void FallCollision();

            /**
             * Main Constructor
             *
             * @param position vector of position coords
             * @param velocity vector of velocity
             */
            Particle(glm::vec2 position, glm::vec2 velocity);

            /**
             * Alternate Constructor
             *
             * @param position
             * @param velocity
             * @param mass
             * @param radius
             */
            Particle(glm::vec2 position, glm::vec2 velocity, int mass, int radius);

            /**
             * Default empty constructor
             */
            Particle() {

            }

            /**
             * Draws the Particle with its current values
             */
            void const Draw();

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

            //RGB channel variables

            int r_ = rand() % 255;
            int g_ = rand() % 255;
            int b_ = rand() % 255;
            float re = (float) r_ / 255.f;
            float gr = (float) g_ / 255.f;
            float bl = (float) b_ / 255.f;

            // Texture File for ball
            ci::gl::Texture2dRef ball_img_;



        };


    }
}

#endif  // NAIVE_BAYES_PARTICLE_H
