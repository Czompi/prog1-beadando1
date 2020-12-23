#pragma once
#include"externalsources.h"
#include"c_string.h"
#include"functions.h"

#pragma region display_members
void display_members(verado* veradok, int hossz, int* elemszelessegek) {
	clear_screen();
	header();
	colored_printf(0, "§3");

#pragma region Header
	printf("%s%s", "Id", str_repeat(" ", (int)(elemszelessegek[0] - 2)));
	printf("%s%s", "Név", str_repeat(" ", (int)(elemszelessegek[1] - 3)));
	printf("%s%s", "Vércsoport", str_repeat(" ", (int)(elemszelessegek[2] - 10)));
	printf("%s%s", "Email", str_repeat(" ", (int)(elemszelessegek[3] - 5)));
	printf("%s%s", "Véradások", str_repeat(" ", (int)(elemszelessegek[4] - 9)));
	printf("%s%s", "Legutolsó", str_repeat(" ", (int)(elemszelessegek[5] - 9)));
	printf("%s", "\n");

	printf("%s%s", str_repeat("-", elemszelessegek[0] - 1), " ");
	printf("%s%s", str_repeat("-", elemszelessegek[1] - 1), " ");
	printf("%s%s", str_repeat("-", elemszelessegek[2] - 1), " ");
	printf("%s%s", str_repeat("-", elemszelessegek[3] - 1), " ");
	printf("%s%s", str_repeat("-", elemszelessegek[4] - 1), " ");
	printf("%s%s", str_repeat("-", elemszelessegek[5] - 1), " ");
#pragma endregion

	for (int i = 0; i < hossz; i++)
	{
		char* color = replace_colors(0, i % 2 == 0 ? "§7" : "§8");
		char* invalid_color = replace_colors(0, i % 2 == 0 ? "§4" : "§c");
		printf("\n%s", color);

		printf("%d%s", veradok[i].id, str_repeat(" ", elemszelessegek[0] - int_len(veradok[i].id)));
		printf("%s%s", veradok[i].nev, str_repeat(" ", elemszelessegek[1] - str_length(veradok[i].nev)));
		printf("%s%s", veradok[i].vercsoport, str_repeat(" ", elemszelessegek[2] - str_length(veradok[i].vercsoport)));
		if (is_valid_email(veradok[i].email)) printf("%s%s", veradok[i].email, str_repeat(" ", elemszelessegek[3] - str_length(veradok[i].email)));
		else printf("%s%s%s%s", invalid_color, "hibás adat", color, str_repeat(" ", elemszelessegek[3] - str_length("hibás adat")));
		printf("%d%s", veradok[i].hanyszor, str_repeat(" ", elemszelessegek[4] - int_len(veradok[i].hanyszor)));
		if (is_valid_date(veradok[i].legutolso)) printf("%s", veradok[i].legutolso);
		else printf("%s%s%s", invalid_color, "hibás adat", color);

		colored_printf(0, "§r");
	}

	colored_printf(1, "\n");
	colored_printf(1, "\n");
}
#pragma endregion

#pragma region add_new_member
void add_new_member(verado** veradok, int hossz, int *ujHossz) {
	int width = 26;

	*ujHossz = hossz;
	do
	{
		(*ujHossz)++;
		clear_screen();
		header();
		char* nev = (char*)malloc(sizeof(char)*128);
		char* vercsoport = (char*)malloc(sizeof(char)*4);
		char* email = (char*)malloc(sizeof(char)*256);
		char* tmp = (char*)malloc(sizeof(char)*10);
		char* legutolso = (char*)malloc(sizeof(char)*11);

		colored_printf(0, "§9 #%d. véradó felvitele§r\n", *ujHossz);
		colored_printf(0, "§9%s§r\n", str_repeat("-", width + 16));

		// Név
		colored_printf(0, "§3Név:%s§e", str_repeat(" ", (int)(width - 4)));
		scanf(" %[^\n]", nev);

		// Vércsoport
		do
		{
			colored_printf(0, "§3Vércsoport:%s§e", str_repeat(" ", (int)(width - 11)));
			scanf(" %[^\n]", vercsoport);
			if (!is_valid_blood_type(vercsoport)) colored_printf(0, "§4HIBA: §cÉrvénytelen vércsoport!\n§r");
		} while (!is_valid_blood_type(vercsoport));
		// E-mail
		do
		{
			colored_printf(0, "§3E-mail:%s§e", str_repeat(" ", (int)(width - 7)));
			scanf(" %[^\n]", email);
			if(!is_valid_email(email)) colored_printf(0, "§4HIBA: §cÉrvénytelen email cím formátum. Az email címnek tartalmaznia kell egy §e.§c és egy §e@§c karaktert!\n§r");
		} while (!is_valid_email(email));

		// Véradások száma
		bool is_number = false;
		int veradasok = 0;
		do
		{
			colored_printf(0, "§3Eddigi véradások száma:%s§e", str_repeat(" ", (int)(width - 23)));
			scanf(" %[^\n]", tmp);
			is_number = is_num(tmp);
			if(is_number) veradasok = atoi(tmp);
			else colored_printf(0, "§4HIBA: §cEzen mező csak számokat fogad el!\n§r");
		} while (!is_number);
		
		// Legutolsó véradás dátuma
		do
		{
			colored_printf(0, "§3Legutolsó véradás dátuma:%s§e", str_repeat(" ", (int)(width - 25)));
			scanf(" %[^\n]", legutolso);
			if (!is_valid_date(legutolso)) colored_printf(0, "§4HIBA: §cÉrvénytelen dátum formátum! Elfogadott dátum formátum: §eyyyy.mm.dd.§c\n§r");
		} while (!is_valid_date(legutolso));

		*veradok = (verado*)realloc(*veradok, *ujHossz * sizeof(verado));

		//(*veradok)[*ujHossz - 1].nev = nev;
		(*veradok)[*ujHossz - 1].id = *ujHossz;
		strcpy((*veradok)[*ujHossz - 1].nev, nev);
		strcpy((*veradok)[*ujHossz - 1].vercsoport, vercsoport);
		strcpy((*veradok)[*ujHossz - 1].email, email);
		(*veradok)[*ujHossz - 1].hanyszor = veradasok;
		strcpy((*veradok)[*ujHossz - 1].legutolso, legutolso);
		nev = NULL;
		vercsoport = NULL;
		email = NULL;
		veradasok = NULL;
		legutolso = NULL;
	} while (once_again_msg("\n§3Szeretne további véradót felvinni?"));
}
#pragma endregion

#pragma region select_members
void select_members(verado* veradok, int hossz, verado** kivalasztott, int* kivalasztottHossz, char* feltetel, verado_enum mezo) {
	*kivalasztott = (verado*)malloc((hossz * sizeof(verado)) + 1);
	(*kivalasztottHossz) = 0;
	for (int i = 0; i < hossz; i++)
	{
		switch (mezo)
		{
		case verado_id:
			if (veradok[i].id == atoi(feltetel)) {
				(*kivalasztottHossz)++;
				memcpy(&(*kivalasztott)[(*kivalasztottHossz) - 1], &veradok[i], sizeof(verado));
			}
			break;
		case verado_nev:
			if (str_equals(veradok[i].nev, feltetel, true)) {
				(*kivalasztottHossz)++;
				memcpy(&(*kivalasztott)[(*kivalasztottHossz) - 1], &veradok[i], sizeof(verado));
			}
			break;
		case verado_vercsoport:
			if (str_equals(veradok[i].vercsoport, feltetel, true)) {
				(*kivalasztottHossz)++;
				memcpy(&(*kivalasztott)[(*kivalasztottHossz) - 1], &veradok[i], sizeof(verado));
			}
			break;
		case verado_email:
			if (str_equals(veradok[i].email, feltetel, true)) {
				(*kivalasztottHossz)++;
				memcpy(&(*kivalasztott)[(*kivalasztottHossz) - 1], &veradok[i], sizeof(verado));
			}
			break;
		case verado_hanyszor:
			if (veradok[i].hanyszor == atoi(feltetel)) {
				(*kivalasztottHossz)++;
				memcpy(&(*kivalasztott)[(*kivalasztottHossz) - 1], &veradok[i], sizeof(verado));
			}
			break;
		case verado_legutolso:
			if (str_equals(veradok[i].legutolso, feltetel, true)) {
				(*kivalasztottHossz)++;
				memcpy(&(*kivalasztott)[(*kivalasztottHossz) - 1], &veradok[i], sizeof(verado));
			}
			break;
		default:
			break;
		}
	}
}
#pragma endregion

#pragma region select_members_by_blood_type
void select_members_by_blood_type(verado* veradok, int hossz, verado** kivalasztott, int* kivalasztottHossz, int* elemszelessegek, char* mai_datum) {
	char vercsoport[4];
	clear_screen();
	header();
	bool vs_b = false;
	do
	{
		colored_printf(0, "\n§3Kérem a keresni kívánt vércsoportot: §e");
		scanf(" %s", vercsoport); vs_b = is_valid_blood_type(vercsoport);
		if(!vs_b) colored_printf(1, "§4HIBA! Érvénytelen vércsoportot adott meg!\n");
	} while (!vs_b);

	select_members(veradok, hossz, kivalasztott, kivalasztottHossz, vercsoport, verado_vercsoport);
	display_members(*kivalasztott, *kivalasztottHossz, elemszelessegek);
	if (once_again_msg("§3Szeretne e-mailt küldeni a 90 napnál régebben vért adott személyeknek?")) {
		int message_length = 0, message_width = 0;
		char** uzenet = file_read_all_lines("email_template.html", &message_length, &message_width);
		for (int i = 0; i < *kivalasztottHossz; i++)
		{
			if (date_to_timestamp(mai_datum) - date_to_timestamp((*kivalasztott)[i].legutolso) >= (90 * 24 * 60 * 60)) {
				send_mail((*kivalasztott)[i], uzenet, message_length, message_width);
			}
		}
	}
}
#pragma endregion
