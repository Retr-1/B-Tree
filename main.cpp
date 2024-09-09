#include <iostream>
#include "btree.h"


int main() {
	BTree<4, int> btree;

	btree.insert(10);
	btree.remove(10);
	btree.remove(420);
	btree.insert(20);
	btree.insert(20);
	btree.insert(30);
	btree.insert(40);
	btree.insert(50);
	btree.insert(60);
	btree.insert(11);
	btree.insert(12);
	btree.insert(15);
	btree.insert(14);
	btree.remove(20);
	btree.remove(20);
	btree.remove(12);
	for (int i = 100; i < 200; i++) {
		btree.insert(i);
	}
	btree.insert(69);
	std::cout << btree.get(20)<<'\n';
	btree.remove(20);
	std::cout << btree.get(20)<<'\n';
	btree.remove(20);


	return 0;
}