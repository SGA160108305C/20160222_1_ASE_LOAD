#include "stdafx.h"
#include "TextureManager.h"


TextureManager::TextureManager()
{
}


TextureManager::~TextureManager()
{
}

//LPDIRECT3DTEXTURE9 TextureManager::GetInstanceTexture(char* fileName)
//{
//	if (textureMap.find(fileName) == textureMap.end())
//	{
//		char fullPath[512];
//		strcpy_s(fullPath, TEXTURE_DIRECTORY);
//		strcat_s(fullPath, fileName);
//
//		D3DXCreateTextureFromFileA(GameManager::GetDevice(), fullPath, &textureMap[fileName]);
//	}
//	return textureMap[fileName];
//}

LPDIRECT3DTEXTURE9 TextureManager::GetInstanceTexture(char* fileName, D3DXIMAGE_INFO* imageInfo)
{
	if ( textureDataMap.find(fileName) == textureDataMap.end() )
	{
		char fullPath[512];
		strcpy_s(fullPath, TEXTURE_DIRECTORY);
		strcat_s(fullPath, fileName);

		D3DXCreateTextureFromFileExA(
			GameManager::GetDevice(),
			fullPath,
			D3DX_DEFAULT_NONPOW2,
			D3DX_DEFAULT_NONPOW2,
			D3DX_DEFAULT,
			0,
			D3DFMT_UNKNOWN,
			D3DPOOL_MANAGED,
			D3DX_FILTER_NONE,
			D3DX_DEFAULT,
			0,
			&textureDataMap[fileName].second,
			nullptr,
			&textureDataMap[fileName].first);
	}

	if ( imageInfo )
	{
		*imageInfo = textureDataMap[fileName].second;
	}

	return textureDataMap[fileName].first;
}

void TextureManager::Destroy()
{
	for ( auto iter = textureDataMap.begin(); iter != textureDataMap.end(); ++iter )
	{
		SAFE_RELEASE(iter->second.first);
	}
	textureDataMap.clear();
}

LPDIRECT3DTEXTURE9 TextureManager::GetInstanceTexture(const char* path, const char* fileName)
{
	if ( textureDataMap.find(fileName) == textureDataMap.end() )
	{
		char fullPath[512];
		strcpy_s(fullPath, path);
		strcat_s(fullPath, fileName);

		D3DXCreateTextureFromFileExA(
			GameManager::GetDevice(),
			fullPath,
			D3DX_DEFAULT_NONPOW2,
			D3DX_DEFAULT_NONPOW2,
			D3DX_DEFAULT,
			0,
			D3DFMT_UNKNOWN,
			D3DPOOL_MANAGED,
			D3DX_FILTER_NONE,
			D3DX_DEFAULT,
			0,
			&textureDataMap[fileName].second,
			nullptr,
			&textureDataMap[fileName].first);
	}
	return textureDataMap[fileName].first;
}