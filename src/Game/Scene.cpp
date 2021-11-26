#include "Scene.hpp"
#include <SDL_keycode.h>

namespace Game {
    Scene::Scene(const std::string_view font_path)
        : font{font_path, FONT_SIZE}, snake{renderer.get_viewport_dimensions()} {}

    void Scene::on_input(const SDL_Keycode input) {
        switch (input) {
            case SDLK_UP:
            case SDLK_w: return snake.set_current_direction(Game::Snake::Direction::UP);
            case SDLK_DOWN:
            case SDLK_s: return snake.set_current_direction(Game::Snake::Direction::DOWN);
            case SDLK_LEFT:
            case SDLK_a: return snake.set_current_direction(Game::Snake::Direction::LEFT);
            case SDLK_RIGHT:
            case SDLK_d: return snake.set_current_direction(Game::Snake::Direction::RIGHT);
            case SDLK_SPACE: break;
        }
    }

    void Scene::tick() {
        if (!is_playing)
            return;

        is_playing = snake.tick();
        if (!is_playing)
            snake.reset();
    }

    void Scene::draw() const {
        if (!is_playing) {
            const SDL_Point dimensions = restart_texture.get_dimensions();
            renderer.clear();
            renderer.render_copy(restart_texture, {}, {{0, 0, dimensions.x, dimensions.y}});
            renderer.present();
            return;
        }

        // TODO: Render the actual snake state
    }
} // namespace Game
