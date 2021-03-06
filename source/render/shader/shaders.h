
#ifndef _SHADERS_SHADER_H_
#define _SHADERS_SHADER_H_

class btShader : public btRefObj
{
public:
	btShader(void);
	~btShader(void);
	void clear(void);
	void generate(GLenum shaderType);
	bool validate(void);
	void compile(const GLchar *shaderSRC);

private:
	friend class btShaderProgram;
	void checkShader(void);

	GLenum	m_Type;
	GLuint	m_shader;
};

class btShaderProgram : public btRefObj
{
public:
	btShaderProgram(void);
	~btShaderProgram(void);

	void clear(void);
	void generate(void);
	bool validate(void);
	void link(void);
	void attachShader(const btIntrusivePtr<btShader> shader);
	const GLuint getProgramId(void) const { return m_program; };
	void bind(void);
	void unbind(void);

private:
	friend class btShaderUniform;

	void checkProgram(void);

	GLuint					m_program;
};

#endif // !_SHADERS_SHADER_H_
