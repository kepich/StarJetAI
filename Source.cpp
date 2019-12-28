#include <iostream>
#include "GameControl.h"
#include "CONF.h"
using namespace std;

void intialize() {
	return;
}

void game_cycle(bool (*game_update)(), void (*game_render)() = nullptr) {
	while ((*game_update)()) {
		if (RENDERING)
			try{
			(*game_render)();
			}
			catch (const std::exception&){
				cout << "###: Game render function is NULL" << endl;
			}
	}
}

int main() {
	GameControl* gc = new GameControl();
	intialize();
	game_cycle(gc->update, gc->render);

	return 0;
}