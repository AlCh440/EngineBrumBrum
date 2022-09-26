#include "Globals.h"
#include "Application.h"
#include "ModuleScene_01.h"

#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl.h"


ModuleScene_01::ModuleScene_01(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleScene_01::~ModuleScene_01()
{}

// Load assets
bool ModuleScene_01::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));

	return ret;
}

// Load assets
bool ModuleScene_01::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update
update_status ModuleScene_01::Update(float dt)
{
	
	ImGui::Begin("My First Tool", &myToolActive, ImGuiWindowFlags_MenuBar);
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Open..", "Ctrl+O")) { /* Do stuff */ }
			if (ImGui::MenuItem("Save", "Ctrl+S")) { /* Do stuff */ }
			if (ImGui::MenuItem("Close", "Ctrl+W")) { myToolActive = false; }
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}
	float color[4] = { 124, 200, 54, 255 };
	// Edit a color stored as 4 floats
	ImGui::ColorEdit4("Color", color);
	
	// Generate samples and plot them
	float samples[100];
	for (int n = 0; n < 100; n++)
		samples[n] = sinf(n * 0.2f + ImGui::GetTime() * 1.5f);
	ImGui::PlotLines("Samples", samples, 100);
	
	// Display contents in a scrolling region
	ImGui::TextColored(ImVec4(1, 1, 0, 1), "Important Stuff");
	ImGui::BeginChild("Scrolling");
	for (int n = 0; n < 50; n++)
		ImGui::Text("%04d: Some text", n);
	ImGui::EndChild();
	ImGui::End();
	return UPDATE_CONTINUE;
}

void ModuleScene_01::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
}

