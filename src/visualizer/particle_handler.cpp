//
// Created by Shrey Patel on 11/1/2020.
//

#include "visualizer/particle_handler.h"
#include "random"
#include "visualizer/naive_bayes_app.h"
#include "math.h"

namespace naivebayes {
    namespace visualizer {
        void particle_handler::update() {

            for (size_t i = 0; i < currentParticles_.size(); i++) {


                if (currentParticles_.at(i)->position_.x < 20) {
                    currentParticles_.at(i)->vert_collision();

                } else if (currentParticles_.at(i)->position_.x > windowSize_ - 20) {
                    currentParticles_.at(i)->vert_collision();

                } else if (currentParticles_.at(i)->position_.y < 20) {
                    currentParticles_.at(i)->hor_collision();

                } else if (currentParticles_.at(i)->position_.y > windowSize_ - 20) {
                    currentParticles_.at(i)->hor_collision();

                } else {
                    if (currentParticles_.size() >= 2) {

                        particle* current;
                        current = currentParticles_.at(i);
                        particle* closest = getClosestParticle(current);

                        for (size_t x = 0; x<currentParticles_.size(); x ++){

                        }






                        if (getDistanceBetweenParticle(*currentParticles_.at(i), *closest) < 40) {

                            glm::vec2 velCur = current->velocity_;
                            glm::vec2 velClose = closest->velocity_;
                            glm::vec2 disDiff = current->position_ - closest->position_;
                            glm::vec2 disDiffTwo = closest->position_ - current->position_;


                            glm::vec2 currentNewVel =
                                    velCur -
                                            (((glm::dot(velCur - velClose, disDiff)) / (glm::length(disDiff) * glm::length(disDiff))) * (disDiff));


                            glm::vec2 closestNewVel = velClose -
                                                      ((glm::dot(velClose - velCur, disDiffTwo)) /
                                                       (glm::length(disDiffTwo) * glm::length(disDiffTwo))) *
                                                      (disDiffTwo);

                            closest->velocity_= closestNewVel;
                            current->velocity_ = currentNewVel;
                            closest->update();


                        }
                    }

                }


                currentParticles_.at(i)->update();
            }

        }

        void particle_handler::draw() {
            for (size_t i = 0; i < currentParticles_.size(); i++) {
                ci::gl::color(150, 150, 150);
                currentParticles_.at(i)->draw();
            }

        }


        void particle_handler::addParticle(int number) {

            for (int i = 0; i < number; i++) {
                float x = (float) rand() * windowSize_;
                float y = (float) rand() * windowSize_;
                double subtractor = rand() / (double) RAND_MAX;
                particle *temp = new particle({rand() % (windowSize_ - 60) + 20, rand() % (windowSize_ - 60) + 20},
                                              {2 * (rand() / (double) RAND_MAX) - subtractor,
                                               2 * (rand() / (double) RAND_MAX) - subtractor});
                currentParticles_.push_back(temp);
            }

        }

        float particle_handler::getDistanceBetweenParticle(particle thisParticle, particle other) {
            float xDis = thisParticle.position_.x - other.position_.x;
            float yDis = thisParticle.position_.y - other.position_.y;

            float distance = sqrt((xDis * xDis) + (yDis * yDis));
            return distance;


        }

        particle* particle_handler::getClosestParticle(particle* thisParticle) {
            float temp = 0;
            float distance = 0;
            particle* tempPart;

            for (size_t i = 0; i < currentParticles_.size(); i++) {
                if (getDistanceBetweenParticle(*thisParticle, *currentParticles_.at(i)) != 0) {
                    distance = getDistanceBetweenParticle(*thisParticle, *currentParticles_.at(i));
                    tempPart = currentParticles_.at(i);

                }
            }


            for (size_t i = 0; i < currentParticles_.size(); i++) {
                temp = getDistanceBetweenParticle(*thisParticle, *currentParticles_.at(i));
                if (temp < distance && temp != 0) {
                    distance = temp;
                    tempPart = currentParticles_.at(i);
                }

            }


            return tempPart;


        }


    }
}
