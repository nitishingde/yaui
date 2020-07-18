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
            bool Init();
            void PollInputs();
            void Update();
            void Render();
        protected:
        public:
            Window(
                const yaui::String &title = "",
                const yaui::int32 &positionX = SDL_WINDOWPOS_UNDEFINED,
                const yaui::int32 &positionY = SDL_WINDOWPOS_UNDEFINED,
                const yaui::int32 &width = 640,
                const yaui::int32 &height = 480
            );
            ~Window();
            void Run();

            /** getters/setters **/
            yaui::int32 GetPositionX() const;
            void SetPositionX(const yaui::int32 &x);
            yaui::int32 GetPositionY() const;
            void SetPositionY(const yaui::int32 &y);
            yaui::Vector2<yaui::int32> GetPosition();
            void SetPosition(const yaui::int32 &x, const yaui::int32 &y);
            yaui::int32 GetWidth() const;
            void SetWidth(const yaui::int32 &width);
            yaui::int32 GetHeight() const;
            void SetHeight(const yaui::int32 &height);
            yaui::Vector2<yaui::int32> GetDimension();
            void SetDimension(const yaui::int32 &width, const yaui::int32 &height);
    };
}


#endif // YAUI_WINDOW_H
