#include "GameObject.h"
#include "surface.h"


using namespace Tmpl8;


Sprite theSprite(new Surface("assets/ball.png"), 1);


void GameObject::Tick(float deltaTime)
{
	updateCollider();
	//printf("%f %f \n", m_transform.GetPosition().x, m_transform.GetPosition().y);
}

void GameObject::Draw(Surface* screen)
{
	if (is_circle)
	{
		int x1 = m_circle_collider.GetTrueCenter()->GetPosition().x;
		int y1 = m_circle_collider.GetTrueCenter()->GetPosition().y;
		for (int i = 0; i < 4; i++)
		{
			int a = 0;
			int b = 0;
			if (i == 0)
			{
				a = 0;
				b = 1;
			}
			if (i == 1)
			{
				a = 1;
				b = 0;
			}
			if (i == 2)
			{
				a = 0;
				b = -1;
			}
			if (i == 3)
			{
				a = -1;
				b = 0;
			}
			int x2 = m_circle_collider.GetTrueCenter()->GetPosition().x + a * m_circle_collider.GetRadius();
			int y2 = m_circle_collider.GetTrueCenter()->GetPosition().y + b * m_circle_collider.GetRadius();
			screen->Line(x1, y1, x2, y2, 255 * 255 * 255);
		}
		//theSprite.DrawScaled(int(m_transform.GetPosition().x), int(m_transform.GetPosition().y), m_circle_collider.GetRadius(), m_circle_collider.GetRadius(), screen);
		//screen->Box(m_rect_collider.GetTopLeftCorner().x, m_rect_collider.GetTopLeftCorner().y, m_rect_collider.GetBottomRightCorner().x, m_rect_collider.GetBottomRightCorner().y, 255 * 255 * 255);
	}
	else
	{
		screen->Box(m_rect_collider.GetTopLeftCorner().x, m_rect_collider.GetTopLeftCorner().y, m_rect_collider.GetBottomRightCorner().x, m_rect_collider.GetBottomRightCorner().y, 255 * 255 * 255);
	}
	//theSprite.Draw(screen, int(m_transform.GetPosition().x), int(m_transform.GetPosition().y));
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