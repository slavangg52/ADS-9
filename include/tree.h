#pragma once
// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <memory>
#include <vector>

struct TreeNode {
  char data;
  std::vector<std::shared_ptr<TreeNode>> childNodes;
  explicit TreeNode(char val) : data(val) {}
};

class PMTree {
 private:
  std::shared_ptr<TreeNode> rootNode;
  int permutationsCount;

  void constructTree(std::shared_ptr<TreeNode> node,
                     const std::vector<char>& elements);
  void cleanupTree(std::shared_ptr<TreeNode> node);

 public:
  explicit PMTree(const std::vector<char>& elements);
  ~PMTree();

  std::shared_ptr<TreeNode> getRoot() const;
  int getSize() const;
};

std::vector<std::vector<char>> getAllPerms(PMTree& tree);
std::vector<char> getPerm1(PMTree& tree, int num);
std::vector<char> getPerm2(PMTree& tree, int num);

#endif
