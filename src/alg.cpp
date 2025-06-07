// Copyright 2022 NNTU-CS
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <locale>
#include <memory>
#include <vector>

#include "tree.h"

PMTree::PMTree(const std::vector<char>& elements) : permutationsCount(0) {
  rootNode = std::make_shared<TreeNode>(0);
  constructTree(rootNode, elements);
}

PMTree::~PMTree() { cleanupTree(rootNode); }

void PMTree::constructTree(std::shared_ptr<TreeNode> node,
                           const std::vector<char>& remaining) {
  std::vector<char> sorted = remaining;
  std::sort(sorted.begin(), sorted.end());

  for (size_t i = 0; i < sorted.size(); ++i) {
    char val = sorted[i];
    auto child = std::make_shared<TreeNode>(val);
    node->childNodes.push_back(child);

    std::vector<char> next = sorted;
    next.erase(next.begin() + i);
    constructTree(child, next);
  }
}

void PMTree::cleanupTree(std::shared_ptr<TreeNode> node) {
  node->childNodes.clear();
}

std::shared_ptr<TreeNode> PMTree::getRoot() const { return rootNode; }

int PMTree::getSize() const { return permutationsCount; }

void collectPermutations(std::shared_ptr<TreeNode> node,
                         std::vector<char>& path,
                         std::vector<std::vector<char>>& result) {
  if (node->data != 0) path.push_back(node->data);
  if (node->childNodes.empty()) {
    result.push_back(path);
  } else {
    for (auto child : node->childNodes) {
      collectPermutations(child, path, result);
    }
  }
  if (!path.empty() && node->data != 0) path.pop_back();
}

std::vector<std::vector<char>> getAllPerms(PMTree& tree) {
  std::vector<std::vector<char>> result;
  std::vector<char> path;
  collectPermutations(tree.getRoot(), path, result);
  return result;
}

std::vector<char> getPerm1(PMTree& tree, int num) {
  auto perms = getAllPerms(tree);
  return (num > 0 && num <= static_cast<int>(perms.size()))
             ? perms[num - 1]
             : std::vector<char>{};
}

std::vector<char> getPermByIndex(std::shared_ptr<TreeNode> node, int& index,
                                 int target) {
  if (node->childNodes.empty()) {
    ++index;
    return (index == target) ? std::vector<char>{node->data}
                             : std::vector<char>{};
  }

  for (auto child : node->childNodes) {
    auto result = getPermByIndex(child, index, target);
    if (!result.empty()) {
      if (node->data != 0) result.insert(result.begin(), node->data);
      return result;
    }
  }
  return {};
}

std::vector<char> getPerm2(PMTree& tree, int num) {
  int index = 0;
  return getPermByIndex(tree.getRoot(), index, num);
}
