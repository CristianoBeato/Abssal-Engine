
#ifndef _IMAGE_LOADER_H_
#define _IMAGE_LOADER_H_

class btTexture;

class btImageLoader
{
	enum imageDepth
	{
		ID_8BW,		//8bpp
		ID_8RGB,	//24bpp
		ID_16RGB,	//48bpp
		ID_16RGBF,	//HDR 48f bpp
		ID_32RGBF,	//HDR 128 f bpp
	};
public:
	btImageLoader(void);
	~btImageLoader(void);

	//Load Image
	virtual bool	loadFromFile(const std::string file) = 0;
	//save image
	virtual bool	saveToFile(const std::string file) = 0;

	bool	loadFromSDLSurface(const btIntrusivePtr<SDL_Surface> src);

	//convert to SDL Surface
	btIntrusivePtr<SDL_Surface> getSDLSurface(void);
	
	//Get image information
	imageDepth					getDepth(void) const;
	void						getSize(Uint32 &width, Uint32 &height, Uint32 &depth);

private:

	Uint32 m_width, m_height, m_depth;
	imageDepth	m_colorDepth;
};

#endif // !_IMAGE_LOADER_H_
