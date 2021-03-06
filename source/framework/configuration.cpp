
#include "precompiled.h"
#pragma hdrstop

#include "configuration.h"

btConfiguration configurationGlobal = btConfiguration();

btConfiguration::btConfiguration(void)
{
	m_configIsChanged = false;
	m_vidConf = videoConf_t();
}

btConfiguration::~btConfiguration(void)
{
}

void btConfiguration::loadConfiguration(const std::string gameConfig)
{
	//the xml source document
	//tinyxml2::XMLDocument	m_configDocument;
	m_configDocument = new tinyxml2::XMLDocument;

	btSmartPtr<btFileStream>	configFile(new btFileStream);

	//try open the game config file
	if(!configFile->open(gameConfig, "r"))
	{
		gConsole.error("can't open the configuration file in \"%s\".\n", gameConfig.c_str());
		m_configIsChanged = true;
		//save defalt config
		return;
	}

	//load the src data
	m_configDocument->Parse((char*)configFile->mapStream(), configFile->size());

	const tinyxml2::XMLElement* config = m_configDocument->FirstChildElement("config");
	if (config != NULL)
	{
		const tinyxml2::XMLElement* video = config->FirstChildElement("video");
		if (video != NULL)
			parseVideoConfig(video);
	
		const tinyxml2::XMLElement* audio = config->FirstChildElement("audio");
		//parseVideoConfig(video);

		//const tinyxml2::XMLElement* video = config->FirstChildElement("gameplay");
		//parseVideoConfig(video);
	}

}

void btConfiguration::saveConfiguration(const std::string gameConfig)
{
	//no changes do nothing
	if (!m_configIsChanged)
		return;

	btSmartPtr<btFileStream>	configFile(new btFileStream);
	configFile->open(gameConfig, "w");
}

void btConfiguration::parseVideoConfig(const tinyxml2::XMLElement * vconfig)
{
	//get display configuration
	const tinyxml2::XMLElement * display = vconfig->FirstChildElement("display");
	if (display)
	{
		//get the display
		Sint32 displayNum = 0;
		display->QueryIntText(&displayNum);
		m_vidConf.currDisplay = displayNum;

		//get the video resolution
		display->QueryUnsignedAttribute("width", &m_vidConf.vidWidth);
		display->QueryUnsignedAttribute("height", &m_vidConf.vidHeight);
	}
	else
	{
		m_vidConf.currDisplay = 0;
		m_vidConf.vidWidth = 620;
		m_vidConf.vidHeight = 460;
	}

	const tinyxml2::XMLElement * windowpos = vconfig->FirstChildElement("windowpos");
	if (windowpos)
	{
		windowpos->QueryIntAttribute("posx", &m_vidConf.posX);
		windowpos->QueryIntAttribute("posy", &m_vidConf.posY);
	}
	else
	{
		m_vidConf.posX = -1;
		m_vidConf.posY = -1;
	}

	const tinyxml2::XMLElement * antialiasing = vconfig->FirstChildElement("antialiasing");
	if (antialiasing)
	{
		Uint32	msaa = 0, fxaa = 0;
		antialiasing->QueryUnsignedAttribute("MSAA", &msaa);
		m_vidConf.multisamples = msaa;
		antialiasing->QueryUnsignedAttribute("FXAA", &fxaa);
		m_vidConf.postFxAA = fxaa;
	}
	else
	{
		m_vidConf.multisamples = 8;
		m_vidConf.postFxAA = 0;
	}

	const tinyxml2::XMLElement * videomode = vconfig->FirstChildElement("videomode");
	if (videomode)
	{
		int mode = 1;
		videomode->QueryIntText(&mode);
		m_vidConf.mode = mode;
	}
	else
	{
		m_vidConf.mode = 1;
	}

	const tinyxml2::XMLElement * render = vconfig->FirstChildElement("render");
	if (render)
	{
		render->QueryBoolAttribute("vsync", &m_vidConf.enableVsync);
		render->QueryBoolAttribute("doubleBuffer", &m_vidConf.doubleBuffer);
	}
	else
	{
		m_vidConf.enableVsync = false;
		m_vidConf.doubleBuffer = false;
	}

	const tinyxml2::XMLElement * gamma = vconfig->FirstChildElement("gamma");
	if (gamma)
	{
		float mode = 2.2f;
		videomode->QueryFloatText(&m_vidConf.gamma);
	}
	else
	{
		m_vidConf.gamma = 2.2;
	}
}
