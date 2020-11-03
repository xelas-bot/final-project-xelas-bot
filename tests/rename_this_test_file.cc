#include <catch2/catch.hpp>

#define private public

#include <core/testing.h>
#include "visualizer/particle_handler.h"
#include "visualizer/particle.h"

namespace naivebayes {


    TEST_CASE("Test Distance/Collisions") {
        //testing calculations is unncecessary since we can simply test if velocity is conserved after/before collision


        SECTION("Horizontal Collision") {
            naivebayes::visualizer::particle_handler particleHandler(875);
            particleHandler.addCustomParticle(400, 400, 10, 0);
            particleHandler.addCustomParticle(600, 400, -5, 0);
            REQUIRE(particleHandler.currentParticles_.at(0)->velocity_.x == 10.0f);
            REQUIRE(particleHandler.currentParticles_.at(1)->velocity_.x == -5.0f);

            float velSum = particleHandler.sumVel();

            while (particleHandler.currentParticles_.at(0)->velocity_.x == 10.0f) {
                particleHandler.update();
            }
            REQUIRE(particleHandler.currentParticles_.at(0)->velocity_.x != 10.0f);
            REQUIRE(particleHandler.currentParticles_.at(1)->velocity_.x != -5.0f);
            REQUIRE(velSum == particleHandler.sumVel());
        }SECTION("Verticle Collision") {
            naivebayes::visualizer::particle_handler particleHandler(875);
            particleHandler.addCustomParticle(400, 400, 0, 15);
            particleHandler.addCustomParticle(400, 600, 0, -6.89f);
            REQUIRE(particleHandler.currentParticles_.at(0)->velocity_.y == 15.0f);
            REQUIRE(particleHandler.currentParticles_.at(1)->velocity_.y == -6.89f);

            float velSum = particleHandler.sumVel();

            while (particleHandler.currentParticles_.at(0)->velocity_.y == 15.0f) {
                particleHandler.update();
            }
            REQUIRE(particleHandler.currentParticles_.at(0)->velocity_.y != 15.0f);
            REQUIRE(particleHandler.currentParticles_.at(1)->velocity_.y != -6.89f);
            REQUIRE(velSum == particleHandler.sumVel());
        }SECTION("Diagonal Collision") {
            naivebayes::visualizer::particle_handler particleHandler(875);
            particleHandler.addCustomParticle(400, 600, 10, 15);
            particleHandler.addCustomParticle(500, 700, -20, -30);
            REQUIRE(particleHandler.currentParticles_.at(0)->velocity_.y == 15.0f);
            REQUIRE(particleHandler.currentParticles_.at(1)->velocity_.y == -30.0f);
            REQUIRE(particleHandler.currentParticles_.at(0)->velocity_.x == 10.0f);
            REQUIRE(particleHandler.currentParticles_.at(1)->velocity_.x == -20.0f);

            float velSum = particleHandler.sumVel();

            while (particleHandler.currentParticles_.at(0)->velocity_.y == 15.0f) {
                particleHandler.update();
            }

            REQUIRE(particleHandler.currentParticles_.at(0)->velocity_.y != 15.0f);
            REQUIRE(particleHandler.currentParticles_.at(1)->velocity_.y != -30.0f);
            REQUIRE(particleHandler.currentParticles_.at(0)->velocity_.x != 10.0f);
            REQUIRE(particleHandler.currentParticles_.at(1)->velocity_.x != -20.0f);

            REQUIRE(velSum == Approx(particleHandler.sumVel()));
        }SECTION("Triple Collision") {
            naivebayes::visualizer::particle_handler particleHandler(875);
            particleHandler.addCustomParticle(400, 400, 0, 15);
            particleHandler.addCustomParticle(400, 600, 0, 0);
            particleHandler.addCustomParticle(400, 800, 0, -15);

            REQUIRE(particleHandler.currentParticles_.at(0)->velocity_.y == 15.0f);
            REQUIRE(particleHandler.currentParticles_.at(2)->velocity_.y == -15.0f);

            float velSum = particleHandler.sumVel();

            while (particleHandler.currentParticles_.at(0)->velocity_.y == 15.0f) {
                particleHandler.update();
            }
            REQUIRE(particleHandler.currentParticles_.at(0)->velocity_.y != 15.0f);
            REQUIRE(particleHandler.currentParticles_.at(2)->velocity_.y != -15.0f);
            REQUIRE(velSum == particleHandler.sumVel());
        }SECTION("Multiple Collisions Velocity Conserved") {
            naivebayes::visualizer::particle_handler particleHandler(875);
            int radius = 40;
            particleHandler.addCustomParticle((float) (rand() % 800) + radius, (float) (rand() % 800) + radius,
                                              (float) (rand() % 10), (float) (rand() % 10));
            particleHandler.addCustomParticle((float) (rand() % 800) + radius, (float) (rand() % 800) + radius,
                                              (float) (rand() % 10), (float) (rand() % 10));
            particleHandler.addCustomParticle((float) (rand() % 800) + radius, (float) (rand() % 800) + radius,
                                              (float) (rand() % 10), (float) (rand() % 10));
            particleHandler.addCustomParticle((float) (rand() % 800) + radius, (float) (rand() % 800) + radius,
                                              (float) (rand() % 10), (float) (rand() % 10));
            particleHandler.addCustomParticle((float) (rand() % 800) + radius, (float) (rand() % 800) + radius,
                                              (float) (rand() % 10), (float) (rand() % 10));
            particleHandler.addCustomParticle((float) (rand() % 800) + radius, (float) (rand() % 800) + radius,
                                              (float) (rand() % 10), (float) (rand() % 10));
            particleHandler.addCustomParticle((float) (rand() % 800) + radius, (float) (rand() % 800) + radius,
                                              (float) (rand() % 10), (float) (rand() % 10));


            float velSum = particleHandler.sumVel();

            for (int i = 0; i < 50; i++) {
                particleHandler.update();
            }

            REQUIRE(velSum == Approx(particleHandler.sumVel()));
        }SECTION("Wall Collision X") {
            // just testing for position bounding and bouncing no need to check for velocity
            naivebayes::visualizer::particle_handler particleHandler(875);
            particleHandler.addCustomParticle(400, 400, 15.0f, 0);

            int radius = particleHandler.currentParticles_.at(0)->kRadius;


            float velSum = particleHandler.sumVel();

            REQUIRE(particleHandler.currentParticles_.at(0)->velocity_.x == 15.0f);

            while (particleHandler.currentParticles_.at(0)->velocity_.x == 15.0f) {
                particleHandler.update();
            }


            REQUIRE(particleHandler.currentParticles_.at(0)->position_.x <=
                    particleHandler.windowSize_ - radius + 5); //5 pixel leeway


            REQUIRE(particleHandler.currentParticles_.at(0)->velocity_.x == -15.0f);
            REQUIRE(velSum == particleHandler.sumVel());


        }SECTION("Wall Collision Y") {
            // just testing for position bounding and bouncing no need to check for velocity
            naivebayes::visualizer::particle_handler particleHandler(875);
            particleHandler.addCustomParticle(400, 400, 0, 15.0f);

            int radius = particleHandler.currentParticles_.at(0)->kRadius;


            float velSum = particleHandler.sumVel();

            REQUIRE(particleHandler.currentParticles_.at(0)->velocity_.y == 15.0f);

            while (particleHandler.currentParticles_.at(0)->velocity_.y == 15.0f) {
                particleHandler.update();
            }


            REQUIRE(particleHandler.currentParticles_.at(0)->position_.y <=
                    particleHandler.windowSize_ - radius + 5); // 5 pixel leeway


            REQUIRE(particleHandler.currentParticles_.at(0)->velocity_.y == -15.0f);
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



