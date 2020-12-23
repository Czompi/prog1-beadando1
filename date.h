#pragma once
#include"bool.h"
#include"externalsources.h"
#include"c_string.h"
#include"functions.h"

#pragma region Definitions
#define SECOND 1
#define MINUTE 60
#define HOUR (60 * 60)
#define DAY (HOUR * 24)
#define WEEK (DAY * 7)
#define YEAR (DAY * 365)
#define YEAR_LEAP (DAY * 366)

const int dim[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
const int dim_l[12] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
const int DaysToMonth365[13] = { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365 };
const int DaysToMonth366[13] = { 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366 };
#pragma endregion



#pragma region date_split
int* date_split(const char* date) {
	char** dateSplit = str_split(date, ".");
	int *dt = (int*)malloc(sizeof(int)*3);
	dt[0] = atoi(dateSplit[0]);
	dt[1] = atoi(dateSplit[1]);
	dt[2] = atoi(dateSplit[2]);
	return dt;
}
#pragma endregion

#pragma region is_leap_year
// Source of the calculation logic: https://docs.microsoft.com/en-us/office/troubleshoot/excel/determine-a-leap-year#how-to-determine-whether-a-year-is-a-leap-year
bool is_leap_year_date(const char* date) {
	int* dateSplit = date_split(date);
	int yr = dateSplit[0];
	return (yr % 400 == 0) || ((yr % 4 == 0) && (yr % 100 != 0));
}

// Source of the calculation logic: https://docs.microsoft.com/en-us/office/troubleshoot/excel/determine-a-leap-year#how-to-determine-whether-a-year-is-a-leap-year
bool is_leap_year(int year) {
	return (year % 400 == 0) || ((year % 4 == 0) && (year % 100 != 0));
}
#pragma endregion

#pragma region is_valid_date
bool is_valid_date(const char* date) {
	if (str_length(date) != 11) return false;
	int* dateSplit = date_split(date);
	int yr = dateSplit[0];
	int mo = dateSplit[1];
	int da = dateSplit[2];
	int yr_chk = int_len(yr) == 4;
	int mo_chk = mo >= 1 && mo <= 12;
	int* dim_a = is_leap_year_date(date) ? dim_l : dim;
	int da_chk = dim_a[mo - 1] >= da && 1 <= da;
	return yr_chk && mo_chk && da_chk;
}
#pragma endregion


#pragma region date_to_timestamp
long date_to_timestamp(const char* date) {
	int* dateSplit = date_split(date);
	int year = dateSplit[0];
	int month = dateSplit[1];
	int day = dateSplit[2];

	if (!is_valid_date(date)) return -1;

	int yr = year - 1970;
	int* dim_ = is_leap_year(year) ? DaysToMonth366 : DaysToMonth365;
	long yr_d = 0;
	for (int i = 0; i < yr; i++)
	{
		yr_d += is_leap_year(1970 + i) ? YEAR_LEAP : YEAR;
	}
	int mo = dim_[month - 1];
	int mo_d = mo * DAY;
	int da_d = (day - 1) * DAY;
	return yr_d + mo_d + da_d;
}
#pragma endregion

#pragma region timestamp_to_date
char* timestamp_to_date(long timestamp) {
	int year_c = timestamp / YEAR, year = year_c;
	year += 1970;
	int* dim_ = is_leap_year(year) ? DaysToMonth366 : DaysToMonth365;
	int stmp_wo_yr = timestamp;
	for (int i = 0; i < year_c; i++)
	{
		stmp_wo_yr -= is_leap_year(1970 + i) ? YEAR_LEAP : YEAR;
	}
	int days = stmp_wo_yr;
	days /= DAY;
	int month = find_closest_id(DaysToMonth366, 13, days);
	month += 1;
	int day = days - dim_[month - 1];
	day += 1;
	char* date = (char*)malloc(11 * sizeof(char));
	sprintf(date, "%04d.%02d.%02d.", year, month, day);
	return date;
}
#pragma endregion
