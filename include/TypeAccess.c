
int ListAllAmmo(int Type) {

    // Ammo types are listed in series but with IDs starting from 1 NOT 0.

    if (MASTER.Types[Type].AmmoCount == 0) {
        return -1; // ERROR: No ammo defined for the type.
    }

    for (int Ammo = 0; Ammo < MASTER.Types[Type - 1].AmmoCount; Ammo++) {
        printf("    AMMO NAME: %s, AMMO ID: %d\n\n", MASTER.Types[Type - 1].Ammo[Ammo].Name, Ammo + 1);
    }

    return 0;
}

int ListAllTypes(char *string) {

    // Types are listed in series but with IDs starting from 1 NOT 0.
    
    if (MASTER.TypeCount == 0) {
        return - 1; // ERROR: No types defined.
    }

    for (int Type = 0; Type < MAX_TYPES && MASTER.Types[Type].AmmoCount != 0; Type++) {
        printf("    TYPE NAME: %s,\tTYPE ID: %d\n", MASTER.Types[Type].Name, Type + 1);
        if (string == "ListAllAmmo") {
            ListAllAmmo(Type + 1);
        }
    }

    printf("\n");

    return 0;
}

int ListCharges(int Type, int Ammo) {

    // Ammo types are listed in series but with IDs starting from 1 NOT 0.

    if (MASTER.Types[Type].AmmoCount == 0) {
        return -1; // ERROR: No ammo defined for the type therefore no charges exist.
                   //        However, there will always be at least 1 charge for a defined ammo.
    }
    
    for (int Charge = 0; Charge < MAX_CHARGES && MASTER.Types[Type - 1].Ammo[Ammo - 1].Charge[Charge] != 0; Charge++) {
        printf("        CHARGE: %d, MAX RANGE: %ld\n", Charge + 1, MASTER.Types[Type - 1].Ammo[Ammo - 1].ChargeMaxRange[Charge]);
    }

    return 0;
}