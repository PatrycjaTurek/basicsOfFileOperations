
#include "stdafx.h"

void readData(std::string fileName, std::vector<std::string> &dataVector)
{
    std::ifstream myFile;
    myFile.open(fileName, std::ios::in); // file with name fileName, read only
    if (!myFile.is_open())
    {
        return;
    }

    std::string tmpString; // temporary variable to take whole line
    while (!myFile.eof()) // if end of file
    {
       getline(myFile, tmpString,' ');
       dataVector.push_back(tmpString);
    }
    myFile.close();
    int i;
};

void writeData(std::string fileName, std::vector<std::string>& dataVector)
{
    std::ofstream myFile;
    myFile.open(fileName, std::ios::trunc); //  delete all data from file fileName, file with dataVector content,
    if (!myFile.is_open())
    {
        return;
    }

    for(int i = 0; i< dataVector.size(); i++)
    {
        myFile << dataVector[i];
        myFile << " ";
    }
    myFile.close();
    int i;
}

void makeDir(std::string dirName)
{
    std::wstring stemp = std::wstring(dirName.begin(), dirName.end()); //nedded to conver string to LPCWSTR type variable
    LPCWSTR sw = stemp.c_str();

    CreateDirectory(sw, NULL); // make directory if it doesnt exist
}

bool copyFile( std::string originalFileName, std::string dirName, std::string new_FileName)
{
    std::ifstream original(originalFileName);

    makeDir(dirName);

    std::string path = dirName + '/' + new_FileName;
    std::ofstream newFile(path, std::ios::binary); 

    if (!original.is_open() || !newFile.is_open() )
    {
        return true;
    }
    newFile << original.rdbuf(); //copy entire source file
    newFile.close();
    original.close();
    return false;
}

bool copyFile(std::string originalFileName, std::string dirName) // polymorphism example, copy file but doesnt change name of file
{
    std::ifstream original(originalFileName); //binary beacuse of rdbuf few lines below

    makeDir(dirName);
    std::string path = dirName + '/' + originalFileName;
    std::ofstream newFile(path, std::ios::binary);

    if (!original.is_open() || !newFile.is_open())
    {
        return true;
    }
    newFile << original.rdbuf(); //copy entire source file
    newFile.close();
    original.close();
    return false;
}

int main()
{
    std::vector<std::string> wholeData;
    wholeData.clear();

    readData("basicFile.txt", wholeData);
    writeData("basicFileRewrited.txt", wholeData);
    
    while (!wholeData.empty())
    {
        wholeData.pop_back();
    }

    if(copyFile("basicFile.txt", "../CopiedFiles","CHUJ.txt"))
    {
        std::cout << " error occured during copying file\n";
        Sleep(1000); //to be able to see error
        return 1;
    }
    int i;
    if (copyFile("basicFile.txt", "../CopiedFiles"))
    {
        std::cout << " error occured during copying file\n";
        Sleep(1000); //to be able to see error
        return 1;
    }
    
  

    return 0;
}
