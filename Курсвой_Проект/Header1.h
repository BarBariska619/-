#pragma once
#include <iostream>
#include <string>
#include <random>
#include <fstream>
#include "Header.h"

using namespace std;
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

struct DoubleList //�������� ���� ������
{

	Appointmen data; //�������������� ����
	DoubleList* next; //��������� �� ��������� �������
	DoubleList* prev; //��������� �� ���������� �������
	DoubleList* prevFIO; //��������� 1�� ������ 
};

struct TreeNode
{
	doctor data;; // ������
	int height; // ������
	TreeNode* left; // ��������� �� ������ �������
	TreeNode* right; // ��������� �� ������� �������
	TreeNode(doctor value) { data = value; left = right = 0; height = 1; } // ����������� ������ ����
};

DoubleList* head; //��������� �� ������ ������� ������
DoubleList* tail; //��������� �� ��������� ������� ������