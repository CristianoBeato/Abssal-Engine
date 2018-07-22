
#include "precompiled.h"
#pragma hdrstop

#include "rs_renderSurface.h"


btRenderSuface::btRenderSuface(void) :
	btRefObj(),
	m_modelMatrix(1.0),
	m_surfaceVbuffer(nullptr),
	m_surfaceMesh(nullptr)
{
}

btRenderSuface::btRenderSuface(const btIntrusivePtr<btVertexBuffer> vertBuff, 
	const btIntrusivePtr<btDrawBuffer> mesh) :
	btRefObj(),
	m_modelMatrix(1.0),
	m_surfaceVbuffer(vertBuff),
	m_surfaceMesh(mesh)
{
}

btRenderSuface::~btRenderSuface(void)
{
	clear();
}

void btRenderSuface::clear(void)
{
	//set at center pos
	m_modelMatrix = glm::mat4(1.0);
}

void btRenderSuface::appendTexture(btIntrusivePtr<btTexture> texRef)
{
	m_renderTextures.push_back(texRef);
}

void btRenderSuface::setPosition(const float x, const float y, const float z)
{
	setPosition(glm::vec3(x, y, z));
}

void btRenderSuface::setPosition(const glm::vec3 pos)
{
	m_modelMatrix = glm::translate(m_modelMatrix, pos);
}

void btRenderSuface::setOrientation(const float x, const float y, const float z, const float w)
{
	setOrientation(glm::quat(w,x,y,z));
}

void btRenderSuface::setOrientation(const glm::quat rot)
{
	m_modelMatrix = glm::rotate(m_modelMatrix, rot.w, glm::vec3(rot.x, rot.y, rot.z));
}

void btRenderSuface::setSize(const float x, const float y, const float z)
{
	setSize(glm::vec3(x, y, z));
}

void btRenderSuface::setSize(const glm::vec3 size)
{
	m_modelMatrix = glm::scale(m_modelMatrix, size);
}

void btRenderSuface::setColor(const Uint32 r, const Uint32 g, const Uint32 b, const Uint32 a)
{
	setColor(btColorApha(r, g, b, a));
}

void btRenderSuface::setColor(const btColorApha color)
{
	m_surfaceRenderColor = color;
}

void btRenderSuface::setCulling(const Uint32 flag)
{
	m_cullMode = flag;
}

void btRenderSuface::setBlending(const Uint32 flag)
{
	m_blendMode = flag;
}

const std::vector<btIntrusivePtr<btTexture>> btRenderSuface::getTextures(void) const
{
	return m_renderTextures;
}

const Uint32 btRenderSuface::getNumTextures(void) const
{
	return m_renderTextures.size();
}

const Uint32 btRenderSuface::getBlendMode(void) const
{
	return m_blendMode;
}

const glm::mat4 btRenderSuface::getModelMatrix(void) const
{
	return m_modelMatrix;
}

const glm::mat4 btRenderSuface::getTextureMatrix(void) const
{
	return m_textureMatrix;
}

const btColorApha btRenderSuface::getModelColor(void) const
{
	return m_surfaceRenderColor;
}

const Uint32 btRenderSuface::getCullingMode(void) const
{
	return m_cullMode;
}

void btRenderSuface::Draw(void)
{
	m_surfaceVbuffer->bind();
	m_surfaceVbuffer->bindVertexBuffer();
	btVertexAttrib vpos(0);
	btVertexAttrib vtcd(1);


	vpos.enable();
	vpos.setPoiner(3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	vtcd.enable();
	vtcd.setPoiner(2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));

	//draw the mesh
	m_surfaceMesh->draw(GL_TRIANGLE_FAN);

	vtcd.disable();
	vpos.enable();
	m_surfaceVbuffer->unbindVertexBuffer();
	m_surfaceVbuffer->unbind();
}
