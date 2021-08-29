#include "PPM.h"
#include <iostream>
#include <bitset>
#include <memory>
#include <fstream>

PPM::PPM()
{
    //
}

bool PPM::encoder()
{
    // TODO: implement encoder

    return true;
}

bool PPM::decoder(const char *path)
{
    std::string id, w, h, cc;
    int size = 0;

    try
    {
        std::ifstream ifs(
            path, std::ifstream::in | std::ifstream::ate | std::ifstream::binary);
        size = ifs.tellg();

        if (!ifs.is_open() || size == 0)
            return false;

        ifs.seekg(0, ifs.beg);

        ifs >> id >> w >> h >> cc;

        if (id != "P6")
            return false;

        this->id = id;
        this->w = std::stoi(w);
        this->h = std::stoi(h);
        this->cc = std::stoi(cc);
        ifs.get(); // skip 0x0A

        while (ifs.good())
        {
            RGB pixel;
            pixel.r = ifs.get();
            pixel.g = ifs.get();
            pixel.b = ifs.get();
            data.push_back(pixel);
        }

        return true;
    }
    catch (const std::exception &e)
    {
        return false;
    }
}

bool PPM::load(const char *path)
{
    data.clear();
    return decoder(path);
}

void PPM::view(float scaleX, float scaleY, bool invertColor)
{
    int ssx = w / (w * scaleX); // sample size x
    int ssy = h / (h * scaleY); // sample size y

    for (int y = 0; y < h; y++)
    {
        if (y % ssy > 0)
            continue;

        for (int x = 0; x < w; x++)
        {
            if (x % ssx > 0)
                continue;

            int idx = y * w + x;
            int sum = data[idx].r + data[idx].g + data[idx].b;

            if (!invertColor)
            {
                if (sum < 153)
                    std::cout << "\xDB";
                else if (sum < 306)
                    std::cout << "\xB2";
                else if (sum < 459)
                    std::cout << "\xB1";
                else if (sum < 612)
                    std::cout << "\xB0";
                else
                    std::cout << " ";
            }
            else
            {
                if (sum < 153)
                    std::cout << " ";
                else if (sum < 306)
                    std::cout << "\xB0";
                else if (sum < 459)
                    std::cout << "\xB1";
                else if (sum < 612)
                    std::cout << "\xB2";
                else
                    std::cout << "\xDB";
            }
        }
        std::cout << "\r\n";
    }

    std::cout << "\r\n";
}