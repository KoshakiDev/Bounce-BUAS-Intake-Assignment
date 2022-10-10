#include "GameObject.h"

Sprite theSprite(new Surface("assets/ball.png"), 1);

GameObject::GameObject() 
{
	Init();
}

void GameObject::Init() 
{
	GameObject::xpos = 0;
	GameObject::ypos = 0;

	//xpos = 0;
	//ypos = 0;
	//Sprite sprite(new Surface("assets/ball.png"), 1);
}

void GameObject::Tick(float deltaTime)
{
	printf("%i", GameObject::xpos);
}

void GameObject::Draw(Surface* screen)
{
	theSprite.Draw(screen, 0, 0);
}