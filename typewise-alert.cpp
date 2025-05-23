#include "typewise-alert.h"
#include <stdio.h>

BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
    if (value < lowerLimit) {
        return TOO_LOW;
    }
    if (value > upperLimit) {
        return TOO_HIGH;
    }
    return NORMAL;
}

void getCoolingLimits(CoolingType coolingType, int &lowerLimit, int &upperLimit) {
    if (coolingType == PASSIVE_COOLING) {
        lowerLimit = 0;
        upperLimit = 35;
    } else if (coolingType == HI_ACTIVE_COOLING) {
        lowerLimit = 0;
        upperLimit = 45;
    } else { // MED_ACTIVE_COOLING
        lowerLimit = 0;
        upperLimit = 40;
    }
}

BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC) {
    int lowerLimit = 0;
    int upperLimit = 0;
    getCoolingLimits(coolingType, lowerLimit, upperLimit);
    return inferBreach(temperatureInC, lowerLimit, upperLimit);
}

void sendLowTemperatureAlert(const char* recipient) {
    printf("To: %s\n", recipient);
    printf("Hi, the temperature is too low\n");
}

void sendHighTemperatureAlert(const char* recipient) {
    printf("To: %s\n", recipient);
    printf("Hi, the temperature is too high\n");
}

void sendToEmail(BreachType breachType) {
    const char* recipient = "a.b@c.com";
    if (breachType == TOO_LOW) {
        sendLowTemperatureAlert(recipient);
    } else if (breachType == TOO_HIGH) {
        sendHighTemperatureAlert(recipient);
    }
}

void sendAlert(BreachType breachType, AlertTarget alertTarget) {
    switch (alertTarget) {
        case TO_CONTROLLER:
            sendToController(breachType);
            break;
        case TO_EMAIL:
            sendToEmail(breachType);
            break;
    }
}

void checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) {
    BreachType breachType = classifyTemperatureBreach(batteryChar.coolingType, temperatureInC);
    sendAlert(breachType, alertTarget);
}

void sendToController(BreachType breachType) {
    const unsigned short header = 0xfeed;
    printf("%x : %x\n", header, breachType);
}
