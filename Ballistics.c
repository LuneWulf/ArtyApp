#include <stdio.h>
#include <math.h>

#define g 9.8

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

int main() {

    double velocity, distance, angle, xVelocity, zVelocity, yVelocity, altitude, crossSetion, weight, dragCoef, increment, a, xFd, yFd, Re, maxAlt, thrust, xT, yT, thrustCut, time, elevation;
    int brk = 0;
    int done = 0;

    // Gun Data
    // pos is given by the first 3 numbers of their coordinate then a point and then the remaining.
        // fx grid 342-982:
            // pos_x = 342
            // pos_y = 982
        // fx grid 3425-9825:
            // pos_x = 342.5
            // pos_y = 982.5
    double GunPos_x = 93.6;
    double GunPos_y = 854.55;
    double GunAlt = 163;
    int Ch = 2;
    int HighLow = 0;        // 0 = High Angle, 1 = Low Angle
    int MultipleTgts = 0;   // 0 = no, 1 = yes
    int Rounds = 4;         // Only applies for multiple tgts.
    double airFriction = -0.00006;
    int graph = 0;

    // Target 1 Data
    double TgtPos_x = 105.7;
    double TgtPos_y = 872.75;
    double TgtAlt = 103;

    // Target 2 Data
    double Tgt2Pos_x = 97.025;
    double Tgt2Pos_y = 959.4-1000;
    double Tgt2Alt = 32;

    //Adjustments
    double RangeAdj = 0;
    double lateralAdj = 0;

    //Map Data -- If airfriction = 0, then this doesnt matter at all.
    double temperature = 18.7;  
    double humidity = 0.615;  
    double pressure = 990.6;

    double WindDir = 0; // degrees
    double WindSpeed = 0.7; // m/s

    //double ChVel[7] = {74,117,160,203,246,289,340};
    double ChVel[3] = {100, 137.5, 190};
    //double ChVel[7] = {222.8, 259.2, 291.6, 344.3, 405, 477.9, 550.8};

    //printf("LatAdj: %f mills\n", asin(lateralAdj/Range) * 6400 / (2* M_PI));

    double dAlt = TgtAlt - GunAlt;

    //printf("WindDir: %f\n", WindDir);
    //printf("TgtDir: %f rad,\nTgtDir: %f mills\n", TgtDir, TgtDir * 6400 / (2*M_PI));

    //printf("dd %f\n", DirDiff);

    altitude = 0;
    distance = 0;
    velocity = ChVel[Ch]; //* (((temperature + 273.13)/288.13 - 1) / 40 + 1);

    //printf("Velocity: %f\n", velocity);

    xVelocity = cos(angle) * velocity;
    zVelocity = sin(angle) * velocity;
    time = 0;
    increment = 0.01;
    double Ovc = (1013.25 - pressure)/(10 * (1 - ((0.0065 * GunAlt)/(temperature + 273.15))));
    
    //printf("angle: %f\n\n", elevation);

    double finalAlt = 0;
    double finalDrift = 0;
    double xInc = (Tgt2Pos_x - TgtPos_x) / (Rounds - 1);
    double yInc = (Tgt2Pos_y - TgtPos_y) / (Rounds - 1);
   
    int solution = 1;

    if (MultipleTgts == 0) {
        Rounds = 1;
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
            //printf("difX: %.2f m,\nRange: %.2f m,\nTgtDir 1: %.5f rad,\nTgtDir 1: %.5f deg,\nTgtDir 1: %.5f mills,\nN: %.f,\nS: %.f,\nE: %.f,\nW: %.f\n", difX, Range, TgtDir, TgtDir * 180 / M_PI, TgtDir * 6400 / (2*M_PI), N, S, E, W);

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
                //printf("TgtDir 2: %.5f rad,\nTgtDir 2: %.5f deg,\nTgtDir 2: %.5f mills,\nN: %.f,\nS: %.f,\nE: %.f,\nW: %.f\n", TgtDir, TgtDir * 180 / M_PI, TgtDir * 6400 / (2*M_PI), N, S, E, W);
        } else if (E) {
            TgtDir = M_PI/2;
            //printf("TgtDir 2: %.5f rad,\nTgtDir 2: %.5f deg,\nN: %.f,\nS: %.f,\nE: %.f,\nW: %.f\n", TgtDir, TgtDir * 180 / M_PI, N, S, E, W);
        } else {
            TgtDir = 3 * M_PI/2;
            //printf("TgtDir 2: %.5f rad,\nTgtDir 2: %.5f deg,\nN: %.f,\nS: %.f,\nE: %.f,\nW: %.f\n", TgtDir, TgtDir * 180 / M_PI, N, S, E, W);
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

            while (brk == 0) {

                double difAlt = simAltitude - GunAlt;

                if (difAlt < 0) {
                    difAlt = difAlt * (-1);
                }

                double rDensity = airDensity(temperature - 0.0065 * difAlt, 1013.25 - 10 * Ovc * (1 - (0.0065 * simAltitude)/(temperature + 273.15)), humidity)/1.225;
                //double rDensity = airDensity(temperature, pressure, humidity)/1.225;

                double kFactor = airFriction * rDensity;

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
                simVelocity = sqrt(pow(xVelocity, 2) + pow(zVelocity, 2));
                angle = atan(zVelocity/xVelocity);

                time = time + increment;

                if (index == 1 && time < 10) {
                    //printf("Time: %f s,\tAltitude: %f m,\tRelative Density: %f,\tDistance: %f m,\tDrift: %f m,\tAngle: %f deg,\tvelocity: %f m/s,\txVelocity: %5.1f m/s,\tzVelocity: %5.1f m/s,\tyVelocity: %5.1f m/s,\tWindX: %.5f,\txAccel: %f,\tzAccel: %f,\tAngle sin: %f\n\n", time, simAltitude, rDensity, distance, drift, angle * 180/M_PI, simVelocity, xVelocity, zVelocity, WindY, WindX, xAccel, zAccel, sinA);
                    //printf("xA: %f,\nzA: %f\n", xAccel, zAccel);
                    //printf("wind adds: %f & %f\n", WindX, WindY);
                    //printf("Angle: %f, 1: %f, 2: %f\n\n", angle, cos(angle), sin(angle));
                }  

                if (simAltitude > maxAlt)
                    maxAlt = simAltitude;

                if (zVelocity < 0 && simAltitude < TgtAlt) {
                    //printf("Index: %.0f\n", index);
                    //printf("ToF: %.2f s,\nMax Altitude: %.2f m,\nDistance: %.2f m,\nRange: %.1f m,\nAngle: %.3f deg,\nAngle: %.1f mills,\nAngle: %.1f rad\n\n", time, maxAlt, distance, Range, elevation * 180 / M_PI, elevation * 6400 / (M_PI * 2), elevation);
                    //printf("Time: %f s,\tAltitude: %f m,\tRelative Density: %f,\tDistance: %f m,\tDrift: %f m,\tAngle: %f deg,\tvelocity: %f m/s,\txVelocity: %5.1f m/s,\tzVelocity: %5.1f m/s,\tyVelocity: %5.1f m/s\tWindX: %.5f\n\n", time, simAltitude, rDensity, distance, drift, angle * 180/M_PI, velocity, xVelocity, zVelocity, WindY, WindX);
                    brk = 1;
                }
            }

            if (distance > 50000 || distance < 0 || index == 2000 || elevation < 0 || elevation > 1600 * M_PI / 3200) {
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
                } else if (dR < 100) {
                    elevation = elevation - 0.025 * M_PI / 180;
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
                } else if (dR < 100) {
                    elevation = elevation + 0.025 * M_PI / 180;
                } else if (dR < 250) {
                    elevation = elevation + 0.05 * M_PI / 180;
                } else if (dR < 1000) {
                    elevation = elevation + 0.75 * M_PI / 180;
                } else {
                    elevation = elevation + 1 * M_PI / 180;
                }
            }

            //printf("Elevation: %f\n", elevation);
        }

        if (HighLow == 1) {
            printf("Firing Solution %d:\nLow Angle,\nCharge: %d,\nToF: %.2f s,\nTgtDir: %.0f mills,\nElevation: %.0f mills,\nDistance - Range: %.2f m, (Sanity check: if not within +/- 0.5 m then check parameters)\nRange: %.2f m,\nRange Adjustment: %.0f m,\nLateral Adjustment: %.0f m\n\n", solution, Ch, time, TgtDir * 6400 / (M_PI * 2), elevation * 6400 / (M_PI * 2), distance - Range, Range, RangeAdj, lateralAdj);
        } else {
            printf("Firing Solution %d:\nHigh Angle,\nCharge: %d,\nToF: %.2f s,\nTgtDir: %.0f mills,\nElevation: %.0f mills,\nDistance - Range: %.2f m, (Sanity check: if not within +/- 0.5 m then check parameters)\nRange: %.2f m,\nRange Adjustment: %.0f m,\nLateral Adjustment: %.0f m\n\n", solution, Ch, time, TgtDir * 6400 / (M_PI * 2), elevation * 6400 / (M_PI * 2), distance - Range, Range, RangeAdj, lateralAdj);
        }

        //printf("SIMULATION FINISHED:\nIndex: %.f,\n\nCharge: %d,\nToF: %.2f s,\nMax Altitude: %.2f m,\nAltitude: %.2f,\nRelative Density: %.2f,\nDistance: %.2f m,\nRange: %.2f m,\nElevation: %.1f mills,\nElevation %.2f deg,\nTgtDir: %.0f mills\nDrift: %.5f m", index, Ch, time, maxAlt, finalAlt, airDensity(temperature, pressure, humidity)/1.225, distance, Range, elevation * 6400 / (M_PI * 2), elevation * 180 / M_PI, TgtDir * 6400 / (M_PI * 2), finalDrift);
        
        if (MultipleTgts == 1) {
            TgtPos_x = TgtPos_x + xInc;
            TgtPos_y = TgtPos_y + yInc;
        }

        if (Rounds == 1 && graph == 1) {

            int points[100];

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

                //double rDensity = airDensity(temperature - 0.0065 * difAlt, 1013.25 - 10 * Ovc * (1 - (0.0065 * simAltitude)/(temperature + 273.15)), humidity)/1.225;
                double rDensity = airDensity(temperature, pressure, humidity)/1.225;

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

                if (Rounds == 1) {
                    int alt = round(simAltitude / 75);
                    if (alt < 0) {
                        alt = 0;
                    }
                    points[(int)round(distance / 75)] = alt;
                    //printf("x: %d,  y: %d\n", (int)round(distance / 50), alt);
                }

                if (zVelocity < 0 && simAltitude < TgtAlt) {
                    //printf("Index: %.0f\n", index);
                    //printf("ToF: %.2f s,\nMax Altitude: %.2f m,\nDistance: %.2f m,\nRange: %.1f m,\nAngle: %.3f deg,\nAngle: %.1f mills,\nAngle: %.1f rad\n\n", time, maxAlt, distance, Range, elevation * 180 / M_PI, elevation * 6400 / (M_PI * 2), elevation);
                    //printf("Time: %f s,\tAltitude: %f m,\tRelative Density: %f,\tDistance: %f m,\tDrift: %f m,\tAngle: %f deg,\tvelocity: %f m/s,\txVelocity: %5.1f m/s,\tzVelocity: %5.1f m/s,\tyVelocity: %5.1f m/s\tWindX: %.5f\n\n", time, simAltitude, rDensity, distance, drift, angle * 180/M_PI, velocity, xVelocity, zVelocity, WindY, WindX);
                    brk = 1;
                }
            }

            for(int line = (int)round(maxAlt / 75) + 2; line >= 0; line--) {
                for(int index = 0; index < (int)round(distance / 75) + 1; index++) {
                    if (line == points[index]) {
                        printf("O ");
                    } else {
                        printf("' ");
                    }
                }
                if ((int)round(maxAlt / 75) + 2 == line) {
                    printf(" ALTITUDE:\n");
                } else {
                    printf(" %d m\n", line * 75);
                }
            }
        }
    }
}