#include <visualizer/visual_app>

using naivebayes::visualizer::VisualApp;

void prepareSettings(VisualApp::Settings* settings) {
  settings->setResizable(false);
  settings->setFrameRate(100);
  settings->setFullScreen(true);
}

// This line is a macro that expands into an "int main()" function.

CINDER_APP(VisualApp, ci::app::RendererGl, prepareSettings);

