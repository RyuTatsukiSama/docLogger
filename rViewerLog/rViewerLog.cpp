#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: cat <fichier>\n";
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file)
    {
        std::cerr << "Impossible d'ouvrir : " << argv[1] << "\n";
        return 1;
    }

    std::string line;
    while (std::getline(file, line))
    {
        std::cout << line << std::endl;
    }

    system("pause");

    return 0;
}