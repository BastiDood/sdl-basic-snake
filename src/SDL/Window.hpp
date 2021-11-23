#pragma once
#include "Renderer.hpp"
#include <SDL_video.h>
#include <memory>
#include <string_view>

namespace SDL {
    class Window {
        using UniqPtr = std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)>;

      public:
        static Window init(std::string_view title, int width, int height);
        Renderer create_renderer() const;

      private:
        Window(SDL_Window * self);
        const UniqPtr m_Self;
    };
} // namespace SDL
