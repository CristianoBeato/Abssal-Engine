
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
