#pragma once

#include "Datetime.h"
#include <string>
#include "ValidatedInput.h"

class Plane {
public:
    enum TicketTypes { Business, Econom };
    const std::string typesArray[2] = { "bussiness", "econom" };
    const int columnWidth[12] = {10, 15, 15, 16, 15, 16, 15, 20, 20, 20, 20, 20}, argsCnt = 12;

    Plane();
    Plane(size_t number, size_t ticketCost, size_t ticketCostEconom, size_t ticketsCntBusiness, size_t ticketsCntEconom, std::string type, std::string destination, Time departureTime, Date departureDate, Time arrivalTime);
    friend std::istream& operator>>(std::istream& in, Plane& plane);
    friend std::ostream& operator<<(std::ostream& out, const Plane& plane);
    Plane& operator=(const Plane& other);
    friend void printRow(const Plane& plane, int index);
    void read();
    bool sell(size_t amount, Plane::TicketTypes ticketType);
    //--------------------------------------------
    bool isObjectEmpty() { return this->isEmpty; }
    size_t getNumber() { return this->number; };
    std::string getDestination() { return this->destination; }
    size_t getCost(Plane::TicketTypes ticketType) { return this->ticketCost[ticketType]; }
    Date getDepartureDate() { return this->departureDate; }
    //--------------------------------------------
    void assignPointers(std::string*& newStr, size_t*& newInt, Time*& newTime, Date*& newDate, int index); 
    void updateCapacity();
    friend bool compareDestination(const Plane& plane1, const Plane& plane2);
    friend bool compareCostBusiness(const Plane& plane1, const Plane& plane2);
    friend bool compareCostEconom(const Plane& plane1, const Plane& plane2);
    friend bool compareDepartureDate(const Plane& plane1, const Plane& plane2);

private:
    bool isEmpty;
    size_t number, ticketCost[2], ticketsCnt[2], planeCapacity;
    Time departureTime, arrivalTime;
    Date departureDate;
    std::string destination;
    std::string type;
};

bool compareDestination(const Plane& plane1, const Plane& plane2); 
bool compareCostBusiness(const Plane& plane1, const Plane& plane2); 
bool compareCostEconom(const Plane& plane1, const Plane& plane2); 
bool compareDepartureDate(const Plane& plane1, const Plane& plane2); 
