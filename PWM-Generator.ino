#include <LiquidCrystal.h>
#include <CheapLCD.h>


LiquidCrystal lcd(8,9,4,5,6,7); 
CheapLCD cLcd;

int PWM_Pin = 3; /* give PWM_Pin name to D3 pin */

 int dutyCycle = 50;
 int period = 50;
 int increment = 10;

 char buf[40];
// Perform initialization inside setup()
void setup()
{
    pinMode(PWM_Pin,OUTPUT);  /*declare D3 pin as an output pin */ 
    cLcd.begin();

    cLcd.clear();
    cLcd.write("PWM GENERATOR");
    delay(1000);
    //cLcd.backlightOff();
    cLcd.clear();
    sprintf(buf, "PER: %d D/C: %d", period, dutyCycle);
    cLcd.write(buf);
}
// loop() executes continously 
void loop()
{
    analogWrite(PWM_Pin,dutyCycle);  /* Produce 50% duty cycle PWM on D3 */
    delay(period);

    static CLCD_Button_t lastButton = BTN_NONE;

  CLCD_Button_t   newReading = cLcd.readButton();

  if (newReading != lastButton) {   // button changed
    lastButton = newReading;
    //cLcd.clear();

    if (newReading != BTN_NONE) {   // button was pressed
      switch(newReading) {
        case BTN_RIGHT:
          //cLcd.write("Right");
          dutyCycle = dutyCycle + increment;
          break;
        case BTN_UP:
          //cLcd.write("Up");
          period = period + increment;
          break;
        case BTN_DOWN:
          //cLcd.write("Down");
          period = period - increment;
          break;
        case BTN_LEFT:
          //cLcd.write("Left");
          dutyCycle = dutyCycle - increment;
          break;
        case BTN_SELECT:
          //cLcd.write("Select");
          increment = (increment == 10) ? 1 : 10;
          
          break;
        default:
          //cLcd.write("ERROR");
          break;
      }
      cLcd.clear();
      sprintf(buf, "PER: %d D/C: %d", period, dutyCycle);
      cLcd.write(buf);
    }
  }

}
