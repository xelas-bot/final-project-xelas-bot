//
// Created by Shrey Patel on 11/6/2020.
//

#include "visualizer/histogram.h"

namespace naivebayes {
    namespace visualizer {
        Histogram::Histogram(particle_handler container, int windowSize, glm::vec2 leftCorner) {
            container_ = container;
            window_size_ = windowSize;
            left_corner_ = leftCorner;
        }

        void Histogram::Draw(std::vector<int> masses) {

            // Draw Box
            DrawBoundingSquare();

            glm::vec2 firstVec = DrawChart({left_corner_.x + 40, left_corner_.y}, masses[0]);
            glm::vec2 secVec = DrawChart({firstVec.x + 40, left_corner_.y}, masses[1]);
            DrawChart({secVec.x + 40, left_corner_.y}, masses[2]);


        }

        void Histogram::DrawLabels(glm::vec2 corner, float lineL, std::vector<int> counts) {
            float interval = lineL / 5;
            std::vector<int> rounded;
            int toPush = 0;

            float max = (float) (container_.currentParticles_.size() * (double) 0.33333333333);


            for (int i = 1; i <= 5; i++) {
                rounded.push_back((int) round((((double) i * (20)) / 100) * max));

            }

            for (int i = 1; i <= 5; i++) {
                ci::gl::drawLine({corner.x, corner.y - ((float) rounded[i - 1] / max) * lineL},
                                 {corner.x + lineL + 20, corner.y - ((float) rounded[i - 1] / max) * lineL});


                ci::Font("arial", 8);
                ci::gl::drawStringCentered(
                        std::to_string(rounded.at(i - 1)),
                        {corner.x - 8, corner.y - (((float) rounded[i - 1] / max) * lineL) - 5}, ci::Color("white"));
            }


        }

        void Histogram::DrawBoundingSquare() {
            ci::gl::lineWidth(1);
            ci::gl::drawLine(left_corner_, {left_corner_.x, left_corner_.y + window_size_});
            glm::vec2 tempVec = {left_corner_.x, left_corner_.y + window_size_};


            ci::gl::lineWidth(1);
            ci::gl::drawLine(tempVec, {tempVec.x + 5 * window_size_, tempVec.y});
            tempVec = {tempVec.x + 5 * window_size_, tempVec.y};

            ci::gl::lineWidth(1);
            ci::gl::drawLine(tempVec, {tempVec.x, tempVec.y - window_size_});
            tempVec = {tempVec.x, tempVec.y - window_size_};

            ci::gl::lineWidth(1);
            ci::gl::drawLine(tempVec, {tempVec.x - 5 * window_size_, tempVec.y});
            tempVec = {tempVec.x - 5 * window_size_, tempVec.y};
        }

        int Histogram::GetCountBetweenInterval(float sOne, float sTwo, int mass) {

            float temp = 0;
            int count = 0;
            for (size_t i = 0; i < container_.currentParticles_.size(); i++) {
                temp = glm::length(container_.currentParticles_.at(i)->velocity_);

                if (temp < sTwo && temp >= sOne && container_.currentParticles_.at(i)->mass_ == mass) {
                    count++;
                }

            }


            return count;
        }

        float Histogram::MaxParticleSpeed(int mass) {

            if (container_.currentParticles_.size() == 1) {
                return glm::length(container_.currentParticles_.at(0)->velocity_);
            }

            float max_speed = 0;

            for (size_t i = 0; i < container_.currentParticles_.size(); i++) {
                float temp = glm::length(container_.currentParticles_.at(i)->velocity_);
                if (temp >= max_speed && container_.currentParticles_.at(i)->mass_ == mass) {
                    max_speed = temp;
                }
            }


            return max_speed;
        }


        glm::vec2 Histogram::DrawChart(glm::vec2 leftCorner, int mass) {
            // Drawing Axes

            ci::gl::lineWidth(1);
            ci::gl::drawLine({leftCorner.x + 10, leftCorner.y + 10},
                             {leftCorner.x + 10, leftCorner.y + window_size_ - 10});

            ci::gl::drawLine({leftCorner.x + 10, leftCorner.y + window_size_ - 10},
                             {leftCorner.x + 10 + window_size_, leftCorner.y + window_size_ - 10});


            int pixelWorkspace = (int) leftCorner.x + 10 + (int) window_size_ - (int) leftCorner.x + 10;


            glm::vec2 newCorner = {leftCorner.x + 10, leftCorner.y + window_size_ - 10};
            int yMax = (int) leftCorner.y + (int) window_size_ - 10 - (int) leftCorner.y + 10 - 20;

            // Label Axes

            DrawLabels({leftCorner.x + 10, leftCorner.y + window_size_ - 10}, (float) yMax, {});

            ci::gl::lineWidth((float) pixelWorkspace);
            int lineW = 10;

            double max = ceil((double) MaxParticleSpeed(mass)) + 1;

            float interval = (float) max / 10;

            // Creating Text

            ci::Font font("arial", 18);
            ci::gl::drawStringCentered(
                    "Histogram intervals are\n " + std::to_string((double) ceil((double) interval)),
                    glm::vec2(left_corner_.x - 70, left_corner_.y + 20), ci::Color("white"), font);

            // Initializing data vectors

            std::vector<int> intCounts;
            std::vector<float> heights;
            for (int i = 1; i <= 10; i++) {

                intCounts.push_back(
                        GetCountBetweenInterval(((float) i - 1) * (float) interval, ((float) i) * (float) interval,
                                                mass));

            }

            for (size_t i = 0; i < intCounts.size(); i++) {


                heights.push_back((float) ((float) 3 * intCounts[i] / (float) container_.currentParticles_.size()) *
                                  (float) yMax);
            }

            for (size_t i = 1; i <= heights.size(); i++) {
                ci::gl::drawLine({newCorner.x + (i * lineW) - 5, newCorner.y},
                                 {newCorner.x + (i * lineW) - 5, newCorner.y - heights[i - 1]});

            }


            glm::vec2 toReturn = {leftCorner.x + 10 + window_size_, leftCorner.y};
            return toReturn;


        }


    }
}
