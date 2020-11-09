//
// Created by Shrey Patel on 11/6/2020.
//

#ifndef NAIVE_BAYES_HISTOGRAM_H
#define NAIVE_BAYES_HISTOGRAM_H
#include "particle_handler.h"

namespace naivebayes {

    namespace visualizer {


        class histogram {

        public:
            histogram(particle_handler container, int windowSize, glm::vec2 leftCorner){
                container_ = container;
                windowSize_ = windowSize;
                leftCorner_ = leftCorner;

            }
            histogram(){

            }

            void Draw();
            glm::vec2 DrawChart(glm::vec2 leftCorner, int mass);
            void Update();
            int GetCountBetweenInterval(float sOne, float sTwo, int mass);
            float MaxParticleSpeed(int mass);




        private:
            particle_handler container_;
            int windowSize_;
            glm::vec2 leftCorner_;

        };





    }
}


#endif //NAIVE_BAYES_HISTOGRAM_H
