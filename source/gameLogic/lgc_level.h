
#ifndef _GAME_LEVEL_H_
#define _GAME_LEVEL_H_

class btGameObject;

#include "render/gui/gui.h"

class btGameLevel
{
public:
	btGameLevel(void);
	~btGameLevel(void);

	void	LoadLevel(const std::string levelDef);
	void	EmptyLevel(void);	//create a enpty game level
	void	clear(void);

	void	update(void);

private:
	void	startingLoadGui(void);

	std::vector<btGameObject*> m_objects;
	btGuiBase	m_gui;	//store the guis Main Game Gui, Pause Guis Loading Gui
};

#endif // !_GAME_LEVEL_H_
