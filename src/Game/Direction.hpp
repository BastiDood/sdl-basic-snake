#pragma once
#include <SDL_events.h>
#include <optional>

enum class Direction { Up, Down, Left, Right };

constexpr std::optional<Direction> derive_direction(SDL_Keycode code);
