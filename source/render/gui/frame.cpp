
#include "precompiled.h"
#pragma hdrstop

#include "frame.h"

//positions				//text coord
const static GLfloat verts[20] = { -1.0f, -1.0f, 0.0f,		0.0, 0.0f,
1.0f, -1.0f, 0.0f,		1.0, 0.0f,
1.0f,  1.0f, 0.0f,		1.0, 1.0f,
-1.0f,	1.0f, 0.0f,		0.0, 1.0f };

const static GLuint	indices[6] = { 0, 1 , 2,
2, 0, 1 };


btFrame::btFrame(void) : btWidget()
{
}

btFrame::btFrame(std::string name, btWidget * parent, 
	glm::vec2 size, 
	glm::vec2 pos,
	btColorApha color,
	btColorApha borderColor,
	float bordersize,
	Uint32 options): btWidget(name, parent, size, pos, options),
	m_bgColor(color),
	m_borderColor(borderColor),
	m_borderSize(bordersize)
{
	//create the frame surface
	btIntrusivePtr<btVertexBuffer> newVBuff(new btVertexBuffer);
	btIntrusivePtr<btDrawBuffer> newMbuff(new btDrawBuffer(6));
	//generate the vertex bufers
	newVBuff->genBuffer();

	//put data in buffer
	//newVBuff->fillBufferData(indices, verts);
	newVBuff->fillBufferData(indices, nullptr);
	
	//setup buffer data reference
	newVBuff->bindVertexBuffer();

	newVBuff->unbindVertexBuffer();

	m_surface = btIntrusivePtr<btRenderSuface>(new btRenderSuface(newVBuff, newMbuff));
}

btFrame::~btFrame(void)
{
}

void btFrame::clear(void)
{
}

void btFrame::draw(void)
{
	//send frame to the renderer
//	gRendererGlobal.renderRectColor(m_position.x, m_position.y, m_size.x, m_size.y, m_bgColor, 0);
	
	//present to the renderer 
	m_surface->setPosition(m_position.x, m_position.y, 0.0f);
	m_surface->setSize(m_size.x, m_size.y, 0.0f);
	m_surface->setColor(m_bgColor);
	gRendererGlobal.appendRenderSurface(m_surface);

	/*
	//draw the borders 
	if( m_borderSize > 0.0f)
	{
		//set the gl Line Boreder size
		glLineWidth(m_borderSize);
		m_FrameGeometry.bind();
		{
			btVertAttribLock v(&vpos), t(&tcoord);
			m_FrameGeometry.bindElementBuffer();
			glDrawElements(GL_LINE_STRIP, 5, GL_UNSIGNED_SHORT, (void*)0);
		}
		m_FrameGeometry.unbind();
		
		//set defalt line size
		glLineWidth(1.0f);
	}
	*/
}