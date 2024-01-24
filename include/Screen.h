#ifndef SCREEN_H
#define SCREEN_H

// Include any necessary libraries or headers here

// Declare your class and its member functions here
class Screen {
    public:
        void updateLCD();
        void printHeader(int lcdHeight, int volume);
        void homeScreen();
        void welcome();
        void blink();
        void openEyes();
};

#endif
