#include "pch.h"
#include "check.h"

int checkphone(char* s) {
	char* p;
	p = s;
	if (strlen(s) != 11) {
		return 0;
	}
	while (*s) {
		if (*s < '0' || *s>'9') {
			return 0;
		}
		s++;
	}
	return 1;
}

int checkemail(char* s)
{
	int checkemail1 = 0, checkemail2 = 0, checkemail13 = 0;
	char* p1, * p2, * p3;
	p1 = s;
	p2 = s;
	p3 = s;
	while (*p1)
	{
		if (*p1 == '@')
		{
			checkemail1 = 1;
			break;
		}
		p1++;
	}
	while (*p2)
	{
		if (*p2 == '.' && p2 > p1 + 1)
		{
			checkemail2 = 1;
			break;
		}
		p2++;
	}
	checkemail13 = 1;
	if (checkemail1 == 1 && checkemail2 == 1 && checkemail13 == 1)
		return 1;
	else
		return 0;
}


int checkpassword(char* password)
{
	char* s;
	s = password;
	if (strlen(password) < 7 || strlen(password) > 16)
	{
		return 0;
	}
	while (*s) {
		if ('a' < *s < 'z' || '0' < *s < '9' || 'A' < *s < 'Z') {
			s++;
		}
		else
			return 0;
	}
	return 1;
}