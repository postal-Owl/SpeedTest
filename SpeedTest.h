#pragma once

#include <iostream>
#include <chrono>

#ifndef SPEEDTEST_H
#define SPEEDTEST_H

// Первый параметр - кол-во итреаций для расчета среднего времени,
// Все прочие аргументы - это лямбда выражения типа:
// [] { foo(); },
// Кол-во передаваемых лямбда функций - неограничено
template<typename... Tasks>
void SpeedTest(const int& N, Tasks... tasks) {
    uint8_t count = 0;
    auto start_total = std::chrono::high_resolution_clock::now();

    ([&] {
        double total = 0;
        for (int i = 0; i < N; i++) {
            auto start = std::chrono::high_resolution_clock::now();
            tasks();
            auto end = std::chrono::high_resolution_clock::now();
            total += std::chrono::duration<double>(end - start).count();
        }
        std::cout << "Среднее время работы блока " << static_cast<int>(count) << ": " << total / N << " сек." << std::endl;
        count++;
        }(), ...);

    auto end_total = std::chrono::high_resolution_clock::now();
    std::cout << "Общее время выполнения: " << std::chrono::duration<double>(end_total - start_total).count() << " сек." << std::endl;
}

#endif // SPEEDTEST_H
