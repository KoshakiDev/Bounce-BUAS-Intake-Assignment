#pragma once

#include <cstdio>
#include <SDL.h>

namespace Tmpl8 {

class Surface;
class Game
{
public:
	void SetTarget( Surface* surface ) { screen = surface; }
	void Init(); // equivalent of _ready() function
	void Shutdown(); 
	void Tick( float deltaTime ); // equivalent of physics_process(delta)
	
	void Draw( Surface* screen );

	//Input-related things
	
	void MouseUp( int button ) { /* implement if you want to detect mouse button presses */ }
	void MouseDown( int button ) { /* implement if you want to detect mouse button presses */ }
	void MouseMove( int x, int y ) { /* implement if you want to detect mouse movement */ }
	void KeyUp(int key) {}
	void KeyDown(int key);
	
private:
	Surface* screen;
};

}; // namespace Tmpl8