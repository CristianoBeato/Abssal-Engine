
#include "precompiled.h"
#pragma hdrstop

#include "text.h"

btRenderText::btRenderText(void) : btTexture(GL_TEXTURE_2D, GL_RGBA8)
{
	m_font = NULL;
}

btRenderText::btRenderText(btFont* textFont, const std::string text) : m_font(textFont), m_text(text)
{
}

btRenderText::~btRenderText(void)
{
}

void btRenderText::render(void)
{
	m_font->renderTextToImage(this, 0);
}

void btRenderText::updateText(const std::string text)
{
	m_text = text;
	
	if (!validate())
		generate(GL_TEXTURE_2D, GL_RGBA8, 1024, 1024, 0); 	//gen the image

	//update text image 
	render();
}

const std::string btRenderText::getText(void) const
{
	return m_text;
}

SDL_Color btRenderText::getTextColor(void) const
{
	return SDL_Color{ m_fontColor.r, m_fontColor.g, m_fontColor.b, m_fontColor.a };
}

SDL_Color btRenderText::getTextBackGroundColor(void) const
{
	return SDL_Color{ m_fontColor.r, m_fontColor.g, m_fontColor.b, m_fontColor.a };
}
