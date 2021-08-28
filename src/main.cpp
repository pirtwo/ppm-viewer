#include "PPM.h"
#include <iostream>
#include <string>
#include <memory>

int main(int argc, char **argv)
{
    std::string path = "";
    float scaleX = 1;
    float scaleY = 1;
    bool invertColor = false;

    for (int i = 1; i < argc; i++)
    {
        std::string arg(argv[i]);

        if (arg.substr(0, 7) == "--path=")
        {
            path = arg.substr(7);
            if (path == "")
            {
                std::cout << "error! invalid path value. (use --help to see usage info) \r\n";
                return EXIT_SUCCESS;
            }
        }
        if (arg.substr(0, 5) == "--sx=")
        {
            scaleX = std::stof(arg.substr(5));
            if (scaleX < 0 || scaleX > 1)
            {
                std::cout << "error! invalid scale value. (use --help to see usage info) \r\n";
                return EXIT_SUCCESS;
            }
        }
        if (arg.substr(0, 5) == "--sy=")
        {
            scaleY = std::stof(arg.substr(5));
            if (scaleY < 0 || scaleY > 1)
            {
                std::cout << "error! invalid scale value. (use --help to see usage info) \r\n";
                return EXIT_SUCCESS;
            }
        }
        if (arg == "--ic")
        {
            invertColor = true;
        }
        if (arg == "--help")
        {
            std::cout << "PPM image viewer \r\n";
            std::cout << "Usage: --path=[path] [args] \r\n";
            std::cout << "Optional arguments list: \r\n";
            std::cout << "  --sx=[0,1]     scale value of x (must be between 0 and 1), default value is 1 \r\n";
            std::cout << "  --sy=[0,1]     scale value of y (must be between 0 and 1), default value is 1 \r\n";
            std::cout << "  --ic           invert color mode \r\n";
            std::cout << "  --help         display help \r\n";
            return EXIT_SUCCESS;
        }
    }

    auto img = std::make_shared<PPM>();
    if (path == "" || !img->load(path.c_str()))
        printf("error! invalid image format or path. (use --help to see usage info) \r\n");
    else
    {
        printf("path:%s | width:%d | height:%d | colour components:%d \r\n",
               path.c_str(), img->w, img->h, img->cc);
        img->view(scaleX, scaleY, invertColor);
    }

    return EXIT_SUCCESS;
}