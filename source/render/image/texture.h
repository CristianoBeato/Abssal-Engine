
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

class btTexture : public btRefObj
{
public:
	btTexture(void);
	btTexture(const GLenum target, const GLenum format);
	~btTexture(void);

	//clear image from memory
	void			clear(void);
	//bind current image to the render, at defined image slot
	void			bind(void);
	//bind a defalt image
	void			bindNull(void);
	//check if is a valid texture
	bool			validate(void);

	//set the texture format
	void			setFormat(const GLenum TextuFormat);
	//set the texture filtering
	void			setFilter(const GLenum Magnification, const GLenum Minification, bool aniso = true);
	//apply to texture the curret filter set
	void			updateFilter(void);
	//set texture reapeating
	void			setWrapping(const GLenum wrap);
	//apply to texture the current wraping set
	void			updateWrapping(void);

	//generate the texture object
	void			generate(GLenum type, GLenum format, GLuint  width, GLuint height, GLuint depth = 0, Uint8 numSamples = 0);

	//update a texture level
	void			updateTextureLevel(Uint32 level, GLenum	dataFormat, void *textureLevelData, 
										Uint32 width, Uint32 height, Uint32 Depth);

	void			updateSubTextureLevel(Uint32 level, GLenum dataFormat, void *textureLevelData, 
										Uint32 width, Uint32 height, Uint32 Depth);


	//
	GLenum			getFormat(void) const;

	//return the open gl texture information
	GLuint			getTextureIdent(void) const;
	//return the texture target format 
	GLenum			getTextureTarget(void) const;

private:
	//texture bind check
	bool			m_isBind;
	//if texture can made use of texture anisotropy
	bool			m_textureUseAnisotropi;
	//OpenGL Texture Identity
	GLuint			m_textureIdent;
	//OpenGL texture Target
	GLenum			m_textureTarget;
	//base image sample size
	GLuint			m_width, m_height, m_depth;
	//internal GL color format
	GLenum			m_internalFormat;
	//pixel color format
	GLenum			m_pixelFormat;
	//pixel store data format
	GLenum			m_dataFormat;
	//texture filtering ops
	GLenum			m_minFilter, m_magFilter;
	//wraping of the texture
	GLenum			m_wrapping;
	//bytes per pixel
	GLuint			m_BPP;
};

#endif // !_TEXTURE_H_
