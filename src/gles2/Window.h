#ifndef YAUI_GLES2_WINDOW_H
#define YAUI_GLES2_WINDOW_H


#include <glm/glm.hpp>
#include <SDL.h>
#include "Types.h"

namespace yaui::gles2 {
    struct WindowCreationException: public std::exception {
        [[nodiscard]] const char *what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_USE_NOEXCEPT override;
    };

    class Window {
    private:
        SDL_Window *mpWindow = nullptr;
        SDL_GLContext mpGlContext = nullptr;
        glm::mat4 mProjectionMatrix = glm::mat4(1.0f);

    public:
        explicit Window(const char *pName, int32 x = 100, int32 y = 100, int32 width = 1080, int32 height = 720, bool borderless = false, bool resizable = true, bool hidden = false);
        ~Window();
        Window(const Window &other) = delete;
        Window& operator=(const Window &other) = delete;
        Window(Window &&other) = delete;
        Window& operator=(Window &&other) = delete;
        void setName(const char *pName) const;
        [[nodiscard]] std::tuple<int32, int32> getSize() const;
        void setSize(int32 width, int32 height);
        [[nodiscard]] glm::mat4 getProjectionMatrix() const;
        void render() const;
    };
}


#endif //YAUI_GLES2_WINDOW_H
