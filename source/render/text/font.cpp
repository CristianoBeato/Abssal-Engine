
#include "precompiled.h"
#pragma hdrstop

#include "font.h"
#include "text.h"

/*
====================
====================
*/
btFont::btFont(void)
{
	m_loaded = false;
}

btFont::~btFont(void)
{
	clear();
}

btSDLFont::btSDLFont(void) : btFont(), m_fontSrc(NULL)
{
}

btSDLFont::~btSDLFont(void)
{
}

bool btSDLFont::load(const std::string fontFile)
{
	return false;
}

void btSDLFont::clear(void)
{
	if(	m_fontSrc != NULL)
	{
		TTF_CloseFont(m_fontSrc);
		m_fontSrc = false;
	}
	
	m_loaded = false;
}

void btSDLFont::renderTextToImage(btIntrusivePtr<btRenderText> text, Uint8 Quality)
{
	btIntrusivePtr<SDL_Surface>	textSurface;

	//if not loaded don't do anithing 
	if(m_loaded)
		return;
	
	//check if font is really loaded
	SDL_assert(m_fontSrc);
	
	//set the text style
	TTF_SetFontStyle(m_fontSrc, TTF_STYLE_BOLD | TTF_STYLE_UNDERLINE);
	
	TTF_SetFontKerning(m_fontSrc, 1);
	if (Quality == 0)
		textSurface = TTF_RenderText_Solid(m_fontSrc, text->getText().c_str(), text->getTextColor());
	else if (Quality == 1)
		textSurface =  TTF_RenderText_Shaded(m_fontSrc, text->getText().c_str(), text->getTextBackGroundColor(), text->getTextBackGroundColor());
	else if (Quality == 2)
		textSurface = TTF_RenderText_Blended(m_fontSrc, text->getText().c_str(), text->getTextBackGroundColor());

	text->updateTextureLevel(0, GL_UNSIGNED_BYTE, textSurface->pixels, textSurface->w, textSurface->h, 0);
}