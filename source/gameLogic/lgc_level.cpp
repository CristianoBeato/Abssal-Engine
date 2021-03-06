
#include "precompiled.h"
#pragma hdrstop

#include "gameLogic/lgc_level.h"

btGameLevel::btGameLevel(void)
{
}

btGameLevel::~btGameLevel(void)
{
}

void btGameLevel::LoadLevel(const std::string levelDef)
{
	//Create the Load Gui
//	m_gui.load()
}

void btGameLevel::EmptyLevel(void)
{
	//pre alocate menu form
	m_gui.create();
	//set the view
	gRendererGlobal.setupView(0.0f, -1.0f);
}

void btGameLevel::clear(void)
{
	m_gui.clear();
}

void btGameLevel::update(void)
{
	m_gui.think();

	//update all game objects
	for (auto objec : m_objects)
	{
	}

	//render gui
	m_gui.render();
}

void btGameLevel::startingLoadGui(void)
{
	//Use a frame to store all of our widgets
	m_gui.create();
}
