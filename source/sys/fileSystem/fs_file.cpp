
#include "precompiled.h"
#pragma hdrstop

#include "fs_file.h"

#ifdef  _WINDOWS
#	include <direct.h>
#	define GetWorkDir getcwd
#else
#	include <unistd.h>
#	define GetWorkDir getcwd
#endif //  WINDOWS

#if 0
/*
===================================================================================
btFileHandler
===================================================================================
*/
btFileHandler::btFileHandler(void)
{
}

btFileHandler::~btFileHandler(void)
{
}

void btFileHandler::setVirtualFileName(const std::string & VirtName)
{
	m_virtualFileName = VirtName;
}

void btFileHandler::setFileName(const std::string & name)
{
	m_fileName = name;
}

std::string btFileHandler::getVirtualFileName(void) const
{
	return m_virtualFileName;
}

std::string btFileHandler::getFileName(void) const
{
	return m_fileName;
}


/*
===================================================================================
btRawFileHandler
===================================================================================
*/

const Uint8 * btRawFileHandler::getFileData(void) const
{
	return m_fileData;
}

size_t btRawFileHandler::getFileSize(void) const
{
	return m_fileSize;
}

btRawFileHandler::btRawFileHandler(void)
{
}

btRawFileHandler::~btRawFileHandler(void)
{
}
#endif

/*
===================================================================================
btFileStream
===================================================================================
*/


btFileStream::btFileStream(void): btStream(), m_mapFile(NULL), m_position(0), m_fileSize(0), m_fileBuff(nullptr)
{
}

btFileStream::~btFileStream(void)
{
}

bool btFileStream::open(const std::string & FileName, const char * mode)
{
	m_fileName = FileName;

	m_mapFile = SDL_RWFromFile(m_fileName.c_str(), mode);
	if (m_mapFile == NULL)
	{
		gConsole.warning(" Unable to open file %s in %s mode\n", FileName.c_str(), mode);
		return false;
	}

	m_fileSize = (size_t)SDL_RWsize(m_mapFile);
	return true;
}

void btFileStream::close(void)
{
	//close the file
	SDL_FreeRW(m_mapFile);

	//if we using the buffer ptr clean
	if (m_fileBuff != nullptr)
		SDL_free(m_fileBuff);

	if (m_streamMap != NULL)
	{
		SDL_free(m_streamMap);
		m_streamMap = NULL;
	}
}

/*
std::string btFileStream::getVirtualFileName(void) const
{
	return std::string();
}
*/

std::string btFileStream::getFileName(void) const
{
	return m_fileName;
}

bool btFileStream::seek(size_t offset, int whence)
{
	if (m_mapFile != NULL)
	{
		m_position = (size_t)SDL_RWseek(m_mapFile, offset, whence);
		return true;
	}
	else
		return false;
}

size_t btFileStream::tell(void) const
{
	return m_position;
}

size_t btFileStream::size(void) const
{
	return m_fileSize;
}

bool btFileStream::end(void)
{
	return m_position >= m_fileSize;
}

size_t btFileStream::read(void * buf, const size_t len)
{
	if (m_mapFile != NULL)
		SDL_RWread(m_mapFile, buf, len, 1);

	//move cursor
	m_position += len;

	return len;
}

size_t btFileStream::write(const void * buf, size_t len)
{
	if (m_mapFile != NULL)
		SDL_RWwrite(m_mapFile, buf, len, 1);

	//move cursor
	m_position += len;

	//increse file size
	m_fileSize += len;
	return len;
}

const Uint8 * btFileStream::mapStream(void) const
{
	if (m_mapFile != NULL)
	{	//whe only map the file wen call mapStream
		if (m_streamMap == NULL)
		{
			size_t filesize = size();
#if 1
			m_streamMap = (Uint8*)SDL_malloc(filesize + 1);
#else
			m_streamMap = (Uint8*)bt_malloc(filesize + 1);
#endif

			SDL_memset(m_streamMap, 0x00, filesize + 1);
			SDL_RWread(m_mapFile, m_streamMap, filesize, 1);
		}

		return m_streamMap;
	}
	else
		return NULL;
}

const Uint8 * btFileStream::mapStreamFromCurrentPos(void) const
{
	if (m_mapFile != NULL)
		return (mapStream() + m_fileSize);

	return NULL;
}

btFileSystemDirs::btFileSystemDirs(void)
{
}

btFileSystemDirs::~btFileSystemDirs(void)
{
}

const std::string btFileSystemDirs::getRunPath(void)
{
	if (m_runPath.empty())
	{
		char runpath[FILENAME_MAX];
		if (!GetWorkDir(runpath, sizeof(runpath)))
			gConsole.fatalError("can't get run path");

		m_runPath = runpath;
		m_runPath += PATH_SEPARATOR;
	}

	return m_runPath;
}

const std::string btFileSystemDirs::getBasePath(void)
{
	if (m_basePath.empty())
	{
		m_basePath = getRunPath();
		m_basePath += GAME_BASE_PATH;
		m_basePath += PATH_SEPARATOR;
	}

	return m_basePath;
}

const std::string btFileSystemDirs::getBaseSavePath(void)
{
	//Beato: uses getenv() on linux, because sdl set in "/home/user name/.local/share/SAVE_PATH/"
#if defined(__linux__)
	char path[MAX_OSPATH];
	sprintf(path, "%s/.rbdoom3bfg", getenv("HOME"));
	m_baseSavePath = std::string(path);
#else

	if (m_baseSavePath.empty())
	{
		char* base_path = SDL_GetPrefPath(GAME_DEVELOPER, GAME_SAVE_FOLDER);
		if (base_path)
		{
			m_baseSavePath = SDL_strdup(base_path);
			SDL_free(base_path);
		}
		else
			m_baseSavePath = GAME_SAVE_FOLDER;
	}
#endif
	return m_baseSavePath;
}

btFileStream * btFileSystemDirs::openFromShaders(std::string file, const char *mode, Uint8 path)
{
	bool	isopen = false;
	std::string shadersSubDir;
	btFileStream *	newFileStram = new btFileStream();

	if (path == FSD_SAVE_PATH)
		shadersSubDir += getBaseSavePath();
	else if (path == FSD_EXEC_PATH)
		shadersSubDir += getRunPath();
	else
		shadersSubDir += getBasePath();

	//set in sub dit
	shadersSubDir += "shaders";
	shadersSubDir += PATH_SEPARATOR;

	shadersSubDir += file;

	isopen = newFileStram->open(shadersSubDir, mode);

	//if open, pass the pointer, if not delete 
	if (isopen)
		return newFileStram;

	//free memory pointer
	delete newFileStram;
	return nullptr;
}

btFileStream * btFileSystemDirs::openFromTextures(std::string file, const char *mode, Uint8 path)
{
	bool	isopen = false;
	std::string shadersSubDir;
	btFileStream *	newFileStram = new btFileStream();

	if (path == FSD_SAVE_PATH)
		shadersSubDir += getBaseSavePath();
	else if (path == FSD_EXEC_PATH)
		shadersSubDir += getRunPath();
	else
		shadersSubDir += getBasePath();

	//set in sub dit
	shadersSubDir += "textures";
	shadersSubDir += PATH_SEPARATOR;

	shadersSubDir += file;

	isopen = newFileStram->open(shadersSubDir, mode);

	//if open, pass the pointer, if not delete 
	if (isopen)
		return newFileStram;

	//free memory pointer
	delete newFileStram;
	return newFileStram;
}

btFileStream * btFileSystemDirs::openFromFonts(std::string file, const char *mode, Uint8 path)
{
	bool	isopen = false;
	std::string shadersSubDir;
	btFileStream *	newFileStram = new btFileStream();

	if (path == FSD_SAVE_PATH)
		shadersSubDir += getBaseSavePath();
	else if (path == FSD_EXEC_PATH)
		shadersSubDir += getRunPath();
	else
		shadersSubDir += getBasePath();

	//set in sub dit
	shadersSubDir += "fonts";
	shadersSubDir += PATH_SEPARATOR;

	shadersSubDir += file;

	isopen = newFileStram->open(shadersSubDir, mode);

	//if open, pass the pointer, if not delete 
	if (isopen)
		return newFileStram;

	//free memory pointer
	delete newFileStram;
	return newFileStram;
}
