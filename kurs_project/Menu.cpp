#include "MyFunction.h"

void Menu()
{
	setlocale(LC_CTYPE, "rus");

	system("cls");

	while (true)
	{
		int menu;
		Disc disk;

		system("cls");

		cout << "1 - Информация о жестком диске." << endl;
		cout << "2 - Информация о разделах диска." << endl;
		cout << "3 - Изменение размера раздела диска." << endl;
		cout << "4 - Выход." << endl;

		cin >> menu;

		switch (menu)
		{
		case 1:
			system("cls");
			Print_PhisicalDrive(PhysDrive);
			cout << "Для продолжения нажмите любую клавишу..." << endl;
			_getch();
			break;
		case 2:
			system("cls");
			disk.Print_Info();
			cout << "Для продолжения нажмите любую клавишу..." << endl;
			_getch();
			break;
		case 3:
			system("cls");
			SectionChange();
			cout << "Для продолжения нажмите любую клавишу..." << endl;
			_getch();
			break;
		case 4:
			return;
			break;
		default:
			system("cls");
			cout << "Выберите пунк меню!" << endl;
			break;
		}
	}
}