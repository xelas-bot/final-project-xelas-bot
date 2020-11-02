#include <vector>
#include "particle.h"

//
// Created by Shrey Patel on 11/1/2020.
//

#ifndef NAIVE_BAYES_PARTICLE_HANDLER_H
#define NAIVE_BAYES_PARTICLE_HANDLER_H
namespace naivebayes {

    namespace visualizer {
        class particle_handler {
        public:
            std::vector<particle> currentParticles_;
            int windowSize_;

            particle_handler(int windowSize) {
                windowSize_ = windowSize;
            }
            particle_handler(){

            }

            void addParticle(int number);

            void update();

            void draw();


        };
    }
}

#endif //NAIVE_BAYES_PARTICLE_HANDLER_H
