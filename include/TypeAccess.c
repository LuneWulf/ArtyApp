#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#include "Tools.c"

#ifndef TYPEACCESS_H

#define TYPEACCESS_H

void ListCharges(int Type, int Ammo) {
    
    for (int Charge = 0; Charge < MAX_CHARGES && MASTER.Types[Type - 1].Ammo[Ammo - 1].Charge[Charge] != 0; Charge++) {
        printf("    CHARGE: %d, MAX RANGE: %ld\n", Charge + 1, MASTER.Types[Type - 1].Ammo[Ammo - 1].ChargeMaxRange[Charge]);
    }

    printf("\n");

}

void ListAmmo(int Type) {

    for (int Ammo = 0; Ammo < MASTER.Types[Type - 1].AmmoCount; Ammo++) {
        printf("        AMMO NAME: %s, AMMO ID: %d, AMMO CHARGE COUNT: %d\n", MASTER.Types[Type - 1].Ammo[Ammo].Name, Ammo + 1, MASTER.Types[Type - 1].Ammo[Ammo].ChargeCount);
    }

    printf("\n");
}

void ListAllTypes(bool List_Ammo) {

    for (int Type = 0; Type < MAX_TYPES && MASTER.Types[Type].AmmoCount != 0; Type++) {
        printf("    TYPE NAME: %s, TYPE ID: %d, TYPE AMMO COUNT: %d\n", MASTER.Types[Type].Name, Type + 1, MASTER.Types[Type].AmmoCount);
        if (List_Ammo == true) {
            ListAmmo(Type + 1);
        }
    }

    printf("\n");

}

#endif
