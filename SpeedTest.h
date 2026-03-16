#pragma once

#include <iostream>
#include <chrono>
#include <vector>

#ifndef SPEEDTEST_H
#define SPEEDTEST_H

// Первый параметр - кол-во итреаций для расчета среднего времени,
// Все прочие аргументы - это лямбда выражения типа:
// [] { foo(); },
// Кол-во передаваемых лямбда функций - неограничено
template<typename... Tasks>
std::vector<double> SpeedTest(const int& N, Tasks... tasks) {
    std::vector<double> Time;

    // unsigned int count = 0;
    // os << "Блоков проверено: " << count;

    ([&] {
        double total = 0;
        for (int i = 0; i < N; i++) {
            auto start = std::chrono::high_resolution_clock::now();
            tasks();
            auto end = std::chrono::high_resolution_clock::now();
            total += std::chrono::duration<double>(end - start).count();
        }
        Time.push_back(total / N);
        // count++;
        // for (int i = 0; pow(10, i) < count; i++)
        //     os << '\b';
        // os << count;

        // count++;
        // os.seekp(18);
        // os << count;
        }(), ...);
    // os << '\n';

    return Time;
}

template<typename SubTask, typename... Tasks>
std::vector<double> SpeedTestSub(const int& N, SubTask First, Tasks... tasks) {
    std::vector<double> Time;

    double SubTime = 0;     // Предполагается, что этот блок присутствует во всех прочих блоках
    for (int i = 0; i < N; i++) {
        auto start = std::chrono::high_resolution_clock::now();
        First();
        auto end = std::chrono::high_resolution_clock::now();
        SubTime += std::chrono::duration<double>(end - start).count();
    }

    SubTime /= N;
    // unsigned int count = 0;
    // os << "Блоков проверено: " << count;

    ([&] {
        double total = 0;
        for (int i = 0; i < N; i++) {
            auto start = std::chrono::high_resolution_clock::now();
            tasks();
            auto end = std::chrono::high_resolution_clock::now();
            total += std::chrono::duration<double>(end - start).count();
        }
        Time.push_back(total / N - SubTime);
        // count++;
        // for (int i = 0; pow(10, i) < count; i++)
        //     os << '\b';
        // os << count;

        // count++;
        // os.seekp(18);
        // os << count;
        }(), ...);
    // os << '\n';
    
    return Time;
}

void STPrint(std::vector<double> data, std::ostream& os);

#endif // SPEEDTEST_H
