// MIT License

// Copyright(c) 2024 GUGONG2

//     Permission is hereby granted,
//     free of charge,
//     to any person obtaining a copy of this software and associated
//     documentation files(the "Software"), to deal in the Software without
//     restriction, including without limitation the rights to use, copy,
//     modify, merge, publish
//     ,
//     distribute, sublicense, and / or sell copies of the Software,
//     and to permit persons to whom the Software is furnished to do so,
//     subject to the following conditions :

//     The above copyright notice and this permission notice shall be included
//     in all copies or substantial portions of the Software.

//     THE SOFTWARE IS PROVIDED "AS IS",
//     WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
//     INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//     FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL
//     THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
//     OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
//     ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
//     OTHER DEALINGS IN THE SOFTWARE.
//
//     2024.11 GUGONG2

#ifndef AVLTREE_H
#define AVLTREE_H
#include "node.h"
#include "tree.h"

template <typename T>
class AVLTree : public Tree<T> {
public:
  // 기본 생성자
  AVLTree() : root_(nullptr) {}
  // node를 root로 가지는 AVLTree 생성자
  AVLTree(Node<T>* node) : root_(node) {}
  // AVLTree의 root 반환
  Node<T>* GetRoot() {
    return this->root_;
  }
  // node를 root로 가지는 트리가 비어있는지 여부 반환
  bool IsEmpty(Node<T>* node);
  // node를 root로 가지는 트리의 원소 수 반환
  int GetSize(Node<T>* node);
  // node를 root로 가지는 트리의 높이 반환
  int GetHeight(Node<T>* node);
  // node를 root로 가지는 트리에서 target 노드의 깊이 반환
  int GetDepth(Node<T>* node, T target);
  // node를 root로 가지는 트리에서 target 노드 포인터 반환
  Node<T>* FindNode(Node<T>* node, T target);
  // AVL tree insert, return depth + height
  int Insert(T target);
  // AVL tree insert, insert node according to BST order
  Node<T>* InsertNode(Node<T>* node, T target);
  // User Defined max function
  T Max(T a, T b);
  // Update Height
  void UpdateHeight(Node<T>* node);
  // right rotate function
  Node<T>* RightRotate(Node<T>* node);
  // left rotate function
  Node<T>* LeftRotate(Node<T>* node);
  // node를 root로 가지는 트리에 target 노드의 깊이와 높이의 합,
  // target 노드의 부모로부터 root까지 경로의 노드들의 key 값들의 합을 공백으로
  // 구분하여 출력
  std::pair<int, int> GetAncestor(Node<T>* node, T target);
  // node를 root로 하는 트리에서 가장 작은 key값을 가진 노ㄷ 반환
  Node<T>* GetMin(Node<T>* node);
  // node를 root로 하는 트리에서 가장 큰 key값을 가진 노드 반환
  Node<T>* GetMax(Node<T>* node);
  // node를 root로 가지는 트리에서 노드들의 key 값의 최솟값(a)와 최댓값(b)의
  // 산술평균((a + b)/2) 을 출력
  int GetAverage(Node<T>* node);
  // node를 root로 가지는 트리에서 target 노드의 깊이와 높이의 합,
  // 순위(rank)를 공백으로 구분하여 출력
  std::pair<int, int> GetRank(Node<T>* node, T target);
  // node를 root로 가지는 트리에서 target 노드의 깊이와 높이의 합을 출력하고
  // 해당 노드를 삭제
  Node<T>* EraseNode(Node<T>* node, T target);
  // AVLTree Erase, return Height + Depth
  int Erase(T target);
  // balanced factor 계산
  int getBf(Node<T>* node);
  // root 반환
  Node<T>* getRoot();

private:
  Node<T>* root_;
};
#endif