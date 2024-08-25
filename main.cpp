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

public:
	Node() {
		items.reserve(KEY_MAX);
		children.reserve(KEY_MAX+1);
	}

	std::tuple<Container, Node, Node> insert(Data& data) {
		for (int i = 0; i < items.size(); i++) {
			if (data == items[i].data) {
				items[i].data++;
				return;
			}
			else if (data < items[i].data) {
				if (children.size() == 0) { // is a leaf node
					items.insert(items.begin() + i, Container(data));
				}
				else {
					return children[i].insert(data);
				}
			}
		}

		if (children.size() == 0) {
			items.push_back(Container(data));

			if (items.size() > KEY_MAX) {
				int split = items.size() / 2;
				//Container splitter = items[items.size() / 2];
				Node left;
				for (int i = 0; i < split; i++) {
					left.items.push_back(items[i]);
				}
				Node right;
				for (int i = split; i < KEY_MAX; i++) {
					right.items.push_back(items[i]);
				}
				return std::make_tuple(items[split], left, right);
				
			}
		}
		else {
			children[KEY_MAX + 1].insert(data);
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