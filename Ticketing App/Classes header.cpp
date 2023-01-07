#include<cstdlib>
#include <iostream>
#include <string>
#include <unordered_map>
#include <random>
#include<fstream>
#include<map>
#include<vector>
using namespace std;

enum class Zone { Normal, VIP };

class EventLocation {
private:
	int maxSeats = 0;
	int numRows = 0;
	vector<Zone> seatZones;  // zone of each seat
	const int CAENCode;
	unordered_map<int, string> seatCoding;  // seat number -> seat code
	vector<bool> seats;  // true: seat is taken, false: seat is free
	static string CINEMAname;
public:

	EventLocation() :CAENCode(0)
	{
		this->maxSeats = 0;
		this->numRows = 0;
		this->seatZones.resize(maxSeats);
		this->seats.resize(maxSeats, false);
	}
	EventLocation(int maxSeats, int numRows, int caencode = 0) :CAENCode(caencode)
	{
		this->maxSeats = maxSeats;
		this->numRows = numRows;
		this->seatZones.resize(maxSeats);
		this->seats.resize(maxSeats, false);  // initialize all seats to be free
	}
	EventLocation(const EventLocation& location) :CAENCode(location.CAENCode)
	{
		this->maxSeats = location.maxSeats;
		this->numRows = location.numRows;
		this->seatZones.resize(location.maxSeats);
		this->seats.resize(location.maxSeats, false);
	}
	EventLocation& operator=(const EventLocation& location)
	{
		if (this != &location)
		{
			this->maxSeats = location.maxSeats;
			this->numRows = location.numRows;
			this->seatZones.resize(location.maxSeats);
			this->seats.resize(location.maxSeats, false);
		}
		return *this;
	}
	int getMaxSeats()const { return this->maxSeats; }
	int getNumRows()const { return this->numRows; }

	unordered_map<int, string> getSeatCoding() { return seatCoding; }
	static void setName(string name) { EventLocation::CINEMAname = name; }
	static string getName() { return CINEMAname; }

	// Add a seat coding to the event location
	void addSeatCoding(int seatNumber, string seatCode, Zone seatZone)
	{
		seatCoding[seatNumber] = seatCode;
		seatZones[seatNumber - 1] = seatZone;
	}

	// Mark a seat as taken
	void markSeatTaken(int seatNumber)
	{
		seats[seatNumber - 1] = true;
	}
	// Check if a seat is free
	bool isSeatFree(int seatNumber)
	{
		Zone zone = Zone::Normal;
		// Check if seat is free in the specified zone
		if (zone == Zone::Normal)
		{
			// Check if seat is free in the normal zone
			return !seats[seatNumber - 1];
		}
		else if (zone == Zone::VIP)
		{
			// Check if seat is free in the VIP zone
			// You can implement this by checking if the seat is in the range of VIP seats
			// For example, if the VIP zone starts at seat number 1 and has 10 seats,
			// you can check if the seat number is between 1 and 10 (inclusive)
			return (seatNumber >= 1 && seatNumber <= 10) && !seats[seatNumber - 1];
		}
	}


	friend class Ticket;
};


class Event :public EventLocation {
private:
	string name;
	string date;
	string time;

public:
	Event()
	{
		this->name = "";
		this->date = "";
		this->time = "";
	};
	Event(string name, string date, string time)
	{
		this->name = name;
		this->date = date;
		this->time = time;
	}
	string getName()
	{
		return this->name;
	}
	friend class Ticket;
};

class Ticket {
private:
	int id;
	string eventName;
	int seatNumber;
	string ticketType;
	static vector<int> issuedIds;  // list of IDs of tickets that have been issued

	Event event;
	EventLocation location;
public:
	Ticket()
	{
		this->id = 0;
		this->eventName = event.getName();
		this->seatNumber = 0;
		this->ticketType = "";
		this->event = Event();
		this->location = EventLocation(0, 0, 0);
	}
	// Generate a ticket for the given event and ticket characteristics
	Ticket(string ticketType, int seatNumber)
	{
		this->id = generateTicketId();
		this->eventName = event.getName();
		this->location = location;
		this->seatNumber = seatNumber;
		this->ticketType = ticketType;
	}
	Ticket(const Ticket& t)
	{
		this->id = generateTicketId();
		this->eventName = event.getName();
		this->location = t.location;
		this->seatNumber = t.seatNumber;
		this->ticketType = t.ticketType;
	}
	Ticket& operator= (const Ticket& t)
	{
		if (this != &t)
		{
			this->id = generateTicketId();
			this->eventName = event.getName();
			this->location = t.location;
			this->seatNumber = t.seatNumber;
			this->ticketType = t.ticketType;
		}
		return *this;
	}

	int getTicketID() { return this->id; }
	int getSeatNumber() { return this->seatNumber; }
	string getTicketType() { return this->ticketType; }
	string getEventName() { return this->eventName; }

	// Generate a random ticket ID using a random number generator
	int generateTicketId() {
		static mt19937 rng(random_device{}());
		static uniform_int_distribution<int> dist;
		return dist(rng);
	}

	// Check if the ticket is unique
	bool isUnique() const {
		for (int issuedId : issuedIds) {
			if (issuedId == id) {
				return false;  // ID already exists in the list, ticket is not unique
			}
		}
		return true;  // ID not found in the list, ticket is unique
	}

	void writeToBinaryFile(ofstream& out)
	{
		out.write((char*)&id, sizeof(id));
		out.write((char*)&eventName, sizeof(eventName));
		out.write((char*)&seatNumber, sizeof(seatNumber));
		out.write((char*)&ticketType, sizeof(ticketType));
		out.close();
	}

	void saveToBinaryFile(const string& filename) {
		ofstream file(filename, ios::binary);
		file.write(reinterpret_cast<char*>(this), sizeof(*this));
		file.close();
	}
	void readFromBinaryFile(ifstream& in)
	{
		in.read((char*)&id, sizeof(id));
		in.read((char*)&eventName, sizeof(eventName));
		in.read((char*)&seatNumber, sizeof(seatNumber));
		in.read((char*)&ticketType, sizeof(ticketType));
		in.close();
	}
	//friend ostream& operator<<(ostream&, Ticket);
	//friend istream& operator>>(istream&, Ticket&);

	friend ostream& operator<<(ostream& out, const Ticket& ticket) {
		out.write((char*)&ticket.id, sizeof(ticket.id));
		out.write((char*)&ticket.eventName, sizeof(ticket.eventName));
		out.write((char*)&ticket.seatNumber, sizeof(ticket.seatNumber));
		out.write((char*)&ticket.ticketType, sizeof(ticket.ticketType));
		return out;
	}

	friend std::istream& operator>>(std::istream& in, Ticket& ticket) {
		in.read(reinterpret_cast<char*>(&ticket.id), sizeof(ticket.id));
		in.read(reinterpret_cast<char*>(&ticket.eventName), sizeof(ticket.eventName));
		in.read(reinterpret_cast<char*>(&ticket.seatNumber), sizeof(ticket.seatNumber));
		in.read(reinterpret_cast<char*>(&ticket.ticketType), sizeof(ticket.ticketType));
		return in;
	}
};