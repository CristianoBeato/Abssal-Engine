
#ifndef _SYS_ENGINE_H_
#define _SYS_ENGINE_H_

#include "framework/configuration.h"
#include "sys_timer.h"
#include "gameLogic/lgc_level.h"

class btEngine
{
public:
	enum engineState
	{
		GE_QUIT = -1,
		GE_STARTING,
		GE_MENU,
		GE_PAUSED,
		GE_RUNNING
	};

	btEngine(void);
	~btEngine(void);

	void			startUp(void);
	void			shutDown(void);

	void			changeState(const Sint8 state);
	const Sint8		getState(void) const;
	bool			sholdQuit(void) const;
	void			thinkFrame(void);			//run a game frame

private:
	Sint8				m_frameHate;	//30, 60 or 120 FPS
	Sint8				m_state;
	btGameLevel			m_level;		//current game level;

public:
	static btTimer				m_mainTimer;
};

//engine loop control 
extern btEngine	engineGlobal;

#endif // !_SYS_ENGINE_H_
