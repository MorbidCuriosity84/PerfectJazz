#pragma once

//Detects key strokes allowing only one stroke at a time
class DetectingKeys {
public:
	//Detects what key is being pressed, not allowing more than one stroke
	static void detectingKeys();
	static bool keyUp;
	static bool keyDown;
	static bool keyEnter;
	static bool keyEscape;
	static bool keySpace;
};

