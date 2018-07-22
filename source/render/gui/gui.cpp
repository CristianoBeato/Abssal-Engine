
#include "precompiled.h"
#pragma hdrstop

#include "gui.h"

btGuiBase::btGuiBase(void)
{
}

btGuiBase::~btGuiBase(void)
{
}

void btGuiBase::create(void)
{
	//create the mouse pointer
	m_guiPointer = new btFrame("pointer", NULL, 
		glm::vec2(0.1f, 0.1f), glm::vec2(0.0f, 0.0f), 
		btColorApha(115, 111, 128, 255));

	//create the base frame
	m_guiFrameBase = new btFrame("MainFrame", NULL,
		glm::vec2(0.1f, 0.1f), glm::vec2(0.0f, 0.0f),
		glm::vec4(255, 255, 0, 255));
}

void btGuiBase::load(const std::string guiPath)
{
}

void btGuiBase::clear(void)
{
	if(m_guiFrameBase)
	{
		delete m_guiFrameBase;
		m_guiFrameBase = NULL;
	}

	if (m_guiPointer)
	{
		delete m_guiPointer;
		m_guiPointer = NULL;
	}
}

void btGuiBase::think(void)
{
	for (Uint32 i = 0; i < inputGlobal.getNumMouseInputs(); i++)
	{
		btMouseInput input;
		inputGlobal.getMouseAction(i, input);

		//get only mouse moviment
		if (input.m_key == btMouseInput::MSE_MOTION)
		{
			m_pointerPos = glm::ivec2(input.moveX, input.moveY);
		}
	}

	m_guiPointer->updatePosition(m_pointerPos);
}

void btGuiBase::render(void)
{
	//Enable alpha blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Enable polygon offset
	glEnable(GL_POLYGON_OFFSET_FILL);
	glPolygonOffset(1.0, 1.0);

	//draw gui 
	if (m_guiFrameBase)
		m_guiFrameBase->draw();

	//draw mouse overlay
	if (m_guiPointer)
		m_guiPointer->draw();
}
