
#include "precompiled.h"
#pragma hdrstop

#include "shaderUniforms.h"

btShaderUniform::btShaderUniform(void)
{
}

btShaderUniform::btShaderUniform(btIntrusivePtr<btShaderProgram> program, const char * uniform)
{
	SDL_assert(program.validate());
	SDL_assert(program->validate());


	m_uniformLocation = glGetUniformLocation(program->m_program, uniform);
}

btShaderUniform::~btShaderUniform(void)
{
}

const GLuint btShaderUniform::getUniforLocation(void) const
{
	return m_uniformLocation;
}

void btShaderUniform::setUniformFloat(const float val)
{
	glUniform1f(m_uniformLocation, val);
}

void btShaderUniform::setUniformInt(const int val)
{
	glUniform1i(m_uniformLocation, val);
}

void btShaderUniform::setUniformUnsInt(const unsigned int val)
{
	glUniform1ui(m_uniformLocation, val);
}

void btShaderUniform::setVec(const glm::vec2 vec)
{
	glUniform2fv(m_uniformLocation, 1, glm::value_ptr(vec));
}

void btShaderUniform::setIvec(const glm::ivec2 vec)
{
	glUniform2iv(m_uniformLocation, 1, glm::value_ptr(vec));
}

void btShaderUniform::setVec(const glm::vec3 vec)
{
	glUniform3fv(m_uniformLocation, 1, glm::value_ptr(vec));
}

void btShaderUniform::setIvec(const glm::ivec3 vec)
{
	glUniform3iv(m_uniformLocation, 1, glm::value_ptr(vec));
}

void btShaderUniform::setVec(const glm::vec4 vec)
{
	glUniform4fv(m_uniformLocation, 1, glm::value_ptr(vec));
}

void btShaderUniform::setIvec(const glm::ivec4 vec)
{
	glUniform4iv(m_uniformLocation, 1, glm::value_ptr(vec));
}

void btShaderUniform::setMatx(const glm::mat2 mat, bool transp)
{
	glUniformMatrix2fv(m_uniformLocation, 1, transp, glm::value_ptr(mat));
}

void btShaderUniform::setMatx(const glm::mat3 mat, bool transp)
{
	glUniformMatrix3fv(m_uniformLocation, 1, transp, glm::value_ptr(mat));
}

void btShaderUniform::setMatx(const glm::mat4 mat, bool transp)
{
	glUniformMatrix4fv(m_uniformLocation, 1, transp, glm::value_ptr(mat));
}
