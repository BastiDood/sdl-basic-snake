#pragma once
#include "Renderer.hpp"
#include <SDL_video.h>
#include <string_view>

namespace SDL {
    class Window {
      public:
        Window(std::string_view title, int width, int height);
        ~Window();

        Renderer create_renderer() const;

      private:
        SDL_Window * const self;
    };
} // namespace SDL
