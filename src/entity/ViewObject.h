#ifndef YAUI_VIEWOBJECT_H
#define YAUI_VIEWOBJECT_H


#include "component/Component.h"
#include "Types.h"

namespace yaui::entity {
    class ViewObject {

        /** constants **/
    private:
    protected:
    public:

        /** data **/
    private:
        Entity mEntity;
        yaui::system::Registry *mpRegistry = nullptr;
        SDL_Texture *mpTexture;
        ArrayList<yaui::component::Component*> mBoxModelComponents;
        ArrayList<yaui::component::Component*> mCustomComponents;
    protected:
    public:


        /** methods **/
    private:
    protected:
    public:
        ViewObject(const yaui::entity::Entity &entity, yaui::system::Registry *registry);
        template<typename Component>
        void AddComponent(const Component &component) {
            this->mpRegistry->emplace<Component>(this->mEntity, component);
        }
    };
}


#endif // YAUI_VIEWOBJECT_H
