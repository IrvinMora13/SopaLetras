#include "fileIO.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;


vector<string> readFile(const string& filename)
{
    ifstream file(filename);
    vector<string> words;
    string word;

    if (file.is_open())
    {
        while (file >> word)
        {
            words.push_back(word);
        }
        file.close();
    }
    else
    {
        cout << "No se pudo abrir el archivo." << endl;
    }

    return words;
}

void writeFile(const string& filename, const vector<string>& words)
{
    ofstream file(filename);

    if (file.is_open())
    {
        for (const auto& word : words)
        {
            file << word << endl;
        }
        file.close();
    }
    else
    {
        cout << "No se pudo abrir el archivo." << endl;
    }
}
