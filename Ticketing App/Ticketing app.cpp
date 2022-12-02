#include<iostream>

using namespace std;
class location {
private:
	int* maxSeats;
	int rows;
	string zone;
	const int CAENCode;
private:
	static string CINEMAname;
};

class event
{
	friend class ticket;
private:
	char* movieName;
	int timeStart;


	int normal, normalPrice;
	int vip, vipPrice;
	int d, m, y;
};

class ticket
{
private:
	int ticketID;
	event movieName;
	event timeStart;
	char* client;
	int age;
	string normalOrVip;
	int noSeats;
	int d, m, y;
};

int main()
{
	std::cout << std::endl << "Hello World!";
}