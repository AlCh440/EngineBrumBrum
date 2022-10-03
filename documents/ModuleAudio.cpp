#include "Globals.h"
#include "Application.h"
#include "ModuleAudio.h"


ModuleAudio::ModuleAudio(Application* app, bool start_enabled) : Module(app, start_enabled)
{}

// Destructor
ModuleAudio::~ModuleAudio()
{}

// Called before render is available
bool ModuleAudio::Init()
{
	LOG("Loading Audio Mixer");
	bool ret = true;
	

	return ret;
}

// Called before quitting
bool ModuleAudio::CleanUp()
{

	return true;
}

// Play a music file
bool ModuleAudio::PlayMusic(const char* path, float fade_time)
{
	bool ret = true;




	LOG("Successfully playing %s", path);
	return ret;
}

// Load WAV
unsigned int ModuleAudio::LoadFx(const char* path)
{
	unsigned int ret = 0;



	return ret;
}

// Play WAV
// There might be an error here (instead of -1 maybe -2 or 0)
bool ModuleAudio::PlayFx(unsigned int id, int repeat)
{
	bool ret = false;

	return ret;
}