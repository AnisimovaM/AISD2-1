#include "functions.cpp"
#include <gtest/gtest.h>
#include <iostream>



using namespace tree;
using namespace std;

TEST(CreatedSet, Copying1) {
	Node<int>* test1 = new Node<int>(1);
	Node<int>* test2 = new Node<int>(4);
	Node<int>* test_res = new Node<int>(2, test1, test2);
	Set<int> a(test_res);
	Set<int> b(1);
	b = a;
	b.print();
}

TEST(CreatedSet, CopyConstructor) {
	Node<int>* test1 = new Node<int>(1);
	Node<int>* test2 = new Node<int>(4);
	Node<int>* test_res = new Node<int>(2, test1, test2);
	Set<int> a(test_res);
	Set<int> b(a);
	b.print();
}
TEST(CreatedSet, InsertElement1) {
	Node<int>* test1 = new Node<int>(1);
	Node<int>* test2 = new Node<int>(4);
	Node<int>* test_res = new Node<int>(2, test1, test2);
	Set<int> a(test_res);
	a.insert(5);
	a.print();
}
TEST(CreatedSet, InsertElement2) {
	Node<int>* test1 = new Node<int>(1);
	Node<int>* test2 = new Node<int>(4);
	Node<int>* test_res = new Node<int>(2, test1, test2);
	Set<int> a(test_res);
	a.insert(3);
	a.print();
}
TEST(CreatedSet, InsertElement3) {
	Node<int>* test1 = new Node<int>(1);
	Node<int>* test2 = new Node<int>(4);
	Node<int>* test_res = new Node<int>(2, test1, test2);
	Set<int> a(test_res);
	a.insert(0);
	a.print();
}
TEST(CreatedSet, ContainElement) {
	Node<int>* test1 = new Node<int>(1);
	Node<int>* test2 = new Node<int>(4);
	Node<int>* test_res = new Node<int>(2, test1, test2);
	Set<int> a(test_res);
	a.insert(0);
	if (a.contain(0)) {
		cout << "this set contain 0." << endl;
	}
	else cout << "this set is not contain 0." << endl;
}
TEST(CreatedSet, NotContainElement) {
	Node<int>* test1 = new Node<int>(1);
	Node<int>* test2 = new Node<int>(4);
	Node<int>* test_res = new Node<int>(2, test1, test2);
	Set<int> a(test_res);
	a.insert(0);
	if (a.contain(5)) {
		cout << "this set contain 5." << endl;
	}
	else cout << "this set is not contain 5." << endl;
}
TEST(CreatedSet, EraseElement1) {
	Set<int> a(1);
	a.insert(0);
	a.insert(5);
	a.insert(3);
	a.insert(2);
	a.insert(4);
	a.insert(6);
	a.print();
	a.erase(5);
	a.print();
}
TEST(CreatedSet, EraseElement2) {
	Set<int> a(1);
	a.insert(0);
	a.insert(5);
	a.insert(3);
	a.print();
	a.erase(5);
	a.print();
	a.erase(3);
	a.print();
	a.erase(0);
	a.print();
}
TEST(Logic_operations, EraseTime) {
	Set<int> test_set_1(1);
	test_set_1.insert(2);
	test_set_1.insert(3);
	test_set_1.insert(4);
	Set<int> test_set_2(4);
	test_set_2.insert(5);
	test_set_2.insert(6);
	test_set_2.insert(7);
	

	Set<int> result = test_set_1.logic_or(test_set_2);
	result.print();
	Set<int> resultx = test_set_1.logic_xor(test_set_2);
	resultx.print();
	
}
TEST(ComparisonOfVectorAndSet, FillTime) {
	int number = 1000;
	cout << number << " " << "Vector time: " << vector_fill_time(number, 100) << endl;
	cout << number << " " << "Set time : " << set_fill_time(number, 100) << endl;
	number = 10000;
	cout << number << " " << "Vector time: " << vector_fill_time(number, 100) << endl;
	cout << number << " " << "Set time : " << set_fill_time(number, 100) << endl;
	number = 100000;
	cout << number << " " << "Vector time: " << vector_fill_time(number, 100) << endl;
	cout << number << " " << "Set time : " << set_fill_time(number, 100) << endl;
}
TEST(ComparisonOfVectorAndSet, ContainTime) {
	int number = 1000;
	cout << number << " " << "Vector time : " << vector_contain_element_time(number, 1000) << endl;
	cout << number << " " << "Set time : " << set_contain_element_time(number, 1000) << endl;
	number = 10000;
	cout << number << " " << "Vector time : " << vector_contain_element_time(number, 1000) << endl;
	cout << number << " " << "Set time : " << set_contain_element_time(number, 1000) << endl;
	number = 100000;
	cout << number << " " << "Vector time : " << vector_contain_element_time(number, 1000) << endl;
	cout << number << " " << "Set time : " << set_contain_element_time(number, 1000) << endl;
}
TEST(ComparisonOfVectorAndSet, InsertTime) {
	int number = 1000;
	cout << number << " " << "Vector time: " << vector_insert_element_time(number, 1000) << endl;
	cout << number << " " << "Set time: " << set_insert_element_time(number, 1000) << endl;
	number = 10000;
	cout << number << " " << "Vector time: " << vector_insert_element_time(number, 1000) << endl;
	cout << number << " " << "Set time: " << set_insert_element_time(number, 1000) << endl;
	number = 100000;
	cout << number << " " << "Vector time: " << vector_insert_element_time(number, 1000) << endl;
	cout << number << " " << "Set time: " << set_insert_element_time(number, 1000) << endl;
}
TEST(ComparisonOfVectorAndSet, EraseTime) {
	int number = 1000;
	cout << number << " " << "Vector time: " << vector_erase_element_time(number, 1000) << endl;
	cout << number << " " << "Set time: " << set_erase_element_time(number, 1000) << endl;
	number = 10000;
	cout << number << " " << "Vector time: " << vector_erase_element_time(number, 1000) << endl;
	cout << number << " " << "Set time: " << set_erase_element_time(number, 1000) << endl;
	number = 100000;
	cout << number << " " << "Vector time: " << vector_erase_element_time(number, 1000) << endl;
	cout << number << " " << "Set time: " << set_erase_element_time(number, 1000) << endl;
}