#include "parsing.h"
#include <fstream>
#include "classes.cpp"
#include <string>

int main()
{
    fstream file;

    file.open("text.xml", ios::in); // open a file to perform read operation using file object

    string xmlText;
    if (file.is_open())
    {
        // checking whether the file is open
        string tp;
        while (getline(file, tp))
        {
            // read data from file object and put it into string.
            xmlText += tp + "\n"; // print the data of the string
        }
    }

    ProcessedFile f = parseXml(xmlText);

    return 0;
}