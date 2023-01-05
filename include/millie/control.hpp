#include "main.h"

using namespace std;
using namespace pros;

namespace driver {

    #define MACRO_COOLDOWN 375

    extern Controller master;

    extern int macroCooldown;
    extern int direction;

    void changeDirection(int newDirection);
    void cd(int increment);
    void rm();

};

namespace programming {

    #define TOTAL_ROUTINES 2

    extern int routine;

    void runAutonomous();

};

namespace brainScreen {

    #define BRAIN_UPDATE_CD 50

    extern int brainCD;

   void leftButton();
   void centerButton();
   void rightButton();
   void init();
   void rb();
   void cd(int increment);
   void update();

};