
template <unsigned KEY_MAX, typename Data>
class Node {
	static const unsigned KEY_MIN = KEY_MAX / 2;

	struct Container {
		Data data;
		int count = 0;
	};

	Node* pointers[KEY_MAX];
	Container values[KEY_MAX];
	int children = 0;

public:
	void insert(Data& data) {
		for (int i = 0; i < children; i++) {
			if (data < values[i].data) {
				return pointers[i]->insert(data);
			}
			else if (data == values[i].data) {
				values[i].count++;
				return;
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