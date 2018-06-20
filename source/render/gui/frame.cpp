
#include "precompiled.h"
#pragma hdrstop

#include "frame.h"

static const GLfloat k_positions[16] =
{
	//pos			//coord
	-1.0f, -1.0f,	0.0f, 0.0f,
	 1.0f, -1.0f,	1.0f, 0.0f,
	 1.0f,  1.0f,	1.0f, 1.0f,
	-1.0f,	1.0f,	0.0f, 1.0f
};

//we need define 5 to draw the line strip from the border
static const GLushort k_indices[5] = 
{
	0, 1, 2, 3, 0
};

btFrame::btFrame(void) : btWidget()
{
}

btFrame::btFrame(std::string name, btWidget * parent, 
	glm::vec2 size, 
	glm::vec2 pos,
	glm::vec4 color, 
	glm::vec4 borderColor, 
	float bordersize,
	Uint32 options): btWidget(name, parent, size, pos, options),
	m_bgColor(color),
	m_borderColor(borderColor),
	m_borderSize(bordersize)
{
	btVertexAttrib vpos(0);
	btVertexAttrib tcoord(1);
	
	//gen the buffer
	m_FrameGeometry = btVertexBuffer();
	m_FrameGeometry.genBuffer();

	//append the buffed data 
	m_FrameGeometry.fillBufferData(k_indices, k_positions);

	m_FrameGeometry.bind();
	m_FrameGeometry.bindVertexBuffer();
	{
		btVertAttribLock v(&vpos), t(&tcoord);
		vpos.setPoiner(2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
		vpos.setPoiner(2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
	}
	m_FrameGeometry.unbind();
}

btFrame::~btFrame(void)
{
}

void btFrame::clear(void)
{
	m_FrameGeometry.clear();
}

void btFrame::draw(void)
{
	//we do here beceuse whe need to draw texture properly
	btVertexAttrib vpos(0);
	btVertexAttrib tcoord(1);
	btVertexAttrib color(2);

	btWidget::draw();
	
	//TODO: Draw Wiget Here
	m_FrameGeometry.bind();
	{
		btVertAttribLock v(&vpos), t(&tcoord);
		glDrawElements(GL_QUADS, 4, GL_UNSIGNED_SHORT, (void*)0);
	}
	m_FrameGeometry.unbind();

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
}