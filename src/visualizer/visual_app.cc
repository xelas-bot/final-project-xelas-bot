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
        particleHandler_.addCustomParticle((float )ci::app::getWindowWidth()/2.0f,(float )ci::app::getWindowHeight() - 500,0,0);
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
             frameCount_++;


        }

        void VisualApp::draw() {
            ci::Color8u background_color(0, 0, 0);  // black
            ci::gl::clear(background_color, true);
            ci::gl::lineWidth(10);
            ci::gl::drawLine({0,0},{ci::app::getWindowWidth(),0});
            ci::gl::drawLine({ci::app::getWindowWidth(),0},ci::app::getWindowSize());
            ci::gl::drawLine(ci::app::getWindowSize(),{0,ci::app::getWindowHeight()});
            ci::gl::drawLine({0,ci::app::getWindowHeight()},{0,0});






            InitiateStartScreen();
            DisplayScore();
            particleHandler_.draw();
            player_->Draw();





        }

        void VisualApp::DisplayScore() {
            ci::Font font("arial", 50);
            ci::gl::drawStringCentered(
                    std::to_string(current_player_score_),
                    glm::vec2(100,100), ci::Color("white"), font);

            ci::gl::drawStringCentered(
                    std::to_string(current_opponent_score),
                    glm::vec2(ci::app::getWindowWidth()-100,100), ci::Color("white"), font);

        }
        void VisualApp::InitiateStartScreen() {
            ci::Font font("arial", 250);

            if (frameCount_ < 350){
                ci::gl::drawStringCentered(
                        "START!",
                        glm::vec2((float )ci::app::getWindowWidth()/2.0f,100), ci::Color("blue"), font);
            }


        }
        void VisualApp::NewGame() {
            player_->centerPos = {100, ci::app::getWindowHeight()-100};
            particleHandler_.currentParticles_.at(1)->position_ = {ci::app::getWindowWidth()/2.0f, ci::app::getWindowHeight()-500};
            particleHandler_.currentParticles_.at(1)->velocity_ = {0,0};
            frameCount_ = 0;
            current_opponent_score = 0;
            current_player_score_=0;
        }

        void VisualApp::keyDown(ci::app::KeyEvent event) {
            keyedUpWhileAirborne = false;

            if (event.getCode() == ci::app::KeyEvent::KEY_RETURN){
                NewGame();
            }
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
