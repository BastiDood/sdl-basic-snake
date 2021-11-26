#include "Scene.hpp"
#include <SDL_keycode.h>

namespace Game {
    Scene::Scene(const std::string_view font_path) : m_Font{font_path, FONT_SIZE} {}

    void Scene::on_input(const SDL_Keycode input) {
        switch (input) {
            case SDLK_UP:
            case SDLK_w: break;
            case SDLK_DOWN:
            case SDLK_s: break;
            case SDLK_LEFT:
            case SDLK_a: break;
            case SDLK_RIGHT:
            case SDLK_d: break;
            case SDLK_SPACE: break;
        }
    }

    void Scene::tick() {
        if (m_IsPlaying)
            return;
    }

    void Scene::draw() const {
        const SDL_Point dimensions = m_RestartTexture.get_dimensions();
        m_Renderer.clear();
        m_Renderer.render_copy(m_RestartTexture, {}, SDL_Rect{0, 0, dimensions.x, dimensions.y});
        m_Renderer.present();
    }
} // namespace Game
