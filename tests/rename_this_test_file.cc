#include <catch2/catch.hpp>

#include <core/testing.h>
#include "visualizer/particle_handler.h"
#include "visualizer/particle.h"

namespace naivebayes{


    TEST_CASE("Test Distance/Collisions") {
        //testing calculations is unncecessary since we can simply test if velocity is conserved after/before collision


        SECTION("Horizontal Collision"){
            naivebayes::visualizer::particle_handler particleHandler(875);
            particleHandler.addCustomParticle(400,400, 10, 0);
            particleHandler.addCustomParticle(600,400, -5, 0);
            REQUIRE(particleHandler.currentParticles_.at(0)->velocity_.x == 10.0f);
            REQUIRE(particleHandler.currentParticles_.at(1)->velocity_.x == -5.0f);

            float velSum = particleHandler.sumVel();

            while(particleHandler.currentParticles_.at(0)->velocity_.x == 10.0f){
                particleHandler.update();
            }
            REQUIRE(particleHandler.currentParticles_.at(0)->velocity_.x != 10.0f);
            REQUIRE(particleHandler.currentParticles_.at(1)->velocity_.x != -5.0f);
            REQUIRE(velSum == particleHandler.sumVel());
        }
        SECTION("Verticle Collision"){
            naivebayes::visualizer::particle_handler particleHandler(875);
            particleHandler.addCustomParticle(400,400, 0, 15);
            particleHandler.addCustomParticle(400,600, 0, -6.89f);
            REQUIRE(particleHandler.currentParticles_.at(0)->velocity_.y == 15.0f);
            REQUIRE(particleHandler.currentParticles_.at(1)->velocity_.y == -6.89f);

            float velSum = particleHandler.sumVel();

            while(particleHandler.currentParticles_.at(0)->velocity_.y == 15.0f){
                particleHandler.update();
            }
            REQUIRE(particleHandler.currentParticles_.at(0)->velocity_.y != 15.0f);
            REQUIRE(particleHandler.currentParticles_.at(1)->velocity_.y != -6.89f);
            REQUIRE(velSum == particleHandler.sumVel());
        }
        SECTION("Triple Collision"){
            naivebayes::visualizer::particle_handler particleHandler(875);
            particleHandler.addCustomParticle(400,400, 0, 15);
            particleHandler.addCustomParticle(400,600, 0, -6.89f);
            REQUIRE(particleHandler.currentParticles_.at(0)->velocity_.y == 15.0f);
            REQUIRE(particleHandler.currentParticles_.at(1)->velocity_.y == -6.89f);

            float velSum = particleHandler.sumVel();

            while(particleHandler.currentParticles_.at(0)->velocity_.y == 15.0f){
                particleHandler.update();
            }
            REQUIRE(particleHandler.currentParticles_.at(0)->velocity_.y != 15.0f);
            REQUIRE(particleHandler.currentParticles_.at(1)->velocity_.y != -6.89f);
            REQUIRE(velSum == particleHandler.sumVel());
        }







    }

    TEST_CASE("Test Particle Velocities") {
        REQUIRE(naivebayes::Placeholder().GetBestClass() == "CS 126");
    }
    TEST_CASE("Test Particle Positions") {
        REQUIRE(naivebayes::Placeholder().GetBestClass() == "CS 126");
    }
    TEST_CASE("Test updating particles") {
        REQUIRE(naivebayes::Placeholder().GetBestClass() == "CS 126");
    }
    TEST_CASE("Test Operator Overloading") {
        REQUIRE(naivebayes::Placeholder().GetBestClass() == "CS 126");
    }

}



