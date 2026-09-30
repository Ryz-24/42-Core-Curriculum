#include <iostream>

int main(int argc, char **argv)
{
    std::string msg = "* LOUD AND UNBEARABLE FEEDBACK NOISE *";

    if (argc == 1)
        std::cout << msg;
    else
    {
        int i = 1;
        while(i < argc)
        {
            int j = 0;
            while(argv[i][j])
            {
                std::cout << (char)toupper(argv[i][j]);
                j++;
            }
            i++;
        }
    }
    std::cout << std::endl;
    return (0);
}
