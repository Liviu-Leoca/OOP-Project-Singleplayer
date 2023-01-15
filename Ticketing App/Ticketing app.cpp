#include<iostream>
#include "Classes header.cpp";
using namespace std;

ostream& operator<<(ostream& out, EventLocation l)
{
    for (int i = 0; i < l.rows; i++) {
        cout << "Row " << i + 1 << ": ";
        for (int j = 0; j < l.columns; j++) {
            cout << (l.seats[i][j] ? 'X' : 'O') << " ";
        }
        cout << endl;
    }
    out << endl << "Total seats:" << l.getSeatCount() << endl;

    return out;
}
istream& operator>>(istream& in, EventLocation& location)
{
    cout << "Enter number of rows: ";
    in >> location.rows;
    cout << "Enter number of columns: ";
    in >> location.columns;
    return in;
}

ostream& operator<<(ostream& out, Event e)
{
    out << "Movie Name: " << e.name << endl;
    out << "Date: " << e.date << endl;
    out << "Time: " << e.time << endl;
    return out;
}
istream& operator>>(istream& in, Event& e)
{
    cout << "Enter event name: ";
    in >> e.name;
    cout << "Enter event date (yyyy-mm-dd): ";
    in >> e.date;
    cout << "Enter event time (hh:mm): ";
    in >> e.time;
    return in;
}

vector<int> Ticket::issuedIds;

ostream& operator<<(ostream& out, Ticket t)
{
    out << "Movie Ticket " << endl;
    out << "Movie: " << t.getEventName() << endl;
    out << "ID: " << t.getTicketID() << endl;
    out << "Number of Seats: " << t.numberOfSeats << endl;
    out << "Seats: ";
    for (int i = 0; i < t.numberOfSeats; i++) {
        out << t.seatNumber[i] << " ";
    }
    out << endl;
    out << "Ticket type: " << t.getTicketType() << endl;
    return out;
}
istream& operator>>(istream& in, Ticket& t)
{
    cout << "Enter the number of seats: ";
    in >> t.numberOfSeats;
    t.seatNumber = new int[t.numberOfSeats];
    cout << "Enter seat numbers: ";
    for (int i = 0; i < t.numberOfSeats; i++)
    {
        in >> t.seatNumber[i];
    }
    cout << "Enter ticket type(n or v): ";
    in >> t.ticketType;
    Zone zone;
    if (t.ticketType == "n") { zone = Zone::Normal; }
    else if (t.ticketType == "v") { zone = Zone::VIP; }
    else {
        if (t.ticketType != "n" || t.ticketType != "v") {
            cout << "Invalid zone." << endl;
        }
    }
    return in;
}


int main() {
    vector<Ticket> tickets;
    Event event;
    EventLocation location;
    enum Option {
        EnterLocation = 1,
        EnterEvent,
        GenerateTicket,
        ShowTicket,
        Quit
    };

    while (true) {
        cout << "Menu:" << endl;
        cout << "  1. Enter event location characteristics" << endl;
        cout << "  2. Enter event characteristics" << endl;
        cout << "  3. Generate ticket" << endl;
        cout << "  4. Show ticket" << endl;
        cout << "  5. Quit" << endl;
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        switch (choice) {
        case EnterLocation: {
            cin >> location;
            cout << location;
            cout << endl;
            break;
        }
        case EnterEvent: {
            cin >> event;
            cout << event << endl;
            cout << endl;
            break;
        }
        case GenerateTicket: {
            //if (event.getName() != "" && location.getRows() != 0 && location.getColumns() != 0) {
            cout << endl;
            cout << location << endl;
            Ticket ticket;
            cin >> ticket;
            cout << ticket;
            ticket.reserveSeats(); // reserve the seats associated with the ticket
            ticket.saveToBinaryFile("tickets.bin");
            cout << endl << location << endl;
            cout << endl << ticket << endl;

            cout << "Ticket issued and saved to binary file." << endl;

            break;
        }
        case ShowTicket: {
            Ticket ticket;
            ifstream inputFile("tickets.bin", ios::binary);
            ticket.readFromBinaryFile(inputFile);

            // Display the ticket details
            cout << "ID: " << ticket.getTicketID() << endl;
            //cout << "Event name: " << ticket.getEventName() << endl;
            cout << "Seat number: " << ticket.getSeatNumber() << endl;
            cout << "Ticket type: " << ticket.getTicketType() << endl;
            inputFile.close();
            break;
        }
        case Quit: {
            return 0;
        }
        default: {
            cout << "Invalid choice." << endl;
            break;
        }

        }
    }
}