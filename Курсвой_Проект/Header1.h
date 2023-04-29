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

struct DoubleList //описание узла списка
{

	Appointmen data; //информационное поле
	DoubleList* next; //указатель на следующий элемент
	DoubleList* prev; //указатель на предыдущий элемент
	DoubleList* prevFIO; //указатель 1го уровня 
};

struct TreeNode
{
	doctor data;; // Данные
	int height; // Высота
	TreeNode* left; // Указатель на левого потомка
	TreeNode* right; // Указатель на правого потомка
	TreeNode(doctor value) { data = value; left = right = 0; height = 1; } // Конструктор нового узла
};

DoubleList* head; //указатель на первый элемент списка
DoubleList* tail; //указатель на последний элемент списка