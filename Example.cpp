#include "main.h"

bool x0 = false;
bool x1 = true;
int x2 = 0;
int x3 = 1;
int x4 = 2;
float x5 = 0.0f;
float x6 = 0.1f;
int x7 = 0;

vector<const wchar_t*> arr = {
    L"AAA",
    L"BBB",
    L"CCC",
    L"DDD",
    L"EEE"
};

bool bOnce = false;
void doOnce(Menu *menu)
{
    if (bOnce)
        return;

    menu = new Menu(d3ddev);
    menu->AddItem(L"Item 0", (void*)&x0, ItemType::DATA_BOOL);
    menu->AddItem(L"Item 1", (void*)&x1, ItemType::DATA_BOOL);
    menu->AddItem(L"Item 2", (void*)&x2, ItemType::DATA_INT);
    menu->AddItem(L"Item 3", (void*)&x3, ItemType::DATA_INT, -10, 10);
    menu->AddItem(L"Item 4", (void*)&x4, ItemType::DATA_INT, 0, 10);
    menu->AddItem(L"Item 5", (void*)&x5, ItemType::DATA_FLOAT);
    menu->AddItem(L"Item 6", (void*)&x6, ItemType::DATA_FLOAT);
    menu->AddItem(L"Item 7", (void*)&x7, ItemType::DATA_STR_VEC, arr, nullptr);
    menu->AddItem(L"...", (void*)&x2, ItemType::NONE);

    bOnce = true;
}