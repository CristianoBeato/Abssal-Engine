#include "precompiled.h"
#pragma hdrstop

#include "fs_stream.h"

/*
===================================================================================

btEndianSwap: Endianess swap helper functions

===================================================================================
*/

short btEndianSwap::readLittleShort(void)
{
	short s = 0;
	read(&s, sizeof(s));
	return SDL_SwapLE16(s);
}

unsigned short btEndianSwap::readLittleUShort(void)
{
	unsigned short s = 0;
	read(&s, sizeof(s));
	return SDL_SwapLE16(s);
}

short  btEndianSwap::readBigShort(void)
{
	short s = 0;
	read(&s, sizeof(s));
	return SDL_SwapBE16(s);
}

unsigned short btEndianSwap::readBigUShort(void)
{
	unsigned short s = 0;
	read(&s, sizeof(s));
	return SDL_SwapBE16(s);
}

int btEndianSwap::readLittleInt(void)
{
	int i = 0;
	read(&i, sizeof(i));
	return SDL_SwapLE32(i);
}

unsigned int btEndianSwap::readLittleUInt(void)
{
	unsigned int i = 0;
	read(&i, sizeof(i));
	return SDL_SwapLE32(i);
}

int btEndianSwap::readBigInt(void)
{
	int i = 0;
	read(&i, sizeof(i));
	return SDL_SwapBE32(i);
}

unsigned int btEndianSwap::readBigUInt(void)
{
	unsigned int  i = 0;
	read(&i, sizeof(i));
	return SDL_SwapBE32(i);
}

long long btEndianSwap::readLittleLong(void)
{
	long long l = 0;
	read(&l, sizeof(l));
	return SDL_SwapBE64(l);
}

unsigned long long btEndianSwap::readLittleULong(void)
{
	unsigned long long l = 0;
	read(&l, sizeof(l));
	return SDL_SwapBE64(l);
}

long long btEndianSwap::readBigLong(void)
{
	long long l = 0;
	read(&l, sizeof(l));
	return SDL_SwapBE64(l);
}

unsigned long long btEndianSwap::readBigULong(void)
{
	unsigned long long l = 0;
	read(&l, sizeof(l));
	return SDL_SwapBE64(l);
}

float btEndianSwap::readLittleFloat(void)
{
	float f = 0.0f;
	read(&f, sizeof(f));
	return SDL_SwapFloatLE(f);
}

float btEndianSwap::readBigFloat(void)
{
	float f = 0.0f;
	read(&f, sizeof(f));
	return SDL_SwapFloatBE(f);
}

/*
===================================================================================

btStream: Abstract class of file stream

===================================================================================
*/
btStream::btStream(void) : m_streamMap(NULL)
{
}

btStream::~btStream(void)
{
	close();
}

bool btStream::putstring(const char * str)
{
	size_t len = SDL_strlen(str);
	return write(str, len) == len;
}

int btStream::printf(const char * fmt, ...)
{
	char msg[MAX_PRINT_MSG_SIZE];
	va_list v;

	va_start(v, fmt);
	int result =  SDL_vsnprintf(msg, MAX_PRINT_MSG_SIZE, fmt, v);
	va_end(v);
	putstring(msg);

	return result;
}
