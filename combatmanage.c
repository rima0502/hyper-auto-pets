#include "combatmanage.h"

void summonenemyteam(int whichstage)
{
	for (int i = 0; i < 4; i++)
	{
		enemy[i].type = 0;
		LoadUnitFromFile(&enemy[i]);
	}
	int buffer[4] = { 0 };
	for (int j = 1; j < 11; j++)
	{
		for (int i = 0; i < 4; i++)
		{
			if (whichstage == j)
			{
				buffer[i] = CP_Random_RangeInt(j * 2 - 3 + 1, j * 2 + 1);
				--buffer[i];
			}
		}
	}
	if (buffer[0] <= 0 && buffer[1] <= 0 && buffer[2] <= 0 && buffer[3] <= 0)
	{
		buffer[0] = 1;
	}
	int j = 0;
	for (int i = 0; i < 4; i++)
	{
		if (buffer[i] > 0) 
		{
			enemy[j].type = buffer[i];
			LoadUnitFromFile(&enemy[j]);
			j++;
		}
	}
}
void hit()
{
	fightteam[3].life -= enemy[0].att;
	enemy[0].life -= fightteam[3].att;
}
int checkdead()
{
	if (fightteam[3].life <= 0 && enemy[0].life <= 0) // both dead
		return 0;
	if (fightteam[3].life > 0 && enemy[0].life <= 0) // enemy dead, team alive
		return 1;
	if (fightteam[3].life <= 0 && enemy[0].life > 0) // enemy alive, team dead
		return 2;
	if (fightteam[3].life > 0 && enemy[0].life > 0) // both alive
		return 3;
	return -1;
}


// Todo team type [1, 0, 0, 1] => [0, 0, 1, 1] 
void fillin_emptyslot(struct unit* abc, int enemyT)// enemy 1 team 0
{
	if (abc[1].type == 0 && abc[2].type == 0)
	{
		if (enemyT == 0) // team
		{
			abc[2] = abc[0];
			abc[0].type = 0;
		}
		else if (enemyT == 1) // enemy
		{
			abc[1] = abc[3];
			abc[3].type = 0;
		}
	}

	if (enemyT == 0) // team
	{
		for (int i = 3; i > 0; i--)
		{
			if (abc[i].type == 0)
			{
				abc[i] = abc[i - 1];
				abc[i].time = 0;
				abc[i - 1].type = 0;

			}
		}
	}
	else if (enemyT == 1) // enemy
	{
		for (int i = 0; i < 3; i++)
		{
			if (abc[i].type == 0)
			{
				abc[i] = abc[i + 1];
				abc[i].time = 0;
				abc[i + 1].type = 0;
			}
		}
	}
}

void CheckHit()
{
	if (1 <= fightteam[3].time)
	{
		hit();
		if (checkdead() == 0)
		{
			fightteam[3].type = 0;
			enemy[0].type = 0;
		}
		if (checkdead() == 1)
		{
			enemy[0].type = 0;
		}
		if (checkdead() == 2)
		{
			fightteam[3].type = 0;
		}

		fightteam[3].time = 0;
		enemy[0].time = 0;
	}
}

void timer()
{
	for (int i = 0; i < 4; i++)
	{
		fightteam[i].time += CP_System_GetDt();
		enemy[i].time += CP_System_GetDt();
	}
}

int checkcombatover()
{
	int t = 0;
	for (int i = 0; i < 4; i++) {
		if (fightteam[i].type == 0)
			t++;
	}
	int e = 0;
	for (int i = 0; i < 4; i++) {
		if (enemy[i].type == 0)
			e++;
	}

	if (e == 4 && t == 4)//draw
	{
		givemoneystage();
		CP_Engine_SetNextGameState(game_init, game_update, game_exit);
		return 2;
	}
	if (t == 4)//lose
	{
		givemoneystage();
		Playerlife -= 1;
		CP_Engine_SetNextGameState(game_init, game_update, game_exit);
		return 0;
	}
	if (e == 4)//win
	{	
		stage++;
		givemoneystage();
		CP_Engine_SetNextGameState(game_init, game_update, game_exit);
		return 1;
	}
	return -1;
}
void teamintofightteam()
{
	for (int i = 0; i < 4; i++)
	{
		fightteam[i] = team[i];
	}
}
void givemoneystage()
{

	switch (stage)
	{
	case 1:
		money = money;
		break;
	case 2:
		money += 2;
		break;
	case 3:
		money += 4;
		break;
	case 4:
		money += 8;
		break;
	case 5:
		money += 10;
		break;
	case 6:
		money += 12;
		break;
	case 7:
		money += 14;
		break;
	case 8:
		money += 16;
		break;
	case 9:
		money += 18;
		break;
	case 10:
		money += 20;
		break;
	}

}