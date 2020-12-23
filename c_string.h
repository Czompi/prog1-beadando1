#pragma once
#include<stdlib.h>
#include<stdio.h>
#include<string.h> 
#include<assert.h>
#include<ctype.h>
#include"bool.h"

#pragma region str_replace
// https://www.geeksforgeeks.org/c-program-replace-word-text-another-given-word/
// Function to replace a string new_value another  
char* str_replace(char* string, char* old_value, char* new_value)
{
    char* result;
    int i, cnt = 0;
    int new_value_len = strlen(new_value);
    int old_value_len = strlen(old_value);

    // Counting the number of times old word 
    // occur in the string 
    for (i = 0; string[i] != '\0'; i++) {
        if (strstr(&string[i], old_value) == &string[i]) {
            cnt++;

            // Jumping to index after the old word. 
            i += old_value_len - 1;
        }
    }

    // Making new string of enough length 
    int len = i + cnt * (new_value_len - old_value_len) + 10;
    result = (char*)malloc(len * 2 * sizeof(char));
    i = 0;
    while (*string) {
        // compare the substring with the result 
        if (strstr(string, old_value) == string) {
            strcpy(&result[i], new_value);
            i += new_value_len;
            string += old_value_len;
            result[i] = 0;
        }
        else
            result[i++] = *string++;
    }

    result[i] = '\0';
    return result;
}
#pragma endregion

#pragma region str_repeat
char* str_repeat(const char* repeatedChar, int times) {
    char* ret = (char*)malloc((times * sizeof(char)));
    for (int i = 0; i < times; i++)
    {
        strcpy(&ret[i], repeatedChar);
    }
    return ret;
}
#pragma endregion

#pragma region str_split
char** str_split(const char* s, char* delim) {
    void* data;
    char* _s = (char*)s;
    const char** ptrs;
    int
        ptrsSize,
        nbWords = 1,
        sLen = strlen(s),
        delimLen = strlen(delim);

    while ((_s = strstr(_s, delim))) {
        _s += delimLen;
        ++nbWords;
    }
    ptrsSize = (nbWords + 1) * sizeof(char*);
    ptrs =
        data = malloc(ptrsSize + sLen + 1);
    if (data) {
        *ptrs =
            _s = strcpy(((char*)data) + ptrsSize, s);
        if (nbWords > 1) {
            while ((_s = strstr(_s, delim))) {
                *_s = '\0';
                _s += delimLen;
                *++ptrs = _s;
            }
        }
        *++ptrs = NULL;
    }
    return data;
}
#pragma endregion

#pragma region int_length
int int_len(int x) {
    if (x >= 1000000000) return 10;
    if (x >= 100000000)  return 9;
    if (x >= 10000000)   return 8;
    if (x >= 1000000)    return 7;
    if (x >= 100000)     return 6;
    if (x >= 10000)      return 5;
    if (x >= 1000)       return 4;
    if (x >= 100)        return 3;
    if (x >= 10)         return 2;
    return 1;
}
#pragma endregion

#pragma region str_length
// Source: https://gist.github.com/stanislaw/f62c36823242c4ffea1b
bool utf8_is_continuation(char c) {
    return (c & 0xc0) == 0x80;
}

// Source: https://gist.github.com/stanislaw/f62c36823242c4ffea1b
int str_length(const char* s) {
    if (!s) return 0;
    int i = 0, len = 0;
    while (s[i]) {
        if (!utf8_is_continuation(s[i])) ++len;
        ++i;
    }
    return len;
}
#pragma endregion

#pragma region str_contains
// Source: https://stackoverflow.com/a/55153978
bool str_contains(char* string, char* toFind)
{
    int slen = strlen(string);
    int tFlen = strlen(toFind);
    int found = 0;

    if (slen >= tFlen)
    {
        for (int s = 0, t = 0; s < slen; s++)
        {
            do {

                if (string[s] == toFind[t])
                {
                    if (++found == tFlen) return true;
                    s++;
                    t++;
                }
                else { s -= found; found = 0; t = 0; }

            } while (found);
        }
        return false;
    }
    else return false;
}
#pragma endregion

#pragma region str_pos
int str_pos(char* string, char* toFind)
{
    int slen = str_length(string);
    int tFlen = str_length(toFind);
    int found = 0;

    if (slen >= tFlen)
    {
        for (int s = 0, t = 0; s < slen; s++)
        {
            do {

                if (string[s] == toFind[t])
                {
                    if (++found == tFlen) return found;
                    s++;
                    t++;
                }
                else { s -= found; found = 0; t = 0; }

            } while (found);
        }
        return -1;
    }
    else return -2;
}
#pragma endregion

#pragma region str_copy
void str_copy(char** dest, char* src)
{
    int dstlen = 0;
    if (*dest != NULL) dstlen = str_length(*dest);
    *dest = (char*)malloc((dstlen + str_length(&src)));
    int i = str_length(*dest);
    while (src[i] != '\0')
    {
        strcpy(*dest, src);
        i++;
    }
    //(*dest)[i] = '\0';
}
#pragma endregion

#pragma region int_to_string
// Source: https://stackoverflow.com/a/9660930
char* int_to_string(int num) {

    const char digit[] = "0123456789";
    char* p = (char*)malloc(12 * sizeof(char));
    if (num < 0) {
        *p++ = '-';
        num *= -1;
    }
    int shifter = num;
    do { //Move to where representation ends
        ++p;
        shifter = shifter / 10;
    } while (shifter);
    *p = '\0';
    do { //Move back, inserting digits as u go
        *--p = digit[num % 10];
        num = num / 10;
    } while (num);
    return p;
}
#pragma endregion

#pragma region str_tolower
/// <summary>
/// Makes string lowercase
/// </summary>
/// <param name="string">string to be lowercased</param>
/// <returns>Lowercase value of provided string</returns>
char* str_tolower(char* string) {
    char* lowercase = string;
    for (int i = 0; i < lowercase[i]; i++) {
        lowercase[i] = tolower(lowercase[i]);
    }
    return lowercase;
}
#pragma endregion

#pragma region str_toupper
/// <summary>
/// Makes string uppercase
/// </summary>
/// <param name="string">string to be uppercased</param>
/// <returns>Uppercase value of provided string</returns>
char* str_toupper(char* string) {
    char* uppercase = string;
    for (int i = 0; i < uppercase[i]; i++) {
        uppercase[i] = toupper(uppercase[i]);
    }
    return uppercase;
}
#pragma endregion

#pragma region str_equals
bool str_equals(const char* str1, const char* str2, bool ignore_case) {
    if (str_length(str1) != str_length(str2)) return false;
    if (ignore_case) {
        str1 = str_tolower(str1);
        str2 = str_tolower(str2);
    }
    int i = 0;
    while (str1[i])
    {
        if (str1[i] != str2[i]) return false;
        i++;
    }
    return true;
}
#pragma endregion
