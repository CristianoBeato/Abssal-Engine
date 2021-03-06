
#ifndef _SHADER_UNIFORMS_H_
#define _SHADER_UNIFORMS_H_

class btShaderProgram;

class btShaderUniform : public btRefObj
{
public:
	btShaderUniform(void);
	btShaderUniform(btIntrusivePtr<btShaderProgram> program, const char * uniform);
	~btShaderUniform(void);

	const GLuint	getUniforLocation(void) const;
	
	//set float uniform data
	void	setUniformFloat(const float val);
	void	setUniformInt(const int val);
	void	setUniformUnsInt(const unsigned int val);

	//setup the vectors
	void	setVec(const glm::vec2 vec);
	void	setIvec(const glm::ivec2 vec);

	void	setVec(const glm::vec3 vec);
	void	setIvec(const glm::ivec3 vec);

	void	setVec(const glm::vec4 vec);
	void	setIvec(const glm::ivec4 vec);

	//setup matrixes
	void	setMatx(const glm::mat2 mat, bool transp = false);
	void	setMatx(const glm::mat3 mat, bool transp = false);
	void	setMatx(const glm::mat4 mat, bool transp = false);

private:
	//get the uniform index
	GLuint			m_uniformLocation;
};

#endif // !_SHADER_UNIFORMS_H_
