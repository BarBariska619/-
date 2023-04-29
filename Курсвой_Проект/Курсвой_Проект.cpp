#include <iostream>
#include <string>
#include <random>
#include <fstream>
#include<Windows.h>
#include "Header.h"

using namespace std;
void PrintListDOC(string doc_FIO);


struct DoubleList //описание узла списка
{
	direction data; //информационное поле
	DoubleList* next; //указатель на следующий элемент
	DoubleList* prev; //указатель на предыдущий элемент
	DoubleList* prevFIO; //указатель 1го уровня 
};
DoubleList* head; //указатель на первый элемент списка
DoubleList* tail; //указатель на последний элемент списка


// Хеш-таблица 
/////////////////////////////////////////////////////////////////////////
const int size_1 = 2500;

struct HashNode
{
	bool deleted;
	string key;
	ill value;
};

struct ListNode
{
	string key;
	ListNode* next;
};

string generateKey()//Создание ключа
{
	string result;
	char temp;
	random_device generate;
	for (char i = 0; i < 8; i++)
	{
		temp = generate() % ('9' - '0') + '0';
		result.push_back(temp);
	}
	return result;
}

bool checkKey(string& key) //Проверка на корректность ключа
{
	bool result = true;
	if (key.length() != 8)
		result = false;
	else
	{
		int i = 0;
		while (i < 8)
		{
			if (!(key[i] >= '0' && key[i] <= '9'))
			{
				result = false;
				break;
			}
			i++;
		}
	}
	return result;
}

string getKey() //Ввод ключа
{
	string str;
	cout << ">> Введите регистрационный номер из 8ми цифр: " << endl;
	cin >> str;
	while (!checkKey(str))
	{
		cout << "Ошибка, повторите ввод: ";
		cin.ignore(cin.rdbuf()->in_avail());
		getline(cin, str);
	}
	return str;
}

int mainHash(string key) // хеш функция
{
	int result = 0;
	for (unsigned int i = 0; i < key.length(); i++)
		result += key[i] * key[i];
	return result % size_1;
}

void push(ListNode*& head, string& key)
{
	ListNode* tmp = new ListNode;
	tmp->key = key;
	tmp->next = head;
	head = tmp;
}


HashNode* get(HashNode* table, string key)
{
	HashNode* result = nullptr;
	int position = mainHash(key);
	if (!table[position].deleted && table[position].key == key)
		result = &table[position];
	else
	{
		int hash = mainHash(key);
		int offset = hash;
		while (offset < size_1)
		{
			if (!table[(position + offset) % size_1].deleted && table[(position + offset) % size_1].key == key)
			{
				result = &table[position + offset];
				break;
			}
			offset += hash;
		}
	}

	return result;
}

bool addValue(HashNode* const& table, const std::string& key, ill& value)
{
	bool result = true;
	int position = 0;
	HashNode* tmp = get(table, key);
	if (tmp != nullptr)
		result = false;
	else
	{
		bool check = true;
		if (table[position].deleted)
		{
			table[position].value.set_adress(value.get_adress());
			table[position].value.set_birthday(value.get_birthday());
			table[position].value.set_fio(value.get_fio());
			table[position].value.set_number(value.get_number());
			table[position].value.set_place_of_work_or_study(value.get_place_of_work_or_study());
			table[position].deleted = false;
			table[position].key = key;
		}
		else
		{
			for (position; position < size_1; position++)
			{
				if (table[position].deleted)
				{
					table[position].value.set_adress(value.get_adress());
					table[position].value.set_birthday(value.get_birthday());
					table[position].value.set_fio(value.get_fio());
					table[position].value.set_number(value.get_number());
					table[position].value.set_place_of_work_or_study(value.get_place_of_work_or_study());
					table[position].deleted = false;
					table[position].key = key;
					break;
				}
			}
		}
	}
	return result;
}

void clear(HashNode* table)
{
	for (uint32_t i = 0; i < size_1; i++)
		table[i].deleted = true;
}

void clear(ListNode*& head)
{
	while (head != nullptr)
	{
		ListNode* tmp = head;
		head = head->next;
		delete tmp;
	}
}

bool remove(HashNode* const& table, string key)
{
	bool result = false;
	HashNode* tmp = get(table, key);
	if (tmp != nullptr)
	{
		tmp->deleted = true;
		result = true;
	}
	DoubleList* z = head;
	int position = 1;
	ill temp_ill = z->data.get_ill_dir();
	string temp_number = temp_ill.get_number();
	while (temp_number != key)
	{
		position++;
		z = z->next;
		temp_ill = z->data.get_ill_dir();
		temp_number = temp_ill.get_number();
	}
	if (head == NULL) { cout << "\nСписок пуст\n\n"; return 0; }
	if (head->next == NULL)
	{
		delete head;
		head = NULL;
	}
	else if (position == 1)
	{
		head->next->prev = NULL;
		head = head->next;
	}
	else
	{
		DoubleList* a = head;
		if (z->next != NULL)
		{
			for (int i = position; i > 1; i--) a = a->next;
			if (a == head) head = a->next;
			a->prev->next = a->next;
			a->next->prev = a->prev;
			delete a;
		}
		else
		{
			int i = 1;
			while (i != position)
			{
				a = a->next;
				i++;
			}
			a->prev->next = NULL;
			delete a;
		}
	}
	return result;
}

ListNode* find(ListNode*& head, string value)
{
	ListNode* result = nullptr;
	if (head != nullptr)
	{
		ListNode* tmp = head;
		while (tmp != nullptr)
		{
			if (tmp->key == value)
			{
				result = tmp;
				break;
			}
			tmp = tmp->next;
		}
	}
	return result;
}
/////////////////////////////////////////////////////////////////////////////////////
//Доктора

struct TreeNode
{
	doctor data;; // Данные
	int height; // Высота
	TreeNode* left; // Указатель на левого потомка
	TreeNode* right; // Указатель на правого потомка
	TreeNode(doctor value) { data = value; left = right = 0; height = 1; } // Конструктор нового узла
};

#pragma region balance
// Обертка для поля height
int height(TreeNode* p)
{
	if (p != NULL)
		return p->height;
	else
		return 0;
}

// Вычисляет balance factor заданного узла
int bfactor(TreeNode* p)
{
	return height(p->right) - height(p->left);
}

// Восстанавливает корректное значение поля height заданного узла
void fixheight(TreeNode* p)
{
	int h_left = height(p->left);
	int h_right = height(p->right);
	if (h_left > h_right)
		p->height = h_left + 1;
	else
		p->height = h_right + 1;
}

// Реализует правый поворот вокруг p
TreeNode* rotateRight(TreeNode* p)
{
	TreeNode* q = p->left;
	p->left = q->right;
	q->right = p;
	fixheight(p);
	fixheight(q);
	return q;
}

// Реализует левый поворот вокруг q
TreeNode* rotateLeft(TreeNode* q) //передаем корень
{
	TreeNode* p = q->right; //создаем указатель на новый корень (новым корнем будет правое поддерево)
	q->right = p->left; //у старого корня правое поддерево становится левым поддеревом нового корня
	p->left = q; //старый корень
	fixheight(q);
	fixheight(p);
	return p; //возвращаем указатель на новый корень
}

// Балансировка узла
TreeNode* balance(TreeNode* p)
{
	fixheight(p);
	if (bfactor(p) == 2)
	{
		if (bfactor(p->right) < 0)
			p->right = rotateRight(p->right);
		return rotateLeft(p);
	}

	if (bfactor(p) == -2)
	{
		if (bfactor(p->left) > 0)
			p->left = rotateLeft(p->left);
		return rotateRight(p);
	}

	return p; // балансировка не нужна
}
#pragma endregion

#pragma region additon
// Поиск узла при добавлении
void search(TreeNode* root, doctor value, bool& found)
{
	// Если дерево пусто
	if (root == NULL)
		return;
	// Если элемент найдет
	else if (root->data.get_FIO_doctor() == value.get_FIO_doctor())
	{
		found = true;
		return;
	}

	if (value.get_FIO_doctor() < root->data.get_FIO_doctor())
		search(root->left, value, found);
	else
		search(root->right, value, found);
	return;
}

// Вставка value в дерево с корнем p
TreeNode* add(TreeNode* p, doctor value)
{
	if (!p)
		return new TreeNode(value);

	if (value.get_FIO_doctor() < p->data.get_FIO_doctor())
		p->left = add(p->left, value);

	else
		p->right = add(p->right, value);

	return balance(p);
}
#pragma endregion

#pragma region delete
// Поиск узла с минимальным ключом в дереве p
TreeNode* findMin(TreeNode* p)
{
	if (p->left)
		return findMin(p->left);
	else
		return p;
}

// Удаление узла с минимальным значением
TreeNode* deleteMin(TreeNode* p)
{
	if (p->left == 0)
		return p->right;
	p->left = deleteMin(p->left);
	return balance(p);
}

// Удаление искомого узла
TreeNode* deleteNode(TreeNode* p, doctor value)
{
	if (!p) return 0;
	if (value.get_FIO_doctor() < p->data.get_FIO_doctor())
		p->left = deleteNode(p->left, value);
	else if (value.get_FIO_doctor() > p->data.get_FIO_doctor())
		p->right = deleteNode(p->right, value);
	else // value == p->data
	{
		TreeNode* q = p->left;
		TreeNode* r = p->right;
		delete p;
		if (!r) return q;
		TreeNode* min = findMin(r);
		min->right = deleteMin(r);
		min->left = q;
		return balance(min);
	}
	return balance(p);
}
#pragma endregion

#pragma region print
//Вывод списка в симметричном порядке обхода
void printSymmetry(TreeNode* root)
{
	if (root == NULL) return;
	printSymmetry(root->left);
	/*cout << "Фамилия врача: ";
	cout << root->data.FIO << endl;
	cout << "Номер кабинета: ";
	cout << root->data.kab_number << endl;
	cout << "Должность: ";
	cout << root->data.post << endl;
	cout << "Время работы: ";
	cout << root->data.time_work << endl;*/
	root->data.Print();
	printSymmetry(root->right);
}
#pragma endregion

//Поиск по фрагменту должности
bool search1(TreeNode* root, doctor value, int& count)
{
	string temp_post_root = root->data.get_post();
	int s1 = temp_post_root.length();
	string temp_post_value = value.get_post();
	int s2 = temp_post_value.length();
	for (int i = 0; i < s1 - s2 + 1; i++)
	{
		for (int j = 0; j < s2; j++)
		{
			if (temp_post_value[j] != temp_post_root[i + j])
				break;
			else if (j == s2 - 1)
			{
				count++;
				return true;
			}
		}
	}
	return false;
}

// Поиск врача по должности
int search_post(TreeNode* root, doctor value, int& count)
{
	if (root == NULL)
	{
		return 0;
	}
	search_post(root->left, value, count);
	if (search1(root, value, count))
	{
		/*cout << "Фамилия врача: ";
		cout << root->data.FIO << endl;
		cout << "Номер кабинета: ";
		cout << root->data.kab_number << endl;
		cout << "Должность: ";
		cout << root->data.post << endl;
		cout << "Время работы: ";
		cout << root->data.time_work << endl;*/
		root->data.Print();
	}
	search_post(root->right, value, count);
}

// Поиск врача по фамилии
int search_FIO(TreeNode* root, doctor value, int& count)
{
	if (root == NULL)
	{
		return 0;
	}
	search_FIO(root->left, value, count);
	if (root->data.get_FIO_doctor() == value.get_FIO_doctor())
	{
		/*cout << "Фамилия врача: ";
		cout << root->data.FIO << endl;
		cout << "Номер кабинета: ";
		cout << root->data.kab_number << endl;
		cout << "Должность: ";
		cout << root->data.post << endl;
		cout << "Время работы: ";
		cout << root->data.time_work << endl;*/
		root->data.Print();
	}
	search_FIO(root->right, value, count);
}

// Вывод дерева на экран
void printTree(TreeNode* p, int level)
{
	TreeNode* pr = p;
	if (pr)
	{
		printTree(pr->right, level + 1);
		for (int i = 0; i < level; i++) cout << " ";
		/*cout << "Фамилия врача: ";
		cout << pr->data.FIO << endl;
		cout << "Номер кабинета: ";
		cout << pr->data.kab_number << endl;
		cout << "Должность: ";
		cout << pr->data.post << endl;
		cout << "Время работы: ";
		cout << pr->data.time_work << endl;*/
		pr->data.get_FIO_doctor();
		printTree(pr->left, level + 1);
	}
}




/////////////////////////////////////////////////////////////////////////////////////
//Направления

//**********************ДОБАВЛЕНИЕ ЭЛЕМЕНТА**********************
int AddList(direction x)
{
	ill temp_ill_x = x.get_ill_dir();
	doctor temp_doctor;
	DoubleList* node = new DoubleList; //создание нового элемента
	ill temp_ill_node = node->data.get_ill_dir();
	node->next = NULL;//указываем, что изначально по следующему адресу пусто
	//node->data.ill_dir.set_number(x.ill_dir.get_number());//присваиваем значение
	//node->data.ill_dir.set_fio(x.ill_dir.get_fio());//присваиваем значение
	node->data.set_ill_dir(x.get_ill_dir());
	//node->data.doc_dir.set_FIO_doctor(x.doc_dir.get_FIO_doctor());//присваиваем значение
	node->data.set_doc_dir(x.get_doc_dir());
	node->data.set_Data_dir(x.get_Data_dir());//присваиваем значение
	node->data.set_Time_Dir(x.get_Time_Dir());//присваиваем значение

	DoubleList* node1 = new DoubleList;
	node1 = head;//временный адрес первого элемента
	while (node1 != NULL)
	{
		if ((node1->data.get_Data_dir() == x.get_Data_dir()) && (node1->data.get_Time_Dir() == x.get_Time_Dir()))
		{
			cout << "На это время уже есть запись!";
			system("pause");
			return 0;
		}
		node1 = node1->next;//смена адреса на следующий элемент
	}
	if (head != NULL) //если список не пуст
	{
		node->prev = tail; //указываем адрес на предыдущий элемент 
		tail->next = node; //указываем адрес следующего за хвостом элемента
		tail = node; //меняем адрес хвоста
		node->prevFIO = NULL;
	}
	else //если список пустой
	{
		node->prev = NULL; //предыдущий указывает в пустоту
		head = tail = node;//начало равно концу и равно новому элементу
	}
	cout << "\nЭлемент добавлен...\n\n";
}

//***********************УДАЛЕНИЕ ЭЛЕМЕНТА***********************
int DeleteList(direction x)
{
	DoubleList* z = head;
	int position = 1;
	while ((x.get_Data_dir() != z->data.get_Data_dir()) && (x.get_doc_dir() != z->data.get_doc_dir()) && (x.get_ill_dir() != z->data.get_ill_dir()) && (x.get_Time_Dir() != z->data.get_Time_Dir()))
	{
		position++;
		z = z->next;
	}
	if (head == NULL) { cout << "\nСписок пуст\n\n"; return 0; }
	if (head->next == NULL)
	{
		delete head;
		head = NULL;
	}
	else if (position == 1)
	{
		head->next->prev = NULL;
		head = head->next;
	}
	else
	{
		DoubleList* a = head;
		if (z->next != NULL)
		{
			for (int i = position; i > 1; i--) a = a->next;
			if (a == head) head = a->next;
			a->prev->next = a->next;
			a->next->prev = a->prev;
			delete a;
		}
		else
		{
			int i = 1;
			while (i != position)
			{
				a = a->next;
				i++;
			}
			a->prev->next = NULL;
			delete a;
		}
	}
	cout << "\nЭлемент удален...\n\n";
}

//*************************ВЫВОД СПИСКА*************************
void PrintList()
{
	DoubleList* node = new DoubleList;
	node = head;//временный адрес первого элемента
	while (node != NULL)
	{
		/*cout << "Регистрационный номер больного: " << node->data.ill_dir.Number << ";" << endl;
		cout << "Фамилия больного: " << node->data.ill_dir.fio << ";" << endl;
		cout << "Фамилия доктора: " << node->data.doc_dir.FIO << ";" << endl;
		cout << "Номер пациента: " << node->data.ill_dir.Number << ";" << endl;*/
		//node->data.ill_dir.Print();
		//node->data.doc_dir.Print();
		node->data.Print();
		//cout << "Дата направления: " << node->data.Data_Dir << ";" << endl;
		//cout << "Время направления: " << node->data.Time_Dir << ";" << endl << endl;
		node = node->next;//смена адреса на следующий элемент
	}
	cout << '\n';
	system("pause");
}

//Вывод для больных
void PrintListFIO(string number_cin)
{
	DoubleList* node = new DoubleList;
	node = head;//временный адрес первого элемента
	while (node != NULL)
	{
		ill temp_ill = node->data.get_ill_dir();
		if (temp_ill.get_number() == number_cin)
		{
			cout << "Больной имеет направления к следующим докторам: \n";
			//cout << "Фамилия доктора: " << node->data.doc_dir.FIO << ";" << endl;
			doctor temp_doc = node->data.get_doc_dir();
			temp_doc.Print();
		}
		node = node->next;//смена адреса на следующий элемент
	}
	cout << '\n';
}

//Вывод для докторов
void PrintListDOC(string doc_FIO)
{
	DoubleList* node = new DoubleList;
	node = head;//временный адрес первого элемент
	cout << "К доктору имеют направления следующие больные: \n\n";
	while (node != NULL)
	{
		doctor temp_doc = node->data.get_doc_dir();
		if (temp_doc.get_FIO_doctor() == doc_FIO)
		{
			//cout << "Фамилия больного: " << node->data.ill_dir.fio << ";" << endl;
			//cout << "Регистрационный номер больного: " << node->data.ill_dir.Number << ";" << endl << endl;
			//node->data.ill_dir.Print();
			//node->data.doc_dir.Print();
			node->data.Print();
		}
		node = node->next;//смена адреса на следующий элемент
	}
	cout << '\n';
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	system("Color 0B");
	setlocale(LC_ALL, "rus");
	//Больные
	ListNode* goodKeys = nullptr, * badKeys = nullptr;
	HashNode table[size_1];
	int variant = 0;
	ill value1;
	string key;
	//Доктора
	TreeNode* root = NULL; //Указатель на корень дерева
	TreeNode* temp = NULL; //Чтобы не трогать корневой указатель
	int count = 0; //счетчик количества шагов при поиске
	doctor value; //значение нового элемента
	bool found = false; //Флаговый регистр поиска
	while (1)
	{
		system("cls");
		cout << ">> Пожалуйста, выберите дальнейшее действие" << endl << endl;
		cout << "   (1) Добавить сведения о больных." << endl;
	//	cout << "   (2) Найти больного по регистрационному номеру." << endl;
		cout << "   (3) Найти больного по ФИО." << endl;
		cout << "   (4) Вывести таблицу со списком больных на экран." << endl;
		cout << "   (5) Очистить таблицу." << endl;
		cout << "   (6) Выгрузить все сведения в файл." << endl;
		cout << "   (7) Удалить больного." << endl << endl;
		cout << "   (8) Добавить врача." << endl;
		cout << "   (9) Удалить врача." << endl;
		cout << "   (10) Поиск врача по ФИО." << endl;
		cout << "   (11) Поиск врача по должности." << endl;
		cout << "   (12) Вывести весь список врачей." << endl << endl;
		cout << "   (13) Зарегистрировать новое направление." << endl;
		cout << "   (14) Зарегестрировать возврат направления." << endl;
		cout << "   (15) Вывести все существующие направления направления." << endl;
		cout << "   (0) Выход из программы." << endl << endl;
		cout << ">> Ваш выбор: ";
		cin >> variant;

		system("cls");
		switch (variant)
		{
		case 1:
		{
			key = getKey();
			cout << ">> Введите адрес проживания: " << endl;
			cin.ignore();
			string temp;
			adress temp_adress;
			int temp1;
			
			cout << "Введите страну: ";
			cin >> temp;
			getline(cin, temp);
			temp_adress.set_country(temp);
			
			cout << "Введите город: ";
			cin >> temp;
			getline(cin, temp);
			temp_adress.set_city(temp);

			cout << "Введите район: ";
			cin >> temp;
			getline(cin, temp);
			temp_adress.set_district(temp);

			cout << "Введите улицу: ";
			cin >> temp;
			getline(cin, temp);
			temp_adress.set_street(temp);

			cout << "Введите номер дома: ";
			cin >> temp1;
			temp_adress.set_house(temp1);

			cout << "Введите номер квартиры (если у Вас частный дом, введите цифру '0': ";
			cin >> temp1;
			temp_adress.set_house(temp1);

			cout << ">> Введите дату рождения: ";
			getline(cin, temp);
			value1.set_birthday(temp);

			cout << ">> Введите Фамилию, Имя и Отчество: ";
			getline(cin, temp);
			value1.set_fio(temp);

			cout << ">> Введите место работы(учебы): ";
			getline(cin, temp);
			value1.set_place_of_work_or_study(temp);

			value1.set_number(key);
			if (checkKey(key))
			{
				if (addValue(table, key, value1))
					push(goodKeys, key);
				else
					push(badKeys, key);
			}
			else cout << ">> Неправильный формат ключа." << endl;
			break;
		}
		case 2:
		{
			key = getKey();
			HashNode* elem = get(table, key);
			if (elem != nullptr)
			{
				/*cout << "Адрес: " << elem->value.address << endl;
				cout << "Дата рождения: " << elem->value.birthday << endl;
				cout << "ФИО: " << elem->value.fio << endl;
				cout << "Регистрационный номер: " << elem->value.Number << endl;
				cout << "Место работы: " << elem->value.place_of_work_or_study << endl << endl;*/
				elem->value.Print();
				PrintListFIO(elem->value.get_number());
			}
			else cout << "Элемент не найден" << std::endl;
			system("pause");
			break;
		}
		case 3:
		{
			cout << ">> Введите ФИО: ";
			string fio;
			cin.ignore();
			getline(cin, fio);
			bool check = false;
			for (int i = 0; i < size_1; i++)
			{
				if (!table[i].deleted)
				{
					if (table[i].value.get_fio() == fio)
					{
						/*cout << "Значение: " << endl;
						cout << "Адрес: " << table[i].value.address << endl;
						cout << "Дата рождения: " << table[i].value.birthday << endl;
						cout << "ФИО: " << table[i].value.fio << endl;
						cout << "Регистрационный номер: " << table[i].value.Number << endl;
						cout << "Место работы: " << table[i].value.place_of_work_or_study << endl << endl;*/
						table[i].value.Print();
						check = true;
					}
				}
			}
			if (check == false)
				cout << ">> Не найдено больного с данным ФИО" << endl;
			system("pause");
			break;
		}
		case 4:
		{
			for (int i = 0; i < size_1; i++)
			{
				if (!table[i].deleted)
				{
					/*cout << "\tЗначение: " << endl;
					cout << "Адрес: " << table[i].value.address << endl;
					cout << "Дата рождения: " << table[i].value.birthday << endl;
					cout << "ФИО: " << table[i].value.fio << endl;
					cout << "Регистрационный номер: " << table[i].value.Number << endl;
					cout << "Место работы: " << table[i].value.place_of_work_or_study << endl << endl;*/
					table[i].value.Print();
				}
			}
			system("pause");
			break;
		}
		case 5:
		{
			clear(table);
			clear(goodKeys);
			clear(badKeys);
			break;
		}
		case 6:
		{
			ofstream fout("table.csv");
			int arr[size_1];
			for (int i = 0; i < size_1; i++)
				arr[i] = 0;

			for (ListNode* i = goodKeys; i != nullptr; i = i->next)
				++arr[mainHash(i->key)];

			for (ListNode* i = badKeys; i != nullptr; i = i->next)
				++arr[mainHash(i->key)];

			for (int i = 0; i < size_1; i++)
				fout << arr[i] << '\n';
			fout.close();
			break;
		}
		case 7:
		{
			key = getKey();
			if (remove(table, key))
				cout << ">> Больной успешно удален из таблицы." << endl;
			else cout << ">> Удалить больного из списка не удалсь." << endl;
			system("pause");
			break;
		}
		case 8://Добавление элемента
		{
			cout << ">> Введите значение добавляемого элемента: ";
			cout << endl;
			cout << "Фамилия врача: ";
			cin.ignore();
			string temp;
			getline(cin, temp);
			value.set_FIO_doctor(temp);
			cout << endl;
			cout << "Номер кабинета: ";
			int temp1;
			cin >> temp1;
			value.set_kab_number(temp1);
			cout << endl;
			cout << "Должность: ";
			cin >> temp;
			value.set_post(temp);
			cout << endl;
			cout << "Время работы: ";
			cin.ignore();
			getline(cin, temp);
			value.set_time_work(temp);
			cout << endl;
			search(root, value, found);
			if (found == true)
				//cout << ">> Доктор " << value.FIO << " уже добавлен." << endl;
			{
				value.Print();
				cout << "Данный доктор уже добавлен!!!";
			}
			else
				root = add(root, value);
			found = false;
			break;
		}
		case 9://Удаление элемента
		{
			cout << ">> Введите фамилию удаляемого врача: ";
			string temp;
			cin >> temp;
			value.set_FIO_doctor(temp);
			root = deleteNode(root, value);
			cout << endl;
			//cout << ">> Доктор " << value.FIO << " удален." << endl;
			value.Print();
			cout << "ДОКТОР УДАЛЕН!!!!";
			system("pause");
			break;
		}
		case 10:
		{
			cout << ">> Введите фамилию искомого врача: ";
			doctor value2;
			string temp;
			cin >> temp;
			value2.set_FIO_doctor(temp);
			search_FIO(root, value2, count);
			PrintListDOC(value2.get_FIO_doctor());
			system("pause");
			break;
		}
		case 11://Поиск элемента должности
		{
			cout << ">> Введите должность искомого врача: ";
			doctor value2;
			string temp;
			cin >> temp;
			value2.set_post(temp);
			search_post(root, value2, count);
			system("pause");
			break;
		}
		case 12://Список элементов в порядке обхода
		{
			cout << ">> Список врачей в симметричном порядке обхода:" << endl;
			printSymmetry(root);
			system("pause");
			break;
		}
		case 13:
		{
			direction x;
			key = getKey();
			HashNode* elem = get(table, key);
			if (elem != nullptr)
			{
				PrintListFIO(elem->value.get_number());
				//x.ill_dir.set_number(elem->value.get_number());
				//x.ill_dir.set_fio(elem->value.get_fio());
				x.set_ill_dir(elem->value);
			}
			cout << ">> Введите фамилию  врача: ";
			doctor value2;
			string temp;
			cin.ignore();
			getline(cin, temp);
			value2.set_FIO_doctor(temp);
			if (search_FIO(root, value2, count))
			{
				//x.doc_dir.set_FIO_doctor(value2.get_FIO_doctor());
				x.set_doc_dir(value2);
			}
			PrintListDOC(value2.get_FIO_doctor());
			cout << ">> Введите назначеный день:  ";
			getline(cin, temp);
			x.set_Data_dir(temp);
			cout << ">> Введите назначенное время:  ";
			getline(cin, temp);
			x.set_Time_Dir(temp);
			AddList(x);
			break;
		}
		case 14:
		{
			direction x;
			string temp;
			ill temp_ill;
			doctor temp_doc;
			cout << ">> Введите регистрационный номер пациента:  ";
			cin >> temp;
			temp_ill.set_number(temp);
			x.set_ill_dir(temp_ill);
			cout << ">> Введите фамилию доктора к которому регистрируется направление:  ";
			cin.ignore();
			getline(cin, temp);
			temp_doc.set_FIO_doctor(temp);
			x.set_doc_dir(temp_doc);
			cout << ">> Введите назначеный день:  ";
			getline(cin, temp);
			x.set_Data_dir(temp);
			cout << ">> Введите назначенное время:  ";
			getline(cin, temp);
			x.set_Time_Dir(temp);
			DeleteList(x);
			break;
		}
		case 15:
		{
			PrintList();
			break;
		}
		case 0:
			return 0;
		default:
			break;
		}
	}

}

/////////////////////////////////////////////////////////////////////



