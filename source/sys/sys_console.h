
#ifndef _GAME_CONSOLE_H_
#define _GAME_CONSOLE_H_

#include <sstream>
#include <string>

class btGameConsole
{
public:
	btGameConsole(void);
	~btGameConsole(void);

	void	startUp(void);
	void	shutDonw(void);

	void	PrintWarnings(void);
	void	PrintErrors(void);

	void	DumpConsole(void);
	void	DumpWarnings(void);
	void	DumpErros(void);

	static void	printf(const char* fmt, ...);
	static void DebugPrintf(const char* fmt, ...);
	static void	warning(const char* fmt, ...);
	static void	error(const char* fmt, ...);
	static void	fatalError(const char* fmt, ...);

private:
	static void VprintfStr(std::string &str, const char* fmt, va_list args);

	static std::stringstream	m_consoleWarnings;	//store the warnings
	static std::stringstream	m_consoleErros;		//store the errors
	static std::stringstream	m_consoleLog;		//store the console full log
};

//global console pointer
extern btGameConsole gConsole;

#endif // !_GAME_CONSOLE_H_
