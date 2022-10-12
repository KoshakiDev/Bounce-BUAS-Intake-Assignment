#include "GameObject.h"
#include "surface.h"


using namespace Tmpl8;


Sprite theSprite(new Surface("assets/ball.png"), 1);


void GameObject::Tick(float deltaTime)
{
	printf("%f %f \n", m_transform.GetPosition().x, m_transform.GetPosition().y);
}

void GameObject::Draw(Surface* screen)
{
	theSprite.Draw(screen, m_transform.GetPosition().x, m_transform.GetPosition().y);
}

void GameObject::Input(int key)
{
	//printf("%i %i", key, SDL_SCANCODE_O);
	/**/
	if (key == SDL_SCANCODE_D)
	{
		m_transform.GetPosition() += vec2(1, 0);
	}
	if (key == SDL_SCANCODE_A)
	{
		m_transform.GetPosition() += vec2(-1, 0);
	}
	/**/
}