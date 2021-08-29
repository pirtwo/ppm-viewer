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

        _id = id;
        _w = std::stoi(w);
        _h = std::stoi(h);
        _cc = std::stoi(cc);
        ifs.get(); // skip 0x0A

        while (ifs.good())
        {
            Pixel pixel;
            pixel.r = ifs.get();
            pixel.g = ifs.get();
            pixel.b = ifs.get();
            _data.push_back(pixel);
        }

        return true;
    }
    catch (const std::exception &e)
    {
        return false;
    }
}

int PPM::getWidth()
{
    return _w;
}

int PPM::getHeight()
{
    return _h;
}

int PPM::getColorComponent()
{
    return _cc;
}

bool PPM::load(const char *path)
{
    _id = "";
    _w = 0;
    _h = 0;
    _cc = 0;
    _data.clear();
    return decoder(path);
}

void PPM::print(float scaleX, float scaleY, bool invertColor)
{
    int ssx = _w / (_w * scaleX); // sample size x
    int ssy = _h / (_h * scaleY); // sample size y

    for (int y = 0; y < _h; y++)
    {
        if (y % ssy > 0)
            continue;

        for (int x = 0; x < _w; x++)
        {
            if (x % ssx > 0)
                continue;

            int idx = y * _w + x;
            int sum = _data[idx].r + _data[idx].g + _data[idx].b;

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

std::optional<Pixel> PPM::getPixel(int index)
{
    return (index < 0 || index >= _w * _h)
               ? std::nullopt
               : std::optional<Pixel>(_data[index]);
}
