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

            for (int i = 0; i < 500; i++) {
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

    TEST_CASE("Test updating particles") {
        SECTION("Test Position Change") {
            naivebayes::visualizer::particle_handler particleHandler(875);
            particleHandler.addCustomParticle(400, 400, -15.0f, 0);
            REQUIRE(particleHandler.currentParticles_.at(0)->position_.x == 400);
            particleHandler.update();
            REQUIRE(particleHandler.currentParticles_.at(0)->position_.x == 385);
            particleHandler.update();
            REQUIRE(particleHandler.currentParticles_.at(0)->position_.x == 370);

        }SECTION("Test Velocity/Position Change Simultaneously") {
            naivebayes::visualizer::particle_handler particleHandler(875);
            int updateCounter = 0;

            particleHandler.addCustomParticle(400, 400, -15.0f, 0);

            float currentVel = particleHandler.currentParticles_.at(0)->velocity_.x;

            float currentPos = 400;
            REQUIRE(particleHandler.currentParticles_.at(0)->position_.x == currentPos + currentVel * updateCounter);
            particleHandler.update();
            currentPos += currentVel * updateCounter;
            updateCounter++;


            REQUIRE(particleHandler.currentParticles_.at(0)->position_.x == currentPos + currentVel * updateCounter);
            particleHandler.update();
            currentPos += currentVel * updateCounter;
            updateCounter++;


            REQUIRE(particleHandler.currentParticles_.at(0)->position_.x == currentPos + currentVel);
            currentPos += currentVel;
            particleHandler.currentParticles_.at(0)->velocity_.x = 50.0f;
            particleHandler.update();
            currentVel = particleHandler.currentParticles_.at(0)->velocity_.x = 50.0f;
            REQUIRE(particleHandler.currentParticles_.at(0)->position_.x == currentPos + currentVel);


        }
    }

    TEST_CASE("Test Operator Overloading") {
        SECTION("Save and Load from file") {
            naivebayes::visualizer::particle_handler particleHandler(875);
            particleHandler.addCustomParticle(400, 400, 0, 15);
            particleHandler.addCustomParticle(400, 600, 0, 0);
            particleHandler.addCustomParticle(400, 800, 0, -15);


            std::ofstream myfile;
            myfile.open(
                    "C:/Users/Shrey Patel/Downloads/cinder_0.9.2_vc2015/my-projects/ideal-gas-xelas-bot/data/testingFile");
            myfile << particleHandler;
            myfile.close();


            naivebayes::visualizer::particle_handler particleHandlerTwo(875);
            std::ifstream file;
            file.open(
                    "C:/Users/Shrey Patel/Downloads/cinder_0.9.2_vc2015/my-projects/ideal-gas-xelas-bot/data/testingFile");
            file >> particleHandlerTwo;
            file.close();


            REQUIRE(particleHandlerTwo.currentParticles_.at(0)->position_.y == 400);
            REQUIRE(particleHandlerTwo.currentParticles_.at(1)->position_.y == 600);
            REQUIRE(particleHandlerTwo.currentParticles_.at(2)->position_.y == 800);

            REQUIRE(particleHandlerTwo.currentParticles_.at(0)->position_.x == 400);
            REQUIRE(particleHandlerTwo.currentParticles_.at(1)->position_.x == 400);
            REQUIRE(particleHandlerTwo.currentParticles_.at(2)->position_.x == 400);

            REQUIRE(particleHandlerTwo.currentParticles_.at(0)->velocity_.x == 0);
            REQUIRE(particleHandlerTwo.currentParticles_.at(1)->velocity_.x == 0);
            REQUIRE(particleHandlerTwo.currentParticles_.at(2)->velocity_.x == 0);

            REQUIRE(particleHandlerTwo.currentParticles_.at(0)->velocity_.y == 15);
            REQUIRE(particleHandlerTwo.currentParticles_.at(1)->velocity_.y == 0);
            REQUIRE(particleHandlerTwo.currentParticles_.at(2)->velocity_.y == -15);


        }
    }

}



