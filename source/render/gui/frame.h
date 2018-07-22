
#ifndef _GUI_FRAME_H_
#define _GUI_FRAME_H_

#include "widget.h"
#include "render/geometry/vertexBuffer.h"

class btRenderSuface;
class btFrame : public btWidget
{
public:
	btFrame(void);
	btFrame(std::string name, btWidget* parent,
		glm::vec2 size = glm::vec2(1.0f, 1.0f),
		glm::vec2 pos = glm::vec2(0.0f, 0.0f),
		btColorApha color = btColorApha(255),
		btColorApha borderColor = btColorApha(255),
		float bordersize = 1.0,
		Uint32 options = GUI_DEFAULT);

	~btFrame(void);

	virtual void	clear(void);
	virtual void	draw(void);

private:
	btIntrusivePtr<btRenderSuface>	m_surface;
	btColorApha						m_bgColor;
	btColorApha						m_borderColor;
	float							m_borderSize;	
};

#endif //!_GUI_FRAME_H_