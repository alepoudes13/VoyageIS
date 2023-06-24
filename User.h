#pragma once
#include "PlaneDatabase.h"
#include "Menu.h"

class User {
protected:
	PlaneDatabase* planeDatabase;
	void findPlanes(); 
	void sortPlanes(); 
	void sellTickets(); 
public:
	User();
	~User();
	void startModule(); 
};

