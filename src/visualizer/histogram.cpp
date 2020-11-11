//
// Created by Shrey Patel on 11/6/2020.
//

#include "visualizer/histogram.h"

namespace naivebayes {
    namespace visualizer {

        void histogram::Draw(std::vector<int> masses) {

            ci::Font("ariel", 8);
            ci::gl::drawStringCentered(
                    "Number Of Particles: \n Each Horizontal\n Bar is 5 particles",
                    glm::vec2(leftCorner_.x-50,leftCorner_.y+20), ci::Color("white"));


            // Draw Box
            DrawBoundingSquare();

            glm::vec2 firstVec = DrawChart({leftCorner_.x+40,leftCorner_.y}, masses[0]);
            glm::vec2 secVec = DrawChart({firstVec.x+40,leftCorner_.y}, masses[1]);
            DrawChart({secVec.x+40,leftCorner_.y}, masses[2]);


        }
        void histogram::DrawLabels(glm::vec2 corner, float lineL, std::vector<int> counts) {
            float interval = lineL/5;
            std::vector<int> rounded;
            int toPush =0;

            float max = (float ) (container_.currentParticles_.size() * (double)0.33333333333);


            for (int i =1; i<=5; i++){
                rounded.push_back((int )round((((double)i * (20))/100) * max));

            }




            for (int i =1; i<=5; i++){
                ci::gl::drawLine({corner.x,corner.y - ((float)rounded[i-1]/max)*lineL}, {corner.x +lineL +20, corner.y - ((float)rounded[i-1]/max)*lineL});


                ci::Font("arial", 8);
                ci::gl::drawStringCentered(
                        std::to_string(rounded.at(i-1)),
                        {corner.x-8,corner.y - (((float)rounded[i-1]/max)*lineL)-5}, ci::Color("white"));
            }




        }

        void histogram::DrawBoundingSquare() {
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
        }

        int histogram::GetCountBetweenInterval(float sOne, float sTwo, int mass) {

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

        float histogram::MaxParticleSpeed(int mass) {

            if (container_.currentParticles_.size() ==1){
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




            DrawLabels({leftCorner.x + 10, leftCorner.y + windowSize_ - 10},(float)yMax, {});





            ci::gl::lineWidth((float) pixelWorkspace);


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

            int lineW = 10;


            double max = ceil((double) MaxParticleSpeed(mass)) + 1;

            float interval = (float) max / 10;

            std::vector<int> intCounts;
            std::vector<float> heights;
            for (int i=1; i<=10; i++){

                intCounts.push_back(GetCountBetweenInterval(((float )i-1)*(float )interval, ((float )i)*(float )interval, mass));

            }

            std::cout << "{";
            for (size_t i = 0; i<intCounts.size(); i++){
                std::cout << intCounts.at(i);

            }
            std::cout << "}";




            for (size_t i = 0; i<intCounts.size(); i++){


                heights.push_back((float) ((float) 3*intCounts[i] / (float )container_.currentParticles_.size()) * (float )yMax);
            }
            std::cout << "{";
            for (size_t i = 0; i<heights.size(); i++){
                std::cout << heights.at(i);
                std::cout << ",";
            }
            std::cout << "}";



            for (size_t i = 1; i<=heights.size(); i++){
                ci::gl::drawLine({newCorner.x + (i* lineW) -5, newCorner.y},
                                 {newCorner.x + (i* lineW) -5, newCorner.y - heights[i-1]});

            }











            glm::vec2 toReturn = {leftCorner.x + 10 + windowSize_, leftCorner.y};
            return toReturn;


        }


    }
}
