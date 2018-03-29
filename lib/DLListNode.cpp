#include "dancingLinks.hpp"

void DancingLinks::ListNode::unregisterNeighbors()
{
  if (Left != nullptr) {
    Left->Right = Right;
  }
  if (Right != nullptr) {
    Right->Left = Left;
  }
  if (Up != nullptr) {
    Up->Down = Down;
  }
  if (Down != nullptr) {
    Down->Up = Up;
  }
}

void DancingLinks::ListNode::unregisterBase()
{
  Column->unregisterNode();
  //Row->unregisterNode();
}

void DancingLinks::ListNode::registerNeighbors()
{
  if (Left != nullptr) {
    Left->Right = this;
  }
  if (Right != nullptr) {
    Right->Left = this;
  }
  if (Up != nullptr) {
    Up->Down = this;
  }
  if (Down != nullptr) {
    Down->Up = this;
  }
}

void DancingLinks::ListNode::registerBase(){
  Column->registerNode();
  //Row->registerNode();
}

void DancingLinks::ListNode::unlink()
{
  unregisterNeighbors();
  unregisterBase();
}
void DancingLinks::ListNode::link(){
  registerNeighbors();
  registerBase();
}
