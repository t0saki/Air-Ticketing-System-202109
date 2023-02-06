#pragma once



/*
typedef struct {
    int n;                      //最多1000个座位，该航班有n个
    char seatNumber[1000][6];   //每个座位内部编号对应的座位号(比如，第105个座位是Y34A)
    int tier[1000];             //每个作为内部编号对应的等级(最多5个等级)
    int price[5];               //每个等级对应的价格
    int remain[5];              //每个等级对应的剩票
}seat;
*/

typedef struct {
    int FUID;
    char flightNumber[10];      //航班号
    char airline[32];           //航司
    char departure[10];         //起飞地
    char land[10];              //降落地
    double takeOffTime;         //起飞时间
    double estTime;             //预计飞行时间
    //seat seatInfo;              //仓位信息
    char type[10];              //机型
    double onTimePerf;          //准点率
    char pilot1[10];            //驾驶员
    char pilot2[10];
    int price1, price2, remain1, remain2;
}flightInfo;

typedef struct {
    int UID;
    char ID[15];
    char name[15];
    int gender;
    long long phone;
    char password[16];
    char email[32];
}userInfo;

typedef struct {
    int UID;
    char ID[15];
    char airline[32];
    char name[15];
    char password[16];
    char email[32];
}adminInfo;

/**
typedef struct {
    userInfo info;
    char password[16];
}userInfo_withPW;

typedef struct {
    adminInfo info;
    char password[16];
}adminInfo_withPW;
**/

typedef struct {
    int OUID, UUID;
    char flightNumber[10];
    int number, tier, isPaid;
    char airline[32];
    double takeOffTime, estTime;
    int price,date,fdate;
}order;

typedef struct {
    int y, m, d;
}tdate;

typedef struct {
    int h, m, s;
}ttime;
