#include "PPM.h"
#include <iostream>
#include <bitset>
#include <memory>
#include <fstream>

auto shader = [](const Pixel &p, int cc, PPM::PrintMode mode)
{
    unsigned char chars[] =
        {'#', '@', '$', '.', ' '};

    unsigned char shades[] =
        {0xDB, 0xB2, 0xB1, 0xB0, 0x20};

    int idx = (p.r + p.g + p.b) / ((cc * 3) / 5);

    switch (mode)
    {
    case PPM::PrintMode::CHAR:
        std::cout << chars[idx];
        break;
    case PPM::PrintMode::SHADE:
        std::cout << shades[idx];
        break;
    default:
        std::cout << '?';
        break;
    }
};

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

void PPM::print(float scaleX, float scaleY, PrintMode mode)
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
            shader(_data[idx], _cc, mode);
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
