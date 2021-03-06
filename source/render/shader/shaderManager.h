
#ifndef _SHADER_MANAGER_H_
#define _SHADER_MANAGER_H_

#include "shaders.h"
#include "shaderUniforms.h"

class btShaderManager
{
	enum shaderType
	{
		SHT_VERTEX = 0,		//vertex shader
		SHT_GEOMETRY,		//geometry shader
		SHT_PIXEL			//pixel (fragment) shader
	};
public:
	btShaderManager(void);
	~btShaderManager(void);

	void		startUp(void);
	void		shutDonw(void);

	void		realoadShaders(void);

	btIntrusivePtr<btShaderProgram>	getShaderProgram(const std::string shaderName);

private:
	btIntrusivePtr<btShader>		getShader(const std::string shaderName, const Uint32 shType);
	btIntrusivePtr<btShaderProgram>	findProgram(const Uint16 shaderHash);
	btIntrusivePtr<btShader>		findShader(const Uint16 shaderHash);
	btIntrusivePtr<btShaderProgram>	loadProgram(const std::string shaderName);
	btIntrusivePtr<btShader>		loadShader(const std::string shaderName,const  Uint32 shType);

	std::map<Uint16, btIntrusivePtr<btShader>>	m_shaderList;
	std::map<Uint16, btIntrusivePtr<btShaderProgram>>	m_programList;
};


#endif // !_SHADER_MANAGER_H_
