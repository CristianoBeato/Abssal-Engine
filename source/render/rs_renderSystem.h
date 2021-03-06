
#ifndef _RENDER_SYSTEM_H_
#define _RENDER_SYSTEM_H_

#include "rs_renderSurface.h"
#include "shader/shaderManager.h"
#include "image/texture.h"

class btFontManager;
class btTextureManager;
class btShaderManager;

const static Uint32 K_BLEND_NONE = 0xD0;

const static Uint32 K_SCISSOR_NONE = 0xE0;

const static Uint32 K_CULL_NONE = 0xF0;
const static Uint32 K_CULL_BACK = 0xF1;
const static Uint32 K_CULL_FRON = 0xF2;


class btRenderSystem
{
public:
	btRenderSystem(void);
	~btRenderSystem(void);

	void	startUp(void);
	void	shutDonw(void);

	//clar previus stages, and setup the render defalt
	void	beginFrame(void);

	//end the rendering, swap buffers
	void	endFrame(void);

	void	setupViewPort(const Uint32 width, const Uint32 height);

	void	setupView(float x, float y, float z = 0);

	void	renderBackend(void);

	//put render surface in buffer
	void	appendRenderSurface(btIntrusivePtr<btRenderSuface> surface);

	//rendel helper macros
	void	renderLine(float xa, float ya, float xb, float yb, btColorApha color, const Uint32 flags);
	void	renderRectColor(float x, float y, float w, float h, btColorApha color, const Uint32 flags);
	void	renderRectTexture(float x, float y, float w, float h, btColorApha color, const Uint32 flags);
	void	renderRectColorTexture(float x, float y, float w, float h, btColorApha color, const Uint32 flags);

	//get the reference from the render sub systems
	btShaderManager		&shaderManager(void) { return *m_shaderManager; };
	btTextureManager	&textureManager(void) { return *m_textureManager; };
	btFontManager		&fontManager(void) { return *m_fontManager; };

	glm::mat4			getViewProjectionMatrix(void);

	void	selectTextureNoClient(Uint32 unit);

protected:
	void	setupCulling(const Uint32 mode = K_CULL_NONE);
	void	setupBlending(const Uint32 mode = K_BLEND_NONE);
	void	setupScissor(const Uint32 mode = K_SCISSOR_NONE,
		const glm::vec2 pos = glm::vec2(0.0f, 0.0f), 
		const glm::vec2 size = glm::vec2(0.0f, 0.0f));

	btShaderManager	*	m_shaderManager;
	btTextureManager*	m_textureManager;
	btFontManager	*	m_fontManager;

	Uint32				m_currentTextureId;
	std::vector<btIntrusivePtr<btRenderSuface > >	m_Surfaces;
private:
	Uint32		m_cullMode, m_blendMode;
	Uint32		m_viewWidth, m_viewHeight;
	glm::mat4	m_viewMatrix;
	glm::mat4	m_projectionMatrix;
	bool		m_multisample;
};

extern btRenderSystem gRendererGlobal;

#endif // !_RENDER_SYSTEM_H_
