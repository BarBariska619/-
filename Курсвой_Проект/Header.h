#pragma once
#include <iostream>
#include <string>
#include <random>
#include <fstream>

using namespace std;

class adress {
private:
	string country;
	string city;
	string district;
	string street;
	int house;
	int apartament;
public:
	void Print();
	//сеттеры
	void set_country(string country);
	void set_city(string city);
	void set_district(string district);
	void set_street(string street);
	void set_house(int house);
	void set_apartament(int apartament);
	//геттеры
	string get_country();
	string get_city();
	string get_district();
	string get_street();
	int get_house();
	int get_apartament();
	//перегрузка 
	bool operator != (const adress& x);
};

class ill {
private:
	string number;
	string fio;
	string birthday;
	adress adress_ill;
	string place_of_work_or_study;
public:
	void Print();
	//сеттеры
	void set_number(string num);
	void set_fio(string fio);
	void set_birthday(string birthday);
	void set_adress(adress adress_ill);
	void set_place_of_work_or_study(string place_of_work_or_study);
	//геттеры
	string get_number();
	string get_fio();
	string get_birthday();
	adress get_adress();
	string get_place_of_work_or_study();
	//перегрузка оператора
	bool operator != (const ill& x);
};

class doctor {
private:
	string FIO_doctor;
	string post;
	int kab_number;
	string time_work;
public:
	void Print();
	//сеттеры
	void set_FIO_doctor(string FIO);
	void set_post(string post);
	void set_kab_number(int kab_number);
	void set_time_work(string time_work);
	//геттеры
	string get_FIO_doctor();
	string get_post();
	int get_kab_number();
	string get_time_work();
	//перегружаем операторы
	bool operator != (const doctor& x);
};


class direction  {
private:
	ill ill_dir;
	doctor doc_dir;
	string Data_Dir;
	string Time_Dir;
public:
	void Print();
	//сеттеры
	void set_ill_dir(ill ill_dir);
	void set_doc_dir(doctor doc_dir);
	void set_Data_dir(string Data_dir);
	void set_Time_Dir(string Time_dir);
	//геттеры
	ill get_ill_dir();
	doctor get_doc_dir();
	string get_Data_dir();
	string get_Time_Dir();
};

