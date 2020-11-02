//
// Created by Shrey Patel on 11/1/2020.
//

#include "visualizer/particle_handler.h"
#include "random"
#include "visualizer/naive_bayes_app.h"
namespace naivebayes{
namespace visualizer{
    void particle_handler::update() {
        for (size_t i=0; i<currentParticles_.size(); i++){
            currentParticles_.at(i).update();
        }

    }

    void particle_handler::draw() {
        for (size_t i=0; i<currentParticles_.size(); i++){
            currentParticles_.at(i).draw();
        }

    }


    void particle_handler::addParticle(int number) {

        for (int i =0; i<number; i++){
            float x = (float )rand() * windowSize_;
            float y = (float )rand() * windowSize_;
            double subtractor =  rand()/ (double) RAND_MAX;
            particle* temp  = new particle({rand()% (windowSize_-20),rand()%(windowSize_ -20)}, {(rand()/ (double) RAND_MAX) - subtractor, (rand()/ (double) RAND_MAX) - subtractor});
            currentParticles_.push_back(*temp);
        }

    }



}
}
