#include <Servo.h>
#include <NewPing.h>

/*
 *  OCAD University
 *  DIGF 6037-001 Creation & Computation 
 *  
 *  Ruby
 *  Kinetic light installation sketch based on Arduino servo sweep code.
 *  
 *  Marcus A. Gordon

*/

int laserPin = 14;

int minScan = 75; // 45
int maxScan = 105; // 135

int laze = maxScan;
int rubyLaserPos = 75;

long lastScan;
int scanRate = 50;

#define trig 12
#define echo 11
#define maxDistance 50

int rubyEye = 7;

Servo rubyServo;
NewPing presence(trig, echo, maxDistance);


void setup()
{
  Serial.begin(9600);
  rubyServo.attach(laserPin);
  rubyServo.write(minScan);
  pinMode(rubyEye, OUTPUT);
  digitalWrite(rubyEye, HIGH);
}


void loop() {

  if ((millis() - lastScan) >= scanRate) {

    if (presence.ping_cm() >= 100) {
      rubyServo.detach();
      digitalWrite(rubyEye, LOW);
    } 

    if (presence.ping_cm() <= 10) {
      rubyServo.attach(laserPin);
      digitalWrite(rubyEye, HIGH);
    }
    
    if (laze == maxScan) {
      if ((rubyLaserPos + 1) <= maxScan) {
        rubyLaserPos++;
        lastScan = millis();
      }
      else {
        laze = minScan;
      }

    }
    if (laze == minScan) {
      if ((rubyLaserPos - 1) >= minScan) {
        rubyLaserPos--;
        lastScan = millis();
      }
      else {
        laze = maxScan;
      }

    }

  }


  Serial.print("Presence: ");
  Serial.print(presence.ping_cm());
  Serial.println("cm");

  rubyServo.write(rubyLaserPos);

}

