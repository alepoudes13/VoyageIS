#pragma once
#include "Authorization.h"
#include "PlaneDatabase.h"
#include "Menu.h"
#include "User.h"

class Admin : private User {
	Authorization* auth;
	void startAccountModule(); 
	void startDataModule(); 
	void editAccount(); 
	void changeLogin(int index); 
	void changePassword(int index); 
	void changeRole(int index); 
	void deleteAccount(); 
	void verify(); 
	void block(); 
	//------------
	void addPlane(); 
	void editPlane(); 
	void deletePlane(); 
public:
	Admin(Authorization* auth);
	void startMainModule();
};

