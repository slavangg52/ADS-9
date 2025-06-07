// Copyright 2022 NNTU-CS
#include "tree.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <fstream>

void printPerm(const std::vector<char>& perm) {
    for (char c : perm) std::cout << c;
    std::cout << "\n";
}

int main() {
    // Пример использования
    std::vector<char> in = {'1', '2', '3'};
    PMTree tree(in);

    std::cout << "Все перестановки:\n";
    auto perms = getAllPerms(tree);
    for (const auto& perm : perms) printPerm(perm);

    std::cout << "Перестановка 1 (getPerm1): ";
    auto perm1 = getPerm1(tree, 1);
    printPerm(perm1);

    std::cout << "Перестановка 2 (getPerm2): ";
    auto perm2 = getPerm2(tree, 2);
    printPerm(perm2);

    // Эксперимент по производительности
    std::ofstream out("results.txt");
    std::mt19937 rng(std::random_device{}());
    for (int n = 1; n <= 10; ++n) {
        std::vector<char> input;
        for (int i = 0; i < n; ++i) input.push_back('1' + i);

        PMTree t(input);
        out << n << " ";

        auto start = std::chrono::high_resolution_clock::now();
        getAllPerms(t);
        auto end = std::chrono::high_resolution_clock::now();
        double time_all = std::chrono::duration<double>(end - start).count();
        out << time_all << " ";

        std::uniform_int_distribution<int> dist(1, t.fact[n]);
        int num = dist(rng);

        start = std::chrono::high_resolution_clock::now();
        getPerm1(t, num);
        end = std::chrono::high_resolution_clock::now();
        double time_perm1 = std::chrono::duration<double>(end - start).count();
        out << time_perm1 << " ";

        start = std::chrono::high_resolution_clock::now();
        getPerm2(t, num);
        end = std::chrono::high_resolution_clock::now();
        double time_perm2 = std::chrono::duration<double>(end - start).count();
        out << time_perm2 << "\n";
    }
    out.close();

    std::cout << "Данные эксперимента записаны в results.txt.\n";

    return 0;
}
