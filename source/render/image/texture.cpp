
#include  "precompiled.h"
#pragma hdrstop

#include "texture.h"

btTexture::btTexture(void) :
	m_textureIdent(INVALID_OBJECT_ID),
	m_textureTarget(GL_NONE),
	m_internalFormat(GL_NONE)
{
	m_isBind = false;
	m_textureUseAnisotropi = false;
	m_width = 0;
	m_height = 0;
	m_depth = 0;
	m_BPP = 0;
	m_minFilter = GL_NEAREST;
	m_magFilter = GL_NEAREST;
	m_wrapping = GL_CLAMP_TO_BORDER;
}

btTexture::btTexture(const GLenum target, const GLenum format) : 
	m_textureIdent(INVALID_OBJECT_ID),
	m_textureTarget(target),
	m_internalFormat(format)
{
	m_isBind = false;
	m_textureUseAnisotropi = false;
	m_width = 0;
	m_height = 0;
	m_depth = 0;
	m_BPP = 0;
	m_minFilter = GL_NEAREST;
	m_magFilter = GL_NEAREST;
	m_wrapping = GL_CLAMP_TO_BORDER;
}

btTexture::~btTexture(void)
{
	clear();
}

void btTexture::clear(void)
{
	if (m_textureIdent != INVALID_OBJECT_ID)
	{
		glDeleteTextures(1, &m_textureIdent);
		m_textureIdent = INVALID_OBJECT_ID;
	}
}

void btTexture::bind(void)
{
	//check texture 
	if (m_textureTarget != INVALID_OBJECT_ID)
		return;

	if (m_textureTarget == GL_TEXTURE_1D || m_textureTarget == GL_TEXTURE_1D_ARRAY)
		glEnable(GL_TEXTURE_1D);
	else if (m_textureTarget == GL_TEXTURE_2D && m_textureTarget == GL_TEXTURE_2D_ARRAY && m_textureTarget == GL_TEXTURE_2D_MULTISAMPLE)
		glEnable(GL_TEXTURE_2D);
	else if (m_textureTarget == GL_TEXTURE_CUBE_MAP)
		glEnable(GL_TEXTURE_CUBE_MAP);
	else if (m_textureTarget == GL_TEXTURE_3D)
		glEnable(GL_TEXTURE_3D);

/*
#if _DEBUG
	CheckGlError(__FILE__, __LINE__);
#endif
*/
	glBindTexture(m_textureTarget, m_textureIdent);

/*
#if _DEBUG
	CheckGlError(__FILE__, __LINE__);
#endif
*/
	m_isBind = true;
}

void btTexture::bindNull(void)
{
	//check texture 
	if (!validate())
		return;

	glBindTexture(m_textureTarget, 0);

	if (m_textureTarget == GL_TEXTURE_1D || m_textureTarget == GL_TEXTURE_1D_ARRAY)
		glDisable(GL_TEXTURE_1D);
	else if (m_textureTarget == GL_TEXTURE_2D && m_textureTarget == GL_TEXTURE_2D_ARRAY && m_textureTarget == GL_TEXTURE_2D_MULTISAMPLE)
		glDisable(GL_TEXTURE_2D);
	else if (m_textureTarget == GL_TEXTURE_CUBE_MAP)
		glDisable(GL_TEXTURE_CUBE_MAP);
	else if (m_textureTarget == GL_TEXTURE_3D)
		glDisable(GL_TEXTURE_3D);

//#if _DEBUG
//	CheckGlError(__FILE__, __LINE__);
//#endif

	m_isBind = false;
}

bool btTexture::validate(void)
{
	if (m_textureIdent != INVALID_OBJECT_ID)
	{
		if (glIsTexture(m_textureIdent) == 0)
			return true;
	}
	return false;
}

void btTexture::setFormat(const GLenum TextuFormat)
{
	m_internalFormat = TextuFormat;

	switch (TextuFormat)
	{
		//No Alpha formats
	case GL_RGB5:
		m_BPP = 16;
		m_pixelFormat = GL_RGB;
		m_dataFormat = GL_UNSIGNED_BYTE;
		break;
	case GL_RGB4:
		m_BPP = 12;
		m_pixelFormat = GL_RGB;
		m_dataFormat = GL_UNSIGNED_BYTE;
		break;
	case GL_RGB8:
		m_BPP = 24;
		m_pixelFormat = GL_RGB;
		m_dataFormat = GL_UNSIGNED_BYTE;
		break;
	case GL_SRGB8:
		m_BPP = 24;
		m_pixelFormat = GL_RGB;
		m_dataFormat = GL_UNSIGNED_BYTE;
		break;
	case GL_RGB10:
		m_BPP = 32;
		m_pixelFormat = GL_RGB;
		m_dataFormat = GL_UNSIGNED_BYTE;
		break;
	case GL_RGB12:
		m_BPP = 36;
		m_pixelFormat = GL_RGB;
		m_dataFormat = GL_UNSIGNED_BYTE;
		break;
	case GL_RGB16:
		m_BPP = 48;
		m_pixelFormat = GL_RGB;
		m_dataFormat = GL_UNSIGNED_BYTE;
		break;
	case GL_RGB16F:
		m_BPP = 48;
		m_pixelFormat = GL_RGB;
		m_dataFormat = GL_UNSIGNED_BYTE;
		break;
	case GL_RGB32F:
		m_BPP = 96;
		m_pixelFormat = GL_RGB;
		m_dataFormat = GL_UNSIGNED_BYTE;
		break;
	case GL_COMPRESSED_RGB_S3TC_DXT1_EXT:
		m_dataFormat = GL_UNSIGNED_BYTE;
		m_BPP = 24;
		m_pixelFormat = GL_RGB;
		break;
	case GL_COMPRESSED_SRGB_S3TC_DXT1_EXT:
		m_dataFormat = GL_UNSIGNED_BYTE;
		m_BPP = 24;
		m_pixelFormat = GL_RGB;
		break;

		//Whit Alpha Format
	case GL_RGBA4:
		m_BPP = 16;
		m_pixelFormat = GL_RGBA;
		m_dataFormat = GL_UNSIGNED_BYTE;
		break;
	case GL_RGBA8:
		m_BPP = 32;
		m_pixelFormat = GL_RGBA;
		m_dataFormat = GL_UNSIGNED_BYTE;
		break;
	case GL_SRGB8_ALPHA8:
		m_BPP = 32;
		m_pixelFormat = GL_RGBA;
		m_dataFormat = GL_UNSIGNED_BYTE;
		break;
	case GL_RGB10_A2:
		m_BPP = 32;
		m_pixelFormat = GL_RGBA;
		m_dataFormat = GL_UNSIGNED_BYTE;
		break;
	case GL_RGBA12:
		m_BPP = 48;
		m_pixelFormat = GL_RGBA;
		m_dataFormat = GL_UNSIGNED_BYTE;
		break;
	case GL_RGBA16:
		m_BPP = 64;
		m_pixelFormat = GL_RGBA;
		m_dataFormat = GL_UNSIGNED_BYTE;
		break;
	case GL_RGBA16F:
		m_BPP = 64;
		m_pixelFormat = GL_RGBA;
		m_dataFormat = GL_UNSIGNED_BYTE;
		break;
	case GL_RGBA32F:
		m_BPP = 128;
		m_pixelFormat = GL_RGBA;
		m_dataFormat = GL_UNSIGNED_BYTE;
		break;
	case GL_COMPRESSED_RGBA_S3TC_DXT1_EXT:
	case GL_COMPRESSED_RGBA_S3TC_DXT3_EXT:
	case GL_COMPRESSED_RGBA_S3TC_DXT5_EXT:
		m_BPP = 24;
		m_pixelFormat = GL_RGBA;
		m_dataFormat = GL_UNSIGNED_BYTE;
		break;
	case GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT1_EXT:
	case GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT3_EXT:
	case GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT5_EXT:
		m_BPP = 24;
		m_pixelFormat = GL_RGBA;
		m_dataFormat = GL_UNSIGNED_BYTE;
		break;

		//depth format 
	case GL_DEPTH_COMPONENT:
		m_BPP = 8;
		m_pixelFormat = GL_DEPTH;
		m_dataFormat = GL_UNSIGNED_INT;
		break;
	case GL_DEPTH_COMPONENT16:
		m_BPP = 16;
		m_pixelFormat = GL_DEPTH;
		m_dataFormat = GL_UNSIGNED_INT;
		break;
	case GL_DEPTH_COMPONENT24:
		m_BPP = 24;
		m_pixelFormat = GL_DEPTH;
		m_dataFormat = GL_UNSIGNED_INT;
		break;
	case GL_DEPTH_COMPONENT32:
		m_BPP = 32;
		m_pixelFormat = GL_DEPTH;
		m_dataFormat = GL_UNSIGNED_INT;
		break;
	case GL_DEPTH_COMPONENT32F:
		m_BPP = 32;
		m_pixelFormat = GL_DEPTH;
		m_dataFormat = GL_FLOAT;
		break;

		//depth and stecil format 
	case GL_DEPTH24_STENCIL8:
		m_BPP = 32;
		m_pixelFormat = GL_DEPTH_STENCIL;
		m_dataFormat = GL_UNSIGNED_INT_24_8;
	case GL_DEPTH32F_STENCIL8:
		m_BPP = 40;
		m_pixelFormat = GL_DEPTH_STENCIL;
		m_dataFormat = GL_FLOAT_32_UNSIGNED_INT_24_8_REV;
		break;

		//single luminance values
	case GL_R8:
	case GL_R16:
	case GL_R16F:
		m_pixelFormat = GL_RED;
		break;

		//double component color palete
	case GL_RG8:
	case GL_RG16:
		m_pixelFormat = GL_RG;
		break;

//LEAK
	//color Palete
	case GL_COLOR_INDEX4_EXT:
	case GL_COLOR_INDEX8_EXT:
	case GL_COLOR_INDEX16_EXT:
		m_pixelFormat = GL_COLOR_INDEX;
		break;

	default:
		std::cout << "ivalid texture Color Format: " << m_internalFormat << std::endl;
		break;
	}
}

void btTexture::setFilter(const GLenum Magnification, const GLenum Minification, bool aniso)
{
	m_minFilter = Magnification;
	m_magFilter = Minification;
	m_textureUseAnisotropi = aniso;
}

void btTexture::updateFilter(void)
{
	bool binded = m_isBind;

	//check texture 
	if (!validate())
		return;

	if (!m_isBind)
		bind();

	glTexParameteri(m_textureTarget, GL_TEXTURE_MIN_FILTER, m_minFilter);
	glTexParameteri(m_textureTarget, GL_TEXTURE_MAG_FILTER, m_magFilter);

//#if _DEBUG
//	CheckGlError(__FILE__, __LINE__);
//#endif

	///TODO: Set the amount of anisostrpy
	//if (m_anisostropy > 0 && glConfig.anisotropicAvailable && m_anisotropic)
	//	glTexParameteri(m_textureTarget, GL_TEXTURE_MAX_ANISOTROPY_EXT, m_anisostropy);

//#if _DEBUG
//	CheckGlError(__FILE__, __LINE__);
//#endif

	if (!binded)
		bindNull();
}

void btTexture::setWrapping(const GLenum wrap)
{
	m_wrapping = wrap;
}

void btTexture::updateWrapping(void)
{
	bool binded = m_isBind;
	//check texture 
	if (!validate())
		return;

	if (!binded)
		bind();

	//multisamples textures dont have repeat
	if (m_textureTarget == GL_TEXTURE_2D_MULTISAMPLE)
	{
		glTexParameteri(m_textureTarget, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(m_textureTarget, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

		if (!binded)
			bindNull();

		return;
	}

//#if _DEBUG
//	CheckGlError(__FILE__, __LINE__);
//#endif

	glTexParameteri(m_textureTarget, GL_TEXTURE_WRAP_S, m_wrapping);
	if (m_textureTarget == GL_TEXTURE_2D || m_textureTarget == GL_TEXTURE_2D_ARRAY || m_textureTarget == GL_TEXTURE_CUBE_MAP)
		glTexParameteri(m_textureTarget, GL_TEXTURE_WRAP_T, m_wrapping);
	else if (m_textureTarget == GL_TEXTURE_3D)
		glTexParameteri(m_textureTarget, GL_TEXTURE_WRAP_R, m_wrapping);

//#if _DEBUG
//	CheckGlError(__FILE__, __LINE__);
//#endif

	if (!binded)
		bindNull();
}

void btTexture::generate(GLenum type, GLenum format, GLuint width, GLuint height, GLuint depth, Uint8 numSamples)
{
	glGenTextures(1, &m_textureIdent);
	m_textureTarget = type;
	m_width = width;
	m_height = height;
	m_depth = depth;

	//set the color format
	setFormat(format);
	
	//bind texture for modyfi
	bind();

	//set the texture wraping
	updateWrapping();

	//set the texture filter
	updateFilter();

	switch (m_textureTarget)
	{
	case GL_TEXTURE_1D:
		glTexImage1D(m_textureTarget, 0, m_internalFormat, m_width, 0, m_pixelFormat, m_dataFormat, NULL);
		break;
	case GL_TEXTURE_1D_ARRAY:
	case GL_TEXTURE_2D:
		glTexImage2D(m_textureTarget, 0, m_internalFormat, m_width, m_height, 0, m_pixelFormat, m_dataFormat, NULL);
		break;
	case GL_TEXTURE_2D_MULTISAMPLE:
		glTexImage2DMultisample(m_textureTarget, numSamples, m_internalFormat, m_width, m_height, GL_FALSE);
		break;
	case GL_TEXTURE_2D_ARRAY:
	case GL_TEXTURE_3D:
		glTexImage3D(m_textureTarget, 0, m_internalFormat, m_width, m_height, m_depth, 0, m_pixelFormat, m_dataFormat, NULL);
		break;
	default:
		gConsole.error("invalid texture target");
		break;
	}

//#if _DEBUG
//	CheckGlError(__FILE__, __LINE__);
//#endif

	bindNull();
}

void btTexture::updateTextureLevel(Uint32 level, GLenum dataFormat, void * textureLevelData, Uint32 width, Uint32 height, Uint32 Depth)
{
	switch (m_textureTarget)
	{
	case GL_TEXTURE_1D:
		glTexImage1D(m_textureTarget, level, m_internalFormat, width, 0, m_pixelFormat, dataFormat, textureLevelData);
		break;
	case GL_TEXTURE_1D_ARRAY:
	case GL_TEXTURE_2D:
		glTexImage2D(m_textureTarget, level, m_internalFormat, width, height, 0, m_pixelFormat, dataFormat, textureLevelData);
		break;
	case GL_TEXTURE_2D_ARRAY:
	case GL_TEXTURE_3D:
		glTexImage3D(m_textureTarget, level, m_internalFormat, width, height, Depth, 0, m_pixelFormat, dataFormat, textureLevelData);
		break;
	default:
		break;
	}
#if _DEBUG
	//CheckGlError(__FILE__, __LINE__);
#endif
}

void btTexture::updateSubTextureLevel(Uint32 level, GLenum dataFormat, void * textureLevelData, Uint32 width, Uint32 height, Uint32 Depth)
{
	switch (m_textureTarget)
	{
	case GL_TEXTURE_1D:
		glTexSubImage1D(m_textureTarget, level, 0, width, m_pixelFormat, dataFormat, textureLevelData);
		break;
	case GL_TEXTURE_1D_ARRAY:
	case GL_TEXTURE_2D:
		glTexSubImage2D(m_textureTarget, level, 0, 0, width, height, m_pixelFormat, dataFormat, textureLevelData);
		break;
	case GL_TEXTURE_2D_ARRAY:
	case GL_TEXTURE_3D:
		glTexSubImage3D(m_textureTarget, level, 0, 0, 0, width, height, Depth, m_pixelFormat, dataFormat, textureLevelData);
		break;
	default:
		break;
	}
//#if _DEBUG
//	CheckGlError(__FILE__, __LINE__);
//#endif
}

GLenum btTexture::getFormat(void) const
{
	return m_internalFormat;
}

GLuint btTexture::getTextureIdent(void) const
{
	return m_textureIdent;
}

GLenum btTexture::getTextureTarget(void) const
{
	return m_textureTarget;
}

