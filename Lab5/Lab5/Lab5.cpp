// Lab5.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdafx.h"
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <iostream> 
#include "rlutil.h"

using namespace std;

int boss_hp = 120;
int tanker_hp = 70;
int archer1_hp = 10;
int archer2_hp = 10;
int healer_hp = 10;

DWORD WINAPI GameThreadProc(PVOID p) {  //Game
	srand(time(NULL));

	HANDLE GameSem = OpenSemaphore(SEMAPHORE_ALL_ACCESS, true, L"MyGameSem");
	if (GameSem == NULL)    GameSem = CreateSemaphore(NULL, 1, 1, L"MyGameSem");
	WaitForSingleObject(GameSem, INFINITE);

	HANDLE TankerSem = OpenSemaphore(SEMAPHORE_ALL_ACCESS, true, L"MyTankerSem");
	if (TankerSem == NULL)    TankerSem = CreateSemaphore(NULL, 1, 1, L"MyTankerSem");

	HANDLE BossSem = OpenSemaphore(SEMAPHORE_ALL_ACCESS, true, L"MyBossSem");
	if (BossSem == NULL)    BossSem = CreateSemaphore(NULL, 1, 1, L"MyBossSem");

	HANDLE Archer1Sem = OpenSemaphore(SEMAPHORE_ALL_ACCESS, true, L"MyArcher1Sem");
	if (Archer1Sem == NULL)    Archer1Sem = CreateSemaphore(NULL, 1, 1, L"MyArcher1Sem");

	HANDLE Archer2Sem = OpenSemaphore(SEMAPHORE_ALL_ACCESS, true, L"MyArcher2Sem");
	if (Archer2Sem == NULL)    Archer2Sem = CreateSemaphore(NULL, 1, 1, L"MyArcher2Sem");

	HANDLE HealerSem = OpenSemaphore(SEMAPHORE_ALL_ACCESS, true, L"MyHealerSem");
	if (HealerSem == NULL)    HealerSem = CreateSemaphore(NULL, 1, 1, L"MyHealerSem");


	printf("Tanker(%d-HP), Boss(%d-HP), Archer1(%d-HP), Archer2(%d-HP), Healer(%d-HP)\n\n", tanker_hp, boss_hp, archer1_hp, archer2_hp, healer_hp);

	rlutil::setColor(2);
	printf("\nGame:");
	rlutil::setColor(7);
	printf(" -Start!\n");
	ReleaseSemaphore(TankerSem, 1, NULL);


	rlutil::setColor(7);
	return 0;
}

DWORD WINAPI TankerThreadProc(PVOID p) {  //Tanker 

	HANDLE GameSem = OpenSemaphore(SEMAPHORE_ALL_ACCESS, true, L"MyGameSem");
	if (GameSem == NULL)    GameSem = CreateSemaphore(NULL, 1, 1, L"MyGameSem");

	HANDLE TankerSem = OpenSemaphore(SEMAPHORE_ALL_ACCESS, true, L"MyTankerSem");
	if (TankerSem == NULL)    TankerSem = CreateSemaphore(NULL, 1, 1, L"MyTankerSem");
	WaitForSingleObject(TankerSem, INFINITE);

	HANDLE BossSem = OpenSemaphore(SEMAPHORE_ALL_ACCESS, true, L"MyBossSem");
	if (BossSem == NULL)    BossSem = CreateSemaphore(NULL, 1, 1, L"MyBossSem");

	HANDLE Archer1Sem = OpenSemaphore(SEMAPHORE_ALL_ACCESS, true, L"MyArcher1Sem");
	if (Archer1Sem == NULL)    Archer1Sem = CreateSemaphore(NULL, 1, 1, L"MyArcher1Sem");

	HANDLE Archer2Sem = OpenSemaphore(SEMAPHORE_ALL_ACCESS, true, L"MyArcher2Sem");
	if (Archer2Sem == NULL)    Archer2Sem = CreateSemaphore(NULL, 1, 1, L"MyArcher2Sem");

	HANDLE HealerSem = OpenSemaphore(SEMAPHORE_ALL_ACCESS, true, L"MyHealerSem");
	if (HealerSem == NULL)    HealerSem = CreateSemaphore(NULL, 1, 1, L"MyHealerSem");

	WaitForSingleObject(TankerSem, INFINITE);  //Tanker wait for Game to be started
	if (boss_hp > 0){
		rlutil::setColor(12);
		printf("\nTanker(%d-HP):", tanker_hp);
		rlutil::setColor(7);
		printf(" -Game has been started! -Attacking boss\n");
		if (boss_hp > 0){
			boss_hp = boss_hp - 10;
		}
		ReleaseSemaphore(BossSem, 1, NULL);
		WaitForSingleObject(TankerSem, INFINITE);	//Tanker wait for Boss to attack back

		rlutil::setColor(12);
		printf("\nTanker(%d-HP):", tanker_hp);
		rlutil::setColor(7);
		printf(" -I got attacked by Boss! -Calling Archer_1 for help\n");
		ReleaseSemaphore(Archer1Sem, 1, NULL);

		WaitForSingleObject(TankerSem, INFINITE);	//Tanker wait for Archer_1 to answer

		rlutil::setColor(12);
		printf("\nTanker(%d-HP):", tanker_hp);
		rlutil::setColor(7);
		printf(" -I called Archer_1 for help! -Now calling Archer_2 for help\n");
		ReleaseSemaphore(Archer2Sem, 1, NULL);

		WaitForSingleObject(TankerSem, INFINITE);	//Tanker wait for Archer_2 to answer

		rlutil::setColor(12);
		printf("\nTanker(%d-HP):", tanker_hp);
		rlutil::setColor(7);
		printf(" -I called Archer_2 for help! -Now calling Healer for help\n");
		ReleaseSemaphore(HealerSem, 1, NULL);

		WaitForSingleObject(TankerSem, INFINITE);	//Tanker wait for Healer to answer

		rlutil::setColor(12);
		printf("\nTanker(%d-HP):", tanker_hp);
		rlutil::setColor(7);
		printf(" -I called Healer for help! -I'm healed -Now attacking Boss again\n");
		if (boss_hp > 0){
			boss_hp = boss_hp - 10;
		}
		ReleaseSemaphore(BossSem, 1, NULL);

		WaitForSingleObject(TankerSem, INFINITE);	//Tanker wait for Healer to answer
		while (boss_hp > 0){
			rlutil::setColor(12);
			printf("\nTanker(%d-HP):", tanker_hp);
			rlutil::setColor(7);
			printf(" -I got attacked by Boss! -Now attacking Boss\n");
			if (boss_hp > 0){
				boss_hp = boss_hp - 10;
			}
			if (boss_hp <= 0){
				rlutil::setColor(2);
				printf("\nGame:");
				rlutil::setColor(7);
				printf(" -Boss is DEAD!\n");
				exit(0);
			}
			if (tanker_hp <= 0){
				rlutil::setColor(2);
				printf("\nGame:");
				rlutil::setColor(7);
				printf(" -Tanker is DEAD!\n");
				exit(0);
			}
			ReleaseSemaphore(BossSem, 1, NULL);
			WaitForSingleObject(TankerSem, INFINITE);
		}

		rlutil::setColor(7);
	}  
	if (boss_hp <= 0){
		rlutil::setColor(2);
		printf("\nGame:");
		rlutil::setColor(7);
		printf(" -Boss is DEAD!\n");
		exit(0);
	}
	if (tanker_hp <= 0){
		rlutil::setColor(2);
		printf("\nGame:");
		rlutil::setColor(7);
		printf(" -Tanker is DEAD!\n");
		exit(0);
	}
	
	return 0;
}

DWORD WINAPI BossThreadProc(PVOID p) {  //Boss
	
	HANDLE GameSem = OpenSemaphore(SEMAPHORE_ALL_ACCESS, true, L"MyGameSem");
	if (GameSem == NULL)    GameSem = CreateSemaphore(NULL, 1, 1, L"MyGameSem");

	HANDLE TankerSem = OpenSemaphore(SEMAPHORE_ALL_ACCESS, true, L"MyTankerSem");
	if (TankerSem == NULL)    TankerSem = CreateSemaphore(NULL, 1, 1, L"MyTankerSem");

	HANDLE BossSem = OpenSemaphore(SEMAPHORE_ALL_ACCESS, true, L"MyBossSem");
	if (BossSem == NULL)    BossSem = CreateSemaphore(NULL, 1, 1, L"MyBossSem");
	WaitForSingleObject(BossSem, INFINITE);	//Boss wait for Tanker to attack

	HANDLE Archer1Sem = OpenSemaphore(SEMAPHORE_ALL_ACCESS, true, L"MyArcher1Sem");
	if (Archer1Sem == NULL)    Archer1Sem = CreateSemaphore(NULL, 1, 1, L"MyArcher1Sem");

	HANDLE Archer2Sem = OpenSemaphore(SEMAPHORE_ALL_ACCESS, true, L"MyArcher2Sem");
	if (Archer2Sem == NULL)    Archer2Sem = CreateSemaphore(NULL, 1, 1, L"MyArcher2Sem");

	HANDLE HealerSem = OpenSemaphore(SEMAPHORE_ALL_ACCESS, true, L"MyHealerSem");
	if (HealerSem == NULL)    HealerSem = CreateSemaphore(NULL, 1, 1, L"MyHealerSem");

	WaitForSingleObject(BossSem, INFINITE);	//Boss wait for Tanker to attack
	if (boss_hp > 0){
		rlutil::setColor(11);
		printf("\nBoss(%d-HP):", boss_hp);
		rlutil::setColor(7);
		printf("-I got attacked by Tanker! -Attacking back Tanker\n");
		if (tanker_hp > 0){
			tanker_hp = tanker_hp - 10;
		}
		ReleaseSemaphore(TankerSem, 1, NULL);
		WaitForSingleObject(BossSem, INFINITE);	//Boss wait for anyone to hit back
		if (boss_hp > 0){
			rlutil::setColor(11);
			printf("\nBoss(%d-HP):", boss_hp);
			rlutil::setColor(7);
			printf("-I got attacked by Archer_1! -Attacking back Archer_1\n");
			if (archer1_hp > 0){
				archer1_hp = archer1_hp - 10;
			}
			ReleaseSemaphore(Archer1Sem, 1, NULL);
			WaitForSingleObject(BossSem, INFINITE);	//Boss wait for anyone to hit back
		}
		else{
			rlutil::setColor(2);
			printf("\nGame:");
			rlutil::setColor(7);
			printf(" -Boss is DEAD!\n");
			return 0;
		}
		if (boss_hp > 0){
			rlutil::setColor(11);
			printf("\nBoss(%d-HP):", boss_hp);
			rlutil::setColor(7);
			printf("-I got attacked by Archer_2! -Attacking back Archer_2\n");
			if (archer2_hp > 0){
				archer2_hp = archer2_hp - 10;
			}
			ReleaseSemaphore(Archer2Sem, 1, NULL);
			WaitForSingleObject(BossSem, INFINITE);	//Boss wait for anyone to hit back
		}
		else{
			rlutil::setColor(2);
			printf("\nGame:");
			rlutil::setColor(7);
			printf(" -Boss is DEAD!\n");
			return 0;
		}
		if (boss_hp > 0){
			rlutil::setColor(11);
			printf("\nBoss(%d-HP):", boss_hp);
			rlutil::setColor(7);
			printf("-I killed Archer_1 & Archer_2! -Attacking Healer\n");
			if (healer_hp > 0){
				healer_hp = healer_hp - 10;
			}

			ReleaseSemaphore(HealerSem, 1, NULL);
			WaitForSingleObject(BossSem, INFINITE);	//Boss wait for anyone to hit back
		}
		else{
			rlutil::setColor(2);
			printf("\nGame:");
			rlutil::setColor(7);
			printf(" -Boss is DEAD!\n");
			return 0;
		}
		if (boss_hp > 0){
			rlutil::setColor(11);
			printf("\nBoss(%d-HP):", boss_hp);
			rlutil::setColor(7);
			printf("-I killed Archer_1 & Archer_2 & Healer! -Attacking Tanker again\n");
			if (tanker_hp > 0){
				tanker_hp = tanker_hp - 10;
			}

			ReleaseSemaphore(TankerSem, 1, NULL);
			WaitForSingleObject(BossSem, INFINITE);	//Boss wait for anyone to hit back
		}
		else{
			rlutil::setColor(2);
			printf("\nGame:");
			rlutil::setColor(7);
			printf(" -Boss is DEAD!\n");
			return 0;
		}
		while (tanker_hp > 0){
		 
				rlutil::setColor(11);
				printf("\nBoss(%d-HP):", boss_hp);
				rlutil::setColor(7);
				printf("-I killed Archer_1 & Archer_2 & Healer! -Attacking Tanker again\n");
				if (tanker_hp > 0){
					tanker_hp = tanker_hp - 10;
				}
				if (boss_hp <= 0){
					rlutil::setColor(2);
					printf("\nGame:");
					rlutil::setColor(7);
					printf(" -Boss is DEAD!\n");
					exit(0);
				}
				if (tanker_hp <= 0){
					rlutil::setColor(2);
					printf("\nGame:");
					rlutil::setColor(7);
					printf(" -Tanker is DEAD!\n");
					exit(0);
				}
				ReleaseSemaphore(TankerSem, 1, NULL);
				WaitForSingleObject(BossSem, INFINITE);
			 
		} 
			 
		rlutil::setColor(7);
	}
	if (boss_hp <= 0){
		rlutil::setColor(2);
		printf("\nGame:");
		rlutil::setColor(7);
		printf(" -Boss is DEAD!\n");
		exit(0);
	}
	if (tanker_hp <= 0){
		rlutil::setColor(2);
		printf("\nGame:");
		rlutil::setColor(7);
		printf(" -Tanker is DEAD!\n");
		exit(0);
	}
	 
	return 0;
}

DWORD WINAPI Archer1ThreadProc(PVOID p) {  //Archer1
	HANDLE GameSem = OpenSemaphore(SEMAPHORE_ALL_ACCESS, true, L"MyGameSem");
	if (GameSem == NULL)    GameSem = CreateSemaphore(NULL, 1, 1, L"MyGameSem");

	HANDLE TankerSem = OpenSemaphore(SEMAPHORE_ALL_ACCESS, true, L"MyTankerSem");
	if (TankerSem == NULL)    TankerSem = CreateSemaphore(NULL, 1, 1, L"MyTankerSem");

	HANDLE BossSem = OpenSemaphore(SEMAPHORE_ALL_ACCESS, true, L"MyBossSem");
	if (BossSem == NULL)    BossSem = CreateSemaphore(NULL, 1, 1, L"MyBossSem");


	HANDLE Archer1Sem = OpenSemaphore(SEMAPHORE_ALL_ACCESS, true, L"MyArcher1Sem");
	if (Archer1Sem == NULL)    Archer1Sem = CreateSemaphore(NULL, 1, 1, L"MyArcher1Sem");
	WaitForSingleObject(Archer1Sem, INFINITE);	//Archer1Sem wait for Tanker to call

	HANDLE Archer2Sem = OpenSemaphore(SEMAPHORE_ALL_ACCESS, true, L"MyArcher2Sem");
	if (Archer2Sem == NULL)    Archer2Sem = CreateSemaphore(NULL, 1, 1, L"MyArcher2Sem");

	HANDLE HealerSem = OpenSemaphore(SEMAPHORE_ALL_ACCESS, true, L"MyHealerSem");
	if (HealerSem == NULL)    HealerSem = CreateSemaphore(NULL, 1, 1, L"MyHealerSem");

	WaitForSingleObject(Archer1Sem, INFINITE);	//Archer1Sem wait for Tanker to call
	if (boss_hp > 0){
		rlutil::setColor(13);
		printf("\nArcher_1(%d-HP):", archer1_hp);
		rlutil::setColor(7);
		printf("-I got called by Tanker! -Attacking Boss\n");
		if (boss_hp > 0){
			boss_hp = boss_hp - 10;
		}

		ReleaseSemaphore(BossSem, 1, NULL);
		WaitForSingleObject(Archer1Sem, INFINITE);	//Boss wait for anyone to hit back
		rlutil::setColor(13);
		printf("\nArcher_1(%d-HP):", archer1_hp);
		rlutil::setColor(7);
		printf("-I got attacked by Boss! - I'm dead (*.*)\n");

		ReleaseSemaphore(TankerSem, 1, NULL);

		rlutil::setColor(7);
	}
	else{
		rlutil::setColor(2);
		printf("\nGame:");
		rlutil::setColor(7);
		printf(" -Boss is DEAD!\n");
	}
	return 0;
}

DWORD WINAPI Archer2ThreadProc(PVOID p) {  //Archer1
	HANDLE GameSem = OpenSemaphore(SEMAPHORE_ALL_ACCESS, true, L"MyGameSem");
	if (GameSem == NULL)    GameSem = CreateSemaphore(NULL, 1, 1, L"MyGameSem");

	HANDLE TankerSem = OpenSemaphore(SEMAPHORE_ALL_ACCESS, true, L"MyTankerSem");
	if (TankerSem == NULL)    TankerSem = CreateSemaphore(NULL, 1, 1, L"MyTankerSem");

	HANDLE BossSem = OpenSemaphore(SEMAPHORE_ALL_ACCESS, true, L"MyBossSem");
	if (BossSem == NULL)    BossSem = CreateSemaphore(NULL, 1, 1, L"MyBossSem");


	HANDLE Archer1Sem = OpenSemaphore(SEMAPHORE_ALL_ACCESS, true, L"MyArcher1Sem");
	if (Archer1Sem == NULL)    Archer1Sem = CreateSemaphore(NULL, 1, 1, L"MyArcher1Sem");

	HANDLE Archer2Sem = OpenSemaphore(SEMAPHORE_ALL_ACCESS, true, L"MyArcher2Sem");
	if (Archer2Sem == NULL)    Archer2Sem = CreateSemaphore(NULL, 1, 1, L"MyArcher2Sem");
	WaitForSingleObject(Archer2Sem, INFINITE);	//Archer2Sem wait for Tanker to call

	HANDLE HealerSem = OpenSemaphore(SEMAPHORE_ALL_ACCESS, true, L"MyHealerSem");
	if (HealerSem == NULL)    HealerSem = CreateSemaphore(NULL, 1, 1, L"MyHealerSem");

	WaitForSingleObject(Archer2Sem, INFINITE);	//Archer2Sem wait for Tanker to call
	if (boss_hp > 0){
		rlutil::setColor(14);
		printf("\nArcher_2(%d-HP):", archer2_hp);
		rlutil::setColor(7);
		printf("-I got called by Tanker! -Attacking Boss\n");
		if (boss_hp > 0){
			boss_hp = boss_hp - 10;
		}

		ReleaseSemaphore(BossSem, 1, NULL);

		WaitForSingleObject(Archer2Sem, INFINITE);	//Boss wait for anyone to hit back
		rlutil::setColor(14);
		printf("\nArcher_2(%d-HP):", archer2_hp);
		rlutil::setColor(7);
		printf("-I got attacked by Boss! - I'm dead (*.*)\n");


		ReleaseSemaphore(TankerSem, 1, NULL);


		rlutil::setColor(7);
	}
	else{
		rlutil::setColor(2);
		printf("\nGame:");
		rlutil::setColor(7);
		printf(" -Boss is DEAD!\n");
	}
	return 0;
}

DWORD WINAPI HealerThreadProc(PVOID p) {  //Archer1
	HANDLE GameSem = OpenSemaphore(SEMAPHORE_ALL_ACCESS, true, L"MyGameSem");
	if (GameSem == NULL)    GameSem = CreateSemaphore(NULL, 1, 1, L"MyGameSem");

	HANDLE TankerSem = OpenSemaphore(SEMAPHORE_ALL_ACCESS, true, L"MyTankerSem");
	if (TankerSem == NULL)    TankerSem = CreateSemaphore(NULL, 1, 1, L"MyTankerSem");

	HANDLE BossSem = OpenSemaphore(SEMAPHORE_ALL_ACCESS, true, L"MyBossSem");
	if (BossSem == NULL)    BossSem = CreateSemaphore(NULL, 1, 1, L"MyBossSem");


	HANDLE Archer1Sem = OpenSemaphore(SEMAPHORE_ALL_ACCESS, true, L"MyArcher1Sem");
	if (Archer1Sem == NULL)    Archer1Sem = CreateSemaphore(NULL, 1, 1, L"MyArcher1Sem");

	HANDLE Archer2Sem = OpenSemaphore(SEMAPHORE_ALL_ACCESS, true, L"MyArcher2Sem");
	if (Archer2Sem == NULL)    Archer2Sem = CreateSemaphore(NULL, 1, 1, L"MyArcher2Sem");

	HANDLE HealerSem = OpenSemaphore(SEMAPHORE_ALL_ACCESS, true, L"MyHealerSem");
	if (HealerSem == NULL)    HealerSem = CreateSemaphore(NULL, 1, 1, L"MyHealerSem");
	WaitForSingleObject(HealerSem, INFINITE);	//HealerSem wait for Tanker to call

	WaitForSingleObject(HealerSem, INFINITE);	//HealerSem wait for Tanker to call
	rlutil::setColor(15);
	printf("\nHealer(%d-HP):", healer_hp);
	rlutil::setColor(7);
	printf("-I got called by Tanker! -Healing Tanker\n");
	if (tanker_hp > 0){
		tanker_hp = tanker_hp + 10;
	}
	else
	{
		printf("-Tanker is dead! I can't help\n");
	}

	ReleaseSemaphore(TankerSem, 1, NULL);

	WaitForSingleObject(HealerSem, INFINITE);	//HealerSem wait for Tanker to call

	rlutil::setColor(15);
	printf("\nHealer(%d-HP):", healer_hp);
	rlutil::setColor(7);
	printf("-I got attacked by Boss! - I'm dead (*.*)\n");


	ReleaseSemaphore(TankerSem, 1, NULL);

	rlutil::setColor(7);
	return 0;
}
int _tmain(int argc, _TCHAR* argv[])
{
	DWORD id;
	HANDLE hGame = CreateThread(NULL, 0, GameThreadProc, (PVOID)1, 0, &id);
	HANDLE hTanker = CreateThread(NULL, 0, TankerThreadProc, (PVOID)2, 0, &id);
	HANDLE hBoss = CreateThread(NULL, 0, BossThreadProc, (PVOID)3, 0, &id);
	HANDLE hArcher1 = CreateThread(NULL, 0, Archer1ThreadProc, (PVOID)4, 0, &id);
	HANDLE hArcher2 = CreateThread(NULL, 0, Archer2ThreadProc, (PVOID)5, 0, &id);
	HANDLE hHealer = CreateThread(NULL, 0, HealerThreadProc, (PVOID)6, 0, &id);

	WaitForSingleObject(hGame, INFINITE);
	WaitForSingleObject(hTanker, INFINITE);
	WaitForSingleObject(hBoss, INFINITE);
	WaitForSingleObject(hArcher1, INFINITE);
	WaitForSingleObject(hArcher2, INFINITE);
	WaitForSingleObject(hHealer, INFINITE);
	 
	_gettchar();
	return 0;
}

