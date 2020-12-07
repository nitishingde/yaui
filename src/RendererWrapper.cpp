#include "RendererWrapper.h"

yaui::RendererWrapper::RendererWrapper(yaui::Renderer *pRenderer) noexcept : mpRenderer(pRenderer) {

}

yaui::RendererWrapper::RendererWrapper(yaui::RendererWrapper &&other) noexcept : mpRenderer(other.mpRenderer) {
    other.mpRenderer = nullptr;
}

yaui::RendererWrapper& yaui::RendererWrapper::operator=(yaui::RendererWrapper &&other) noexcept {
    if(this != &other) {
        mpRenderer = other.mpRenderer;
        other.mpRenderer = nullptr;
    }
}

yaui::RendererWrapper::~RendererWrapper() {
    mpRenderer = nullptr;
}

yaui::Renderer &yaui::RendererWrapper::getRenderer() {
    return *mpRenderer;
}
