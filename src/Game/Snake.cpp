#include "Snake.hpp"
#include <algorithm>

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
        // Propagate new velocities and positions
        auto current_dir = direction;
        for (auto & [position, velocity] : nodes) {
            std::swap(current_dir, velocity);
            switch (velocity) {
                case Direction::UP: position.y = position.y > 0 ? position.y - 1 : bounds.y; break;
                case Direction::DOWN:
                    position.y = position.y < bounds.y ? position.y + 1 : 0;
                    break;
                case Direction::LEFT:
                    position.x = position.x > 0 ? position.x - 1 : bounds.x;
                    break;
                case Direction::RIGHT:
                    position.x = position.x < bounds.x ? position.x + 1 : 0;
                    break;
            }
        }

        // Check for any collisions with the head
        const auto & head = nodes.front().position;
        const auto end = nodes.cend();
        return std::find_if(nodes.cbegin() + 1, end, [&head](auto const & node) {
                   return node.position.x == head.x && node.position.y == head.y;
               }) == end;
    }

    void Snake::reset() {
        direction = Direction::RIGHT;
        nodes.clear();
        nodes.push_front({});
    }
} // namespace Game
