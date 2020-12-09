#include <catch2/catch.hpp>

#define private public

#include <core/testing.h>
#include "visualizer/particle_handler.h"
#include "visualizer/particle.h"
#include "visualizer/player.h"
#include <cinder/app/AppBase.h>
#include "cinder/gl/gl.h"

namespace engine {


    TEST_CASE("Test Distance/Collisions") {
        //testing calculations is unncecessary since we can simply test if velocity is conserved after/before collision


        SECTION("Horizontal Collision") {
            engine::visualizer::Particle_handler ParticleHandler;
            ParticleHandler.testing_mode_ = true;

            ParticleHandler.AddCustomParticle(400, 400, 10, 0);
            ParticleHandler.AddCustomParticle(600, 400, -5, 0);

            REQUIRE(ParticleHandler.currentParticles_.at(0)->velocity_.x == 10.0f);
            REQUIRE(ParticleHandler.currentParticles_.at(1)->velocity_.x == -5.0f);

            float velSum = ParticleHandler.SumVel();

            while (ParticleHandler.currentParticles_.at(0)->velocity_.x == 10.0f) {
                ParticleHandler.Update();
            }
            REQUIRE(ParticleHandler.currentParticles_.at(0)->velocity_.x != 10.0f);
            REQUIRE(ParticleHandler.currentParticles_.at(1)->velocity_.x != -5.0f);
            REQUIRE(velSum == 250.f);

        }SECTION("Verticle Collision") {
            engine::visualizer::Particle_handler ParticleHandler;
            ParticleHandler.testing_mode_ = true;

            ParticleHandler.AddCustomParticle(400, 400, 0, 15);
            ParticleHandler.AddCustomParticle(400, 600, 0, -6.89f);

            REQUIRE(ParticleHandler.currentParticles_.at(0)->velocity_.y == 15.0f);
            REQUIRE(ParticleHandler.currentParticles_.at(1)->velocity_.y == -6.89f);

            float velSum = ParticleHandler.SumVel();

            while (ParticleHandler.currentParticles_.at(0)->velocity_.y == 15.0f) {
                ParticleHandler.Update();
            }
            REQUIRE(ParticleHandler.currentParticles_.at(0)->velocity_.y != 15.0f);
            REQUIRE(ParticleHandler.currentParticles_.at(1)->velocity_.y != -6.89f);
            REQUIRE(velSum == Approx(544.944f));
        }SECTION("Diagonal Collision") {
            engine::visualizer::Particle_handler ParticleHandler;
            ParticleHandler.testing_mode_ = true;
            ParticleHandler.AddCustomParticle(400, 600, 10, 15);
            ParticleHandler.AddCustomParticle(500, 700, -20, -30);

            REQUIRE(ParticleHandler.currentParticles_.at(0)->velocity_.y == 15.0f);
            REQUIRE(ParticleHandler.currentParticles_.at(1)->velocity_.y == -30.0f);
            REQUIRE(ParticleHandler.currentParticles_.at(0)->velocity_.x == 10.0f);
            REQUIRE(ParticleHandler.currentParticles_.at(1)->velocity_.x == -20.0f);

            float velSum = ParticleHandler.SumVel();

            while (ParticleHandler.currentParticles_.at(0)->velocity_.y == 15.0f) {
                ParticleHandler.Update();
            }

            REQUIRE(ParticleHandler.currentParticles_.at(0)->velocity_.y != 15.0f);
            REQUIRE(ParticleHandler.currentParticles_.at(1)->velocity_.y != -30.0f);
            REQUIRE(ParticleHandler.currentParticles_.at(0)->velocity_.x == 10.0f);
            REQUIRE(ParticleHandler.currentParticles_.at(1)->velocity_.x == -20.0f);

            REQUIRE(velSum == Approx(3249.99));
        }SECTION("Multiple Collisions Velocity Conserved") {
            engine::visualizer::Particle_handler ParticleHandler;
            ParticleHandler.testing_mode_ = true;

            int radius = 40;
            ParticleHandler.AddCustomParticle((float) (rand() % 800) + radius, (float) (rand() % 800) + radius,
                                              (float) (rand() % 10), (float) (rand() % 10));
            ParticleHandler.AddCustomParticle((float) (rand() % 800) + radius, (float) (rand() % 800) + radius,
                                              (float) (rand() % 10), (float) (rand() % 10));
            ParticleHandler.AddCustomParticle((float) (rand() % 800) + radius, (float) (rand() % 800) + radius,
                                              (float) (rand() % 10), (float) (rand() % 10));
            ParticleHandler.AddCustomParticle((float) (rand() % 800) + radius, (float) (rand() % 800) + radius,
                                              (float) (rand() % 10), (float) (rand() % 10));
            ParticleHandler.AddCustomParticle((float) (rand() % 800) + radius, (float) (rand() % 800) + radius,
                                              (float) (rand() % 10), (float) (rand() % 10));
            ParticleHandler.AddCustomParticle((float) (rand() % 800) + radius, (float) (rand() % 800) + radius,
                                              (float) (rand() % 10), (float) (rand() % 10));
            ParticleHandler.AddCustomParticle((float) (rand() % 800) + radius, (float) (rand() % 800) + radius,
                                              (float) (rand() % 10), (float) (rand() % 10));


            float velSum = ParticleHandler.SumVel();

            for (int i = 0; i < 500; i++) {
                ParticleHandler.Update();
            }

            REQUIRE((3.51548f) * velSum == Approx(ParticleHandler.SumVel()));
        }SECTION("Wall Collision X Forward") {
            // just testing for position bounding and bouncing no need to check for velocity
            engine::visualizer::Particle_handler ParticleHandler;
            ParticleHandler.testing_mode_ = true;
            ParticleHandler.AddCustomParticle(400, 400, 15.0f, 0);

            int radius = ParticleHandler.currentParticles_.at(0)->radius_;


            float velSum = ParticleHandler.SumVel();

            REQUIRE(ParticleHandler.currentParticles_.at(0)->velocity_.x == 15.0f);

            while (ParticleHandler.currentParticles_.at(0)->velocity_.x == 15.0f) {
                ParticleHandler.Update();
            }


            REQUIRE(ParticleHandler.currentParticles_.at(0)->position_.x <=
                    875 - radius + 5); //5 pixel leeway


            REQUIRE(ParticleHandler.currentParticles_.at(0)->velocity_.x == -15.0f);


        }SECTION("Wall Collision X Backward") {
            // just testing for position bounding and bouncing no need to check for velocity
            engine::visualizer::Particle_handler ParticleHandler;
            ParticleHandler.testing_mode_ = true;
            ParticleHandler.AddCustomParticle(400, 400, -15.0f, 0);

            int radius = ParticleHandler.currentParticles_.at(0)->radius_;


            float velSum = ParticleHandler.SumVel();

            REQUIRE(ParticleHandler.currentParticles_.at(0)->velocity_.x == -15.0f);

            while (ParticleHandler.currentParticles_.at(0)->velocity_.x == -15.0f) {
                ParticleHandler.Update();
            }


            REQUIRE(ParticleHandler.currentParticles_.at(0)->position_.x >=
                    0 + radius + 5); //5 pixel leeway


            REQUIRE(ParticleHandler.currentParticles_.at(0)->velocity_.x == 15.0f);


        }SECTION("Wall Collision Y Down") {
            // just testing for position bounding and bouncing no need to check for velocity
            engine::visualizer::Particle_handler ParticleHandler;
            ParticleHandler.testing_mode_ = true;
            ParticleHandler.AddCustomParticle(400, 400, 0, 15.0f);

            int radius = ParticleHandler.currentParticles_.at(0)->radius_;


            float velSum = ParticleHandler.SumVel();

            REQUIRE(ParticleHandler.currentParticles_.at(0)->velocity_.y == 15.0f);

            while (ParticleHandler.currentParticles_.at(0)->velocity_.y == 15.0f) {
                ParticleHandler.Update();
            }


            REQUIRE(ParticleHandler.currentParticles_.at(0)->position_.y <=
                    875 - radius + 5); // 5 pixel leeway


            REQUIRE(ParticleHandler.currentParticles_.at(0)->velocity_.y == 15.75f);


        }SECTION("Erroneous Collisions") {
            // just testing for position bounding and bouncing no need to check for velocity
            engine::visualizer::Particle_handler ParticleHandler;
            ParticleHandler.testing_mode_ = true;
            ParticleHandler.AddCustomParticle(400, 400, -15.0f, 0);
            ParticleHandler.AddCustomParticle(419, 400, 15.0f, 0);

            int radius = ParticleHandler.currentParticles_.at(0)->radius_;


            float velSum = ParticleHandler.SumVel();

            REQUIRE(ParticleHandler.currentParticles_.at(0)->velocity_.x == -15.0f);
            REQUIRE(ParticleHandler.currentParticles_.at(1)->velocity_.x == 15.0f);

            for (int i = 0; i < 20; i++) {
                ParticleHandler.Update();
            }

            REQUIRE(ParticleHandler.currentParticles_.at(0)->velocity_.x == -15.0f);
            REQUIRE(ParticleHandler.currentParticles_.at(1)->velocity_.x == 15.0f);


        }


    }

    TEST_CASE("Test updating particles") {
        SECTION("Test Position Change") {
            engine::visualizer::Particle_handler ParticleHandler;
            ParticleHandler.testing_mode_ = true;

            ParticleHandler.AddCustomParticle(400, 400, -15.0f, 0);
            REQUIRE(ParticleHandler.currentParticles_.at(0)->position_.x == 400);
            ParticleHandler.Update();
            REQUIRE(ParticleHandler.currentParticles_.at(0)->position_.x == 385);
            ParticleHandler.Update();
            REQUIRE(ParticleHandler.currentParticles_.at(0)->position_.x == 370);

        }SECTION("Test Velocity/Position Change Simultaneously") {
            engine::visualizer::Particle_handler ParticleHandler;
            ParticleHandler.testing_mode_ = true;
            int UpdateCounter = 0;

            ParticleHandler.AddCustomParticle(400, 400, -15.0f, 0);

            float currentVel = ParticleHandler.currentParticles_.at(0)->velocity_.x;

            float currentPos = 400;
            REQUIRE(ParticleHandler.currentParticles_.at(0)->position_.x == currentPos + currentVel * UpdateCounter);
            ParticleHandler.Update();
            currentPos += currentVel * UpdateCounter;
            UpdateCounter++;


            REQUIRE(ParticleHandler.currentParticles_.at(0)->position_.x == currentPos + currentVel * UpdateCounter);
            ParticleHandler.Update();
            currentPos += currentVel * UpdateCounter;
            UpdateCounter++;


            REQUIRE(ParticleHandler.currentParticles_.at(0)->position_.x == currentPos + currentVel);
            currentPos += currentVel;
            ParticleHandler.currentParticles_.at(0)->velocity_.x = 50.0f;
            ParticleHandler.Update();
            currentVel = ParticleHandler.currentParticles_.at(0)->velocity_.x = 50.0f;
            REQUIRE(ParticleHandler.currentParticles_.at(0)->position_.x == currentPos + currentVel);


        }
    }


}
