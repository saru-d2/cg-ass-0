#include "main.h"

class Texture
{
public:
    /* data */
    int m_width, m_height, m_bpp;
    char * m_Localbuffer;
    // int texture;
    std::string m_filepath;
    Texture(const std::string &path);

    void bind(int slot = 0);
    void unBind ();
};

