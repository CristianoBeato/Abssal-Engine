
#ifndef _FONT_MANAGER_H_
#define _FONT_MANAGER_H_

#include "font.h"

class btFontManager
{
public:
	btFontManager(void);
	~btFontManager(void);

	//free all the fonts 
	void		clear(void);
	
	void		removeFont(const std::string fontname);
	void		removeFont(const btFont* fontdata);
	
	//load the fonr (need to be in the fonts folder) if not can, load the defalt font
	btFont*		loadFont(const std::string fontName);
	

private:
	std::map<std::string, btFont*>	m_fontMap;
};

#endif //!_FONT_MANAGER_H_