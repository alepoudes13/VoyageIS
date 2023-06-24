#pragma once
#include "AccountDatabase.h"
#include "ValidatedInput.h"
#include <conio.h>

class Authorization {
    AccountDatabase* accountDatabase;
    Account activeAccount;
public:
    Authorization();
    ~Authorization();
    void protectedInput(std::string& password); 
    void startModule(bool isLoggingNeeded = true);
    Account getActiveAccount(); 
    void setActiveAccount(Account account); 
    AccountDatabase* getAccountDB();
};

