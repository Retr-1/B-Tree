#include <vector>
#include <tuple>

template <unsigned KEY_MAX, typename Data>
class Node {
	static const unsigned KEY_MIN = KEY_MAX / 2;

	struct Container {
		Data data;
		int count = 0;

		Container(const Data& data) {
			this->data = data;
		}
	};

	std::vector<Container*> items;
	std::vector<Node*> children;

	//void split_node() {

	//}

	void destroy(int i, Node* parent, int p_index) {
		if (i < children.size()) {
			if (i+1 < children.size() && children[i + 1]->items.size() > KEY_MIN) {
				items[i] = children[i + 1]->items[0];
				children[i + 1]->destroy(0, this, i+1);
			}
			else {
				items[i] = children[i]->items.back();
				children[i]->destroy(children[i]->items.size() - 1, this, i);
			}
		}
		else {
			items.erase(items.begin() + i);
		}
		balance(parent, p_index);
	}

	void balance(Node* parent, int index) {
		if (items.size() >= KEY_MIN) {
			return;
		}

		if (parent == nullptr) {
			return;
		}

		// Stealing node from sibling

		if (index > 0) {
			auto& left_sibling = parent->children[index - 1];
			if (left_sibling->items.size() > KEY_MIN) {
				auto& item = left_sibling->items.back();
				std::swap(item, parent->items[index]);
				items.insert(items.begin(), item);
				return;
			}
		}

		if (index + 1 < parent->children.size()) {
			auto& right_sibling = parent->children[index + 1];
			if (right_sibling->items.size() > KEY_MIN) {
				auto& item = right_sibling->items[0];
				std::swap(item, parent->items[index]);
				items.push_back(item);
				return;
			}
		}

		// Merging sibling

		if (index > 0) {
			Node* left_sibling = parent->children[index - 1];
			Container* sep = parent->items[index - 1];
			parent->items.erase(parent->items.begin() + (index - 1));
			parent->children.erase(parent->children.begin() + (index - 1));
			items.insert(items.begin(), sep);
			for (int i = left_sibling->items.size() - 1; i >= 0; i--) {
				items.insert(items.begin(), left_sibling->items[i]);
			}
			for (int i = left_sibling->children.size() - 1; i >= 0; i--) {
				children.push_back(left_sibling->children[i]);
			}
			delete left_sibling;
			return;
		}

		if (index < parent->items.size()) {
			Node* right_sibling = parent->children[index + 1];
			Container* sep = parent->items[index];
			parent->items.erase(parent->items.begin() + index);
			parent->children.erase(parent->children.begin() + (index + 1));
			items.push_back(sep);
			for (int i = 0; i < right_sibling->items.size(); i++) {
				items.push_back(right_sibling->items[i]);
			}
			for (int i = 0; i < right_sibling->children.size(); i++) {
				children.push_back(right_sibling->children[i]);
			}
			delete right_sibling;
			return;
		}
		
	}

public:
	Node() {
		items.reserve(KEY_MAX+1);
		children.reserve(KEY_MAX+2);
	}

	Node* insert(const Data& data, Node* parent=nullptr, int index=0) {
		for (int i = 0; i < items.size(); i++) {
			if (data == items[i]->data) {
				items[i]->data++;
				return this;
			}
			else if (data < items[i]->data) {
				if (children.size() == 0) { // is a leaf node
					items.insert(items.begin() + i, new Container(data));
					goto FOR_ELSE_END;
				}
				else {
					children[i]->insert(data, this, i);
					goto FOR_ELSE_END;
				}
			}
		}

		if (children.size() == 0) {
			items.push_back(new Container(data));
		}
		else {
			children[items.size()]->insert(data, this, items.size());
		}

		FOR_ELSE_END:;

		if (items.size() <= KEY_MAX) {
			return this;
		}
		
		// Splitting node into 2

		Node* right = new Node();

		int n = items.size();
		for (int i = 0; i < n/2; i++) {
			Container* pop_item = items.back();
			right->items.insert(right->items.begin(), pop_item);
			items.pop_back();
		}

		n = children.size();
		for (int i = 0; i < n/2; i++) {
			Node* pop_child = children.back();
			right->children.insert(right->children.begin(), pop_child);
			children.pop_back();
		}

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

	Node* remove(const Data& data, Node* parent=nullptr, int index=0) {
		for (int i = 0; i < items.size(); i++) {
			if (items[i]->data == data) {
				items[i]->count--;
				if (items[i]->count <= 0) {
					delete items[i];
					destroy(i, parent, index);
				}
				goto FOR_ELSE_END;
			}
			else if (data < items[i]->data) {
				if (i < children.size()) {
					children[i]->remove(data, this, i);
					balance(parent, index);
				}
				goto FOR_ELSE_END;
			}
		}

		if (children.size() > 0) {
			children.back()->remove(data, this, items.size());
			balance(parent, index);
		}

		FOR_ELSE_END:;

		if (children.size() == 1) {
			return children[0];
		}
		return this;
	}
};


template <unsigned KEY_MAX, typename Data>
class BTree {
	Node<KEY_MAX,Data>* head = new Node<KEY_MAX, Data>();
public:
	void insert(const Data& data) {
		head = head->insert(data);
	}

	void remove(const Data& data) {
		head = head->remove(data);
	}
};

// TODO: Put KEY_MIN into template and set KEY_MAX = 2*KEY_MIN, so that KEY_MAX is always even

int main() {
	BTree<4, int> btree;

	btree.insert(10);
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
	for (int i = 100; i < 200; i++) {
		btree.insert(i);
	}
	btree.insert(69);

	return 0;
}