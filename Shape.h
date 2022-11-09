#include "Components.h"
#include <unordered_map>

extern Pixel moldy_white, moldy_black;


class Shape
{
public:
    ShapeType type;
    ObjectType object_type;

    Pixel color;

    TransformComponent* ptransformComponent;

    unordered_map<string, float> params;

    static Shape* Create(ShapeType set_type);

    virtual void Init() {}
    virtual void Tick(float delta) {}
    virtual void Draw(Surface* screen) {}

    //Input
    virtual void MouseUp(int button) {}
    virtual void MouseDown(int button) {}
    virtual void MouseMove(int x, int y) {}
    virtual void KeyUp(int key);
    virtual void KeyDown(int key) {}
};
