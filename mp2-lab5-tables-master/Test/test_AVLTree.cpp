#include <gtest.h>
#include "AVLTree.h"

TEST(AVLTreeTest, AddAndFind) {
  AVLTree tree;
  tree.add(TableElement());  
  tree.add(TableElement()); 
  tree.add(TableElement()); 

  // ����� ����������� �����
  TableElement* node1 = tree.find(TableElement());
  TableElement* node2 = tree.find(TableElement());
  TableElement* node3 = tree.find(TableElement());

  // �������� ��������� �����
  ASSERT_NE(node1, nullptr);
  EXPECT_EQ(node1->value);
  ASSERT_NE(node2, nullptr);
  EXPECT_EQ(node2->value);
  ASSERT_NE(node3, nullptr);
  EXPECT_EQ(node3->value);
}

TEST(AVLTreeTest, FindNonexistentNode) {
  AVLTree tree;
  tree.add(TableElement()); 
  tree.add(TableElement());  
  tree.add(TableElement());  

  // ����� ���� � �������������� ������
  TableElement* node = tree.find(TableElement());

  // ��������, ��� ����� ������ nullptr
  EXPECT_EQ(node, nullptr);
}