#include <vector>
#include <cinder/audio/Voice.h>
#include "particle.h"
#include "player.h"

//
// Created by Shrey Patel on 11/1/2020.
//

#ifndef NAIVE_BAYES_PARTICLE_HANDLER_H
#define NAIVE_BAYES_PARTICLE_HANDLER_H
namespace engine {

    namespace visualizer {
        class Particle_handler {
        public:


            std::vector<Particle *> currentParticles_;
            bool testing_mode_ = false;


            /**
             * Main Constructor
             *
             * @param windowHeight height of container
             * @param windowWidth width of container
             * @param player first Player position data
             * @param playerTwo second Player position data
             */
            Particle_handler(int32_t windowHeight, int32_t windowWidth, Player* player, class Player* playerTwo);

            /**
             * Default constructor
             */
            Particle_handler() {}


            /**
             * Add particles to the container
             *
             * @param number of particles to add
             */
            void AddParticle(int number, int mass, int radius);

            /**
             * Testing method to add particles in custom locations with custom velocities
             *
             * @param x position
             * @param y position
             * @param xVel x velocty
             * @param yVel y velocity
             */
            void AddCustomParticle(float x, float y, float xVel, float yVel);

            /**
             * Updates pos and vel of all particles in the container
             */
            void Update();

            /**
             * Multiplies the speed of the particles
             *
             * @param speedMult multiplier
             */
            void SpeedMultiplyer(double speedMult);

            /**
             * Testing method that sums velocities of each Particle
             *
             * @return: a float representing the sum total of each Particle
             */
            float SumVel();

            /**
             * Draws all particles in the Particle container
             */
            void const Draw();

            friend std::ostream &operator<<(std::ostream &out, const Particle_handler &c);

            friend std::istream &operator>>(std::istream &in, Particle_handler &c);

        private:

            // Game State Variables
            visualizer::Player* player_;
            visualizer::Player* player_two_;
            ci::audio::VoiceRef ball_hit_;

            // Visualizer Variables
            int particleCount_ = 0;
            int32_t windowHeight_=875;
            int32_t windowWidth_=875;

            float sumXVel_ = 0;
            float sumYVel_ = 0;
            Particle *getClosestParticle(Particle *thisParticle);

            float getDistanceBetweenParticle(Particle thisParticle, Particle other);


        };
    }
}

#endif //NAIVE_BAYES_PARTICLE_HANDLER_H