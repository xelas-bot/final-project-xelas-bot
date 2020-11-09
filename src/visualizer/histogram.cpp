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

            glm::vec2 firstVec = DrawChart(leftCorner_,1);
            glm::vec2 secVec = DrawChart(firstVec,100);
            DrawChart(secVec,200);


        }

        int histogram::GetCountBetweenInterval(float sOne, float sTwo, int mass) {

            float temp = 0;
            int count=0;
            for (size_t i = 0; i < container_.currentParticles_.size(); i++) {
                temp = glm::length(container_.currentParticles_.at(i)->velocity_);

                if (temp < sTwo && temp > sOne && container_.currentParticles_.at(i)->mass_ == mass){
                    count++;
                }

            }


            return count;
        }

        float histogram::MaxParticleSpeed(int mass) {
            float max_speed = 0;

            for (size_t i = 0; i < container_.currentParticles_.size(); i++) {
                float temp = glm::length(container_.currentParticles_.at(i)->velocity_);
                if (temp >= max_speed && container_.currentParticles_.at(i)->mass_ == mass) {
                    max_speed = temp;
                }
            }


            return max_speed;
        }


        glm::vec2 histogram::DrawChart(glm::vec2 leftCorner, int mass) {
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


            double max = ceil((double ) MaxParticleSpeed(mass));
            float interval = (float  )max/5;

            int one = GetCountBetweenInterval(0, interval,mass);
            int two = GetCountBetweenInterval(interval, 2*interval,mass);
            int three = GetCountBetweenInterval(2*interval, 3*interval,mass);
            int four = GetCountBetweenInterval(3*interval, 4*interval,mass);
            int five = GetCountBetweenInterval(4*interval, 5*interval,mass);

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
