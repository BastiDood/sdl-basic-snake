#include "Window.hpp"
#include <SDL_render.h>
#include <SDL_video.h>
#include <cassert>

namespace SDL {
    Window::Window(const std::string_view title, const int width, const int height)
        : self{SDL_CreateWindow(title.data(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                width, height, SDL_WINDOW_OPENGL)} {
        assert(self);
    }

    Window::~Window() { SDL_DestroyWindow(self); }

    Renderer Window::create_renderer() const {
        auto * const renderer = SDL_CreateRenderer(self, -1, SDL_RENDERER_ACCELERATED);
        assert(renderer);
        return {renderer};
    }
} // namespace SDL
