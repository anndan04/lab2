#pragma once
#ifndef TRAIN_H
#define TRAIN_H

#include <iostream>
class TRAIN {
private:
    char* destination;      // Название пункта назначения
    int trainNumber;        // Номер поезда
    char* departureTime;    // Время отправления (формат "ЧЧ:ММ")

    // Вспомогательные методы для работы с динамической памятью
    void copyString(char*& dest, const char* src);

public:
    // Конструкторы
    TRAIN();                                   // Без параметров
    TRAIN(const char* dest, int num, const char* time); // С параметрами
    TRAIN(const TRAIN& other);                 // Копирования

    // Деструктор
    ~TRAIN();

    // Оператор присваивания
    TRAIN& operator=(const TRAIN& other);

    // Set-методы
    void setDestination(const char* dest);
    void setTrainNumber(int num);
    void setDepartureTime(const char* time);

    // Get-методы
    const char* getDestination() const;
    int getTrainNumber() const;
    const char* getDepartureTime() const;

    // Метод сравнения времени (возвращает true, если текущее время > указанного)
    bool departsAfter(const char* time) const;

    // Перегрузка операторов ввода/вывода
    friend std::ostream& operator<<(std::ostream& os, const TRAIN& train);
    friend std::istream& operator>>(std::istream& is, TRAIN& train);

    // Для сортировки 
    friend bool compareByDestination(const TRAIN& a, const TRAIN& b);
};

#endif 