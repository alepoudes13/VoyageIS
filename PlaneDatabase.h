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
    const std::vector<std::string> columnNames = { "Индекс", "Номер", "Цена бизнес", "Билетов бизнес", "Цена эконом", "Билетов эконом", "Вместимость", "Время отправления", "Дата отправления", "Время прибытия", "Назначение", "Тип самолета" };
    PlaneDatabase();
    ~PlaneDatabase();
    int findByNumber(size_t number); //Вернуть индекс рейса в базе по его номеру
    int addPlane(Plane plane); //Добавить рейс в базу
    Plane getAtIndex(int index); //Вернуть рейс из базы по индексу
    void setAtIndex(int index, Plane plane); //Установить рейс на позицию индекса в базе
    void deleteAtIndex(int index); //Удалить рейс из базы по индексу
    void show(); //Вывести базу рейсов таблицей
    std::vector<int> find(std::string destination); //Вернуть список рейсов, удовлетворяющих заданному направлению
    std::vector<int> find(size_t ticketCost, Plane::TicketTypes ticketType); //Вернуть список рейсов, удовлетворяющих заданным цене и типу билета
    std::vector<int> find(Date departureDate); //Вернуть список рейсов, удовлетворяющих заданной дате отправления
    void sort(bool isSwapNeeded(const Plane& plane1, const Plane& plane2)); //Отсортировать рейсы по указанному критерию
};
