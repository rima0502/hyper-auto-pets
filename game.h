#pragma once
#include "clickobject.h"
#include "cprocessing.h"
#include "drawunit.h"
#include "shop.h"
#include "unit.h"
#include "stage.h"

void game_init(void);
void game_update(void);
void game_exit(void);


void summonshop();
int checkstorelist(int sl);
void Drawspidertext(float posx, float posy);
void Drawunittext(float posx, float posy, int type);
void Callswap(int myId, int otherId, int size); 
void BuyUnit(int shopID, int teamID, int sizeshop, int sizeteam);

extern int money;
extern int Playerlife;
extern int stage;
extern int storelevel;
extern int select;

extern struct unit shop[3];
extern struct unit team[4];
extern struct unit enemy[4];
extern struct unit fightteam[4];