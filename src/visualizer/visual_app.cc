#include <visualizer/visual_app>
#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"

namespace naivebayes {

    namespace visualizer {

        VisualApp::VisualApp() {


            player playerTemp(ci::app::getWindowHeight(), ci::app::getWindowWidth());
            player_ = playerTemp;

        }

        void VisualApp::setup() {



        }

        void VisualApp::update() {
            //ci::Color8u background_color(0, 0, 0);  // black
            //ci::gl::clear(background_color);

            player_.Update();



        }

        void VisualApp::draw() {
            ci::Color8u background_color(0, 0, 0);  // black
            ci::gl::clear(background_color, true);
            ci::gl::lineWidth(10);
            ci::gl::drawLine({0,0},{ci::app::getWindowWidth(),0});
            ci::gl::drawLine({ci::app::getWindowWidth(),0},ci::app::getWindowSize());
            ci::gl::drawLine(ci::app::getWindowSize(),{0,ci::app::getWindowHeight()});
            ci::gl::drawLine({0,ci::app::getWindowHeight()},{0,0});


            player_.Draw();





        }

        void VisualApp::mouseDown(ci::app::MouseEvent event) {
            //sketchpad_.HandleBrush(event.getPos());
        }

        void VisualApp::mouseDrag(ci::app::MouseEvent event) {
            //sketchpad_.HandleBrush(event.getPos());
        }

        void VisualApp::keyDown(ci::app::KeyEvent event) {
            if (event.getCode() == ci::app::KeyEvent::KEY_RIGHT ){
                player_.MoveRight();
            }

            if (event.getCode() == ci::app::KeyEvent::KEY_LEFT ){
                player_.MoveLeft();
            }
            if (event.getCode() == ci::app::KeyEvent::KEY_UP){
                player_.Jump();
            }

        }

    }  // namespace visualizer

}  // namespace naivebayes
