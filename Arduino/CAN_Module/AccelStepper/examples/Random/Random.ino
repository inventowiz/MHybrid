// Random.pde
// -*- mode: C++ -*-
//
// Make a single stepper perform random changes in speed, position and acceleration
//
// Copyright (C) 2009 Mike McCauley
// $Id: Random.pde,v 1.1 2011/01/05 01:51:01 mikem Exp mikem $

#include <AccelStepper.h>

// Define a stepper and the pins it will use
AccelStepper stepper(AccelStepper::DRIVER,2,3);

void setup()
{  
  Serial.begin(115200);
}

int steps = 400 * 16;
int loc = 0;

void loop()
{
    if (stepper.distanceToGo() == 0)
    {
        if(loc){
                loc = steps;
        	stepper.moveTo(loc);
        	stepper.setMaxSpeed((rand() % steps) + 1);
        	stepper.setAcceleration((rand() % steps) + 1);
        }else{
                loc = 0;
                stepper.moveTo(loc);
        	stepper.setMaxSpeed((rand() % steps) + 1);
        	stepper.setAcceleration((rand() % steps) + 1);
        }
    }
    stepper.run();
}
