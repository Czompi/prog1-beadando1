#pragma once
#include"bool.h"
#include<stdarg.h>
#include<ctype.h>
#include"c_string.h"
#include"externalsources.h"

#pragma region clear_screen
void clear_screen() {
#if _WIN32
	system("CLS");
#else
	system("clear");
#endif
}
#pragma endregion

#pragma region is_num
bool is_num(char* str) {

	int length = str_length(str);
	for (int i = 0; i < length; i++) {
		int cc = (int)str[i];
		if (!(cc >= 48 && cc <= 57)) return false;
	}
	return true;
}
#pragma endregion


#pragma region Console coloring
/// <summary>
///	Use Minecraft color codes to simplify coloring
/// </summary>
/// <param name="addColorReset">If set to 1, it'll reset the color at the end of rendered string.</param>
/// <param name="string"></param>
/// <returns></returns>
char* replace_colors(int addColorReset, const char* string) {
	char* str = string;
	str = str_replace(str, "§0", "\033[30m");
	str = str_replace(str, "§1", "\033[34m");
	str = str_replace(str, "§2", "\033[32m");
	str = str_replace(str, "§3", "\033[36m");
	str = str_replace(str, "§4", "\033[31m");
	str = str_replace(str, "§5", "\033[35m");
	str = str_replace(str, "§6", "\033[33m");
	str = str_replace(str, "§7", "\033[37m");
	str = str_replace(str, "§8", "\033[90m");
	str = str_replace(str, "§9", "\033[94m");
	str = str_replace(str, "§a", "\033[92m");
	str = str_replace(str, "§b", "\033[96m");
	str = str_replace(str, "§c", "\033[91m");
	str = str_replace(str, "§d", "\033[95m");
	str = str_replace(str, "§e", "\033[93m");
	str = str_replace(str, "§f", "\033[97m");


	//str = str_replace(str, "\0", "§r\0");
	str = str_replace(str, "§r", "\033[0m");
	str = str_replace(str, "\n", "\033[0m\n");

	if (addColorReset == 1) {
		int l = str_length(str);
		str[l + 0] = '\033';
		str[l + 1] = '[';
		str[l + 2] = '0';
		str[l + 3] = 'm';
		/*str[l + 2] = '0';
		str[l + 3] = ';';
		str[l + 4] = '0';
		str[l + 5] = 'm';*/
		str[l + 6] = '\0';
	}
	return str;
}
#pragma endregion

#pragma region printf
/// <summary>
///	Write to the console with colors.
/// </summary>
/// <param name="addColorReset">If set to 1, it'll reset the color at the end of rendered string.</param>
/// <param name="string">Colorable content (use Minecraft Color Codes with § sign before color code)</param>
/// <param name="format"></param>
void colored_printf(int addColorReset, const char* string, ...) {
	va_list args;
	va_start(args, string);
	vprintf(replace_colors(addColorReset, string), args);
	va_end(args);
}
#pragma endregion

#pragma region Once again
// Check if user wants to retry the thing
bool once_again_msg_ynoverride(const char* message, char true_option, char false_option) {
	char res[128];
	char true_str[2];
	true_str[0] = true_option;
	true_str[1] = '\0';
	char false_str[2];
	false_str[0] = false_option;
	false_str[1] = '\0';
	do
	{
		colored_printf(0, "§6%s §r(§9%c§r/§9%c§r) §e", replace_colors(0, message), true_option, false_option);
		scanf(" %s", res);
		colored_printf(0, "§r");
		if(!str_equals(res, true_str, true) && !str_equals(res, false_str, true)) colored_printf(0, "§4HIBA: §cCsak §e%c§c és §e%c§c értékek fogadhatóak kis- és nagybetűs formában.\n", true_option, false_option);
	} while (!str_equals(res, true_str, true) && !str_equals(res, false_str, true));
	if (str_equals(res, true_str, true)) return true;
	else return false;
}

// Check if user wants to retry the thing
bool once_again_msg(const char* message) {
	return once_again_msg_ynoverride(message, 'y', 'n');
}

// Check if user wants to retry the thing
bool once_again() {
	return once_again_msg("Újra próbálja?");
}
#pragma endregion

#pragma region maximum
int maximum(int x, int y) {
	if (x > y) return x;
	else return y;
}
#pragma endregion

#pragma region action
int action(int start, int end, int selected) {
	char *res = NULL;

	if (!(res = (char*)malloc(maximum(start, end)))) {
		colored_printf(0, "§cSikertelen helyfoglalás! :o\n\t §e%s§c: hívó függvény §e%s§r\n", "functions.h(126)", "action");
		return -1;
	}
	bool is_valid_action = false;
	if(selected != -1) strcpy(res, int_to_string(selected));
	while (!is_valid_action) {
		printf(replace_colors(0, "§6Végrehajtani kívánt művelet §r(§9%d§r-§9%d§r): §e"), start, end);
		scanf(" %s", res);
		colored_printf(0, "\r");
		is_valid_action = is_num(res) && atoi(res) >= start && atoi(res) <= end;
	}
	return atoi(res);
}
#pragma endregion

#pragma region Header
void header() {
	colored_printf(1, "§9 __      __                _                     _ _                  _             _            \n");
	colored_printf(1, "§9 \\ \\    / /               | |                   (_) |                | |           | |           \n");
	colored_printf(1, "§9  \\ \\  / /__ _ __ __ _  __| | ___    _ __  _   _ _| |_   ____ _ _ __ | |_ __ _ _ __| |_ __ _ ___ \n");
	colored_printf(1, "§9   \\ \\/ / _ \\ '__/ _` |/ _` |/ _ \\  | '_ \\| | | | | \\ \\ / / _` | '_ \\| __/ _` | '__| __/ _` / __|\n");
	colored_printf(1, "§9    \\  /  __/ | | (_| | (_| | (_) | | | | | |_| | | |\\ V / (_| | | | | || (_| | |  | || (_| \\__ \\\n");
	colored_printf(1, "§9     \\/ \\___|_|  \\__,_|\\__,_|\\___/  |_| |_|\\__, |_|_| \\_/ \\__,_|_| |_|\\__\\__,_|_|   \\__\\__,_|___/\n");
	colored_printf(1, "§9                                            __/ |                                                \n");
	colored_printf(1, "§9                                           |___/                                                 \n");
	colored_printf(1, "§9\n");
}
#pragma endregion


#pragma region is_valid_email
bool is_valid_email(char* email) {
	int dotIndex = -1, atIndex = -1, numberOfDots = 0, numberOfAts = 0, diff, length = str_length(email);
	for (int i = 0; i < length; i++)
	{
		if (email[i] == '.') { dotIndex = i; numberOfDots++; }
		if (email[i] == '@') { atIndex = i; numberOfAts++; }
	}

	// Missing one of those characters
	if ((diff = dotIndex - atIndex) < 0 && numberOfDots == 1) return false;
	// Missing one of those characters
	if (numberOfDots == 0 || numberOfAts == 0) return false;
	// One of them is at the end of the string
	if (dotIndex + 1 == length || atIndex + 1 == length) return false;
	// One of them is at the start of the string
	if (dotIndex == 0 || atIndex == 0) return false;
	// They're next to each other
	if (diff == 1) return false;


	return true;
}
#pragma endregion

#pragma region is_valid_blood_type
bool is_valid_blood_type(char* vercsoport) {
	char vercsoportok[8][3] = { "0+", "A+", "B+", "0-", "A-", "B-", "AB+", "AB-" };
	int tries = 0;
	for (int i = 0; i < 8; i++)
	{
		char *val = vercsoportok[i];
		if (str_equals(vercsoport, val, true)) return true;
	}
	return false;
}
#pragma endregion


#pragma region find_closest_id
// Returns the id of the closest to target in arr[] 
int find_closest_id(const int* arr, int n, int target)
{
	for (int i = 0; i < n - 1; i++)
	{
		if (i + 2 == n && arr[i + 1] <= target) return i + 1; else
		if (arr[i] <= target && arr[i + 1] >= target) return i;
	}
	return -1;
}
#pragma endregion

#pragma region find_closest
// Returns element closest to target in arr[] 
int find_closest(const int* arr, int n, int target)
{
	for (int i = 0; i < n - 1; i++)
	{
		if (i + 2 == n && arr[i + 1] <= target) return arr[i + 1]; else
		if (arr[i] <= target && arr[i + 1] >= target) return arr[i];
	}
	return -1;
}
#pragma endregion
