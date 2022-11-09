#pragma once
#include "Components.h"

/*
Purpose:
- Player input
*/

class PlayerComponent : public Component
{
public:
    PlayerComponent() {}
    ~PlayerComponent() {}

    TransformComponent* ptransformComponent;
    ShapeComponent* pShapeComponent;
    KinematicsComponent* pKinematicsComponent;

    void Init();
    

    void Tick(float delta) {}
    void Draw(Surface* screen) {}

    void MouseUp(int button);
    void MouseDown(int button);
    void MouseMove(int x, int y);
    void KeyUp(int key);
    void KeyDown(int key);
};

