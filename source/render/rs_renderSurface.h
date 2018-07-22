
#ifndef _RENDER_SURFACE_H_
#define _RENDER_SURFACE_H_

class btRenderSuface : public btRefObj
{
public:
	btRenderSuface(void);
	btRenderSuface(const btIntrusivePtr<btVertexBuffer> vertBuff, const btIntrusivePtr<btDrawBuffer> mesh);
	~btRenderSuface(void);

	void	clear(void);

	//append a texture to the render mesh 
	void	appendTexture(btIntrusivePtr<btTexture> texRef);

	void	setPosition(const float x, const float y, const float z);
	void	setPosition(const glm::vec3 pos);

	//rotate model (based in the current location)
	void	setOrientation(const float x, const float y, const float z, const float w);
	void	setOrientation(const glm::quat rot);

	//resize the model (based in current size)
	void	setSize(const float x, const float y, const float z);
	void	setSize(const glm::vec3 size);

	//set surface color
	void	setColor(const Uint32 r, const Uint32 g, const Uint32 b, const Uint32 a);
	void	setColor(const btColorApha color);
	//set the surface culling
	void	setCulling(const Uint32 flag);
	//set the surface blending
	void	setBlending(const Uint32 flag);

	//get surface textures
	const std::vector<btIntrusivePtr<btTexture>>	getTextures(void) const;
	//get the number of textures on the current surface
	const Uint32									getNumTextures(void) const;
	//get the surface cull mode
	const Uint32									getCullingMode(void) const;
	//get the surface blend mode
	const Uint32									getBlendMode(void) const;
	//get the model matrix
	const glm::mat4									getModelMatrix(void) const;
	//get the texture tranformation matrix
	const glm::mat4									getTextureMatrix(void) const;
	//the model color
	const btColorApha								getModelColor(void) const;
	//the surface buffer draw call
	void											Draw(void);

private:
	//model tranformation matrix
	glm::mat4									m_modelMatrix;
	//texture tranformatiom matrix
	glm::mat4									m_textureMatrix;

	btColorApha									m_surfaceRenderColor;
	Uint32										m_renderMode;
	Uint32										m_blendMode;
	Uint32										m_cullMode;
	std::vector<btIntrusivePtr<btTexture> >		m_renderTextures;
	btIntrusivePtr<btVertexBuffer>				m_surfaceVbuffer;
	btIntrusivePtr<btDrawBuffer>				m_surfaceMesh;
};

#endif // !_RENDER_SURFACE_H_
