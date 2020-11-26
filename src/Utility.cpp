#include "Utility.h"

yaui::Size yaui::getDimensionForText(const component::Text &text, component::BoxModel *pBoxModel) {
    int width = 0, height = 0;
    TTF_SizeText(text.pFont, text.value.c_str(), &width, &height);
    if(pBoxModel) {
        width += int(pBoxModel->border.left + pBoxModel->padding.left + pBoxModel->border.right + pBoxModel->padding.right);
        height += int(pBoxModel->border.bottom + pBoxModel->padding.bottom + pBoxModel->border.top + pBoxModel->padding.top);
    }
    return Size{uint32(width), uint32(height)};
}

bool yaui::isColliding(const yaui::ViewPort &viewPort, const yaui::Vec2 &point) {
    if(point.x < viewPort.x or viewPort.x+viewPort.w < point.x) return false;
    if(point.y < viewPort.y or viewPort.y+viewPort.h < point.y) return false;
    return true;
}
