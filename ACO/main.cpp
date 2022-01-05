#include <iostream>
#include "DataReader.h"
#include "Test.h"
#include <conio.h>


int main()
{
    Test::runTest();
    cout << "\nWcisnij dowolny klawisz..." << endl;
    int znak = _getch();
    return 0;
}   
