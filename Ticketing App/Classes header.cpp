#include<cstdlib>
#include <iostream>
#include <string>
#include <unordered_map>
#include <random>
#include<fstream>
#include<map>
#include<vector>
using namespace std;

class EventLocation {
private:
	int maxSeats = 0;
	int numRows = 0;
	int numZones = 0;
	const int CAENCode;
	unordered_map<int, string> seatCoding;  // seat number -> seat code
	vector<bool> seats;  // true: seat is taken, false: seat is free
	static string CINEMAname;
public:

	EventLocation() :CAENCode(0)
	{
		this->maxSeats = 0;
		this->numRows = 0;
		this->numZones = 0;
	}
	EventLocation(int maxSeats, int numRows, int numZones, int caencode = 0) :CAENCode(caencode)
	{
		this->maxSeats = maxSeats;
		this->numRows = numRows;
		this->numZones = numZones;
		this->seats.resize(maxSeats, false);  // initialize all seats to be free
	}
	EventLocation(const EventLocation& location) :CAENCode(location.CAENCode)
	{
		this->maxSeats = location.maxSeats;
		this->numRows = location.numRows;
		this->numZones = location.numZones;
		this->seats.resize(location.maxSeats, false);
	}
	EventLocation& operator=(const EventLocation& location)
	{
		if (this != &location)
		{
			this->maxSeats = location.maxSeats;
			this->numRows = location.numRows;
			this->numZones = location.numZones;
			this->seats.resize(location.maxSeats, false);
		}
		return *this;
	}
	int getMaxSeats()const { return this->maxSeats; }
	int getNumRows()const { return this->numRows; }
	int getNumZones() const { return numZones; }
	unordered_map<int, string> getSeatCoding() { return seatCoding; }
	static void setName(string name) { EventLocation::CINEMAname = name; }
	static string getName() { return CINEMAname; }

	// Add a seat coding to the event location
	void addSeatCoding(int seatNumber, string seatCode)
	{
		seatCoding[seatNumber] = seatCode;
	}
	// Mark a seat as taken
	void markSeatTaken(int seatNumber)
	{
		seats[seatNumber - 1] = true;
	}
	// Check if a seat is free
	bool isSeatFree(int seatNumber)
	{
		return !seats[seatNumber - 1];
	}
	friend class Ticket;
};

class event
{
	friend class ticket;
private:
	string movieName;
	int timeStart;
	int normal, normalPrice;
	int vip, vipPrice;
	int d, m, y;

	event()
	{
		movieName = "";
		timeStart = 0;
		normal = 0;
		normalPrice = 0;
		vip = 0;
		vipPrice = 0;
		d, m, y = 0;
	}
	event(string movieName, int timeStart, int normal, int normalPrice, int vip, int vipPrice, int d, int m, int y)
	{
		this->movieName = movieName;
		this->timeStart = timeStart;
		this->normal = normal;
		this->normalPrice = normalPrice;
		this->vip = vip;
		this->vipPrice = vipPrice;
		this->d = d;
		this->m = m;
		this->y = y;
	}
	event(const event& e)
	{
		this->movieName = e.movieName;
		this->timeStart = e.timeStart;
		this->normal = e.normal;
		this->normalPrice = e.normalPrice;
		this->vip = e.vip;
		this->vipPrice = e.vipPrice;
		this->d = e.d;
		this->m = e.m;
		this->y = e.y;
	}
	event& operator=(const event& e)
	{
		if (this != &e)
		{
			this->movieName = e.movieName;
			this->timeStart = e.timeStart;
			this->normal = e.normal;
			this->normalPrice = e.normalPrice;
			this->vip = e.vip;
			this->vipPrice = e.vipPrice;
			this->d = e.d;
			this->m = e.m;
			this->y = e.y;
		}
		return *this;
	}
	void setMovieName(string MovieName)
	{
		this->movieName = MovieName;
	}
	string getMovieName()
	{
		return this->movieName;
	}
	void setTimeStart(int timestart)
	{
		this->timeStart = timestart;
	}
	int getTimeStart()
	{
		return this->timeStart;
	}
	void setNormalSeats(int normalseats)
	{
		this->normal = normalseats;
	}
	int setNormalSeats()
	{
		return this->normal;
	}
	void setNormalSeatsPrice(int normalseatsprice)
	{
		this->normalPrice = normalseatsprice;
	}
	int setNormalSeatsPrice()
	{
		return this->normalPrice;
	}
	void setVipSeats(int vipseats)
	{
		this->vip = vipseats;
	}
	int setVIPSeats()
	{
		return this->vip;
	}
	void setVipSeatsPrice(int vipseatsprice)
	{
		this->vipPrice = vipseatsprice;
	}
	int setVipSeatsPrice()
	{
		return this->vipPrice;
	}
	void setDay(int day)
	{
		this->d = day;
	}
	int getDay()
	{
		return this->d;
	}
	void setMonth(int month)
	{
		this->m = month;
	}
	int getMonth()
	{
		return this->m;
	}
	void setYear(int year)
	{
		this->y = year;
	}
	int getYear()
	{
		return this->y;
	}
	friend ostream& operator<<(ostream& out, event e);
};

class ticket
{
private:
	int ticketID;
	event movieName;
	event timeStart;
	char* client;
	bool normalOrVip;
	int noSeats;
	event d, m, y;
public:
	ticket()
	{
		ticketID = rand() % 10000000;
		client = nullptr;
		normalOrVip = 0;
		noSeats = 0;
	}
	ticket(char* client, int age, bool normalOrVip, int noSeats, int d, int m, int y)
	{
		this->client = new char[strlen(client) + 1];
		strcpy_s(this->client, strlen(client + 1), client);
		this->normalOrVip = normalOrVip;
		this->noSeats = noSeats;

	}
	//ticket(const ticket& t)
	//{

	//	this->client = new char[strlen(t.client) + 1];
	//	strcpy_s(this->client, strlen(t.client + 1), t.client);
	//	this->normalOrVip = t.normalOrVip;
	//	this->noSeats = t.noSeats;
	//	this->movieName = t.movieName;
	//	this->timeStart = t.timeStart;

	//}
	~ticket()
	{
		if (client != nullptr)
		{
			delete[] client;
		}
	}
	ticket& operator=(const ticket& t)
	{
		if (this != &t)
			if (client != nullptr)
			{
				delete[] client;
			}
		//this->ticketID = t.ticketID;
		this->client = new char[strlen(t.client) + 1];
		strcpy_s(this->client, strlen(t.client + 1), t.client);
		this->normalOrVip = t.normalOrVip;
		this->noSeats = t.noSeats;
		return *this;
	};
	void setTicketId()
	{
		int ticket = rand();
		this->ticketID = ticket;
	}
	int getTicketId()
	{
		return this->ticketID;
	}
	void setClient(char* client)
	{
		this->client = client;
	}
	char* getClient()
	{
		return this->client;
	}
	void setNormalOrVip(bool normalOrVip)
	{
		this->normalOrVip = normalOrVip;
	}
	bool getNormalOrVip()
	{
		if (this->normalOrVip = 0)
			return "n";
		else
			return "v";
	}
	void setNoSeats(int noSeats)
	{
		this->noSeats = noSeats;
	}
	int getNoSeats()
	{
		return this->noSeats;
	}
	friend ostream& operator<<(ostream& out, ticket t);
};