#ifndef TREE_H
#define TREE_H

#include <utility>
#include "TreeNode.h"
#include "tableelement.h"

// Класс "дерево"
class AVLTree
{
	// Структура узла
	struct AVLNode
	{
		TableElement data;
		AVLNode* left;
		AVLNode* right;
		int height;

		AVLNode(const TableElement& _data) : data(_data), left(nullptr), right(nullptr), height(1) {}
	};

	AVLNode* root; // Корень

// Метод для подсчета высоты узла
	int getHeight(AVLNode* Node) {
		return (Node == nullptr) ? 0 : Node->height;
	}

	// Метод для подсчета баланса узла
	int getBalanceFactor(AVLNode* Node) {
		return getHeight(Node->right) - getHeight(Node->left);
	}

	// Метод для пересчета высоты узла
	void fixHeight(AVLNode* Node) {
		int left_height = getHeight(Node->left);
		int right_height = getHeight(Node->right);
		Node->height = std::max(left_height, right_height) + 1;
	}

	// Метод для поворота вправо
	AVLNode* rotateRight(AVLNode* Node) {
		AVLNode* new_root = Node->left;
		Node->left = new_root->right;
		new_root->right = Node;
		fixHeight(Node);
		fixHeight(new_root);
		return new_root;
	}

	// Метод для поворота влево
	AVLNode* rotateLeft(AVLNode* Node) {
		AVLNode* new_root = Node->right;
		Node->right = new_root->left;
		new_root->left = Node;
		fixHeight(Node);
		fixHeight(new_root);
		return new_root;
	}

	// Метод для балансировки узла
	AVLNode* balance(AVLNode* Node) {
		fixHeight(Node);
		if (getBalanceFactor(Node) == 2) {
			if (getBalanceFactor(Node->right) < 0) {
				Node->right = rotateRight(Node->right);
			}
			return rotateLeft(Node);
		}
		if (getBalanceFactor(Node) == -2) {
			if (getBalanceFactor(Node->left) > 0) {
				Node->left = rotateLeft(Node->left);
			}
			return rotateRight(Node);
		}
		return Node;
	}

	// Добавление в дерево
	AVLNode* _add(AVLNode* Node, const TableElement& data)
	{
		// Если пуст, то создание нового узла
		if (Node == nullptr)
			return new AVLNode(data);

		if (data < Node->data)
			Node->left = _add(Node->left, data);
		else if (Node->data < data)
			Node->right = _add(Node->right, data);
		else // ключ уже существует
			return Node;

		// Обновление высоты текущего узла
		Node->height = std::max(getHeight(Node->left), getHeight(Node->right)) + 1;

		// Получаем балансировку текущего узла
		int balance = getBalanceFactor(Node);

		// Проверяем, не нарушается ли баланс дерева
		if (balance > 1 && data < Node->left->data)
			return rotateRight(Node);

		if (balance < -1 && Node->right->data < data)
			return rotateLeft(Node);

		if (balance > 1 && Node->left->data < data)
		{
			Node->left = rotateLeft(Node->left);
			return rotateRight(Node);
		}

		if (balance < -1 && data < Node->right->data)
		{
			Node->right = rotateRight(Node->right);
			return rotateLeft(Node);
		}

		return Node;
	}

	// Поиск по дереву
	std::pair<AVLNode*, int> _find(AVLNode* Node, const TableElement& key, int count)
	{
		// Если текущий пуст или нашли ключ, то возвращаем текущий
		if (Node == nullptr || Node->data == key)
			return std::pair<AVLNode*, int>(Node, count + 1);
		// Иначе переход в левое или правое поддерево
		else if (Node->data < key)
			return _find(Node->right, key, count + 1);
		else
			return _find(Node->left, key, count + 1);
	}

	bool _existsKey(AVLNode* Node, const TableElement& te)
	{
		if (Node == nullptr)
			return false;
		else if (Node->data.key() == te.key())
			return true;
		else if (Node->data < te)
			return _existsKey(Node->right, te);
		else
			return _existsKey(Node->left, te);
	}

	// Удаление из дерева
	AVLNode* _remove(AVLNode* Node, const TableElement& key)
	{
		// Если текущий пуст, то возвращаем nullptr
		if (Node == nullptr)
			return Node;
		// Иначе переход в левое или правое поддерево
		if (key < Node->data)
			Node->left = _remove(Node->left, key);
		else if (key > Node->data)
			Node->right = _remove(Node->right, key);
		else // Найден ключ
		{
			// Если один из дочерних узлов пуст
			if (Node->left == nullptr || Node->right == nullptr)
			{
				AVLNode* temp = Node->left ? Node->left : Node->right;

				// Если оба дочерних узла пусты
				if (temp == nullptr)
				{
					temp = Node;
					Node = nullptr;
				}
				else // Если один дочерний узел не пуст
					*Node = *temp; // Копирование значений дочернего узла в текущий узел
				delete temp;
			}
			else // Оба дочерних узла не пусты
			{
				AVLNode* temp = Node->right;
				while (temp->left != nullptr)
					temp = temp->left;

				Node->data = temp->data; // Замена значений текущего узла на значения крайнего левого дочернего узла
				Node->right = _remove(Node->right, temp->data);
			}
		}
		// Если в дереве остался только один узел, то сразу возвращаем его
		if (Node == nullptr)
			return Node;

		// Обновляем высоту текущего узла
		Node->height = std::max(getHeight(Node->left), getHeight(Node->right)) + 1;

		// Получаем балансировку текущего узла
		int balance = getBalanceFactor(Node);

		// Проверяем, не нарушается ли баланс дерева
		if (balance > 1 && getBalanceFactor(Node->right) >= 0)
			return rotateLeft(Node);

		if (balance < -1 && getBalanceFactor(Node->left) <= 0)
			return rotateRight(Node);

		if (balance > 1 && getBalanceFactor(Node->right) < 0)
		{
			Node->right = rotateRight(Node->right);
			return rotateLeft(Node);
		}

		if (balance < -1 && getBalanceFactor(Node->left) > 0)
		{
			Node->left = rotateLeft(Node->left);
			return rotateRight(Node);
		}
		return Node;
}
};

#endif TREE_H
