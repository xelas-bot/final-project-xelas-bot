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
            std::vector<particle*> currentParticles_;
            int windowSize_;
            friend std::ostream & operator << (std::ostream &out, const particle_handler &c);
            friend std::istream & operator >> (std::istream &in, particle_handler &c);


            particle_handler(int windowSize) {
                windowSize_ = windowSize;

            }
            particle_handler(){

            }

            void addParticle(int number);

            void update();
            void speedMultiplyer(double speedMult);

            void draw();
            particle* getClosestParticle(particle* thisParticle);
            float getDistanceBetweenParticle(particle thisParticle, particle other);


        };
    }
}

#endif //NAIVE_BAYES_PARTICLE_HANDLER_H
