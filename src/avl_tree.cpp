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

#include "avl_tree.h"

// node를 root로 가지는 트리가 비어있는지 여부 반환
template <typename T>
bool AVLTree<T>::IsEmpty(Node<T>* node) {
  if (node == nullptr) {
    return -1;  // 찾지 못한 경우 -1 반환
  }
  if (node->size_ == 0) {
    return true;
  }
  return false;
}

// node를 root로 가지는 트리의 원소 수 반환
template <typename T>
int AVLTree<T>::GetSize(Node<T>* node) {
  if (node == nullptr) {
    return -1;  // 찾지 못한 경우 -1 반환
  }
  return node->size_;
}

// node를 root로 가지는 트리의 높이 반환
template <typename T>
int AVLTree<T>::GetHeight(Node<T>* node) {
  if (node == nullptr) {
    return -1;  // 찾지 못한 경우 -1 반환
  }
  return node->height_;
}

// node를 root로 가지는 트리에서 target 노드의 깊이 반환
template <typename T>
int AVLTree<T>::GetDepth(Node<T>* node, T target) {
  int depth        = 0;
  Node<T>* current = node;

  while (current != nullptr) {
    if (current->key_ == target) {
      return depth;
    }
    if (current->key_ > target) {
      current = current->left_;
    } else {
      current = current->right_;
    }
    depth++;
  }
  return -1;  // 찾지 못한 경우 -1 반환
}

// node를 root로 가지는 트리에서 target 노드의 포인터 반환
template <typename T>
Node<T>* AVLTree<T>::FindNode(Node<T>* node, T target) {
  while (node != nullptr) {
    if (node->key_ == target) {
      return node;
    }
    if (node->key_ > target) {
      node = node->left_;
    } else {
      node = node->right_;
    }
  }
  return nullptr;  // 찾지 못한 경우 nullptr 반환
}

// a와 b 중 더 큰 값을 return
template <typename T>
T AVLTree<T>::Max(T a, T b) {
  return (a > b) ? a : b;
}
// 특정 노드의 Left-child subtree, Right-child subtree의 Height를 기준으로
// Height update
template <typename T>
void AVLTree<T>::UpdateHeight(Node<T>* node) {
  // GetHeight의 기본값이 -1일 경우 0으로 치환
  int left_height  = GetHeight(node->left_);
  left_height      = (left_height == -1) ? 0 : left_height;
  int right_height = GetHeight(node->right_);
  right_height     = (right_height == -1) ? 0 : right_height;
  // height update
  node->height_ = 1 + Max(left_height, right_height);

  // Height가 1인경우는 Leaf node. node 초기화
  if (node->height_ == 1) {
    node->left_  = nullptr;
    node->right_ = nullptr;
    node->size_  = 1;
  } else {
    // Node에 해당 node를 root로 하는 Subtree의 Size 정보가 있으므로 갱신
    int lsize   = (node->left_ != nullptr) ? node->left_->size_ : 0;
    int rsize   = (node->right_ != nullptr) ? node->right_->size_ : 0;
    node->size_ = lsize + rsize + 1;
  }
}
// 균형을 유지하기 위한 Right Rotate
template <typename T>
Node<T>* AVLTree<T>::RightRotate(Node<T>* node) {
  Node<T>* left_child       = node->left_;
  Node<T>* left_right_child = left_child->right_;

  left_child->right_ = node;
  node->left_        = left_right_child;

  UpdateHeight(node);
  UpdateHeight(left_child);

  return left_child;
}

// 균형을 유지하기 위한 Left Rotate
template <typename T>
Node<T>* AVLTree<T>::LeftRotate(Node<T>* node) {
  Node<T>* right_child      = node->right_;
  Node<T>* right_left_child = right_child->left_;

  right_child->left_ = node;
  node->right_       = right_left_child;

  UpdateHeight(node);
  UpdateHeight(right_child);

  return right_child;
}

// 실제로 AVLtree에 Insert하는 로직
template <typename T>
Node<T>* AVLTree<T>::InsertNode(Node<T>* node, T target) {
  // 노드가 자기 자리를 찾았을 경우
  if (node == nullptr) {
    return new Node(target);
  }  // BST order에 따라 자리 탐색
  if (target < node->key_) {
    node->left_ = InsertNode(node->left_, target);
  } else if (target > node->key_) {
    node->right_ = InsertNode(node->right_, target);
  }

  // target node의 모든 Ancestor의 height를 update
  UpdateHeight(node);

  // get balance factor in specific node
  int left_height  = GetHeight(node->left_);
  left_height      = (left_height == -1) ? 0 : left_height;
  int right_height = GetHeight(node->right_);
  right_height     = (right_height == -1) ? 0 : right_height;
  int bf           = left_height - right_height;

  // LL case
  if (bf > 1 && target < node->left_->key_) {
    return RightRotate(node);
  }  // RR case
  if (bf < -1 && target > node->right_->key_) {
    return LeftRotate(node);
  }  // LR case
  if (bf > 1 && target > node->left_->key_) {
    node->left_ = LeftRotate(node->left_);
    return RightRotate(node);
  }  // RL case
  if (bf < -1 && target < node->right_->key_) {
    node->right_ = RightRotate(node->right_);
    return LeftRotate(node);
  }
  return node;
}

// 트리에 target 노드를 추가
template <typename T>
int AVLTree<T>::Insert(T target) {
  root_ = InsertNode(root_, target);
  // 문제 조건의 깊이와 높이의 합을 리턴
  return GetDepth(root_, target) + FindNode(root_, target)->height_;
}

// target의 높이, 깊이의 합 출력 , target의 부모 ~ 루트 경로의 노드들의 key값의
// 합 출력
template <typename T>
std::pair<int, int> AVLTree<T>::GetAncestor(Node<T>* node, T target) {
  Node<T>* target_node = FindNode(node, target);
  if (target_node == nullptr) {
    return std::make_pair(-1, -1);
  }

  int depth  = GetDepth(node, target);
  int height = GetHeight(target_node);
  int K      = depth + height;

  int key_sum      = 0;
  Node<T>* current = node;  // root start
  while (current != nullptr) {
    if (current->key_ == target) {
      break;
    }
    key_sum += current->key_;
    if (target < current->key_) {
      current = current->left_;
    } else {
      current = current->right_;
    }
  }
  return std::make_pair(K, key_sum);
}

// node를 root로 가지는 트리에서 가장 작은 값을 return
template <typename T>
Node<T>* AVLTree<T>::GetMin(Node<T>* node) {
  while (node != nullptr && node->left_ != nullptr) {
    node = node->left_;
  }
  return node;
}

// node를 root로 가지는 트리에서 가장 큰 값을 return
template <typename T>
Node<T>* AVLTree<T>::GetMax(Node<T>* node) {
  while (node != nullptr && node->right_ != nullptr) {
    node = node->right_;
  }
  return node;
}

// node를 root로 가지는 트리에서 최고값과 최솟값의 산술평균 리턴
template <typename T>
int AVLTree<T>::GetAverage(Node<T>* node) {
  Node<T>* min_node = GetMin(node);
  Node<T>* max_node = GetMax(node);

  T min_key   = min_node->key_;
  T max_key   = max_node->key_;
  int average = (min_key + max_key) / 2;

  return average;
}

// 전체 트리의 root리턴
template <typename T>
Node<T>* AVLTree<T>::getRoot() {
  return root_;
}
// 문제 조건에 맞추기 위한 Erase
template <typename T>
int AVLTree<T>::Erase(T target) {
  Node<T>* node = FindNode(root_, target);
  if (node == nullptr)
    return 0;
  else {
    int ret = GetDepth(root_, target) + FindNode(root_, target)->height_;
    root_   = EraseNode(root_, target);
    return ret;
  }
}

// node를 root로 가지는 트리에서 target 노드를 제거
template <typename T>
Node<T>* AVLTree<T>::EraseNode(Node<T>* node, T target) {
  // Node를 찾지 못하는 경우 nullptr return
  if (node == nullptr) return node;
  // BST order에 따라 Node 찾음
  if (target < node->key_)
    node->left_ = EraseNode(node->left_, target);
  else if (target > node->key_)
    node->right_ = EraseNode(node->right_, target);
  else {
    // Erase logic
    if (node->left_ == nullptr || node->right_ == nullptr) {
      Node<T>* tmp = node->left_ ? node->left_ : node->right_;
      if (tmp == nullptr) {
        tmp  = node;
        node = nullptr;
      } else {
        *node = *tmp;
      }
      delete tmp;
    } else {
      Node<T>* cur = node->right_;
      while (cur->left_ != nullptr) {
        cur = cur->left_;
      }
      node->key_   = cur->key_;
      node->right_ = EraseNode(node->right_, cur->key_);
    }
  }
  if (node == nullptr) {
    return node;
  }
  // 모든 Ancestor에 대해 Height update
  UpdateHeight(node);

  // 균형을 검사하기 위한 Balance Factor 계산
  int bf = getBf(node);

  if (bf > 1 && getBf(node->left_) >= 0) return RightRotate(node);
  if (bf > 1 && getBf(node->left_) < 0) {
    node->left_ = LeftRotate(node->left_);
    return RightRotate(node);
  }
  if (bf < -1 && getBf(node->right_) <= 0) return LeftRotate(node);
  if (bf < -1 && getBf(node->right_) > 0) {
    node->right_ = RightRotate(node->right_);
    return LeftRotate(node);
  }
  return node;
}
// balanced factor 계산 로직
template <typename T>
int AVLTree<T>::getBf(Node<T>* node) {
  if (node == nullptr) return 0;
  int lh = node->left_ != nullptr ? node->left_->height_ : 0;
  int rh = node->right_ != nullptr ? node->right_->height_ : 0;
  return lh - rh;
}

// node를 root로 가지는 트리에서 target 값의 height + depth 와 rank 리턴
template <typename T>
std::pair<int, int> AVLTree<T>::GetRank(Node<T>* node, T target) {
  int depth        = 0;
  int rank         = 0;
  Node<T>* current = node;

  while (current != nullptr) {
    if (current->key_ == target) {
      rank += (current->left_ != nullptr ? current->left_->size_ : 0) + 1;
      int height = current->height_;
      int K      = depth + height;
      return std::make_pair(K, rank);  // return K, rank
    }

    if (target < current->key_) {
      current = current->left_;
    } else {
      rank += (current->left_ != nullptr ? current->left_->size_ : 0) + 1;
      current = current->right_;
    }
    depth++;
  }

  return std::make_pair(-1, -1);  // error case , 없는 값이 들어온 경우
}