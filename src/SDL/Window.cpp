#include "Window.hpp"
#include <SDL_render.h>
#include <SDL_video.h>
#include <cassert>

namespace SDL {
    Window::Window(const std::string_view title, const int width, const int height)
        : self{Window::Pointer{SDL_CreateWindow(title.data(), SDL_WINDOWPOS_UNDEFINED,
                                                SDL_WINDOWPOS_UNDEFINED, width, height,
                                                SDL_WINDOW_OPENGL),
                               &SDL_DestroyWindow}} {
        assert(self);
    }

    Renderer Window::create_renderer() const {
        auto * const renderer = SDL_CreateRenderer(self.get(), -1, SDL_RENDERER_ACCELERATED);
        assert(renderer);
        return {renderer};
    }
} // namespace SDL
