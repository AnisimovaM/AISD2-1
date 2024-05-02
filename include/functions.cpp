#include <fstream>
#include <iostream>
#include <vector>
#include <complex>
#include <algorithm>
#include <chrono>
#include <random>
#include <functional>

using namespace std;

namespace tree {

	template<typename T>
	struct Node {

		T _value;
		Node<T>* _left;
		Node<T>* _right;
		

		Node(T number) : _value(number), _left(nullptr), _right(nullptr) {}
		Node(T number, Node* ref1, Node* ref2) : _value(number), _left(ref1), _right(ref2){}

	};

	template<typename T>
	class Set {
	private:

		Node<T>* _root;

		Node<T>* copying(Node<T>* root) {
			if (root) {
				Node<int>* copied_el = new Node<int>(root->_value);
				copied_el->_left = copying(root->_left);
				copied_el->_right = copying(root->_right);
				return copied_el;
			}
			return nullptr;
		}

		bool adding_element(Node<T>*& root, T val) {
			if (!root) {
				root = new Node(val);
				return true;
			}
			if (val < root->_value) return adding_element(root->_left, val);
			else if (val > root->_value) return adding_element(root->_right, val);
			return false;
		}

		bool element_presence(Node<T>*& root, T val) {
			if (!root) {
				return false;
			}
			if (val < root->_value) return element_presence(root->_left, val);
			else if (val > root->_value) return element_presence(root->_right, val);
			return true;
		}

		bool delete_element(Node<T>*& root, T val) {
			if (!root) {
				return false;
			}
			if (val < root->_value) return delete_element(root->_left, val);
			else if (val > root->_value) return delete_element(root->_right, val);
			else {
				if (!root->_left) {
					Node<T>* node = root->_right;
					delete root;
					root = node;
				}
				else if (!root->_right) {
					Node<T>* node = root->_left;
					delete root;
					root = node;
				}
				else if (!root->_right && !root->_left) {
					delete root;
				}
				else {
					Node<T>* node = root->_left;
					while (node->_right) {
						node = node->_right;
					}
					root->_value = node->_value;
					delete_element(root->_left, node->_value);
				}
				return true;
			}
		}

		void deletion(Node<T>* root) {
			if (root) {
				deletion(root->_left);
				deletion(root->_right);
				delete root;
			}
			return;
		}

		void print(Node<T>* node) {
			if (!node) {
				return;
			}
			print(node->_left);
			cout << node->_value << " ";
			print(node->_right);
		}

	public:

		Set() {
			_root = nullptr;
		}

		Set(T value) {
			_root = new Node<T>(value);
		}

		Set(Node<T>* node) {
			_root = new Node<T>(node->_value, node->_left, node->_right);
		}

		Set(const Set<T>& other) {
			_root = copying(other._root);
		}

		

		Set<T>& operator=(const Set<T>& other) {
			if (this != &other) {
				deletion(_root);
				_root = copying(other._root);
			}
			return *this;
		}

		Node<T>* get_root() const {
			return _root;
		}

		bool erase(T value) {
			return delete_element(_root, value);
		}

		bool contain(T value) {
			return element_presence(_root, value);
		}

		bool insert(T value) {
			return adding_element(_root, value);
		}

		void print() {
			if (_root) {
				print(_root);
			}
			cout << endl;
		}

		~Set() {
			deletion(_root);
		}

	};

	

	