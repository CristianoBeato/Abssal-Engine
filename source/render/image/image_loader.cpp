
#include "precompiled.h"
#pragma hdrstop

#include "image_loader.h"

btImageLoader::btImageLoader(void)
{
}

btImageLoader::~btImageLoader(void)
{
}

bool btImageLoader::loadFromSDLSurface(const btIntrusivePtr<SDL_Surface> src)
{
	return false;
}

btIntrusivePtr<SDL_Surface> btImageLoader::getSDLSurface(void)
{
	return btIntrusivePtr<SDL_Surface>();
}

btImageLoader::imageDepth btImageLoader::getDepth(void) const
{
	return m_colorDepth;
}

void btImageLoader::getSize(Uint32 & width, Uint32 & height, Uint32 & depth)
{
}
