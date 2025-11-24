#include "irrKlang.h"
using namespace irrklang;
int main()
{
    ISoundEngine* engine = createIrrKlangDevice();
    if (!engine) {
        return 0;

    }

    engine->play2D("media/getout.ogg", true);
    while (true) {

    }
    engine->drop();

}