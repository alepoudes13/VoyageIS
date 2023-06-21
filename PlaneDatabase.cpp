#include "PlaneDatabase.h"

PlaneDatabase::PlaneDatabase() {
	std::ifstream in(PlaneDatabase::PLANES_FILE, std::ifstream::in);
	int n = -1;
	in >> n;
	if (n == -1)
		return;
	in.ignore();
	this->planes.resize(n);
	for (int i = 0; i < n; i++)
		in >> this->planes[i];
}

PlaneDatabase::~PlaneDatabase() {
	std::ofstream out(PlaneDatabase::PLANES_FILE, std::ofstream::out);
	out << this->planes.size() << '\n';
	for (size_t i = 0; i < this->planes.size(); i++)
		out << this->planes[i];
}

int PlaneDatabase::findByNumber(size_t number) {
	for (size_t i = 0; i < this->planes.size(); i++)
		if (this->planes[i].getNumber() == number)
			return i;
	return -1;
}

int PlaneDatabase::addPlane(Plane Plane) {
	if (this->findByNumber(Plane.getNumber()) == -1) {
		this->planes.push_back(Plane);
		return this->planes.size() - 1;
	}
	return -1;
}

Plane PlaneDatabase::getAtIndex(int index) {
	if (index < 0 || index >= static_cast<int>(this->planes.size()))
		return Plane();
	return this->planes[index];
}

void PlaneDatabase::setAtIndex(int index, Plane Plane) {
	if (index < 0 || index >= static_cast<int>(this->planes.size()))
		return;
	this->planes[index] = Plane;
}

void PlaneDatabase::deleteAtIndex(int index) {
	if (index < 0 || index >= static_cast<int>(this->planes.size()))
		return;
	this->planes.erase(this->planes.begin() + index);
}

void PlaneDatabase::show() {
	printRow(Plane(), this->columnNames);
	for (size_t i = 0; i < this->planes.size(); i++)
		printRow(this->planes[i], i);
}

std::vector<int> PlaneDatabase::find(std::string destination) {
	std::vector<int> results;
	for (size_t i = 0; i < this->planes.size(); i++)
		if (this->planes[i].getDestination() == destination)
			results.push_back(i);
	return results;
}

std::vector<int> PlaneDatabase::find(size_t ticketCost, Plane::TicketTypes ticketType) {
	std::vector<int> results;
	for (size_t i = 0; i < this->planes.size(); i++)
		if (this->planes[i].getCost(ticketType) == ticketCost)
			results.push_back(i);
	return results;
}

std::vector<int> PlaneDatabase::find(Date departureDate) {
	std::vector<int> results;
	for (size_t i = 0; i < this->planes.size(); i++)
		if (this->planes[i].getDepartureDate() == departureDate)
			results.push_back(i);
	return results;
}

void PlaneDatabase::sort(bool isSwapNeeded(const Plane& plane1, const Plane& plane2)) {
	for (size_t i = 0; i < this->planes.size(); i++)
		for (size_t j = 0; j < this->planes.size(); j++)
			if (isSwapNeeded(this->planes[i], this->planes[j]))
				std::swap(this->planes[i], this->planes[j]);
}