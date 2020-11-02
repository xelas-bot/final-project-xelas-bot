#include <visualizer/naive_bayes_app.h>

using naivebayes::visualizer::NaiveBayesApp;

void prepareSettings(NaiveBayesApp::Settings* settings) {
  settings->setResizable(false);
  settings->setFrameRate(60);
}

// This line is a macro that expands into an "int main()" function.
CINDER_APP(NaiveBayesApp, ci::app::RendererGl, prepareSettings);
