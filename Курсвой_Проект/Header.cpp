#include "Header.h"
using namespace std;

#pragma region ill
void ill::Print()
{
	cout << "Регистрационный номер: " << number << endl;
	cout << "Фамилия, Имя и Отчество: " << fio << endl;
	cout << "Дата рождения: " << birthday << endl;
	cout << "Адрес проживания: ";
	adress_ill.Print();
	cout << endl;
	cout << "Место работы (учебы): " << place_of_work_or_study << endl;
}

void ill::set_number(string num)
{
	number = num;
}

void ill::set_fio(string fio)
{
	this->fio = fio;
}

void ill::set_birthday(string birthday)
{
	this->birthday = birthday;
}

void ill::set_adress(adress adress_ill)
{
	this->adress_ill = adress_ill;
}

void ill::set_place_of_work_or_study(string place_of_work_or_study)
{
	this->place_of_work_or_study = place_of_work_or_study;
}

string ill::get_number()
{
	return number;
}

string ill::get_fio()
{
	return fio;
}

string ill::get_birthday()
{
	return birthday;
}

adress ill::get_adress()
{
	return adress_ill;
}

string ill::get_place_of_work_or_study()
{
	return place_of_work_or_study;
}

bool ill::operator!=(const ill& x)
{
	return ((this->adress_ill != x.adress_ill) && (this->birthday != x.birthday) && (this->fio != x.fio) && (this->number != x.number) && (this->place_of_work_or_study != x.place_of_work_or_study));
}

#pragma endregion

void doctor::Print()
{
	cout << "ФАМИЛИЯ: " << FIO_doctor << endl;
	cout << "ПОСТ: " << post << endl;
	cout << "НОМЕР КАБИНЕТА: " << kab_number << endl;
	cout << "ВРЕМЯ РАБОТЫ: " << time_work << endl;
}

void doctor::set_FIO_doctor(string FIO)
{
	this->FIO_doctor = FIO;
}

void doctor::set_post(string post)
{
	this->post = post;
}

void doctor::set_kab_number(int kab_number)
{
	this->kab_number = kab_number;
}

void doctor::set_time_work(string time_work)
{
	this->time_work = time_work;
}

string doctor::get_FIO_doctor()
{
	return FIO_doctor;
}

string doctor::get_post()
{
	return post;
}

int doctor::get_kab_number()
{
	return kab_number;
}

string doctor::get_time_work()
{
	return time_work;
}

bool doctor::operator!=(const doctor& x)
{
	return ((this->FIO_doctor != x.FIO_doctor) && (this->kab_number != x.kab_number) && (this->post != x.post) && (this->time_work != x.time_work));
}

void direction::Print()
{
	ill_dir.Print();
	doc_dir.Print();
	cout << "Дата регистрации: " << Data_Dir << endl;
	cout << "Время регистрации: " << Time_Dir << endl;
}

void direction::set_ill_dir(ill ill_dir)
{
	this->ill_dir = ill_dir;
}

void direction::set_doc_dir(doctor doc_dir)
{
	this->doc_dir = doc_dir;
}

void direction::set_Data_dir(string Data_dir)
{
	this->Data_Dir = Data_Dir;
}

void direction::set_Time_Dir(string Time_dir)
{
	this->Time_Dir = Time_Dir;
}

ill direction::get_ill_dir()
{
	return ill_dir;
}

doctor direction::get_doc_dir()
{
	return doc_dir;
}

string direction::get_Data_dir()
{
	return Data_Dir;
}

string direction::get_Time_Dir()
{
	return Time_Dir;
}

#pragma region adress
void adress::Print()
{
	cout << "Cтрана: " << country << endl;
	cout << "Город: " << city << endl;
	cout << "Район: " << district << endl;
	cout << "Улица: " << street << endl;
	cout << "Номер дома: " << house << endl;
	if (apartament != 0)
		cout << "Квартира номер: " << apartament << endl;
}

void adress::set_country(string country)
{
	this->country = country;
}

void adress::set_city(string city)
{
	this->city = city;
}

void adress::set_district(string district)
{
	this->district = district;
}

void adress::set_street(string street)
{
	this->street = street;
}

void adress::set_house(int house)
{
	this->house = house;
}

void adress::set_apartament(int apartament)
{
	this->apartament = apartament;
}

string adress::get_country()
{
	return country;
}

string adress::get_city()
{
	return city;
}

string adress::get_district()
{
	return district;
}

string adress::get_street()
{
	return street;
}

int adress::get_house()
{
	return house;
}

int adress::get_apartament()
{
	return apartament;
}

bool adress::operator!=(const adress& x)
{
	return false;
}
#pragma endregion
