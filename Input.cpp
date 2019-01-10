#include "input.h"

/* Input class
* Keeps track of keyboard state
*/

//This function gets claled at the beginning of each frame to reset the keys
void Input::resetKeys() {
	this->_pressedKeys.clear();
	this->_releasedKeys.clear();
}
// this gets called when a keys has been pressed
void Input::keyDownEvent(const SDL_Event& SDL_event) {
	this->_pressedKeys[SDL_event.key.keysym.scancode] = true;
	this->_heldKeys[SDL_event.key.keysym.scancode] = true;
}

// this gets called when a key is released
void Input::keyUpEvent(const SDL_Event& SDL_event) {
	this->_releasedKeys[SDL_event.key.keysym.scancode] = true;
	this->_heldKeys[SDL_event.key.keysym.scancode] = false;
}

//check if a specific key was  pressed
bool Input::wasKeyPressed(SDL_Scancode key) {
	return this->_pressedKeys[key];
}

//check if a specific key was released
bool Input::wasKeyReleased(SDL_Scancode key) {
	return this->_releasedKeys[key];
}

//check if a specific key is being held
bool Input::isKeyHeld(SDL_Scancode key) {
	return this->_heldKeys[key];
}