#include "MyFunction.h"

void Print_PhisicalDrive(const char* drive)
{
    setlocale(LC_CTYPE, "rus");
    // Сведения о геометрии диска, на котором расположен раздел.
    DISK_GEOMETRY diskGeometry = { 0 };

    // Буфер для чтения.
    BYTE* buffer = NULL;

    // Количество возвращенных байт.
    DWORD bytesReturned = 0;

    //Дескриптор устройсва 
    HANDLE partition = CreateFile("\\\\.\\PHYSICALDRIVE1",
        GENERIC_READ,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL,
        OPEN_EXISTING,
        0,
        NULL);

    // Открываем физический диск.
    if (partition == INVALID_HANDLE_VALUE)
    {
        cout << "Error: " << GetLastError() << endl;

        return;
    }

    // Запрашиваем сведения о геометрии диска, на котором расположен раздел.
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

    cout << "Объем жесткого диска: \t\t" << (diskGeometry.Cylinders.QuadPart) *
        diskGeometry.TracksPerCylinder * diskGeometry.SectorsPerTrack *
        diskGeometry.BytesPerSector << " b" << endl;
    cout << "Количество цилиндров: \t\t" << diskGeometry.Cylinders.QuadPart << endl;
    cout << "Количество дорожек на цилинд: \t" << diskGeometry.TracksPerCylinder << endl;
    cout << "Количество секторов на дорожку: " << diskGeometry.SectorsPerTrack << endl;
    cout << "Байт в секторе: \t\t" << diskGeometry.BytesPerSector << endl << endl << endl;
    CloseHandle(partition);

    return;
}