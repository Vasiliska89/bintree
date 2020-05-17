#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <iomanip>

struct node {
	int id;
	int weight;
	node* left;
	node* right;
};

void show(node* t, int n) {
	if (t != NULL) {
		show(t->left, n + 1);
		std::cout << std::setw(n * 3) << t->id << std::endl;
		show(t->right, n + 1);
	}
}

int findright(node*& ptr) {
	if (ptr->right == NULL) {
		int t = ptr->id;
		ptr = ptr->left;
		return t;
	}
	else return findright(ptr->right);
}
void del(node*& ptr, int val) {
	if (val < ptr->id) {
		del(ptr->left, val);
	}
	else if (val > ptr->id) del(ptr->right, val);
	else {
		if (ptr->left == NULL) ptr = ptr->right;
		else {
			if (ptr->right == NULL) ptr = ptr->left;
			else {
				int tmp = findright(ptr->left);
				ptr->id = tmp;
			}
		}
	}
}
void push(node*& ptr, int val) {
	if (val < ptr->id) {
		if (ptr->left == NULL) {
			node* tmp = new node;
			tmp->id = val;
			tmp->left = NULL;
			tmp->right = NULL;
			tmp->weight = pow(-rand() % 2, rand());
			ptr->left = tmp;
		}
		else push(ptr->left, val);
	}
	else {
		if (ptr->right == NULL) {
			node* tmp = new node;
			tmp->id = val;
			tmp->left = NULL;
			tmp->right = NULL;
			tmp->weight = pow(-rand() % 2, rand());
			ptr->right = tmp;
		}
		else push(ptr->right, val);
	}
}
void generate(node*& root) {
	srand(time(0));
	node* tmp = new node;
	tmp->id = rand() % 10;
	tmp->left = NULL;
	tmp->right = NULL;
	tmp->weight = pow(-rand() % 2, rand());
	root = tmp;
	for (int i = 1; i < 10; i++) {
		push(root, rand() % 10);
	}
}
void menu() {
	std::cout << "1 - Добавить элемент"<< std::endl;
	std::cout << "2 - Удалить элемент"<<std::endl;
	std::cout << "3 - Индивидуальное задание - Найти не менее 2х четных элементов с положительным весом" << std::endl;
	std::cout << "4 - Показать дерево" << std::endl;
	std::cout << "5 - Показать дерево с весами" << std::endl;
	std::cout << "0 - Выход" << std::endl;
}
int indiv(node* ptr) {
	int n = 0;
	if (ptr != NULL) {
		n+=indiv(ptr->left);
		if (ptr->id % 2 == 0 && ptr->weight > 0) {
			n++;
			std::cout << ptr->id << "(" << ptr->weight << ") ";
		}
		n += indiv(ptr->right);
	}
	return n;
}
void show2(node* t, int n) {
	if (t != NULL) {
		show2(t->left, n + 1);
		std::cout << std::setw(n * 3) << t->id<<"("<<t->weight<<")" << std::endl;
		show2(t->right, n + 1);
	}
}
int main() {

	setlocale(LC_ALL, "Russian");
	node* root = NULL;
	generate(root);
	show(root, 1);
	int t;
	while (true) {
		menu();
		int i;
		std::cin >> i;
		switch (i) {
		case(1):
			std::cout << "Введите значение:" << std::endl;
			
			std::cin >> t;
			push(root, t);
			break;
		case(2):
			std::cout << "Введите значение:" << std::endl;
			std::cin >> t;
			del(root, t);
			break;
		case(3):
			t = indiv(root);
			if (t < 2) std::cout << " Не нашлось!" << std::endl;
			else std::cout << " Нашлось!" << std::endl;
			break;
		case(4):
			show(root, 1);
			break;
		case(5):
			show2(root, 1);
			break;
		case(0):
			return 0;
		}
	}
}