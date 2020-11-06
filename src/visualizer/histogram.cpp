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
            ci::gl::drawLine(tempVec, {tempVec.x + 5*windowSize_ , tempVec.y});
            tempVec = {tempVec.x + 5*windowSize_ , tempVec.y};

            ci::gl::lineWidth(1);
            ci::gl::drawLine(tempVec, {tempVec.x  , tempVec.y - windowSize_});
            tempVec = {tempVec.x  , tempVec.y - windowSize_};

            ci::gl::lineWidth(1);
            ci::gl::drawLine(tempVec, {tempVec.x -5*windowSize_  , tempVec.y});
            tempVec = {tempVec.x -5*windowSize_  , tempVec.y};


            DrawChart({leftCorner_});






        }


        void histogram::DrawChart(glm::vec2 leftCorner) {
            ci::gl::lineWidth(1);
            ci::gl::drawLine({leftCorner.x + 10, leftCorner.y +10},{leftCorner.x+10, leftCorner.y +windowSize_ - 10});

            ci::gl::drawLine({leftCorner.x+10, leftCorner.y +windowSize_ - 10},{leftCorner.x+10 + windowSize_, leftCorner.y +windowSize_ - 10});

            int pixelWorkspace =  (int )leftCorner.x+10 + (int )windowSize_ - (int)leftCorner.x+10;

            int xOfFirstLine = (int )pixelWorkspace/3;

            glm::vec2 newCorner = {leftCorner.x+10, leftCorner.y +windowSize_ - 10};
            int yMax = (int ) leftCorner.y + (int )windowSize_ - 10 - (int )leftCorner.y +10 -20 ;


            ci::gl::lineWidth((float )pixelWorkspace);



            float heightNeg =0;
            float heightPos =0;
            int numNeg=0;
            int numPos=0;

            for (size_t i=0; i<container_.currentParticles_.size(); i++){
                if (container_.currentParticles_.at(i)->velocity_.x <0){
                    numNeg++;
                }
                if (container_.currentParticles_.at(i)->velocity_.x >0){
                    numPos++;
                }
            }

            heightNeg = (float )((float )numNeg/container_.particleCount_) * yMax;
            heightPos = (float )((float )numPos/container_.particleCount_) * yMax;






            ci::gl::drawLine({newCorner.x + pixelWorkspace/3, newCorner.y} ,{newCorner.x + pixelWorkspace/3, newCorner.y - heightPos });




            ci::gl::drawLine({newCorner.x + 2*pixelWorkspace/3, newCorner.y} ,{newCorner.x + 2*pixelWorkspace/3, newCorner.y - heightNeg });







        }


    }
}
