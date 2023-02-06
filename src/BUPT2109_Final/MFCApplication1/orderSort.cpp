
#include "pch.h"
#include "orderSort.h"


void orderSortByTime(order* src, int size) {
	order orders[100];
	memcpy(orders, src, size * sizeof(order));
	//begin
	int i = 0, j = 0;
	for (i = 0; i < size - 1; i++)
	{
		for (j = 0; j < size - i - 1; j++)
		{
			if (orders[j].takeOffTime > orders[j + 1].takeOffTime)
			{
				order temp;
				temp = orders[j];
				orders[j] = orders[j + 1];
				orders[j + 1] = temp;
			}
		}
	}
	//end
	memcpy(src, orders, size * sizeof(order));
}

void orderSortByIncome(order* src, int size) {
	order orders[100];
	memcpy(orders, src, size * sizeof(order));
	//begin
	int i = 0, j = 0;
	for (i = 0; i < size - 1; i++)
	{
		for (j = 0; j < size - i - 1; j++)
		{
			if (orders[j].price* orders[j].number < orders[j+1].price * orders[j+1].number)
			{
				order temp;
				temp = orders[j];
				orders[j] = orders[j + 1];
				orders[j + 1] = temp;
			}
		}
	}
	//end
	memcpy(src, orders, size * sizeof(order));
}

int checkOrder(order* src, order newOrder, int size, int date)
{
	order orders[100];
	memcpy(orders, src, size * sizeof(order));
	//begin
	int i = 0;
	int k = 0;
	int j = 0;
	int number = 0;
	orderSortByTime(src, size);
	for (; i < size; i++)
	{
		if (orders[i].date == date)
		{
			orders[i].price = -1;
		}
	}
	for (; k < size; k++)
	{
		if (orders[k].price == -1)
		{
			number = number + orders[k].number;
		}
	}
	if (number + newOrder.number > 5)
	{
		return 0;
	}
	else
	{
		for (; j < size; j++)
		{
			if ((newOrder.takeOffTime - orders[j].takeOffTime - orders[j].estTime < 10800.0) && (newOrder.fdate == orders[j].fdate))
			{
				return 0;
			}
		}
		return 1;
	}



	//end
	//memcpy(src, orders, size * sizeof(order));
}