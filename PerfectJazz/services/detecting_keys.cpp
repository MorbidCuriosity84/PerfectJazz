#include "detecting_keys.h"
#include <windows.h>
#include <fstream>

bool DetectingKeys::keyUp = false;
bool DetectingKeys::keyDown = false;
bool DetectingKeys::keyEnter = false;

void DetectingKeys::detectingKeys() {
	if (GetAsyncKeyState(VK_UP) < 0 && !DetectingKeys::keyUp) { DetectingKeys::keyUp = true; }
	if (GetAsyncKeyState(VK_UP) == 0 && DetectingKeys::keyUp) { DetectingKeys::keyUp = false; }
	if (GetAsyncKeyState(VK_DOWN) < 0 && !DetectingKeys::keyDown) { DetectingKeys::keyDown = true; }
	if (GetAsyncKeyState(VK_DOWN) == 0 && DetectingKeys::keyDown) { DetectingKeys::keyDown = false; }
	if (GetAsyncKeyState(VK_RETURN) < 0 && !DetectingKeys::keyEnter) { DetectingKeys::keyEnter = true; }
	if (GetAsyncKeyState(VK_RETURN) == 0 && DetectingKeys::keyEnter) { DetectingKeys::keyEnter = false; }
}