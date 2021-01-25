#include <iostream>
#include <cassert>

#include "RBTree.hpp"

void TestEmpty() {
	std::cout << "Empty tree test: ";
	RBTree<int> tree;

	assert(tree.GetSize() == 0);
	assert(!tree.Find(5));

	std::cout << "OK" << std::endl;
}

void TestInsert() {
	std::cout << "Insert to RBTree test: ";
	RBTree<int> tree;

	tree.Insert(5);
	assert(tree.GetSize() == 1);
	assert(tree.Find(5));
	assert(!tree.Find(10));

	tree.Insert(10);
	tree.Insert(15);
	tree.Insert(2);
	tree.Insert(7);

	assert(tree.GetSize() == 5);
	assert(tree.Find(2));
	assert(tree.Find(5));
	assert(tree.Find(7));
	assert(tree.Find(10));
	assert(tree.Find(15));

	std::cout << "OK" << std::endl;
}

// тест копии-присваивания
void TestCopyAssign() {
	RBTree<int> tree;
	int n = 6;
	int values[] = { 1, 6, 10, 5, -5, 15 };

	for (int i = 0; i < n; i++)
		tree.Insert(values[i]); // вставляем в дерево

	std::cout << "Copy constructor test: ";
	RBTree<int> copy(tree); // копируем дерево

	assert(copy.GetSize() == n);
	for (int i = 0; i < n; i++)
		assert(copy.Find(values[i]));
	std::cout << "OK" << std::endl;

	std::cout << "Assign operator (operator=) test: ";
	RBTree<int> assigned = tree; // выполняем присваивание

	assert(copy.GetSize() == n);
	for (int i = 0; i < n; i++)
		assert(assigned.Find(values[i]));
	std::cout << "OK" << std::endl;
}

void TestRemove() {
	RBTree<int> tree;
	int n = 6;
	int values[] = { 1, 6, 10, 5, -5, 15 };

	for (int i = 0; i < n; i++)
		tree.Insert(values[i]); // вставляем в дерево

	std::cout << "Remove test: ";

	for (int i = 0; i < n; i++) {
		assert(tree.Remove(values[i]));
		assert(tree.GetSize() == n - 1 - i);
	}

	std::cout << "OK" << std::endl;
}

int main() {
	TestEmpty();
	TestInsert();
	TestCopyAssign();
	TestRemove();
}