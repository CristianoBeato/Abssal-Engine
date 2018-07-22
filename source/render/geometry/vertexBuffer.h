
#ifndef _VERTEX_BUFFER_H_
#define _VERTEX_BUFFER_H_

class btShader;

class btVertexAttrib
{
public:
	btVertexAttrib(void);
	btVertexAttrib(GLuint AttribId);
	~btVertexAttrib(void);

	//enable the attrib location
	void	enable(void);

	//disable the attrib location
	void	disable(void);

//	void	getPointer(btShader * shader, std::string attribName);
	void	setPoiner(GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* pointer);

private:
	GLuint	m_attrbLocation;
};

class btVertAttribLock
{
public:
	btVertAttribLock(btVertexAttrib *loc) : m_location(loc)
	{
		m_location->enable();
	}

	~btVertAttribLock(void) 
	{
		if (m_location)
			m_location->disable();
	}

private:
	btVertexAttrib	* m_location;
};

class btVertexBuffer  : public btRefObj
{
public:
	btVertexBuffer(void);
	btVertexBuffer(const GLenum usage);
	~btVertexBuffer(void);

	void			clear(void);
	void			genBuffer(void);
	bool			validate(void);

	void			bind(void);
	void			bindVertexBuffer(void);
	void			bindElementBuffer(void);

	static void		unbind(void);
	static void		unbindVertexBuffer(void);
	static void		unbindElementBuffer(void);

	const GLuint	getVertexArrayId(void) const { return m_vertexArrayId; };
	const GLuint	getVertexBufferId(void) const { return m_vertexBufferId;};
	const GLuint	getElementBufferId(void) const { return m_elementBufferId; };

	void			fillBufferData(const GLvoid * elementsPtr, const GLvoid * vertexPtr);
	void			fillBufferData(const GLsizei elementsBuffSize, const GLvoid * elementsPtr,
									const GLsizei vertexBuffSize, const GLvoid * vertexPtr);

private:
	GLenum	m_bufferUsage;
	GLuint	m_vertexArrayId;
	GLuint	m_vertexBufferId;
	GLuint	m_elementBufferId;
};

class btDrawBuffer : public btRefObj
{
public:
	btDrawBuffer(void);
	btDrawBuffer(const Uint32 numIndices, const Uint32 numIntances = 0, const Uint32 baseIndex = 0, const Uint32 baseVert = 0);
	~btDrawBuffer(void);

	void	clear(void);
	void	draw(GLenum mode = GL_TRIANGLE_FAN);

private:
	GLuint		m_baseVertex;
	GLuint		m_baseIndex;
	GLuint		m_numIndexes;
	GLuint		m_numIntances;
};

#endif // !_VERTEX_BUFFER_H_
