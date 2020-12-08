#include <vector>
#include "particle.h"
#include "player.h"

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

            int32_t windowHeight_;
            int32_t windowWidth_;


            friend std::ostream &operator<<(std::ostream &out, const particle_handler &c);

            friend std::istream &operator>>(std::istream &in, particle_handler &c);



            /**
             * Main constructor
             *
             * @param windowSize the "size" of the container
             */
            particle_handler(int32_t windowHeight, int32_t windowWidth, player* player, class player* playerTwo);

            /**
             * Default constructor
             */
            particle_handler() {}


            /**
             * Add particles to the container
             *
             * @param number of particles to add
             */
            void addParticle(int number, int mass, int radius);

            /**
             * Testing method to add particles in custom locations with custom velocities
             *
             * @param x position
             * @param y position
             * @param xVel x velocty
             * @param yVel y velocity
             */
            void addCustomParticle(float x, float y, float xVel, float yVel);

            /**
             * Updates pos and vel of all particles in the container
             */
            void Update();

            void speedMultiplyer(double speedMult);

            /**
             * Testing method that sums velocities of each Particle
             *
             * @return: a float representing the sum total of each Particle
             */
            float sumVel();

            /**
             * Draws all particles in the Particle container
             */
            void draw();
            std::vector<Particle *> currentParticles_;



        private:
            visualizer::player* player_;
            visualizer::player* player_two_;

            float sumXVel_ = 0;
            float sumYVel_ = 0;
            Particle *getClosestParticle(Particle *thisParticle);

            float getDistanceBetweenParticle(Particle thisParticle, Particle other);


        };
    }
}

#endif //NAIVE_BAYES_PARTICLE_HANDLER_H