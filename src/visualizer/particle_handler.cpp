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
                int radius = currentParticles_.at(i)->kRadius;


                if (currentParticles_.at(i)->position_.x < radius && currentParticles_.at(i)->velocity_.x < 0) {
                    currentParticles_.at(i)->vert_collision();
                    currentParticles_.at(i)->update();

                } else if (currentParticles_.at(i)->position_.x > windowSize_ - radius &&
                           currentParticles_.at(i)->velocity_.x > 0) {
                    currentParticles_.at(i)->vert_collision();
                    currentParticles_.at(i)->update();

                } else if (currentParticles_.at(i)->position_.y < radius && currentParticles_.at(i)->velocity_.y < 0) {
                    currentParticles_.at(i)->hor_collision();
                    currentParticles_.at(i)->update();

                } else if (currentParticles_.at(i)->position_.y > windowSize_ - radius &&
                           currentParticles_.at(i)->velocity_.y > 0) {
                    currentParticles_.at(i)->hor_collision();
                    currentParticles_.at(i)->update();

                } else if (currentParticles_.size() >= 2) {
                    particle *current;
                    current = currentParticles_.at(i);
                    particle *closest = getClosestParticle(current);


                    if (getDistanceBetweenParticle(*currentParticles_.at(i), *closest) < 2 * radius
                        &&
                        glm::dot((current->velocity_ - closest->velocity_), (current->position_ - closest->position_)) <
                        0) {

                        glm::vec2 velCur = current->velocity_;
                        glm::vec2 velClose = closest->velocity_;
                        glm::vec2 disDiff = current->position_ - closest->position_;
                        glm::vec2 disDiffTwo = closest->position_ - current->position_;


                        glm::vec2 currentNewVel =
                                velCur -
                                (((glm::dot(velCur - velClose, disDiff)) /
                                  (glm::length(disDiff) * glm::length(disDiff))) * (disDiff));


                        glm::vec2 closestNewVel = velClose -
                                                  ((glm::dot(velClose - velCur, disDiffTwo)) /
                                                   (glm::length(disDiffTwo) * glm::length(disDiffTwo))) *
                                                  (disDiffTwo);

                        closest->velocity_ = closestNewVel;
                        current->velocity_ = currentNewVel;
                        current->update();
                        closest->update();


                    } else {
                        currentParticles_.at(i)->update();
                    }


                }


            }

        }

        void particle_handler::draw() {
            for (size_t i = 0; i < currentParticles_.size(); i++) {
                currentParticles_.at(i)->draw();
            }

        }

        void particle_handler::speedMultiplyer(double speedMult) {
            for (size_t i = 0; i < currentParticles_.size(); i++) {

                currentParticles_.at(i)->velocity_ *= speedMult;


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

        std::ostream &operator<<(std::ostream &out, const particle_handler &c) {
            for (size_t i = 0; i < c.currentParticles_.size(); i++) {
                out << c.currentParticles_.at(i)->position_.x << " " << c.currentParticles_.at(i)->position_.y
                    << std::endl;
                out << c.currentParticles_.at(i)->velocity_.x << " " << c.currentParticles_.at(i)->velocity_.y
                    << std::endl;
            }
            return out;

        }

        std::istream &operator>>(std::istream &in, particle_handler &c) {

            for (size_t i = 0; i < c.currentParticles_.size(); i++) {
                delete c.currentParticles_.at(i);
            }
            c.currentParticles_.clear();


            int lineNumber = 1;
            std::string str;
            particle *temp;
            while (std::getline(in, str)) {


                std::stringstream row_stream(str);
                float num = 0;
                std::vector<float> row;
                while (row_stream >> num) {
                    row.push_back(num);
                }
                if (lineNumber % 2 != 0) {
                    temp = new particle({row.at(0), row.at(1)}, {0, 0});
                }


                if (lineNumber % 2 == 0) {
                    temp->velocity_ = {row.at(0), row.at(1)};
                    c.currentParticles_.push_back(temp);
                }

                lineNumber++;
            }


            return in;

        }


        particle *particle_handler::getClosestParticle(particle *thisParticle) {
            float temp = 0;
            float distance = 0;
            particle *tempPart;

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
