#ifndef YAUI_WINDOW_H
#define YAUI_WINDOW_H


#include "SDL.h"
#include "Types.h"
#include "entity/ViewObject.h"

namespace yaui::system {
    class Window {

        /** constants **/
    private:
    protected:
    public:

        /** data **/
    private:
        SDL_Window *mpWindow;
        SDL_Renderer *mpRenderer;
        yaui::system::Registry *mpRegistry;
        yaui::ArrayList<yaui::entity::ViewObject> mViewObjectStore;
        yaui::ArrayList<SDL_Event> mEventQueue;
    protected:
    public:

        /** methods **/
    private:
        bool init();
        void pollInputs();
        void update();
        void render();
    protected:
    public:
        explicit Window(
            const yaui::String &title = "",
            const yaui::int32 &positionX = SDL_WINDOWPOS_UNDEFINED,
            const yaui::int32 &positionY = SDL_WINDOWPOS_UNDEFINED,
            const yaui::int32 &width = 640,
            const yaui::int32 &height = 480
        );
        ~Window();
        void run();
        yaui::entity::ViewObject* getViewObject();

        /** getters/setters **/
        yaui::int32 getPositionX() const;
        void setPositionX(const yaui::int32 &x);
        yaui::int32 getPositionY() const;
        void setPositionY(const yaui::int32 &y);
        yaui::Vector2<yaui::int32> getPosition();
        void setPosition(const yaui::int32 &x, const yaui::int32 &y);
        yaui::int32 getWidth() const;
        void setWidth(const yaui::int32 &width);
        yaui::int32 getHeight() const;
        void setHeight(const yaui::int32 &height);
        yaui::Vector2<yaui::int32> getDimension();
        void setDimension(const yaui::int32 &width, const yaui::int32 &height);
    };
}


#endif // YAUI_WINDOW_H
