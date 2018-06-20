
#include "precompiled.h"
#pragma hdrstop

#include "sys_console.h"

//global console pointer initialization
btGameConsole gConsole = btGameConsole();

//static reference for the console stream
std::stringstream	btGameConsole::m_consoleLog = std::stringstream();
std::stringstream	btGameConsole::m_consoleWarnings = std::stringstream();
std::stringstream	btGameConsole::m_consoleErros = std::stringstream();

btGameConsole::btGameConsole(void)
{
}

btGameConsole::~btGameConsole(void)
{
}

void btGameConsole::startUp(void)
{
}

void btGameConsole::shutDonw(void)
{
}

void btGameConsole::PrintWarnings(void)
{
}

void btGameConsole::PrintErrors(void)
{
}

void btGameConsole::DumpConsole(void)
{
	btSmartPtr<btFileStream>	consoleLogFile(new btFileStream);
	consoleLogFile->open("ConsoleLog.txt", "w");
	//get the console buff
	std::string		cons = m_consoleLog.str();

	//write out the buff
	consoleLogFile->write(cons.c_str(), cons.length());
}

void btGameConsole::DumpWarnings(void)
{
	btSmartPtr<btFileStream>	consoleLogFile(new btFileStream);
	consoleLogFile->open("WarningLog.txt", "w");
	//get the console buff
	std::string		cons = m_consoleWarnings.str();

	//write out the buff
	consoleLogFile->write(cons.c_str(), cons.length());
}

void btGameConsole::DumpErros(void)
{
	btSmartPtr<btFileStream>	consoleLogFile(new btFileStream);
	consoleLogFile->open("ERRORS.txt", "w");
	//get the console buff
	std::string		cons = m_consoleErros.str();

	//write out the buff
	consoleLogFile->write(cons.c_str(), cons.length());
}

void btGameConsole::printf(const char * fmt, ...)
{
	std::string str;
	va_list argptr;
	va_start(argptr, fmt);
	VprintfStr(str, fmt, argptr); 
	va_end(argptr);

	//append mesage to the console log
	m_consoleLog << str;
}

void btGameConsole::DebugPrintf(const char * fmt, ...)
{
//TODO: append a way to manually set this on/off
#if _DEBUG
	std::string str;
	va_list argptr;
	va_start(argptr, fmt);
	VprintfStr(str, fmt, argptr);
	va_end(argptr);

	//append mesage to the console log 
	m_consoleLog << str;
#endif
}

void btGameConsole::warning(const char * fmt, ...)
{
	std::string str = std::string("WARNING: ");
	va_list argptr;
	va_start(argptr, fmt);
	VprintfStr(str, fmt, argptr);
	va_end(argptr);

	//append mesage to the console log and warning logs
	m_consoleLog << str;
	m_consoleWarnings << str;
}

void btGameConsole::error(const char * fmt, ...)
{
	std::string str = std::string("ERROR: ");
	va_list argptr;
	va_start(argptr, fmt);
	VprintfStr(str, fmt, argptr);
	va_end(argptr);

	//append mesage to the console log and ERROR logs
	m_consoleLog << str;
	m_consoleErros << str;
}

void btGameConsole::fatalError(const char * fmt, ...)
{
	std::string str = std::string("FATAL ERROR: ");
	va_list argptr;
	va_start(argptr, fmt);
	VprintfStr(str, fmt, argptr);
	va_end(argptr);

	//append mesage to the console log and ERROR logs
	m_consoleLog << str;
	m_consoleErros << str;

	//dump console to a file
	gConsole.DumpConsole();
	gConsole.DumpErros();
	Quit();
}

void btGameConsole::VprintfStr(std::string & str, const char * fmt, va_list args)
{
	char msg[MAX_PRINT_MSG_SIZE];
	SDL_vsnprintf(msg, MAX_PRINT_MSG_SIZE, fmt, args);

	//append to the string
	str += msg;

	//print the msg in system console (if is build on console mode on windows)
	std::cout << str;
}
