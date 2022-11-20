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
	 
	Every time we call this function with a specific type `T`,
    we are actually calling an instantiation of this template,
    with its own unique static `typeID` variable.

    Upon calling this function for the first time with a specific
    type `T1`, `typeID` will be initialized with an unique ID.
    Subsequent calls with the same type `T1` will return the same ID.
	
	We use a `static_assert` to make sure this function
    is only called with types that inherit from `Component`.
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
Assumptions:
1. An entity can only contain only one instance of a certain component type.
2. Every component type has an ID integer number (first component type will have ID 0, and the other component types will have ID 1, 2, 3, ..., N)

With these assumptions,
We create a sequence of bits (and a linear array) that helps us check
whether or not an entity has a certain component type.

Component bitset (Holds whether an entity has a certain component):
	[ 0 0 0 0 0 0 0 1 0 0 1 ]
					|     |
					|	  \___ Component Type #0
					|
					\___ Component Type #3

Component array (Holds reference to a certain component):
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
	/*
	Defining a base `Component` class. Game components will inherit from this class.
	
	We will use a pointer to store the parent entity/object as "owner".
	*/
	Object* owner;
	/*
	Usually a game component will have:
		* Some data
		* Update behavior
		* Drawing behavior

	Therefore we define two virtual methods that
	will be overridden by game component types.
	*/
	virtual void Init() {}
	virtual void Tick(float delta) {}
	virtual void Draw(Surface* screen) {}
	//Input
	virtual void MouseUp(int button) {}
	virtual void MouseDown(int button) {}
	virtual void MouseMove(int x, int y) {}
	virtual void KeyUp(int key) {}
	virtual void KeyDown(int key) {}
	
	/*
	As we'll be using this class polymorphically, it requires a virtual destructor.
	*/
	virtual ~Component() {}
};

class Object 
{
/*
Object is a container for components. 
It has methods to add, update, and draw components.
*/
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

	/*
	Methods to control the lifetime of the entity.
	*/

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
		We won't notify the manager that a group has been
        removed here, as it will automatically remove
        entities from the "wrong" group containers during
        refresh.
		*/
	}

	/*
	To check if this entity has a component, we simply query the bitset.
	We check if a certain entity has a component with a "bitwise and"
	*/

	template <typename T> bool hasComponent() const
	{
		return componentBitset[getComponentTypeID<T>()];
	}

	/*
	This method adds components to our entity.
    We'll take advantage of C++11 variadic templates and emplacement to directly construct our components in place.
    
	`T` is the component type. 
	`TArgs` is a parameter pack of types used to construct the component.
	*/

	template <typename T, typename... TArgs>
	T& addComponent(TArgs&&... mArgs)
	{
		/*
		Before adding a component, 
		we make sure it doesn't already exist by using an assertion
		*/
		assert(!hasComponent<T>());
		/*
		First, allocate memory for the component of type `T`, 
		by forwarding the passed arguments to the Component T's constructor.
		*/
		T* c(new T(std::forward<TArgs>(mArgs)...));

		/*
		We set the component's entity to the current instance.
		*/
		c->owner = this;

		/*
		To add (emplace) the reference to the component to our component container,
		We will wrap the raw pointer into a smart one.
		
		Keeping a reference also helps us make sure we do not leak any memory 
		by releasing it later when we no longer need it
		*/

		std::unique_ptr<Component> uPtr{ c };

		/*
		Now we'll add the smart pointer to our component container.
        (`std::move` is required, as `std::unique_ptr` cannot be copied)
		*/

		components.emplace_back(std::move(uPtr));

		/*
		When we add a component of type `T`, we add it to the bitset and to the array.
		*/
		componentArray[getComponentTypeID<T>()] = c;
		componentBitset[getComponentTypeID<T>()] = true;

		/*
		We can now call `Component::Init()`
		*/
		c->Init();

		/*
		...and we will return a reference to the newly added
		component, in case the user wants to do something with it.
		*/
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
If `Entity` is an aggregate of components, `Manager` is an aggregate of entities. 
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
        This is known as the "erase-remove idiom".
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