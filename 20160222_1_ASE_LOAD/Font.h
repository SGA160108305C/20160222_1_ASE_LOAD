#pragma once
class Font
{
private:
	Font();
	Font(const Font& other);
	~Font();

public :
	static Font& Get()
	{
		static Font instance;
		return instance;
	}

	void Initialize();
	void Destroy();

	static inline LPD3DXFONT GetFont(){ return Font::Get().GetInstanceFont(); }

protected:
	LPD3DXFONT font = nullptr;

	inline LPD3DXFONT GetInstanceFont(){ return font; }

	

};

