//#pragma once
#pragma once

#include "pch.h"
#include "execsqlite3.h"

using namespace std;

sqlite3* db = 0;
char* star = (char*)"*";
char airline[20];
int callbackCount = 0;
char unc[20];
int thisUUID;
int md[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
tdate globalDate;
ttime globalTime;
int thisDate;
flightInfo flight[100];
order orders[100];

void int2date(int src, tdate* dest) {
    tdate ret;
    //int m[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
    ret.y = src/365;
    src = src % 365;
    for (ret.m =1; ret.m <= 12; ret.m++) {
        if (src < md[ret.m - 1]) break;
        src -= md[ret.m - 1];
    }
    ret.d = src;
    memcpy(dest, &ret, sizeof(ret));
}

int date2int(tdate* src) {
    int ret = src->y*365;
    for (int i = 1; i < src->m; i++)
        ret += md[i-1];
    ret += src->d;
    return ret;
}

void int2time(int src, ttime* dest) {
    ttime ret;
    ret.h = src / 3600;
    ret.m = (src % 3600) / 60;
    ret.s = src % 60;
    memcpy(dest, &ret, sizeof(ret));
}

int time2int(ttime* src) {
    return src->h * 3600 + src->m * 60 + src->s;
}

void Cstring2Char(CString src, char* dst)
{
    DWORD dwMinSize;
    dwMinSize = WideCharToMultiByte(CP_ACP, NULL, src, -1, NULL, 0, NULL, FALSE);
    char* pp = new char[dwMinSize];
    WideCharToMultiByte(CP_OEMCP, NULL, src, -1, pp, dwMinSize, NULL, FALSE);
    strcpy(dst, pp);
    delete[] pp;
}

sqlite3* openDb(char* fname) {
    //db=;
    star = (char*)"*";
    char* execMsg = 0;
    callbackCount = 0;
    int ret;
    ret = sqlite3_open(fname, &db);
    if (ret != SQLITE_OK) {
        fprintf(stderr, "open SQL error: %s\n", execMsg);
        sqlite3_free(execMsg);
        return (sqlite3*)0;
    }
    else {
        fprintf(stdout, "open db successfully\n");
        return db;
    }
}

static int callback_userInfo(void* data, int argc, char** argv, char** azColName) {
    userInfo ret;
    printf("callback userinfo UID %s\n", argv[0]);
    //for (i = 1; i<argc; i++)
    //printf("%s = %s\n",azColName[i],argv[i] ? argv[i] : "NULL");
    ret.UID = atoi(argv[0]);
    strcpy(ret.ID, argv[1]);
    strcpy(ret.name, argv[2]);
    ret.gender = atoi(argv[3]);
    ret.phone = atoll(argv[4]);
    strcpy(ret.password, argv[5]);
    strcpy(ret.email, argv[6]);

    memcpy((char*)data + callbackCount * sizeof(ret), &ret, sizeof(ret));
    callbackCount++;
    return 0;
}

static int callback_adminInfo(void* data, int argc, char** argv, char** azColName) {
    adminInfo ret;
    printf("callback admininfo UID %s\n", argv[0]);
    //for (i = 1; i<argc; i++)
    //printf("%s = %s\n",azColName[i],argv[i] ? argv[i] : "NULL");
    ret.UID = atoi(argv[0]);
    strcpy(ret.ID, argv[1]);
    strcpy(ret.airline, argv[2]);
    strcpy(ret.name, argv[3]);
    strcpy(ret.email, argv[4]);
    strcpy(ret.password, argv[5]);

    memcpy((char*)data + callbackCount * sizeof(ret), &ret, sizeof(ret));
    callbackCount++;
    return 0;
}
static int callback_order(void* data, int argc, char** argv, char** azColName) {
    order ret;
    //ret.flightNumber = "";
    printf("callback order UID %s\n", argv[0]);
    ret.OUID = atoi(argv[0]);
    ret.UUID = atoi(argv[1]);
    //ret.FUID = atoi(argv[2]);
    strcpy(ret.flightNumber, argv[2]);
    ret.number = atoi(argv[3]);
    ret.tier = atoi(argv[4]);
    ret.isPaid = atoi(argv[5]);
    strcpy(ret.airline, argv[6]);
    ret.takeOffTime = atof(argv[7]);
    ret.estTime = atof(argv[8]);
    ret.price = atoi(argv[9]);
    ret.date = atoi(argv[10]);
    ret.fdate = atoi(argv[11]);
    memcpy(((char*)data + callbackCount * sizeof(ret)), &ret, sizeof(ret));
    callbackCount++;
    return 0;
}

static int callback_flight(void* data, int argc, char** argv, char** azColName) {
    flightInfo ret;
    printf("callback flight UID %s\n", argv[0]);
    ret.FUID = atoi(argv[0]);
    strcpy(ret.flightNumber, argv[1]);
    strcpy(ret.airline, argv[2]);
    strcpy(ret.departure, argv[3]);
    strcpy(ret.land, argv[4]);
    ret.takeOffTime = atof(argv[5]);
    ret.estTime = atof(argv[6]);
    strcpy(ret.type, argv[8]);
    ret.onTimePerf = atof(argv[9]);
    strcpy(ret.pilot1, argv[10]);
    strcpy(ret.pilot2, argv[11]);
    ret.price1 = atoi(argv[12]);
    ret.price2 = atoi(argv[13]);
    ret.remain1 = atoi(argv[14]);
    ret.remain2 = atoi(argv[15]);

    memcpy((char*)data + callbackCount * sizeof(ret), &ret, sizeof(ret));
    callbackCount++;
    return 0;
}

int getUserInfo(sqlite3* db, userInfo* dest, char* userName) {
    char sql[100];
    sprintf(sql, "SELECT * from User WHERE ID GLOB '%s'", userName);
    //const char* data = "Callback function called";
    //userInfo data[maxn];
    //const userInfo* data = dest;
    /* Execute SQL statement */
    callbackCount = 0;
    int ret;
    char* execMsg;
    ret = sqlite3_exec(db, sql, callback_userInfo, (void*)dest, &execMsg);
    if (ret != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", execMsg);
        sqlite3_free(execMsg);
        return 1;
    }
    else {
        fprintf(stdout, "getUserInfo done successfully\n");
    }
    //memcpy(dest,&data,sizeof(data));

    if (userName != star)
        thisUUID = dest->UID;

    return 0;
}

int getAdminInfo(sqlite3* db, adminInfo* dest, char* userName) {
    char sql[100];
    sprintf(sql, "SELECT * from Admin WHERE ID GLOB '%s'", userName);
    //const char* data = "Callback function called";
    //userInfo data[maxn];
    //const userInfo* data = dest;
    /* Execute SQL statement */
    callbackCount = 0;
    int ret;
    char* execMsg;
    ret = sqlite3_exec(db, sql, callback_adminInfo, (void*)dest, &execMsg);
    if (ret != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", execMsg);
        sqlite3_free(execMsg);
        return 1;
    }
    else {
        fprintf(stdout, "getAdminInfo done successfully\n");
    }
    //memcpy(dest,&data,sizeof(data));

    if (userName != star)
        thisUUID = dest->UID;

    return 0;
}

int getOrder(sqlite3* db, order* dest, int UUID) {
    char sql[100];
    if (UUID >= 0)
        sprintf(sql, "SELECT * from Orders WHERE UUID == %d\n", UUID);
    else sprintf(sql, "SELECT * from Orders");
    //printf("SELECT * from Order WHERE UUID == %d\n",UUID);
    /* Execute SQL statement */
    callbackCount = 0;
    int ret;
    char* execMsg;
    ret = sqlite3_exec(db, sql, callback_order, (void*)dest, &execMsg);
    //ret = sqlite3_exec(db, sql, callback_order, nullptr, nullptr);
    if (ret != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", execMsg);
        sqlite3_free(execMsg);
        return 1;
    }
    else {
        fprintf(stdout, "getOrder done successfully\n");
    }
    //memcpy(dest,&data,sizeof(data));
    return 0;
}

int getOrderByAl(sqlite3* db, order* dest, char* airline) {
    char sql[100];
    sprintf(sql, "SELECT * from Orders WHERE airline GLOB '%s'\n",airline);
    //printf("SELECT * from Order WHERE UUID == %d\n",UUID);
    /* Execute SQL statement */
    callbackCount = 0;
    int ret;
    char* execMsg;
    ret = sqlite3_exec(db, sql, callback_order, (void*)dest, &execMsg);
    //ret = sqlite3_exec(db, sql, callback_order, nullptr, nullptr);
    if (ret != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", execMsg);
        sqlite3_free(execMsg);
        return 1;
    }
    else {
        fprintf(stdout, "getOrder done successfully\n");
    }
    //memcpy(dest,&data,sizeof(data));
    return 0;
}

int getFlightInfo(sqlite3* db, flightInfo* dest, char* com) {
    char sql[100];
    if (com)
        sprintf(sql, "SELECT * from Flight WHERE airline GLOB '%s'", com);
    else sprintf(sql, "SELECT * from Flight");
    /* Execute SQL statement */
    callbackCount = 0;
    int ret;
    char* execMsg = 0;
    //ret = sqlite3_exec(db, sql, callback_flight, (void*)dest, &execMsg);
    ret = sqlite3_exec(db, sql, callback_flight, (void*)dest, nullptr);
    if (ret != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", execMsg);
        sqlite3_free(execMsg);
        return 1;
    }
    else {
        fprintf(stdout, "getFlight done successfully\n");
    }
    //memcpy(dest,&data,sizeof(data));
    return 0;
}

int addOrder(sqlite3* db, order orderInfo) {
    char sql[1024];
    int ret;
    //char seatInfo[sizeof(flight.seatInfo)+100];
    //memcpy(seatInfo,&flight.seatInfo,sizeof(flight.seatInfo));

    /*printf("INSERT INTO Flight (flightNumber,airline,departure,land,takeOffTime,estTime,price1,price2,remain1,remain2,type,onTimePerf,pilot1,pilot2) "\
        "VALUES ('%s','%s','%s','%s',%.3lf,%.3lf,%d,%d,%d,%d,'%s',%.3lf,'%s','%s')",
        flight.flightNumber,flight.airline,flight.departure,flight.land,flight.takeOffTime,flight.estTime,flight.price1,flight.price2,flight.remain1,flight.remain2,flight.type,flight.onTimePerf,flight.pilot1,flight.pilot2);*/

    sprintf(sql, "INSERT INTO Orders (UUID,flightNumber,number,tier,isPaid,airline,takeOffTime,estTime,price,date,fdate) "\
        "VALUES (%d,'%s',%d,%d,%d,'%s',%lf,%lf,%d,%d,%d)",
        orderInfo.UUID, orderInfo.flightNumber, orderInfo.number, orderInfo.tier,
        orderInfo.isPaid, orderInfo.airline,orderInfo.takeOffTime, orderInfo.estTime, orderInfo.price, orderInfo.date, orderInfo.fdate);

    /* Execute SQL statement */
    char* zErrMsg = 0;
    ret = sqlite3_exec(db, sql, nullptr, 0, &zErrMsg);
    if (ret != SQLITE_OK) {
        printf("%d\n", ret);
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    else {
        printf("%d\n", ret);
        fprintf(stdout, "Records created successfully\n");
    }

    return 0;
}

int addFlight(sqlite3* db, flightInfo flight) {
    char sql[1024];
    int ret;
    //char seatInfo[sizeof(flight.seatInfo)+100];
    //memcpy(seatInfo,&flight.seatInfo,sizeof(flight.seatInfo));

    /*printf("INSERT INTO Flight (flightNumber,airline,departure,land,takeOffTime,estTime,price1,price2,remain1,remain2,type,onTimePerf,pilot1,pilot2) "\
        "VALUES ('%s','%s','%s','%s',%.3lf,%.3lf,%d,%d,%d,%d,'%s',%.3lf,'%s','%s')",
        flight.flightNumber,flight.airline,flight.departure,flight.land,flight.takeOffTime,flight.estTime,flight.price1,flight.price2,flight.remain1,flight.remain2,flight.type,flight.onTimePerf,flight.pilot1,flight.pilot2);*/

    sprintf(sql, "INSERT INTO Flight (flightNumber,airline,departure,land,takeOffTime,estTime,price1,price2,remain1,remain2,type,onTimePerf,pilot1,pilot2) "\
        "VALUES ('%s','%s','%s','%s',%.3lf,%.3lf,%d,%d,%d,%d,'%s',%.3lf,'%s','%s')",
        flight.flightNumber, flight.airline, flight.departure, flight.land, flight.takeOffTime, flight.estTime, flight.price1, flight.price2, flight.remain1, 
        flight.remain2, flight.type, flight.onTimePerf, flight.pilot1, flight.pilot2);

    /* Execute SQL statement */
    char* zErrMsg = 0;
    ret = sqlite3_exec(db, sql, nullptr, 0, &zErrMsg);
    if (ret != SQLITE_OK) {
        printf("%d\n", ret);
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    else {
        printf("%d\n", ret);
        fprintf(stdout, "Records created successfully\n");
        return 1;
    }

    return 0;
}

int orderCheck(int OUID, int UUID) {
    return 0;
}

int loginUser(sqlite3* db, char* ID, char* password) {
    userInfo user;
    if (getUserInfo(db, &user, ID)) {
        printf("login Error\n");
        return 0;
    }
    else if (strcmp(user.password, password) == 0)
        return 1;
    else return 0;
}

int changePaid(sqlite3* db, int OUID) {
    char sql[100];
    sprintf(sql,"UPDATE Orders set isPaid = 1 where OUID=%d; ",
            OUID);
    char* zErrMsg = 0;
    /* Execute SQL statement */
    int ret = sqlite3_exec(db, sql, nullptr, nullptr, &zErrMsg);
    if (ret != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return 1;
    }
    else {
        fprintf(stdout, "update done successfully\n");
        return 0;
    }
}

int loginAdmin(sqlite3* db, char* ID, char* password) {
    adminInfo admin;
    if (getAdminInfo(db, &admin, ID)) {
        printf("login Error\n");
        return 0;
    }
    else if (strcmp(admin.password, password) == 0)
        return 1;
    else return 0;
}

CString getUserName(int UUID) {
    userInfo info;

    char sql[100];
    sprintf(sql, "SELECT * from User WHERE UID = %d", UUID);
    //const char* data = "Callback function called";
    //userInfo data[maxn];
    //const userInfo* data = dest;
    /* Execute SQL statement */
    callbackCount = 0;
    int ret;
    char* execMsg;
    ret = sqlite3_exec(db, sql, callback_userInfo, (void*)&info, &execMsg);
    if (ret != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", execMsg);
        sqlite3_free(execMsg);
        return _T("Error");
    }
    else {
        fprintf(stdout, "getUserInfo done successfully\n");
        return CString(info.ID);
    }
}

int changeUserInfo(int type,char* value) {
    char sql[100];
    switch (type) {
    case 1:
        sprintf(sql, "UPDATE User SET password = '%s' WHERE UID = %d", value, thisUUID);
        break;    
    case 2:
        sprintf(sql, "UPDATE User SET phone = %s WHERE UID = %d", value, thisUUID);
        break;
    case 3:
        sprintf(sql, "UPDATE User SET email = '%s' WHERE UID = %d", value, thisUUID);
        break;
    }
    char* zErrMsg = 0;
    /* Execute SQL statement */
    int ret = sqlite3_exec(db, sql, nullptr, nullptr, &zErrMsg);
    if (ret != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return 1;
    }
    else {
        fprintf(stdout, "update done successfully\n");
        return 0;
    }
}

int changeAdminInfo(int type, char* value) {
    char sql[100];
    switch (type) {
    case 1:
        sprintf(sql, "UPDATE Admin SET password = '%s' WHERE UID = %d", value, thisUUID);
        break;
    /*case 2:
        sprintf(sql, "UPDATE User SET phone = %s WHERE ID = %d", value, thisUUID);
        break;*/
    case 3:
        sprintf(sql, "UPDATE Admin SET email = '%s' WHERE UID = %d", value, thisUUID);
        break;
    }
    char* zErrMsg = 0;
    /* Execute SQL statement */
    int ret = sqlite3_exec(db, sql, nullptr, nullptr, &zErrMsg);
    if (ret != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return 1;
    }
    else {
        fprintf(stdout, "update done successfully\n");
        return 0;
    }
}

int deleteOrder(sqlite3* db, int OUID) {
    char sql[100];
    if (OUID >= 0)
        sprintf(sql, "DELETE from Orders WHERE OUID == %d\n", OUID);
    else return 1;
    //printf("SELECT * from Order WHERE UUID == %d\n",UUID);
    /* Execute SQL statement */
    callbackCount = 0;
    int ret;
    char* execMsg;
    ret = sqlite3_exec(db, sql, nullptr,nullptr, &execMsg);
    //ret = sqlite3_exec(db, sql, callback_order, nullptr, nullptr);
    if (ret != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", execMsg);
        sqlite3_free(execMsg);
        return 1;
    }
    else {
        fprintf(stdout, "deleteOrder done successfully\n");
    }
    //memcpy(dest,&data,sizeof(data));
    return 0;
}

int getFlightInfoByCol(sqlite3* db, flightInfo* dest, char* col,char* name) {
    char sql[100];
    sprintf(sql, "SELECT * from Flight WHERE %s GLOB '%s'", col,name);
    //else sprintf(sql, "SELECT * from Flight");
    /* Execute SQL statement */
    callbackCount = 0;
    int ret;
    char* execMsg = 0;
    //ret = sqlite3_exec(db, sql, callback_flight, (void*)dest, &execMsg);
    ret = sqlite3_exec(db, sql, callback_flight, (void*)dest, nullptr);
    if (ret != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", execMsg);
        sqlite3_free(execMsg);
        return 1;
    }
    else {
        fprintf(stdout, "getFlight done successfully\n");
    }
    //memcpy(dest,&data,sizeof(data));
    return 0;
}

int boughtFlight(sqlite3* db, int FUID,int Num,int isPro) {
    char sql[100];
    if (!isPro)
        sprintf(sql, "UPDATE Flight set remain1 = %d where UID=%d; ",Num,FUID);
    else
        sprintf(sql, "UPDATE Flight set remain2 = %d where UID=%d; ", Num, FUID);
    char* zErrMsg = 0;
    /* Execute SQL statement */
    int ret = sqlite3_exec(db, sql, nullptr, nullptr, &zErrMsg);
    if (ret != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        return 1;
    }
    else {
        fprintf(stdout, "update done successfully\n");
        return 0;
    }
}

int getTicketNum(sqlite3* db, int gDate, char* flightNumber) {
    char sql[100];
    if (gDate) sprintf(sql, "SELECT * from Orders WHERE flightNumber GLOB '%s' AND fdate = %d", flightNumber, gDate);
    else return 0;
    //else sprintf(sql, "SELECT * from Flight");
    /* Execute SQL statement */
    callbackCount = 0;
    int ret;
    char* execMsg = 0;
    order dest[100];
    memset(dest, 0, sizeof(dest));
    //ret = sqlite3_exec(db, sql, callback_flight, (void*)dest, &execMsg);
    ret = sqlite3_exec(db, sql, callback_order, (void*)dest, nullptr);
    if (ret != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", execMsg);
        sqlite3_free(execMsg);
        return -1;
    }
    else {
        fprintf(stdout, "getFlight done successfully\n");
        int n = 0, p1 = 0,p2 = 0;
        while (dest[n].OUID >= 0) {
            if (dest[n].tier == 1) p1 += dest[n].number;
            else p2 += dest[n].number;
            n++;
        }
        return (p1 << 16) + p2;
    }
}