#ifndef TREE_H
#define TREE_H

#include <utility>
#include "TreeNode.h"
#include "tableelement.h"

// ����� "������"
class AVLTree
{
	// ��������� ����
	struct AVLNode
	{
		TableElement data;
		AVLNode* left;
		AVLNode* right;
		int height;

		AVLNode(const TableElement& _data) : data(_data), left(nullptr), right(nullptr), height(1) {}
	};

	AVLNode* root; // ������

// ����� ��� �������� ������ ����
	int getHeight(AVLNode* Node) {
		return (Node == nullptr) ? 0 : Node->height;
	}

	// ����� ��� �������� ������� ����
	int getBalanceFactor(AVLNode* Node) {
		return getHeight(Node->right) - getHeight(Node->left);
	}

	// ����� ��� ��������� ������ ����
	void fixHeight(AVLNode* Node) {
		int left_height = getHeight(Node->left);
		int right_height = getHeight(Node->right);
		Node->height = std::max(left_height, right_height) + 1;
	}

	// ����� ��� �������� ������
	AVLNode* rotateRight(AVLNode* Node) {
		AVLNode* new_root = Node->left;
		Node->left = new_root->right;
		new_root->right = Node;
		fixHeight(Node);
		fixHeight(new_root);
		return new_root;
	}

	// ����� ��� �������� �����
	AVLNode* rotateLeft(AVLNode* Node) {
		AVLNode* new_root = Node->right;
		Node->right = new_root->left;
		new_root->left = Node;
		fixHeight(Node);
		fixHeight(new_root);
		return new_root;
	}

	// ����� ��� ������������ ����
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

	// ���������� � ������
	AVLNode* _add(AVLNode* Node, const TableElement& data)
	{
		// ���� ����, �� �������� ������ ����
		if (Node == nullptr)
			return new AVLNode(data);

		if (data < Node->data)
			Node->left = _add(Node->left, data);
		else if (Node->data < data)
			Node->right = _add(Node->right, data);
		else // ���� ��� ����������
			return Node;

		// ���������� ������ �������� ����
		Node->height = std::max(getHeight(Node->left), getHeight(Node->right)) + 1;

		// �������� ������������ �������� ����
		int balance = getBalanceFactor(Node);

		// ���������, �� ���������� �� ������ ������
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

	// ����� �� ������
	std::pair<AVLNode*, int> _find(AVLNode* Node, const TableElement& key, int count)
	{
		// ���� ������� ���� ��� ����� ����, �� ���������� �������
		if (Node == nullptr || Node->data == key)
			return std::pair<AVLNode*, int>(Node, count + 1);
		// ����� ������� � ����� ��� ������ ���������
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

	// �������� �� ������
	AVLNode* _remove(AVLNode* Node, const TableElement& key)
	{
		// ���� ������� ����, �� ���������� nullptr
		if (Node == nullptr)
			return Node;
		// ����� ������� � ����� ��� ������ ���������
		if (key < Node->data)
			Node->left = _remove(Node->left, key);
		else if (key > Node->data)
			Node->right = _remove(Node->right, key);
		else // ������ ����
		{
			// ���� ���� �� �������� ����� ����
			if (Node->left == nullptr || Node->right == nullptr)
			{
				AVLNode* temp = Node->left ? Node->left : Node->right;

				// ���� ��� �������� ���� �����
				if (temp == nullptr)
				{
					temp = Node;
					Node = nullptr;
				}
				else // ���� ���� �������� ���� �� ����
					*Node = *temp; // ����������� �������� ��������� ���� � ������� ����
				delete temp;
			}
			else // ��� �������� ���� �� �����
			{
				AVLNode* temp = Node->right;
				while (temp->left != nullptr)
					temp = temp->left;

				Node->data = temp->data; // ������ �������� �������� ���� �� �������� �������� ������ ��������� ����
				Node->right = _remove(Node->right, temp->data);
			}
		}
		// ���� � ������ ������� ������ ���� ����, �� ����� ���������� ���
		if (Node == nullptr)
			return Node;

		// ��������� ������ �������� ����
		Node->height = std::max(getHeight(Node->left), getHeight(Node->right)) + 1;

		// �������� ������������ �������� ����
		int balance = getBalanceFactor(Node);

		// ���������, �� ���������� �� ������ ������
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
