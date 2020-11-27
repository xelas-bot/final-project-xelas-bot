#include <visualizer/visual_app>
#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"

namespace naivebayes {

    namespace visualizer {

        VisualApp::VisualApp() {
            player_ = new player(ci::app::getWindowHeight(), ci::app::getWindowWidth());

            particle_handler particleHandler(ci::app::getWindowHeight(), ci::app::getWindowWidth(), player_);
            particleHandler_ = particleHandler;



        }

        void VisualApp::setup() {
        particleHandler_.addCustomParticle(500,(float )ci::app::getWindowHeight() -400,0,0);
            preJumpVelocity =  player_->Jump();
            ci::audio::SourceFileRef sourceFile = ci::audio::load( ci::app::loadAsset( "bruh.mp3" ) );
            mVoice = ci::audio::Voice::create( sourceFile );


        }

        void VisualApp::update() {
            //ci::Color8u background_color(0, 0, 0);  // black
            //ci::gl::clear(background_color);


            player_->Update();
             if (!player_->IsAirBorne() && keyedUpWhileAirborne){
                 player_->velocity.x = 0;
             }
             particleHandler_.Update();


        }

        void VisualApp::draw() {
            ci::Color8u background_color(0, 0, 0);  // black
            ci::gl::clear(background_color, true);
            ci::gl::lineWidth(10);
            ci::gl::drawLine({0,0},{ci::app::getWindowWidth(),0});
            ci::gl::drawLine({ci::app::getWindowWidth(),0},ci::app::getWindowSize());
            ci::gl::drawLine(ci::app::getWindowSize(),{0,ci::app::getWindowHeight()});
            ci::gl::drawLine({0,ci::app::getWindowHeight()},{0,0});

            ci::gl::drawString(std::to_string(particleHandler_.currentParticles_.at(0)->velocity_.y), {200,200});

            particleHandler_.draw();
            player_->Draw();





        }

        void VisualApp::mouseDown(ci::app::MouseEvent event) {
            //sketchpad_.HandleBrush(event.getPos());
        }

        void VisualApp::mouseDrag(ci::app::MouseEvent event) {
            //sketchpad_.HandleBrush(event.getPos());
        }

        void VisualApp::keyDown(ci::app::KeyEvent event) {
            keyedUpWhileAirborne = false;


            if (event.getCode() == ci::app::KeyEvent::KEY_UP){


                preJumpVelocity = player_->Jump();
                mVoice->start();
            }
            if (event.getCode() == ci::app::KeyEvent::KEY_RIGHT ){
                player_->MoveRight();
                if (player_->IsAirBorne()){
                    player_->MidAirStrafeRight(preJumpVelocity);
                }

                rightHeldDown = true;
                leftHeldDown = false;

            }

            if (event.getCode() == ci::app::KeyEvent::KEY_LEFT ){
                player_->MoveLeft();
                if (player_->IsAirBorne()){
                    player_->MidAirStrafeLeft(preJumpVelocity);
                }
                leftHeldDown = true;
                rightHeldDown = false;
            }

        }

        void VisualApp::keyUp(ci::app::KeyEvent event) {
            if (event.getCode() == ci::app::KeyEvent::KEY_RIGHT ){
                if (!player_->IsAirBorne()){
                    keyedUpWhileAirborne = false;
                    player_->velocity.x = 0;
                }else {
                    keyedUpWhileAirborne = true;
                }

            }

            if (event.getCode() == ci::app::KeyEvent::KEY_LEFT ){
                if (!player_->IsAirBorne()){
                    keyedUpWhileAirborne = false;
                    player_->velocity.x = 0;
                }else {
                    keyedUpWhileAirborne = true;
                }

            }
            if (event.getCode() == ci::app::KeyEvent::KEY_UP){
                //mVoice->stop();
            }
        }

    }  // namespace visualizer

}  // namespace naivebayes
