// Copyright 2022 NNTU-CS
#include <chrono>
#include <iostream>
#include <memory>
#include <random>
#include <vector>

#include "tree.h"

int main() {
  const std::vector<char> inputData = {'1', '2', '3', '4', '5', '6'};
  PMTree permutationTree(inputData);
  auto timeStart = std::chrono::high_resolution_clock::now();
  auto allPermutations = getAllPerms(permutationTree);
  auto timeEnd = std::chrono::high_resolution_clock::now();
  std::cout << "Total permutations: " << allPermutations.size() << '\n';
  std::cout
      << "getAllPerms execution time: "
      << std::chrono::duration<double, std::milli>(timeEnd - timeStart).count()
      << " ms\n";

  std::random_device randomDevice;
  std::mt19937 generator(randomDevice());
  std::uniform_int_distribution<> distribution(1, allPermutations.size());
  const int testIndex = distribution(generator);

  timeStart = std::chrono::high_resolution_clock::now();
  auto permutation1 = getPerm1(permutationTree, 5000);
  timeEnd = std::chrono::high_resolution_clock::now();

  std::cout
      << "getPerm1 execution time: "
      << std::chrono::duration<double, std::milli>(timeEnd - timeStart).count()
      << " ms\n";

  timeStart = std::chrono::high_resolution_clock::now();
  auto permutation2 = getPerm2(permutationTree, 5000);
  timeEnd = std::chrono::high_resolution_clock::now();

  std::cout
      << "getPerm2 execution time: "
      << std::chrono::duration<double, std::milli>(timeEnd - timeStart).count()
      << " ms\n";

  if (permutation1 != permutation2) {
    std::cerr << "Error: Different results from getPerm1 and getPerm2!\n";
    return 1;
  }

  return 0;
}
