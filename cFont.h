#pragma once

class cFont
{
private:
	LPDIRECT3DDEVICE9 pDevice = nullptr;
	LPD3DXFONT pFont = nullptr;
	bool valid = false;

public:
	cFont(LPDIRECT3DDEVICE9& pDevice, LPCWSTR wszFontName, int iSize);
	~cFont();

	void Print(LPCWSTR wszText, int x, int y, D3DCOLOR color, DWORD dwLado = DT_CENTER);
	void Clean();

	LONG GetTextWidth(LPCWSTR wszText) const;
	D3DXFONT_DESC GetFontDetails() const;
};
