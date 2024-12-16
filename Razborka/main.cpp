// для преобразования в .*
/*
#include <iostream>
#include <fstream>
#include <string>
#include <regex>

int main() {
    std::ifstream inputFile("tochka.txt");
    std::string outputString = "";

    if (!inputFile) {
        std::cerr << "Ошибка открытия файла." << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(inputFile, line)) {
        std::regex pattern("(=.*?)(\x01)");
        std::string replacedLine = std::regex_replace(line, pattern, "=.*$2");
        outputString += replacedLine + "\n";
    }

    inputFile.close();

    std::ofstream outputFile("out.txt");
    if (!outputFile) {
        std::cerr << "Ошибка открытия файла для записи." << std::endl;
        return 1;
    }

    outputFile << outputString;
    outputFile.close();

    std::cout << "Замена завершена. Результат сохранен в output.txt." << std::endl;

    return 0;
}*/


//выделение тэгов
/*
#include <iostream>
#include <fstream>
#include <string>
#include <regex>

int main() {
    std::ifstream inputFile("input.txt");

    if (!inputFile) {
        std::cerr << "Ошибка открытия файла." << std::endl;
        return 1;
    }

    std::string line;
    std::regex pattern("\x01(\\d+)=");
    std::smatch matches;

    int numbersCounter = 1;

    while (std::getline(inputFile, line)) {
        std::string::const_iterator searchStart(line.cbegin());
        std::string numbers;

        while (std::regex_search(searchStart, line.cend(), matches, pattern)) {
            numbers += matches[1].str() + ",";
            searchStart = matches.suffix().first;
        }

        if (!numbers.empty()) {
            numbers.pop_back();
            std::cout << "Numbers " << numbersCounter << ": " << numbers << std::endl;
            numbersCounter++;
        }
    }

    inputFile.close();

    return 0;
}*/

//Сравнение с первым 1=2 в numbers убрать нумерацию 

#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <unordered_set>
#include <sstream>
#include <vector>

int main() {
    std::ifstream inputFile("sravn.txt");

    if (!inputFile) {
        std::cerr << "Ошибка открытия файла." << std::endl;
        return 1;
    }

    std::string firstLine;
    if (!std::getline(inputFile, firstLine)) {
        inputFile.close();
        std::cerr << "Файл пуст." << std::endl;
        return 1;
    }

    std::regex pattern("\\d+");
    std::smatch matches;

    std::unordered_set<std::string> referenceNumbers;
    std::string::const_iterator searchStart(firstLine.cbegin());

    while (std::regex_search(searchStart, firstLine.cend(), matches, pattern)) {
        referenceNumbers.insert(matches[0]);
        searchStart = matches.suffix().first;
    }

    std::vector<std::unordered_set<std::string>> numbersList;
    numbersList.push_back(referenceNumbers);

    int lineNumber = 1;

    while (std::getline(inputFile, firstLine)) {
        std::unordered_set<std::string> currentNumbers;
        std::string::const_iterator searchStart(firstLine.cbegin());

        while (std::regex_search(searchStart, firstLine.cend(), matches, pattern)) {
            currentNumbers.insert(matches[0]);
            searchStart = matches.suffix().first;
        }

        numbersList.push_back(currentNumbers);

        std::cout << "Numbers " << lineNumber << ":\n";

        std::cout << "1) new:";
        bool newNumbersFound = false;
        for (const auto& num : currentNumbers) {
            if (referenceNumbers.find(num) == referenceNumbers.end()) {
                std::cout << " " << num;
                newNumbersFound = true;
            }
        }
        if (!newNumbersFound) {
            std::cout << " -";
        }
        std::cout << std::endl;

        std::cout << "2) no:";
        bool missingNumbersFound = false;
        for (const auto& num : referenceNumbers) {
            if (currentNumbers.find(num) == currentNumbers.end()) {
                std::cout << " " << num;
                missingNumbersFound = true;
            }
        }
        if (!missingNumbersFound) {
            std::cout << " -";
        }
        std::cout << std::endl;

        lineNumber++;
    }

    inputFile.close();

    return 0;
}







