#include "Disc.h"

Disc::Disc()
{
	int sz = GetLogicalDriveStrings(NULL, 0);
	TCHAR* szLogicalDrives = new TCHAR[sz];
	DiscsA = (char**)calloc(sz, sizeof(char*));
	DiscsW = (char**)calloc(sz, sizeof(char*));
	quntityDisks = 0;

	GetLogicalDriveStrings(sz, szLogicalDrives);

	while (*szLogicalDrives)
	{
		quntityDisks++;
		DiscsA[quntityDisks] = szLogicalDrives;
		szLogicalDrives += 4;
	}

	DiscW();
}

char** Disc::Get_DiscsA()
{
	return DiscsA;
}

int Disc::Get_Quntity()
{
	return quntityDisks;
}

void Disc::Print_Info()
{
	for (int i = 1; i <= quntityDisks; i++)
	{
		UINT uDriveType = GetDriveType(DiscsA[i]);

		if (uDriveType == DRIVE_FIXED)
		{
			HANDLE disk = NULL;
			PARTITION_INFORMATION_EX diskInfo;
			DWORD bytes = 0;

			if ((disk = CreateFile(DiscsW[i],
				GENERIC_READ,
				FILE_SHARE_READ | FILE_SHARE_WRITE,
				NULL,
				OPEN_EXISTING,
				0,
				NULL)) == INVALID_HANDLE_VALUE)
			{
				cout << "Error: " << DiscsW[i] << GetLastError() << endl;
				return;
			}
			if (!DeviceIoControl(disk,
				IOCTL_DISK_GET_PARTITION_INFO_EX,
				NULL,
				0,
				&diskInfo,
				sizeof(PARTITION_INFORMATION_EX),
				&bytes,
				(LPOVERLAPPED)NULL))
			{
				cout << "Error: " << DiscsW[i] << GetLastError() << endl;
				CloseHandle(disk);
				return;
			}

			char fileSystem[8];

			GetVolumeInformation(DiscsA[i], NULL, NULL, NULL, NULL, NULL, fileSystem, sizeof(fileSystem));

			cout << DiscsA[i] << endl;

			__int64 All_Size, Free_Size;

			GetDiskFreeSpaceEx(DiscsA[i], (PULARGE_INTEGER)&Free_Size, (PULARGE_INTEGER)&All_Size, NULL);

			cout << "Начальное смещение:\t" << diskInfo.StartingOffset.QuadPart << endl;

			cout << "Размер раздела:\t\t" << diskInfo.PartitionLength.QuadPart / (1024 * 1024 * 1024) << " Gb\t"
				<< diskInfo.PartitionLength.QuadPart / (1024 * 1024) << " Mb\t" << diskInfo.PartitionLength.QuadPart << " b" << endl;

			cout << "Доступно пользователю:\t" << All_Size / (1024 * 1024 * 1024) << " Gb\t"
				<< All_Size / (1024 * 1024) << " Mb\t" << All_Size << " b" << endl;

			cout << "Занято:\t\t\t" << (All_Size - Free_Size) / (1024 * 1024 * 1024) << " Gb\t"
				<< (All_Size - Free_Size) / (1024 * 1024) << " Mb\t" << All_Size - Free_Size << " b" << endl;

			cout << "Свободно:\t\t" << Free_Size / (1024 * 1024 * 1024) << " Gb\t"
				<< Free_Size / (1024 * 1024) << " Mb\t" << Free_Size << " b" << endl;

			cout << "Свободно:\t\t" << (Free_Size * 100) / All_Size << "%" << endl;

			cout << "Файловая система: \t" << fileSystem << endl;

			cout << endl << endl;
		}
	}
}

void Disc::DiscW()
{
	for (int i = 1; i <= quntityDisks; i++)
	{
		DiscsW[i] = new char[strlen(DiscsA[i]) + strlen(Wstr)];
		strcpy(DiscsW[i], Wstr);
		strcat(DiscsW[i], DiscsA[i]);
		int j = 0;
		while (DiscsW[i][j] != '\0')
		{
			j++;
		}
		DiscsW[i][j - 1] = '\0';
	}
}

__int64 Disc::GetSize(char* path)
{
	HANDLE disk;
	PARTITION_INFORMATION_EX diskInfo;
	DWORD bytes = 0;

	if ((disk = CreateFile(path,
		GENERIC_READ,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		OPEN_EXISTING,
		0,
		NULL)) == INVALID_HANDLE_VALUE)
	{
		cout << "Error: " << path << GetLastError() << endl;
	}
	if (!DeviceIoControl(disk,
		IOCTL_DISK_GET_PARTITION_INFO_EX,
		NULL,
		0,
		&diskInfo,
		sizeof(PARTITION_INFORMATION_EX),
		&bytes,
		(LPOVERLAPPED)NULL))
	{
		cout << "Error: " << path << GetLastError() << endl;
		CloseHandle(disk);
	}
	CloseHandle(disk);
	return diskInfo.PartitionLength.QuadPart;
}

char** Disc::Get_DiscsW()
{
	return DiscsW;
}

