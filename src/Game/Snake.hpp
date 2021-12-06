#include "../SDL/Renderer.hpp"

#include <deque>
#include <SDL_rect.h>

namespace Game {
    class Snake {
        static constexpr SDL_Point BOUNDS{10, 10};

      public:
        enum class Direction { UP, DOWN, LEFT, RIGHT };

        /**
         * Controls the upcoming direction in the next tick.
         * Ignore invalid inputs, such as when trying to send
         * the snake into a 180-degree turn.
         */
        constexpr void set_current_direction(Direction dir);
        /** Returns `true` if tick was successful. Otherwise, the game is over. */
        bool tick();
        /** Render the snake on the screen. */
        void draw(SDL::Renderer const & renderer, int width, int height) const;
        /** Resets the snake's state. */
        constexpr void reset();

      private:
        /** Determines whether a given direction cancels out the current direction. */
        bool is_opposite_direction(Direction dir) const;

        struct Node {
            SDL_Point position{0, 0};
            Direction direction = Direction::RIGHT;
        };

        /** The upcoming velocity of the snake head. By default, it goes right. */
        Direction direction = Direction::RIGHT;
        /** Velocity and grid position of each snake node. */
        std::deque<Node> nodes{{{2, 0}}, {{1, 0}}, {}};
    };
} // namespace Game
