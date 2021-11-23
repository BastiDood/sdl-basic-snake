#include "Direction.hpp"

constexpr std::optional<Direction> derive_direction(const SDL_Keycode code) {
    switch (code) {
        case SDLK_w:
        case SDLK_UP: return Direction::Up;
        case SDLK_s:
        case SDLK_DOWN: return Direction::Down;
        case SDLK_a:
        case SDLK_LEFT: return Direction::Left;
        case SDLK_d:
        case SDLK_RIGHT: return Direction::Right;
        default: return {};
    }
}
