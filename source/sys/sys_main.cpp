// AbssalEngine.cpp : Defines the entry point for the console application.
//

#include "precompiled.h"
#pragma hdrstop

#include "sys_main.h"
//define game dir paths
btFileSystemDirs	gFileSystem = btFileSystemDirs();

int main(int argc, char *argv[])
{
	//to make sure the sdl cleaning 
	atexit(SDL_Quit);

	//Boot Up game engine Here
	startUp();

	//run main game loop
	Run();

	//exit game
	shutDown();

	getchar();

    return 0;
}

void startUp(void)
{
	//start sdl and set enviroment
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		//print error on console and in the err file
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		fprintf(stderr, "SDL could not initialize! SDL Error: %s\n", SDL_GetError());

		//go to quit diret
		Quit();
	}

	//initialize the game console 
	gConsole.startUp();

	//load game configuration
	configurationGlobal.loadConfiguration(gFileSystem.getBaseSavePath() + GAME_CFG);

	//initialize the video 
	videoManagerGlobal.StartUp();

	engineGlobal.startUp();

	//welcome message
	btGameConsole::printf("STARTING %s Ver %i.%i - %s\n", GAME_NAME, GAME_MAJOR_VER, GAME_MINOR_VER, GAME_STATUS);
}

void shutDown(void)
{
	//check for config change and save them 
	//load game configuration
	configurationGlobal.saveConfiguration(gFileSystem.getBaseSavePath() + GAME_CFG);

	engineGlobal.shutDown();

	//clean video 
	videoManagerGlobal.ShutDonw();

	//clean game console 
	gConsole.shutDonw();
}

void Run(void)
{
	//start engine time counter
	btEngine::m_mainTimer.start();

	//main game loop
	do
	{
		//
		engineGlobal.thinkFrame();
		
		//Update screen
		videoManagerGlobal.PresentFrame();

	} while (!engineGlobal.sholdQuit());

	btGameConsole::printf("exiting game\n");
}

void Quit(void)
{
	//call a error exit
	exit(-1);
}
