#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <vector>
#include <sstream>
#include <locale>
#include <cwctype>

bool isLetter(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||//какая буква
        (c >= 'а' && c <= 'я') || (c >= 'А' && c <= 'Я');
}


int countShortWords(const std::string& text) {
    int count = 0;
    std::string word;
    bool inWord = false;
    int letterCount = 0;

    for (char c : text) {
        if (isLetter(c)) {
            if (!inWord) {
                inWord = true;
                letterCount = 0;
            }
            letterCount++;
            word += c;
        }
        else {
            if (inWord) {
                if (letterCount <= 4) {
                    count++;
                }
                inWord = false;
                word.clear();
                letterCount = 0;
            }
        }
    }

    // Проверка последнего слова в тексте
    if (inWord && letterCount <= 4) {
        count++;
    }

    return count;
}

int main() {
    std::setlocale(LC_ALL, "Russian");
    std::string filename;

    std::cout << "Введите имя файла для анализа: ";
    std::getline(std::cin, filename);

    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Ошибка: не удалось открыть файл '" << filename << "'" << std::endl;
        return 1;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string text = buffer.str();

    file.close();

    // подсчет слов
    int shortWordCount = countShortWords(text);

    std::cout << "\nАнализ файла: " << filename << std::endl;
    std::cout << "Количество слов, состоящих не более чем из 4 букв: "
        << shortWordCount << std::endl;

    std::cout << "\nТекст файла:" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    std::cout << text << std::endl;
    std::cout << "----------------------------------------" << std::endl;

    return 0;
}