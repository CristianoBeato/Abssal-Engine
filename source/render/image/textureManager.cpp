
#include "precompiled.h"
#pragma hdrstop

#include "textureManager.h"

btTextureManager::btTextureManager(void)
{
}

btTextureManager::~btTextureManager(void)
{
}

void btTextureManager::startUp(void)
{
}

void btTextureManager::shutDonw(void)
{
}

void btTextureManager::clear(void)
{
}

void btTextureManager::reload(void)
{
}

void btTextureManager::purgeTexture(const std::string textureName)
{
}

void btTextureManager::purgeTexture(const Uint32 textureHash)
{
}

btIntrusivePtr<btTexture> btTextureManager::getAsyncTexture(const std::string textureName)
{
	return btIntrusivePtr<btTexture>();
}

btIntrusivePtr<btTexture> btTextureManager::getAsyncTexture(const Uint32 textureHash)
{
	return btIntrusivePtr<btTexture>();
}

btIntrusivePtr<btTexture> btTextureManager::getTexture(const std::string textureName)
{
	return btIntrusivePtr<btTexture>();
}

btIntrusivePtr<btTexture> btTextureManager::getTexture(const Uint32 textureHash)
{
	return btIntrusivePtr<btTexture>();
}
