#include "gtest.h"
#include "TreeTable.h"
#include "tableelement.h"
#include "AVLTree.h"

TEST(TreeTest, Add) {
  // Создаем дерево и добавляем элементы
  Tree t;
  TableElement te1("key1", Polynomial());
  TableElement te2("key2", Polynomial());
  TableElement te3("key3", Polynomial());
  t.add(te1), 1;
  t.add(te2), 2;
  t.add(te3), 3;
}

TEST(TreeTest, Find) {
  // Создаем дерево и добавляем элементы
  Tree t;
  TableElement te1("key1", Polynomial());
  TableElement te2("key2", Polynomial());
  TableElement te3("key3", Polynomial());
  t.add(te1);
  t.add(te2);
  t.add(te3);
  // Поиск элементов
  auto res1 = t.find(te1);
  ASSERT_TRUE(res1.first != nullptr);
  ASSERT_EQ(res1.second, 1);
  auto res2 = t.find(te2);
  ASSERT_TRUE(res2.first != nullptr);
  ASSERT_EQ(res2.second, 2);
  auto res3 = t.find(te3);
  ASSERT_TRUE(res3.first != nullptr);
  ASSERT_EQ(res3.second, 3);
  // Поиск несуществующего элемента
  TableElement te4("key4", Polynomial());
  auto res4 = t.find(te4);
  ASSERT_TRUE(res4.first == nullptr);
}

TEST(TreeTest, ExistsKey) {
  // Создаем дерево и добавляем элементы
  Tree t;
  TableElement te1("key1", Polynomial());
  TableElement te2("key2", Polynomial());
  TableElement te3("key3", Polynomial());
  t.add(te1);
  t.add(te2);
  t.add(te3);
  // Проверка существования ключей
  ASSERT_TRUE(t.existsKey(te1));
  ASSERT_TRUE(t.existsKey(te2));
  ASSERT_TRUE(t.existsKey(te3));
  TableElement te4("key4", Polynomial());
  ASSERT_FALSE(t.existsKey(te4));
}

TEST(TreeTest, Get) {
  // Создаем дерево и добавляем элементы
  Tree t;
  TableElement te1("key1", Polynomial("2x^2"));
  TableElement te2("key2", Polynomial("x^3 + 3"));
  TableElement te3("key3", Polynomial("3x"));
  t.add(te1);
  t.add(te2);
  t.add(te3);
  // Получение значений по ключу
  ASSERT_EQ(t.get("key1"), te1);
  ASSERT_EQ(t.get("key2"), te2);
  ASSERT_EQ(t.get("key3"), te3);
  // Получение значения по несуществующему ключу
  ASSERT_EQ(t.get("key4"), TableElement());
}
