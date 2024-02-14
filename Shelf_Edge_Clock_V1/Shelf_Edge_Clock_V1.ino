/*
 * 3D printed smart shelving with a giant hidden digital clock in the front edges of the shelves - DIY Machines
   Modified for digital output photoresistor

==========

More info and build instructions: https://www.youtube.com/watch?v=8E0SeycTzHw

3D printed parts can be downloaded from here: https://www.thingiverse.com/thing:4207524

You will need to install the Adafruit Neopixel library which can be found in the library manager.

This project also uses the handy DS3231 Simple library:- https://github.com/sleemanj/DS3231_Simple   Please follow the instruction on installing this provided on the libraries page

Before you install this code you need to set the time on your DS3231. Once you have connected it as shown in this project and have installed the DS3231_Simple library (see above) you
 to go to  'File' >> 'Examples' >> 'DS3231_Simple' >> 'Z1_TimeAndDate' >> 'SetDateTime' and follow the instructions in the example to set the date and time on your RTC

==========


 * SAY THANKS:

Buy me a coffee to say thanks: https://ko-fi.com/diymachines
Support us on Patreon: https://www.patreon.com/diymachines

SUBSCRIBE:
■ https://www.youtube.com/channel/UC3jc4X-kEq-dEDYhQ8QoYnQ?sub_confirmation=1

INSTAGRAM: https://www.instagram.com/diy_machines/?hl=en
FACEBOOK: https://www.facebook.com/diymachines/

*/

#include <Adafruit_NeoPixel.h>
#include <DS3231_Simple.h>

DS3231_Simple Clock;

DateTime MyDateAndTime;

#define LEDCLOCK_PIN        6
#define LEDDOWNLIGHT_PIN    5
#define LEDCLOCK_COUNT      216
#define LEDDOWNLIGHT_COUNT  12

uint32_t clockMinuteColour = 0x008000; // pure green
uint32_t clockHourColour = 0x800000;   // pure red

int clockFaceBrightness = 0;

Adafruit_NeoPixel stripClock(LEDCLOCK_COUNT, LEDCLOCK_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel stripDownlighter(LEDDOWNLIGHT_COUNT, LEDDOWNLIGHT_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
    Serial.begin(9600);
    Clock.begin();

    stripClock.begin();
    stripClock.show();
    stripClock.setBrightness(100);

    stripDownlighter.begin();
    stripDownlighter.show();
    stripDownlighter.setBrightness(50);
}

void loop() {
    readTheTime();
    displayTheTime();
    stripClock.show();
    stripDownlighter.fill(16777215, 0, LEDDOWNLIGHT_COUNT);
    stripDownlighter.show();
    delay(5000); // Delay para pruebas
}

void readTheTime() {
    MyDateAndTime = Clock.read();
    Serial.println("");
    Serial.print("Time is: ");   Serial.print(MyDateAndTime.Hour);
    Serial.print(":"); Serial.print(MyDateAndTime.Minute);
    Serial.print(":"); Serial.println(MyDateAndTime.Second);
    Serial.print("Date is: 20");   Serial.print(MyDateAndTime.Year);
    Serial.print(":");  Serial.print(MyDateAndTime.Month);
    Serial.print(":");    Serial.println(MyDateAndTime.Day);
}

void displayTheTime() {
    stripClock.clear();

    int firstMinuteDigit = MyDateAndTime.Minute % 10;
    displayNumber(firstMinuteDigit, 0, clockMinuteColour);

    int secondMinuteDigit = floor(MyDateAndTime.Minute / 10);
    displayNumber(secondMinuteDigit, 63, clockMinuteColour);

    int firstHourDigit = MyDateAndTime.Hour;
    if (firstHourDigit > 12) {
        firstHourDigit = firstHourDigit - 12;
    }
    firstHourDigit = firstHourDigit % 10;
    displayNumber(firstHourDigit, 126, clockHourColour);

    int secondHourDigit = MyDateAndTime.Hour;
    if (secondHourDigit > 12) {
        secondHourDigit = secondHourDigit - 12;
    }
    if (secondHourDigit > 9) {
        stripClock.fill(clockHourColour, 189, 18);
    }
}

void displayNumber(int digitToDisplay, int offsetBy, uint32_t colourToUse) {
    switch (digitToDisplay) {
        case 0:
            digitZero(offsetBy, colourToUse);
            break;
        case 1:
            digitOne(offsetBy, colourToUse);
            break;
        case 2:
            digitTwo(offsetBy, colourToUse);
            break;
        case 3:
            digitThree(offsetBy, colourToUse);
            break;
        case 4:
            digitFour(offsetBy, colourToUse);
            break;
        case 5:
            digitFive(offsetBy, colourToUse);
            break;
        case 6:
            digitSix(offsetBy, colourToUse);
            break;
        case 7:
            digitSeven(offsetBy, colourToUse);
            break;
        case 8:
            digitEight(offsetBy, colourToUse);
            break;
        case 9:
            digitNine(offsetBy, colourToUse);
            break;
        default:
            break;
    }
}
