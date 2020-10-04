#include "Input.h"

Input::Input() {
	//_keysPressed.fill(false);

}

Input::~Input() {

}

void Input::SetKeyPressed(int keyCode, int action) {
	
	if(action == GLFW_PRESS)
		_keysPressed[keyCode] = true;
}

bool Input::GetKeyPressed(int keyCode) {
	return _keysPressed[keyCode];
}

void Input::CleanInput(){
	_keysPressed.fill(false);
}