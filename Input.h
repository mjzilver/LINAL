#pragma once
#include <SDL.h>
#undef main

#include <map>

class Input {
public:
	void resetKeys();
	void keyUpEvent(const SDL_Event& SDL_event);
	void keyDownEvent(const SDL_Event& SDL_event);

	bool wasKeyPressed(SDL_Scancode key);
	bool wasKeyReleased(SDL_Scancode key);
	bool isKeyHeld(SDL_Scancode key);
private:
	std::map<SDL_Scancode, bool> _heldKeys;
	std::map<SDL_Scancode, bool> _pressedKeys;
	std::map<SDL_Scancode, bool> _releasedKeys;
};

