#include <iostream>
//#include <Windows.h>
#include <cstdlib>
#include <string>
#include <limits>






int size = 10;
int receiptSize = 1;
double totalSum = 0;
int quantity = 0;
int CountOfPurchases = 0;
double price;
const int max = 10;



int* test = new int[size];
std::string* nameArr = new std::string[size];
int* countArr = new int[size];
float* priceArr = new float[size];


std::string* nameReceipt = new std::string[receiptSize];
int* countReceiptArr = new int[receiptSize];
double* priceReceiptArr = new double[receiptSize];


std::string names[max];
int quantities[max];
double prices[max];
int numItems = 0;



void Start();
void CreateStorage();
template<typename ArrType>
void FillArray(ArrType staticArray[], ArrType dinArray[], int size);
template<typename ArrType>
void PrintArray(ArrType arr[], int size);
void Shop();
void ShowStorage();
void Selling();
void AddElementToReceipt(int& receiptSize, int id, int count);
void PrintReceipt();
void ChangePrice();
void RemoveStorage();
void AddToStorage();
void ChangeStorage();
void AddElement();
void DeleteElement();
double QuantityDiscount(int quantity, double price);
int FreeCucumber(double totalSum);
double PromoCoolCucumber(std::string promo, double totalsum);
void pauseConsole();
void CreateStorage2();




int main() {


	setlocale(LC_ALL, "ru");
	srand(time(NULL));

	Start();

	delete[] test;
	delete[] nameArr;
	delete[] countArr;
	delete[] nameReceipt;
	delete[] countReceiptArr;
	delete[] priceReceiptArr;



	system("pause");
	return 0;
}		

void Start()
{
	bool exit = false;
	std::string adminLogin = "AdminCucumber";
	std::string adminPassword = "cucumber123";
	std::string login, password;
	int choose;
	int chooseStorageType;


	std::cout << "\t\t\tТравкаШоп\n\t\t    Добро пожаловать!!!" << std::endl;

	do
	{
		std::cout << "\nЛогин: ";
		std::getline(std::cin, login, '\n');

		std::cout << "Пароль: ";
		std::getline(std::cin, password, '\n');

		if (login != adminLogin || password != adminPassword) {
			std::cerr << "\nНеверный логин и пароль\n";
			std::cout << "\nПопробовать ещё раз?\n1 - да, 2 - выход из прогаммы\n";
			std::cin >> choose;
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			if (choose == 2)
			{
				exit = true;
			}
		}
		else {
			exit = true;
			int chooseStorageType;

			do
			{
				std::cout << "Выберите формат склада: \n1-Гoтовый склад\n2-Создать склад вручную \n";
				std::cin >> chooseStorageType;
			} while (chooseStorageType < 1 || chooseStorageType>2);
			if (chooseStorageType == 1)
			{
				CreateStorage();
				Shop();
			}
			else if (chooseStorageType == 2)
			{
				CreateStorage2();
				Shop();
			}
			else
			{
				std::cout << "Error";

			}
		}
	} while (!exit);




}

void CreateStorage()
{
	const int staticSize = 10;
	int id[staticSize]{ 0,1,2,3,4,5,6,7,8,9, };
	std::string name[staticSize]{ "Бонсай Артём","Фикус Алексей","Кактус Борис" ,
		"Алоэ Вера" ,"Филодендрон" ,"Кокос   ",
		"Адиантум","Кислица Лидия","Монстера София",
		"Пальма Антон" };
	int count[staticSize]{ 3,5,10,7,6,30,9,10,9 };
	float price[staticSize]{ 699.99,899.39,349.99,599.99,1299.99,10000,999.99,699.99,799.99,1499.29 };

	FillArray(id, test, staticSize);
	FillArray(name, nameArr, staticSize);
	FillArray(count, countArr, staticSize);
	FillArray(price, priceArr, staticSize);

}

void Shop()
{
	int choose;
	system("cls");
	while (true)
	{

		do
		{
			std::cout << "1) Показать склад\n";
			std::cout << "2) Начать продажу\n";
			std::cout << "3) Изменить цену\n";
			std::cout << "4) Списать товар\n";
			std::cout << "5) Пополнить товар\n";
			std::cout << "6) Изменить склад\n";
			std::cout << "0) Закончить смену\n";
			std::cin >> choose;
		} while (choose < 0 || choose>6);

		if (choose == 1) {

			system("cls");
			ShowStorage();


		}
		else if (choose == 2) {

			system("cls");
			Selling();

		}
		else if (choose == 3) {

			system("cls");
			ChangePrice();

		}
		else if (choose == 4) {

			system("cls");
			RemoveStorage();

		}
		else if (choose == 5) {

			system("cls");
			AddToStorage();

		}
		else if (choose == 6) {

			system("cls");
			ChangeStorage();

		}
		else if (choose == 0) {

			break;

		}
		else {

			std::cout << "Error";

		}

	}
}

void ShowStorage()
{
	int choose;
	std::cout << "Показать готовый склад или свой склад? \n1-Готовый склад\n2-Свой склад\n";
	std::cin >> choose;
	if (choose == 1) {
		std::cout << "\tid товара\tНазвание\t\t\tЦена\t\tКол-во\n\n";
		for (int i = 0; i < size; i++)
		{
			std::cout << "\t" << test[i] + 1 << "\t\t" << nameArr[i] << "\t\t\t" << priceArr[i] << "\t\t" << countArr[i] << "\n";
		}
	}
	else if (choose == 2) {

		std::cout << "\tНазвание\t\t\tЦена\t\tКол-во\n\n";

		for (int i = 0; i < numItems; i++) {
			std::cout << "\t" << names[i] << "\t\t\t" << quantities[i] << "\t\t" << prices[i] << "\n";
		}

	}
	else
	{

		std::cout << "Error";

	}

}

void Selling()
{
	int chooseId, chooseCount, confirm, CountOfPurchases = 0;
	bool isFirst = true;
	std::cout << "Действующие акции:\n1) при покупке от 5-ти растений скидка 5%\n2) при покупке от 1500 рублей антистресс Cucumber в подарок\n3) единоразовая скидка по промокоду 'coolcucumber' 15% ";
	while (true)
	{
		do
		{
			std::cout << "\nВведите id товара: ";
			std::cin >> chooseId;
			if (chooseId<1 || chooseId>size)
			{
				std::cerr << "Нет такого Id\n";
				continue;
			}
			if (countArr[chooseId - 1] > 0)
			{
				while (true)
				{
					std::cout << "\nВы выбрали: " << nameArr[chooseId - 1] << "\n";
					std::cout << "\nКол-во товара на складе:  " << countArr[chooseId - 1] << "\n";
					std::cout << "Выберите кол-во товара для покупки: ";
					std::cin >> chooseCount;
					if (chooseCount<1 || chooseCount>countArr[chooseId - 1])
					{
						std::cerr << "Тoвара не хватает\n";
						continue;
					}
					else {
						break;
					}
				}
			}
			else
			{
				std::cerr << "Этого товара нет на складе\n";
				continue;
			}
			std::cout << "\nВы выбрали: " << nameArr[chooseId - 1] << "\n";
			std::cout << "В количестве:  " << chooseCount << "\n";
			std::cout << "Подтвердите выбор: \n1 - Всё хорошо\n2 - Повторить\n";
			std::cin >> confirm;

			if (confirm == 1)
			{
				if (isFirst)
				{
					isFirst = false;
					nameReceipt[receiptSize - 1] = nameArr[chooseId - 1];
					countReceiptArr[receiptSize - 1] = chooseCount;
					priceReceiptArr[receiptSize - 1] = priceArr[chooseId - 1] * chooseCount;
					countArr[chooseId - 1] -= chooseCount;
				}
				else if (!isFirst)
				{
					AddElementToReceipt(receiptSize, chooseId, chooseCount);

				}
			}
			
			else
			{
				continue;
			}
			std::cout << "Купить ещё один товар?\n1-Да\n2-Нет\n";
			std::cin >> confirm;
			if (confirm == 1)
			{
				continue;
			}
			else
			{
				break;
			}

		} while (true);
		system("cls");
		PrintReceipt();
		break;
	}
}

template<typename ArrType>
void PrintArray(ArrType arr[], int size)
{
	for (int i = 0; i < size; i++)
	{
		std::cout << arr[i] << " ";
	}
	std::cout << "\n";
}


void AddElementToReceipt(int& receiptSize, int id, int count)
{

	std::string* nameReceiptTemp = new std::string[receiptSize];
	int* countReceiptArrTemp = new int[receiptSize];
	double* priceReceiptArrTemp = new double[receiptSize];

	for (int i = 0; i < receiptSize; i++)
	{
		nameReceiptTemp[i] = nameReceipt[i];
		countReceiptArrTemp[i] = countReceiptArr[i];
		priceReceiptArrTemp[i] = priceReceiptArr[i];
	}
	delete[] nameReceipt;
	delete[] countReceiptArr;
	delete[] priceReceiptArr;

	receiptSize++;

	nameReceipt = new std::string[receiptSize];
	countReceiptArr = new int[receiptSize];
	priceReceiptArr = new double[receiptSize];

	for (int i = 0; i < receiptSize - 1; i++)
	{
		nameReceipt[i] = nameReceiptTemp[i];
		countReceiptArr[i] = countReceiptArrTemp[i];
		priceReceiptArr[i] = priceReceiptArrTemp[i];
	}

	nameReceipt[receiptSize - 1] = nameArr[id - 1];
	countReceiptArr[receiptSize - 1] = count;
	priceReceiptArr[receiptSize - 1] = priceArr[id - 1] * count;
	countArr[id - 1] -= count;


	delete[] nameReceiptTemp;
	delete[] countReceiptArrTemp;
	delete[] priceReceiptArrTemp;

}

void PrintReceipt()
{
	std::string promo;
	int choose;
	std::cout << "Желаете ввести промокод?\n1 - да\n2 - нет\n";
	do
	{
		std::cin >> choose;
	} while (choose < 1 || choose > 2);
	if (choose == 1)
	{
		std::cout << "\nВведите промокод: ";
		std::cin >> promo;
	}
	
	std::cout << "Название\t\t\tКол-во\t\tЦена\n\n";
	for (int i = 0; i < receiptSize; i++)
	{
		std::cout << nameReceipt[i] << "\t\t\t" << countReceiptArr[i] << "\t\t" << priceReceiptArr[i] << "\n";
		totalSum += priceReceiptArr[i] * countReceiptArr[i];
	}

	double quantityDiscount = QuantityDiscount(quantity, totalSum);
	double FreeCucumbers = FreeCucumber(totalSum);
	double Promo = PromoCoolCucumber(promo, totalSum);

	std::cout << "\nОбщая сумма: " << totalSum << std::endl;
	if (quantityDiscount > 0) {
		std::cout << "Скидка за количество товаров: " << quantityDiscount << "\n";
	}
	if (FreeCucumbers > 0) {
		std::cout << "Вы получили антистресс Cucumber!!: ";
	}
	if (Promo > 0) {
		std::cout << "\nСкидка по промокоду: " << Promo << "\n";
	}
	double finalPrice = totalSum - quantityDiscount - Promo;
	std::cout << "Итоговая цена: " << finalPrice << std::endl;
}

void ChangePrice()
{

	int id;
	double newPrice;
	do
	{
		std::cout << "Введите id товара: ";
		std::cin >> id;

	} while (id<1 || id>test[size - 1]);
	std::cout << "\n\nТекущая цена продукта: " << nameArr[id - 1] << " = " << priceArr[id - 1];
	do
	{
		std::cout << "Введите новую цену: ";
		std::cin >> newPrice;

	} while (newPrice < 0.01 || newPrice>100000.03);
	priceArr[id - 1] = newPrice;
	std::cout << "Цена изменена";
}

void RemoveStorage()
{

	int id;
	int goodCount;
	do
	{
		std::cout << "Введите id товара: ";
		std::cin >> id;

	} while (id<1 || id>test[size - 1]);
	std::cout << "\n\nТекущее количество товара: " << nameArr[id - 1] << " = " << countArr[id - 1];
	do
	{
		std::cout << "\nЧисло списывания товара: ";
		std::cin >> goodCount;

	} while (goodCount > countArr[id - 1]);
	countArr[id - 1] -= goodCount;
	std::cout << "\nCписание произошло успешно";





}

void AddToStorage()
{

	int id;
	int goodCount;
	do
	{
		std::cout << "Введите id товара: ";
		std::cin >> id;

	} while (id<1 || id>test[size - 1]);
	std::cout << "\n\nТекущее количество товара: " << nameArr[id - 1] << " = " << countArr[id - 1];
	do
	{
		std::cout << "\nЧисло добавления товара: ";
		std::cin >> goodCount;

	} while (goodCount < 0);
	countArr[id - 1] += goodCount;
	std::cout << "\nПополнение произошло успешно";

}

void ChangeStorage()
{
	int choose;
	do
	{
		std::cout << "Изменение склада. \nДобавить новый товар-1\nУдалить товар-2\nВыход-3\n";
		std::cin >> choose;
	} while (choose < 1 || choose>3);
	if (choose == 1)
	{
		AddElement();
	}
	else if (choose == 2)
	{
		DeleteElement();
	}
	else if (choose == 3)
	{
		std::cout << "Выход";
	}

}

void AddElement()
{

	int* idArrTemp = new int[size];
	std::string* nameArrTemp = new std::string[size];
	int* countArrTemp = new int[size];
	float* priceArrTemp = new float[size];


	for (int i = 0; i < size; i++)
	{
		idArrTemp[i] = test[i];
		nameArrTemp[i] = nameArr[i];
		countArrTemp[i] = countArr[i];
		priceArrTemp[i] = priceArr[i];
	}
	delete[] test;
	delete[] nameArr;
	delete[] countArr;
	delete[] priceArr;

	size++;

	test = new int[size];
	nameArr = new std::string[size];
	countArr = new int[size];
	priceArr = new float[size];


	for (int i = 0; i < size - 1; i++)
	{
		test[i] = idArrTemp[i];
		nameArr[i] = nameArrTemp[i];
		countArr[i] = countArrTemp[i];
		priceArr[i] = priceArrTemp[i];
	}

	test[size - 1] = size - 1;
	std::cout << "\nВведите имя нового товара: ";
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::getline(std::cin, nameArr[size - 1], '\n');
	std::cout << "\nВведите кол-во нового товара: ";
	std::cin >> countArr[size - 1];
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cout << "\nВведите цену нового товара: ";
	std::cin >> priceArr[size - 1];
	std::cout << "\nТовар успешно добавлен\n\n";

	delete[] idArrTemp;
	delete[] nameArrTemp;
	delete[] countArrTemp;
	delete[] priceArrTemp;
}
void DeleteElement()
{

	int* idArrTemp = new int[size];
	std::string* nameArrTemp = new std::string[size];
	int* countArrTemp = new int[size];
	float* priceArrTemp = new float[size];


	for (int i = 0; i < size; i++)
	{
		idArrTemp[i] = test[i];
		nameArrTemp[i] = nameArr[i];
		countArrTemp[i] = countArr[i];
		priceArrTemp[i] = priceArr[i];
	}
	delete[] test;
	delete[] nameArr;
	delete[] countArr;
	delete[] priceArr;

	size--;

	test = new int[size];
	nameArr = new std::string[size];
	countArr = new int[size];
	priceArr = new float[size];

	int index = 0;
	std::cout << "Какой товар удалить? \nВведите id товара: ";
	std::cin >> index;
	for (int i = 0, j = 0; j < size, i < size; i++, j++)
	{
		if (i == index - 1)
		{
			i++;
			test[j] = idArrTemp[j];
			nameArr[j] = nameArrTemp[i];
			countArr[j] = countArrTemp[i];
			priceArr[j] = priceArrTemp[i];
		}
		else {

			test[j] = idArrTemp[j];
			nameArr[j] = nameArrTemp[i];
			countArr[j] = countArrTemp[i];
			priceArr[j] = priceArrTemp[i];

		}
	}
	delete[] idArrTemp;
	delete[] nameArrTemp;
	delete[] countArrTemp;
	delete[] priceArrTemp;

}
template<typename ArrType>
void FillArray(ArrType staticArray[], ArrType dinArray[], int size)
{
	for (int i = 0; i < size; i++)
	{
		dinArray[i] = staticArray[i];
	}
}

double QuantityDiscount(int quantity, double sum) {
	if (quantity >= 5) {
		return sum * 0.1;
	}
	else {
		return 0;
	}
}


int FreeCucumber(double totalSum) {
	if (totalSum >= 1500) {
		return 1;
	}
	else {
		return 0;
	}
}

double PromoCoolCucumber(std::string promo, double totalsum)
{
	if (promo == "coolcucumber" && CountOfPurchases < 1)
	{
		return totalsum * 0.15;
	}
	else {
		return 0;
	}
}

void pauseConsole() {
	std::cout << "Нажмите Enter для продолжения...";
	std::cin.get();
}



void CreateStorage2() {

	while (true) {
		system("cls");

		if (numItems >= max) {
			std::cout << "Склад заполнен на максимум\n";
			break;
		}

		std::cout << "Введите название товара, для завершения создания склада введите 'cтоп': ";
		std::cin >> names[numItems];
		std::cin.ignore();

		if (names[numItems] == "стоп") {
			break;
		}

		std::cout << "Введите количество: ";
		std::cin >> quantities[numItems];
		std::cin.ignore();

		std::cout << "Введите цену: ";
		std::cin >> prices[numItems];
		std::cin.ignore();

		numItems++;

		pauseConsole();
	}

	system("cls");

	std::cout << "Товары на складе:\n";
	for (int i = 0; i < numItems; i++) {
		std::cout << "\t" << names[i] << "\t\t\t" << quantities[i] << "\t\t" << prices[i] << "\n";
	}

	pauseConsole();
}