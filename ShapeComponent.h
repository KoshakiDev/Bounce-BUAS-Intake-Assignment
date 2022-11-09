#pragma once
#include "Components.h"

/*
Purpose:
- Contain the geometrical information about the object (circle or rectangle)
- Draw the visual representation of the object
*/


//class Shape;

class ShapeComponent : public Component
{
public:
    ShapeComponent() {}
    
    ShapeComponent(ShapeType type);
    
    Shape* pShape;
    TransformComponent* ptransformComponent;


    void Init();

    void Tick(float delta)
    {
        pShape->Tick(delta);
    }
    void Draw(Surface* screen)
    {
        pShape->Draw(screen);
    }
    void MouseUp(int button) 
    {
        pShape->MouseUp(button);
    }
    void MouseDown(int button) 
    {
        pShape->MouseDown(button);
    }
    void MouseMove(int x, int y) 
    {
        pShape->MouseMove(x, y);
    }
    void KeyUp(int key)
    {
        pShape->KeyUp(key);   
    }
    void KeyDown(int key) 
    {
        pShape->KeyDown(key);
    }
    virtual ~ShapeComponent() {}  
};

