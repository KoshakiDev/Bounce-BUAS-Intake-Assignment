#pragma once
#include "Components.h"

enum ShapeType {t_point, t_lineSegment, t_circle, t_rectangle};

class Shape
{
public:
    string name;
    Pixel color = 255 * 255 * 255;
    Vector2D position;

    //virtual void getInfo() {}
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
        name = "POINT";
        position = Vector2D(0, 0);
    }
    void Draw(Surface* screen)
    {
        screen->Point(position.x, position.y, color);
    }
};

class LineSegment : public Shape
{
public:
    LineSegment()
    {
        name = "LINE";
        position = Vector2D(0, 0);
        point = Vector2D(0, 0);
    }
    Vector2D point;
    void Draw(Surface* screen)
    {
        screen->Point(position.x, position.y, color);
        screen->Point(point.x, point.y, color);
        screen->Line(position.x, position.y, point.x, point.y, color);
    }
};

class Circle : public Shape
{
public:
    Circle()
    {
        name = "CIRCLE";
        position = Vector2D(0, 0);
        radius = 1.0;
    }
    float radius;
    
    void Draw(Surface* screen)
    {
        //cout << "a " << name <<" is being drawn with position " << transform << " and radius " << radius << endl;
        screen->ApproximateCircle(position.x, position.y, radius, color);
    }
};

class Rectangle : public Shape
{
public:
    Rectangle()
    {
        name = "RECTANGLE";
        position = Vector2D(0, 0);
        width = 1.0;
        height = 1.0;
    }
    float width;
    float height;
    void Draw(Surface* screen)
    {
        screen->Box(position.x, position.y, position.x + width, position.y + height, color);
    }
};


class ShapeComponent : public Component
{
public:
    ShapeComponent() {}
    ShapeComponent(ShapeType type)
    {
        pShape = Shape::Create(type);
    }
    Shape* pShape;
    TransformComponent* ptransformComponent;

    void Init()
    {
        if (!owner->hasComponent<TransformComponent>())
        {
            owner->addComponent<TransformComponent>();
        }
        ptransformComponent = &owner->getComponent<TransformComponent>();
    }
    void Tick(float delta)
    {
        pShape->Tick(delta);
        pShape->position = ptransformComponent->position;
    }
    void Draw(Surface* screen)
    {
        pShape->Draw(screen);
    }

    virtual ~ShapeComponent() {}
};

