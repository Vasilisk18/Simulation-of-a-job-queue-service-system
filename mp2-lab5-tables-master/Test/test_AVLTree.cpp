#include <gtest.h>
#include "AVLTree.h"

TEST(AVLTreeTest, AddAndFind) {
  AVLTree tree;
  tree.add(TableElement());  
  tree.add(TableElement()); 
  tree.add(TableElement()); 

  // Поиск добавленных узлов
  TableElement* node1 = tree.find(TableElement());
  TableElement* node2 = tree.find(TableElement());
  TableElement* node3 = tree.find(TableElement());

  // Проверка найденных узлов
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

  // Поиск узла с несуществующим ключом
  TableElement* node = tree.find(TableElement());

  // Проверка, что поиск вернул nullptr
  EXPECT_EQ(node, nullptr);
}