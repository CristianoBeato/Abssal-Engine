
#ifndef _GUI_H_
#define _GUI_H_

#include "widget.h"
#include "frame.h"
#include "image.h"

class btGuiBase
{
public:
	btGuiBase(void);
	~btGuiBase(void);

	void	create(void);
	void	load(const std::string guiPath);
	void	clear(void);

	//update gui structure
	void	think(void);

	//render gui ents 
	void	render(void);

private:

	glm::ivec2		m_pointerPos;
	btFrame	*		m_guiPointer;
	btFrame	*		m_guiFrameBase;
};

#endif // !_GUI_H_