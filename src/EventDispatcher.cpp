#include "EventDispatcher.h"

static yaui::EventDispatcher *pInstance = nullptr;

yaui::EventDispatcher *yaui::EventDispatcher::getInstance() {
    if(pInstance == nullptr) {
        pInstance = new EventDispatcher();
    }
    return pInstance;
}

void yaui::EventDispatcher::clear() {
    mEventListenerStore.clear();
}

const yaui::ArrayList<yaui::EventDispatcher::ListenerIdentity>* yaui::EventDispatcher::getEventListeners(const yaui::String &listenerComponent) {
    if(auto listener = mEventListenerStore.find(listenerComponent); listener != mEventListenerStore.end()) {
        return &listener->second;
    }
    return nullptr;
}

void
yaui::EventDispatcher::registerListener(const yaui::String &listenerComponent, yaui::entity::Registry &registry, const yaui::entity::Entity &entity) {
    auto listenerIdentity = ListenerIdentity{&registry, entity};
    if(auto listeners = mEventListenerStore.find(listenerComponent); listeners == mEventListenerStore.end()) {
        mEventListenerStore[listenerComponent].emplace_back(listenerIdentity);
    } else if(std::find(listeners->second.begin(), listeners->second.end(), listenerIdentity) == listeners->second.end()) {
        listeners->second.emplace_back(listenerIdentity);
    }
}

void
yaui::EventDispatcher::unregisterListener(const yaui::String &listenerComponent, yaui::entity::Registry &registry, const yaui::entity::Entity &entity) {
    if(auto listener = mEventListenerStore.find(listenerComponent); listener != mEventListenerStore.end()) {
        listener->second.erase(std::remove(listener->second.begin(), listener->second.end(), ListenerIdentity{&registry, entity}));
    }
}
