#ifndef PPM_H_INCLUDE
#define PPM_H_INCLUDE

#include <string>
#include <vector>

class PPM
{
protected:
    bool encoder();
    bool decoder(const char *path);

public:
    PPM();

    bool load(const char *path);

    void view(float scaleX = 1, float scaleY = 1, bool invertColor = false);

    std::string id;                  // PPM magic identifier
    int w;                           // PPM image width
    int h;                           // PPM image height
    int cc;                          // PPM max colour component per pixel
    std::vector<unsigned char> data; // PPM image data
};

#endif