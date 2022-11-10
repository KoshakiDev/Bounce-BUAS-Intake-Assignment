#include "Components.h"


Shape* Shape::Create(ShapeType type)
{
    if (type == t_circle)
        return new Circle();
    else if (type == t_rectangle)
        return new Rectangle();
    else return NULL;
}

void Shape::KeyUp(int key)
{
    if (key == SDL_SCANCODE_Z)
    {
        color = (color == moldy_white) ? moldy_black : 
            (color == moldy_black) ? moldy_white : color;
    }
    
}