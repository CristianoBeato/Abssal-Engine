
#include "precompiled.h"
#pragma hdrstop

#include "shaders.h"

btShader::btShader(void) : btRefObj(), m_shader(INVALID_OBJECT_ID)
{
	m_Type = GL_NONE;
}

btShader::~btShader(void)
{
	clear();
}

void btShader::clear(void)
{
	if (m_shader != 0)
	{
		//	glDete
		glDeleteShader(m_shader);
		//btVerifyGL();

		m_shader = INVALID_OBJECT_ID;
	}

	//keep type
	//m_Type = GL_NONE;
}

void btShader::generate(GLenum shaderType)
{
	m_Type = shaderType;
	SDL_assert(	m_Type == GL_VERTEX_SHADER ||
				m_Type == GL_TESS_CONTROL_SHADER ||
				m_Type == GL_TESS_EVALUATION_SHADER ||
				m_Type == GL_GEOMETRY_SHADER ||
				m_Type == GL_FRAGMENT_SHADER);


	//clear previus shader before gen a new
	if (m_shader != 0)
		clear();

	m_shader = glCreateShader(m_Type);
	//btVerifyGL();
}

bool btShader::validate(void)
{
	if (m_shader != INVALID_OBJECT_ID)
	{
		if (glIsShader(m_shader) == GL_TRUE)
			return true;

		checkShader();
	}

	return false;
}

void btShader::compile(const GLchar * shaderSRC)
{
	GLint success;

	//check shader is generated
	if (m_shader == INVALID_OBJECT_ID)
		return;

	glShaderSource(m_shader, 1, &shaderSRC, GL_NONE);
	glCompileShader(m_shader);
	//btVerifyGL();

	// Print compile errors if any
	glGetShaderiv(m_shader, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE)
	{
		checkShader();

		clear(); //don't leak the shader
	}
}

void btShader::checkShader(void)
{
	std::string shtype = std::string();
	GLint logSize = 0;
	GLchar *Log = nullptr;
	
	glGetShaderiv(m_shader, GL_INFO_LOG_LENGTH, &logSize);
	Log = (GLchar*)SDL_malloc(logSize);

	glGetShaderInfoLog(m_shader, logSize, GL_NONE, Log);

	switch (m_Type)
	{
	case GL_VERTEX_SHADER:
		shtype = "VERTEX";
		break;
	case GL_TESS_CONTROL_SHADER:
		shtype = "TESS_CONTROL";
		break;
	case GL_TESS_EVALUATION_SHADER:
		shtype = "TESS_EVALUATION";
		break;
	case GL_GEOMETRY_SHADER:
		shtype = "GEOMETRY";
		break;
	case GL_FRAGMENT_SHADER:
		shtype = "FRAGMENT";
		break;
	default:
		shtype = "UKNOW";
		break;
	}

	gConsole.error("SHADER::%s::COMPILATION_FAILED:\n%s:\n", shtype.c_str(), Log);
	SDL_free(Log);
}

btShaderProgram::btShaderProgram(void) : m_program(INVALID_OBJECT_ID)
{
}

btShaderProgram::~btShaderProgram(void)
{
	clear();
}

void btShaderProgram::clear(void)
{
	if (m_program != INVALID_OBJECT_ID)
	{
		glDeleteProgram(m_program);
		m_program = INVALID_OBJECT_ID;
	}
}

void btShaderProgram::generate(void)
{
	if (m_program != INVALID_OBJECT_ID)
		clear();

	//gen the prog name
	m_program = glCreateProgram();
}

bool btShaderProgram::validate(void)
{
	if (m_program != INVALID_OBJECT_ID)
	{
		if (glIsProgram(m_program) == GL_TRUE)
			return true;
	}

	return false;
}

void btShaderProgram::link(void)
{
	GLint success;

	//to generate the program binaryfmt
	glProgramParameteri(m_program, GL_PROGRAM_BINARY_RETRIEVABLE_HINT, GL_TRUE);

	//is a shader separable program
	glProgramParameteri(m_program, GL_PROGRAM_SEPARABLE, GL_TRUE);

	glLinkProgram(m_program);
	//btVerifyGL();

	glGetProgramiv(m_program, GL_LINK_STATUS, &success);
	if (success == GL_FALSE)
	{
		checkProgram();

		clear(); //don't leak the program
	}
}

void btShaderProgram::attachShader(const btIntrusivePtr<btShader> shader)
{
	if (!shader.validate())
	{
		gConsole.error("try attach a invalid shader\n");
		return;
	}

	glAttachShader(m_program, shader->m_shader);
	//btVerifyGL();
}

void btShaderProgram::bind(void)
{
	glUseProgram(m_program);
}

void btShaderProgram::unbind(void)
{
	glUseProgram(0);
}

void btShaderProgram::checkProgram(void)
{
	GLint logSize = 0;

	glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &logSize);

	GLchar *infoLog = new GLchar[logSize];
	glGetProgramInfoLog(m_program, logSize, GL_NONE, infoLog);
	std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	delete infoLog;
}
