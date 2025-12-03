#include <iostream>
#include <cstdlib>
#include <algorithm>
#include "train.h"
#include "locale.h"


void displayMenu();
void addTrain(TRAIN*& trains, int& count, int& capacity);
//void deleteTrain(TRAIN*& trains, int& count, int index);
//void editTrain(TRAIN* trains, int count, int index);
//void displayTrains(TRAIN* trains, int count);
//void sortTrains(TRAIN* trains, int count);
//void findTrains(TRAIN* trains, int count);


int main() {
	setlocale(LC_ALL, "Russian");
	int count = 0;
	int choice;
	int capacity = 0;
	TRAIN* trains = nullptr;

	do {
		displayMenu();
		std::cout << "Выберите действие:";
		std::cin >> choice;
		try {
			switch (choice) {
				case 1:
					addTrain(trains, count, capacity);
					break;
				case 2:
					if (count == 0) {
						std::cout << "Список поездов пуст!" << std::endl;
						break;
					}
					std::cout << "Все поезда:" << std::endl;
					for (int i = 0; i < count; i++) {
						std::cout << i + 1 << ". " << trains[i] << std::endl;
					}
					std::cout << "Введите номер поезда для удаления: ";
					int delIndex;
					std::cin >> delIndex;
					if (delIndex < 1 || delIndex > count) {
						throw std::out_of_range("Неверный номер поезда");
					}
					//deleteTrain(trains, count, delIndex - 1);
					break;

				case 3: // Редактировать поезд
					if (count == 0) {
						std::cout << "Список поездов пуст!" << std::endl;
						break;
					}
					std::cout << "Все поезда:" << std::endl;
					for (int i = 0; i < count; i++) {
						std::cout << i + 1 << ". " << trains[i] << std::endl;
					}
					std::cout << "Введите номер поезда для редактирования: ";
					int editIndex;
					std::cin >> editIndex;
					if (editIndex < 1 || editIndex > count) {
						throw std::out_of_range("Неверный номер поезда");
					}
					//editTrain(trains, count, editIndex - 1);
					break;
				case 4:
					//displayTrains(trains, count);
					break;

				case 5: // Отсортировать по пункту назначения
					//sortTrains(trains, count);
					std::cout << "Поезда отсортированы по пункту назначения." << std::endl;
					break;
				case 6: // Найти поезда после указанного времени
					//findTrains(trains, count);
					break;

				case 0: // Выход
					std::cout << "Выход из программы..." << std::endl;
					break;

				default:
					std::cout << "Неверный выбор. Попробуйте снова." << std::endl;
				}
		}
		catch (const std::exception& e) {
			std::cout << "Ошибка: " << e.what() << std::endl;
		}

		std::cout << std::endl;

	} while (choice != 0);
	delete[] trains;
	return 0;
}
void displayMenu() {
	std::cout << "МЕНЮ УПРАВЛЕНИЯ ПОЕЗДАМИ" << std::endl;
	std::cout << "1. Добавить поезд" << std::endl;
	std::cout << "2. Удалить поезд" << std::endl;
	std::cout << "3. Редактировать поезд" << std::endl;
	std::cout << "4. Показать все поезда" << std::endl;
	std::cout << "5. Отсортировать поезда по пункту назначения" << std::endl;
	std::cout << "6. Найти поезда, отправляющиеся после указанного времени" << std::endl;
	std::cout << "0. Выход" << std::endl;
}


// Добавление нового поезда
void addTrain(TRAIN*& trains, int& count, int& capacity) {
	if (count >= capacity) {
		// Увеличиваем емкость массива
		int newCapacity = (capacity == 0) ? 2 : capacity * 2;
		TRAIN* newTrains = new TRAIN[newCapacity];

		// Копируем существующие поезда
		for (int i = 0; i < count; i++) {
			newTrains[i] = trains[i];
		}

		delete[] trains;
		trains = newTrains;
		capacity = newCapacity;
	}

	// Ввод данных для нового поезда
	std::cout << "Добавление нового поезда:" << std::endl;
	std::cin >> trains[count];
	count++;

	std::cout << "Поезд успешно добавлен!" << std::endl;
}