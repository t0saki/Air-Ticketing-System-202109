#pragma once



/*
typedef struct {
    int n;                      //���1000����λ���ú�����n��
    char seatNumber[1000][6];   //ÿ����λ�ڲ���Ŷ�Ӧ����λ��(���磬��105����λ��Y34A)
    int tier[1000];             //ÿ����Ϊ�ڲ���Ŷ�Ӧ�ĵȼ�(���5���ȼ�)
    int price[5];               //ÿ���ȼ���Ӧ�ļ۸�
    int remain[5];              //ÿ���ȼ���Ӧ��ʣƱ
}seat;
*/

typedef struct {
    int FUID;
    char flightNumber[10];      //�����
    char airline[32];           //��˾
    char departure[10];         //��ɵ�
    char land[10];              //�����
    double takeOffTime;         //���ʱ��
    double estTime;             //Ԥ�Ʒ���ʱ��
    //seat seatInfo;              //��λ��Ϣ
    char type[10];              //����
    double onTimePerf;          //׼����
    char pilot1[10];            //��ʻԱ
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
