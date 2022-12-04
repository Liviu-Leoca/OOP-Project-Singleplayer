#include<iostream>
#include<string>

using namespace std;

class location{
	friend class event;
private:
	int* maxSeats;
	int rows;
	int vipOrNah;
	const int CAENCode;
public:
	static string CINEMAname;

	location() :CAENCode(1234)
	{
		maxSeats = nullptr;
		rows = 0;
		vipOrNah = 0;

	}

	location(int caencode,int* maxSeats, int rows, int vipOrNah) :CAENCode(caencode)
	{
		if (maxSeats != nullptr && vipOrNah > 0)
		{
			this->maxSeats = new int[vipOrNah];
			for (int i = 0; i < vipOrNah; i++)
			{
				this->maxSeats[i] = maxSeats[i];
			}
			this->vipOrNah = vipOrNah;

		}
		else
		{
			this->maxSeats = nullptr;

		}
		this->rows = rows;
		this->vipOrNah = vipOrNah;
	}
	~location()
	{
		if (this->maxSeats != nullptr)
			delete[] this->maxSeats;
	}
	location(const location& l) :CAENCode(l.CAENCode)
	{
		if (l.maxSeats != nullptr && l.vipOrNah > 0)
		{
			this->maxSeats = new int[l.vipOrNah];
			for (int i = 0; i < l.vipOrNah; i++)
			{
				this->maxSeats[i] = l.maxSeats[i];
			}
			this->vipOrNah = l.vipOrNah;
		}
		else
		{
			this->maxSeats = nullptr;
		}
		this->rows = l.rows;
		this->vipOrNah = l.vipOrNah;
	}
	location& operator=(const location& l)
	{
		if (this != &l)
		{
			if (l.maxSeats != nullptr && l.vipOrNah > 0)
			{
				if (maxSeats != nullptr)
				{
					delete[] maxSeats;
				}
				this->maxSeats = new int[l.vipOrNah];
				for (int i = 0; i < l.vipOrNah; i++)
				{
					this->maxSeats[i] = l.maxSeats[i];
				}
				this->vipOrNah = l.vipOrNah;
			}
			else
			{
				this->maxSeats = nullptr;

			}
			this->rows = l.rows;
			this->vipOrNah = l.vipOrNah;
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
	string movieName;
	int timeStart;
	location maxSeats;
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
	event(char* movieName, int timeStart, int normal, int normalPrice, int vip, int vipPrice, int d, int m, int y)
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
	ticket()
	{
		ticketID = 0;
		client = nullptr;
		normalOrVip = 0;
		noSeats = 0;
	}
	ticket(int ticketID, char* client, int age, bool normalOrVip, int noSeats, int d, int m, int y)
	{
		this->ticketID = ticketID;
		this->client = new char[strlen(client) + 1];
		strcpy_s(this->client, strlen(client + 1), client);
		this->normalOrVip = normalOrVip;
		this->noSeats = noSeats;

	}
	ticket(const ticket& t)
	{
		this->ticketID = t.ticketID;
		this->client = new char[strlen(t.client) + 1];
		strcpy_s(this->client, strlen(t.client + 1), t.client);
		this->normalOrVip = t.normalOrVip;
		this->noSeats = t.noSeats;

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
		this->normalOrVip = t.normalOrVip;
		this->noSeats = t.noSeats;
		return *this;
	};
};