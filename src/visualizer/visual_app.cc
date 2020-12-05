#include <visualizer/visual_app>
#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"

namespace naivebayes {

    namespace visualizer {

        VisualApp::VisualApp() {
            player_ = new player(ci::app::getWindowHeight()-15, ci::app::getWindowWidth());
            player_two_ = new player(ci::app::getWindowHeight()-15, ci::app::getWindowWidth());
            player_two_->lefty_ = true;
            player_->righty_ = true;

            particle_handler particleHandler(ci::app::getWindowHeight()-15, ci::app::getWindowWidth(), player_, player_two_);
            particleHandler_ = particleHandler;


        }

        void VisualApp::setup() {
            particleHandler_.addCustomParticle((float) ci::app::getWindowWidth() / 2.0f,
                                               (float) ci::app::getWindowHeight() - 55, 0, 0);
            preJumpVelocity = player_->Jump();
            ci::audio::SourceFileRef sourceFile = ci::audio::load(ci::app::loadAsset("bruh.mp3"));
            mVoice = ci::audio::Voice::create(sourceFile);


        }

        void VisualApp::update() {
            //ci::Color8u background_color(0, 0, 0);  // black
            //ci::gl::clear(background_color);
            goal_scored = GoalChecker();
            if (Menu_State) {

            } else {
                if (!goal_scored){
                    particleHandler_.Update();
                    player_->Update();
                    player_two_->Update();
                    if (!player_->IsAirBorne() && keyedUpWhileAirborne) {
                        player_->velocity.x = 0;
                    }
                    if (!player_two_->IsAirBorne() && keyedUpWhileAirborne) {
                        player_two_->velocity.x = 0;
                    }

                    frameCount_++;
                }else {
                    ResetPlayingField();
                    goal_scored = false;
                }

            }


        }

        void VisualApp::draw() {


            float_t center = ci::app::getWindowWidth() / 2.0f;

            if (Menu_State) {
                ci::Font font("arial", 200);
                ci::gl::drawStringCentered(
                        "Head Soccer!",
                        glm::vec2(ci::app::getWindowWidth() / 2.0f, 200), ci::Color("red"), font);

                ci::Rectf rectf = {center - 150, 500, center + 150, 600};
                ci::gl::drawStrokedRect(rectf, 5);
                ci::Font font_two("arial", 50);
                ci::gl::drawStringCentered(
                        "Press V to start",
                        glm::vec2(ci::app::getWindowWidth() / 2.0f, 535), ci::Color("red"), font_two);


            } else {
                ci::Color8u background_color(0, 0, 0);  // black
                ci::gl::clear(background_color, true);
                ci::gl::lineWidth(10);
                ci::gl::drawLine({0, 0}, {ci::app::getWindowWidth(), 0});
                ci::gl::drawLine({ci::app::getWindowWidth(), 0}, ci::app::getWindowSize());
                ci::gl::drawLine(ci::app::getWindowSize(), {0, ci::app::getWindowHeight()});
                ci::gl::drawLine({0, ci::app::getWindowHeight()}, {0, 0});

                ci::gl::drawLine({0, ci::app::getWindowHeight() - k_goal_height_},
                                 {k_goal_width_, ci::app::getWindowHeight() - k_goal_height_});
                ci::gl::drawLine({ci::app::getWindowWidth(), ci::app::getWindowHeight() - k_goal_height_},
                                 {ci::app::getWindowWidth() - k_goal_width_, ci::app::getWindowHeight() - k_goal_height_});

                InitiateStartScreen();
                DisplayScore();
                particleHandler_.draw();
                player_->Draw();
                player_two_->Draw();
            }


        }

        bool VisualApp::GoalChecker() {
            size_t size = particleHandler_.currentParticles_.size();
            visualizer::particle* particle = particleHandler_.currentParticles_.at(size-1);
            float yOffset = (float )ci::app::getWindowHeight();

            if (particle->position_.x < k_goal_width_ && particle->position_.y > yOffset-k_goal_height_ ){
                current_opponent_score++;
                return true;
            }

            if (particle->position_.x > ci::app::getWindowWidth() - k_goal_width_ && particle->position_.y > yOffset-k_goal_height_ ){
                current_player_score_++;
                return true;
            }

            return false;
        }

        void VisualApp::DisplayScore() {
            ci::Font font("arial", 50);
            ci::gl::drawStringCentered(
                    std::to_string(current_player_score_),
                    glm::vec2(100, 100), ci::Color("white"), font);

            ci::gl::drawStringCentered(
                    std::to_string(current_opponent_score),
                    glm::vec2(ci::app::getWindowWidth() - 100, 100), ci::Color("white"), font);

        }

        void VisualApp::InitiateStartScreen() {
            ci::Font font("arial", 250);

            if (frameCount_ < 150) {
                ci::gl::drawStringCentered(
                        "START!",
                        glm::vec2((float) ci::app::getWindowWidth() / 2.0f, 100), ci::Color("blue"), font);
            }


        }

        void VisualApp::NewGame() {
            size_t size = particleHandler_.currentParticles_.size();

            player_->centerPos = {100, ci::app::getWindowHeight() - 100};
            player_two_->centerPos = {ci::app::getWindowWidth()-100,ci::app::getWindowHeight() - 100 };
            particleHandler_.currentParticles_.at(size-1)->position_ = {ci::app::getWindowWidth() / 2.0f,ci::app::getWindowHeight() - 550};
            particleHandler_.currentParticles_.at(size-1)->velocity_ = {0, 0};
            frameCount_ = 0;
            current_opponent_score = 0;
            current_player_score_ = 0;
        }

        void VisualApp::ResetPlayingField() {
            size_t size = particleHandler_.currentParticles_.size();

            player_->centerPos = {100, ci::app::getWindowHeight() - 100};
            player_two_->centerPos = {ci::app::getWindowWidth()-100,ci::app::getWindowHeight() - 100 };
            particleHandler_.currentParticles_.at(size-1)->position_ = {ci::app::getWindowWidth() / 2.0f,ci::app::getWindowHeight() - 550};
            particleHandler_.currentParticles_.at(size-1)->velocity_ = {0, 0};
            frameCount_ = 0;
        }

        void VisualApp::keyDown(ci::app::KeyEvent event) {
            keyedUpWhileAirborne = false;
            keyedUpWhileAirborneTwo = false;
            if (event.getCode() == ci::app::KeyEvent::KEY_SPACE) {
                player_->KickLeg();
            }
            if (event.getCode() == ci::app::KeyEvent::KEY_v) {
                Start_Button = true;
                Menu_State = false;
            }
            if (event.getCode() == ci::app::KeyEvent::KEY_RETURN) {
                NewGame();
            }
            if (event.getCode() == ci::app::KeyEvent::KEY_UP) {


                preJumpVelocity = player_->Jump();
                mVoice->start();
            }
            if (event.getCode() == ci::app::KeyEvent::KEY_RIGHT) {
                player_->MoveRight();
                if (player_->IsAirBorne()) {
                    player_->MidAirStrafeRight(preJumpVelocity);
                }

                rightHeldDown = true;
                leftHeldDown = false;

            }

            if (event.getCode() == ci::app::KeyEvent::KEY_LEFT) {
                player_->MoveLeft();
                if (player_->IsAirBorne()) {
                    player_->MidAirStrafeLeft(preJumpVelocity);
                }
                leftHeldDown = true;
                rightHeldDown = false;
            }

            if (two_player_selected_){
                if (event.getCode() == ci::app::KeyEvent::KEY_q) {
                    player_two_->KickLeg();
                }
                if (event.getCode() == ci::app::KeyEvent::KEY_w) {
                    preJumpVelocityTwo = player_two_->Jump();
                    mVoice->start();
                }
                if (event.getCode() == ci::app::KeyEvent::KEY_d) {
                    player_two_->MoveRight();
                    if (player_two_->IsAirBorne()) {
                        player_two_->MidAirStrafeRight(preJumpVelocityTwo);
                    }

                    rightHeldDown = true;
                    leftHeldDown = false;

                }

                if (event.getCode() == ci::app::KeyEvent::KEY_a) {
                    player_two_->MoveLeft();
                    if (player_two_->IsAirBorne()) {
                        player_two_->MidAirStrafeLeft(preJumpVelocityTwo);
                    }
                    leftHeldDown = true;
                    rightHeldDown = false;
                }
            }

        }

        void VisualApp::keyUp(ci::app::KeyEvent event) {


            if (event.getCode() == ci::app::KeyEvent::KEY_RIGHT) {
                if (!player_->IsAirBorne()) {
                    keyedUpWhileAirborne = false;
                    player_->velocity.x = 0;
                } else {
                    keyedUpWhileAirborne = true;
                }

            }

            if (event.getCode() == ci::app::KeyEvent::KEY_LEFT) {
                if (!player_->IsAirBorne()) {
                    keyedUpWhileAirborne = false;
                    player_->velocity.x = 0;
                } else {
                    keyedUpWhileAirborne = true;
                }

            }

            if (two_player_selected_){
                if (event.getCode() == ci::app::KeyEvent::KEY_d) {
                    if (!player_two_->IsAirBorne()) {
                        keyedUpWhileAirborneTwo = false;
                        player_two_->velocity.x = 0;
                    } else {
                        keyedUpWhileAirborneTwo = true;
                    }

                }

                if (event.getCode() == ci::app::KeyEvent::KEY_a) {
                    if (!player_two_->IsAirBorne()) {
                        keyedUpWhileAirborneTwo = false;
                        player_two_->velocity.x = 0;
                    } else {
                        keyedUpWhileAirborneTwo = true;
                    }

                }
            }



        }

    }  // namespace visualizer

}  // namespace naivebayes