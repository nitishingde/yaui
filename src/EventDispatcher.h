#ifndef YAUI_EVENTDISPATCHER_H
#define YAUI_EVENTDISPATCHER_H


#include "Types.h"

namespace yaui {
    class EventDispatcher {
    private:
        struct ListenerIdentity {
            entity::Registry *pRegistry = nullptr;
            entity::Entity entity = entity::null;
            bool operator==(const ListenerIdentity &other) const {
                return pRegistry == other.pRegistry and entity == other.entity;
            }
        };
        HashMap<String, ArrayList<ListenerIdentity>> mEventListenerStore;

    private:
        EventDispatcher() = default;
    public:
        static EventDispatcher* getInstance();
        void clear();
        const ArrayList<ListenerIdentity>* getEventListeners(const String &listenerComponent);
        void registerListener(const String &listenerComponent, entity::Registry &registry, const entity::Entity &entity);
        void unregisterListener(const String &listenerComponent, entity::Registry &registry, const entity::Entity &entity);
    };
}


#endif //YAUI_EVENTDISPATCHER_H
