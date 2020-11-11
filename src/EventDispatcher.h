#ifndef YAUI_EVENTDISPATCHER_H
#define YAUI_EVENTDISPATCHER_H


#include "Types.h"

namespace yaui {
    class EventDispatcher {
    private:
        struct ListenerIdentity {
            entity::Entity entity = entity::null;
            IEventListener *pListener;
            entity::Registry *pRegistry = nullptr;
            bool operator==(const ListenerIdentity &other) const {
                return pListener == other.pListener or (entity == other.entity and pRegistry == other.pRegistry);
            }
        };
        HashMap<String, ArrayList<ListenerIdentity>> mEventListenerStore;

    private:
        EventDispatcher() = default;
    public:
        static EventDispatcher* getInstance();
        void clear();
        const ArrayList<ListenerIdentity>* getEventListeners(const String &listenerComponent);
        void registerListener(IEventListener &eventListener, entity::Registry &registry, const entity::Entity &entity);
        void unregisterListener(IEventListener &eventListener, entity::Registry &registry, const entity::Entity &entity);
        void unregisterListener(IEventListener &eventListener);
    };
}


#endif //YAUI_EVENTDISPATCHER_H
