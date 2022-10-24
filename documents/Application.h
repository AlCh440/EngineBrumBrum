#pragma once


#include <iostream>
#include <list>
#include "Globals.h"
#include "Timer.h"
#include "Module.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleRenderer3D.h"
#include "ModuleCamera3D.h"
#include "ModuleScene_01.h"
#include "PerfTimer.h"
#include "ModuleLoadFBX.h"
#include "ModuleTextures.h"

using namespace std;


class Application
{
public:
	ModuleWindow* window;
	ModuleInput* input;
	ModuleAudio* audio;
	ModuleRenderer3D* renderer3D;
	ModuleCamera3D* camera;
	ModuleScene_01* scene_01;
	ModuleLoadFBX* loadfbx;
	ModuleTextures* texturer;

private:

	Timer	ms_timer;
	float	dt;
	list<Module*> list_modules;
public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

	// Timer thingies
	PerfTimer ptimer;
	PerfTimer frameDuration;

	Timer startupTime;
	Timer frameTime;
	Timer lastSecFrameTime;

	float frameCount = 0;
	int framesPerSecond = 0;
	int lastSecFrameCount = 0;
	bool FPSCapTo30 = false;
	float averageFps = 0.0f;
	int maxFrameRate = 30;

private:

	void AddModule(Module* mod);
	void PrepareUpdate();
	void FinishUpdate();

	void CreateFile();
	void SaveGame();
	void LoadGame();

	bool CreateFileRequest = true;
	bool SaveGameRequest = false;
	bool LoadGameRequest = false;

public:
	const char* nameOrg = NULL;
	const char* nameEngine = NULL;
};