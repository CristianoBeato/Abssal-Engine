
#include "precompiled.h"
#pragma hdrstop

#include "rs_renderSystem.h"

btRenderSystem gRendererGlobal = btRenderSystem();

btRenderSystem::btRenderSystem(void)
{
	m_currentTextureId = 0;
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
	//set the defalt render 
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	if (m_multisample)
		glEnable(GL_MULTISAMPLE);
	else
		glDisable(GL_MULTISAMPLE);

	//preload shaders
	m_shaderManager->startUp();

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
	//clear the render list
	m_Surfaces.clear();

	//glDrawBuffer(GL_BACK);
	glFlush();
}

void btRenderSystem::setupViewPort(const Uint32 width, const Uint32 height)
{
	m_viewWidth = width;
	m_viewHeight = height;
#if 0
	int left = (m_viewWidth / 2) *-1;
	int top = (m_viewHeight / 2) *-1;
#else
	int left = 0;
	int top = 0;
#endif
	//setup the view port
	glViewport(left, top, m_viewWidth, m_viewHeight);

	m_projectionMatrix = glm::ortho((float)left, (float)m_viewWidth, (float)top, (float)m_viewHeight, 0.1f, 100.0f);
}

void btRenderSystem::setupView(float x, float y, float z)
{
	glm::vec3 viewPos, lookPos;

	viewPos = glm::vec3(x, y, z);
	//
	lookPos = glm::vec3(x, y, z - 1);
	m_viewMatrix = glm::lookAt(viewPos, lookPos, glm::vec3(0.0f, 1.0f, 0.0f));
}

void btRenderSystem::renderBackend(void)
{
	btIntrusivePtr<btShaderProgram> program;

	//render all the surfaces
	for (btIntrusivePtr<btRenderSuface> suface : m_Surfaces)
	{
		Uint32 numTextures = 0;
		
		//the mode of the surface cull
		setupCulling(suface->getCullingMode());

		//
		setupCulling(suface->getCullingMode());

		//selec the shader 
		if (suface->getTextures().size() > 0)
			program = m_shaderManager->getShaderProgram("spritesTextured");
		else
			program = m_shaderManager->getShaderProgram("spriteFrame");

		//todo, bind render program here
		program->bind();

		//setup shader uniforms
		btShaderUniform modelMatrix = btShaderUniform(program, "uModel");
		btShaderUniform viewProj = btShaderUniform(program, "uViewProjection");
		btShaderUniform	modelColor = btShaderUniform(program, "uColorModel");
		btShaderUniform textureMatrix = btShaderUniform(program, "uTextureMatrix");

		//set the model render matrix
		modelMatrix.setMatx(suface->getModelMatrix());

		//set the 
		viewProj.setMatx(getViewProjectionMatrix());

		//set the surface rendering color
		modelColor.setVec(suface->getModelColor());

		//if use textures set surface
		if (suface->getTextures().size() > 0)
			textureMatrix.setMatx(suface->getTextureMatrix());

		//bind textures units
		for (btIntrusivePtr<btTexture> texture: suface->getTextures())
		{
			//apply texture at current id
			selectTextureNoClient(numTextures);
			texture->bind();
			numTextures++;
		}

#if 0
		glBegin(GL_QUADS);
		glVertex3f(-1.0f, -1.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f);

		glVertex3f(1.0f, -1.0f, 0.0f);
		glTexCoord2f(1.0f, 0.0f);

		glVertex3f(1.0f, 1.0f, 0.0f);
		glTexCoord2f(1.0f, 1.0f);

		glVertex3f(-1.0f, 1.0f, 0.0f);
		glTexCoord2f(0.0f, 1.0f);
		glEnd();
#endif

		//the mesh draw call 
		suface->Draw();

		//clear textures stages
		for (btIntrusivePtr<btTexture> texture : suface->getTextures())
		{
			//apply texture at current id
			selectTextureNoClient(numTextures);
			texture->bindNull();
			numTextures--;
		}
	}

	//clear render programs
	program->unbind();
}

void btRenderSystem::appendRenderSurface(btIntrusivePtr<btRenderSuface> surface)
{
	m_Surfaces.push_back(surface);
}

void btRenderSystem::renderLine(float xa, float ya, float xb, float yb, btColorApha color, const Uint32 flags)
{
}

void btRenderSystem::renderRectColor(float x, float y, float w, float h, btColorApha color, const Uint32 flags)
{
//
}

void btRenderSystem::renderRectTexture(float x, float y, float w, float h, btColorApha color, const Uint32 flags)
{
}

void btRenderSystem::renderRectColorTexture(float x, float y, float w, float h, btColorApha color, const Uint32 flags)
{
}

glm::mat4 btRenderSystem::getViewProjectionMatrix(void)
{
	return m_projectionMatrix * m_viewMatrix;
}

void btRenderSystem::selectTextureNoClient(Uint32 unit)
{
	m_currentTextureId = unit;
	glActiveTexture(GL_TEXTURE0 + unit);
}

void btRenderSystem::setupCulling(const Uint32 mode)
{
	//don't need changes
	if (mode == m_cullMode)
		return;

	if (mode == K_CULL_NONE)
		glDisable(GL_CULL_FACE);
	else
	{
		if (m_cullMode == K_CULL_NONE)
			glEnable(GL_CULL_FACE);

		if (m_cullMode == K_CULL_BACK)
			glCullFace(GL_BACK);
		else if(m_cullMode == K_CULL_FRON)
			glCullFace(GL_FRONT);

		//don't need 
		glFrontFace(GL_CCW);
	}

	m_cullMode = mode;
}

void btRenderSystem::setupScissor(const Uint32 mode, const glm::vec2 pos, const glm::vec2 size)
{
}

void btRenderSystem::setupBlending(const Uint32 mode)
{
	//don't need changes
	if (mode == m_blendMode)
		return;

	if (mode == K_BLEND_NONE)
		glDisable(GL_CULL_FACE);
	else
	{
		if (m_cullMode == K_BLEND_NONE)
			glEnable(GL_BLEND);

		GLenum srcFactor, dstFactor;

		glBlendFunc(srcFactor, dstFactor);

	}

	m_blendMode = mode;
}
