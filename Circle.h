#include "Components.h"

class Circle : public Shape
{
public:
    Circle()
    {
        type = t_circle;
        object_type = t_ball;
        params["radius"] = float(1.0);
    }

    void Draw(Surface* screen)
    {
        screen->DrawCircleObject(
            object_type,
            ptransformComponent->position.x,
            ptransformComponent->position.y,
            params["radius"],
            color);
    }
};
