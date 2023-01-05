#include<iostream>
#include "Classes header.cpp";
using namespace std;

//ostream& operator<<(ostream& out, EventLocation l)
//{
//	int sum = 0;
//	out << "Maximum number of Seats: ";
//	for (int i = 0; i < l.vipOrNah; ++i)
//		sum += l.maxSeats[i];
//	out << sum << endl;
//	out << "Number of Normal Seats: ";
//	out << l.maxSeats[0]; out << endl;
//	out << "Number of VIP Seats: ";
//	out << l.maxSeats[1]; out << endl;
//	return out;
//}
//
//ostream& operator<<(ostream& out, event e)
//{
//	out << "Movie Name: ";
//	out << e.movieName; out << endl;
//	out << "Starts at: ";
//	out << e.timeStart; out << endl;
//	out << "Number of Normal Seats: ";
//	out << e.normal; out << endl;
//	out << "Price of Normal Seats: ";
//	out << e.normalPrice; out << endl;
//	out << "Number of VIP Seats: ";
//	out << e.vip; out << endl;
//	out << "Price of VIP Seats: ";
//	out << e.vipPrice; out << endl;
//	return out;
//}
//
//ostream& operator<<(ostream& out, ticket t)
//{
//	out << "Ticket ID: ";
//	out << t.ticketID; out << endl;
//	//out << "Movie Name: ";
//	//out << t.movieName; out << endl;
//	//out << "Starts at: ";
//	//out << t.timeStart; out << endl;
//	out << "Clients: ";
//	for (int i = 0; i < t.noSeats; ++i)
//		 out<<" "<< t.client[i]<<endl;
//	out << "Number Seats: ";
//	out << t.noSeats; out << endl;
//	out << "Type: ";
//	out << t.getNormalOrVip(); out << endl;
//	return out;
//}

vector<int> Ticket::issuedIds;
string EventLocation::CINEMAname = "Cinema City Onesti";

int main() {
    vector<Ticket> tickets;
    // Create an event location
    EventLocation location;
    // Create an event
    Event event;

    // Menu options
    enum Option {
        EnterLocation = 1,
        EnterEvent,
        GenerateTicket,
        ShowTicket,
        Quit
    };

    while (true) {
        // Display menu
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
            // Enter event location characteristics
            int  maxSeats, numRows;
            cout << "Enter maximum number of seats: ";
            cin >> maxSeats;
            cout << "Enter number of rows: ";
            cin >> numRows;

            location = EventLocation(maxSeats, numRows);
            cout << "Event location characteristics entered." << endl;
            cout << endl;
            break;
        }
        case EnterEvent: {
            // Enter event characteristics
            string name, date, time;
            cout << "Enter event name: ";
            cin >> name;
            cout << "Enter event date (yyyy-mm-dd): ";
            cin >> date;
            cout << "Enter event time (hh:mm): ";
            cin >> time;

            event = Event(name, date, time);
            cout << "Event characteristics entered." << endl;
            cout << endl;
            break;
        }
        case GenerateTicket: {
            // Issue a ticket
            // Check if event and event location are set
            if (event.getName() == "" || location.getMaxSeats() == 0) {
                cout << "Event or event location not set." << endl;
                break;
            }

            // Read seat number
            int seatNumber;
            cout << "Enter seat number: ";
            cin >> seatNumber;


            // Check if seat is available
            if (!location.isSeatFree(seatNumber))
            {
                cout << "Seat is not available." << endl;
                break;
            }

            // Read ticket type
            string ticketType;
            cout << "Enter ticket type(n or v): ";
            cin >> ticketType;

            Zone zone;
            if (ticketType == "n") { zone = Zone::Normal; }
            else if (ticketType == "v") { zone = Zone::VIP; }
            else {
                if (ticketType != "n" || ticketType != "v") {
                    cout << "Invalid zone." << endl;
                    break;
                }
            }
            // Issue ticket
            Ticket ticket;

            // Save the ticket to the binary file
            ticket.saveToBinaryFile("tickets.bin");

            cout << "Ticket issued and saved to binary file." << endl;
            break;
        }
        case ShowTicket: {
            // Load ticket data from binary file
            Ticket ticket;
            ifstream inputFile("tickets.bin", ios::binary);
            ticket.readFromBinaryFile(inputFile);

            // Display the ticket details
            cout << "ID: " << ticket.getTicketID() << endl;
            cout << "Event name: " << ticket.getEventName() << endl;
            cout << "Seat number: " << ticket.getSeatNumber() << endl;
            cout << "Ticket type: " << ticket.getTicketType() << endl;
            inputFile.close();
            break;
        }
                       //case DisplaySeats: {
                       //    // Display a matrix of seats
                       //    cout << "Seats: " << endl;
                       //    for (int i = 1; i <= location.getMaxSeats(); i++) {
                       //        cout << location.isSeatFree(i);
                       //        if (i % 10 == 0) {
                       //            cout << endl;
                       //        }
                       //    }
                       //    cout << endl;
                       //    break;
                       //}
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