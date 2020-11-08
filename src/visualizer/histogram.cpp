//
// Created by Shrey Patel on 11/6/2020.
//

#include "visualizer/histogram.h"

namespace naivebayes {
    namespace visualizer {

        void histogram::Draw() {

            // Draw Box

            ci::gl::lineWidth(1);
            ci::gl::drawLine(leftCorner_, {leftCorner_.x, leftCorner_.y + windowSize_});
            glm::vec2 tempVec = {leftCorner_.x, leftCorner_.y + windowSize_};


            ci::gl::lineWidth(1);
            ci::gl::drawLine(tempVec, {tempVec.x + 5 * windowSize_, tempVec.y});
            tempVec = {tempVec.x + 5 * windowSize_, tempVec.y};

            ci::gl::lineWidth(1);
            ci::gl::drawLine(tempVec, {tempVec.x, tempVec.y - windowSize_});
            tempVec = {tempVec.x, tempVec.y - windowSize_};

            ci::gl::lineWidth(1);
            ci::gl::drawLine(tempVec, {tempVec.x - 5 * windowSize_, tempVec.y});
            tempVec = {tempVec.x - 5 * windowSize_, tempVec.y};


            //DrawChart({leftCorner_});

            glm::vec2 secVec = DrawChart(DrawChart({leftCorner_}));
            DrawChart(secVec);


        }

        int histogram::GetCountBetweenInterval(float sOne, float sTwo) {

            float temp = 0;
            int count=0;
            for (size_t i = 0; i < container_.currentParticles_.size(); i++) {
                temp = glm::length(container_.currentParticles_.at(i)->velocity_);

                if (temp < sTwo && temp > sOne){
                    count++;
                }

            }


            return count;
        }

        float histogram::MaxParticleSpeed() {
            float max_speed = glm::length(container_.currentParticles_.at(0)->velocity_);

            for (size_t i = 0; i < container_.currentParticles_.size(); i++) {
                float temp = glm::length(container_.currentParticles_.at(i)->velocity_);
                if (temp >= max_speed) {
                    max_speed = temp;
                }
            }


            return max_speed;
        }


        glm::vec2 histogram::DrawChart(glm::vec2 leftCorner) {
            ci::gl::lineWidth(1);
            ci::gl::drawLine({leftCorner.x + 10, leftCorner.y + 10},
                             {leftCorner.x + 10, leftCorner.y + windowSize_ - 10});

            ci::gl::drawLine({leftCorner.x + 10, leftCorner.y + windowSize_ - 10},
                             {leftCorner.x + 10 + windowSize_, leftCorner.y + windowSize_ - 10});

            int pixelWorkspace = (int) leftCorner.x + 10 + (int) windowSize_ - (int) leftCorner.x + 10;

            int xOfFirstLine = (int) pixelWorkspace / 3;

            glm::vec2 newCorner = {leftCorner.x + 10, leftCorner.y + windowSize_ - 10};
            int yMax = (int) leftCorner.y + (int) windowSize_ - 10 - (int) leftCorner.y + 10 - 20;


            ci::gl::lineWidth((float) pixelWorkspace);


            float heightNeg = 0;
            float heightPos = 0;
            int numNeg = 0;
            int numPos = 0;

            for (size_t i = 0; i < container_.currentParticles_.size(); i++) {
                if (container_.currentParticles_.at(i)->velocity_.x < 0) {
                    numNeg++;
                }
                if (container_.currentParticles_.at(i)->velocity_.x > 0) {
                    numPos++;
                }
            }




            heightNeg = (float) ((float) numNeg / container_.particleCount_) * yMax;
            heightPos = (float) ((float) numPos / container_.particleCount_) * yMax;
            int lineW=5;


            double max = ceil((double ) MaxParticleSpeed());
            float interval = (float )max/5;

            int one = GetCountBetweenInterval(0, interval);
            int two = GetCountBetweenInterval(interval, 2*interval);
            int three = GetCountBetweenInterval(2*interval, 3*interval);
            int four = GetCountBetweenInterval(3*interval, 4*interval);
            int five = GetCountBetweenInterval(4*interval, 5*interval);

            float heightOne =(float) ((float) one / container_.particleCount_) * yMax;
            float heightTwo =(float) ((float) two / container_.particleCount_) * yMax;
            float heightThree =(float) ((float) three / container_.particleCount_) * yMax;
            float heightFour =(float) ((float) four / container_.particleCount_) * yMax;
            float heightFive =(float) ((float) five / container_.particleCount_) * yMax;



            ci::gl::drawLine({newCorner.x + lineW, newCorner.y},
                             {newCorner.x + lineW, newCorner.y - heightOne});


            ci::gl::drawLine({newCorner.x + 3 * lineW, newCorner.y},
                             {newCorner.x + 3 * lineW, newCorner.y - heightTwo});

            ci::gl::drawLine({newCorner.x + 5 * lineW, newCorner.y},
                             {newCorner.x + 5 * lineW, newCorner.y - heightThree});

            ci::gl::drawLine({newCorner.x + 7 * lineW, newCorner.y},
                             {newCorner.x + 7 * lineW, newCorner.y - heightFour});


            ci::gl::drawLine({newCorner.x + 9 * lineW, newCorner.y},
                             {newCorner.x + 9 * lineW, newCorner.y - heightFive});



            glm::vec2 toReturn = {leftCorner.x + 10 + windowSize_, leftCorner.y};
            return toReturn;


        }


    }
}
