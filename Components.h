#pragma once
/*
Purpose:
- Contain all existing components as one header

NOTE: the order that you include the headers DOES matter. If one header uses another, it needs to be set before
*/
#include "Enums.h"

#include "template.h"
#include "ObjectComponentSystem.h"



#include "TransformComponent.h"
#include "KinematicsComponent.h"
#include "MovingTileComponent.h"


#include "LevelLoader.h"

#include "ObjectCreator.h"

#include "Shape.h"
#include "Circle.h"
#include "Rectangle.h"
#include "ShapeComponent.h"
#include "Collision.h"

#include "PlayerComponent.h"





