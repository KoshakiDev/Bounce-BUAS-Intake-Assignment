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
	
	void ClearLevel();
	void LoadLevel();
	void RestartLevel();
	void NextLevel();


	void Shutdown(); 

	void Tick( float delta ); // equivalent of physics_process(delta)
	void Draw( Surface* screen );

	//Checking functions
	void CheckTileCollision( float delta );
	void CheckSkullCollision( float delta );
	void CheckAcceleratorCollision( float delta );
	void CheckFlagCollision( float delta );
	//Input
	
	virtual void MouseUp(int button);
	virtual void MouseDown(int button);
	virtual void MouseMove(int x, int y);
	virtual void KeyUp(int key);
	virtual void KeyDown(int key);

	Surface* getScreen() { return screen; }
	enum groupLabels : std::size_t
	{
		groupMap,
		groupPlayers,
		groupColliders,
		groupSkulls,
		groupFlags,
		groupAccelerators,
	};
	
private:
	Surface* screen;
	int mousex, mousey;

};

}; // namespace Tmpl8