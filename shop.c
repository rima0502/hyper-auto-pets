#include "shop.h"

int shopInfo[MAX_SHOP_LEVEL][1 + MAX_UNIT_TIER] = {
	// cost, rate(unit A, B, C, D)
	{ 0, 100,  0,  0,  0},
	{10,  50, 50,  0,  0},
	{15,  25, 50, 25,  0},
	{25,  15, 40, 40,  5},
	{30,  10, 35, 45, 10}
};

int LastIdxUnitTier(int sl)
{
	switch (sl) {
	case 1:
		return Frog;
	case 2:
		return Cheerleader;
	case 3:
		return Magpie;
	case 4:
		return Chameleon;
	default:
		return 0;
	}
}

void SummonShop(struct unit *shop, int shopLv)
{
	srand((unsigned int)time(NULL));
	
	for (int i = 0; i < SHOP_SIZE; i++)
	{
		int randNum = rand() % 100;
		int threshold = 0;

		for (int j = 0; j < MAX_UNIT_TIER; j++)
		{
			threshold += shopInfo[shopLv - 1][j + 1];

			if (randNum < threshold)
			{
				int storeUnit = -1;
				if (j == 0)
					storeUnit = CP_Random_RangeInt(1, LastIdxUnitTier(j + 1));
				else
				{
					do
					{
						storeUnit = CP_Random_RangeInt(1 + LastIdxUnitTier(j), LastIdxUnitTier(j + 1));
					} while (storeUnit == 9);
				}
				
				/*shop[i].type = storeUnit;
				LoadUnitFromFile(&shop[i]);*/
				InitializeUnit(&shop[i], storeUnit);
				break;
			}
		}
	}
}

bool IsRefreshClicked()
{
	if (clickedrect(1200, 800, 300, 200) == 1)
		return 1;
	return 0;
}

bool IsFreezeClicked()
{
	if (clickedrect(1525, 800, 200, 200) == 1)
		return 1;	
	return 0;
}

bool IsUpgradeClicked()
{
	if (clickedrect(200, 840, 250, 100) == 1)
		return 1;
	return 0;
}

bool IsEndturnClicked()
{
	if (clickedrect(1750, 800, 200, 200) == 1)
		return 1;
	return 0;
}

void UpgradeShop()
{
	int cost = shopInfo[shopLevel][0] + upgradeShopDiscount;
	if (shopLevel < 5 && money >= cost)
	{
		money -= cost;
		shopLevel++;
	}
}