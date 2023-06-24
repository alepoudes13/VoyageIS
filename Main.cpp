#include "Admin.h"

using namespace std;

int main()
{
    srand(time(0));
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    Authorization auth;

    int actionCase;
    enum State{Exit, Authorize};
    vector<string> menuLines = {
        "Exit.",
        "Authorization."
    };
    string title = "--------Welcome------------------------------";
    Menu menu(title, menuLines);

    do {
        actionCase = menu.getResponse();
        switch (actionCase) {
        default:
        case Exit:
            break;
        case Authorize:
            auth.startModule();
            if (auth.getActiveAccount().getRole() == Account::Role::ADMIN) {
                Admin admin(&auth);
                admin.startMainModule();
            }
            else if (auth.getActiveAccount().getRole() == Account::Role::USER) {
                User user;
                user.startModule();
            }
            break;
        }
    } while (actionCase);
}
