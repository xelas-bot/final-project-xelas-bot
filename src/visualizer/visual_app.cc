#include <visualizer/visual_app>

namespace naivebayes {

    namespace visualizer {

        VisualApp::VisualApp() {
            particle_handler particleHandlerTemp((int) kContainerSize);

            particleHandler_ = particleHandlerTemp;


            ci::app::setWindowSize((int) kWindowSize, (int) kWindowSize);

            particle particle({kWindowSize, kWindowSize}, {-10, -10});
            particle_ = particle;

            histogram_ = histogram(particleHandler_,100,{150,700});
        }

        void VisualApp::setup() {
            //particleHandler_.addParticle(1);


            particleHandler_.addParticle(10,1,10);


            particleHandler_.addParticle(10,4,15);
            particleHandler_.addParticle(25,3,20);

            std::ofstream myfile;
            myfile.open(
                    "C:/Users/Shrey Patel/Downloads/cinder_0.9.2_vc2015/my-projects/ideal-gas-xelas-bot/data/testOverload");
            myfile << particleHandler_;
            myfile.close();


        }

        void VisualApp::update() {
            //ci::Color8u background_color(0, 0, 0);  // black
            //ci::gl::clear(background_color);

            histogram_ = histogram(particleHandler_,100,{150,700});
            particleHandler_.update();



        }

        void VisualApp::draw() {
            ci::Color8u background_color(0, 0, 0);  // black
            ci::gl::clear(background_color, true);
            ci::gl::lineWidth(1);
            ci::gl::drawLine({0,0},{kContainerSize,0});
            ci::gl::drawLine({kContainerSize,0},{kContainerSize,kContainerSize});
            ci::gl::drawLine({kContainerSize,kContainerSize},{0,kContainerSize});
            ci::gl::drawLine({1,kContainerSize},{1,0});



            particleHandler_.draw();

            histogram_.Draw({1,3,4});


            ci::gl::drawStringCentered(
                    "Press Delete to slow the sim. Press Enter to speed the sim. Press f to pay resp- save to file. Press s to load a saved file",
                    glm::vec2(kWindowSize / 2, kMargin / 2), ci::Color("white"));


            ci::gl::drawStringCentered(

                    "Number of particles " + std::to_string(particleHandler_.particleCount_),
                    glm::vec2(kWindowSize / 2, kWindowSize - kMargin / 2), ci::Color("white"));


        }

        void VisualApp::mouseDown(ci::app::MouseEvent event) {
            //sketchpad_.HandleBrush(event.getPos());
        }

        void VisualApp::mouseDrag(ci::app::MouseEvent event) {
            //sketchpad_.HandleBrush(event.getPos());
        }

        void VisualApp::keyDown(ci::app::KeyEvent event) {
            switch (event.getCode()) {
                case ci::app::KeyEvent::KEY_s: {


                    std::ifstream file;
                    file.open(
                            "C:/Users/Shrey Patel/Downloads/cinder_0.9.2_vc2015/my-projects/ideal-gas-xelas-bot/data/testOverload");
                    file >> particleHandler_;
                    file.close();

                }
                case ci::app::KeyEvent::KEY_RETURN: {


                    particleHandler_.speedMultiplyer(speedMult_ + 0.25);


                    break;
                }
                case ci::app::KeyEvent::KEY_DELETE: {


                    particleHandler_.speedMultiplyer(speedMult_ - 0.25);


                    break;
                }
                case ci::app::KeyEvent::KEY_f: {


                    std::ofstream myfile;
                    myfile.open(
                            "C:/Users/Shrey Patel/Downloads/cinder_0.9.2_vc2015/my-projects/ideal-gas-xelas-bot/data/testOverload");
                    myfile << particleHandler_;
                    myfile.close();
                }


            }
        }

    }  // namespace visualizer

}  // namespace naivebayes
