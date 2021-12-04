#pragma once
#include "Renderer.hpp"

#include <memory>
#include <string_view>

namespace SDL {
    class Window {
        using Pointer = std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)>;

      public:
        Window(std::string_view title, int width, int height);

        Renderer create_renderer() const;

      private:
        const Pointer self;
    };
} // namespace SDL
