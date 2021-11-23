#include "Window.hpp"
#include <SDL_render.h>
#include <cassert>
#include <memory>

namespace SDL {
    Window::Window(SDL_Window * const self) : m_Self{Window::UniqPtr{self, &SDL_DestroyWindow}} {}

    Window Window::init(const std::string_view title, const int width, const int height) {
        auto * const self =
            SDL_CreateWindow(title.data(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width,
                             height, SDL_WINDOW_OPENGL);
        assert(self);
        return {self};
    }

    Renderer Window::create_renderer() const {
        auto * const self = SDL_CreateRenderer(m_Self.get(), -1, SDL_RENDERER_ACCELERATED);
        assert(self);
        return {self};
    }
} // namespace SDL
