#include "main.h"

static SlideAnim slide(5.0f, 1000.0f);

Menu::Menu(LPDIRECT3DDEVICE9& pDevice)
{
	this->pDevice = pDevice;
	font = new cFont(pDevice, FONT_NAME, FONT_SIZE);

	items = new Item[MAX_ITEMS];
	count = 0;
}

Menu::~Menu()
{
	delete[] items;
}

void Menu::ToggleVisible()
{
	l_stConfig.bMenuVisible = !l_stConfig.bMenuVisible;
}

void Menu::AddHeader(const wchar_t* wszText)
{
	if (items == nullptr || count >= MAX_ITEMS)
		return;

	Item& curr = items[count++];

	int wsize = wcslen(wszText) + 1;
	curr.szText = new wchar_t[wsize];
	memset(curr.szText, 0, wsize);
	wcscpy_s(curr.szText, wsize, wszText);

	curr.type = ItemType::NONE;
}

void Menu::AddItem(const wchar_t* wszText, void* pValue, ItemType type, int min, int max, void* callback)
{
	if (items == nullptr || count >= MAX_ITEMS)
		return;

	Item& curr = items[count++];

	int wsize = wcslen(wszText) + 1;
	curr.szText = new wchar_t[wsize];
	memset(curr.szText, 0, wsize);
	wcscpy_s(curr.szText, wsize, wszText);

	curr.pValue = pValue;
	curr.type = type;
	curr.callback = callback;
	curr.min = min;
	curr.max = max;
	curr.strVec = nullptr;
}

void Menu::AddItem(const wchar_t* wszText, void* pValue, ItemType type, vector<const wchar_t*>& strVec, void* callback)
{
	if (items == nullptr || count >= MAX_ITEMS)
		return;

	Item& curr = items[count++];

	int wsize = wcslen(wszText) + 1;
	curr.szText = new wchar_t[wsize];
	memset(curr.szText, 0, wsize);
	wcscpy_s(curr.szText, wsize, wszText);

	curr.pValue = pValue;
	curr.type = type;
	curr.callback = callback;
	curr.min = 0;
	curr.max = strVec.size() - 1;
	curr.strVec = &strVec;
}

void Menu::Render() const
{
	if (pDevice == nullptr)
		return;

	if (!l_stConfig.bMenuVisible)
		return;

	static int max_width = 0;
	const int spacing = 20;
	for (int i = 0; i < count; i++)
	{
		Item& item = items[i];

		const D3DCOLOR WHITE = D3DCOLOR_ARGB(255, 255, 255, 255);
		D3DCOLOR color = WHITE;
//		if(item.type == ItemType::DATA_BOOL && static_cast<bool*>(item.pValue) != nullptr)
//			if(*static_cast<bool*>(item.pValue) == true)
//				color = D3DCOLOR_ARGB(255 - (21 * slide.OffsetPx()), 11, 81, 218);

		if (cursor == i)
			color = D3DCOLOR_ARGB(255 - (21 * slide.OffsetPx()), 11, 218, 81);

		int newY = (FONT_SIZE + 1) * i;

		font->Print(item.szText, l_stConfig.startX, (l_stConfig.startY + newY), WHITE, DT_LEFT);

		if (cursor == i && count > 0)
		{
			//const wchar_t* c = L"\u25B6";
			const wchar_t* c = L">";
			int txt_width = this->font->GetTextWidth(c);
			int newX = ((l_stConfig.startX - txt_width) - 3) + -slide.OffsetPx();
			font->Print(c, newX, (l_stConfig.startY + newY), WHITE, DT_LEFT);
		}

		if (font->GetTextWidth(item.szText) > max_width)
			max_width = font->GetTextWidth(item.szText);

		wchar_t buf[MAX_ITEM_VALUE_SIZE];
		memset(buf, 0, MAX_ITEM_VALUE_SIZE);
		if (item.type != ItemType::NONE)
		{
			bool* bVal = nullptr;
			int* iVal = nullptr;
			float* fVal = nullptr;
			vector<wchar_t>* pVec = nullptr;

			switch (item.type)
			{
			case DATA_BOOL:
				bVal = static_cast<bool*>(item.pValue);
				if(bVal != nullptr)
					swprintf_s(buf, L"%ls", (*bVal ? L"On" : L"Off"));
				else swprintf_s(buf, L"nullptr");
				break;

			case DATA_INT:
				iVal = static_cast<int*>(item.pValue);
				if (iVal != nullptr)
					swprintf_s(buf, L"%d", *iVal);
				else swprintf_s(buf, L"nullptr");
				break;

			case DATA_FLOAT:
				fVal = static_cast<float*>(item.pValue);
				if (fVal != nullptr)
					swprintf_s(buf, L"%.3f", *fVal);
				else swprintf_s(buf, L"nullptr");
				break;

			case DATA_STR_VEC:
				iVal = static_cast<int*>(item.pValue);
				if (iVal != nullptr)
					swprintf_s(buf, L"%ls", item.strVec->at(*iVal));
				else swprintf_s(buf, L"nullptr");

				break;
			}
			font->Print(buf, l_stConfig.startX + max_width + spacing, (l_stConfig.startY + newY), color, DT_LEFT);
		}
		
	}

}

void Menu::Clear()
{
	// ??
}


#define bIsPressed(x) (GetAsyncKeyState(x) & 0x8000) != 0 ? true : false
#define CommitClick   dwLastTickKeyboard = GetTickCount(); return;
void Menu::KeyboardCapture(DWORD dwMSDelay)
{
	if ((GetTickCount() - dwLastTickKeyboard) < dwMSDelay)
		return;

	bool bInsertPressed	= bIsPressed(VK_INSERT);
	bool bUpPressed		= bIsPressed(VK_UP);
	bool bDownPressed	= bIsPressed(VK_DOWN);
	bool bRightPressed	= bIsPressed(VK_RIGHT);
	bool bLeftPressed	= bIsPressed(VK_LEFT);

	if (bInsertPressed)
	{
		ToggleVisible();
		CommitClick
	}

	if (!l_stConfig.bMenuVisible)
		return;

	if (count > 1)
	{
		if (bUpPressed)
		{
			if (cursor == 0)
				cursor = count - 1;
			else cursor--;
			CommitClick
		}
		else if (bDownPressed)
		{
			if ((cursor + 1) == count)
				cursor = 0;
			else cursor++;
			CommitClick
		}
	}

	if (count >= 1)
	{
		Item& item = items[cursor];
		bool* bVal = nullptr;
		int* iVal = nullptr;
		float* fVal = nullptr;

		if (bRightPressed || bLeftPressed)
		{
			switch (item.type)
			{
			case ItemType::DATA_BOOL:
				bVal = static_cast<bool*>(item.pValue);
				if (bVal != nullptr)
				{
					*bVal = !*bVal;
					CommitClick
				}
				break;

			case ItemType::DATA_INT:
			case ItemType::DATA_STR_VEC:
				iVal = static_cast<int*>(item.pValue);
				if (iVal != nullptr)
				{
					if (bRightPressed)
					{
						if (*iVal + 1 > item.max)
							*iVal = item.min;
						else *iVal += 1;
					}
					else if (bLeftPressed)
					{
						if (*iVal - 1 < item.min)
							*iVal = item.max;
						else *iVal -= 1;
					}
					CommitClick
				}
				break;

			case ItemType::DATA_FLOAT:
				fVal = static_cast<float*>(item.pValue);
				if (fVal != nullptr)
				{
					if (bRightPressed)
					{
						if (*fVal + 0.1f > item.max)
							*fVal = (float)item.min;
						else *fVal += 0.1f;
					}
					else if (bLeftPressed)
					{
						if (*fVal - 0.1f < item.min)
							*fVal = (float)item.max;
						else *fVal -= 0.1f;
					}
					CommitClick
				}
				break;
			}
		}
	}
}

