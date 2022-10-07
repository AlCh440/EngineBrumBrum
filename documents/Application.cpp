#include "Application.h"

#include "parson/include/parson.c"
#include "parson/include/parson.h"
#include <iostream>





using namespace std;

const char* get_file_path(const char* filename) {
	static char path_buf[2048] = { 0 };
	memset(path_buf, 0, sizeof(path_buf));
	return path_buf;
}

Application::Application()
{
	window = new ModuleWindow(this);
	input = new ModuleInput(this);
	audio = new ModuleAudio(this, true);
	renderer3D = new ModuleRenderer3D(this);
	camera = new ModuleCamera3D(this);
	scene_01 = new ModuleScene_01(this);

	// The order of calls is very important!
	// Modules will Init() Start() and Update in this order
	// They will CleanUp() in reverse order

	// Main Modules
	AddModule(window);
	AddModule(camera);
	AddModule(input);
	AddModule(audio);
	
	AddModule(scene_01);

	// Renderer last!
	AddModule(renderer3D);
}

Application::~Application()
{
	list<Module*>::iterator item = list_modules.end();

	while (list_modules.empty() == true) {

		item = list_modules.erase(item);
		item--;
	}
	
}

bool Application::Init()
{
	bool ret = true;

	// Call Init() in all modules
	list<Module*>::iterator item = list_modules.begin();



	while (item != list_modules.end() && ret == true) {

		ret = item._Ptr->_Myval->Init();
		item++;
	}

	// After all Init calls we call Start() in all modules
	LOG("Application Start --------------");
	
	item = list_modules.begin();

	while (item != list_modules.end() && ret == true) {

		ret = item._Ptr->_Myval->Start();
		item++;
	}
	ms_timer.Start();
	return ret;
}

// ---------------------------------------------
void Application::PrepareUpdate()
{
	frameCount++;
	lastSecFrameCount++;
	dt = frameDuration.ReadMs();
	frameDuration.Start();
}

// ---------------------------------------------
void Application::FinishUpdate()
{
	if (SaveGameRequest)
	{
		SaveGame();
		SaveGameRequest = false;
	}

	float secondsSinceStartup = startupTime.ReadSec();
	

	if (lastSecFrameTime.Read() > 1000) {
		lastSecFrameTime.Start();
		framesPerSecond = lastSecFrameCount;
		lastSecFrameCount = 0;
		averageFps = (averageFps + framesPerSecond) / 2;
	}

	//LOG("FPS: %f", (float)framesPerSecond);

	static char title[256];
	//sprintf_s(title, 256, "Av.FPS: %.2f FPS: %i Delta Time: %.3f Time since startup: %.3f Frame Count: %I64u ",
	//	averageFps, framesPerSecond, dt, secondsSinceStartup, frameCount);
	/*int x,y;
	input->GetMouseWorldPosition(x,y);
	sprintf_s(title, 256, "Mouse position x %d y %d, Camera x %d y %d", x, y,render->camera.x,render->camera.y);*/

	sprintf_s(title, 256, "FPS: %i", framesPerSecond);



	float delay = float(1000 / maxFrameRate) - frameDuration.ReadMs();



	PerfTimer* delayt = new PerfTimer();
	delayt->Start();
	if (maxFrameRate > 0 && delay > 0) SDL_Delay(delay);

	
	window->SetTitle(title);
}

void Application::SaveGame()
{
	
		JSON_Value* schema = json_parse_string("{\"BrumBrum\":\"\"}");
		JSON_Value* user_data = json_parse_file("user_data.json");
		const char* buf;
		const char* name = NULL;
		if (user_data == NULL || json_validate(schema, user_data) != JSONSuccess) {
			buf = { "are" };
			user_data = json_value_init_object();
			json_object_set_string(json_object(user_data), "name", buf);
			json_serialize_to_file(user_data, "user_data.json");
		}
		name = json_object_get_string(json_object(user_data), "name");
		printf("Hello, %s.", name);
		json_value_free(schema);
		json_value_free(user_data);
		
	
}

void Application::LoadGame()
{

}

// Call PreUpdate, Update and PostUpdate on all modules
update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;
	PrepareUpdate();
	
	list<Module*>::iterator item = list_modules.begin();

	while (item != list_modules.end() && ret == true) {

		ret = item._Ptr->_Myval->PreUpdate(dt);
		item++;
	}

	if (input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)
		SaveGameRequest = true;

	item = list_modules.begin();

	while (item != list_modules.end() && ret == true) {

		ret = item._Ptr->_Myval->Update(dt);
		item++;
	}
	
	item = list_modules.begin();

	while (item != list_modules.end() && ret == true) {

		ret = item._Ptr->_Myval->PostUpdate(dt);
		item++;
	}


	FinishUpdate();
	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;
	list<Module*>::iterator item = list_modules.begin();

	while (item != list_modules.end() && ret == true) {

		ret = item._Ptr->_Myval->CleanUp();
		item++;
	}

	return ret;
}

void Application::AddModule(Module* mod)
{
	list_modules.push_back(mod);
}