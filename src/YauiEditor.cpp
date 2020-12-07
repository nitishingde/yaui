
#include "yaui.h"

using namespace yaui;

int main() {
    auto dir = Director::getInstance();
    dir->setFPS(60);
    dir->pushScene(new Scene("Yaui Editor"));
    dir->setWindowBackgroundColour({0, 0, 0, 255});
    dir->setWindowSize(Size{1920, 1440});
    auto &scene = dir->getScene();
    dir->run();
    return 0;
}
