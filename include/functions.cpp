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

	

	size_t lcg() {
		static size_t x = 0;
		x = (1021 * x + 24631) % 116640;
		return x;
	}

	

	uint64_t time_now() {
		using namespace std::chrono;
		return duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();
	}

	double set_fill_time(int numbers_for_filling, int attempts) {
		double res = 0;
		for (int attempt = 0; attempt < attempts; attempt++) {
			Set<int> new_set;
			int current_count_of_elements = 0;
			uint64_t begin = time_now();
			while (current_count_of_elements != numbers_for_filling) {
				if (new_set.insert(lcg())) {
					current_count_of_elements++;
				}
			}
			uint64_t end = time_now();
			res += (end - begin);
		}
		return res / attempts;
	}

	double vector_fill_time(int numbers_for_filling, int attempts) {
		double res = 0;
		for (int attempt = 0; attempt < attempts; attempt++) {
			vector<int> new_vector;
			int current_count_of_elements = 0;
			uint64_t begin = time_now();
			while (current_count_of_elements != numbers_for_filling) {
				new_vector.push_back(lcg());
				current_count_of_elements++;
			}
			uint64_t end = time_now();
			res += (end - begin);
		}
		return res / attempts;
	}

	double set_contain_element_time(int numbers_for_filling, int attempts) {
		double res = 0;
		for (int attempt = 0; attempt < attempts; attempt++) {
			Set<int> new_set;
			int current_count_of_elements = 0;
			while (current_count_of_elements != numbers_for_filling) {
				if (new_set.insert(lcg())) {
					current_count_of_elements++;
				}
			}
			uint64_t begin = time_now();
			new_set.contain(lcg());
			uint64_t end = time_now();
			res += (end - begin);
		}
		return res / attempts;
	}

	double vector_contain_element_time(int numbers_for_filling, int attempts) {
		double res = 0;
		for (int attempt = 0; attempt < attempts; attempt++) {
			vector<int> new_vector;
			int current_count_of_elements = 0;
			while (current_count_of_elements != numbers_for_filling) {
				new_vector.push_back(lcg());
				current_count_of_elements++;
			}
			uint64_t begin = time_now();
			size_t element = lcg();
			for (int i = 0; i < new_vector.size(); i++) {
				if (new_vector[i] == element) {
					break;
				}
			}
			uint64_t end = time_now();
			res += (end - begin);
		}
		return res / attempts;
	}

	double set_insert_element_time(int numbers_for_filling, int attempts) {
		double res = 0;
		for (int attempt = 0; attempt < attempts; attempt++) {
			Set<int> new_set;
			int current_count_of_elements = 0;
			while (current_count_of_elements != numbers_for_filling) {
				if (new_set.insert(lcg())) {
					current_count_of_elements++;
				}
			}
			uint64_t begin = time_now();
			new_set.insert(lcg());
			uint64_t end = time_now();
			res += (end - begin);
		}
		return res / attempts;
	}

	double vector_insert_element_time(int numbers_for_filling, int attempts) {
		double res = 0;
		for (int attempt = 0; attempt < attempts; attempt++) {
			vector<int> new_vector;
			int current_count_of_elements = 0;
			while (current_count_of_elements != numbers_for_filling) {
				new_vector.push_back(lcg());
				current_count_of_elements++;
			}
			uint64_t begin = time_now();
			new_vector.push_back(lcg());
			uint64_t end = time_now();
			res += (end - begin);
		}
		return res / attempts;
	}

	double set_erase_element_time(int numbers_for_filling, int attempts) {
		double res = 0;
		for (int attempt = 0; attempt < attempts; attempt++) {
			Set<int> new_set;
			int current_count_of_elements = 0;
			while (current_count_of_elements != numbers_for_filling) {
				if (new_set.insert(lcg())) {
					current_count_of_elements++;
				}
			}
			uint64_t begin = time_now();
			new_set.erase(lcg());
			uint64_t end = time_now();
			res += (end - begin);
		}
		return res / attempts;
	}

	double vector_erase_element_time(int numbers_for_filling, int attempts) {
		double res = 0;
		for (int attempt = 0; attempt < attempts; attempt++) {
			vector<int> new_vector;
			int current_count_of_elements = 0;
			while (current_count_of_elements != numbers_for_filling) {
				new_vector.push_back(lcg());
				current_count_of_elements++;
			}
			uint64_t begin = time_now();
			size_t element = lcg();
			for (int i = 0; i < new_vector.size(); i++) {
				if (new_vector[i] == element) {
					new_vector.erase(new_vector.begin() + i);
					break;
				}
			}
			uint64_t end = time_now();
			res += (end - begin);
		}
		return res / attempts;
	}

	template<typename T>
	Set<T> logic_or(Set<T> left_tree, Set<T> right_tree) {
		Set<T> result;
		std::function<void(Node<T>*)> m_union = [&](Node<T>* node) {
			if (node != nullptr) {
				m_union(node->_left);
				result.insert(node->_value);
				m_union(node->_right);
			}
			};
		m_union(left_tree.get_root());
		m_union(right_tree.get_root());
		return result;
	}
	template<typename T>
	Set<T> logic_xor(Set<T> left_tree, Set<T> right_tree) {
		Set<T> result;
		std::function<void(Node<T>*)> m_union = [&](Node<T>* node) {
			if (node != nullptr) {
				m_union(node->_left);
				if (!(left_tree.contain(node->_value) && right_tree.contain(node->_value))) {
					result.insert(node->_value);
				}
				m_union(node->_right);
			}
			};
		m_union(left_tree.get_root());
		m_union(right_tree.get_root());
		return result;
	}
}