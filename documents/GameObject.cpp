#include "Application.h"
#include "GameObject.h"
#include "ModuleScene_01.h"

#include "Component.h"
#include "Transform.h"


#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl.h"

#include "glew/include/GL/glew.h"
#include "SDL\include\SDL_opengl.h"

GameObject::GameObject(bool noParent)
{

	transform = new Transform();
	transform->myGameObject = this;
	components.push_back(transform);

	parent = nullptr;

	if (noParent) return;

	//Application::GetInstance()->hierarchy->rootHierarchy->AddChild(this);
}

GameObject::~GameObject()
{
	//Unbind with parent
	if (parent != nullptr) {
		//Unbind with parent
		parent->RemoveChild(this);
	}

	transform = nullptr;

	//Delete Childs
	while (!childs.empty())
	{
		childs.pop_back();
	}

	//Delete Components
	for (size_t i = 0; i < components.size(); i++)
	{
		delete components[i];
		components[i] = nullptr;
	}
	components.clear();
}

void GameObject::PrintInspector()
{
	ModuleScene_01::ThemeStyleWind();
	ModuleScene_01::ThemeStylePopUp();

	char* listComponenets[]{ "Add Component", "Mesh Component", "Texture Component" };

	ImGui::Begin("Inspector");

	if (parent != nullptr)
	{
		strcpy(aux, this->name.c_str());

		
		ImGui::Checkbox("Enable", &isEnabled);

		ImGui::BulletText("Name:");
		ImGui::SameLine();

		
		ImGui::InputText("##Name", aux, 255, ImGuiInputTextFlags_EnterReturnsTrue);

		if (ImGui::IsKeyDown(ImGuiKey_Enter))
			name = aux;

		for (size_t i = 0; i < components.size(); i++)
		{
			ImGui::Separator();

			components[i]->PrintInspector();

			
		}

		ImGui::Separator();
		ImGui::Text("");
		ImGui::Text("");
		ImGui::Text("");

		ImGui::Text("");
		ImGui::SameLine(ImGui::GetWindowWidth() / 6);
		if (ImGui::Combo("##AddComponent", &componentNum, listComponenets, 3)) //number of total components u can give to a GO
		{
			switch (componentNum) {
			case 1:
			{
				
				
			}
			break;
			case 2:
			{
				
				
			}
			break;
			}
			componentNum = 0;
		}

	}
	ImGui::End();
	ImGui::PopStyleColor(4);

}

void GameObject::AddComponent(Component* component)
{
	components.push_back(component);
	component->containerParent = this;
}

ComponentMesh* GameObject::GetComponentMesh()
{
	for (size_t i = 0; i < components.size(); i++)
	{
		if (components[i]->type == ComponentType::MESH) return (ComponentMesh*)components[i];
	}
	return nullptr;
}



bool GameObject::isTotalEnabled()
{
	if (parent == nullptr) return isEnabled;

	return parent->isTotalEnabled() ? isEnabled : false;
}

GameObject* GameObject::getParent()
{
	return parent;
}

bool GameObject::isChildFrom(GameObject* GO)
{

	if (GO == this) return true;

	
	if (GO->childs.empty()) return false;

	
	for (size_t i = 0; i < GO->childs.size(); i++)
	{
		if (isChildFrom(GO->childs[i])) return true;
	}

	
	return false;
}

bool GameObject::AddChild(GameObject* GO)
{
	
	if (isChildFrom(GO)) return false;

	
	GO->parent = this;
	childs.push_back(GO);
	return true;
}

bool GameObject::RemoveChild(GameObject* GO)
{
	for (size_t i = 0; i < childs.size(); i++)
	{
		
		if (childs[i] == GO) {
			GO->parent = nullptr;
			childs.erase(childs.begin() + i);
			return true;
		}
	}
	
	return false;
}

void GameObject::Free()
{
	
	parent->RemoveChild(this);
	
}

bool GameObject::MoveToParent(GameObject* GOparent)
{
	if (parent != nullptr) {
		
		if (GOparent->isChildFrom(this)) return false;

		parent->RemoveChild(this);
	}

	
	GOparent->AddChild(this);

	return false;
}
