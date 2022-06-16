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
        void set_current_direction(Direction dir);

        /** Returns `true` if tick was successful. Otherwise, the game is over. */
        bool tick();
        /** Render the snake on the screen. */
        void draw(const SDL::Renderer & renderer, int width, int height) const;

        /** Resets the snake's state. */
        void reset();

      private:
        /** Determines whether the user's latest input conflicts with the current velocity. */
        bool is_input_opposite_dir() const;

        /** The previous velocity of the snake head. By default, it goes right. */
        Direction direction = Direction::RIGHT;
        /** The latest input of the user. */
        Direction input = direction;
        /** Velocity and grid position of each snake node. */
        std::deque<SDL_Point> nodes{{2, 0}, {1, 0}, {}};
    };
} // namespace Game
