#include "EventDispatcher.h"
#include <spdlog/spdlog.h>

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
yaui::EventDispatcher::registerListener(IEventListener &eventListener, yaui::entity::Registry &registry, const yaui::entity::Entity &entity) {
    auto listenerIdentity = ListenerIdentity{entity, &eventListener, &registry};
    if(auto listeners = mEventListenerStore.find(eventListener.getClassName()); listeners == mEventListenerStore.end()) {
        mEventListenerStore[eventListener.getClassName()].emplace_back(listenerIdentity);
    } else if(std::find(listeners->second.begin(), listeners->second.end(), listenerIdentity) == listeners->second.end()) {
        listeners->second.emplace_back(listenerIdentity);
    }
}

void
yaui::EventDispatcher::unregisterListener(IEventListener &eventListener, yaui::entity::Registry &registry, const yaui::entity::Entity &entity) {
    if(auto listener = mEventListenerStore.find(eventListener.getClassName()); listener != mEventListenerStore.end()) {
        listener->second.erase(std::remove(
            listener->second.begin(),
            listener->second.end(),
            ListenerIdentity{entity, &eventListener, &registry}
        ));
    }
}

void yaui::EventDispatcher::unregisterListener(yaui::IEventListener &eventListener) {
    if(auto listener = mEventListenerStore.find(eventListener.getClassName()); listener != mEventListenerStore.end()) {
        listener->second.erase(std::remove_if(
            listener->second.begin(),
            listener->second.end(),
            [&eventListener](const ListenerIdentity &listenerIdentity) {
                return listenerIdentity.pListener == &eventListener;
            }
        ));
    }
}
