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

	std::vector<Container*> items;
	std::vector<Node*> children;

	void destroy(Container* container) {

	}

public:
	Node() {
		items.reserve(KEY_MAX+1);
		children.reserve(KEY_MAX+2);
	}

	Node* insert(Data& data, Node* parent=nullptr, int index=0) {
		for (int i = 0; i < items.size(); i++) {
			if (data == items[i]->data) {
				items[i]->data++;
				return this;
			}
			else if (data < items[i]->data) {
				if (children.size() == 0) { // is a leaf node
					items.insert(items.begin() + i, new Container(data));
					goto FOR_END;
				}
				else {
					children[i]->insert(data, this, i);
					goto FOR_END;
				}
			}
		}

		if (children.size() == 0) {
			items.push_back(new Container(data));
		}
		else {
			children[items.size()]->insert(data, this, items.size());
		}

		FOR_END:;

		if (items.size() <= KEY_MAX) {
			return this;
		}

		int split_index = items.size() / 2;
		Node* right = new Node();
		for (int i = split_index + 1; i < KEY_MAX; i++) {
			Container* pop_item = items.back();
			Node* pop_child = children.back();
			right->items.insert(right->items.begin(), pop_item);
			right->children.insert(right->children.begin(), pop_child);

			items.pop_back();
			children.pop_back();
		}
		right->children.insert(right->children.begin(), children.back());
		children.pop_back();
		Container* splitter = items.back();
		items.pop_back();

		if (parent) {
			parent->items.insert(parent->items.begin() + index, splitter);
			parent->children.insert(parent->children.begin() + index + 1, right);
			return this;
		}
		else {
			Node* parent_node = new Node();
			parent_node->items.push_back(splitter);
			parent_node->children.push_back(this);
			parent_node->children.push_back(right);
			return parent_node;
		}
	}

	void remove(Data& data) {
		for (int i = 0; i < items.size(); i++) {
			if (items[i]->data == data) {
				items[i]->count--;
				if (items[i]->count <= 0) {

				}
			}
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