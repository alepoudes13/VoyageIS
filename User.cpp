#include "User.h"

User::User() {
	this->planeDatabase = new PlaneDatabase;
}

User::~User() {
	delete this->planeDatabase;
}

void User::startModule() {
	int actionCase;
	enum State { Exit, View, Search, Sort, Sell };
	std::vector<std::string> menuLines = {
		"�����.",
		"��������.",
		"�����.",
		"����������.",
		"������� �������."
	};
	std::string title = "--------���� ������������--------------------";
	Menu menu(title, menuLines);

	do {
		actionCase = menu.getResponse();
		switch (actionCase)
		{
		default:
		case Exit:
			break;
		case View:
			this->planeDatabase->show();
			break;
		case Search:
			this->findPlanes();
			break;
		case Sort:
			this->sortPlanes();
			break;
		case Sell:
			this->sellTickets();
			break;
		}
	} while (actionCase != Exit);
}

void User::sellTickets() {
	int index;
	�ustValidatedInput("������� ������ ��������: ", 1, "%d", &index);
	Plane plane = this->planeDatabase->getAtIndex(index);
	if (plane.isObjectEmpty()) {
		std::cout << "[!] ��� �������� � ����� ��������.\n";
		return;
	}

	enum State { Business, Econom };
	std::vector<std::string> menuLines = {
		"������.",
		"������."
	};
	std::string title = "�������� �����:";
	Menu menu(title, menuLines);

	int amount, type = menu.getResponse();
	do {
		�ustValidatedInput("������� ����� �������: ", 1, "%d", &amount);
	} while (amount < 0);
	if (plane.sell(amount, static_cast<Plane::TicketTypes>(type)))
		this->planeDatabase->setAtIndex(index, plane);
}

void User::findPlanes() {
	int actionCase;
	enum State { Exit, Destination, Cost, DepartureDate };
	std::vector<std::string> menuLines = {"�����.",	"�� �����������.", "�� ���� ������.", "�� ���� �����������."};
	std::string title = "--------���� ������--------------------------";
	Menu menu(title, menuLines);
	do {
		actionCase = menu.getResponse();
		std::vector<int> results;
		bool printRes = true;
		switch (actionCase)
		{
		default: case Exit:
			printRes = false;
			break;
		case Destination:{
			std::string destination;
			std::cout << "������� �����������: ";
			std::getline(std::cin, destination);
			if(destination == "")
				std::getline(std::cin, destination);
			results = this->planeDatabase->find(destination);
			break;
		}
		case Cost:{
			enum State { Business, Econom };
			std::vector<std::string> menuLines = {"������.", "������."};
			std::string title = "�������� �����:";
			Menu menu(title, menuLines);

			int cost, type = menu.getResponse();
			do {
				�ustValidatedInput("������� ���� ������: ", 1, "%d", &cost);
			} while (cost < 0);
			results = this->planeDatabase->find(cost, static_cast<Plane::TicketTypes>(type));
			break;
		}
		case DepartureDate:{
			Date date;
			date.readLoop("������� ���� �����������(��.��.��): ");
			results = this->planeDatabase->find(date);
			break;
		}
		}
		if (printRes) {
			if (results.empty())
				std::cout << "���������� ����������� �� ����������.\n";
			else {
				printRow(Plane(), this->planeDatabase->columnNames);
				for (auto i : results)
					printRow(this->planeDatabase->getAtIndex(i), i);
			}
		}
	} while (actionCase != Exit);
}

void User::sortPlanes() {
	int actionCase;
	enum State { Exit, Destination, CostBusiness, CostEconom, DepartureDate };
	std::vector<std::string> menuLines = {
		"�����.",
		"�� �����������.",
		"�� ���� ������ ������-������.",
		"�� ���� ������ ������-������.",
		"�� ���� �����������."
	};
	std::string title = "--------���� ����������----------------------";
	Menu menu(title, menuLines);

	do {
		actionCase = menu.getResponse();
		bool printRes = true;
		switch (actionCase)
		{
		default:
		case Exit:
			printRes = false;
			break;
		case Destination:
			this->planeDatabase->sort(compareDestination);
			break;
		case CostBusiness:
			this->planeDatabase->sort(compareCostBusiness);
			break;
		case CostEconom:
			this->planeDatabase->sort(compareCostEconom);
			break;
		case DepartureDate:
			this->planeDatabase->sort(compareDepartureDate);
			break;
		}
		if (printRes) {
			std::cout << "���e��� �������������.\n";
			this->planeDatabase->show();
		}
	} while (actionCase != Exit);
}