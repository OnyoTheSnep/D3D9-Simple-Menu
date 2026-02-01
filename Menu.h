#pragma once

#define MAX_ITEMS				16
#define FONT_NAME				L"Tahoma" // L"JetBrains Mono"
#define FONT_SIZE				22
#define MAX_ITEM_VALUE_SIZE		128

enum ItemType
{
	NONE,
	DATA_BOOL,
	DATA_INT,
	DATA_FLOAT,
	DATA_STR_VEC
};

struct Item
{
	wchar_t* szText;
	void* pValue = nullptr;
	void* callback = nullptr;
	
	ItemType type = NONE;
	int min = 0;
	int max = 1;
	vector<const wchar_t*> *strVec = nullptr;
};

class Menu
{
private:
	LPDIRECT3DDEVICE9 pDevice = nullptr;
	Item* items = nullptr;
	int count = 0;
	int cursor = 0;
	cFont* font;
	struct
	{
		bool bMenuVisible = true;
		int startX = 20;
		int startY = 20;
	} l_stConfig;
	DWORD dwLastTickKeyboard = 0;
	//	DWORD dwMSDelay = 100; // Constant ?


public:
	Menu(LPDIRECT3DDEVICE9& pDevice);
	~Menu();

	void ToggleVisible();
	void AddHeader(const wchar_t* wszText);
	void AddItem(const wchar_t* wszText, void* pValue, ItemType type, int min = 0, int max = 1, void* callback = nullptr);
	void AddItem(const wchar_t* wszText, void* pValue, ItemType type, vector<const wchar_t*>& strVec, void* callback = nullptr);

	void Render() const;
	void Clear();

	void KeyboardCapture(DWORD dwMSDelay);
};
