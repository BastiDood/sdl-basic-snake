#include "Scene.hpp"
#include <SDL_keycode.h>

namespace Game {
    Scene::Scene(const std::string_view font_path)
        : m_Font{font_path, 16}, m_Renderer{m_Window.create_renderer()},
          m_ScoreTexture(m_Renderer.create_texture_from_surface(
              m_Font.render_text_blended("Score:", {255, 255, 255, 255}))),
          m_RestartTexture{m_Renderer.create_texture_from_surface(m_Font.render_text_blended(
              "Game over! Press [Space] to restart...", {255, 255, 255, 255}))} {}

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
        m_Renderer.clear();
        m_Renderer.render_copy(m_ScoreTexture);
        m_Renderer.present();
    }
} // namespace Game
