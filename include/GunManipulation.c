#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#include "Tools.c"
#include "Structs.c"
#include "Ballistics.c"

#ifndef TYPEMANIPULATION_H

#define TYPEMANIPULATION_H

void ChargeMaxRange(int type, int ammo, int charge) {

    struct FireData Data;

    Data = Simulate(0, 0, Atmosphere.WindDir, type, ammo, charge, 800, 1);

    MASTER.Types[type - 1].Ammo[ammo - 1].ChargeMaxRange[charge - 1] = Data.Distance;

}

int AddCharge(int Type, int Ammo, bool CanCancel) {

    char Answer = 'N';
    float MuzzleVelocity;

    while (Answer != 'Y') {
        
        if (CanCancel) {
            printf("    ENTER CHARGE %d MUZZLE VELOCITY (ENTER 0 TO CANCEL): ", MASTER.Types[Type - 1].Ammo[Ammo - 1].ChargeCount + 1);
        } else {
            printf("    ENTER CHARGE %d MUZZLE VELOCITY: ", MASTER.Types[Type - 1].Ammo[Ammo - 1].ChargeCount + 1); 
        }

        scanf("%f", &MuzzleVelocity);
        printf("\n");
        clear();
        
        if (MuzzleVelocity == 0 && CanCancel) {
            return 0;
        } if (MuzzleVelocity <= 0) {
            printf("    ERROR: MUZZLE VELOCITY MUST BE GREATER THAN 0!\n\n");
        } else {
            while (true) {
                printf("    CONFIRM \"%f\" IS CORRECT (Y/N): ", MuzzleVelocity);
                scanf("%1c", &Answer);
                printf("\n");
                clear();

                if (Answer == 'Y' || Answer == 'N') {
                    break;
                } else if (Answer != 'N') {
                    printf("    ERROR: ANSWER MUST BE Y OR N!\n\n");
                }
            }
        }
    }

    MASTER.Types[Type - 1].Ammo[Ammo - 1].Charge[MASTER.Types[Type - 1].Ammo[Ammo - 1].ChargeCount] = MuzzleVelocity;

    MASTER.Types[Type - 1].Ammo[Ammo - 1].ChargeCount++;

    ChargeMaxRange(Type, Ammo, MASTER.Types[Type].Ammo[Ammo].ChargeCount);

    return 1;
}

int AddAmmo(int Type, bool CanCancel) {

    // Adds a new ammo type at the end of the type's ammo array,
    // then adds at least 1 charge.
    
    float AirFriction;

    char AmmoName[50];

    if (CanCancel) {
        InputString("ENTER AMMO TYPE NAME (MAX 50 CHARACTERS, ENTER 0 TO CANCEL): ", AmmoName);

        if (*AmmoName == '0') {
            return 0;
        }
    } else {
        InputString("ENTER AMMO TYPE NAME (MAX 50 CHARACTERS): ", AmmoName);
    }

    MASTER.Types[Type - 1].AmmoCount++;

    int Ammo = MASTER.Types[Type - 1].AmmoCount;

    strcpy(MASTER.Types[Type - 1].Ammo[Ammo - 1].Name, AmmoName);

    AirFriction = Inputfloat("ENTER AMMO AIR FRICTION: ", -100, 0);

    MASTER.Types[Type - 1].Ammo[Ammo - 1].AirFriction = AirFriction;

    printf("    ><>< DEFINE CHARGES ><><\n\n");
    printf("    TO STOP DEFINING CHARGES ENTER 0 INSTEAD OF A VELOCITY\n");
    printf("    MINIMUM OF 1 CHARGE MAXIMUM 20 CHARGES:\n\n");

    AddCharge(Type, Ammo, false);

    int test;

    for (int i = 1; i < MAX_CHARGES; i++) {
        test = AddCharge(Type, Ammo, true);

        if (test == 0) {
            break;
        } 
    }

    return 1;
}

void AddType(void) {

    char TypeName[50], Answer;
    
    InputString("ENTER TYPE NAME (MAX 50 CHARACTERS, ENTER 0 TO CANCEL): ", TypeName);

    if (*TypeName == '0') {
        return;
    }

    MASTER.TypeCount++;

    strcpy(MASTER.Types[MASTER.TypeCount - 1].Name, TypeName);

    printf("    ><>< DEFINE A NEW AMMO TYPE FOR THE NEW TYPE ><><\n\n");

    AddAmmo(MASTER.TypeCount, false);

    Answer = Confirm("DO YOU WISH TO ADD ANOTHER AMMO TYPE? (Y/N): ");

    for (int i = 1; i < MAX_AMMO && Answer == 'Y'; i++) {
        
        int test = AddAmmo(MASTER.TypeCount, true);

        if (test == 0) {
            break;
        }

        Answer = Confirm("DO YOU WISH TO ADD ANOTHER AMMO TYPE? (Y/N): ");
    }
}

void RemoveCharge(int type, int ammo, int charge, bool ReArrange) {

    MASTER.Types[type - 1].Ammo[ammo - 1].Charge[charge - 1] = 0;
    MASTER.Types[type - 1].Ammo[ammo - 1].ChargeMaxRange[charge - 1] = 0;

    for (int i = charge; charge < MASTER.Types[type - 1].Ammo[ammo - 1].ChargeCount; charge++) {
        MASTER.Types[type - 1].Ammo[ammo - 1].Charge[i - 1] = MASTER.Types[type - 1].Ammo[ammo - 1].Charge[i];
        MASTER.Types[type - 1].Ammo[ammo - 1].ChargeMaxRange[i - 1] = MASTER.Types[type - 1].Ammo[ammo - 1].ChargeMaxRange[i];        
    }

    MASTER.Types[type - 1].Ammo[ammo - 1].ChargeCount--;

}

void RemoveAmmo(int type, int ammo, bool ReArrange) {
        
    strcpy(MASTER.Types[type - 1].Ammo[ammo - 1].Name, "\0");
    MASTER.Types[type - 1].Ammo[ammo - 1].AirFriction = 0;

    for (int n = 0; n < MASTER.Types[type - 1].Ammo[ammo - 1].ChargeCount; n++) {
        RemoveCharge(type, ammo, n, false);
    }

    if (ReArrange == true) {
        for (int i = ammo; i < MASTER.Types[type - 1].AmmoCount; i++) {
            MASTER.Types[type - 1].Ammo[i - 1] = MASTER.Types[type - 1].Ammo[i];
        }
    }

    MASTER.Types[type - 1].AmmoCount--;

}

void RemoveType(int type) {
    strcpy(MASTER.Types[type - 1].Name, "\0");

    for (int i = 0; i < MASTER.Types[type - 1].AmmoCount; i++) {
        RemoveAmmo(type, i, false);
    }
    
    // Move back all other types one place if they had
    // a larger id than the removed type so no gaps exist.
    for (int i = type; i < MASTER.TypeCount; i++) {
        MASTER.Types[i - 1] = MASTER.Types[i];
    }

    MASTER.TypeCount--;
}

#endif
