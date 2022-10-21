#pragma once
#include "Components.h"
#include <unordered_map>
#include <map>
#include <any> 

enum ShapeType {t_point, t_lineSegment, t_circle, t_rectangle};

class Shape
{
public:
    ShapeType type;
    Pixel color = 255 * 255 * 255;
    Vector2D position;
    unordered_map<string, auto> params;

    // some function which returns the shape information
    Shape* getInfo(Shape shape);
    
    static Shape* Create(ShapeType set_type);
    virtual void Init() {}
    virtual void Tick(float delta) {}
    virtual void Draw(Surface* screen) {}
};

class Point : public Shape
{
public:
    Point()
    {
        type = t_point;
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
        type = t_lineSegment;
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
        type = t_circle;
        position = Vector2D(0, 0);
        //radius = 1.0;
        params["radius"] = 1.0;
    }
    //float radius;
    
    void Draw(Surface* screen)
    {
        //cout << "a " << name <<" is being drawn with position " << transform << " and radius " << radius << endl;
        screen->ApproximateCircle(position.x, position.y, params["radius"], color);
    }
};

class Rectangle : public Shape
{
public:
    Rectangle()
    {
        type = t_rectangle;
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

