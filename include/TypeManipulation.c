int AddCharge(int Type, int Ammo) {

    if (MASTER.Types[Type - 1].Ammo[Ammo - 1].ChargeCount >= MAX_CHARGES) {
        return -1; // ERROR: CHARGE LIMIT EXCEEDED
    }

    long int MuzzleVelocity;

    while (true) {
        printf("    ENTER CHARGE %d MUZZLE VELOCITY: ", MASTER.Types[Type - 1].Ammo[Ammo - 1].ChargeCount);
        scanf("&ld", &MuzzleVelocity); 

        if (MuzzleVelocity <= 0) {
            printf("    ERROR: INVALID CHARGE MUZZLE VELOCITY!\n");
        } else {
            break;
        }
    }

    MASTER.Types[Type - 1].Ammo[Ammo - 1].ChargeCount++;

    return 0;
}

int AddAmmo(int Type) {
    
    // Adds a new ammo type at the end of the type's ammo array,
    // then adds at least 1 charge.

    if (MASTER.Types[Type - 1].AmmoCount == MAX_AMMO) {
        return -1; // ERROR: Ammo limit exceeded
    }
    
    double AirFriction;

    char AmmoName[50];

    char Answer;

    while (true) {
        printf("    ENTER AMMO NAME (MAX 50 CHARACTERS): ");
        fgets(AmmoName, sizeof(AmmoName), stdin);

        size_t len = strlen(AmmoName);
        if (len > 0 && AmmoName[len - 1] == '\n') {
            AmmoName[len - 1] = '\0';
        }

        printf("    STORED AMMO NAME: %s\n", AmmoName);
        printf("    IS THE STORED NAME CORRECT? (Y/N): ");
        scanf("%c", &Answer);
        printf("\n");

        if (Answer == 'Y') {
            break;
        }
    }

    strcpy(MASTER.Types[Type - 1].Ammo[MASTER.Types[Type - 1].AmmoCount].Name, AmmoName);

    while (true) {
        printf("    ENTER AMMO AIR FRICTION: ");
        scanf("%lf", &AirFriction);

        printf("    STORED AMMO AIR FRICTION: %lf\n", AirFriction);
        printf("    IS THE STORED AMMO AIR FRICTION CORRECT? (Y/N): ");
        scanf("%c", &Answer);
        printf("\n");

        if (AirFriction <= 0 && Answer == 'Y') {
            break;
        } else if (Answer == 'Y') {
            printf("    ERROR: AIR FRICTION MUST BE LESS THAN OR EQUAL TO 0\n");
        } else {
            printf("    ERROR: ANSWER ")
        }
    }

    MASTER.Types[Type - 1].Ammo[MASTER.Types[Type - 1].AmmoCount].AirFriction = AirFriction;

    int ChargeCount;

    printf("\n    NOW DEFINE CHARGE VELOCITIES, MAX 20 CHARGES!\n");
    printf("    TO STOP DEFINING CHARGES ENTER -1 INSTEAD OF A VELOCITY\n");
    printf("    MINIMUM OF 1 CHARGE:\n\n");

    for (int i = 0; i < 20; i++, ChargeCount++) {
        
        long int TempVel = 0;

        while (true) {
            printf("    ENTER CHARGE %d MUZZLE VELOCITY: ", i+1);
            scanf("%ld", &TempVel);

            if (i != 0 && TempVel == -1) {
                break;
            } else if (TempVel <= 0) {
                printf("    ERROR: INVALID CHARGE MUZZLE VELOCITY!\n");
            } else {
                break;
            }
        }

        MASTER.Types[Type - 1].Ammo[MASTER.Types[Type - 1].AmmoCount].Charge[i] = TempVel;
    }

    MASTER.Types[Type - 1].AmmoCount++;
}

int AddType(void) {

    // Adds a new type at the end of the Type array,
    // then adds at least 1 ammo type with at least 1 charge.

    if (MASTER.TypeCount == MAX_TYPES) {
        return -1; // ERROR: Max amount of types reached
    }

    char TypeName[50];

    char Answer;

    while (true) {
        printf("    ENTER TYPE NAME (MAX 50 CHARACTERS): ");
        fgets(TypeName, sizeof(TypeName), stdin);

        size_t len = strlen(TypeName);
        if (len > 0 && TypeName[len - 1] == '\n') {
            TypeName[len - 1] = '\0';
        }

        printf("    STORED TYPE NAME: %s\n", TypeName);
        pritnf("    IS THE STORED NAME CORRECT? (Y/N): ");
        scanf("%c", &Answer);
        printf("\n");

        if (Answer == 'Y') {
            break;
        }
    }

    strcpy(MASTER.Types[MASTER.TypeCount].Name, TypeName);

    printf("\n    DEFINE A NEW AMMO TYPE FOR THE NEW TYPE:\n");

    AddAmmo(MASTER.TypeCount);

    char Answer;

    while (true) {
        printf("    DO YOU WISH TO ADD ANOTHER AMMO TYPE? (Y/N): ");
        scanf("%c", &Answer);
        printf("\n");

        if (Answer == 'Y' || Answer == 'N') {
            break;
        } else {
            printf("    ERROR: ANSWER WAS NOT Y OR N!\n\n");
        }        
    }

    for (int i = 0; i < 4 && Answer == 'Y'; i++) {
        
        while(getchar() != '\n');
        AddAmmo(MASTER.TypeCount);

        while (true) {
            printf("    DO YOU WISH TO ADD ANOTHER AMMO TYPE? (Y/N): ");
            scanf("%c", &Answer);
            printf("\n");

            if (Answer == 'Y') {
                AddAmmo(MASTER.TypeCount);
            } else if (Answer == 'N') {
                break;
            } else {
                printf("    ERROR: ANSWER WAS NOT Y OR N!\n\n");
            }        
        }
    }

    MASTER.TypeCount++;
}

int ChargeMaxRange(int type, int ammo, int charge) {

    long int MaxRange;

    // Call function for ballistics simulator at angle of 45 deg.
    // IRL max range does not occur at 45 deg, bur normally around 30 deg,
    // but this does not apply to ARMA 3 with and without ACE 3 physics.

    MASTER.Types[type - 1].Ammo[ammo - 1].ChargeMaxRange[charge - 1] = MaxRange;

}
