#include "Header.h"
int main()
{
	int variant;
	setlocale(LC_CTYPE, "rus");
	menu();
	std::cin >> variant;
	if (variant == 1)
	{
		system("cls");
		int count;
		std::cout << "������� ���������� ��������� ��� ������� \n";
		if (std::cin >> count)
		{
			while (true)
			{
				HashTable ht(count);
				ht.fromKeyboard(count);
				ht.printTable();
				while (true)
				{
					std::cout << "1. ������� ������� \n";
					std::cout << "2. ����� ������� \n";
					std::cout << "3. ����� \n";
					std::cout << "> ";
					int n;
					while (!(std::cin >> n) || (n > 3))
					{
						std::cout << "\033[0;31m������ �����... ���������� �����.\033[0m\n";
						std::cout << "> ";
						std::cin.clear();
						std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					}

					if (n == 1)
					{
						std::string country, city, street;
						int house;
						std::cout << "������� ������, ������� ������ ������� \n";
						std::cout << "������: ";
						std::cin >> country;
						std::cout << "�����: ";
						std::cin >> city;
						std::cout << "�����: ";
						std::cin >> street;
						std::cout << "����� ����: ";
						std::cin >> house;

						Address addressToDelete(country, city, street, house);
						bool removed = ht.remove(addressToDelete);
						if (!removed) 
						{
							std::cout << "\033[0;31m����� ������ ��� \033[0m\n";
						}
						ht.printTable();
					}
					if (n == 2)
					{
						std::string country, city, street;
						int house;
						std::cout << "������� ������, ������� ������ ����� \n";
						std::cout << "������: ";
						std::cin >> country;
						std::cout << "�����: ";
						std::cin >> city;
						std::cout << "�����: ";
						std::cin >> street;
						std::cout << "����� ����: ";
						std::cin >> house;
						Address addressToFind(country, city, street, house);
						TreeNode* foundNode = ht.search(addressToFind);
						if (foundNode)
						{
							std::cout << "\033[0;32m����� ������: \033[0m" << foundNode->address.toString() << std::endl;
						}
						else
						{
							std::cout << "\033[0;31m����� �� ������.\033[0m" << std::endl;
						}
					}
					if (n == 3)
					{
						exit(0);
					}
				}
			}
		}
		else
		{
			std::cout << "\033[0;31m������ �����... ���������� �����.\033[0m\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	}
	if (variant == 2)
	{
		system("cls");
		int count;
		std::cout << "������� ���������� ��������� ��� ������� \n";
		if (std::cin >> count)
		{
			while (true)
			{
				HashTable ht(count);
				ht.fromKeyboard(count);
				ht.saveToFile("file.txt");
				break;
			}
		}
		else
		{
			std::cout << "������ �����... ���������� �����.\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	}
	if (variant == 3)
	{
		system("cls");
		HashTable ht(checkFile("file.txt"));
		ht.readFromFile("file.txt");
		ht.printTable();
		while (true)
		{
			std::cout << "1. ������� ������� \n";
			std::cout << "2. ����� ������� \n";
			std::cout << "3. ����� \n";
			std::cout << "> ";
			int n;
			while (!(std::cin >> n) || (n > 3))
			{
				std::cout << "\033[0;31m������ �����... ���������� �����.\033[0m\n";
				std::cout << "> ";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}

			if (n == 1)
			{
				std::string country, city, street;
				int house;
				std::cout << "������� ������, ������� ������ ������� \n";
				std::cout << "������: ";
				std::cin >> country;
				std::cout << "�����: ";
				std::cin >> city;
				std::cout << "�����: ";
				std::cin >> street;
				std::cout << "����� ����: ";
				std::cin >> house;

				Address addressToDelete(country, city, street, house);
				bool removed = ht.remove(addressToDelete);
				if (!removed)
				{
					std::cout << "\033[0;31m����� ������ ��� \033[0m\n";
				}
				ht.printTable();
			}
			if (n == 2)
			{
				std::string country, city, street;
				int house;
				std::cout << "������� ������, ������� ������ ����� \n";
				std::cout << "������: ";
				std::cin >> country;
				std::cout << "�����: ";
				std::cin >> city;
				std::cout << "�����: ";
				std::cin >> street;
				std::cout << "����� ����: ";
				std::cin >> house;
				Address addressToFind(country, city, street, house);
				TreeNode* foundNode = ht.search(addressToFind);
				if (foundNode)
				{
					std::cout << "\033[0;32m����� ������: \033[0m" << foundNode->address.toString() << std::endl;
				}
				else
				{
					std::cout << "\033[0;31m����� �� ������.\033[0m" << std::endl;
				}
			}
			if (n == 3)
			{
				exit(0);
			}
		}
	}
	else
	{
		exit(0);
	} 
	return 0; 
}