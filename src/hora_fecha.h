#include <iostream> 
#include <ctime>
#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

void showDateTime()
{
    time_t now = time(0);
    tm *localTime = localTime(&now);
    cout << "╔════════════════════════════════════╗\n";
    cout << "║ Date :";

    cout << localTime->tm_mday << "/"
         << localTime->tm_mon + 1 << "/"
         << localTime->tm_year + 1900 << "                   ║";
    cout << "\n║ Time : ";

    if (localTime->tm_hour < 10)
        cout << "0";
    cout << localTime->tm_hour << ":";
    if (localTime->tm_min < 10)
        cout << "0";
    cout << localTime->tm_min << ":";
    if (localTime->tm_sec < 10)
        cout << "0";
    cout << localTime->tm_sec << "                    ║" << endl;
    cout << "╚════════════════════════════════════╝\n";
}

int main()
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    while (true)
    {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
        showDateTime();
#ifdef _WIN32
        Sleeep(1000);
#else
        sleep(1);
#endif
    }

    return 0;
}
