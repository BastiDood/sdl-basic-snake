#include "Scene.hpp"

constexpr int FONT_SIZE = 16;

namespace Game {
    Scene::Scene(const std::string_view font_path)
        : m_Font{TTF::Font::load(font_path, FONT_SIZE)} {}

    void Scene::handle_mouse(const SDL_Point point) {
        if (!m_IsMenu)
            return;
    }

    void Scene::handle_key(const SDL_Keycode code) {
        if (m_IsMenu)
            return;
    }

    void Scene::update(const std::variant<SDL_Point, SDL_Keycode> input) {
        auto const * const point = std::get_if<SDL_Point>(&input);
        if (point != nullptr) {
            handle_mouse(*point);
            return;
        }

        auto const * const code = std::get_if<SDL_Keycode>(&input);
        if (code != nullptr) {
            handle_key(*code);
            return;
        }
    }

    void Scene::tick() {
        if (m_IsMenu)
            return;
    }

    void Scene::draw(SDL::Renderer const & renderer) const {
        if (m_IsMenu) {
            renderer.set_render_draw_color(0, 0, 0, 1);
            renderer.clear();
            renderer.fill_rect(SDL_Rect{0, 0, 50, 50});
        }

        renderer.present();
    }
} // namespace Game
