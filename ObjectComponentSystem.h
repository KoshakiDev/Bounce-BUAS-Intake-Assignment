#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

#include "surface.h"

#include <SDL.h>


/*
The Object Component System was inspired by "Let's Make Games" Entity Component System
https://www.youtube.com/watch?v=XsvI8Sng6dk
*/


using namespace std;
using namespace Tmpl8;

class Component;
class Object; 
class Manager;

using ComponentID = std::size_t;
using Group = std::size_t;

inline ComponentID getNewComponentTypeID()
{
	static ComponentID lastID = 0u;
	return lastID++;
}

template <typename T> inline ComponentID getComponentTypeID() noexcept
{
	static_assert (std::is_base_of<Component, T>::value, "");
	static ComponentID typeID = getNewComponentTypeID();
	return typeID;
}

constexpr std::size_t maxComponents = 32;
constexpr std::size_t maxGroups = 32;

using ComponentBitSet = std::bitset<maxComponents>;
using GroupBitset = std::bitset<maxGroups>;

using ComponentArray = std::array<Component*, maxComponents>;


class Component
{
public:
	Object* owner;

	virtual void Init() {}
	virtual void Tick(float delta) {}
	virtual void Draw(Surface* screen) {}
	//Input
	virtual void MouseUp(int button) {}
	virtual void MouseDown(int button) {}
	virtual void MouseMove(int x, int y) {}
	virtual void KeyUp(int key) {}
	virtual void KeyDown(int key) {}
	
	virtual ~Component() {}
};

class Object 
{
public:
	Object(Manager& mManager) : manager(mManager) {}

	void Tick(float delta)
	{
		for (auto& c : components) c->Tick(delta);
	}
	void Draw(Surface* screen)
	{
		for (auto& c : components) c->Draw(screen);
	}
	//Input
	void MouseUp(int button) 
	{
		for (auto& c : components) c->MouseUp(button);
	}
	void MouseDown(int button) 
	{
		for (auto& c : components) c->MouseDown(button);
	}
	void MouseMove(int x, int y) 
	{
		for (auto& c : components) c->MouseMove(x, y);
	}
	void KeyUp(int key) 
	{
		for (auto& c : components) c->KeyUp(key);
	}
	void KeyDown(int key) 
	{
		for (auto& c : components) c->KeyDown(key);
	}



	bool isActive() const { return active; }
	void destroy() { active = false; }

	bool hasGroup(Group mGroup)
	{
		return groupBitset[mGroup];
	}

	void addGroup(Group mGroup);
	void delGroup(Group mGroup)
	{
		groupBitset[mGroup] = false;
	}
	template <typename T> bool hasComponent() const
	{
		return componentBitset[getComponentTypeID<T>()];
	}

	template <typename T, typename... TArgs>
	T& addComponent(TArgs&&... mArgs)
	{
		T* c(new T(std::forward<TArgs>(mArgs)...));
		c->owner = this;
		std::unique_ptr<Component>uPtr{ c };
		components.emplace_back(std::move(uPtr));

		componentArray[getComponentTypeID<T>()] = c;
		componentBitset[getComponentTypeID<T>()] = true;

		c->Init();
		return *c;
	}

	template<typename T> T& getComponent() const
	{
		auto ptr(componentArray[getComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);
	}

private:
	Manager& manager;
	bool active = true;
	std::vector<std::unique_ptr<Component>> components;

	ComponentArray componentArray;
	ComponentBitSet componentBitset;
	GroupBitset groupBitset;
};

class Manager
{
public:

	void Tick(float delta)
	{
		for (auto& o : objects) o->Tick(delta);
	}
	void Draw(Surface* screen)
	{
		for (auto& o : objects) o->Draw(screen);
	}
	//Input
	void MouseUp(int button)
	{
		for (auto& o : objects) o->MouseUp(button);
	}
	void MouseDown(int button)
	{
		for (auto& o : objects) o->MouseDown(button);
	}
	void MouseMove(int x, int y)
	{
		for (auto& o : objects) o->MouseMove(x, y);
	}
	void KeyUp(int key)
	{
		for (auto& o : objects) o->KeyUp(key);
	}
	void KeyDown(int key)
	{
		for (auto& o : objects) o->KeyDown(key);
	}

	void refresh()
	{

		for (auto i(0u); i < maxGroups; i++)
		{
			auto& v(groupedObjects[i]);
			v.erase(
				std::remove_if(std::begin(v), std::end(v),
					[i](Object* mObject)
					{
						return !mObject->isActive() || !mObject->hasGroup(i);
					}),
				std::end(v));
		}


		objects.erase(std::remove_if(std::begin(objects), std::end(objects),
			[](const std::unique_ptr<Object>& mObject)
			{
				return !mObject->isActive();
			}),
			std::end(objects));
	}

	void AddToGroup(Object* mObject, Group mGroup)
	{
		groupedObjects[mGroup].emplace_back(mObject);
	}

	std::vector<Object*>& getGroup(Group mGroup)
	{
		return groupedObjects[mGroup];
	}

	Object& addObject()
	{
		Object* o = new Object(*this);
		std::unique_ptr<Object> uPtr{ o };
		objects.emplace_back(std::move(uPtr));
		return *o;
	}

private:
	std::vector<std::unique_ptr<Object>> objects;
	std::array<std::vector<Object*>, maxGroups> groupedObjects;
};