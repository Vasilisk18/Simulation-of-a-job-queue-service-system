#include <gtest.h>
#include "../include/hashtable.h"

TEST(KEYHASH, check_function)
{
	KeyHash k;
	auto key = k("123");
	ASSERT_EQ(key, 50);
	key = k(";d");
	ASSERT_EQ(key, 59);
	key = k("abcde");
	ASSERT_EQ(key, 95);
}

// Тест добавления элемента в хэш-таблицу
TEST(HashTableTest, AddElementTest)
{
  HashTable<std::string, int, KeyHash> hashTable;
  hashTable.add("test_key", 100);
  int value = 0;
  EXPECT_TRUE(hashTable.get("test_key", value));
  EXPECT_EQ(value, 100);
}

// Тест поиска несуществующего ключа в хэш-таблице
TEST(HashTableTest, GetNonExistingKeyTest)
{
  HashTable<std::string, int, KeyHash> hashTable;
  int value = 0;
  EXPECT_FALSE(hashTable.get("non_existing_key", value));
}

// Тест удаления элемента из хэш-таблицы
TEST(HashTableTest, RemoveElementTest)
{
  HashTable<std::string, int, KeyHash> hashTable;
  hashTable.add("test_key", 100);
  EXPECT_TRUE(hashTable.existsKey("test_key"));
  hashTable.remove("test_key");
  EXPECT_FALSE(hashTable.existsKey("test_key"));
}
