// SpeedTest.cpp : Определяет функции для статической библиотеки.
//

#include "SpeedTest.h"

template<typename... Tasks>
std::vector<double> SpeedTest(const int& N, Tasks... tasks);

template<typename SubTask, typename... Tasks>
std::vector<double> SpeedTestSub(const int& N, SubTask First, Tasks... tasks);

void STPrint(std::vector<double> Time, std::ostream& os) {
    unsigned int size = 0;
    for (auto block : Time) {
        os << "Среднее время работы блока [" << size << "]: " << block << " сек." << std::endl;
        size++;
    }
}

//  /\__/\
// (=^x^=)
//  (")(")_/