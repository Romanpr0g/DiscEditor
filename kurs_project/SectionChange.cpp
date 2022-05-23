#include "MyFunction.h"

void SectionChange()
{
	bool w = true;
	char* path, * name = (char*)calloc(1, 1);
	PARTITION_INFORMATION_EX info;
	DWORD byteRe;

	while (w)
	{
		system("cls");
		cout << "Введите название диска(Заглавную букву): " << endl;

		cin >> name;

		if (name[0] >= 65 && name[0] <= 90)
		{
			path = new char[10];
			strcpy(path, Wstr);
			strcat(path, name);
			strcat(path, endStr);
			w = false;
		}
		else
		{
			system("cls");
			cout << "Попробуйте ввести еще раз..." << endl;
			Sleep(2000);
		}
	}

	HANDLE hDisk = CreateFile(path,
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL, OPEN_EXISTING,
		FILE_FLAG_RANDOM_ACCESS,
		NULL);

	if (hDisk == INVALID_HANDLE_VALUE)
	{
		cout << "Error" << endl;
		CloseHandle(hDisk);
		return;
	}

	if (!DeviceIoControl(hDisk, IOCTL_DISK_GET_PARTITION_INFO_EX, NULL, 0, &info, sizeof(PARTITION_INFORMATION_EX), &byteRe, (LPOVERLAPPED)NULL))
	{
		cout << "Error" << endl;
		return;
	}

	system("cls");
	cout << "Отрицательное число уменьшит раздел." << endl << "Положительное увеличит размер раздела, если есть неразмеченное пространство." << endl;
	cout << "После изменения размера, нужно форматировать рздел для дальнейшего нормального использования." << endl;
	cout << "Введите значение, на которое хотите уменьшить или увеличить раздел: " << endl;
	LARGE_INTEGER change;
	cin >> change.QuadPart;
	system("cls");

	_DISK_GROW_PARTITION size;
	size.PartitionNumber = info.PartitionNumber;
	size.BytesToGrow = change;

	if (!DeviceIoControl(hDisk, IOCTL_DISK_GROW_PARTITION, &size, sizeof(size), NULL, NULL, NULL, NULL))
	{
		cout << "Error" << endl;
		CloseHandle(hDisk);
	}
	return;
}
