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
            int particleCount_ = 0;

            int windowSize_;

            friend std::ostream &operator<<(std::ostream &out, const particle_handler &c);

            friend std::istream &operator>>(std::istream &in, particle_handler &c);




            particle_handler(int windowSize) {
                windowSize_ = windowSize;

            }

            particle_handler() {

            }

            void addParticle(int number);

            /**
             * Testing method to add particles in custom locations with custom velocities
             *
             * @param x position
             * @param y position
             * @param xVel x velocty
             * @param yVel y velocity
             */
            void addCustomParticle(float x, float y, float xVel, float yVel);

            void update();

            void speedMultiplyer(double speedMult);

            /**
             * Testing method that sums velocities of each particle
             *
             * @return: a float representing the sum total of each particle
             */
            float sumVel();

            void draw();



        private:
            std::vector<particle *> currentParticles_;
            float sumXVel = 0;
            float sumYVel = 0;
            particle *getClosestParticle(particle *thisParticle);

            float getDistanceBetweenParticle(particle thisParticle, particle other);


        };
    }
}

#endif //NAIVE_BAYES_PARTICLE_HANDLER_H
