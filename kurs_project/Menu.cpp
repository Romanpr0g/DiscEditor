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

		cout << "1 - ���������� � ������� �����." << endl;
		cout << "2 - ���������� � �������� �����." << endl;
		cout << "3 - ��������� ������� ������� �����." << endl;
		cout << "4 - �����." << endl;

		cin >> menu;

		switch (menu)
		{
		case 1:
			system("cls");
			Print_PhisicalDrive(PhysDrive);
			cout << "��� ����������� ������� ����� �������..." << endl;
			_getch();
			break;
		case 2:
			system("cls");
			disk.Print_Info();
			cout << "��� ����������� ������� ����� �������..." << endl;
			_getch();
			break;
		case 3:
			system("cls");
			SectionChange();
			cout << "��� ����������� ������� ����� �������..." << endl;
			_getch();
			break;
		case 4:
			return;
			break;
		default:
			system("cls");
			cout << "�������� ���� ����!" << endl;
			break;
		}
	}
}