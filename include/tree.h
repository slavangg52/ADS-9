// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <vector>

class PMTree {
private:
    struct Node {
        char value;                  // Значение узла (символ)
        std::vector<Node*> children; // Дети узла
        Node(char val = '\0') : value(val) {}
    };
    Node* root;                      // Корень дерева
    int n;                           // Размер входного вектора
    std::vector<int> fact;           // Предвычисленные факториалы

    void buildTree(Node* node, std::vector<char> remaining); // Построение дерева
    void deleteTree(Node* node);                             // Удаление дерева

public:
    PMTree(const std::vector<char>& in); // Конструктор
    ~PMTree();                           // Деструктор

    // Дружественные функции для доступа к дереву
    friend std::vector<std::vector<char>> getAllPerms(PMTree& tree);
    friend std::vector<char> getPerm1(PMTree& tree, int num);
    friend std::vector<char> getPerm2(PMTree& tree, int num);
};

// Прототипы функций
std::vector<std::vector<char>> getAllPerms(PMTree& tree);
std::vector<char> getPerm1(PMTree& tree, int num);
std::vector<char> getPerm2(PMTree& tree, int num);

#endif  // INCLUDE_TREE_H_
