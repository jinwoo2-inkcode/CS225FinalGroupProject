/**
 * @file heap.cpp
 * Implementation of a heap class.
 */
#include <cmath>
#include <map>
using namespace std;

template <class T, class Compare>
size_t heap<T, Compare>::root() const
{
  // @TODO Update to return the index you are choosing to be your root.
  return 0;
}

template <class T, class Compare>
size_t heap<T, Compare>::leftChild(size_t currentIdx) const
{
  // @TODO Update to return the index of the left child.
  return 2*currentIdx + 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::rightChild(size_t currentIdx) const
{
  // @TODO Update to return the index of the right child.
  return (2*currentIdx) + 2;
}

template <class T, class Compare>
size_t heap<T, Compare>::parent(size_t currentIdx) const
{
  // @TODO Update to return the index of the parent.
  return floor((currentIdx-1)/2);
}

template <class T, class Compare>
bool heap<T, Compare>::hasAChild(size_t currentIdx) const
{
  // @TODO Update to return whether the given node has a child
  if (leftChild(currentIdx) < _elems.size()) return true;
  else if (rightChild(currentIdx) < _elems.size()) return true;
  else return false;
}

template <class T, class Compare>
size_t heap<T, Compare>::maxPriorityChild(size_t currentIdx) const
{
  // @TODO Update to return the index of the child with highest priority
  ///   as defined by higherPriority()
  size_t left = leftChild(currentIdx);
  size_t right = rightChild(currentIdx);
  if (right < _elems.size()) {
    bool smallerLeft = higherPriority(_elems[left], _elems[right]);
    if (smallerLeft) return left;
    else return right;
  }
  return left;
}

template <class T, class Compare>
void heap<T, Compare>::heapifyDown(size_t currentIdx)
{
  // @TODO Implement the heapifyDown algorithm.
  if (hasAChild(currentIdx)) {
    size_t minChild = maxPriorityChild(currentIdx);
    double weight1 = _weights[_elems[currentIdx]];
    double weight2 = _weights[_elems[minChild]];
    if (weight1 < weight2) {
      std::swap(_elems[currentIdx], _elems[minChild]);
      heapifyDown(minChild);
    }
  }
}

template <class T, class Compare>
void heap<T, Compare>::heapifyUp(size_t currentIdx)
{
    if (currentIdx == root())
      return;
    size_t parentIdx = parent(currentIdx);
    double weight1 = _weights[_elems[currentIdx]];
    double weight2 = _weights[_elems[parentIdx]];
    if (weight1 < weight2) {
      std::swap(_elems[currentIdx], _elems[parentIdx]);
      heapifyUp(parentIdx);
    }
}

template <class T, class Compare>
heap<T, Compare>::heap()
{
    // @TODO Depending on your implementation, this function may or may
    ///   not need modifying
}

template <class T, class Compare>
heap<T, Compare>::heap(const std::vector<T>& elems)
{
  // @TODO Construct a heap using the buildHeap algorithm
  _elems = elems;
  for (size_t i = _elems.size(); i > 0; i--) {
    heapifyDown(parent(i));
  }
}

template <class T, class Compare>
T heap<T, Compare>::pop()
{
    // @TODO Remove, and return, the element with highest priority
    std::swap(_elems[root()], _elems[_elems.size()-1]);
    T result = _elems.back();
    _elems.pop_back();
    heapifyDown(root());
    return result;
}

template <class T, class Compare>
T heap<T, Compare>::peek() const
{
    // @TODO Return, but do not remove, the element with highest priority
    return _elems[root()];
}

template <class T, class Compare>
void heap<T, Compare>::push(const T& elem)
{
    // @TODO Add elem to the heap
    _elems.push_back(elem);
    heapifyUp(_elems.size()-1);
}

template <class T, class Compare>
void heap<T, Compare>::updateElem(const size_t & idx, const T& elem)
{
  // @TODO In-place updates the value stored in the heap array at idx
  // Corrects the heap to remain as a valid heap even after update
  _elems[idx] = elem;
  heapifyUp(idx);
  heapifyDown(idx);
}

template <class T, class Compare>
bool heap<T, Compare>::empty() const
{
  // @TODO Determine if the heap is empty
  if (_elems.empty()) return true;

  /*
  for (size_t i = 0; i < _elems.size(); i++) {
    if (_elems[i]. != T()) return false;
  }
  */
  return false;
}

template <class T, class Compare>
void heap<T, Compare>::getElems(std::vector<T> & heaped) const
{
  for (size_t i = root(); i < _elems.size(); i++) {
      heaped.push_back(_elems[i]);
  }
}

template <class T, class Compare>
void heap<T, Compare>::changeWeight(T item, double newWeight) {
  _weights[item] = newWeight;
}

template <class T, class Compare>
void heap<T, Compare>::addWeights(map<T, double> weights) {
  _weights = weights;
}
