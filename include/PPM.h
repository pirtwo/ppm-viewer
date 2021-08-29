#ifndef PPM_H_INCLUDE
#define PPM_H_INCLUDE

#include <string>
#include <vector>

struct RGB
{
    RGB() : r(0), g(0), b(0) {}
    unsigned char r, g, b;
};

class PPM
{
protected:
    bool encoder();
    bool decoder(const char *path);

public:
    PPM();

    bool load(const char *path);

    void view(float scaleX = 1, float scaleY = 1, bool invertColor = false);

    std::string id;        // PPM magic identifier
    int w;                 // PPM image width
    int h;                 // PPM image height
    int cc;                // PPM max colour component per pixel
    std::vector<RGB> data; // PPM image data
};

#endif