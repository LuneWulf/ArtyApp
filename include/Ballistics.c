#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#include "Tools.c"
#include "Structs.c"

#ifndef BALLISTICS_H

#define BALLISTICS_H

#define g 9.8
#define Increment 0.01

double airDensity(double temperature, double pressure, double humidity) {
    
    double airdensity;

    pressure = pressure * 100;

    double pSat = 610.78 * pow(10, (7.5*temperature)/(temperature+237.3));
    double vaporPressure = humidity * pSat;
    double PP = pressure - vaporPressure;

    airdensity = (PP * 0.028964 + vaporPressure * 0.018016) / (8.314 * (temperature + 273.15));

    return airdensity;
}

struct FireData Simulate(float GunAlt, float TargetAlt, float Direction, int TypeID, int AmmoID, int Charge, double Elevation, int MaxRange) {
    
    struct FireData Solution;
    
    float ChargeVel = MASTER.Types[TypeID - 1].Ammo[AmmoID - 1].Charge[Charge - 1];
    
    Solution.Direction = Direction;
    Solution.Elevation = Elevation;

    Direction = Direction * M_PI / 3200;

    float WindDirection = 0;
    float WindX = 0;
    float WindY = 0;

    if (MaxRange == 0) {
        WindDirection = Atmosphere.WindDir * M_PI / 180;
        float DirDiff = WindDirection - Direction;
        WindX = cos(DirDiff) * Atmosphere.WindSpeed;
        WindY = sin(DirDiff) * Atmosphere.WindSpeed;
    }

    float time = 0;
    float xVelocity = 0;
    float yVelocity = 0;
    float zVelocity = 0;
    float distance = 0;
    float drift = 0;
    float MaxAlt = 0;

    float simAltitude = GunAlt;
    float angle = Elevation * M_PI / 3200;
    float simVelocity = ChargeVel;
    float rDensity;
    
    while (true) {

        float difAlt = simAltitude - GunAlt;

        if (difAlt < 0) {
            difAlt = -difAlt;
        }

        rDensity = airDensity(Atmosphere.Temperature - 0.0065 * difAlt, Atmosphere.Pressure, Atmosphere.Humidity)/1.225;

        float kFactor = MASTER.Types[TypeID - 1].Ammo[AmmoID - 1].AirFriction * rDensity;

        float Drag = kFactor * simVelocity;

        float xAccel = cos(angle) * simVelocity * Drag;
        float zAccel = sin(angle) * simVelocity * Drag;

        if (zAccel > 0) {
            zAccel = -zAccel;
        }

        xVelocity = cos(angle) * simVelocity + xAccel * Increment;
        zVelocity = sin(angle) * simVelocity + zAccel * Increment - g * Increment;
        simAltitude = simAltitude + zVelocity * Increment;
        distance = distance + xVelocity * Increment + WindX * Increment;
        drift = drift + WindY * Increment;
        simVelocity = sqrt(pow(xVelocity, 2) + pow(zVelocity, 2) + pow(WindY, 2));
        angle = atan(zVelocity/xVelocity);

        time = time + Increment;

        if (simAltitude > MaxAlt)
            MaxAlt = simAltitude;

        if (zVelocity < 0 && simAltitude < TargetAlt) {
            break;
        }
    }

    Solution.Direction += atan(Solution.Drift / Solution.Distance) * 3200 / M_PI;

    Solution.MaxAlt = MaxAlt;
    Solution.ToF = time;
    Solution.Distance = distance;
    Solution.Drift = drift;

    return Solution;    
}

#endif
