
#include "precompiled.h"
#pragma hdrstop

#include "rs_renderSystem.h"

btRenderSystem rendererGlobal = btRenderSystem();

btRenderSystem::btRenderSystem(void)
{
	m_multisample = false;
	m_shaderManager = new btShaderManager;
	m_textureManager = new btTextureManager;
	m_fontManager = new btFontManager;
}

btRenderSystem::~btRenderSystem(void)
{
	delete m_fontManager;
	delete m_textureManager;
	delete m_shaderManager;
}

void btRenderSystem::startUp(void)
{
	//setup the view port
	glViewport(0, 0, 800, 600);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	if (m_multisample)
		glEnable(GL_MULTISAMPLE);
	else
		glDisable(GL_MULTISAMPLE);

	//preload shaders
	m_shaderManager->startUp();
	//m_shaderManager->getProgramInLib("gspass");
	//m_shaderManager->getProgramInLib("lightpass");

	//set the texture load thread, and préload textures
	m_textureManager->startUp();

	//load the defalt font
	m_fontManager->loadFont("SourceCodePro");
}

void btRenderSystem::shutDonw(void)
{
	m_fontManager->clear();
	m_textureManager->shutDonw();
	m_shaderManager->shutDonw();
}

void btRenderSystem::beginFrame(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void btRenderSystem::endFrame(void)
{
	//glDrawBuffer(GL_BACK);
	glFlush();
}
