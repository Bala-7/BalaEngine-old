#pragma once
#include <algorithm>
#include <array>
#include <GLFW/glfw3.h>

class Input
{
public:
	Input();
	~Input();
	
	void SetKeyPressed(int keyCode, int action);
	bool GetKeyPressed(int keyCode);
	void CleanInput();
public:
	std::array<bool, 350> _keysPressed;
};

