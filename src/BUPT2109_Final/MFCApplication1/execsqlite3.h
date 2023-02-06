#pragma once


#define _CRT_SECURE_NO_DEPRECATE
#pragma warning(disable:4996)
#include "pch.h"
#include "dataType.h"


#include <cstring>
#include<string>
#include<atlstr.h>


#include <iostream>
#include "../sqlite3/src/sqlite3.h"
#include <string.h>

//using namespace std;

extern sqlite3* db;

extern char* star;
extern char unc[20];
extern char airline[20];
extern int callbackCount;
extern int thisUUID;
extern tdate globalDate;
extern ttime globalTime;
extern int md[12];
extern int thisDate;
extern flightInfo flight[100];
extern order orders[100];


void int2date(int src, tdate* dest);

int date2int(tdate* src);

void int2time(int src, ttime* dest);

int time2int(ttime* src);

void Cstring2Char(CString src, char* dst);

sqlite3* openDb(char* fname);

static int callback_userInfo(void* data, int argc, char** argv, char** azColName);

static int callback_order(void* data, int argc, char** argv, char** azColName);

static int callback_flight(void* data, int argc, char** argv, char** azColName);

int getUserInfo(sqlite3* db, userInfo* dest, char* userName);

int getAdminInfo(sqlite3* db, adminInfo* dest, char* userName);

int getOrder(sqlite3* db, order* dest, int UUID);

int getOrderByAl(sqlite3* db, order* dest, char* airline);

int getFlightInfo(sqlite3* db, flightInfo* dest, char* com);

int addOrder(sqlite3* db, order orderInfo);

int addFlight(sqlite3* db, flightInfo flight);

int orderCheck(int OUID, int UUID);

int loginUser(sqlite3* db, char* ID, char* password);

int changePaid(sqlite3* db, int OUID);

int loginAdmin(sqlite3* db, char* ID, char* password);

CString getUserName(int UUID);

int changeUserInfo(int type, char* value);

int changeAdminInfo(int type, char* value);

int deleteOrder(sqlite3* db, int OUID);

int getFlightInfoByCol(sqlite3* db, flightInfo* dest, char* col, char* name);

int boughtFlight(sqlite3* db, int FUID, int origNum, int isPro);

int getTicketNum(sqlite3* db, int gDate, char* flightNumber);