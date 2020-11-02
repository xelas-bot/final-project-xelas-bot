#include <visualizer/naive_bayes_app.h>

namespace naivebayes {

namespace visualizer {

NaiveBayesApp::NaiveBayesApp()
    : sketchpad_(glm::vec2(kMargin, kMargin), kImageDimension,
                 kWindowSize - 2 * kMargin) {
    particle_handler particleHandlerTemp((int )kWindowSize);

    particleHandler_ = particleHandlerTemp;
    std::cout << "hello";


  ci::app::setWindowSize((int) kWindowSize, (int) kWindowSize);

  particle particle({kWindowSize,kWindowSize}, {-10,-10});
  particle_ = particle;
}
void NaiveBayesApp::setup() {
    particleHandler_.addParticle(50);
}

void NaiveBayesApp::update() {
    //ci::Color8u background_color(0, 0, 0);  // black
    //ci::gl::clear(background_color);
    particleHandler_.update();



}

void NaiveBayesApp::draw() {
  ci::Color8u background_color(0, 0, 0);  // black
  ci::gl::clear(background_color,true);
  int xCen = (int)kWindowSize/2;
  int yCen = (int)kWindowSize/2;
  int pixelCount = 0;

    float x = (float) cos( getElapsedSeconds() ) * 100.0f;
    float y = (float)sin( getElapsedSeconds() ) * 100.0f;
    ci::Color("red");
    //ci::gl::drawSolidCircle( glm::vec2 ( x + getWindowSize().x/2, y + getWindowSize().y/2 ), 50 );

    particleHandler_.draw();





  ci::gl::drawStringCentered(
      "Press Delete to pause the sim. Press Enter to start the sim.",
      glm::vec2(kWindowSize / 2, kMargin / 2), ci::Color("white"));
    std::cout << "hello";

    particle* poi;
    poi = particleHandler_.currentParticles_.at(0);
    ci::gl::drawStringCentered(

      "Prediction: " + std::to_string(particleHandler_.getClosestParticle(poi)->position_.x)  ,
      glm::vec2(kWindowSize / 2, kWindowSize - kMargin / 2), ci::Color("white"));

}

void NaiveBayesApp::mouseDown(ci::app::MouseEvent event) {
  sketchpad_.HandleBrush(event.getPos());
}

void NaiveBayesApp::mouseDrag(ci::app::MouseEvent event) {
  sketchpad_.HandleBrush(event.getPos());
}

void NaiveBayesApp::keyDown(ci::app::KeyEvent event) {
  switch (event.getCode()) {
    case ci::app::KeyEvent::KEY_RETURN:





      break;

    case ci::app::KeyEvent::KEY_DELETE:
      sketchpad_.Clear();
      break;
  }
}

}  // namespace visualizer

}  // namespace naivebayes
