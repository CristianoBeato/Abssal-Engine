/*
*/
#ifndef _FS_STREAM_H_
#define _FS_STREAM_H_

#include "sys/threading/th_atomic.h"

//SAME SDL
enum
{
	FS_SEEK_SET = 0,
	FS_SEEK_CUR = 1,
	FS_SEEK_END = 2
};

/*
===================================================================================
btEndianSwap
===================================================================================
*/
class btEndianSwap
{
public:
	virtual size_t read(void* buf, const size_t len) { return 0; };
	virtual size_t write(const void *buf, const size_t len) { return 0; };

	//16
	virtual short				readLittleShort(void);
	virtual unsigned short		readLittleUShort(void);
	virtual short				readBigShort(void);
	virtual unsigned short		readBigUShort(void);
	//32
	virtual int					readLittleInt(void);
	virtual unsigned int		readLittleUInt(void);
	virtual int					readBigInt(void);
	virtual unsigned int		readBigUInt(void);
	//64
	virtual long long			readLittleLong(void);
	virtual unsigned long long	readLittleULong(void);
	virtual long long			readBigLong(void);
	virtual unsigned long long	readBigULong(void);

	//Float
	virtual float	readLittleFloat(void);
	virtual float	readBigFloat(void);
};

/*
===================================================================================
btStream
===================================================================================
*/
class btStream : 
	public btRefObj//,
//	public btEndianSwap 
{
public:
	btStream(void);
	virtual ~btStream(void);

	virtual void		close(void) {};
	virtual bool		end(void) = 0;
	virtual size_t		tell(void) const = 0;
	virtual size_t		size(void) const = 0;
	virtual bool		seek(size_t offset, int whence = FS_SEEK_SET) = 0;
	virtual size_t		read(void* buf, const size_t len) = 0;
	virtual size_t		write(const void *buf, const size_t len) = 0;
	virtual bool		putstring(const char *str);
	virtual int			printf(const char *fmt, ...);

	template<class T> inline bool put(T n);
	template<class T> inline T get(void);

	virtual const Uint8* mapStream(void) const = 0;
	virtual const Uint8* mapStreamFromCurrentPos(void) const = 0;

protected:
	mutable Uint8	*m_streamMap;
};
 
template<class T>
inline bool btStream::put(T n)
{
	return write(&n, sizeof(n)) == sizeof(n);
}

template<class T>
inline T btStream::get(void)
{
	T n; 
	return read(&n, sizeof(n)) == sizeof(n) ? n : 0;
}

/*
template<class T>
inline bool btStream::putlil(T n)
{
	return false;
}

template<class T>
inline bool btStream::putbig(T n)
{
	return false;
}

template<class T>
inline T btStream::getlil(void)
{
	return T();
}

template<class T>
inline T btStream::getbig(boid)
{
	return T();
}
*/

#endif // !_STREAM_H_