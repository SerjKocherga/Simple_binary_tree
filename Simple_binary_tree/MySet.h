#pragma once

template <class T>
class MySet
{
public:

	MySet() { root = 0; }

	void erase(const T &val) {

		if (find(val) == false) return;
		node *&reference = insert_find(root, val);
		if (reference->pLeft == 0) {

			node* temp = reference->pRight;
			delete reference;
			reference = temp;
		}
		else if (reference->pRight == 0) {

			node* temp = reference->pLeft;
			delete reference;
			reference = temp;
		}
		else {

			node* t = reference->pRight;
			while (t->pLeft != 0) t = t->pLeft;
			t->pLeft = reference->pLeft;
			node* temp = reference->pRight;
			delete reference;
			reference = temp;
		}
	}

	void insert(const T &val) {

		if (find(val) == true) return;
		if (root == 0) { root = new node(val, 0, 0); }
		insert_find(root, val) = new node(val, 0, 0);
	}
	bool find(const T &val) {

		node* temp = find_ptr(root, val);
		return temp != 0 ? true : false;
	}

	~MySet() { destructor(root); }

private:

	struct node {
	
		node(const T &val, node* left, node* right) : data(val), pLeft(left), pRight(right) {}
	
		T data;
		node* pLeft;
		node* pRight;
	};

	node* find_ptr(node *root_subtree, const T &val) {

		if (root_subtree == 0) return 0;
		node* current = root_subtree;
			if (!(val < current->data) && !(val > current->data)) return current;
			if (val < current->data) return find_ptr(current->pLeft, val);
			else return find_ptr(current->pRight, val);
	}

	node*& insert_find(node *&root_subtree, const T &val) {

		if (val < root_subtree->data) {

			if (root_subtree->pLeft == 0) return root_subtree->pLeft;
			else return insert_find(root_subtree->pLeft, val);
		}
		if (val > root_subtree->data) {

			if (root_subtree->pRight == 0) return root_subtree->pRight;
			else return insert_find(root_subtree->pRight, val);
		}
		return root_subtree;
	}
	
	void destructor(node* root_subtree) {

		if (root_subtree == 0) return;
		destructor(root_subtree->pLeft);
		destructor(root_subtree->pRight);
		delete root_subtree;
	}

	node* root;
};

