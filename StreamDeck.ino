/* Pro Micro Test Code
   by: Nathan Seidle
   modified by: Jim Lindblom
   SparkFun Electronics
   date: September 16, 2013
   license: Public Domain - please use this code however you'd like.
   It's provided as a learning tool.

   This code is provided to show how to control the SparkFun
   ProMicro's TX and RX LEDs within a sketch. It also serves
   to explain the difference between Serial.print() and
   Serial1.print().
*/

#include <Keyboard.h> // The main library for sending keystrokes.

int RXLED = 17;  // The RX LED has a defined Arduino pin
// Note: The TX LED was not so lucky, we'll need to use pre-defined
// macros (TXLED1, TXLED0) to control that.
// (We could use the same macros for the RX LED too -- RXLED1,
//  and RXLED0.)

// Pins 2-5 are the pins we will use to poll the button matrix
int pollPins[4] = {2, 3, 4, 5};

// Pins 18-21 are the pins we will use to read the button matrix
int readPins[4] = {21, 20, 19, 18};
int lastrow = 255, lastcol = 255;

// {KeyCount, PreventRepeat, [Keys]}

//Premiere Editing Macros
/*
char PAD_KEY_1[] = {3, 1, KEY_LEFT_CTRL, KEY_LEFT_SHIFT, 'k'};
char PAD_KEY_2[] = {2, 1, KEY_LEFT_CTRL, 'r'};
char PAD_KEY_3[] = {2, 1, KEY_LEFT_CTRL, 'c'};
char PAD_KEY_4[] = {2, 1, KEY_LEFT_SHIFT, KEY_DELETE};
char PAD_KEY_5[] = {1, 1, 'j'};
char PAD_KEY_6[] = {1, 1, 'k'};
char PAD_KEY_7[] = {1, 1, 'l'};
char PAD_KEY_8[] = {2, 1, KEY_LEFT_CTRL, 'z'};
char PAD_KEY_9[] = {2, 0, KEY_LEFT_SHIFT, KEY_LEFT_ARROW};
char PAD_KEY_10[] = {1, 1, ' '};
char PAD_KEY_11[] = {2, 0, KEY_LEFT_SHIFT, KEY_RIGHT_ARROW};
char PAD_KEY_12[] = {0};
char PAD_KEY_13[] = {0};
char PAD_KEY_14[] = {0};
char PAD_KEY_15[] = {0};
char PAD_KEY_16[] = {0};
*/

char PAD_KEY_1[] = {3, 1, KEY_LEFT_CTRL, KEY_LEFT_SHIFT, KEY_F1};
char PAD_KEY_2[] = {3, 1, KEY_LEFT_CTRL, KEY_LEFT_SHIFT, KEY_F2};
char PAD_KEY_3[] = {3, 1, KEY_LEFT_CTRL, KEY_LEFT_SHIFT, KEY_F3};
char PAD_KEY_4[] = {3, 1, KEY_LEFT_CTRL, KEY_LEFT_SHIFT, KEY_F4};

char PAD_KEY_5[] = {3, 1, KEY_LEFT_CTRL, KEY_LEFT_SHIFT, KEY_F5};
char PAD_KEY_6[] = {3, 1, KEY_LEFT_CTRL, KEY_LEFT_SHIFT, KEY_F6};
char PAD_KEY_7[] = {3, 1, KEY_LEFT_CTRL, KEY_LEFT_SHIFT, KEY_F7};
char PAD_KEY_8[] = {3, 1, KEY_LEFT_CTRL, KEY_LEFT_SHIFT, KEY_F8};

char PAD_KEY_9[] = {3, 1, KEY_LEFT_CTRL, KEY_LEFT_SHIFT, KEY_F9};
char PAD_KEY_10[] = {3, 1, KEY_LEFT_CTRL, KEY_LEFT_SHIFT, KEY_F10};
char PAD_KEY_11[] = {3, 1, KEY_LEFT_CTRL, KEY_LEFT_SHIFT, KEY_F11};
char PAD_KEY_12[] = {3, 1, KEY_LEFT_CTRL, KEY_LEFT_SHIFT, KEY_F12};

char PAD_KEY_13[] = {3, 1, KEY_LEFT_CTRL, KEY_LEFT_SHIFT, KEY_F13};
char PAD_KEY_14[] = {3, 1, KEY_LEFT_CTRL, KEY_LEFT_SHIFT, KEY_F14};
char PAD_KEY_15[] = {3, 1, KEY_LEFT_CTRL, KEY_LEFT_SHIFT, KEY_F15};
char PAD_KEY_16[] = {3, 1, KEY_LEFT_CTRL, KEY_LEFT_SHIFT, KEY_F16};

// Array of key values CTRL + SHIFT + <KEY>
char *keyLookup[16] = {
                        PAD_KEY_1, PAD_KEY_2, PAD_KEY_3, PAD_KEY_4,
                        PAD_KEY_5, PAD_KEY_6, PAD_KEY_7, PAD_KEY_8,
                        PAD_KEY_9, PAD_KEY_10, PAD_KEY_11, PAD_KEY_12,
                        PAD_KEY_13, PAD_KEY_14, PAD_KEY_15, PAD_KEY_16
                    };

void setup()
{
  pinMode(RXLED, OUTPUT);  // Set RX LED as an output

//  Serial.begin(9600); //This pipes to the serial monitor
//  Serial.println("Initialize Serial Monitor");

  for(int i=0; i<4; i++)
  {
    pinMode(pollPins[i], OUTPUT);
    digitalWrite(pollPins[i], LOW);
    pinMode(readPins[i], INPUT);
  }

  //Keyboard.begin();
}

void loop()
{
  readMatrix();
  delay(10);
}

void readMatrix()
{
  bool keyread=false;
  
  for(int r=0; r<4; r++)
  {
    //Set the pin high
    digitalWrite(pollPins[r], HIGH);

    //Read the values
    for(int c=0; c<4; c++)
    {
        if(digitalRead(readPins[c]))
        {
          handleKeypress(r,c);
          keyread=true;
          break;
        }
    }
    
    //Reset the pin low
    digitalWrite(pollPins[r], LOW);
  }

  if(!keyread)
  {
    lastcol = 255;
    lastrow = 255;
  }
}

void handleKeypress(int row, int col)
{

    char* keys = keyLookup[(row*4)+col];
    if(keys[0]>0 && keys[1]==1 && lastrow == row && lastcol == col) return;

    lastrow = row;
    lastcol = col;
    
    for(int c=0; c<keys[0]; c++)
    {
      Keyboard.press(keys[c+2]);
    }    
    delay(100);
    Keyboard.releaseAll();
}
