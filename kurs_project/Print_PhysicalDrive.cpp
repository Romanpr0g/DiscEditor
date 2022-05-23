#include "MyFunction.h"

void Print_PhisicalDrive(const char* drive)
{
    setlocale(LC_CTYPE, "rus");
    // �������� � ��������� �����, �� ������� ���������� ������.
    DISK_GEOMETRY diskGeometry = { 0 };

    // ����� ��� ������.
    BYTE* buffer = NULL;

    // ���������� ������������ ����.
    DWORD bytesReturned = 0;

    //���������� ��������� 
    HANDLE partition = CreateFile("\\\\.\\PHYSICALDRIVE1",
        GENERIC_READ,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL,
        OPEN_EXISTING,
        0,
        NULL);

    // ��������� ���������� ����.
    if (partition == INVALID_HANDLE_VALUE)
    {
        cout << "Error: " << GetLastError() << endl;

        return;
    }

    // ����������� �������� � ��������� �����, �� ������� ���������� ������.
    if (!DeviceIoControl(partition,
        IOCTL_DISK_GET_DRIVE_GEOMETRY,
        NULL,
        0,
        &diskGeometry,
        sizeof(DISK_GEOMETRY),
        &bytesReturned,
        NULL))
    {
        cout << "Error: " << GetLastError() << endl;
        CloseHandle(partition);

        return;
    }

    cout << "����� �������� �����: \t\t" << (diskGeometry.Cylinders.QuadPart) *
        diskGeometry.TracksPerCylinder * diskGeometry.SectorsPerTrack *
        diskGeometry.BytesPerSector << " b" << endl;
    cout << "���������� ���������: \t\t" << diskGeometry.Cylinders.QuadPart << endl;
    cout << "���������� ������� �� ������: \t" << diskGeometry.TracksPerCylinder << endl;
    cout << "���������� �������� �� �������: " << diskGeometry.SectorsPerTrack << endl;
    cout << "���� � �������: \t\t" << diskGeometry.BytesPerSector << endl << endl << endl;
    CloseHandle(partition);

    return;
}