
#include "precompiled.h"
#pragma hdrstop

#include "shaderManager.h"

btShaderManager::btShaderManager(void)
{
}

btShaderManager::~btShaderManager(void)
{
}

void btShaderManager::startUp(void)
{
	//load common shaders
	getShaderProgram("shadersCommon");
}

void btShaderManager::shutDonw(void)
{
	//clear programs
	for (auto shader : m_shaderList)
	{
		shader.second.clear();
	}
	m_shaderList.clear();

	//clear shader
	for (auto program : m_programList)
	{
		program.second.clear();
	}
	m_programList.clear();
}

void btShaderManager::realoadShaders(void)
{
	//TODO:
}

btIntrusivePtr<btShaderProgram> btShaderManager::getShaderProgram(const std::string shaderName)
{
	Uint16 progrmaHash = 0;
	std::hash<std::string>			hashstring;
	btIntrusivePtr<btShaderProgram>	shaderProgram;

	//get the string hash
	progrmaHash = hashstring(shaderName);

	//check if already loaded shader
	shaderProgram = findProgram(progrmaHash);
	if (shaderProgram.validate())
		return shaderProgram;

	//try load shaders
	shaderProgram = loadProgram(shaderName);
	if (shaderProgram.validate())
		return shaderProgram;

	return nullptr;
}

btIntrusivePtr<btShader> btShaderManager::getShader(const std::string shaderName, const Uint32 shType)
{
	Uint16 shaderHash = 0;
	std::hash<std::string>	hashstring;
	btIntrusivePtr<btShader>	shader;

	//get the string hash
	shaderHash = hashstring(shaderName);

	//try get shader if already loaded
	shader = findShader(shaderHash);
	if (shader.validate())
		return shader;

	//load shader
	shader = loadShader(shaderName, shType);
	if (shader.validate())
	{
		m_shaderList[shaderHash] = shader;
		return shader;
	}

	//fail to load
	return nullptr;
}

btIntrusivePtr<btShaderProgram> btShaderManager::findProgram(const Uint16 shaderHash)
{
	std::map<Uint16, btIntrusivePtr<btShaderProgram>>::iterator it;
	it = this->m_programList.find(shaderHash);
	if (it != this->m_programList.end())
		return it->second;
	else
		return nullptr;
}

btIntrusivePtr<btShader> btShaderManager::findShader(const Uint16 shaderHash)
{
	std::map<Uint16, btIntrusivePtr<btShader>>::iterator it;
	it = this->m_shaderList.find(shaderHash);
	if (it != this->m_shaderList.end())
		return it->second;
	else
		return nullptr;
}

btIntrusivePtr<btShaderProgram> btShaderManager::loadProgram(const std::string programControl)
{
	tinyxml2::XMLDocument *shaderControlDoc = nullptr;
	btIntrusivePtr<btShaderProgram>	program = nullptr;
	Uint16 progrmaHash = 0;

	//TODO: try load bynary shader here

	//Open the shader control file
	btFileStream* shaderControlFile = nullptr;
	shaderControlFile = gFileSystem.openFromShaders(programControl + std::string(".xml"));
	if (!shaderControlFile)
	{
		gConsole.printf("FAIL!\n");
		gConsole.error("btShaderManager::loadProgram(%s)unable to open control file %s\n",
			programControl.c_str(),
			shaderControlFile->getFileName().c_str());
		return nullptr;
	}

	//start the XML parser
	shaderControlDoc = new tinyxml2::XMLDocument;

	//parse from the source
	tinyxml2::XMLError err = shaderControlDoc->Parse(
		(char*)shaderControlFile->mapStream(), 
		shaderControlFile->size());

	if (err != tinyxml2::XML_SUCCESS)
	{
		gConsole.printf("FAIL!\n");
		gConsole.error("btShaderManager::loadProgram(%s) error on parse control file\n",
			programControl.c_str());
		return nullptr;
	}

	//get the root
	const tinyxml2::XMLElement* shaderControl = shaderControlDoc->FirstChildElement("shaderControl");
	if (shaderControl)
	{
		const tinyxml2::XMLElement* shaderProgram = shaderControl->FirstChildElement("shaderProgram");
		if (shaderProgram)
		{
			do
			{
				//get the program name
				std::string programName = shaderProgram->Attribute("name");
				std::hash<std::string>	hashstring;
				//store the hash to identifique the program
				progrmaHash = hashstring(programName);

				//create a program handler
				btIntrusivePtr<btShaderProgram>	newProgram = btIntrusivePtr<btShaderProgram>(new btShaderProgram);
				newProgram->generate();

				//get the program shaders
				const tinyxml2::XMLElement* shader = shaderProgram->FirstChildElement("shader");
				if (shader)
				{
					do
					{
						Uint32 shType = 0;
						std::string shaderType = shader->Attribute("type");
						
						//get the name of the shader file

						std::string shaderFile = shader->Attribute("source");
						
						if (StringCompare(shaderType, "vertex"))
						{
							btIntrusivePtr<btShader> vertex = getShader(shaderFile, SHT_VERTEX);
 							newProgram->attachShader(vertex);
						}
						else if (StringCompare(shaderType, "geometry"))
						{
							btIntrusivePtr<btShader> geometry = getShader(shaderFile, SHT_GEOMETRY);
							newProgram->attachShader(geometry);
						}
						else if (StringCompare(shaderType, "pixel"))
						{
							btIntrusivePtr<btShader> fragment = getShader(shaderFile, SHT_PIXEL);
							newProgram->attachShader(fragment);
						}
						else
						{
							gConsole.error("not valid shader set in control\n");
							break;
						}

						//get nex shader in list
						shader = shader->NextSiblingElement();
					}
					while (shader);
				}

				//link the bind stages
				newProgram->link();

				if (newProgram->validate())
				{
					//put program in the render program list
					m_programList[progrmaHash] = newProgram;

					//set to return the last valid render program
					program = newProgram;
				}

				//get the next shader
				shaderProgram = shaderProgram->NextSiblingElement();
			} while (shaderProgram);
		}
	}
#if 1
	delete shaderControlDoc;
#endif

	return 	program;
}

btIntrusivePtr<btShader> btShaderManager::loadShader(const std::string shaderName, const  Uint32 shType)
{
	bool	compiled = false;
	GLenum	shaderType = 0xFFFFFF;
	//btSmartPtr<btFileStream>	sahderSRC = btSmartPtr<btFileStream>(nullptr);
	btIntrusivePtr<btShader>	newShader = btIntrusivePtr<btShader>(nullptr);
	btFileStream* sahderSRC = nullptr;

	gConsole.printf("trying load shader %s - ", shaderName.c_str());

	if (shType == SHT_VERTEX)
	{
		shaderType = GL_VERTEX_SHADER;
		gConsole.printf("VERTEX SHADER\n");
	}
	else if (shType == SHT_GEOMETRY)
	{
		shaderType = GL_GEOMETRY_SHADER;
		gConsole.printf("GEOMETRY SHADER\n");
	}
	else if (shType == SHT_PIXEL)
	{
		shaderType = GL_FRAGMENT_SHADER;
		gConsole.printf("PIXEL SHADER\n");
	}

	sahderSRC = gFileSystem.openFromShaders(shaderName);
	//if (!sahderSRC.validade())
	if(!sahderSRC)
	{
		gConsole.printf("FAIL!\n");
		return nullptr;
	}

	//create a shader
	newShader = btIntrusivePtr<btShader>(new btShader);
	newShader->generate(shaderType);

	//compile shader from source
	newShader->compile((GLchar*)sahderSRC->mapStream());

	//free the source
	delete sahderSRC;

	//check if shader is compiled
	if (!newShader->validate())
	{
		//m_shaderList.erase(hash);
		newShader.~btIntrusivePtr();
		gConsole.printf("FAIL!\n");
		return nullptr;
	}

	gConsole.printf("OK!\n");
	return newShader;
}
