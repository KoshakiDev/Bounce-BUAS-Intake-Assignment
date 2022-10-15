#include "Tile.h"

void Tile::Tick(float deltaTime)
{

}

void Tile::Draw(Surface* screen)
{
	screen->Box(
		m_rect_collider.GetTopLeftCorner().x, 
		m_rect_collider.GetTopLeftCorner().y, 
		m_rect_collider.GetBottomRightCorner().x, 
		m_rect_collider.GetBottomRightCorner().y, 
		255 * 255 * 255
	);
}
/**/