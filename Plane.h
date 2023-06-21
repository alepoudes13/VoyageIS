#pragma once

#include "Datetime.h"
#include <string>
#include "ValidatedInput.h"

class Plane {
public:
    enum TicketTypes { Business, Econom };
    const std::string typesArray[2] = { "бизнес", "эконом" };
    const int columnWidth[12] = {10, 15, 15, 16, 15, 16, 15, 20, 20, 20, 20, 20}, argsCnt = 12;

    Plane();
    Plane(size_t number, size_t ticketCost, size_t ticketCostEconom, size_t ticketsCntBusiness, size_t ticketsCntEconom, std::string type, std::string destination, Time departureTime, Date departureDate, Time arrivalTime);
    friend std::istream& operator>>(std::istream& in, Plane& plane);
    friend std::ostream& operator<<(std::ostream& out, const Plane& plane);
    Plane& operator=(const Plane& other);
    friend void printRow(const Plane& plane, int index);
    void read(); //”добный пользователю ввод данных
    bool sell(size_t amount, Plane::TicketTypes ticketType); //ѕродать указанное число билетов указанного типа
    //--------------------------------------------
    bool isObjectEmpty() { return this->isEmpty; }
    size_t getNumber() { return this->number; };
    std::string getDestination() { return this->destination; }
    size_t getCost(Plane::TicketTypes ticketType) { return this->ticketCost[ticketType]; }
    Date getDepartureDate() { return this->departureDate; }
    //--------------------------------------------
    void assignPointers(std::string*& newStr, size_t*& newInt, Time*& newTime, Date*& newDate, int index); //«адать указатель на измен€емое поле объекта в соответствии с его индексом
    void updateCapacity(); //¬ычислить вместимость самолЄта на основе числа билетов
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

bool compareDestination(const Plane& plane1, const Plane& plane2); //¬ернуть истину, если пункт назначени€ первого рейса меньше либо равен назначению второго лексикографически
bool compareCostBusiness(const Plane& plane1, const Plane& plane2); //¬ернуть истину, если пункт цена билета бизнес-класса первого рейса меньше либо равна цене второго
bool compareCostEconom(const Plane& plane1, const Plane& plane2); //¬ернуть истину, если пункт цена билета эконом-класса первого рейса меньше либо равна цене второго
bool compareDepartureDate(const Plane& plane1, const Plane& plane2); //¬ернуть истину, если дата отправлени€ первого рейса меньше либо равна дате второго
