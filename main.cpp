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

node* findright(node*& ptr) {
	if (ptr->right == NULL) {
		node* tmp = ptr;
		node* s = new node;
		s->id = tmp->id;
		s->weight = tmp->weight;
		ptr = ptr->left;
		free(tmp);
		return s;
	}
	else return findright(ptr->right);
}
void del(node*& ptr, int val) {
	if (val < ptr->id) {
		del(ptr->left, val);
	}
	else if (val > ptr->id) del(ptr->right, val);
	else {
		if (ptr->left == NULL) {
			node* tmp = ptr;
			ptr = ptr->right;
			free(tmp);
		}
		else {
			if (ptr->right == NULL) ptr = ptr->left;
			else {
				node* tmp = findright(ptr->left);
				ptr->id = tmp->id;
				ptr->weight = tmp->weight;
				free(tmp);
			}
		}
	}
}
void push(node*& ptr, int val, int weight) {
	if (ptr == NULL) {
		ptr = new node;
		ptr->id = val;
		ptr->left = NULL;
		ptr->right = NULL;
		ptr->weight = weight;
	}
	else if (val < ptr->id) {
		if (ptr->left == NULL) {
			node* tmp = new node;
			tmp->id = val;
			tmp->left = NULL;
			tmp->right = NULL;
			tmp->weight = weight;
			ptr->left = tmp;
		}
		else push(ptr->left, val, weight);
	}
	else {
		if (ptr->right == NULL) {
			node* tmp = new node;
			tmp->id = val;
			tmp->left = NULL;
			tmp->right = NULL;
			tmp->weight = weight;
			ptr->right = tmp;
		}
		else push(ptr->right, val, weight);
	}
}
void generate(node*& root) {
	srand(time(0));
	for (int i = 0; i < 10; i++) {
		push(root, rand() % 10, pow(-rand()%2, rand()));
	}
}
void menu() {
	std::cout << "1 - Добавить элемент"<< std::endl;
	std::cout << "2 - Удалить элемент"<<std::endl;
	std::cout << "3 - Индивидуальное задание - Найти 2 четных элемента с положительным весом" << std::endl;
	std::cout << "4 - Показать дерево" << std::endl;
	std::cout << "5 - Показать дерево с весами" << std::endl;
	std::cout << "0 - Выход" << std::endl;
}
int indiv(node* ptr) {
	int n = 0;
	if (ptr != NULL) {
		n+=indiv(ptr->left);
		if (n >= 2) return n;
		if (ptr->id % 2 == 0 && ptr->weight > 0) {
			n++;
			std::cout << ptr->id << "(" << ptr->weight << ") ";
			if (n >= 2) return n;
		}
		n += indiv(ptr->right);
		if (n >= 2) return n;
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
	int t,s;
	while (true) {
		menu();
		int i;
		std::cin >> i;
		switch (i) {
		case(1):
			std::cout << "Введите значение:" << std::endl;
			
			std::cin >> t;
			std::cout << "Введите вес:" << std::endl;

			std::cin >> s;

			push(root, t, s);
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