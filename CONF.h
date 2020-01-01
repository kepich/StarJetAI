#pragma once

constexpr auto RENDERING = false;
// Video settings
constexpr auto WINDOW_RECT_WIDTH = 600;
constexpr auto WINDOW_RECT_HEIGHT = 400;
constexpr auto FPS = 60;

// Game constants

constexpr auto SPACESHIP_WIDTH = 30;
constexpr auto SPACESHIP_HEIGHT = 30;

enum ControllerType{
	AI,
	PLAYER
};