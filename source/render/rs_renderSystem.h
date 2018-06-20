
#ifndef _RENDER_SYSTEM_H_
#define _RENDER_SYSTEM_H_
 
class btFontManager;
class btTextureManager;
class btShaderManager;

class btRenderSystem
{
public:
	btRenderSystem(void);
	~btRenderSystem(void);

	void	startUp(void);
	void	shutDonw(void);

	void	beginFrame(void);
	void	endFrame(void);

protected:
	btShaderManager	*	m_shaderManager;
	btTextureManager*	m_textureManager;
	btFontManager	*	m_fontManager;

private:
	bool	m_multisample;
};

extern btRenderSystem rendererGlobal;

#endif // !_RENDER_SYSTEM_H_
