#include <iostream>
#include <string>
#include <random>
#include<fstream>
#include<vector>
using namespace std;

enum class Zone { Normal, VIP };

class Seats
{
    virtual int generateTicketId() = 0;
};

class EventLocation {
private:
    int rows;
    int columns;
    bool** seats;

public:
    EventLocation() {
        this->rows = 0;
        this->columns = 0;
        this->seats = nullptr;
    }
    bool** allocate(size_t m, size_t n)
    {
        bool** seats = nullptr;

        if (n != 0 && m != 0)
        {
            seats = new bool* [m];

            for (size_t i = 0; i < m; i++) seats[i] = new bool[n];
        }

        return seats;
    }
    EventLocation(int rows, int columns) :rows(rows), columns(columns), seats(allocate(rows, columns)) {
        this->rows = rows;
        this->columns = columns;
        this->seats = new bool* [rows];
        this->seats = new bool* [rows];
        for (int i = 0; i < rows; i++) {
            this->seats[i] = new bool[columns];
        }
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                this->seats[i][j] = seats[i][j];
            }
        }
    }
    EventLocation(const EventLocation& location) :rows(location.rows), columns(location.columns), seats(allocate(location.rows, location.columns)) {
        this->rows = location.rows;
        this->columns = location.columns;
        if (location.seats != nullptr)
        {
            this->seats = new bool* [location.rows];
            for (int i = 0; i < location.rows; i++) {
                this->seats[i] = new bool[location.columns];
                for (int j = 0; j < location.columns; j++) {
                    this->seats[i][j] = location.seats[i][j];
                }
            }
        }
    }
    EventLocation& operator=(const EventLocation& location) {
        if (this != &location) {
            for (int i = 0; i < this->rows; i++) {
                delete[] seats[i];
            }
            delete[] seats;
            this->rows = location.rows;
            this->columns = location.columns;
            this->seats = new bool* [location.rows];
            for (int i = 0; i < location.rows; i++) {
                this->seats[i] = new bool[location.columns];
                for (int j = 0; j < location.columns; j++) {
                    this->seats[i][j] = location.seats[i][j];
                }
            }
        }
        return *this;
    }
    ~EventLocation() {
        for (int i = 0; i < this->rows; i++) {
            delete[] seats[i];
        }
        delete[] seats;
    }
    int getRows()const { return rows; }
    int getColumns()const { return columns; }
    static int calculateTotalSeats(int rows, int columns) {
        return rows * columns;
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
    char* name;
    string date;
    string time;
    const int ReleaseDate;
public:
    Event() :ReleaseDate(2023)
    {
        this->name = nullptr;
        this->date = "";
        this->time = "";
    }
    Event(const char* name, string date, string time) :ReleaseDate(2023)
    {
        this->name = new char[strlen(name) + 1];
        strcpy_s(this->name, strlen(name) + 1, name);
        this->date = date;
        this->time = time;
    }
    Event(const Event& e) :ReleaseDate(e.ReleaseDate)
    {
        this->name = new char[strlen(e.name) + 1];
        strcpy_s(this->name, strlen(e.name) + 1, e.name);
        this->date = e.date;
        this->time = e.time;
    }
    ~Event()
    {
        delete[] name;
    }
    Event& operator=(const Event& e)
    {
        if (this != &e)
        {
            if (e.name != nullptr)
            {
                if (name != nullptr)
                {
                    delete[] name;
                }

                this->name = new char[strlen(e.name) + 1];
                strcpy_s(this->name, strlen(e.name) + 1, e.name);
            }
            this->date = e.date;
            this->time = e.time;
        }
        return *this;
    }
    char* getName() {
        return name;
    }
    string getDate() { return date; }
    string getTime() { return time; }
    friend class Ticket;
    friend ostream& operator<<(ostream&, Event);
    friend istream& operator>>(istream&, Event&);
};

class Ticket : public Seats {
private:
    int id;
    char* eventName;
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
    char* getEventName() { return eventName; }

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


    bool isUnique() const {
        for (int issuedId : issuedIds) {
            if (issuedId == id) {
                return false;
            }
        }
        return true;
    }
    void saveToBinaryFile(const string& filename) {
        ofstream file(filename, ios::binary);
        int seatNumberSize = sizeof(seatNumber);
        file.write((char*)&id, sizeof(id));
        file.write((char*)&seatNumberSize, sizeof(seatNumberSize));
        for (int i = 0; i < seatNumberSize; i++) {
            file.write((char*)&seatNumber[i], sizeof(seatNumber[i]));
        }
        short dim = this->ticketType.length();
        file.write((char*)&dim, sizeof(dim));
        file.write(ticketType.c_str(), dim + 1);
        file.close();
    }

    void readFromBinaryFile(const string& filename)
    {
        ifstream file(filename, ios::binary);
        file.read((char*)&id, sizeof(id));
        int seatNumberSize;
        file.read((char*)&seatNumberSize, sizeof(seatNumberSize));
        vector<int>seatNumber;
        for (int i = 0; i < seatNumberSize; i++) {
            file.read((char*)&seatNumber[i], sizeof(seatNumber[i]));
        }
        short dim = 0;
        file.read((char*)&dim, sizeof(dim));
        char* n = new char[dim + 1];
        file.read(n, dim + 1);
        ticketType = n;
        delete[] n;
        file.close();
    }
    void reserveSeats(const EventLocation& location) {

        for (int i = 0; i < this->numberOfSeats; i++) {
            int col = this->seatNumber[i] % location.columns;
            int row = this->seatNumber[i] / location.columns;
            if (location.seats[row][col] != true)
            {
                cout << "Seat has been taken.";
            }
            else {
                location.seats[row][col] = false;
            }

        }
        cout << endl;
    }

    friend ostream& operator<<(ostream&, Ticket);
    friend istream& operator>>(istream&, Ticket&);
};