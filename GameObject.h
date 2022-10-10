#include "game.h"
#include "surface.h"

using namespace std;
using namespace Tmpl8;


class GameObject {

public:
	GameObject();
	~GameObject();
	void Init();
	void Tick(float deltaTime);
	void Draw(Surface* screen);

private:
	int xpos = 0;
	int ypos = 0;
};