
#ifndef _GUI_FRAME_H_
#define _GUI_FRAME_H_

#include "widget.h"
#include "render/geometry/vertexBuffer.h"

class btFrame : public btWidget
{
public:
	btFrame(void);
	btFrame(std::string name, btWidget* parent,
		glm::vec2 size = glm::vec2(1.0f, 1.0f),
		glm::vec2 pos = glm::vec2(0.0f, 0.0f),
		glm::vec4 color = glm::bvec4(1.0),
		glm::vec4 borderColor = glm::bvec4(0.0),
		float bordersize = 1.0,
		Uint32 options = GUI_DEFAULT);

	~btFrame(void);

	virtual void	clear(void);
	virtual void	draw(void);

private:
	btVertexBuffer	m_FrameGeometry;
	glm::vec4		m_bgColor;
	glm::vec4		m_borderColor;
	float			m_borderSize;	
};

#endif //!_GUI_FRAME_H_