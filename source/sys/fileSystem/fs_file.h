
#ifndef _FS_FILE_H_
#define _FS_FILE_H_

#include "fs_stream.h"
#include <string>

#if defined( _WIN32 )
const char PATH_SEPARATOR = '\\';
#else
const char PATH_SEPARATOR = '/';
#endif

static const int		MAX_OSPATH = 255;

#if 0
/*
===================================================================================
btFileHandler
===================================================================================
*/
class btFileHandler : public btRefObj
{
public:
	btFileHandler(void);
	~btFileHandler(void);

	void			setVirtualFileName(const std::string& VirtName);
	void			setFileName(const std::string& name);
	std::string		getVirtualFileName(void) const;
	std::string		getFileName(void)        const;

	virtual const Uint8*	getFileData(void) const = 0;
	virtual size_t			getFileSize(void) const = 0;

protected:
	std::string		m_fileName;
	std::string		m_virtualFileName;
};

/*
===================================================================================
btRawFileHandler
Physical file representation
===================================================================================
*/
class btRawFileHandler
{
public:
	btRawFileHandler(void);
	~btRawFileHandler(void);

	bool open(const std::string& fileName, const std::string& virtualFileName, const char* mode);
	void close(void);

	virtual const Uint8*	getFileData(void) const;
	virtual size_t			getFileSize(void) const;
private:
	Uint8*    m_fileData;
	size_t    m_fileSize;
};
#endif

/*
===================================================================================
btFileStream
===================================================================================
*/
class btFileStream : public btStream
{
public:
	btFileStream(void);
	~btFileStream(void);

	virtual bool open(const std::string& FileName, const char* mode);
	virtual void close(void);

	//virtual std::string		getVirtualFileName(void) const;
	virtual std::string		getFileName(void) const;
	virtual bool			end(void);
	virtual size_t			tell(void) const;
	virtual size_t			size(void) const;
	virtual bool			seek(size_t offset, int whence = FS_SEEK_SET);
	virtual size_t			read(void* buf, const size_t len);
	virtual size_t			write(const void *buf, const size_t len);

	virtual const Uint8*	mapStream(void) const;
	virtual const Uint8*	mapStreamFromCurrentPos(void) const;

private:
	std::string						m_fileName;
	Uint8*							m_fileBuff;
	SDL_RWops*						m_mapFile;
	// Cached read/write position to avoid SDL_tell() function calls
	size_t							m_position;		//position of carret on the file
	// Cached final file size to avoid SDL_size() function calls
	size_t							m_fileSize;
};

class btFileSystemDirs
{
public:
	enum
	{
		FSD_BASE_PATH = 0,	//open file from game base path
		FSD_EXEC_PATH,
		FSD_SAVE_PATH		//open file from game save path
	};

	btFileSystemDirs(void);
	~btFileSystemDirs(void);

	const std::string		getRunPath(void);
	const std::string		getBasePath(void);
	const std::string		getBaseSavePath(void);

	btFileStream*	openFromShaders(std::string file, const char *mode = "r", Uint8 path = FSD_BASE_PATH);
	btFileStream*	openFromTextures(std::string file, const char *mode = "r", Uint8 path = FSD_BASE_PATH);
	btFileStream*	openFromFonts(std::string file, const char *mode = "r", Uint8 path = FSD_BASE_PATH);

private:
	std::string			m_basePath, m_runPath, m_baseSavePath;
};

extern btFileSystemDirs	gFileSystem;

#endif // !_FS_FILE_H_
