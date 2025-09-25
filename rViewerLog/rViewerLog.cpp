#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char *argv[])
{
    if (argc < 2) // Make sur there is only on parameter
    {
        std::cerr << "Usage: cat <fichier>\n";
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file) // make sure the argument is a file, and try to pen it
    {
        std::cerr << "Impossible d'ouvrir : " << argv[1] << "\n";
        return 1;
    }

    std::string line;
    while (std::getline(file, line))
    {
        std::cout << line << std::endl; // display all the line of the files into the console
    }

    system("pause");

    return 0;
}