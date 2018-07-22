
#include "precompiled.h"
#pragma hdrstop

#include "vertexBuffer.h"


btVertexAttrib::btVertexAttrib(void) : m_attrbLocation(0)
{
}

btVertexAttrib::btVertexAttrib(GLuint AttribId) : m_attrbLocation(AttribId)
{
}

btVertexAttrib::~btVertexAttrib(void)
{
	disable();
}

void btVertexAttrib::enable(void)
{
	glEnableVertexAttribArray(m_attrbLocation);
}

void btVertexAttrib::disable(void)
{
	glDisableVertexAttribArray(m_attrbLocation);
}

void btVertexAttrib::setPoiner(GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid * pointer)
{
	glVertexAttribPointer(m_attrbLocation, size, type, normalized, stride, pointer);
}

/*
=========================================

=========================================
*/

btVertexBuffer::btVertexBuffer(void): m_bufferUsage(GL_STATIC_DRAW),
	m_vertexArrayId(INVALID_OBJECT_ID),
	m_vertexBufferId(INVALID_OBJECT_ID),
	m_elementBufferId(INVALID_OBJECT_ID)
{
}

btVertexBuffer::btVertexBuffer(const GLenum usage): m_bufferUsage(usage),
	m_vertexArrayId(INVALID_OBJECT_ID),
	m_vertexBufferId(INVALID_OBJECT_ID),
	m_elementBufferId(INVALID_OBJECT_ID)
{
}

btVertexBuffer::~btVertexBuffer(void)
{
	clear();
}

void btVertexBuffer::clear(void)
{
	if (m_elementBufferId != INVALID_OBJECT_ID)
	{
		glDeleteBuffers(1, &m_elementBufferId);
		m_elementBufferId = INVALID_OBJECT_ID;
	}

	if (m_vertexBufferId != INVALID_OBJECT_ID)
	{
		glDeleteBuffers(1, &m_vertexBufferId);
		m_vertexBufferId = INVALID_OBJECT_ID;
	}

	if (m_vertexArrayId != INVALID_OBJECT_ID)
	{
		glDeleteVertexArrays(1, &m_vertexArrayId);
		m_vertexArrayId = INVALID_OBJECT_ID;
	}
}

void btVertexBuffer::genBuffer(void)
{
	if (m_vertexArrayId != INVALID_OBJECT_ID)
		clear();

	glGenVertexArrays(1, &m_vertexArrayId);
	glGenBuffers(1, &m_vertexBufferId);
	glGenBuffers(1, &m_elementBufferId);
}

bool btVertexBuffer::validate(void)
{
	if (m_vertexArrayId != INVALID_OBJECT_ID)
	{
		if (glIsVertexArray(m_vertexArrayId) == GL_TRUE)
			return true;
	}
	return false;
}

void btVertexBuffer::bind(void)
{
	if (m_vertexArrayId == 0)
		return;

	glBindVertexArray(m_vertexArrayId);
}

void btVertexBuffer::bindVertexBuffer(void)
{
	if (m_vertexBufferId == 0)
		return;

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);
}

void btVertexBuffer::bindElementBuffer(void)
{
	if (m_elementBufferId == 0)
		return;

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBufferId);
}

void btVertexBuffer::unbind(void)
{
	glBindVertexArray(0);
}

void btVertexBuffer::unbindVertexBuffer(void)
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void btVertexBuffer::unbindElementBuffer(void)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void btVertexBuffer::fillBufferData(const GLvoid * elementsPtr, const GLvoid * vertexPtr)
{
	fillBufferData(sizeof(elementsPtr), elementsPtr, sizeof(vertexPtr), vertexPtr);
}

void btVertexBuffer::fillBufferData(const GLsizei elementsBuffSize, const GLvoid * elementsPtr, const GLsizei vertexBuffSize, const GLvoid * vertexPtr)
{
	//bind vertex array
	bind();
	bindVertexBuffer();
	glBufferData(GL_ARRAY_BUFFER, vertexBuffSize, vertexPtr, m_bufferUsage);
//	btVerifyGL();

	bindElementBuffer();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, elementsBuffSize, elementsPtr, m_bufferUsage);
//	btVerifyGL();

	//free vertex array
	unbind();
}

btDrawBuffer::btDrawBuffer(void) :
	m_numIndexes(0),
	m_numIntances(0),
	m_baseIndex(0),
	m_baseVertex(0)
{
}

btDrawBuffer::btDrawBuffer(	const Uint32 numIndices, 
							const Uint32 numIntances,
							const Uint32 baseIndex, 
							const Uint32 baseVert):
	m_numIndexes(numIndices),
	m_numIntances(numIntances),
	m_baseIndex(baseIndex),
	m_baseVertex(baseVert)
{
}

btDrawBuffer::~btDrawBuffer(void)
{
	clear();
}

void btDrawBuffer::clear(void)
{
}

void btDrawBuffer::draw(GLenum mode)
{
	if (m_baseIndex > 0)
	{
		if (m_numIntances > 1)
			glDrawElementsInstanced(mode, m_numIndexes, GL_UNSIGNED_INT, 0, m_numIntances);
		else
			glDrawElements(mode, m_numIndexes, GL_UNSIGNED_INT, 0);
	}
	else
	{
		if (m_numIntances > 1)
			glDrawElementsInstancedBaseVertex(mode, m_numIndexes, GL_UNSIGNED_INT,
			(void*)(sizeof(Uint32) * m_baseIndex), m_numIntances, m_baseVertex);
		else
			glDrawElementsBaseVertex(mode,m_numIndexes, GL_UNSIGNED_INT,
			(void*)(sizeof(Uint32) * m_baseIndex), m_baseVertex);
	}
}
