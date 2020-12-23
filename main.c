#pragma warning(disable : 4996)

#include<stdlib.h>
#include<signal.h>
#include<time.h>
#include<stdio.h>
#include<locale.h>
#include"models.h"
#include"functions.h"
#include"date.h"
#include"filemanager.h"
#include"membermanager.h"
#include"main.h"

int elemszelessegek[6] = { 6, 20, 14, 40, 14, 12 };

#pragma region main
// ^((|\./)beadando1(.exe|) [filename.csv [2017.09.01 [1]]])$
//                          ^ filename    ^ date      ^ selected action
int main(int argc, char* argv[]) {
	setlocale(LC_ALL, ".utf8");
#if _WIN32
	system("TITLE Véradó nyílvántartás");
#endif
	clear_screen();
	header(); 
	char *fileName = (char*)malloc(sizeof(char)*256);
	char * currentDate = (char*)malloc(sizeof(char)*256);
	verado* veradok = NULL;
	verado* selected; int selected_hossz = 0;
	bool db_changed = false;
	int hossz = 0, eredeti_hossz = 0, ujra, selectedAction=-1;
	if (argc >= 2) fileName = argv[1];
	if (argc >= 3 && str_length(argv[2]) == 11) currentDate = argv[2];
	if (argc >= 4) selectedAction = atoi(argv[3]);
	while (!is_valid_date(currentDate))
	{
		colored_printf(0, "§bAdja meg a jelenlegi dátumot (írjon be kötőjelet §2-§b az aktuális dátum használatához): §e"); scanf(" %s", currentDate);
		if (str_equals(currentDate, "-", false)) {
			time_t t = time(NULL);
			struct tm tm = *localtime(&t);
			sprintf(currentDate, "%04d.%02d.%02d.", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
		}
		colored_printf(0, "§r");
	}

	while (ujra = readFile(fileName, &veradok, &hossz, argc >= 2))
	{
		if (ujra == 2) { return 0; }
	}
	eredeti_hossz = hossz;
	do
	{
		clear_screen();
		header();

		colored_printf(0, "\t§3Elérhető műveletek:\r\n");
		colored_printf(0, "\t§3----------------------------------------------------------------------------\r\n");
		colored_printf(0, "\t§31.§f Tagok megtekintése.\r\n");
		colored_printf(0, "\t§32.§f Új tag felvitele.\r\n");
		colored_printf(0, "\t§33.§f Vércsoportra keresés, az adott vércsoportú tagok számára névre szóló,\r\n\t   véradásra felkérő emailek összeállítása, fájlba írása, ahol a fájl(ok)\r\n\t   neve(i) a címzett(ek) email címe(i), valamint, megelőlegezvén a bizalmat,\r\n\t   véradás - számuk és legutóbbi véradás dátumuk felülírása a program és a \r\n\t   nyilvántartást dokumentáló fájl listájában is.\r\n");
		colored_printf(0, "\n");

		switch (action(1, 3, selectedAction))
		{
		case 1:
			display_members(veradok, hossz, elemszelessegek);
			break;
		case 2:
			add_new_member(&veradok, hossz, &hossz);
			break;
		case 3:
			select_members_by_blood_type(veradok, hossz, &selected, &selected_hossz, elemszelessegek, currentDate);
			db_changed = true;
			for (int i = 0; i < selected_hossz; i++)
			{
				int suspected_id = selected[i].id - 1;
				veradok[suspected_id].hanyszor++;
				strcpy(&*veradok[suspected_id].legutolso, currentDate);
			}
			selected = NULL;
			break;
		default:
			break;
		}

		selectedAction = -1;
	} while (once_again_msg("§bSzeretné folytatni a program futtatását?"));

	if (eredeti_hossz != hossz || db_changed) changes_were_made(fileName, veradok, hossz); 
	//if(!(veradok == NULL)) free(veradok);
	argv = NULL;
	currentDate = NULL;
	fileName = NULL;
	free(veradok);
	veradok = NULL;

	return 0;
}
#pragma endregion

#pragma region changes_were_made
void changes_were_made(char* fileName, verado* veradok, int hossz) {
	clear_screen();
	header();
	if(once_again_msg("§3Változások történtek a nyílvántartásban. Kilépés előtt menteni szeretné ezeket?")) 
		writeFile(fileName, veradok, hossz);
}
#pragma endregion

#pragma warning( pop )