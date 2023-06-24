#pragma once
#include "TablePrinting.h"
#include "Plane.h"
#include <vector>
#include <fstream>

class PlaneDatabase {
    const std::string PLANES_FILE = "planes.txt";
    Plane planesVector[100];
    std::vector<Plane> planes;
public:
    const std::vector<std::string> columnNames = { "Index", "Number", "Cost bussiness", "Tickets buss.", "Cost econom", "Tickets econom", "Capacity", "Departure time", "Departure date", "Arrival time", "Destination", "Plane type" };
    PlaneDatabase();
    ~PlaneDatabase();
    int findByNumber(size_t number); 
    int addPlane(Plane plane); 
    Plane getAtIndex(int index); 
    void setAtIndex(int index, Plane plane); 
    void deleteAtIndex(int index); 
    void show(); 
    std::vector<int> find(std::string destination);
    std::vector<int> find(size_t ticketCost, Plane::TicketTypes ticketType);
    std::vector<int> find(Date departureDate);
    void sort(bool isSwapNeeded(const Plane& plane1, const Plane& plane2));
};
