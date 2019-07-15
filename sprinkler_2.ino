#include <DS3232RTC.h>    //Get library here http://github.com/JChristensen/DS3232RTC
#include <Time.h> 
#include <Wire.h>

int val ; 
int set_hr = 8; //Sets the hour at which the sprinkler watering will start
int set_min = 30; //Sets the minute at which the sprinkler watering will start
int set_period = 2; //Sets the number of minutes the sprinkler will fe in action for a given event
int set_rep = 2; //Sets the number of watering events on a given day
int end_min=set_min+set_period; //Calculates the time at which the watering will end
int sprinkler=7; //Defines the pin number used by the sprinkler relay
int droplet=8; //Defines the pin number used by the droplet relay
bool rep = false;
int set_hr_2;
int set_hr_3;

void setup() 
{
  Serial.begin(9600);
  pinMode(7, OUTPUT); //relay1
  
  if (set_rep == 2){
    rep=!rep;
    set_hr_2=set_hr+12;
  }
  else if (set_rep == 3){
    rep=!rep;
    set_hr_2=set_hr+8;
    set_hr_3=set_hr+16;
    if (set_hr_3 >=24){
      set_hr_3 = set_hr_3-24;
    }
    else {}
  }
  else{}
  Serial.println();
  Serial.println("will water at: ");
  Serial.print(set_hr);
  Serial.print(":");
  Serial.print(set_min);
  Serial.print(" to ");
  Serial.print(set_hr );
  Serial.print(":");
  Serial.println(end_min );
  
  Serial.print(set_hr_2);
  Serial.print(":");
  Serial.print(set_min);
  Serial.print(" to ");
  Serial.print(set_hr_2 );
  Serial.print(":");
  Serial.println(end_min );

  Serial.print(set_hr_3);
  Serial.print(":");
  Serial.print(set_min);
  Serial.print(" to ");
  Serial.print(set_hr_3);
  Serial.print(":");
  Serial.println(end_min );
  
  Serial.print(set_rep );  
  Serial.print(" times a day");
  Serial.println();
 //Serial.println(rep);
  //Uncomment both lines below when you want to set the time and coment them after
  //setTime(12, 00, 00, 13, 07, 2019);//Hours / minutes / second / day of month / month / year
  //RTC.set(now());
  
  setSyncProvider(RTC.get);   // the function to get the time from the RTC
    if(timeStatus() != timeSet) 
        Serial.println("Unable to sync with the RTC");
    else
       Serial.println("RTC has set the system time");   
}
 
void loop() 
{
  
AutomaticProgram();
digitalClockDisplay();
AutomaticProgram(); 

}
 

void AutomaticProgram() 
{   
    int hr = (hour()); //Grow/Day - Groei/Dag between 4:00 and 22:00
    int mn = (minute());
    
    if ((set_hr == hr) && (mn >= set_min && mn < end_min))             
    {
      digitalWrite (sprinkler, LOW);
      digitalWrite (droplet, LOW);


    }
    else if(rep==true && (set_hr_2 == hr) && (mn >= set_min && mn < end_min))
    {

    digitalWrite(sprinkler, LOW);

    }
    else if(rep==true && set_rep==3 && (set_hr_3 == hr) && (mn >= set_min && mn < end_min))
    {
    digitalWrite(sprinkler, LOW);
    }
    else
    {
    digitalWrite(sprinkler, HIGH);
    digitalWrite (droplet, HIGH);
    }
}
void digitalClockDisplay(void)
{
    // digital clock display of the time
    Serial.print(hour());
    printDigits(minute());
    printDigits(second());
   // Serial.print(' ');
   // Serial.print(day());
   // Serial.print(' ');
   // Serial.print(month());
   // Serial.print(' ');
    //Serial.print(year()); 
    Serial.println(); 
}
void displayClockLCD(void)
{
tmElements_t tm;
RTC.read(tm);
Serial.print(tm.Hour, DEC);
Serial.print(':');
Serial.print(tm.Minute,DEC);
Serial.print(':');
Serial.println(tm.Second,DEC);
}

void printDigits(int digits)
{
    // utility function for digital clock display: prints preceding colon and leading 0
    Serial.print(':');
    if(digits < 10)
        Serial.print('0');
    Serial.print(digits);
}
