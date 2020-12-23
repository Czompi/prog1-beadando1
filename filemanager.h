#pragma once
#include<stdio.h>
#include"models.h"
#include"functions.h"
#include"models.h"

#pragma region file_exists
bool file_exists(const char* fileName) {
	FILE* file;
	if ((file = fopen(fileName, "r")) != NULL)
	{
		fclose(file);
		return true;
	}
	else
	{
		return false;
	}
}
#pragma endregion

#pragma region readFile
/**
* Reads the file to the correct format
* \param fileName Name of the file, that contains the database.
* \param veradok Array of verados (pointer)
* \param h Length of verados array (pointer)
*/
int readFile(char *fileName, verado **veradok, int *h, int is_filename_set) {

	FILE* fajl = NULL; int i;
	
	if (is_filename_set != 1) {
		colored_printf(0, "§bBeolvasandó fájl neve: §e"); scanf(" %s", fileName);
		colored_printf(0, "§r");
	}
	if (!(fajl = fopen(fileName, "r")) && !file_exists(fileName))
	{
		colored_printf(1, "§4HIBA: §cA(z) §e%s§c állomány megnyitása sikertelen (Talán nem megfelelő az elérési út).\n", fileName);
		if (once_again()) { return 1; }
		else { colored_printf(1, "§cA program kilép.\n"); return 2; }
	}

	while (!feof(fajl))
	{
		char ln[1000];
		fscanf(fajl, "%[^\n]\n", ln);
		if (ln != "") { (*h)++; }
	}
	(*h)--; // remove header
	if (!((*veradok) = (verado*)malloc(*h * sizeof(verado))))
	{
		colored_printf(1, "§4HIBA: §cA művelet végrehajtásához nincs elég memória.\n");
		if (once_again()) { return 1; }
		else { colored_printf(1,"§cA program kilép.\n"); return 2; }
	}

	rewind(fajl);

	char* buffer = (char*)malloc(sizeof(char)*512);
	fscanf(fajl, "%s", buffer); // First line is a header
	for (i = 0; i < (*h); i++)
	{
		int id;
		char nev[128];
		char vercsoport[16];
		char email[256];
		int hanyszor;
		char legutolso[16];
		fscanf(fajl, "%d;%[^;];%[^;];%[^;];%d;%[^(\r|)\n]", &id, nev, vercsoport, email, &hanyszor, legutolso);
		(*veradok)[i].id = id;
		strcpy((*veradok)[i].nev, nev);
		strcpy((*veradok)[i].vercsoport, vercsoport);
		if (is_valid_email(email)) strcpy((*veradok)[i].email, email);
		else strcpy((*veradok)[i].email, "");
		(*veradok)[i].hanyszor = hanyszor;
		if (is_valid_date(legutolso)) strcpy((*veradok)[i].legutolso, legutolso);
		else strcpy((*veradok)[i].legutolso, "0000.00.00.");
	}
	//fflush(fajl);
	fclose(fajl);
	colored_printf(1, "§aFájl beolvasva.\n");
	return 0;
}
#pragma endregion

#pragma region writeFile
int writeFile(const char* fileName, verado* veradok, int hossz) {
	FILE* fajl = NULL; ; int i;

	if (!(fajl = fopen(fileName, "w")))
	{
		colored_printf(1, "§4HIBA: §cA(z) §e%s§c állomány megnyitása sikertelen (Talán nem megfelelő az elérési út).\n", fileName);
		if (once_again()) { return 1; }
		else { colored_printf(1, "§cA program kilép.\n"); return 2; }
	}

	fprintf(fajl, "%s;%s;%s;%s;%s;%s\n", "id", "nev", "vercsoport", "email", "veradasok_szama", "legutolso_veradas");
	for (i = 0; i < hossz; i++)
	{
		fprintf(fajl, "%d;%s;%s;%s;%d;%s\n", veradok[i].id, veradok[i].nev, veradok[i].vercsoport, veradok[i].email, veradok[i].hanyszor, veradok[i].legutolso);
	}
	fclose(fajl);
	return 0;
}
#pragma endregion

#pragma region send_mail
void send_mail(verado verado_, char** message, int message_length, int message_width) {
	FILE* fajl = NULL;
	char* fileName = NULL;
	if (!(fileName = (char*)malloc(str_length(verado_.nev) + sizeof(".html")))) {
		colored_printf(0, "§cSikertelen helyfoglalás! :o\n\t §e%s§c: hívó függvény §e%s§r\n", "functions.h(221)", "send_mail");
		return false;
	}
	str_copy(&fileName, verado_.nev);
	strncat(fileName, ".html", sizeof(".html") + 1);

	if (!(fajl = fopen(fileName, "w")))
	{
		colored_printf(0, "§4HIBA: §cA(z) §e%s§c állomány megnyitása sikertelen (Talán nem megfelelő az elérési út).\n§r", fileName);
	}

	char* line = NULL;
	if (!(line = (char*)malloc(sizeof(char) * message_width * 2))) {
		colored_printf(0, "§cSikertelen helyfoglalás! :o\n\t §e%s§c: hívó függvény §e%s§r\n", "functions.h(226)", "send_mail");
		return false;
	}
	for (int i = 0; i < message_length; i++)
	{
		line = message[i];
		char* id = int_to_string(verado_.id);
		line = str_replace(line, "{id}", id);
		line = str_replace(line, "{nev}", verado_.nev);
		line = str_replace(line, "{vercsoport}", verado_.vercsoport);
		line = str_replace(line, "{email}", verado_.email);
		char* hanyszor = int_to_string(verado_.hanyszor);
		line = str_replace(line, "{hanyszor}", hanyszor);
		line = str_replace(line, "{legutolso}", verado_.legutolso);
		fprintf(fajl, "%s\n", line);
	}
	free(line);
	fclose(fajl);
}

#pragma endregion

#pragma region file_read_all_lines
char** file_read_all_lines(char* fileName, int* message_length, int* max_line_width) {

	FILE* fajl = NULL; int i = 0;
	(*message_length) = 0;
	if (!(fajl = fopen(fileName, "r")))
	{
		colored_printf(0, "§4HIBA: §cA(z) %s állomány megnyitása sikertelen (Talán nem megfelelő az elérési út).\n", fileName);
		return NULL;
	}

	char* ln = (char*)malloc(sizeof(char*));
	while (!feof(fajl))
	{
		fscanf(fajl, "%[^\n]\n", ln);
		if (ln != "") {
			(*message_length)++;
			int line_width = str_length(ln);
			if (maximum(line_width, *max_line_width) == line_width) *max_line_width = line_width;
		}
	}
	ln = NULL;

	rewind(fajl);

	char** lines = (char**)malloc((*message_length) * (*max_line_width) * sizeof(char));
	for (int i = 0; i < (*message_length); i++)
	{
		lines[i] = (char*)malloc((*max_line_width) * sizeof(char));
	}
	i = 0;
	for (int i = 0; i < (*message_length); i++)
	{
		fscanf(fajl, "%[^\n]\n", lines[i]);
	}
	return lines;
}
#pragma endregion
