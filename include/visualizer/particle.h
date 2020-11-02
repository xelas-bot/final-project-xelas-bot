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
            glm::vec2 position_ = {0, 0};
            glm::vec2 velocity_ = {1, 1};

            particle(glm::vec2 position, glm::vec2 velocity) {
                position_ = position;
                velocity_ = velocity;
            }
            particle(){

            }

            void draw();

            void update();

            void vert_collision();

            void hor_collision();

            void particle_collision();


        };


    }
}

#endif  // NAIVE_BAYES_PARTICLE_H
