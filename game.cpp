#include "game.h"
#include "surface.h"
#include "GameObject.h"
#include "Transform.h"

#include "RectCollider.h"
using namespace std;


namespace Tmpl8
{
	//GameObject* player;

	GameObject* rect_1;
	GameObject* circle_2;

	GameObject* rect_3;

	// -----------------------------------------------------------
	// Initialize the application
	// -----------------------------------------------------------
	void Game::Init()
	{
		//player = new GameObject(vec2(0, 0));
		rect_1 = new GameObject((vec2(500, 500)));
		circle_2 = new GameObject((vec2(250, 250)));
		rect_1->setRect(32 * 5, 32 * 6);
		circle_2->setRadius(32 * 3);
		rect_3 = new GameObject((vec2(500, 500)));
		rect_3->setRect(32 * 5, 32 * 6);
		
	}
	
	// -----------------------------------------------------------
	// Close down application
	// -----------------------------------------------------------
	void Game::Shutdown()
	{
	}
	// -----------------------------------------------------------
	// Main application tick function
	// -----------------------------------------------------------


	//Sprite theSprite(new Surface("assets/ball.png"), 1);
	void Game::Tick(float deltaTime)
	{
		Draw(screen);
		rect_1->Tick(deltaTime);
		rect_3->Tick(deltaTime);
		circle_2->Tick(deltaTime);
		rect_1->GetTransform()->SetTransform(vec2(Game::mousex, Game::mousey));
		//printf("Mouse position: %i %i \n", Game::mousex, Game::mousey);

		//printf("Rect1 position: %f %f \n", rect_1->GetTransform()->GetPosition().x, rect_1->GetTransform()->GetPosition().y);

		if (rect_1->GetRectCollider()->IsCircleColliding(circle_2->GetCircleCollider()))
			printf("Rectangle 1 collides with Circle 2 \n");
		else
			printf("Rectangle 1 NOT collides with Circle 2 \n");
		/*
		if(rect_1->GetRectCollider()->IsRectColliding(rect_3->GetRectCollider()))
			printf("Rectangle 1 collides with Rect 3 \n");
		else
			printf("Rectangle 1 NOT collides with Rect 3 \n");
		/**/
		//printf("%i", player->xpos);
		//player->Tick(deltaTime);
	}

	void Game::Draw(Surface* screen)
	{
		screen->Clear(0);
		rect_1->Draw(screen);
		circle_2->Draw(screen);
		rect_3->Draw(screen);
		//player->Draw(screen);
	}

	
	void Game::KeyDown(int key) //NOTE: Do not forget the "Game::" prefix, otherwise functions don't works
	{
		//player->Input(key);	
	}
	
};