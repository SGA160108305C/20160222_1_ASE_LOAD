#pragma once
#include <Windows.h>
#include <Windowsx.h>

#include <assert.h>

#include <list>
#include <map>
#include <vector>
#include <string>

#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

#include "MemoryLeakCheck.h"

#include "FVF.h"
#include "Triangle.h"
#include "Grid.h"

#include "GameObject.h"
#include "CubeMan.h"
#include "CubeMan_Light.h"

#include "Obj.h"

#include "Font.h"
#include "RandomUtil.h"

#include "TextureManager.h"
#include "GameStateManager.h"
#include "GameManager.h"

#pragma comment(lib, "winmm.lib")


LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);

static const WCHAR WINDOW_CLASS_NAME[] = L"Win32App";
static const WCHAR WINDOW_TITLE_CAPTION[] = L"SGA 3D";

static const unsigned int RESOLUTION_X = 1280;
static const unsigned int RESOLUTION_Y = 720;


template<typename T>
ULONG SAFE_RELEASE(T& object)
{
	ULONG result = 0;
	if ( object )
	{
		result = object->Release();
		object = nullptr;
	}
	return result;
}

template<typename T>
void SAFE_DELETE(T& object)
{
	if ( object )
	{
		object->Destroy();
		delete object;
		object = nullptr;
	}
}

template<typename T>
void SAFE_ARRAY_DELETE(T& object, UINT32 arrayCount)
{
	if ( object )
	{
		for ( int i = 0; i < arrayCount; ++i )
		{
			object[i]->Destroy();
		}
		delete [] object;
		object = nullptr;
	}
}

template<typename T>
void SAFE_DELETE_ARRAY_ONLY(T& object)
{
	if ( object )
	{
		delete [] object;
		object = nullptr;
	}
}