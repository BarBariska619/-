#include "Header1.h"
#include "Header.h"

#pragma region TREE
string generateKey()//�������� �����
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

bool checkKey(string& key) //�������� �� ������������ �����
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

string getKey() //���� �����
{
	string str;
	cout << ">> ������� ��������������� ����� �� 8�� ����: " << endl;
	cin >> str;
	while (!checkKey(str))
	{
		cout << "������, ��������� ����: ";
		cin.ignore(cin.rdbuf()->in_avail());
		getline(cin, str);
	}
	return str;
}

int mainHash(string key) // ��� �������
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

bool addValue(HashNode* const& table, const std::string& key, ill value)
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
			table[position].value.get_adress(value.set_adress());
			table[position].value.get_birthday(value.set_birthday());
			table[position].value.get_name(value.set_name());
			table[position].value.get_surname(value.set_surname());
			table[position].value.get_number(value.set_number());
			table[position].value.get_place_of_work_or_study(value.set_place_of_work_or_study());
			table[position].deleted = false;
			table[position].key = key;
		}
		else
		{
			for (position; position < size_1; position++)
			{
				if (table[position].deleted)
				{
					table[position].value.get_adress(value.set_adress());
					table[position].value.get_birthday(value.set_birthday());
					table[position].value.get_name(value.set_name());
					table[position].value.get_surname(value.set_surname());
					table[position].value.get_number(value.set_number());
					table[position].value.get_place_of_work_or_study(value.set_place_of_work_or_study());
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
	ill temp_ill = z->data.set_ill();
	while (temp_ill.set_number() != key)
	{
		position++;
		z = z->next;
	}
	if (head == NULL) { cout << "\n������ ����\n\n"; return 0; }
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

#pragma endregion

#pragma region balance
// ������� ��� ���� height
int height(TreeNode* p)
{
	if (p != NULL)
		return p->height;
	else
		return 0;
}

// ��������� balance factor ��������� ����
int bfactor(TreeNode* p)
{
	return height(p->right) - height(p->left);
}

// ��������������� ���������� �������� ���� height ��������� ����
void fixheight(TreeNode* p)
{
	int h_left = height(p->left);
	int h_right = height(p->right);
	if (h_left > h_right)
		p->height = h_left + 1;
	else
		p->height = h_right + 1;
}

// ��������� ������ ������� ������ p
TreeNode* rotateRight(TreeNode* p)
{
	TreeNode* q = p->left;
	p->left = q->right;
	q->right = p;
	fixheight(p);
	fixheight(q);
	return q;
}

// ��������� ����� ������� ������ q
TreeNode* rotateLeft(TreeNode* q) //�������� ������
{
	TreeNode* p = q->right; //������� ��������� �� ����� ������ (����� ������ ����� ������ ���������)
	q->right = p->left; //� ������� ����� ������ ��������� ���������� ����� ���������� ������ �����
	p->left = q; //������ ������
	fixheight(q);
	fixheight(p);
	return p; //���������� ��������� �� ����� ������
}

// ������������ ����
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

	return p; // ������������ �� �����
}
#pragma endregion

#pragma region additon
// ����� ���� ��� ����������
void search(TreeNode* root, doctor value, bool& found)
{
	// ���� ������ �����
	if (root == NULL)
		return;
	// ���� ������� ������
	else if (root->data.set_name() == value.set_name())
	{
		found = true;
		return;
	}

	if (value.set_name() < root->data.set_name() && value.set_surname() < root->data.set_surname())
		search(root->left, value, found);
	else
		search(root->right, value, found);
	return;
}

// ������� value � ������ � ������ p
TreeNode* add(TreeNode* p, doctor value)
{
	if (!p)
		return new TreeNode(value);

	if (value.set_name() < p->data.set_name() && value.set_surname() < p->data.set_surname()) 
		p->left = add(p->left, value);

	else
		p->right = add(p->right, value);

	return balance(p);
}
#pragma endregion

#pragma region print

void printSymmetry(TreeNode* root)//����� ������ � ������������ ������� ������
{
	if (root == NULL) return;
	printSymmetry(root->left);
	root->data.Print();
	printSymmetry(root->right);
}


void printTree(TreeNode* p, int level)// ����� ������ �� �����
{
	TreeNode* pr = p;
	if (pr)
	{
		printTree(pr->right, level + 1);
		for (int i = 0; i < level; i++) cout << " ";
		pr->data.Print();
		printTree(pr->left, level + 1);
	}
}


void PrintList() //����� ������
{
	DoubleList* node = new DoubleList;
	node = head;//��������� ����� ������� ��������
	while (node != NULL)
	{
		node->data.Print();
		node = node->next;//����� ������ �� ��������� �������
	}
	cout << '\n';
	system("pause");
}


void PrintListFIO(string number_cin)//����� ��� �������
{
	DoubleList* node = new DoubleList;
	node = head;//��������� ����� ������� ��������
	while (node != NULL)
	{
		ill temp_ill = node->data.set_ill();
		if (temp_ill.set_number() == number_cin)
		{
			cout << "������� ����� ����������� � ��������� ��������: \n";
			doctor temp_doctor = node->data.set_doctor();
			temp_doctor.Print();
		}
		node = node->next;//����� ������ �� ��������� �������
	}
	cout << '\n';
}


void PrintListDOC(string cin_name, string cin_surname)//����� ��� ��������
{
	DoubleList* node = new DoubleList;
	node = head;//��������� ����� ������� �������
	cout << "� ������� ����� ����������� ��������� �������: \n\n";
	while (node != NULL)
	{
		doctor temp_doctor = node->data.set_doctor();
		if (temp_doctor.set_name() == cin_name && temp_doctor.set_surname() == cin_surname)
		{
			ill temp_ill = node->data.set_ill();
			temp_ill.Print();
		}
		node = node->next;//����� ������ �� ��������� �������
	}
	cout << '\n';
}
#pragma endregion

#pragma region search
bool search1(TreeNode* root, doctor value, int& count)
{
	string temp1 = root->data.set_position();
	int s1 = temp1.length();

	string temp2 = value.set_position();
	int s2 = temp2.length();
	for (int i = 0; i < s1 - s2 + 1; i++)
	{
		for (int j = 0; j < s2; j++)
		{
			/*string temp1 = value.set_position();
			string temp2 = root->data.set_position();*/
			if (temp1[j] != temp2[i + j])
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

// ����� ����� �� ���������
int search_post(TreeNode* root, doctor value, int& count)
{
	if (root == NULL)
	{
		return 0;
	}
	search_post(root->left, value, count);
	if (search1(root, value, count))
	{
		root->data.Print();
	}
	search_post(root->right, value, count);
}

// ����� ����� �� �������
int search_FIO(TreeNode* root, doctor value, int& count)
{
	if (root == NULL)
	{
		return 0;
	}
	search_FIO(root->left, value, count);
	if (root->data.set_name() == value.set_name() && root->data.set_surname() == value.set_surname())
	{
		root->data.Print();
	}
	search_FIO(root->right, value, count);
}
#pragma endregion

#pragma region appointmen
int AddList(Appointmen x)
{
	DoubleList* node = new DoubleList; //�������� ������ ��������
	node->next = NULL;//���������, ��� ���������� �� ���������� ������ �����
	node->data.get_ill(x.a_ill);//����������� ��������
	node->data.get_doctor(x.a_doctor);//����������� ��������
	node->data.get_day_of_appointmen(x.day_of_appointmen);
	node->data.get_month_of_appointmen(x.month_of_appointmen);
	node->data.get_year_of_appointmen(x.year_of_appointmen);//����������� ��������
	node->data.get_time_of_appointmen(x.time_of_appointmen);//����������� ��������*/

	DoubleList* node1 = new DoubleList;
	node1 = head;//��������� ����� ������� ��������
	while (node1 != NULL)
	{
		int temp_node_day = node1->data.set_day_of_appointmen();
		int temp_x_day = x.set_day_of_appointmen();

		int temp_node_month = node1->data.set_month_of_appointmen();
		int temp_x_month = x.set_month_of_appointmen();

		int temp_node_year = node1->data.set_year_of_appointmen();
		int temp_x_year = x.set_year_of_appointmen();

		string temp_node_time = node1->data.a_doctor.set_time_of_work();
		string temp_x_time = x.a_doctor.set_time_of_work();

		if ((temp_node_day == temp_x_day) && (temp_node_month == temp_x_month) && (temp_node_year == temp_x_year) && (temp_node_time == temp_x_time))
		{
			cout << "�� ��� ����� ��� ���� ������!";
			system("pause");
			return 0;
		}
		node1 = node1->next;//����� ������ �� ��������� �������
	}
	if (head != NULL) //���� ������ �� ����
	{
		node->prev = tail; //��������� ����� �� ���������� ������� 
		tail->next = node; //��������� ����� ���������� �� ������� ��������
		tail = node; //������ ����� ������
		node->prevFIO = NULL;
	}
	else //���� ������ ������
	{
		node->prev = NULL; //���������� ��������� � �������
		head = tail = node;//������ ����� ����� � ����� ������ ��������
	}
	cout << "\n������� ��������...\n\n";
}

//***********************�������� ��������***********************
int DeleteList(Appointmen x)
{
	DoubleList* z = head;
	int position = 1;
	int temp_node_day = z->data.set_day_of_appointmen();
	int temp_x_day = x.set_day_of_appointmen();

	int temp_node_month = z->data.set_month_of_appointmen();
	int temp_x_month = x.set_month_of_appointmen();

	int temp_node_year = z->data.set_year_of_appointmen();
	int temp_x_year = x.set_year_of_appointmen();

	string temp_node_time = z->data.a_doctor.set_time_of_work();
	string temp_x_time = x.a_doctor.set_time_of_work();
	while ((temp_node_day != temp_x_day) && (temp_node_month != temp_x_month) && (temp_node_year != temp_x_year) && (temp_node_time != temp_x_time))
	{
		position++;
		z = z->next;
	}
	if (head == NULL) { cout << "\n������ ����\n\n"; return 0; }
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
	cout << "\n������� ������...\n\n";
}
TreeNode* findMin(TreeNode* p)
{
	if (p->left)
		return findMin(p->left);
	else
		return p;
}

// �������� ���� � ����������� ���������
TreeNode* deleteMin(TreeNode* p)
{
	if (p->left == 0)
		return p->right;
	p->left = deleteMin(p->left);
	return balance(p);
}

TreeNode* deleteNode(TreeNode* p, doctor value)
{
	if (!p) return 0;
	if (value.set_surname() < p->data.set_surname())//������ ��� ����������� �� �������!!!!
		p->left = deleteNode(p->left, value);
	else if (value.set_surname() > p->data.set_surname())//������ ��� ����������� �� �������!!!!
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

}

#pragma endregion