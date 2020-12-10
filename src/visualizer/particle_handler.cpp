//
// Created by Shrey Patel on 11/1/2020.
//

#include "visualizer/particle_handler.h"
#include "random"
#include "visualizer/visual_app"
#include "math.h"

namespace engine {
    namespace visualizer {
        Particle_handler::Particle_handler(int32_t windowHeight, int32_t windowWidth, Player *player,
                                           class Player *playerTwo) {
            windowHeight_ = windowHeight;
            windowWidth_ = windowWidth;
            player_ = player;
            player_two_ = playerTwo;

            // Load Audio
            ci::audio::SourceFileRef sourceFile = ci::audio::load(ci::app::loadAsset("kick.mp3"));
            ball_hit_ = ci::audio::Voice::create(sourceFile);

            // Loading Player/Ball Resources
            Particle *temp = new Particle({player_->centerPos.x, player_->centerPos.y},
                                          {player_->velocity.x, player_->velocity.y}, (int) 4, (int) player_->radius_);
            temp->is_player = true;
            temp->is_leg = false;
            currentParticles_.push_back(temp);

            Particle *tempTwo = new Particle({player_two_->centerPos.x, player_two_->centerPos.y},
                                             {player_two_->velocity.x, player_two_->velocity.y}, (int) 4,
                                             (int) player_two_->radius_);
            tempTwo->is_player = true;
            tempTwo->is_leg = false;
            currentParticles_.push_back(tempTwo);


            Particle *leg = new Particle({player_->center_pos_leg.x, player_->center_pos_leg.y},
                                         {player_->tangential_vel_.x, player_->tangential_vel_.y}, (int) 4,
                                         (int) player_->leg_radius_);
            leg->is_player = false;
            leg->is_leg = true;
            currentParticles_.push_back(leg);

            Particle *legTwo = new Particle({player_two_->center_pos_leg.x, player_two_->center_pos_leg.y},
                                            {player_two_->tangential_vel_.x, player_two_->tangential_vel_.y}, (int) 4,
                                            (int) player_two_->leg_radius_);
            legTwo->is_player = false;
            legTwo->is_leg = true;
            currentParticles_.push_back(legTwo);

        }

        void Particle_handler::Update() {
            if (!testing_mode_){
                Particle *temp = currentParticles_.at(0);
                temp->position_ = player_->centerPos;
                temp->velocity_ = player_->velocity;

                Particle *tempTwo = currentParticles_.at(1);
                tempTwo->position_ = player_two_->centerPos;
                tempTwo->velocity_ = player_two_->velocity;

                Particle *leg = currentParticles_.at(2);
                leg->position_ = player_->center_pos_leg;
                leg->velocity_ = player_->tangential_vel_;
                leg->mass_ = 10;
                leg->radius_ = (int) player_->leg_radius_;
                leg->is_player = false;
                leg->is_leg = true;

                Particle *legTwo = currentParticles_.at(3);
                legTwo->position_ = player_two_->center_pos_leg;
                legTwo->velocity_ = player_two_->tangential_vel_;
                legTwo->mass_ = 10;
                legTwo->radius_ = (int) player_two_->leg_radius_;
                legTwo->is_player = false;
                legTwo->is_leg = true;
            }

            for (size_t i = 0; i < currentParticles_.size(); i++) {
                if (true) {
                    int radius = currentParticles_.at(i)->radius_;
                    currentParticles_.at(i)->k_accel_ = {0, 0.75};

                    if (currentParticles_.at(i)->position_.x <= 100+radius){
                        if (currentParticles_.at(i)->position_.y >= windowHeight_ - 300-radius){
                            currentParticles_.at(i)->HorCollision();
                            currentParticles_.at(i)->Update();
                        }

                    }else if (currentParticles_.at(i)->position_.x >= windowWidth_-radius){

                            if (currentParticles_.at(i)->position_.y >= windowHeight_ - 300-radius){
                                currentParticles_.at(i)->HorCollision();
                                currentParticles_.at(i)->Update();
                            }
                    }

                    if (currentParticles_.at(i)->position_.x < radius && currentParticles_.at(i)->velocity_.x < 0) {
                        currentParticles_.at(i)->VertCollision();
                        currentParticles_.at(i)->Update();

                    } else if (currentParticles_.at(i)->position_.x > windowWidth_ - radius &&
                               currentParticles_.at(i)->velocity_.x > 0) {
                        currentParticles_.at(i)->VertCollision();
                        currentParticles_.at(i)->Update();

                    } else if (currentParticles_.at(i)->position_.y < radius &&
                               currentParticles_.at(i)->velocity_.y < 0) {
                        currentParticles_.at(i)->HorCollision();
                        currentParticles_.at(i)->Update();

                    } else if (currentParticles_.at(i)->position_.y >= windowHeight_ - radius &&
                               currentParticles_.at(i)->velocity_.y >= 0) {

                        currentParticles_.at(i)->HorCollision();
                        currentParticles_.at(i)->FallCollision();

                    } else if (currentParticles_.size() >= 2) {
                        Particle *current;
                        current = currentParticles_.at(i);
                        Particle *closest = getClosestParticle(current);


                        if (getDistanceBetweenParticle(*currentParticles_.at(i), *closest) < radius + closest->radius_
                            &&
                            glm::dot((current->velocity_ - closest->velocity_),
                                     (current->position_ - closest->position_)) <
                            0) {

                            glm::vec2 velCur = current->velocity_;
                            glm::vec2 velClose = closest->velocity_;
                            glm::vec2 disDiff = current->position_ - closest->position_;
                            glm::vec2 disDiffTwo = closest->position_ - current->position_;

                            float massMultiplierOne = (2 * closest->mass_) / (float) (current->mass_ + closest->mass_);
                            float massMultiplierTwo = (2 * current->mass_) / (float) (current->mass_ + closest->mass_);
                            if (!testing_mode_){
                                ball_hit_->start();
                            }



                            glm::vec2 currentNewVel =
                                    velCur -
                                    (massMultiplierOne * ((glm::dot(velCur - velClose, disDiff)) /
                                                          (glm::length(disDiff) * glm::length(disDiff))) * (disDiff));


                            glm::vec2 closestNewVel = velClose -
                                                      massMultiplierTwo * ((glm::dot(velClose - velCur, disDiffTwo)) /
                                                                           (glm::length(disDiffTwo) *
                                                                            glm::length(disDiffTwo))) *
                                                      (disDiffTwo);

                            closest->velocity_ = closestNewVel;
                            current->velocity_ = currentNewVel;
                            current->Update();
                            closest->Update();


                        } else {
                            currentParticles_.at(i)->Update();
                        }


                    }

                    if (currentParticles_.size() == 1) {
                        currentParticles_.at(i)->Update();
                    }

                }
            }


        }

        void const Particle_handler::Draw() {
            currentParticles_.at(currentParticles_.size() - 1)->Draw();

        }

        void Particle_handler::SpeedMultiplyer(double speedMult) {
            for (size_t i = 0; i < currentParticles_.size(); i++) {

                currentParticles_.at(i)->velocity_ *= speedMult;


            }


        }


        void Particle_handler::AddParticle(int number, int mass, int radius) {

            Particle particleRad;


            for (int i = 0; i < number; i++) {
                float x = (float) rand() * windowWidth_;
                float y = (float) rand() * windowHeight_;
                double subtractor = rand() / (double) RAND_MAX;
                Particle *temp = new Particle(
                        {rand() % (windowWidth_ - 2 * radius) + radius, rand() % (windowHeight_ - 2 * radius) + radius},
                        {2 * (rand() / (double) RAND_MAX) - subtractor,
                         2 * (rand() / (double) RAND_MAX) - subtractor}, mass, radius);
                currentParticles_.push_back(temp);
                particleCount_++;
            }

        }

        float Particle_handler::getDistanceBetweenParticle(Particle thisParticle, Particle other) {
            float xDis = thisParticle.position_.x - other.position_.x;
            float yDis = thisParticle.position_.y - other.position_.y;

            float distance = sqrt((xDis * xDis) + (yDis * yDis));
            return distance;


        }

        std::ostream &operator<<(std::ostream &out, const Particle_handler &c) {
            for (size_t i = 0; i < c.currentParticles_.size(); i++) {
                out << c.currentParticles_.at(i)->position_.x << " " << c.currentParticles_.at(i)->position_.y
                    << std::endl;
                out << c.currentParticles_.at(i)->velocity_.x << " " << c.currentParticles_.at(i)->velocity_.y
                    << std::endl;
            }
            return out;

        }

        void Particle_handler::AddCustomParticle(float x, float y, float xVel, float yVel) {
            Particle *temp;
            if (!testing_mode_){
                temp = new Particle({x, y}, {xVel, yVel},2,40);
            }else {
                temp = new Particle({x, y}, {xVel, yVel});
            }
            currentParticles_.push_back(temp);
            particleCount_++;

        }

        float Particle_handler::SumVel() {
            float sumX = 0;
            float sumY = 0;
            float KE = 0;


            for (size_t i = 0; i < currentParticles_.size(); i++) {
                sumX += currentParticles_.at(i)->velocity_.x * currentParticles_.at(i)->velocity_.x;
                sumY += currentParticles_.at(i)->velocity_.y * currentParticles_.at(i)->velocity_.y;
                KE += (glm::length(currentParticles_.at(i)->velocity_) *
                       glm::length(currentParticles_.at(i)->velocity_)) * (currentParticles_.at(i)->mass_);
            }

            sumXVel_ = sumX;
            sumYVel_ = sumY;

            return KE;


        }

        std::istream &operator>>(std::istream &in, Particle_handler &c) {

            for (size_t i = 0; i < c.currentParticles_.size(); i++) {
                delete c.currentParticles_.at(i);
            }
            c.currentParticles_.clear();


            int lineNumber = 1;
            std::string str;
            Particle *temp;
            while (std::getline(in, str)) {


                std::stringstream row_stream(str);
                float num = 0;
                std::vector<float> row;
                while (row_stream >> num) {
                    row.push_back(num);
                }
                if (lineNumber % 2 != 0) {
                    temp = new Particle({row.at(0), row.at(1)}, {0, 0});
                }


                if (lineNumber % 2 == 0) {
                    temp->velocity_ = {row.at(0), row.at(1)};
                    c.currentParticles_.push_back(temp);
                }

                lineNumber++;
            }


            return in;

        }


        Particle *Particle_handler::getClosestParticle(Particle *thisParticle) {

            if (thisParticle->is_leg) {
                return currentParticles_.at(currentParticles_.size() - 1);
            }
            if (thisParticle->is_player) {
                return currentParticles_.at(currentParticles_.size() - 1);
            }

            float dist = getDistanceBetweenParticle(*thisParticle, *currentParticles_.at(0));
            Particle *iter = currentParticles_.at(0);
            for (size_t i = 0; i < currentParticles_.size(); i++) {
                if (currentParticles_.at(i) != thisParticle) {
                    if (getDistanceBetweenParticle(*thisParticle, *currentParticles_.at(i)) <= dist) {
                        dist = getDistanceBetweenParticle(*thisParticle, *currentParticles_.at(i));
                        iter = currentParticles_.at(i);
                    }
                }


            }

            return iter;
        }


    }
}
