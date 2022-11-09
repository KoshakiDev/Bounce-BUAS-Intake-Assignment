#include "Components.h"

class Rectangle : public Shape
{
public:
    Rectangle()
    {
        type = t_rectangle;
        object_type = t_basic;
        params["width"] = 1.0;
        params["height"] = 1.0;
    }
    void Draw(Surface* screen)
    {
        screen->DrawRectangleObject(
            object_type, 
            ptransformComponent->position.x,
            ptransformComponent->position.y,
            ptransformComponent->position.x + params["width"],
            ptransformComponent->position.y + params["height"],
            color);
    }
};
