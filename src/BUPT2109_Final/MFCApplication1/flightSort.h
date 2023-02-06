#pragma once
#include "execsqlite3.h"

void flightSortByTime(flightInfo* src, int size);

void flightSortByPrice(flightInfo* src, int size);

int checkFlight1(flightInfo* src, flightInfo newFlight, int size);

int checkFlight2(flightInfo* src, flightInfo newFlight, int size);