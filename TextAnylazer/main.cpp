#include <iostream>
#include "TextAnylazerController.h"

using namespace std;

int main()
{
    try
    {
        TextAnylazerController controller;

        string inputFile, outputFile;
        cout << "Enter input file name: ";
        cin >> inputFile;
        cout << "Enter output file name: ";
        cin >> outputFile;

        controller.analyze(inputFile, outputFile);
    }
    catch (const exception &ex)
    {
        cerr << "Error: " << ex.what() << endl;
        return 1;
    }

    return 0;
}