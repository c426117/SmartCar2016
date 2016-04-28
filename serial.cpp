#include "serial.h"

void serial_init (QString com)
{
    HANDLE hcomf;

    hcomf = CreateFile(com, GENERIC_READ,0,NULL, OPEN_EXISTING, FILE_ATTRIBUTE_ARCHIVE ,NULL);
    if (hcomf == INVALID_HANDLE_VALUE)
    {
        CloseHandle(hcomf);
        cout << "shibai"<<endl;
        return false;
    }


}
