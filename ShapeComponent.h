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
    Pixel color = (0 << ALPHA) + (255 << RED) + (255 << GREEN) + (0 << BLUE);
    Vector2D position;
    

    /*
    NOTE: I tried to use any, but turns out it is literally useless. I just decided to keep only floats
    in there (I also figured that there is no purpose to store a vector2d there; it can be stored as pointx and pointy)
    */
    unordered_map<string, float> params;

    
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
        params["point.x"] = 0.0;
        params["point.y"] = 0.0;
    }

    void Draw(Surface* screen)
    {
        screen->Point(position.x, position.y, color);
        screen->Point(params["point.x"], params["point.y"], color);
        screen->Line(position.x, position.y, params["point.x"], params["point.y"], color);
    }
   
};

class Circle : public Shape
{
public:
    Circle()
    {
        type = t_circle;
        position = Vector2D(0, 0);
        params["radius"] = float(1.0);
    }
    
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
        params["width"] = 1.0;
        params["height"] = 1.0;
    }
    void Draw(Surface* screen)
    {
        screen->Box(position.x, position.y, position.x + params["width"], position.y + params["height"], color);
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

