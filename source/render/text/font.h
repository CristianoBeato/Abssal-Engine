
#ifndef _FONT_H_
#define _FONT_H_

class btRenderText;

//abstract font loader
class btFont : public btRefObj
{
public:
	enum fontHintting
	{
		FTQ_LOW = 0x00,
		FTQ_MEDIUM,
		FTQ_HIGH
	};

	enum fontStyle
	{
		FTS_BOLD = 0x00,
		FTS_ITALIC,
		FTS_UNDERLINE,
		FTS_STRIKETHROUGH,
		FTS_NORMAL
	};
	
	btFont(void);
	virtual ~btFont(void);

	//load the font 
	virtual bool	load(const std::string fontFile) = 0;
	
	//free the current font
	virtual void	clear(void){};
	
	//check if font are loaded
	bool	loaded(void) {return m_loaded; };

	//render the imagem text
	virtual void	renderTextToImage(btIntrusivePtr<btRenderText> text, Uint8 Quality = 1) = 0;
	
protected:
	bool	m_loaded;
};

class btImageFont :  public btFont
{
public:
	btImageFont(void);
	~btImageFont(void);
};

//
class btSDLFont : public btFont
{
public:
	btSDLFont(void);
	~btSDLFont(void);
	
	//load the font 
	virtual bool	load(const std::string fontFile);
	virtual void	clear(void);	

	virtual void	renderTextToImage(btIntrusivePtr<btRenderText> text, Uint8 Quality = 1);
private:
	Uint32	convertStyles(Uint32	styles);

	TTF_Font*	m_fontSrc;	
};

#endif //!_FONT_H_