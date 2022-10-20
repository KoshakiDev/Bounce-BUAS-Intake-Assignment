#pragma once
#include "Components.h"

enum ShapeType {t_point, t_lineSegment, t_circle, t_rectangle};

class Shape : public Component
{
public:
    string name;
    Pixel color = 255 * 255 * 255;
    static Shape* Create(ShapeType type);
    virtual void Init() {}
    virtual void Tick(float delta) {}
    virtual void Draw(Surface* screen) {}
};

class Point : public Shape
{
public:
    Point()
    {
        point = Vector2D(0, 0);
    }
    string name = "POINT";
    Vector2D point;
    void Draw(Surface* screen)
    {
        Shape::Draw(screen);

        screen->Point(point.x, point.y, color);
    }
};

class LineSegment : public Shape
{
public:
    LineSegment()
    {
        point_1 = Vector2D(0, 0);
        point_2 = Vector2D(0, 0);
    }
    string name = "LINE";
    Vector2D point_1;
    Vector2D point_2;
    void Draw(Surface* screen)
    {
        Shape::Draw(screen);
        screen->Point(point_1.x, point_1.y, color);
        screen->Point(point_2.x, point_2.y, color);
        screen->Line(point_1.x, point_1.y, point_2.x, point_2.y, color);
    }
};

class Circle : public Shape
{
public:
    Circle()
    {
        transform = Vector2D(0, 0);
        radius = 1.0;
    }
    string name = "CIRCLE";
    Vector2D transform;
    float radius;
    void Draw(Surface* screen)
    {
        Shape::Draw(screen);
        screen->ApproximateCircle(transform.x, transform.y, radius, color);
    }
};

class Rectangle : public Shape
{
public:
    Rectangle()
    {
        transform = Vector2D(0, 0);
        width = 1.0;
        height = 1.0;
    }
    string name = "RECTANGLE";
    Vector2D transform;
    float width;
    float height;
    void Draw(Surface* screen)
    {
        Shape::Draw(screen);
        screen->Box(transform.x, transform.y, transform.x + width, transform.y + height, color);
    }
};


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

class ShapeComponent : public Component
{
public:
    ShapeComponent() {}
    ShapeComponent(ShapeType type)
    {
        pShape = Shape::Create(type);
    }
    Shape* pShape;
    virtual ~ShapeComponent() {}
};

