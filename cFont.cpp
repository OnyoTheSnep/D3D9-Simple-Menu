#include "main.h"

cFont::cFont(LPDIRECT3DDEVICE9& pDevice, LPCWSTR wszFontName, int iSize)
{
	if (pDevice == nullptr || wszFontName == nullptr || lstrlenW(wszFontName) == 0)
		return;

	this->pDevice = pDevice;

	if (FAILED(D3DXCreateFontW(pDevice, iSize, 0, 400, 1, 0, 1, 0, 4, 0 | (0 << 4), wszFontName, &this->pFont)))
		return;

	valid = true;
}

cFont::~cFont()
{
	delete pFont;
}

void cFont::Print(LPCWSTR wszText, int x, int y, D3DCOLOR color, DWORD dwLado)
{
	RECT pos;
	SetRect(&pos, x, y, x, y);

	this->pFont->DrawTextW(nullptr, wszText, -1, &pos, dwLado | DT_NOCLIP, color);
}

void cFont::Clean()
{
	pFont->Release();
	pFont = nullptr;
}

LONG cFont::GetTextWidth(LPCWSTR wszText) const
{
	if (pFont == nullptr)
		return -1;

	RECT rcRect = { 0 ,0 ,0 ,0 };
	this->pFont->DrawTextW(nullptr, wszText, lstrlenW(wszText), &rcRect, DT_CALCRECT, NULL);
	LONG res = (rcRect.right - rcRect.left);

	return res;
}

D3DXFONT_DESC cFont::GetFontDetails() const
{
	D3DXFONT_DESC d3dFontDesc;
	pFont->GetDesc(&d3dFontDesc);
	return d3dFontDesc;
}