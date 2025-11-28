#include <iostream>
#include<string>
#include<iomanip>
using namespace std;
bool isrun(int n)
{
    if (n % 4 == 0 && n % 100 != 0 || n % 400 == 0)
        return true;
    else
        return false;
}
int main()
{
    int n;
    string weeks[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
    int weekday[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    while (cin >> n)
    {
        if (n == -1)
            return 0;
        int days = 0, month = 1, year = 2000;
        string week = weeks[(n + 5) % 7];
        while (n >= (isrun(year) ? 366 : 365))
        {
            n -= (isrun(year) ? 366 : 365);
            year++;
        }

        if (n == 366)
        {
            cout << year << "-12-31 " << week << endl;
        }
        else
        {
            while (n >= weekday[month])
            {
                n -= weekday[month];
                month++;
                if (month == 2 )
                {
                    if (isrun(year))
                        weekday[2] = 29;
                    else
                        weekday[2] = 28;
                }

            }
            cout << year << "-";
            cout << setfill('0') << setw(2) << month << "-";
            cout << setfill('0') << setw(2) << (n + 1) << " " << week << endl;
        }
    }
}