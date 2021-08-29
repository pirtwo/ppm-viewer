#ifndef PPM_H_INCLUDE
#define PPM_H_INCLUDE

#include <string>
#include <vector>
#include <optional>

struct Pixel
{
    Pixel() : r(0), g(0), b(0) {}
    unsigned char r, g, b;
};

class PPM
{
protected:
    bool encoder();

    bool decoder(const char *path);

    std::string _id;          // PPM magic identifier
    int _w;                   // PPM image width
    int _h;                   // PPM image height
    int _cc;                  // PPM max colour component per pixel
    std::vector<Pixel> _data; // PPM image data

public:
    enum class PrintMode
    {
        CHAR,
        SHADE,
        COLOR
    };

    PPM();

    bool load(const char *path);

    void print(float scaleX = 1, float scaleY = 1, PrintMode mode = PrintMode::SHADE);

    int getSize();

    int getWidth();

    int getHeight();

    int getColorComponent();

    std::optional<Pixel> getPixel(int index);
};

#endif