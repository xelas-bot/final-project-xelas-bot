//
// Created by Shrey Patel on 11/1/2020.
//
#include "cinder/gl/gl.h"

#ifndef NAIVE_BAYES_PARTICLE_H
#define NAIVE_BAYES_PARTICLE_H
namespace naivebayes {
    namespace visualizer {

        class particle {
        public:
            // Fields made public to simulate a data storage class

            glm::vec2 position_ = {0, 0};
            glm::vec2 velocity_ = {1, 1};
            int radius_ = 20;
            int mass_ = 1;

            /**
             * Main Constructor
             *
             * @param position vector of position coords
             * @param velocity vector of velocity
             */
            particle(glm::vec2 position, glm::vec2 velocity);


            particle(glm::vec2 position, glm::vec2 velocity, int mass, int radius);

            /**
             * Default empty constructor
             */
            particle() {

            }

            /**
             * Draws the particle with its current values
             */
            void Draw();

            /**
             * updates the particle using current position and velocity values
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


        };


    }
}

#endif  // NAIVE_BAYES_PARTICLE_H
