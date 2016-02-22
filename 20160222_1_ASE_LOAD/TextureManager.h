#pragma once
#include <vector>

class TextureManager
{
private:
	TextureManager();
	TextureManager(const TextureManager& other);
	~TextureManager();

public:
	static TextureManager& Get()
	{
		static TextureManager instance;
		return instance;
	}
	
	void Destroy();

	static inline LPDIRECT3DTEXTURE9 GetTexture(char* fileName, D3DXIMAGE_INFO* imageInfo = nullptr){ return TextureManager::Get().GetInstanceTexture(fileName, imageInfo); }
	static inline LPDIRECT3DTEXTURE9 GetTexture(const char* path, const char* fileName){ return TextureManager::Get().GetInstanceTexture(path, fileName); }
		

private:
	const char* TEXTURE_DIRECTORY = "./Data/Texture/";
	
	//std::map<std::string, LPDIRECT3DTEXTURE9> textureMap;
	//std::map<std::string, D3DXIMAGE_INFO> imageInfoMap;
	std::map<std::string, std::pair<LPDIRECT3DTEXTURE9, D3DXIMAGE_INFO>> textureDataMap;
	
	LPDIRECT3DTEXTURE9 GetInstanceTexture(char* fileName, D3DXIMAGE_INFO* imageInfo = nullptr);
	LPDIRECT3DTEXTURE9 GetInstanceTexture(const char* path, const char* fileName);
};

