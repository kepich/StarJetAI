#pragma once

constexpr auto RENDERING = false;
// Video settings
constexpr auto WINDOW_RECT_WIDTH = 600;
constexpr auto WINDOW_RECT_HEIGHT = 400;
constexpr auto FPS = 60;

// Game constants

constexpr auto GAMEFIELD_WIDTH = 500;
constexpr auto GAMEFIELD_HEIGHT = 400;

constexpr auto SPACESHIP_WIDTH = 30;
constexpr auto SPACESHIP_HEIGHT = 30;
constexpr auto SPACESHIP_LINEAR_MAX_SPEED = 2;

enum ControllerType{
	AI,
	PLAYER,
	EMPTY
};