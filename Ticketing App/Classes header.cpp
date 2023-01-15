#include <iostream>
#include <string>
#include <unordered_map>
#include <random>
#include<fstream>
#include<map>
#include<vector>
using namespace std;

enum class Zone { Normal, VIP };

class Seats
{
	virtual int generateTicketId() = 0;
};

class EventLocation {
private:
	int rows = 0;
	int columns = 0;
	int seatCount = 0;
	bool** seats=nullptr;

public:
	EventLocation() {
		this->rows = 0;
		this->columns = 0;
        if (rows != 0 && columns != 0)
            this->seatCount = rows * columns;
        else
            this->seatCount = 0;
        this->seats = new bool* [rows];
        for (int i = 0; i < rows; i++) {
            this->seats[i] = new bool[columns];
        }
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                this->seats[i][j] = false;
            }
        }
	}
	EventLocation(int rows, int columns) {
		this->rows = rows;
		this->columns = columns;
        if (rows != 0 && columns != 0)
            this->seatCount = rows * columns;
        else
            this->seatCount = 0;
		this->seats = new bool* [rows];
		for (int i = 0; i < rows; i++) {
			this->seats[i] = new bool[columns];
		}
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) {
				this->seats[i][j] = false;
			}
		}
	}
	EventLocation(const EventLocation& location) {
		this->rows = location.rows;
		this->columns = location.columns;
        if (location.rows != 0 && location.columns != 0)
            this->seatCount = location.rows * location.columns;
        else
            this->seatCount = 0;
		this->seats = new bool* [location.rows];
		for (int i = 0; i < location.rows; i++) {
			this->seats[i] = new bool[location.columns];
		}
		for (int i = 0; i < location.rows; i++) {
			for (int j = 0; j < location.columns; j++) {
				this->seats[i][j] = false;
			}
		}
	}
	EventLocation& operator=(const EventLocation& location) {
		if (this != &location) {
			this->rows = location.rows;
			this->columns = location.columns;
            if (location.rows != 0 && location.columns != 0)
                this->seatCount = location.rows * location.columns;
            else
                this->seatCount = 0;
			this->seats = new bool* [location.rows];
			for (int i = 0; i < location.rows; i++) {
				this->seats[i] = new bool[location.columns];
			}
			for (int i = 0; i < location.rows; i++) {
				for (int j = 0; j < location.columns; j++) {
					this->seats[i][j] = false;
				}
			}
		}
		return *this;
	}
	~EventLocation() {
		if (this->seats != nullptr)
		{
			delete[] seats;
		}
	}
	int getRows()const { return rows; }
	int getColumns()const { return columns; }
	int getSeatCount()const { return seatCount; }
	void displaySeats() {
		for (int i = 0; i < seatCount; i++) {
			cout << (seats[i] ? 'X' : '.');
			if ((i + 1) % columns == 0) {
				cout << endl;
			}
		}
	}
    bool isSeatTaken(int seatNumber)
    {
        int col = seatNumber % columns;
        int row = seatNumber / columns;
        return seats[row][col];
    }
	friend class Ticket;
	friend ostream& operator<<(ostream&, EventLocation);
	friend istream& operator>>(istream&, EventLocation& location);
};


class Event :public EventLocation {
private:
	string name;
	string date;
	string time;
   // const string ReleaseDate;
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
	Event(const Event& e)
	{
		this->name = e.name;
		this->date = e.date;
		this->time = e.time;
	}
	string getName() { return name; }
	friend class Ticket;
	friend ostream& operator<<(ostream&, Event);
	friend istream& operator>>(istream&, Event&);
};

class Ticket : public Seats {
private:
    int id;
    string eventName;
    int numberOfSeats;
    int* seatNumber;
    string ticketType;
    static vector<int> issuedIds;
    static const int MAX_SEATS_PER_RESERVATION = 10;

    Event event;
    EventLocation location;
public:
    Ticket()
    {
        this->id = 0;
        this->eventName = event.getName();
        this->numberOfSeats = 1;
        this->seatNumber = nullptr;
        this->ticketType = "";
    }
    Ticket(string ticketType, int* seatNumber, int numberOfSeats)
    {
        this->id = generateTicketId();
        this->eventName = event.getName();
        this->numberOfSeats = numberOfSeats;
        this->seatNumber = new int[numberOfSeats];
        for (int i = 0; i < numberOfSeats; i++)
            this->seatNumber[i] = seatNumber[i];
        this->ticketType = ticketType;
    }
    Ticket(const Ticket& t)
    {
        this->id = generateTicketId();
        this->eventName = event.getName();
        this->numberOfSeats = t.numberOfSeats;
        this->seatNumber = new int[t.numberOfSeats];
        for (int i = 0; i < t.numberOfSeats; i++)
            this->seatNumber[i] = t.seatNumber[i];
        this->ticketType = t.ticketType;
    }
    Ticket& operator= (const Ticket& t)
    {
        if (this != &t)
        {
            this->id = generateTicketId();
            this->eventName = event.getName();
            this->numberOfSeats = t.numberOfSeats;
            this->seatNumber = new int[t.numberOfSeats];
            for (int i = 0; i < t.numberOfSeats; i++)
                this->seatNumber[i] = t.seatNumber[i];
            this->ticketType = t.ticketType;
        }
        return *this;
    }
    ~Ticket()
    {
        delete[] seatNumber;
    }
    int getTicketID() { return this->id; }
    int getNumberOfSeats() { return this->numberOfSeats; }
    int* getSeatNumber() { return this->seatNumber; }
    string getTicketType() { return this->ticketType; }
    string getEventName() { return this->eventName; }

    int reserveSeats(int numberOfSeats) {
        if (numberOfSeats > MAX_SEATS_PER_RESERVATION) {
            cout << "Cannot reserve more than " << MAX_SEATS_PER_RESERVATION << " seats at once." << endl;
            return -1;
        }
        else return 0;
    }
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
        return true;
    }
    void writeToBinaryFile(ofstream& out)
    {
        out.write((char*)&id, sizeof(id));
        int seatNumberSize = sizeof(seatNumber);
        out.write((char*)&seatNumberSize, sizeof(seatNumberSize));
        for (int i = 0; i < seatNumberSize; i++) {
            out.write((char*)&seatNumber[i], sizeof(seatNumber[i]));
        }
        out.write((char*)&ticketType, sizeof(ticketType));
        out.close();
    }

    void saveToBinaryFile(const string& filename) {
        ofstream file(filename, ios::binary);
        int seatNumberSize = sizeof(seatNumber);
        file.write((char*)&id, sizeof(id));
        file.write((char*)&seatNumberSize, sizeof(seatNumberSize));
        for (int i = 0; i < seatNumberSize; i++) {
            file.write((char*)&seatNumber[i], sizeof(seatNumber[i]));
        }
        file.write((char*)&ticketType, sizeof(ticketType));
        file.close();
    }

    void readFromBinaryFile(const string& filename)
    {
        ifstream file(filename, ios::binary);
        if (file.fail())
        {
            cerr << "Error: Could not open file '" << filename << "' for reading." << endl;
            return;
        }
        file.read((char*)&id, sizeof(id));
        int seatNumberSize;
        file.read((char*)&seatNumberSize, sizeof(seatNumberSize));
        vector<int>seatNumber;
        for (int i = 0; i < seatNumberSize; i++) {
            file.read((char*)&seatNumber[i], sizeof(seatNumber[i]));
        }
        file.read((char*)&ticketType, sizeof(ticketType));
        file.close();
    }
    void reserveSeats(const EventLocation& location) {
        cout << "Reserving seat(s): ";
        if (location.seatCount == 0) {
            cout << "Invalid location" << endl;
            return;
        }
        for (int i = 0; i < this->numberOfSeats; i++) {
            int col = this->seatNumber[i] % location.columns;
            int row = this->seatNumber[i] / location.columns;
            /*if (row >= location.rows || col >= location.columns) {
                cout << "Invalid seat" << endl;
            }*/
            if (location.seats[row][col] != false) 
            {
                cout << "Seat has been taken.";
            }
            else {
                location.seats[row][col] = true;
            }
            
        }
        cout << endl;
    }

    friend ostream& operator<<(ostream&, Ticket);
    friend istream& operator>>(istream&, Ticket&);
};