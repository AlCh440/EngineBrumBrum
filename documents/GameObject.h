#pragma once
#include "Globals.h"
#include <string>
#include <vector>

enum class ComponentType;
class Component;
class Transform;
class ComponentTexture;
class ComponentMesh;

class GameObject {
public:
	GameObject(bool noParent = false);
	~GameObject();

	bool isEnabled = true;
	std::string name = "GameObject";


	Transform* transform;

	std::vector<GameObject*> childs;

	void PrintInspector();

	void AddComponent(Component* component);
	ComponentMesh* GetComponentMesh();
	ComponentTexture* GetComponentTexture();

	
	bool isTotalEnabled();

	GameObject* getParent();


	bool isChildFrom(GameObject* GO);

	
	bool AddChild(GameObject* GO);

	
	bool RemoveChild(GameObject* GO);

	
	void Free();

	
	bool MoveToParent(GameObject* GOparent);

private:
	GameObject* parent;

	std::vector<Component*> components;

	char aux[255] = { ' ' };
	char listComponenets[255] = { ' ' };

	int componentNum = 0;


	bool isSelected = false;
};