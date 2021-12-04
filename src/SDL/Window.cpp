#include "Window.hpp"

#include <stdexcept>

namespace SDL {
    Window::Window(const std::string_view title, const int width, const int height)
        : self{Window::Pointer{SDL_CreateWindow(title.data(), SDL_WINDOWPOS_UNDEFINED,
                                                SDL_WINDOWPOS_UNDEFINED, width, height,
                                                SDL_WINDOW_OPENGL),
                               &SDL_DestroyWindow}} {
        if (self == nullptr) throw std::runtime_error{SDL_GetError()};
    }

    Renderer Window::create_renderer() const {
        auto * const renderer = SDL_CreateRenderer(self.get(), -1, SDL_RENDERER_ACCELERATED);
        if (renderer == nullptr) throw std::runtime_error{SDL_GetError()};
        return {renderer};
    }
} // namespace SDL
