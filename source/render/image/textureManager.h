
#ifndef _TEXTURE_MANAGER_H_
#define _TEXTURE_MANAGER_H_

#include "texture.h"
#include "image_loader.h"

class btTextureManager;

//Helper for manage texture
class btRenderTexture : public btTexture 
{
public:
	btRenderTexture(void);
	btRenderTexture(btTextureManager* mng, Uint32 textureHash,  const GLenum target, const GLenum format);
	~btRenderTexture(void);

	void	reload(void);
	void	purge(void);

private:
	std::string			m_textureName;
	Sint32				m_textureIndex;
	btTextureManager*	m_managerRef;
};

class btTextureManager
{
public:
	btTextureManager(void);
	~btTextureManager(void);

	void	startUp(void);
	void	shutDonw(void);

	//free all textures
	void	clear(void);

	void	reload(void);

	//clean a texture from list
	void	purgeTexture(const std::string textureName);
	void	purgeTexture(const Uint32 textureHash);

	//
	btIntrusivePtr<btTexture>	getAsyncTexture(const std::string textureName);
	btIntrusivePtr<btTexture>	getAsyncTexture(const Uint32 textureHash);
	
	//
	btIntrusivePtr<btTexture>	getTexture(const std::string textureName);
	btIntrusivePtr<btTexture>	getTexture(const Uint32 textureHash);

private:
	std::map<std::string, Uint32 >						m_textureMap;
	std::map<Uint32, btIntrusivePtr<btRenderTexture>>	m_textureList;

};

#endif // !_TEXTURE_MANAGER_H_

