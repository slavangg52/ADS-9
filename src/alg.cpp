// Copyright 2022 NNTU-CS
#include "tree.h"
#include <vector>

// Вспомогательная функция для getAllPerms
void dfsAll(PMTree::Node* node, std::vector<char>& path, std::vector<std::vector<char>>& result) {
    if (node->children.empty()) {
        result.push_back(path);
        return;
    }
    for (auto* child : node->children) {
        path.push_back(child->value);
        dfsAll(child, path, result);
        path.pop_back();
    }
}

std::vector<std::vector<char>> getAllPerms(PMTree& tree) {
    std::vector<std::vector<char>> result;
    std::vector<char> path;
    dfsAll(tree.root, path, result);
    return result;
}

// Вспомогательная функция для getPerm1
void dfsPerm1(PMTree::Node* node, std::vector<char>& path, int& count, int num, std::vector<char>& result) {
    if (node->children.empty()) {
        if (++count == num) result = path;
        return;
    }
    for (auto* child : node->children) {
        path.push_back(child->value);
        dfsPerm1(child, path, count, num, result);
        path.pop_back();
        if (!result.empty()) return;
    }
}

std::vector<char> getPerm1(PMTree& tree, int num) {
    std::vector<char> result, path;
    int count = 0;
    dfsPerm1(tree.root, path, count, num, result);
    return result;
}

// Вспомогательная функция для getPerm2
std::vector<char> getPerm2Helper(PMTree::Node* node, int num, int remaining, std::vector<char> path, const std::vector<int>& fact) {
    if (remaining == 0) {
        return (num == 1) ? path : std::vector<char>();
    }
    int perms_per_child = fact[remaining - 1];
    int i = (num - 1) / perms_per_child;
    if (i >= static_cast<int>(node->children.size())) return {};
    auto* child = node->children[i];
    path.push_back(child->value);
    int next_num = num - i * perms_per_child;
    return getPerm2Helper(child, next_num, remaining - 1, path, fact);
}

std::vector<char> getPerm2(PMTree& tree, int num) {
    if (tree.root->children.empty() || num < 1 || num > tree.fact[tree.n]) return {};
    return getPerm2Helper(tree.root, num, tree.n, {}, tree.fact);
}
