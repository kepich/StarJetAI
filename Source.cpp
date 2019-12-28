#include <iostream>
#include <functional>
#include "GameControl.h"
#include "CONF.h"
#include "Logger.h"
using namespace std;

void intialize() {
	return;
}

void game_cycle(const function<bool()>& game_update, const function<void()> & game_render = nullptr) {
	while (game_update())
		if (RENDERING)
			if (game_render) game_render();
}

int main() {
	GameControl* gc = new GameControl();
	intialize();

	game_cycle([&gc]() mutable { return gc->update(); }, [&gc]() mutable { return gc->render(); });

	return 0;
}