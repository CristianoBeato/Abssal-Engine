
#ifndef _ENGINE_CONFIGURATION_H_
#define _ENGINE_CONFIGURATION_H_

#include "dictionary.h"

#include "tinyxml2.h"
class btConfiguration
{
public:
	btConfiguration(void);
	~btConfiguration(void);

	typedef struct videoConf_s
	{
		bool	enableVsync, doubleBuffer;
		Uint8	mode;			// 0 fullscreen, 1 window, 2 window borderless
		Uint8	currDisplay;
		Uint8	multisamples, postFxAA;
		Sint32	posX, posY;
		Uint32	vidWidth, vidHeight;
		float	gamma;
	}videoConf_t;

	void			loadConfiguration(const std::string gameConfig);
	void			saveConfiguration(const std::string gameConfig);
	videoConf_t		getVideoConfig(void) const { return m_vidConf; };
	void			setVideoConfig(const videoConf_t conf) { m_vidConf = conf; m_configIsChanged = true; };

private:
	void	parseVideoConfig(const tinyxml2::XMLElement* vconfig);

	//store the video configuration
	videoConf_t			m_vidConf;
	//check for changes in game configuration
	bool				m_configIsChanged;

	tinyxml2::XMLDocument	*m_configDocument;
};

extern btConfiguration configurationGlobal;

#endif // !_ENGINE_CONFIGURATION_H_
