#include "HC_SR04.h"
// Make sure you import that library first
int cm = 0;
double inches = 0.0;
unsigned int valueChangeTime;
int prev;

int trigPin = D4;
int echoPin = D5;

HC_SR04 rangefinder = HC_SR04(trigPin, echoPin);

void setup() 
{
    Spark.variable("cm", &cm, INT);
    Spark.variable("inches", &inches, DOUBLE);
    valueChangeTime = millis();
}

void loop() 
{
    prev = cm;
    cm = rangefinder.getDistanceCM();
    inches = rangefinder.getDistanceInch();
    if ( cm > 0  && millis() - valueChangeTime > 3000) {
            int diff = cm - prev;
            if (diff > 40) {
                Particle.publish("Sensor_Trigger", (String) "True", PUBLIC);
                prev = cm;
                delay(1000);
            }
            
    }
    delay(1000);
    
}

