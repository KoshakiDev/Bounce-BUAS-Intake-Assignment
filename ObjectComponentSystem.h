#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>
#include <cassert>

#include "surface.h"

#include <SDL.h>


/*
The Object Component System was inspired by Vittorio Romeo
https://www.youtube.com/watch?v=QAmtgvwHInM
*/


using namespace std;
using namespace Tmpl8;


// Forward-declaration of Component, Object, and Manager
class Component;
class Object; 
class Manager;

/*
We define a typedef for the component ID type:
*/
using ComponentID = std::size_t;
using Group = std::size_t;

inline ComponentID getNewComponentTypeID()
{
	/*
	This function automacially gives and guarantees 
	a unique ID every time we call a function with a specific type.

	We store a `static` lastID variable. 
	Static means that every time we call this function it will refer to the same `lastID` instance.
    */
	static ComponentID lastID = 0u;
	return lastID++;
}


template <typename T> inline ComponentID getComponentTypeID() noexcept
{
	/*
	This function returns a unique ComponentID based on the passed type
	
	We assure that the passed type inherits from 'Component'.

	First call with a passed type 'T1' will initialize `typeID` with an unique ID

	Subsequent calls with the same passed type `T1` will return the same ID.
	*/
	static_assert (std::is_base_of<Component, T>::value, "");
	static ComponentID typeID = getNewComponentTypeID();
	return typeID;
}

constexpr std::size_t maxComponents = 32;
constexpr std::size_t maxGroups = 32;

using ComponentBitSet = std::bitset<maxComponents>;
using GroupBitset = std::bitset<maxGroups>;

using ComponentArray = std::array<Component*, maxComponents>;

/*
Component Bitset (Holds whether an entity has a certain component):
	[ 0 0 0 0 0 0 0 1 0 0 1 ]
					|     |
					|	  \___ Component Type #0
					|
					\___ Component Type #3

Component Array (Holds reference to a certain component):
	[0] 	= (Component Type #0)*
	[1] 	= nullptr
	[2] 	= nullptr
	[3] 	= (Component Type #3)*
	[4] 	= nullptr
	...
	[11] 	= nullptr
*/


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

	// Methods to control the lifetime of the entity.
	bool isActive() const { return active; }
	void destroy() { active = false; }

	/*
	Groups will be handled at runtime, not compile-time:
    therefore we will pass groups as a function argument.
	*/

	bool hasGroup(Group mGroup)
	{
		return groupBitset[mGroup];
	}

	/*
	"Add/Remove Group" methods alter the bitset.
    
	We are going to call `Manager::addtoGroup` here. 
	Therefore, we will define this method after the definition of `Manager`
	*/

	void addGroup(Group mGroup) noexcept;
	void delGroup(Group mGroup)
	{
		groupBitset[mGroup] = false;
		/*
		Manager will automatically remove
        entities from the "wrong" group containers during
        refresh.
		We won't notify the manager that a group has been
        removed here. 
		*/
	}

	template <typename T> 
	bool hasComponent() const
	{
		//To check if this entity has a component, we simply query the bitset.
		return componentBitset[getComponentTypeID<T>()];
	}

	/*
	`T` is the component type. 
	`TArgs` is a parameter pack of types used to construct the component.
	*/

	template <typename T, typename... TArgs>
	T& addComponent(TArgs&&... mArgs)
	{
		// Assure a component doesn't already exist
		assert(!hasComponent<T>());
		// Construct the component 'T' with the passed arguments 
		T* c(new T(std::forward<TArgs>(mArgs)...));
		// Set the component's owner to the current instance.
		c->owner = this;
		// Wrap the raw pointer into a smart one. This creates reference to the object.
		std::unique_ptr<Component> uPtr{ c };

		// Add the smart pointer to our component container.
		components.emplace_back(std::move(uPtr));

		// Add the 'T' component to the bitset and to the array.
		componentArray[getComponentTypeID<T>()] = c;
		componentBitset[getComponentTypeID<T>()] = true;

		c->Init();
		return *c;
	}

	template <typename T>
	T& getComponent() const
	{
		/*
		To retrieve a specific component, we get it from the array. 
		We'll also assert its existance.
		*/
		assert(hasComponent<T>());
		auto ptr(componentArray[getComponentTypeID<T>()]);
		return *reinterpret_cast<T*>(ptr);
	}


private:
	Manager& manager;
	// We'll keep track of whether the entity is alive or dead with a boolean
	bool active = true;
	// We'll store the components in a private vector of `std::unique_ptr<Component>`, to allow polymorphism.
	std::vector<std::unique_ptr<Component>> components;
	/*
	We'll add an array to quickly get a component with a specific ID,
	and a bitset to check the existance of a component with a specific ID.
	*/
	ComponentArray componentArray;
	ComponentBitSet componentBitset;
	GroupBitset groupBitset;
	
};


/*
`Entity` is an aggregate of components, 
`Manager` is an aggregate of entities. 
Implementation is straightforward, and resembles the previous one

Groups are implemented by giving a group bitset to every entity, 
and storing entity pointers in the entity manager.
*/
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
		/*
		During refresh, we need to remove dead entities and entities
		with incorrect groups from the buckets.
		*/
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

		/*
		We're going through all entities and erasing the "dead" ones.
        */

		objects.erase(std::remove_if(std::begin(objects), std::end(objects),
			[](const std::unique_ptr<Object>& mObject)
			{
				return !mObject->isActive();
			}),
			std::end(objects));
	}

	/*
	When we add a group to an entity, 
	we just add it to the correct "group bucket".
	*/

	void AddToGroup(Object* mObject, Group mGroup)
	{
		groupedObjects[mGroup].emplace_back(mObject);
	}

	/*
	To get entities that belong to a certain group, 
	we can simply get one of the "buckets" from the array.
	*/

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
	/*
	We store entities in groups by creating "group buckets" in an array. 
	`std::vector<Entity*>` could be also replaced for `std::set<Entity*>`.
	*/
	std::vector<std::unique_ptr<Object>> objects;
	std::array<std::vector<Object*>, maxGroups> groupedObjects;
};