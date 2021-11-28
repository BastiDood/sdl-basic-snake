#include "Window.hpp"
#include <SDL_render.h>
#include <SDL_video.h>
#include <stdexcept>

namespace SDL {
    Window::Window(const std::string_view title, const int width, const int height)
        : self{Window::Pointer{SDL_CreateWindow(title.data(), SDL_WINDOWPOS_UNDEFINED,
                                                SDL_WINDOWPOS_UNDEFINED, width, height,
                                                SDL_WINDOW_OPENGL),
                               &SDL_DestroyWindow}} {
        if (self == nullptr)
            throw std::runtime_error{"failed to initialize window"};
    }

    Renderer Window::create_renderer() const {
        auto * const renderer = SDL_CreateRenderer(self.get(), -1, SDL_RENDERER_ACCELERATED);
        if (renderer == nullptr)
            throw std::runtime_error{"cannot create renderer from window"};
        return {renderer};
    }
} // namespace SDL
