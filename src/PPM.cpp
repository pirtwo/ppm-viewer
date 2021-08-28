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
    std::string w, h, cc;
    std::ifstream ifs(
        path, std::ifstream::in | std::ifstream::ate | std::ifstream::binary);

    if (!ifs.is_open())
        return false;

    int size = ifs.tellg();
    ifs.seekg(0, ifs.beg);

    if (size == 0)
        return false;

    auto buffer = std::shared_ptr<unsigned char[]>(
        new unsigned char[size]);

    ifs.read((char *)&buffer[0], size);
    ifs.close();

    int sector = 0;
    for (int i = 0; i < size; i++)
    {
        auto token = buffer[i];

        // skip comments
        if (token == 0x23)
        {
            while (i < size)
            {
                i++;
                if (buffer[i] == 0x0A)
                    break;
            }
            continue;
        }

        if (sector < 4)
        {
            if (token == 0x0A || token == 0x20)
            {
                sector++;
                continue;
            }

            switch (sector)
            {
            case 0:
                this->id += token;
                break;
            case 1:
                w += token;
                break;
            case 2:
                h += token;
                break;
            case 3:
                cc += token;
                break;
            default:
                break;
            }
        }
        else
        {
            data.push_back(token);
        }
    }

    this->w = std::atoi(w.c_str());
    this->h = std::atoi(h.c_str());
    this->cc = std::atoi(cc.c_str());

    return true;
}

bool PPM::load(const char *path)
{
    data.clear();
    return decoder(path);
}

void PPM::view(float scaleX, float scaleY, bool invertColor)
{
    unsigned char r, g, b;      // rgb channels
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

            int byteIdx = y * w * 3 + x * 3;

            r = data[byteIdx];
            g = data[byteIdx + 1];
            b = data[byteIdx + 2];
            int sum = r + g + b;

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