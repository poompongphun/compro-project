// Import Library
#include <LiquidCrystal.h>

// rs (LCD pin 4) to Arduino pin 5
// rw (LCD pin 5) to Arduino pin 6
// enable (LCD pin 6) to Arduino pin 7
// LCD pins d4, d5, d6, d7 to Arduino pins 8, 9, 10, 11
LiquidCrystal lcd(5, 6, 7, 8, 9, 10, 11);
// LCD pin 15 to Arduino pin 4
int bl = 4;

// Buzzer Positive to pin 1
// Switch Common to pin 2
// Ultrasonic SIG to pin 3
int buzzer = 1, switchBtn = 2, ultrasonic = 3;

// Show "Off" Text State
int showOffAlr = 0;
long oldDistance = 0;

// All distance
int stop = 70, should = 95, tclose = 150, close = 200, gtclose = 300;

void setup()
{
    pinMode(buzzer, OUTPUT);
    pinMode(switchBtn, INPUT);

    pinMode(bl, OUTPUT);
    digitalWrite(bl, HIGH); // turn backlight on
    lcd.begin(16, 2);       // use 16 col and 2 row
    lcd.clear();            // start with a blank screen
    lcd.display();          // Turn on the display:
}

void loop()
{
    int sw = digitalRead(switchBtn); // Read switch state

    // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
    // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
    pinMode(ultrasonic, OUTPUT);
    digitalWrite(ultrasonic, LOW);
    delayMicroseconds(2);
    digitalWrite(ultrasonic, HIGH);
    delayMicroseconds(5);
    digitalWrite(ultrasonic, LOW);

    pinMode(ultrasonic, INPUT);

    if (sw == HIGH)
    {
        long cm = pulseIn(ultrasonic, HIGH) / 29 / 2; // convert the time into a distance (cm)
        showText(cm);                                 // Display Distance num, text
        beepSound(cm);                                // Beep Beep Sound up to distance

        showOffAlr = 0; // just set value to 0 for off state
    }
    else
    {
        if (showOffAlr == 0) // clear display if already show some text
            lcd.clear();

        // Show this text if switch state is off
        lcd.setCursor(6, 0);
        lcd.print("Off.");
        lcd.setCursor(1, 1);
        lcd.print("turn on switch");
        showOffAlr = 1;
    }

    delay(100);
}

void beepSound(long cm)
{
    int delayVal = beepDelay(cm); // get beep beep delay value
    tone(buzzer, 700);
    if (delayVal != 0) // if val is 0 then buzzer will not stop beepๆๆๆ
    {
        delay(delayVal);
        noTone(buzzer); // stop beep
        delay(delayVal);
    }
}

void showText(int cm)
{
    if (oldDistance != cm) // if distance not change then dont need to update display
    {

        lcd.clear(); // clear all text
        lcd.setCursor(0, 0);
        if (cm < 336) // Should be in range
        {
            // Row 1: Show Distance num
            lcd.print("Distance: ");
            lcd.print(cm);
            lcd.print(" cm");

            // Row 2: Show warning text
            lcd.setCursor(0, 1);
            if (cm <= stop)
                lcd.print("STOP!");
            else if (cm <= should)
                lcd.print("SHOULD STOP");
            else if (cm <= tclose)
                lcd.print("TOO CLOSE");
            else if (cm <= close)
                lcd.print("CLOSE");
            else if (cm <= gtclose)
                lcd.print("GETTING CLOSE");
            else
                lcd.print("NOT CLOSE");
        }
        else
            lcd.print("OUT OF RANGE");
    }
    oldDistance = cm;
}

int beepDelay(long cm)
{
    // return beep beep delay
    int milisec = 1000;
    if (cm <= stop)
        milisec = 0;
    else if (cm <= should)
        milisec = 75;
    else if (cm <= tclose)
        milisec = 150;
    else if (cm <= close)
        milisec = 300;
    else if (cm <= gtclose)
        milisec = 600;
    return milisec;
}