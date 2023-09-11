#pragma once
#ifndef ECSCOMPONENT_H
#define ECSCOMPONENT_H
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>
#include "../../RequireLibs.h"
#include "../SaveSystem/CheckVar.h"

using namespace std;

class Component;
class Entity;
class Manager;
class Transform;

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
	Entity* entity;
	bool enabled = true;
	virtual void init() {}
	virtual void update() {}
	virtual void draw() {}
	virtual void PreRender(){}
	virtual void PostRender(){}
	virtual void clean() {}
	virtual std::string serialize() { return ""; }
	virtual void deserialize(std::string g, std::string path = "") {}
	virtual ~Component() {}
};

class Transform {
public:
	glm::vec3 Position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 LocalPosition = glm::vec3(1.0f, 1.0f, 1.0f);


	glm::vec3 Rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 Scale = glm::vec3(1.0f, 1.0f, 1.0f);

	glm::mat4 Matrix = glm::mat4(1.0f);
	glm::quat rotation;

	void update() {
		Matrix = glm::mat4(1.0f);

		// Aplicar traslación

		Matrix = glm::translate(Matrix, glm::vec3(Position.x, Position.y, Position.z));
		glm::quat rotationZ = glm::angleAxis(glm::radians(Rotation.x), glm::vec3(0.0f, 0.0f, 1.0f));
		glm::quat rotationY = glm::angleAxis(glm::radians(Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		glm::quat rotationX = glm::angleAxis(glm::radians(Rotation.z), glm::vec3(1.0f, 0.0f, 0.0f));

		rotation = rotationZ * rotationY * rotationX;

		//glm::mat4 rotationMatrix = glm::mat4_cast(rotation);


		Matrix *= glm::mat4_cast(rotation);
		Matrix = glm::scale(Matrix, Scale);

		//std::cout << "Position: (" << Position.x << ", " << Position.y << ", " << Position.z << ")" << std::endl;
		//std::cout << "Rotation: (" << Rotation.x << ", " << Rotation.y << ", " << Rotation.z << ")" << std::endl;
		//std::cout << "Scale: (" << Scale.x << ", " << Scale.y << ", " << Scale.z << ")" << std::endl;
	}

	glm::mat4 GetMatrix() {
		return Matrix;
	}

	//SAVE DATA AND LOAD
	std::string serialize() {
		json componentData;
		componentData["posx"] = Position.x;
		componentData["posy"] = Position.y;
		componentData["posz"] = Position.z;
		componentData["scalex"] = Scale.x;
		componentData["scaley"] = Scale.y;
		componentData["scalez"] = Scale.z;
		componentData["rotationx"] = Rotation.x;
		componentData["rotationy"] = Rotation.y;
		componentData["rotationz"] = Rotation.z;

		return componentData.dump ();
	}

	void deserialize(std::string g, std::string path = "") {
		json componentData = json::parse(g);


		if (CheckVar::Has(componentData, "posx"))
			Position.x = (float)componentData["posx"];

		if (CheckVar::Has (componentData, "posy"))
			Position.y = (float)componentData["posy"];

		if (CheckVar::Has(componentData, "posz"))
			Position.z = (float)componentData["posz"];

		if (CheckVar::Has(componentData, "scalex"))
			Scale.x = (float)componentData["scalex"];

		if (CheckVar::Has(componentData, "scaley"))
			Scale.y = (float)componentData["scaley"];

		if (CheckVar::Has(componentData, "scalez"))
			Scale.z = (float)componentData["scalez"];

		if (CheckVar::Has(componentData, "rotationx"))
			Rotation.x = (float)componentData["rotationx"];

		if (CheckVar::Has(componentData, "rotationy"))
			Rotation.y = (float)componentData["rotationy"];

		if (CheckVar::Has(componentData, "rotationz"))
			Rotation.z = (float)componentData["rotationz"];



		std::cout << "Position: (" << (float)componentData["posx"] << ", " << (float)componentData["posy"] << ", " << (float)componentData["posz"] << ")" << std::endl;
		std::cout << "Rotation: (" << (float)componentData["rotationx"] << ", " << (float)componentData["rotationy"] << ", " << (float)componentData["rotationz"] << ")" << std::endl;
		std::cout << "Scale: (" << (float)componentData["scalex"] << ", " << (float)componentData["scaley"] << ", " << (float)componentData["scalez"] << ")" << std::endl;
	}
};

class Entity
{

private:
	//Manager& manager;
	bool active = true;
	std::vector<Component*> components;

	ComponentArray componentArray;
	ComponentBitSet componentBitset;
	GroupBitset groupBitset;



	
public:
	std::string ObjectName = "New Entity";
	std::string ObjectTag = "None";
	int objectID = 1;
	Transform* transform = new Transform();

	Entity* entity;
	Entity* parent;
	vector<Entity*> childrens;

	//Entity(Manager& mManager) : manager(mManager) {}

	void addChild (Entity* newChild) {
		childrens.push_back (newChild);
	}

	void update()
	{
		//C++20 REQUIRE FOR THIS
		/*for (Entity* g : childrens) {
			if (g != nullptr && g->parent != this) {
				auto it = std::ranges::find(childrens, g);
				if (it != childrens.end()) {
					delete g;
					childrens.erase(it);
				}
			}
		}*/

		for (auto it = childrens.begin(); it != childrens.end();) {
			Entity* g = *it;
			if (g != nullptr && g->parent != this) {
				it = std::find(childrens.begin(), childrens.end(), g);
				if (it != childrens.end()) {
					delete g;
					it = childrens.erase(it);
				}
			}
			else {
				++it;
			}
		}

		for (auto& c : components)
		{
			c->entity = entity;
			
			if (c->enabled)
			c->update();
		}

		for (auto& c : components)
		{
			c->entity = entity;

			if (c->enabled)
				c->update();
		}

		transform->update();

		entityUpdate();
	}


	void PreRender() {
		for (auto& c : components)
		{
			c->entity = entity;

			if (c->enabled)
				c->PreRender();
		}
	}

	void PostRender() {
		for (auto& c : components)
		{
			c->entity = entity;

			if (c->enabled)
				c->PostRender();
		}
	}


	void draw()
	{
		for (auto& c : components) { 
			if (c->enabled)
				c->draw();
		}
	}

	void entityUpdate();

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


	template <typename T, typename... TArgs>
	T& addComponent(TArgs&&... mArgs)
	{
		T* c = new T(std::forward<TArgs>(mArgs)...);
		c->entity = this;
		components.emplace_back(c);

		componentArray[getComponentTypeID<T>()] = c;
		componentBitset[getComponentTypeID<T>()] = true;

		if (c->enabled)
		c->init();
		return *c;
	}

	template<typename T> T& getComponent() const
	{
		auto ptr(componentArray[getComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);
	}

	
	template <typename T>
	std::vector<T*> getComponents() const
	{
		std::vector<T*> result;
		for (auto& c : components)
		{
			T* component = dynamic_cast<T*>(c);
			if (component)
			{
				result.push_back(component);
			}
		}
		return result;
	}


	template <typename T> bool hasComponent() const
	{
		return componentBitset[getComponentTypeID<T>()];
	}

	template <typename T>
	bool removeComponent()
	{
		if (hasComponent<T>())
		{
			Component& component = getComponent<T>();
			component.clean();

			componentBitset[getComponentTypeID<T>()] = false;
			componentArray[getComponentTypeID<T>()] = nullptr;
			std::cout << "Components: " << componentArray.size() << std::endl;
			return true;
		}
		return false;
	}

	void setParent (Entity* newParent) {
		parent = newParent;
	}
};
#endif
