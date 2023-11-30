#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
class Address {
public:
	std::string country;
	std::string city;
	std::string street;
	int house;
	//Конструктор с параметром
	Address(std::string co, std::string ci, std::string s, int h) : country(co), city(ci), street(s), house(h) {}
	//Метод для преобразования в строку
	std::string toString() const
	{
		return country + " " + city + " " + street + " " + std::to_string(house);
	}

	//Оператор == сравнивающий объекты класса
	bool operator==(const Address& other) const {
		return country == other.country &&
			city == other.city &&
			street == other.street &&
			house == other.house;
	}
	//Оператор <
	bool operator<(const Address& other) const {
		if (country != other.country) {
			return country < other.country;
		}
		if (city != other.city) {
			return city < other.city;
		}
		if (street != other.street) {
			return street < other.street;
		}
		return house < other.house;
	}
};

//Класс для описания узла дерева
class TreeNode {
public:
	Address address;	//данные узла
	TreeNode* left;		//указатель на левый элемент
	TreeNode* right;	//указатель на правый элемент
	//Конструктор с параметром
	TreeNode(Address addr) : address(addr), left(nullptr), right(nullptr) {}
};

//Класс для описания хеш-таблицы
class HashTable {
private:
	std::vector<TreeNode*> table;
	int size;
	//функция хеширования ("середины квадрата")
	int functionHash(const Address& address)
	{
		std::string key = address.toString();
		int square = 0;
		for (char c : key)
		{
			square += c * c;
		}
		return (square * square) % size;
	}
public:
	//Метод для хеширования таблицы
	HashTable(int s) : size(s)
	{
		table.resize(size, nullptr);
	}
	//Алгоритм вставки
	void insert(Address address)
	{
		//Проверка, нужно ли увеличивать размер таблицы
		checkAndResize();
		//Индекс объекта, который нужно захешировать
		int index = functionHash(address);
		//Если такого элемента нет
		if (!table[index])
		{
			//Создается элемент 
			table[index] = new TreeNode(address);
		}
		else
		{
			TreeNode* root = table[index];
			while (root)
			{
				if (root->address.toString() == address.toString())
				{
					return;
				}
				if (address.toString() < root->address.toString())
				{
					if (!root->left)
					{
						root->left = new TreeNode(address);
						break;
					}
					root = root->left;
				}
				else
				{
					if (!root->right)
					{
						root->right = new TreeNode(address);
						break;
					}
					root = root->right;
				}
			}
		}
	}

	//--------------------------------------------------------------------------
	//Алгоритм поиска
	TreeNode* search(Address address)
	{
		//Хешируется объект и записывается в переменную
		int index = functionHash(address);
		//Создается элемент в таблице
		TreeNode* root = table[index];
		//Проходим по всему элементу
		while (root)
		{
			//Если элементы совпадают
			if (root->address.toString() == address.toString())
			{
				//Возвращаем корень
				return root;
			}
			if (address.toString() < root->address.toString())
			{
				root = root->left;
			}
			else
			{
				root = root->right;
			}
		}
		return nullptr;
	}

	//--------------------------------------------------------------------------
	//Вспомогательная фунция для удаления 
	TreeNode* findMin(TreeNode* root)
	{
		while (root->left)
		{
			root = root->left;
		}
		return root;
	}

	//--------------------------------------------------------------------------
	//Вспомогательная фунция для удаления 
	TreeNode* remove(Address address, TreeNode* root)
	{
		if (!root)				//если дерево пустое
		{
			return nullptr;
		}
		if (address.toString() < root->address.toString())
		{
			root->left = remove(address, root->left);
		}
		else if (address.toString() > root->address.toString())
		{
			root->right = remove(address, root->right);
		}
		else
		{
			if (!root->left)
			{
				TreeNode* temp = root->right;
				delete root;
				return temp;
			}
			else if (!root->right)
			{
				TreeNode* temp = root->left;
				delete root;
				return temp;
			}
			TreeNode* temp = findMin(root->right);
			root->address = temp->address;
			root->right = remove(temp->address, root->right);
		}
		return root;
	}

	//--------------------------------------------------------------------------
	//Метод удаления
	bool remove(const Address& address) {
		int index = functionHash(address);
		TreeNode* node = table[index];
		TreeNode* parent = nullptr;
		while (node) 
		{
			if (node->address == address) 
			{
				if (!parent) 
				{
					table[index] = nullptr;
				}
				else if (parent->left == node) 
				{
					parent->left = nullptr;
				}
				else if (parent->right == node) 
				{
					parent->right = nullptr;
				}
				delete node; // Освобождаем память
				return true; // Успешно удалено
			}
			else 
			{
				parent = node;
				if (address < node->address) 
				{
					node = node->left;
				}
				else 
				{
					node = node->right;
				}
			}
		}
		return false; // Записи не было в таблице
	}

	//--------------------------------------------------------------------------
	//Вывод дерева
	void printTree(TreeNode* node)
	{
		if (node)
		{
			printTree(node->left);
			std::cout << node->address.toString() << std::endl;
			printTree(node->right);
		}
	}

	//--------------------------------------------------------------------------
	//Вывод таблицы
	void printTable()
	{
		std::cout << "-------- Таблица -------- \n";
		for (int i = 0; i < size; i++)
		{
			if (table[i])
			{
				printTree(table[i]);
			}
		}
		std::cout << "-------------------------- \n";
	}

	//--------------------------------------------------------------------------
	//функция для создания новой таблицы с увеличенным размером
	void resizeTable(int newSize) 
	{
		std::vector<TreeNode*> newTable(newSize, nullptr);
		for (int i = 0; i < size; ++i) {
			TreeNode* root = table[i];
			while (root) 
			{
				Address addr = root->address;
				int newIdx = functionHash(addr);
				TreeNode* temp = root;
				root = root->right;
				temp->left = temp->right = nullptr;

				if (!newTable[newIdx]) 
				{
					newTable[newIdx] = temp;
				}
				else 
				{
					TreeNode* newRoot = newTable[newIdx];
					while (newRoot) {
						if (addr.toString() < newRoot->address.toString()) 
						{
							if (!newRoot->left) 
							{
								newRoot->left = temp;
								break;
							}
							newRoot = newRoot->left;
						}
						else 
						{
							if (!newRoot->right) 
							{
								newRoot->right = temp;
								break;
							}
							newRoot = newRoot->right;
						}
					}
				}
			}
		}
		table = newTable;
		size = newSize;
	}

	//--------------------------------------------------------------------------
	// Дополнительная функция для проверки, когда нужно выполнить ре-хеширование
	void checkAndResize() {
		int numElements = 0;
		for (int i = 0; i < size; ++i) 
		{
			if (table[i]) {
				TreeNode* root = table[i];
				while (root) 
				{
					numElements++;
					root = root->right;
				}
			}
		}
		if (numElements >= size) 
		{
			int newSize = size * 2; // Увеличиваем размер вдвое
			resizeTable(newSize);
		}
	}

	//--------------------------------------------------------------------------
	//Метод для заполнения хеш-таблицы с клавиатуры
	void fromKeyboard(int n)
	{
		std::cin.ignore(); // Очистка буфера
		for (int i = 0; i < n; i++)
		{
			std::string country, city, street;
			int house;
			while (true)
			{
				std::cout << "Введите страну: ";
				std::getline(std::cin, country);
				if (country.find_first_of("0123456789") == std::string::npos)
				{
					break;
				}
				std::cout << "\033[0;31mОшибка ввода... Попробуйте снова.\033[0m\n";
			}
			
			while (true)
			{
				std::cout << "Введите город: ";
				std::getline(std::cin, city);
				if (city.find_first_of("0123456789") == std::string::npos)
				{
					break;
				}
				std::cout << "\033[0;31mОшибка ввода... Попробуйте снова.\033[0m\n";
			}
			
			while (true)
			{
				std::cout << "Введите улицу: ";
				std::getline(std::cin, street);
				if (street.find_first_of("0123456789") == std::string::npos)
				{
					break;
				}
				std::cout << "\033[0;31mОшибка ввода... Попробуйте снова.\033[0m\n";
			}
			
			std::cout << "Введите номер дома: ";
			while (!(std::cin >> house)) 
			{
				std::cout << "\033[0;31mОшибка ввода... Попробуйте снова.\033[0m\n";
				std::cout << "Введите номер дома: ";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
			std::cin.ignore();
			Address newAddress(country, city, street, house);
			insert(newAddress);
			std::cout << "\033[0;32mЗапись сделана \033[0m\n";
		}
	}
	
	//--------------------------------------------------------------------------
	//Запись в файл
	void writeToFile(TreeNode *node, std::ofstream& file)
	{
		if (node)
		{
			writeToFile(node->left, file);
			file << node->address.toString() << std::endl;
			writeToFile(node->left, file);
		}
	}

	//--------------------------------------------------------------------------
	//Сохранение в файл
	void saveToFile(const std::string& filename)
	{
		std::ofstream file(filename);
		if (!file.is_open())
		{
			std::cout << "Ошибка открытия файла..." << std::endl;
			return;
		}
		for (int i = 0; i < size; i++)
		{
			if (table[i])
			{
				writeToFile(table[i], file);
			}
		}
		file.close();
	}

	//--------------------------------------------------------------------------
	//Чтение из файла
	void readFromFile(const std::string& filename)
	{
		std::ifstream file(filename);
		if (!file.is_open())
		{
			std::cout << "Ошибка открытия файла..." << std::endl;
			return;
		}
		std::string str;
		while (std::getline(file, str))
		{
			std::istringstream iss(str);
			std::string country, city, street;
			int house;
			iss >> country;
			for (char ch : country)
			{
				if (isdigit(ch))
				{
					std::cout << "Ошибка чтения из файла \n";
					exit(0);
				}
			}
			iss >> city;
			for (char ch : city)
			{
				if (isdigit(ch))
				{
					std::cout << "Ошибка чтения из файла \n";
					exit(0);
				}
			}
			iss >> street;
			for (char ch : street)
			{
				if (isdigit(ch))
				{
					std::cout << "Ошибка чтения из файла \n";
					exit(0);
				}
			}
			iss >> house;
			Address address(country, city, street, house);
			insert(address);
			if (iss.fail()) {
				std::cerr << "Ошибка при чтения из файла." << std::endl;
				exit(0);
			}

			// Проверяем, что в файле не осталось ничего лишнего
			std::string remaining;
			if (std::getline(file, remaining)) {
				std::cerr << "Ошибка чтения из файла." << std::endl;
				exit(0);
			}
		}
		file.close();
	}
};

//--------------------------------------------------------------------------
//Функция для меню
void menu()
{
	std::cout << "1. Заполнить таблицу \n";
	std::cout << "2. Ввести таблицу в файл \n";
	std::cout << "3. Считать таблицу из файла \n";
	std::cout << "4. Выход \n";
}

int checkFile(const std::string& filename)
{
	std::ifstream file(filename);
	if (!file.is_open())
	{
		std::cout << "Ошибка открытия файла..." << std::endl;
	}
	int count = 0;
	std::string tmp;
	while (std::getline(file, tmp))
	{
		count++;
	}
	file.close();
	return count;
}
