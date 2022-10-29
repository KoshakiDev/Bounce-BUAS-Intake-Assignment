#pragma once
#include "Components.h"
#include <unordered_map>
#include <map>
#include <any>

extern Pixel moldy_white, moldy_black;

enum ShapeType {t_circle, t_rectangle};

class Shape
{
public:
    ShapeType type;
    Pixel color = moldy_black;
    
    TransformComponent* ptransformComponent;
    //Vector2D position;
    
    /*
    NOTE: I tried to use any, but turns out it is literally useless. I just decided to keep only floats
    in there (I also figured that there is no purpose to store a vector2d there; it can be stored as pointx and pointy)
    */
    unordered_map<string, float> params;
    unordered_map<string, bool> material_type;
    
    static Shape* Create(ShapeType set_type);
    virtual void Init() {}
    virtual void Tick(float delta) {}
    virtual void Draw(Surface* screen) {}
};

class Circle : public Shape
{
public:
    Circle()
    {
        type = t_circle;
        //position = Vector2D(0, 0);
        params["radius"] = float(1.0);
        material_type["ball"] = true;
        material_type["balloon"] = false;
        material_type["rock"] = false;
    }
    
    void Draw(Surface* screen)
    {
        /**/
        if (material_type["balloon"])
        {
            screen->Balloon(ptransformComponent->position.x, ptransformComponent->position.y, params["radius"], color);
        }
        if (material_type["ball"])
        {
            screen->Ball(ptransformComponent->position.x, ptransformComponent->position.y, params["radius"], color);
        }
        if (material_type["rock"])
        {
            screen->Rock(ptransformComponent->position.x, ptransformComponent->position.y, params["radius"], color);
        }
        /**
        screen->ApproximateCircle(
            ptransformComponent->position.x, 
            ptransformComponent->position.y, 
            params["radius"], 
            color);
        /**/
    }
};

class Rectangle : public Shape
{
public:
    Rectangle()
    {
        type = t_rectangle;
        params["width"] = 1.0;
        params["height"] = 1.0;
    }
    void Draw(Surface* screen)
    {
        if (material_type["basic_tile"])
        {
            screen->Box(ptransformComponent->position.x,
                ptransformComponent->position.y,
                ptransformComponent->position.x + params["width"],
                ptransformComponent->position.y + params["height"],
                color);
        }
        if (material_type["flag"])
        {
            screen->Flag(ptransformComponent->position.x,
                ptransformComponent->position.y,
                ptransformComponent->position.x + params["width"],
                ptransformComponent->position.y + params["height"],
                color);
        }
        if (material_type["skull"])
        {
            screen->Skull(ptransformComponent->position.x,
                ptransformComponent->position.y,
                ptransformComponent->position.x + params["width"],
                ptransformComponent->position.y + params["height"],
                color);
        }
        if (material_type["accelerator_up"])
        {
            screen->AcceleratorUp(ptransformComponent->position.x,
                ptransformComponent->position.y,
                ptransformComponent->position.x + params["width"],
                ptransformComponent->position.y + params["height"],
                color);
        }
        if (material_type["accelerator_down"])
        {
            screen->AcceleratorDown(ptransformComponent->position.x,
                ptransformComponent->position.y,
                ptransformComponent->position.x + params["width"],
                ptransformComponent->position.y + params["height"],
                color);
        }
        if (material_type["accelerator_left"])
        {
            screen->AcceleratorLeft(ptransformComponent->position.x,
                ptransformComponent->position.y,
                ptransformComponent->position.x + params["width"],
                ptransformComponent->position.y + params["height"],
                color);
        }
        if (material_type["accelerator_right"])
        {
            screen->AcceleratorRight(ptransformComponent->position.x,
                ptransformComponent->position.y,
                ptransformComponent->position.x + params["width"],
                ptransformComponent->position.y + params["height"],
                color);
        }
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
        pShape->ptransformComponent = &owner->getComponent<TransformComponent>();
    }
    void Tick(float delta)
    {
        pShape->Tick(delta);
    }
    void Draw(Surface* screen)
    {
        pShape->Draw(screen);
    }

    virtual ~ShapeComponent() {}


    void KeyUp(int key)
    {
        if (key == SDL_SCANCODE_Z)
        {
            if (pShape->color == moldy_white)
            {
                pShape->color = moldy_black;
            }
            else if (pShape->color == moldy_black)
            {
                pShape->color = moldy_white;
            }
        }
        /**/
        if (key == SDL_SCANCODE_J) //Balloon
        {
            pShape->material_type["balloon"] = true;
            pShape->material_type["ball"] = false;
            pShape->material_type["rock"] = false;
        }
        if (key == SDL_SCANCODE_K) //Ball
        {

            pShape->material_type["balloon"] = false;
            pShape->material_type["ball"] = true;
            pShape->material_type["rock"] = false;
        }
        if (key == SDL_SCANCODE_L) //Rock
        {
            pShape->material_type["balloon"] = false;
            pShape->material_type["ball"] = false;
            pShape->material_type["rock"] = true;
        }
        /**/
    }
    
};

