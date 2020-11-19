//
// Created by Shrey Patel on 11/6/2020.
//

#ifndef NAIVE_BAYES_HISTOGRAM_H
#define NAIVE_BAYES_HISTOGRAM_H
#include "particle_handler.h"

namespace naivebayes {

    namespace visualizer {


        class Histogram {

        public:
            Histogram(particle_handler container, int windowSize, glm::vec2 leftCorner);
            Histogram(){}

            /**
             * Returns max speed of the particles within container, made public for testing purposes
             * @param mass seperate particles by mass
             * @return max speed
             */
            float MaxParticleSpeed(int mass);

            /**
             * Draws current histogram
             * @param masses list of three massses to graph
             */
            void Draw(std::vector<int> masses);

            /**
             * Updates histogram
             */
            void Update();





        private:
            particle_handler container_;
            int window_size_;
            glm::vec2 left_corner_;
            int max_count_ = 0;

            /**
             * Draws the chart given input data
             *
             * @param leftCorner positioning vector
             * @param mass of particles
             * @return vector of new corner for further histograms
             */
            glm::vec2 DrawChart(glm::vec2 leftCorner, int mass);

            /**
             * Returns number of particles between intervals
             *
             * @param sOne first interval
             * @param sTwo second interval
             * @param mass of particle to choose from
             * @return count of particles between interval
             */
            int GetCountBetweenInterval(float sOne, float sTwo, int mass);

            /**
             * Draws initial bouding square for histogram
             */
            void DrawBoundingSquare();

            /**
             * Draws number labels
             *
             * @param corner of histogram
             * @param lineL line length of axes
             * @param counts data needed to produce labels
             */
            void DrawLabels(glm::vec2 corner, float lineL, std::vector<int> counts);

        };





    }
}


#endif //NAIVE_BAYES_HISTOGRAM_H
