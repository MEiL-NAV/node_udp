#include "ParametersHandler.h"
#include <Arduino.h>


ParametersHandler::~ParametersHandler()
{
    eeprom.end();
}

void ParametersHandler::init()
{
    eeprom.begin(sizeof(Parameters));
    if(eeprom.read(0) != parameters.version)
    {
        restore_defaults();
    }
    eeprom.get(0,parameters);
}

void ParametersHandler::save() 
{ 
    eeprom.put(0, parameters);
    eeprom.commit();
}

void ParametersHandler::restore_defaults() 
{
    save();
    Serial.println("Restored default parameters.");
}
