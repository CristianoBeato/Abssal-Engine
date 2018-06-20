
#ifndef _SYS_TIMER_H_
#define _SYS_TIMER_H_

class btTimer
{
public:
	btTimer(void);
	~btTimer(void);

	//The various clock actions
	void	start(void);
	void	stop(void);
	void	pause(void);
	void	unPause(void);

	//Gets the timer's time
	int		getTicks(void);

	//Checks the status of the timer
	bool	isStarted(void);
	bool	isPaused(void);

private:
	//The clock time when the timer started
	Uint32     m_startTicks;

	//The ticks stored when the timer was paused
	Uint32     m_pausedTicks;

	//The timer status
	bool    m_paused;

	bool    m_started;
};

 
#endif // !_SYS_TIMER_H_
