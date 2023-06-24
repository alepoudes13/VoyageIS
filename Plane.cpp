#include "Plane.h"

Plane::Plane() : isEmpty(true) {

}

Plane::Plane(size_t number, size_t ticketCostBusiness, size_t ticketCostEconom, size_t ticketsCntBusiness, size_t ticketsCntEconom, std::string type, std::string destination, Time departureTime, Date departureDate, Time arrivalTime) {
	this->number = number;
	this->type = type;
	this->ticketCost[Plane::Business] = ticketCostBusiness;
	this->ticketCost[Plane::Econom] = ticketCostEconom;
	this->ticketsCnt[Plane::Business] = ticketsCntBusiness;
	this->ticketsCnt[Plane::Econom] = ticketsCntEconom;
	this->planeCapacity = this->ticketsCnt[Plane::Econom] + this->ticketsCnt[Plane::Business];
	this->destination = destination;
	this->departureTime = departureTime;
	this->departureDate = departureDate;
	this->arrivalTime = arrivalTime;
	this->isEmpty = false;
}

std::istream& operator>>(std::istream& in, Plane& plane) {
	in >> plane.number >> plane.ticketCost[Plane::Business] >> plane.ticketCost[Plane::Econom] >> plane.ticketsCnt[Plane::Business] >> plane.ticketsCnt[Plane::Econom] >> plane.planeCapacity >> plane.departureTime >> plane.departureDate >> plane.arrivalTime;
	std::getline(in, plane.destination);
	std::getline(in, plane.destination);
	std::getline(in, plane.type);
	plane.isEmpty = false;
	return in;
}

std::ostream& operator<<(std::ostream& out, const Plane& plane) {
	out << plane.number << ' ' << plane.ticketCost[Plane::Business] << ' ' << plane.ticketCost[Plane::Econom] << ' ' << plane.ticketsCnt[Plane::Business] << ' ' << plane.ticketsCnt[Plane::Econom] << ' ' << plane.planeCapacity << ' ' << plane.departureTime << ' ' << plane.departureDate << ' ' << plane.arrivalTime << '\n' << plane.destination << '\n' << plane.type << '\n';
	return out;
}

Plane& Plane::operator=(const Plane& other) {
	this->number = other.number;
	this->type = other.type;
	this->ticketCost[Plane::Business] = other.ticketCost[Plane::Business];
	this->ticketCost[Plane::Econom] = other.ticketCost[Plane::Econom];
	this->ticketsCnt[Plane::Business] = other.ticketsCnt[Plane::Business];
	this->ticketsCnt[Plane::Econom] = other.ticketsCnt[Plane::Econom];
	this->planeCapacity = other.planeCapacity;
	this->destination = other.destination;
	this->departureTime = other.departureTime;
	this->departureDate = other.departureDate;
	this->arrivalTime = other.arrivalTime;
	this->isEmpty = other.isEmpty;
	return *this;
}

void Plane::read() {
	int buffer, buffer2;
	do {
		ñustValidatedInput("Number: ", 1, "%d", &buffer);
	} while (buffer < 0);
	this->number = static_cast<size_t>(buffer);
	do {
		ñustValidatedInput("Ticket price bussiness/econom: ", 2, "%d/%d", &buffer, &buffer2);
	} while (buffer < 0 || buffer2 < 0);
	this->ticketCost[Plane::Business] = static_cast<size_t>(buffer);
	this->ticketCost[Plane::Econom] = static_cast<size_t>(buffer2);
	do {
		ñustValidatedInput("Tickets left business/econom: ", 2, "%d/%d", &buffer, &buffer2);
	} while (buffer < 0 || buffer2 < 0);
	this->ticketsCnt[Plane::Business] = static_cast<size_t>(buffer);
	this->ticketsCnt[Plane::Econom] = static_cast<size_t>(buffer2);
	this->planeCapacity = this->ticketsCnt[Plane::Business] + this->ticketsCnt[Plane::Econom];
	this->departureTime.readLoop("Departure time(hh:mm): ");
	this->departureDate.readLoop("Departure date(dd.mm.yy): ");
	this->arrivalTime.readLoop("Arrival time(hh:mm): ");
	std::cout << "Destination: ";
	std::getline(std::cin, this->destination);
	std::cout << "Plane type: ";
	std::getline(std::cin, this->type);
	this->isEmpty = false;
}

bool Plane::sell(size_t amount, Plane::TicketTypes ticketType) {
	if (!this->ticketsCnt[ticketType])
		return std::cout << "[!] There are no " << this->typesArray[ticketType] << " tickets, but " << this->ticketsCnt[1 - ticketType] << " tickets of " << this->typesArray[1 - ticketType] << " class are left\n", false;
	if (this->ticketsCnt[ticketType] < amount)
		return std::cout << "[!] There is no tickets for requested amount. The remaining tickets of class " << this->typesArray[ticketType] << ": " << this->ticketsCnt[ticketType] << '\n', false;
	this->ticketsCnt[ticketType] -= amount;
	return std::cout << "Purchase successful. The price to pay is " << amount * this->ticketCost[ticketType] << '\n', true;
}

void Plane::assignPointers(std::string*& newStr, size_t*& newInt, Time*& newTime, Date*& newDate, int actionCase) {
	enum State { Number = 1, CostBusiness, CostEconom, CntBusiness, CntEconom, DepTime, DepDate, ArrTime, Destination, Type };
	newStr = NULL, newInt = NULL, newTime = NULL, newDate = NULL;
	switch (actionCase) {
	case Number:
		newInt = &this->number;
		break;
	case CostBusiness:
		newInt = &this->ticketCost[Plane::Business];
		break;
	case CostEconom:
		newInt = &this->ticketCost[Plane::Econom];
		break;
	case CntBusiness:
		newInt = &this->ticketsCnt[Plane::Business];
		break;
	case CntEconom:
		newInt = &this->ticketsCnt[Plane::Econom];
		break;
	case DepTime:
		newTime = &this->departureTime;
		break;
	case DepDate:
		newDate = &this->departureDate;
		break;
	case ArrTime:
		newTime = &this->arrivalTime;
		break;
	case Destination:
		newStr = &this->destination;
		break;
	case Type:
		newStr = &this->type;
		break;
	default:
		break;
	}
}

void Plane::updateCapacity() {
	this->planeCapacity = this->ticketsCnt[Plane::Business] + this->ticketsCnt[Plane::Econom];
}

bool compareDestination(const Plane& plane1, const Plane& plane2) {
	return plane1.destination == plane2.destination ? plane1.departureTime <= plane2.departureTime : plane1.destination <= plane2.destination;
}

bool compareCostBusiness(const Plane& plane1, const Plane& plane2) {
	return plane1.ticketCost[Plane::Business] <= plane2.ticketCost[Plane::Business];
}

bool compareCostEconom(const Plane& plane1, const Plane& plane2) {
	return plane1.ticketCost[Plane::Econom] <= plane2.ticketCost[Plane::Econom];
}

bool compareDepartureDate(const Plane& plane1, const Plane& plane2) {
	return plane1.departureDate <= plane2.departureDate;
}