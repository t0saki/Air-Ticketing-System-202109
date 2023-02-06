#include "pch.h"
#include "flightSort.h"

void flightSortByTime(flightInfo* src, int size) {
	flightInfo info[100];
	memcpy(info, src, size * sizeof(flightInfo));
	//begin
	int i = 0, j = 0;
	for (i = 0; i < size - 1; i++) {
		for (j = 0; j < size - i - 1; j++) {
			if (info[j].takeOffTime > info[j + 1].takeOffTime) {
				flightInfo temp;
				temp = info[j];
				info[j] = info[j + 1];
				info[j + 1] = temp;
			}
		}
	}



	//end
	memcpy(src, info, size * sizeof(flightInfo));
}

void flightSortByPrice(flightInfo* src, int size) {
	flightInfo info[100];
	memcpy(info, src, size * sizeof(flightInfo));
	//begin
	int i = 0, j = 0;
	for (i = 0; i < size - 1; i++) {
		for (j = 0; j < size - i - 1; j++) {
			if (info[j].price1 > info[j + 1].price1) {
				flightInfo temp;
				temp = info[j];
				info[j] = info[j + 1];
				info[j + 1] = temp;
			}
		}
	}
	memcpy(src, info, size * sizeof(flightInfo));
}


int checkFlight1(flightInfo* src, flightInfo newFlight, int size) {
	flightInfo info[100];
	flightSortByTime(src, size);
	memcpy(info, src, size * sizeof(flightInfo));
	int i = 1;
	for (i = 1; i < size; i++) {
		if (info[i].takeOffTime + info[i].estTime + 12800 > info[i - 1].takeOffTime) {
			return 0;
		}
	}
	return 1;
}

int checkFlight2(flightInfo* src, flightInfo newFlight, int size) {
	flightInfo info[100];
	flightSortByTime(src, size);
	memcpy(info, src, size * sizeof(flightInfo));
	int i = 1;
	for (i = 1; i < size; i++) {
		if (info[i].takeOffTime + info[i].estTime + 12800 > info[i - 1].takeOffTime) {
			return 0;
		}
	}
	return 1;
}