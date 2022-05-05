#include <LiquidCrystal.h>

LiquidCrystal lcd(5, 6, 7, 8, 9, 10, 11);
int buzzer = 1, switchBtn = 2, ultrasonic = 3, bl = 4;
int showOffAlr = 0;

void setup()
{
    pinMode(buzzer, OUTPUT);
    pinMode(switchBtn, INPUT);
    pinMode(bl, OUTPUT);
    digitalWrite(bl, HIGH);
    lcd.begin(16, 2);
    lcd.clear();
    lcd.display();
}

void loop()
{
    int sw = digitalRead(switchBtn);

    pinMode(ultrasonic, OUTPUT);
    digitalWrite(ultrasonic, LOW);
    delayMicroseconds(2);
    digitalWrite(ultrasonic, HIGH);
    delayMicroseconds(5);
    digitalWrite(ultrasonic, LOW);

    pinMode(ultrasonic, INPUT);

    if (sw == HIGH)
    {
        long cm = pulseIn(ultrasonic, HIGH) / 29 / 2;
        showText(cm);
        beepSound(cm);
        showOffAlr = 0;
    }
    else
    {
        if (showOffAlr == 0)
            lcd.clear();
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
    int delayVal = beepDelay(cm);
    tone(buzzer, 700);
    delay(delayVal);
    if (delayVal != 0)
        noTone(buzzer);
    delay(delayVal);
}

void showText(int cm)
{
    lcd.clear();
    lcd.setCursor(0, 0);
    if (cm <= 336)
    {
        lcd.print("Distance: ");
        lcd.print(cm);
        lcd.print(" cm");
        lcd.setCursor(0, 1);
        if (cm <= 70)
        {
            lcd.print("STOP!");
        }
        else if (cm <= 95)
        {
            lcd.print("SHOULD STOP");
        }
        else if (cm <= 150)
        {
            lcd.print("TOO CLOSE");
        }
        else if (cm <= 200)
        {
            lcd.print("CLOSE");
        }
        else if (cm <= 300)
        {
            lcd.print("GETTING CLOSE");
        }
        else
        {
            lcd.print("NOT CLOSE");
        }
    }
    else
        lcd.print("OUT OF RANGE");
}

int beepDelay(long cm)
{
    if (cm <= 70)
    {
        return 0;
    }
    else if (cm <= 95)
    {
        return 75;
    }
    else if (cm <= 150)
    {
        return 150;
    }
    else if (cm <= 200)
    {
        return 300;
    }
    else if (cm <= 300)
    {
        return 600;
    }
    return 1000;
}