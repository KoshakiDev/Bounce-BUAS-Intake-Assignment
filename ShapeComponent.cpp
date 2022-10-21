#include "Components.h"

Shape* Shape::Create(ShapeType type)
{
    if (type == t_point)
        return new Point();
    else if (type == t_lineSegment)
        return new LineSegment();
    else if (type == t_circle)
        return new Circle();
    else if (type == t_rectangle)
        return new Rectangle();
    else return NULL;
}


// currently under construction
Shape* Shape::getInfo(Shape shape)
{
    if (shape.type == t_point)
        return new Point();
    else if (shape.type == t_lineSegment)
        return new LineSegment();
    else if (shape.type == t_circle)
        return new Circle();
    else if (shape.type == t_rectangle)
        return new Rectangle();
    else return NULL;

}