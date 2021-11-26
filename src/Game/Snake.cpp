#include "Snake.hpp"

namespace Game {
    Snake::Snake(const SDL_Point game_bounds) : bounds{game_bounds} {}

    bool Snake::is_opposite_direction(const Direction dir) const {
        switch (direction) {
            case Direction::UP: return dir == Direction::DOWN;
            case Direction::DOWN: return dir == Direction::UP;
            case Direction::LEFT: return dir == Direction::RIGHT;
            case Direction::RIGHT: return dir == Direction::LEFT;
        }
    }

    void Snake::set_current_direction(const Direction dir) {
        if (!is_opposite_direction(dir))
            direction = dir;
    }

    bool Snake::tick() {
        // TODO: Propagate the velocities across every node
    }
} // namespace Game
