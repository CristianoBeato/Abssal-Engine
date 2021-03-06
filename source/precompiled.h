// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#ifndef _PRECOMPILED_H_
#define _PRECOMPILED_H_

#include "targetver.h"

#include <iostream>
#include <stdio.h>
#include <tchar.h>

#include <string>
#include <vector>

//include before SDL
#include "render/rs_types.h"

//SDL Utils
#include <SDL.h>

//SDL font loader
#include <SDL_ttf.h>

//system 
#include "sys/sys_main.h"
#include "sys/sys_engine.h"
#include "sys/sys_defines.h"
#include "sys/sys_console.h"
#include "sys/sys_timer.h"
#include "sys/sys_video.h"

//
#include "sys/threading/th_atomic.h"
#include "sys/threading/th_criticalSection.h"

//
#include "sys/fileSystem/fs_stream.h"
#include "sys/fileSystem/fs_file.h"

//
#include "sys/memory/mem_pointers.h"
#include "sys/memory/mem_alloc.h"
#include "sys/memory/mem_blockAlloc.h"

//
#include "sys/inputHandler/in_handler.h"

//
#include "framework/dictionary.h"
#include "framework/configuration.h"
#include "framework/string.h"

//renderer
#include "render/rs_renderSystem.h"
#include "render/image/textureManager.h"
#include "render/geometry/vertexBuffer.h"
#include "render/text/fontManager.h"
#include "render/shader/shaderManager.h"
#include "render/gui/gui.h"

//game logic
#include "gameLogic/lgc_object.h"
#include "gameLogic/lgc_level.h"

#endif // !_PRECOMPILED_H_