
#ifndef _TEXT_H_
#define _TEXT_H_

#include "font.h"

class btRenderText : public btTexture
{
public:
	btRenderText(void);
	btRenderText(btFont* textFont, const std::string text);
	~btRenderText(void);
	
	//render the font to a image;
	void				render(void);
	
	//update the text and render image
	void				updateText(const std::string text);
	//get the text
	const std::string	getText(void) const;
	//set the maximun bounds of the text
	void				setTextBounds(Uint32 width, Uint32 height);
	//set the 
	void				getTextBounds(Uint32 &width, Uint32 &height);
	//get the text color
	SDL_Color			getTextColor(void) const;
	//get the text bacground color
	SDL_Color			getTextBackGroundColor(void) const;

private:

	//the text
	std::string		m_text;
	//the font for rendering
	btFont*			m_font;

	//font Color
	glm::u8vec4		m_fontColor;

	//Font Background Color
	glm::u8vec4		m_fontBackground;
};

#endif //!_TEXT_H_