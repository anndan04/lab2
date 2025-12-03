#include "train.h"
#include <cstring>
#include <stdexcept>
#include <string>

// для копирования строк
void TRAIN::copyString(char*& dest, const char* src) {
    if (src == nullptr) {
        dest = nullptr;
        return;
    }
    size_t src_len = strlen(src);
    delete[] dest;
    dest = new char[strlen(src) + 1];
    strcpy_s(dest, src_len + 1, src);
}

// Конструктор без параметров
TRAIN::TRAIN() : destination(nullptr), trainNumber(0), departureTime(nullptr) {
    std::cout << "Вызван конструктор без параметров для объекта TRAIN" << std::endl;
}

// Конструктор с параметрами
TRAIN::TRAIN(const char* dest, int num, const char* time)
    : destination(nullptr), trainNumber(num), departureTime(nullptr) {

    setDestination(dest);
    setDepartureTime(time);
    std::cout << "Вызван конструктор с параметрами для объекта TRAIN: "
        << (dest ? dest : "null") << std::endl;
}

// Конструктор копирования
TRAIN::TRAIN(const TRAIN& other)
    : destination(nullptr), trainNumber(other.trainNumber), departureTime(nullptr) {

    copyString(destination, other.destination);
    copyString(departureTime, other.departureTime);
    std::cout << "Вызван конструктор копирования для объекта TRAIN: "
        << (other.destination ? other.destination : "null") << std::endl;
}

// Деструктор
TRAIN::~TRAIN() {
    std::cout << "Вызван деструктор для объекта TRAIN: "
        << (destination ? destination : "null") << std::endl;
    delete[] destination;
    delete[] departureTime;
}

// Оператор присваивания
TRAIN& TRAIN::operator=(const TRAIN& other) {
    if (this != &other) {
        trainNumber = other.trainNumber;
        copyString(destination, other.destination);
        copyString(departureTime, other.departureTime);
    }
    return *this;
}

// Set-методы
void TRAIN::setDestination(const char* dest) {
    if (dest == nullptr || strlen(dest) == 0) {
        throw std::invalid_argument("Название пункта назначения не может быть пустым");
    }
    copyString(destination, dest);
}

void TRAIN::setTrainNumber(int num) {
    if (num <= 0) {
        throw std::invalid_argument("Номер поезда должен быть положительным числом");
    }
    trainNumber = num;
}

void TRAIN::setDepartureTime(const char* time) {
    if (time == nullptr || strlen(time) != 5 || time[2] != ':') {
        throw std::invalid_argument("Время должно быть в формате ЧЧ:ММ");
    }

    // Простая проверка формата времени
    int hours = std::stoi(std::string(time, 2));
    int minutes = std::stoi(std::string(time + 3, 2));

    if (hours < 0 || hours > 23 || minutes < 0 || minutes > 59) {
        throw std::invalid_argument("Некорректное время (часы: 0-23, минуты: 0-59)");
    }

    copyString(departureTime, time);
}

// Get-методы
const char* TRAIN::getDestination() const {
    return destination ? destination : "";
}

int TRAIN::getTrainNumber() const {
    return trainNumber;
}

const char* TRAIN::getDepartureTime() const {
    return departureTime ? departureTime : "";
}

// Сравнение времени отправления
bool TRAIN::departsAfter(const char* time) const {
    if (departureTime == nullptr || time == nullptr) return false;

    // Сравниваем как строки (формат "ЧЧ:ММ" позволяет лексикографическое сравнение)
    return strcmp(departureTime, time) > 0;
}

// Перегрузка оператора вывода
std::ostream& operator<<(std::ostream& os, const TRAIN& train) {
    os << "Пункт назначения: " << (train.destination ? train.destination : "не указан")
        << ", Номер поезда: " << train.trainNumber
        << ", Время отправления: " << (train.departureTime ? train.departureTime : "не указано");
    return os;
}

// Перегрузка оператора ввода
std::istream& operator>>(std::istream& is, TRAIN& train) {
    char buffer[100];

    std::cout << "Введите пункт назначения: ";
    is.ignore(); // Игнорируем предыдущий символ новой строки
    is.getline(buffer, 100);
    train.setDestination(buffer);

    std::cout << "Введите номер поезда: ";
    int num;
    is >> num;
    train.setTrainNumber(num);

    std::cout << "Введите время отправления (формат ЧЧ:ММ): ";
    is.ignore();
    is.getline(buffer, 100);
    train.setDepartureTime(buffer);

    return is;
}

// Функция для сравнения по пункту назначения (для сортировки)
bool compareByDestination(const TRAIN& a, const TRAIN& b) {
    const char* destA = a.getDestination();
    const char* destB = b.getDestination();

    if (destA == nullptr && destB == nullptr) return false;
    if (destA == nullptr) return true;
    if (destB == nullptr) return false;

    return strcmp(destA, destB) < 0;
}