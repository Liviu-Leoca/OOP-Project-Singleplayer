#include<iostream>
#include "Classes header.cpp";
using namespace std;

ostream& operator<<(ostream& out, location l)
{
	int sum = 0;
	out << "Maximum number of Seats: ";
	for (int i = 0; i < l.vipOrNah; ++i)
		sum += l.maxSeats[i];
	out << sum << endl;
	out << "Number of Normal Seats: ";
	out << l.maxSeats[0]; out << endl;
	out << "Number of VIP Seats: ";
	out << l.maxSeats[1]; out << endl;
	return out;
}

ostream& operator<<(ostream& out, event e)
{
	out << "Movie Name: ";
	out << e.movieName; out << endl;
	out << "Starts at: ";
	out << e.timeStart; out << endl;
	out << "Number of Normal Seats: ";
	out << e.normal; out << endl;
	out << "Price of Normal Seats: ";
	out << e.normalPrice; out << endl;
	out << "Number of VIP Seats: ";
	out << e.vip; out << endl;
	out << "Price of VIP Seats: ";
	out << e.vipPrice; out << endl;
	return out;
}

ostream& operator<<(ostream& out, ticket t)
{
	out << "Ticket ID: ";
	out << t.ticketID; out << endl;
	//out << "Movie Name: ";
	//out << t.movieName; out << endl;
	//out << "Starts at: ";
	//out << t.timeStart; out << endl;
	out << "Clients: ";
	for (int i = 0; i < t.noSeats; ++i)
		 out<<" "<< t.client[i]<<endl;
	out << "Number Seats: ";
	out << t.noSeats; out << endl;
	out << "Type: ";
	out << t.getNormalOrVip(); out << endl;
	return out;
}

string location::CINEMAname = "Cinema City Onesti";
int main()
{
	std::cout << std::endl << "Hello World!"<<endl;
	ticket t1;
	cout << t1.getTicketId() << endl;;
}