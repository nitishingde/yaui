#ifndef YAUI_VIEWOBJECT_H
#define YAUI_VIEWOBJECT_H


#include "component/Component.h"
#include "Types.h"

namespace yaui { namespace entity {
    class ViewObject {

        /** constants **/
        private:
        protected:
        public:

        /** data **/
        private:
            Entity mEntity;
            yaui::system::Registry* mpRegistry = nullptr;
            ArrayList<yaui::component::Component*> mBoxModelComponents;
            ArrayList<yaui::component::Component*> mCustomComponents;
        protected:
        public:

        /** methods **/
        private:
        protected:
        public:
            ViewObject();
            void AddComponent(const yaui::component::Component &component);
    };
}}


#endif // YAUI_VIEWOBJECT_H
