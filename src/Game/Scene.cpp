#include "Scene.hpp"
#include <SDL_keycode.h>

namespace Game {
    Scene::Scene(const std::string_view font_path) : font{font_path, FONT_SIZE} {}

    void Scene::on_input(const SDL_Keycode input) {
        // Respond to input
        if (is_playing)
            switch (input) {
                case SDLK_UP:
                case SDLK_w: return snake.set_current_direction(Game::Snake::Direction::UP);
                case SDLK_DOWN:
                case SDLK_s: return snake.set_current_direction(Game::Snake::Direction::DOWN);
                case SDLK_LEFT:
                case SDLK_a: return snake.set_current_direction(Game::Snake::Direction::LEFT);
                case SDLK_RIGHT:
                case SDLK_d: return snake.set_current_direction(Game::Snake::Direction::RIGHT);
            }

        // Reset the game otherwise
        if (pending_reset) {
            is_playing = true;
            pending_reset = false;
            score = 0;
            snake.reset();
        }
    }

    void Scene::tick() {
        if (is_playing) {
            is_playing = snake.tick();
            pending_reset = !is_playing;
        }
    }

    void Scene::draw() const {
        renderer.set_render_draw_color(0, 0, 0, 255);
        renderer.clear();

        if (!is_playing) {
            const SDL_Point dimensions = restart_texture.get_dimensions();
            renderer.render_copy(restart_texture, {}, {{0, 0, dimensions.x, dimensions.y}});
            renderer.present();
            return;
        }

        // TODO: Render the actual snake state
        snake.draw(renderer);
        renderer.present();
    }
} // namespace Game
