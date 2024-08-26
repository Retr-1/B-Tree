#include <vector>
#include <tuple>

template <unsigned KEY_MAX, typename Data>
class Node {
	static const unsigned KEY_MIN = KEY_MAX / 2;

	struct Container {
		Data data;
		int count = 0;

		Container(Data& data) {
			this->data = data;
		}
	};

	std::vector<Container> items;
	std::vector<Node> children;

	void split_into_parent(Node* parent, int index) {
		int split_index = items.size() / 2;
		Node right;
		for (int i = split_index + 1; i < KEY_MAX; i++) {
			Container& pop = items.back();
			right.items.push_back(pop);
			items.pop_back();
		}

		if (parent) {
			parent->items.insert(parent->items.begin() + index, items[split_index]);
			parent->children.insert(parent->children.begin() + index + 1, right);
		}
		else {
			Node parent_node;
			parent_node.items.push_back(items[split_index]);
			parent_node.children.push_back(*this);
			parent_node.children.push_back(right);
		}
	}

public:
	Node() {
		items.reserve(KEY_MAX);
		children.reserve(KEY_MAX+1);
	}

	void insert(Data& data, Node* parent=nullptr, int index=0) {
		for (int i = 0; i < items.size(); i++) {
			if (data == items[i].data) {
				items[i].data++;
				return;
			}
			else if (data < items[i].data) {
				if (children.size() == 0) { // is a leaf node
					items.insert(items.begin() + i, Container(data));
					goto FOR_END;
				}
				else {
					children[i].insert(data);
					goto FOR_END;
				}
			}
		}

		if (children.size() == 0) {
			items.push_back(Container(data));
		}
		else {
			children[KEY_MAX + 1].insert(data);
		}

		FOR_END:;
		if (items.size() > KEY_MAX) {
			split_into_parent(parent, index);
		}
	}
};


template <unsigned KEY_MAX, typename Data>
class BTree {
	struct DataNode {
		Data data;
		int count = 0;
	};

	struct Node {
		BTree* pointers[KEY_MAX];
		DataNode values[KEY_MAX];
	};

	unsigned KEY_MIN = KEY_MAX / 2;


public:
	void insert() {

	}

	void remove() {

	}
};


int main() {
	return 0;
}