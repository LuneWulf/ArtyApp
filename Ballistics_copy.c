#include <stdio.h>
#include "lib.c"
#include <stdbool.h>
#include <math.h>

#define g 9.8

struct FireData {
    double ToF;
    double Distance;
    double Drift;
};

struct guns {
    double x;
    double y;
    double alt;
    int charge;
    int HighLow;
    double airFriction;
    double RangeAdj;
    double LateralAdj;
    int Weapon;
    int Ammo;
    int Targets;
};

struct targets {
    double x;
    double y;
    double alt;
};

double airDensity(double temperature, double pressure, double humidity) {
    
    double airdensity;

    pressure = pressure * 100;

    if (humidity > 0) {
        double pSat = 610.78 * pow(10, (7.5*temperature)/(temperature+237.3));
        double vaporPressure = humidity * pSat;
        double PP = pressure - vaporPressure;

        airdensity = (PP * 0.028964 + vaporPressure * 0.018016) / (8.314 * (temperature + 273.15));
    } else {
        airdensity = pressure / (8.314 * (temperature + 273.15));
    }

    return airdensity;
}

struct FireData Simulate(double GunAlt, double TgtAlt, double temperature, double humidity, double Ovc, double elevation, double ChVel, double airFriction, double increment, double WindX, double WindY, int graph) {
    
    double time = 0;
    double xVelocity = 0;
    double yVelocity = 0;
    double zVelocity = 0;
    double distance = 0;
    double drift = 0;
    double maxAlt = 0;
    
    int brk = 0;

    double simAltitude = GunAlt;
    double angle = elevation;
    double simVelocity = ChVel;
    
    while (brk == 0) {

        double difAlt = simAltitude - GunAlt;

        if (difAlt < 0) {
            difAlt = difAlt * (-1);
        }

        double rDensity = airDensity(temperature - 0.0065 * difAlt, 1013.25 - 10 * Ovc * (1 - (0.0065 * simAltitude)/(temperature + 273.15)), humidity)/1.225;

        double kFactor = airFriction * rDensity;

        double Drag = kFactor * simVelocity;

        double sinA = sin(angle);
        double cosA = cos(angle);

        double xAccel = cosA * simVelocity * Drag;
        double zAccel = sinA * simVelocity * Drag;

        if (zAccel > 0) {
            zAccel = -zAccel;
        }

        //printf("xA: %f,\nzA: %f\n\n", xAccel, zAccel);
        //printf("wind adds: %f\n", sin(DirDiff) * WindSpeed);
        //printf("Angle: %f, 1: %f, 2: %f\n", angle, cos(angle), sin(angle));

        xVelocity = cosA * simVelocity + xAccel * increment;
        zVelocity = sinA * simVelocity + zAccel * increment - g * increment;
        simAltitude = simAltitude + zVelocity * increment;
        distance = distance + xVelocity * increment + WindX * increment;
        drift = drift + WindY * increment;
        simVelocity = sqrt(pow(xVelocity, 2) + pow(zVelocity, 2) + pow(WindY, 2));
        angle = atan(zVelocity/xVelocity);

        time = time + increment;

        //if (solution == 2 && index == 1 && time < 10)
        //    printf("Time: %f s,\tAltitude: %f m,\tRelative Density: %f,\tDistance: %f m,\tDrift: %f m,\tAngle: %f deg,\tvelocity: %f m/s,\txVelocity: %5.1f m/s,\tzVelocity: %5.1f m/s,\tyVelocity: %5.1f m/s,\tWindX: %.5f,\txAccel: %f,\tzAccel: %f,\tAngle sin: %f\n\n", time, simAltitude, rDensity, distance, drift, angle * 180/M_PI, simVelocity, xVelocity, zVelocity, WindY, WindX, xAccel, zAccel, sinA);
        
        if (simAltitude > maxAlt)
            maxAlt = simAltitude;

        //count++;

        if (graph == 1) {
            int alt = round(simAltitude / 100);
            if (alt < 0) {
                alt = 0;
            }
            points[(int)round(distance / 100)] = alt;
            //printf("x: %d,  y: %d\n", (int)round(distance / 50), alt);
        }

        if (zVelocity < 0 && simAltitude < TgtAlt) {
            //printf("Index: %.0f\n", index);
            //printf("ToF: %.2f s,\nMax Altitude: %.2f m,\nDistance: %.2f m,\nRange: %.1f m,\nAngle: %.3f deg,\nAngle: %.1f mills,\nAngle: %.1f rad\n\n", time, maxAlt, distance, Range, elevation * 180 / M_PI, elevation * 6400 / (M_PI * 2), elevation);
            //printf("Time: %f s,\tAltitude: %f m,\tRelative Density: %f,\tDistance: %f m,\tDrift: %f m,\tAngle: %f deg,\tvelocity: %f m/s,\txVelocity: %5.1f m/s,\tzVelocity: %5.1f m/s,\tyVelocity: %5.1f m/s\tWindX: %.5f\n\n", time, simAltitude, rDensity, distance, drift, angle * 180/M_PI, velocity, xVelocity, zVelocity, WindY, WindX);
            brk = 1;
        }
    }

    struct FireData Data;

    Data.ToF = time;
    Data.Distance = distance;
    Data.Drift = drift;

    return Data;
}

struct targets CreateTarget(double x, double y, double alt) {
    struct targets Target;

    Target.x = x;
    Target.y = y;
    Target.alt = alt;

    return Target;
}

struct guns CreateGun(double x, double y, double alt, int charge, int HighLow, double airFriction, double RangeAdj, double LateralAdj, int Weapon, int Ammo, int Targets[20]) {
    struct guns Gun;

    Gun.x = x;
    Gun.y = y;
    Gun.alt = alt;
    Gun.charge = charge;
    Gun.HighLow = HighLow;
    Gun.airFriction = airFriction;
    Gun.RangeAdj = RangeAdj;
    Gun.LateralAdj = LateralAdj;
    Gun.Weapon = Weapon;
    Gun.Ammo = Ammo;

    return Gun;
}

int main() {


    // Define guns.
    double Guns[10][11] = {
        {1, 1, 1, 0, 0, -0.00006, 0, 0, 0, 0, {0}},
        {2, 2, 2, 0, 0, -0.00006, 0, 0, 0, 0, {0}},
        {3, 3, 3, 0, 0, -0.00006, 0, 0, 0, 0, {0}},
        {4, 4, 4, 0, 0, -0.00006, 0, 0, 0, 0, {0}}
    };

    // Define targets.
    double Targets[20][3] = {
        {6, 6, 6},
        {5, 5, 5},
        {4, 4, 4},
        {3, 3, 3},
        {2, 2, 2},
        {1, 1, 1}
    };

    struct guns Gun[10];
    struct targets Target[20];

    // Init Guns:
    // Take Guns array and create a struct from each.
    for(int i = 0; i < sizeof(Guns)/sizeof(Guns[i]); i++) {
        Gun[i] = CreateGun(Guns[i][0], Guns[i][1], Guns[i][2], Guns[i][3], Guns[i][4], Guns[i][5], Guns[i][6], Guns[i][7], Guns[i][8], Guns[i][9], (int)Guns[i][10]);
    }

    // Init Targets:
    // Take Guns array and create a struct from each.
    for(int i = 0; i < sizeof(Targets)/sizeof(Targets[i]); i++) {
        Target[i] = CreateTarget(Targets[i][0], Targets[i][1], Targets[i][2]);
    }

    //Map Data -- If airfriction = 0, then this does not matter at all.
    double temperature = 14.6;  
    double humidity = 0.5;  
    double pressure = 1006.7;

    //Wind data
    double WindDir = 179.5; // degrees
    double WindSpeed = 0;   // m/s

    //Estimate wind based on nearby building count and tree count.
    double eyeHeight = 1.7;
    int BuildingCount = 0;
    int TreeCount = 0;
    int RoughnessIndex = 2 + BuildingCount + round(TreeCount/9);
    if (RoughnessIndex > 9)
        RoughnessIndex = 9;

    double Roughness[10] = {0.0002, 0.0005, 0.0024, 0.03, 0.055, 0.1, 0.2, 0.4, 0.8, 1.6};
    double multiplier = ln(eyeHeight / Roughness[RoughnessIndex]) / ln(20 / Roughness[RoughnessIndex]);
    
    if (multiplier < 0) {
        multiplier = 0;
        // Print something like: "Wind speed cannot be estimated, either the wind is 0 or you need to find a new base speed.""
    } else {
        WindSpeed = WindSpeed / multiplier;
    }


    // Extend to store multiple weapons and their differing Muzzle Velocities (Some weapons have a different muzzle velocity for each ammo type)
    // ChVel[weaponIndex][ammoIndex][chargeIndex], something like this.
    double ChVel[3][7] = {
        {81, 162, 243},
        {74,117,160,203,246,289,340},
        {222.8, 259.2, 291.6, 344.3, 405, 477.9, 550.8}
    };

    double dAlt = TgtAlt - GunAlt;

    altitude = 0;
    distance = 0;
    velocity = ChVel[Ch] * (((temperature + 273.13)/288.13 - 1) / 40 + 1);
    xVelocity = cos(angle) * velocity;
    zVelocity = sin(angle) * velocity;
    time = 0;
    increment = 0.001;
    double Ovc = (1013.25 - pressure)/(10 * (1 - ((0.0065 * GunAlt)/(temperature + 273.15))));
    
    double finalAlt = 0;
    double finalDrift = 0;
    double xInc = (Tgt2Pos_x - TgtPos_x) / (Rounds - 1);
    double yInc = (Tgt2Pos_y - TgtPos_y) / (Rounds - 1);
   
    int solution = 1;

    if (MultipleTgts == 0) {
        Rounds = 1;
    }

    // assign targets:
    
    switch (Method) {
        default:    // assign targets in order,
                    // if TgtAmount > GunAmount, this will overflow and assign the overflows in order to Gun 1 and then on.
            for(int i = 0; i < TgtAmount; i++) {

            }
    }


    for(solution; solution <= Rounds; solution++) {

        double Range = sqrt(pow((GunPos_x - TgtPos_x),2)+pow((GunPos_y - TgtPos_y),2)) * 100;

        double difX = (GunPos_x - TgtPos_x) * 100;

        double N = GunPos_y < TgtPos_y;
        double S = GunPos_y > TgtPos_y;
        double E = GunPos_x < TgtPos_x;
        double W = GunPos_x > TgtPos_x;

        if (difX < 0)
            difX = -difX;

        double TgtDir;

        if (N || S) {
            TgtDir = acos(difX/Range);

                while (TgtDir < 0) {
                    TgtDir = TgtDir + 2 * M_PI;
                }

                if (TgtDir < M_PI/2 && TgtDir != 0) {
                    if (N && W) {
                        TgtDir = (3 * M_PI /2) + TgtDir; // adjust 19:05 25/05
                    } else if (S && W) {
                        TgtDir = (3 * M_PI / 2) - TgtDir;
                    } else if (S && E) {
                        TgtDir = TgtDir + M_PI / 2; // adjusted 22:25 24/05
                    } else if (N && E) {
                        TgtDir = (M_PI / 2) - TgtDir;
                    }
                } else if (N && TgtDir != 0){
                    TgtDir = 0;
                } else {
                    TgtDir = M_PI;
                }
        } else if (E) {
            TgtDir = M_PI/2;
        } else {
            TgtDir = 3 * M_PI/2;
        }

        Range = Range + RangeAdj;

        Range = sqrt(pow(lateralAdj, 2) + pow(Range, 2));

        TgtDir = TgtDir + asin(lateralAdj/Range);

        WindDir = WindDir * M_PI / 180;

        double DirDiff = WindDir - TgtDir;

        double WindY = sin(DirDiff) * WindSpeed;
        double WindX = cos(DirDiff) * WindSpeed;
    
        double index = 0;
    
        elevation = 45 * M_PI / 180;

        while (distance >= (Range + 0.5) || distance <= (Range - 0.5)) {
            brk = 0;

            time = 0;

            double simVelocity = velocity;
            double simAltitude = GunAlt;
            double drift = 0;
            maxAlt = GunAlt;
            distance = 0;

            angle = elevation;

            int count = 0;

            simulate(GunAlt, TgtAlt, temperature, humidity, Ovc, elevation, velocity, 0, increment, WindX, WindY, graph);

            double difAlt = simAltitude - GunAlt;

            if (difAlt < 0) {
                difAlt = difAlt * (-1);
            }

            double rDensity = airDensity(temperature - 0.0065 * difAlt, 1013.25 - 10 * Ovc * (1 - (0.0065 * simAltitude)/(temperature + 273.15)), humidity)/1.225;

            double kFactor = 0 * rDensity;

            double Drag = kFactor * simVelocity;

            double sinA = sin(angle);
            double cosA = cos(angle);

            double xAccel = cosA * simVelocity * Drag;
            double zAccel = sinA * simVelocity * Drag;

            if (zAccel > 0) {
                zAccel = -zAccel;
            }

            xVelocity = cosA * simVelocity + xAccel * increment;
            zVelocity = sinA * simVelocity + zAccel * increment - g * increment;
            simAltitude = simAltitude + zVelocity * increment;
            distance = distance + xVelocity * increment + WindX * increment;
            drift = drift + WindY * increment;
            simVelocity = sqrt(pow(xVelocity, 2) + pow(zVelocity, 2) + pow(WindY, 2));
            angle = atan(zVelocity/xVelocity);

            time = time + increment;

            
            if (simAltitude > maxAlt)
                maxAlt = simAltitude;

            if (zVelocity < 0 && simAltitude < TgtAlt) {
                brk = 1;
            }

            if (distance > 50000 || distance < 0 || index > 5000 || elevation < 0 || elevation > 1600 * M_PI / 3200) {
                printf("\n\n\t\tSIMULATION FAILED CHECK PARAMETERS!\n\n");
                break;
            }

            finalAlt = simAltitude;

            finalDrift = drift;

            index++;

            double dR = Range - distance;

            if (dR < 0)
                dR = -dR;

            if (HighLow == 1) {
                if (dR < 5) {
                    elevation = elevation - 0.0005 * M_PI / 180;
                } else if (dR < 50) {
                    elevation = elevation - 0.05 * M_PI / 180;
                } else if (dR < 250) {
                    elevation = elevation - 0.1 * M_PI / 180;
                } else if (dR < 1000) {
                    elevation = elevation - 0.75 * M_PI / 180;
                } else {
                    elevation = elevation - 1 * M_PI / 180;
                }
            } else if (HighLow == 0) {
                if (dR < 5) {
                    elevation = elevation + 0.0005 * M_PI / 180;
                } else if (dR < 50) {
                    elevation = elevation + 0.05 * M_PI / 180;
                } else if (dR < 250) {
                    elevation = elevation + 0.1 * M_PI / 180;
                } else if (dR < 1000) {
                    elevation = elevation + 0.75 * M_PI / 180;
                } else {
                    elevation = elevation + 1 * M_PI / 180;
                }
            }
        }

        if (HighLow == 1) {
            printf("Firing Solution %d:\nLow Angle,\nCharge: %d,\nToF: %.2f s,\nTgtDir: %.0f mills,\nElevation: %.0f mills,\nDistance - Range: %.2f m, (Sanity check: if not within +/- 0.5 m then check parameters)\nRange: %.2f m,\nRange Adjustment: %.0f m,\nLateral Adjustment: %.0f m\n\n", solution, Ch, time, TgtDir * 6400 / (M_PI * 2), elevation * 6400 / (M_PI * 2), distance - Range, Range, RangeAdj, lateralAdj);
        } else {
            printf("Firing Solution %d:\nHigh Angle,\nCharge: %d,\nToF: %.2f s,\nTgtDir: %.0f mills,\nElevation: %.0f mills,\nDistance - Range: %.2f m, (Sanity check: if not within +/- 0.5 m then check parameters)\nRange: %.2f m,\nRange Adjustment: %.0f m,\nLateral Adjustment: %.0f m\n\n", solution, Ch, time, TgtDir * 6400 / (M_PI * 2), elevation * 6400 / (M_PI * 2), distance - Range, Range, RangeAdj, lateralAdj);
        }

        
        if (MultipleTgts == 1) {
            TgtPos_x = TgtPos_x + xInc;
            TgtPos_y = TgtPos_y + yInc;
        }

        if (Rounds == 1 && graph == 1) {

            int points[200];

            brk = 0;

            time = 0;

            double simVelocity = velocity;
            double simAltitude = GunAlt;
            double drift = 0;
            maxAlt = GunAlt;
            distance = 0;

            angle = elevation;

            int count = 0;

            points[200];

            while (brk == 0) {

                double difAlt = simAltitude - GunAlt;

                if (difAlt < 0) {
                    difAlt = difAlt * (-1);
                }

                double rDensity = airDensity(temperature - 0.0065 * difAlt, 1013.25 - 10 * Ovc * (1 - (0.0065 * simAltitude)/(temperature + 273.15)), humidity)/1.225;

                //double kFactor = airFriction * rDensity;
                double kFactor = 0 * rDensity;

                double Drag = kFactor * simVelocity;

                double sinA = sin(angle);
                double cosA = cos(angle);

                double xAccel = cosA * simVelocity * Drag;
                double zAccel = sinA * simVelocity * Drag;

                if (zAccel > 0) {
                    zAccel = -zAccel;
                }

                xVelocity = cosA * simVelocity + xAccel * increment;
                zVelocity = sinA * simVelocity + zAccel * increment - g * increment;
                simAltitude = simAltitude + zVelocity * increment;
                distance = distance + xVelocity * increment + WindX * increment;
                drift = drift + WindY * increment;
                simVelocity = sqrt(pow(xVelocity, 2) + pow(zVelocity, 2) + pow(WindY, 2));
                angle = atan(zVelocity/xVelocity);

                time = time + increment;
                
                if (simAltitude > maxAlt)
                    maxAlt = simAltitude;

                //count++;

                if (Rounds == 1) {
                    int alt = round(simAltitude / 100);
                    if (alt < 0) {
                        alt = 0;
                    }
                    points[(int)round(distance / 100)] = alt;
                    //printf("x: %d,  y: %d\n", (int)round(distance / 50), alt);
                }

                if (zVelocity < 0 && simAltitude < TgtAlt) {
                    brk = 1;
                }
            }

            for(int line = (int)round(maxAlt / 100) + 2; line >= 0; line--) {
                for(int index = 0; index < (int)round(distance / 100) + 1; index++) {
                    if (line == points[index]) {
                        printf("O ");
                    } else {
                        printf("' ");
                    }
                }
                if ((int)round(maxAlt / 100) + 2 == line) {
                    printf(" ALTITUDE:\n");
                } else {
                    printf(" %d m\n", line * 100);
                }
            }
        }
    }
}