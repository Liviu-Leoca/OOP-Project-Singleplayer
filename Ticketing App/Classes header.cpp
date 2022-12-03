#include<iostream>
#include<string>

using namespace std;

class location {
private:
	int* maxSeats;
	int rows;
	string zone;
	const int CAENCode;
private:
	static string CINEMAname;

	location() :CAENCode(1234)
	{
		maxSeats = nullptr;
		rows = 0;
		zone = "unknown";
	}

	location(int* maxSeats, int rows, string zone) :CAENCode(1234)
	{
		if (maxSeats != nullptr && rows > 0)
		{
			this->maxSeats = new int[rows];
			for (int i = 0; i < rows; i++)
			{
				this->maxSeats[i] = maxSeats[i];
			}
			this->rows = rows;
		}
		else
		{
			this->maxSeats = nullptr;
			this->rows = 0;
		}
		this->rows = rows;
		this->zone = zone;
	}
	~location()
	{
		if (this->maxSeats != nullptr)
			delete[] this->maxSeats;
	}
	location(const location& l) :CAENCode(1234)
	{
		if (l.maxSeats != nullptr && l.rows > 0)
		{
			this->maxSeats = new int[l.rows];
			for (int i = 0; i < l.rows; i++)
			{
				this->maxSeats[i] = l.maxSeats[i];
			}
			this->rows = l.rows;
		}
		else
		{
			this->maxSeats = nullptr;
			this->rows = 0;
		}
		this->rows = l.rows;
		this->zone = l.zone;
	}
	location& operator=(const location& l)
	{
		if (this != &l)
		{
			if (l.maxSeats != nullptr && l.rows > 0)
			{
				if (maxSeats != nullptr)
				{
					delete[] maxSeats;
				}
				this->maxSeats = new int[l.rows];
				for (int i = 0; i < l.rows; i++)
				{
					this->maxSeats[i] = l.maxSeats[i];
				}
				this->rows = l.rows;
			}
			else
			{
				this->maxSeats = nullptr;
				this->rows = 0;
			}
			this->rows = l.rows;
			this->zone = l.zone;
		}
		return *this;
	}
	static void setName(string name)
	{
		location::CINEMAname = name;
	}
	static string getName()
	{
		return CINEMAname;
	}
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

	event()
	{
		movieName = nullptr;
		timeStart = 0;
		normal = 0;
		normalPrice = 0;
		vip = 0;
		vipPrice = 0;
		d, m, y = 0;
	}
	event(char* movieName, int timeStart, int normal, int normalPrice, int vip, int vipPrice, int d, int m, int y)
	{
		if (movieName != nullptr)
		{
			this->movieName = new char[strlen(movieName) + 1];
			strcpy_s(this->movieName, strlen(movieName) + 1, movieName);
		}
		else
		{
			this->movieName = nullptr;
		}
		this->timeStart = timeStart;
		this->normal = normal;
		this->normalPrice = normalPrice;
		this->vip = vip;
		this->vipPrice = vipPrice;
		this->d = d;
		this->m = m;
		this->y = y;
	}
	~event()
	{
		if (this->movieName != nullptr)
			delete[] this->movieName;
	}
	event(const event& e)
	{
		if (e.movieName != nullptr)
		{
			this->movieName = new char[strlen(e.movieName) + 1];
			strcpy_s(this->movieName, strlen(e.movieName) + 1, e.movieName);
		}
		else
		{
			this->movieName = nullptr;
		}
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
			if (e.movieName != nullptr)
			{
				if (movieName != nullptr)
				{
					delete[] movieName;
				}
				this->movieName = new char[strlen(e.movieName) + 1];
				strcpy_s(this->movieName, strlen(e.movieName) + 1, e.movieName);
			}
			else
			{
				this->movieName = nullptr;
			}
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
};

class ticket
{
private:
	int ticketID;
	event movieName;
	event timeStart;
	char* client;
	int age;
	bool normalOrVip;
	int noSeats;
	int d, m, y;
	ticket()
	{
		ticketID = 0;
		client = nullptr;
		age = 0;
		normalOrVip = 0;
		noSeats = 0;
		d, m, y = 0;
	}
	ticket(int ticketID, char* client, int age, bool normalOrVip, int noSeats, int d, int m, int y)
	{
		this->ticketID = ticketID;
		this->client = new char[strlen(client) + 1];
		strcpy_s(this->client, strlen(client + 1), client);
		this->age = age;
		this->normalOrVip = normalOrVip;
		this->noSeats = noSeats;
		this->d = d;
		this->m = m;
		this->y = y;
	}
	ticket(const ticket& t)
	{
		this->ticketID = t.ticketID;
		this->client = new char[strlen(t.client) + 1];
		strcpy_s(this->client, strlen(t.client + 1), t.client);
		this->age = t.age;
		this->normalOrVip = t.normalOrVip;
		this->noSeats = t.noSeats;
		this->d = t.d;
		this->m = t.m;
		this->y = t.y;
	}
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
		this->ticketID = t.ticketID;
		this->client = new char[strlen(t.client) + 1];
		strcpy_s(this->client, strlen(t.client + 1), t.client);
		this->age = t.age;
		this->normalOrVip = t.normalOrVip;
		this->noSeats = t.noSeats;
		this->d = t.d;
		this->m = t.m;
		this->y = t.y;
		return *this;
	};

};