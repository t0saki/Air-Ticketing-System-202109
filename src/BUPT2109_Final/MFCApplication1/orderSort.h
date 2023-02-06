#pragma once
#include "execsqlite3.h"

void orderSortByTime(order* src, int size);

void orderSortByIncome(order* src, int size);

int checkOrder(order* src, order newOrder, int size, int date);