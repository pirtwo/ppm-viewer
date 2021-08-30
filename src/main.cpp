#include "PPM.h"
#include <iostream>
#include <string>
#include <memory>

int main(int argc, char **argv)
{
    std::string path = "";
    float scaleX = 1;
    float scaleY = 1;
    PPM::PrintMode mode = PPM::PrintMode::SHADE;

    try
    {
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
            if (arg.substr(0, 6) == "--mod=")
            {
                mode = static_cast<PPM::PrintMode>(std::stoi(arg.substr(6)));
                if (static_cast<int>(mode) < 0 || static_cast<int>(mode) > 2)
                {
                    std::cout << "error! invalid mode value. (use --help to see usage info) \r\n";
                    return EXIT_SUCCESS;
                }
            }
            if (arg == "--help")
            {
                std::cout << "PPM image viewer \r\n";
                std::cout << "Usage: --path=[path] [args] \r\n";
                std::cout << "Optional arguments list: \r\n";
                std::cout << "  --sx=[0,1]     scale value of x (must be between 0 and 1), default value is 1 \r\n";
                std::cout << "  --sy=[0,1]     scale value of y (must be between 0 and 1), default value is 1 \r\n";
                std::cout << "  --mod=[mode]   image display mode [0=char, 1=shade, 2=color], default value is 1 \r\n";
                std::cout << "                 shade mode requires encoding cyrillic-IBM855 \r\n";
                std::cout << "  --help         display help \r\n";
                return EXIT_SUCCESS;
            }
        }
    }
    catch (const std::exception &e)
    {
        std::cout << "error! invalid arg value. (use --help to see usage info) \r\n";
        return EXIT_SUCCESS;
    }

    auto img = std::make_shared<PPM>();
    if (path == "" || !img->load(path.c_str()))
        printf("error! invalid image format or path. (use --help to see usage info) \r\n");
    else
    {
        printf("path:%s | width:%d | height:%d | colour components:%d \r\n",
               path.c_str(), img->getWidth(), img->getHeight(), img->getColorComponent());
        img->print(scaleX, scaleY, mode);
    }

    return EXIT_SUCCESS;
}