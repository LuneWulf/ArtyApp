char *introPage(void) {

    char ThrowAway;

    printf("                        WELCOME!\n\n");
    printf("    THIS PROGRAM IS AN ARTILLERY COMPUTER FOR ARMA 3,\n");
    printf("    IT SUPPORTS THE USE OF EITHER ACE3 OR STANDARD\n");
    printf("    ARMA 3 PHYSICS.\n\n");
    printf("    THIS PROGRAM ALLOWS YOU TO INPUT YOUR GUN TYPES\n");
    printf("    AND AMMO TYPES WHICH DEFINE THE MUZZLE VELOCITY\n");
    printf("    AND THE AIRFRICTION OF THE ROUND BEING USED.\n\n");
    printf("    N   GUN TYPES AND ASSOCIATED AMMUNITION TYPES ARE\n");    
    printf("    O   STORED IN THE FILE NAME TYPES&AMMO.DAT, WHICH\n");
    printf("    T   CAN EASILY BE EDITED BY YOU IN ANY TEXT\n");
    printf("    E   EDITOR OF YOUR CHOOSING.\n\n");
    printf("    FIRE MISSIONS ARE SAVED FOR THE DURATION THAT THE\n");
    printf("    PROGRAM IS RUNNING, AFTER WHICH ALL OF THE\n");
    printf("    COMPUTED FIRE MISSIONS ARE DISCARDED.\n\n");
    printf("    TO AID THE FDC, THE TARGETS CAN BE ASSIGNED TO A\n");
    printf("    GUN AUTOMATICALLY OR MANUALLY AND THE COMPUTER\n");
    printf("    COMES WITH PRE-DEFINED FIRE METHODS.\n\n");
    printf("    FOR ANY QUESTIONS AND/OR CONCERNS PLEASE CONTACT\n");
    printf("    ME ON DISCORD _LEMONBOI\n\n");

    printf("    PRESS ENTER TO CONTINUE");
    scanf("%c", &ThrowAway);

    return "Directory";
}

char *DirectoryPage(void) {

    printf("    ->->->->->->->->->-> DIRECTORY PAGE <-<-<-<-<-<-<-<-<-<-\n\n");
    printf("    ><>< QUICK COMMANDS ><><\n\n");
    printf("    CREATE QUICK FIRE MISSION (1 TGT 1 GUN): 1\n\n");
    printf("    ><>< PAGE COMMANDS ><><\n\n");
    printf("    SETTINGS: 2\n");
    printf("    STORAGE: 3\n");
    printf("    FIRE MISSION: 4\n");
    printf("    GUIDE: 5\n\n");
    printf("    ><>< OTHER COMMANDS ><><\n");
    printf("    LOAD STORAGE: 6\n");
    printf("    SAVE STORAGE: 7\n");
    printf("    SAVE STORAGE AND EXIT PROGRAM: 8\n");
    printf("    EXIT PROGRAM WITHOUT SAVING: 9\n\n");

    int command = EnterCommand(1, 9);
    
    switch (command) {
        case 1: return "QuickFireMission";
        case 2: return "Settings";
        case 3: return "Storage";
        case 4: return "FireMission";
        case 5: return "Guide";
        case 6: load();
        case 7: Save();
                return "Directory";
        case 8: 
                Save();
                exit(0);
        case 9: exit(0);
    }
}

/* char *QuickFireMissionPage(void) {

    int GunID, TgtID, type;

    if (*GunStorage == NULL) {

        char Grid[10];
        long int Elevation;

        RETURN_ONE:

        printf("    NO GUNS STORED, ADD GUN TO USE:\n\n");
        printf("    ENTER GRID (2 TO 10 DIGIT GRID): ");
        scanf("%10s", &Grid);

        long int x, y;
        int test = GridToCoordinates(Grid, &x, &y);

        if (test == 1) goto RETURN_ONE;

        printf("    ENTER ELEVATION (METERS): ");
        scanf("%ld", &Elevation);
        printf("\n");

        while (Elevation > 8849 || Elevation < -10984) {
            printf("    ENTER ELEVATION (METERS): ");
            scanf("%ld", &Elevation);
            printf("\n");

            // Elevation cant be greater than Mt. Everet's or less than The Mariana Trench's...
            if (Elevation > 8849) {
                printf("    ERROR: ELEVATION TO HIGH, MUST NOT BE GREATER THAN 8849 M!");
            } else if (Elevation < -10984) {
                printf("    ERROR: ELEVATION TO LOW, MUST NOT BE LESS THAN -10984 M!");
            }
        }

        if (MASTER.TypeCount == 0) {
            AddType();
        } else {
            printf("    CHOOSE TYPE FROM LIST:\n\n");

            ListAllTypes("");
            
            RETURN_THREE:


            while (type > count || type < 1)

            printf("    ENTER TYPE: ");
            scanf("%d", type);
            printf("\n\n")

            if (type > count || type < 1) {
                printf("    ERROR: TYPE DOES NOT EXIST!\n\n");
                goto RETURN_THREE;
            }

            printf("    CHOOSE AMMO FROM LIST:\n\n");

            for (int i = 0; *(TypeStorage + type - 1)->Ammo + i) != NULL; i++) {
                printf("    TYPE: %d,    NAME: %c\n", i + 1, *(TypeStorage + i).name);
                count++
            }

            //for (int i = 0; i < (sizeof(*(TypeStorage + type - 1)->ammo) - sizeof(char) - sizeof(double))/sizeof(struct Charge)) {
            //    prinf("    AMMO: %d,    NAME: %c\n", i + 1, *(TypeStorage + type - 1)->ammo.name);
            //}


        }



        AddGun(Grid, Elevation, type)

    } else {
        
        printf("    CHOOSE GUN FROM LIST:\n\n")
        
        int x, y;

        for (i = 0; i < sizeof(GunStorage)/sizeof(struct Gun); i++) {
            GunID = *(GunStorage + i).id;
            x = *(GunStorage + i).x;
            y = *(GunStorage + i).y;
            type = *(GunStorage + i).Type;
            printf("    GUN %d:    GRID: %d%d    TYPE: %d\n", GunID, x, y, type)
        }
        printf("    ENTER GUN ID: ");
        scanf("%d", GunID);
    }

    if (*TgtStorage == NULL) {

    } else {

    }

    long int grid;
    int x, y, z;
    printf("ENTER TGT GRID: ");
    scanf("%ld", &grid);
    GridToCoordinates(tempGRID, &x, &y);
    printf("")

} */

char *SettingsPage(void) {
    
    printf("    ->->->->->->->->->-> SETTINGS <-<-<-<-<-<-<-<-<-<-\n\n");
    printf("    ><>< SETTINGS AND THEIR COMMAND ID ><><\n\n");
    printf("    FORMAT: NAME, VALUE: COMMAND ID\n\n");
    printf("    VALUE FORMAT: 1 = TRUE, 0 = FALSE\n\n");
    printf("    ACE3 DRAG,    %d:    1\n", Settings.Ace3Drag);
    printf("    ACE3 WEATHER,    %d:    2\n\n\n", Settings.Ace3Weather);
    printf("    ><>< OTHER COMMANDS ><><\n\n");
    printf("    GO BACK: 3\n\n");
    
    int command = EnterCommand(1, 3);

    int value;

    switch (command) {
        case 1: 
            
            while (true) {
                printf("    ENTER NEW VALUE FOR ACE3 DRAG: ");
                scanf("%d", &value);

                if (value != 1 && value != 0) {
                    printf("    ERROR: VALUE MUST BE EITHER 1 OR 0!\n\n");
                } else {
                    Settings.Ace3Drag = value;
                    break;
                }
            }

            return "Settings";

        case 2:
            
            while (true) {
                printf("    ENTER NEW VALUE FOR ACE3 WEATHER: ");
                scanf("%d", &value);

                if (value != 1 && value != 0) {
                    printf("    ERROR: VALUE MUST BE EITHER 1 OR 0!\n\n");
                } else {
                    Settings.Ace3Weather = value;
                    break;
                }
            }

            return "Settings";

        case 3: return "Directory";
    }
}

char *StoragePage(void) {

    printf("    ->->->->->->->->->-> STORAGE <-<-<-<-<-<-<-<-<-<-\n\n");
    printf("    ><>< COMMANDS ><><\n\n");
    printf("    TYPE STORAGE: 1\n");
    printf("    GUN STORAGE: 2\n");
    printf("    TARGET STORAGE: 3\n");
    printf("    GO BACK: 4\n\n");

    int command = EnterCommand(1, 4);

    switch (command) {
        case 1: return "TypeStorage";
        case 2: return "GunStorage";
        case 3: return "TargetStorage";
        case 4: return "Directory";
    }
}

char *TypeStoragePage(void) {

    int command;

    printf("\
    ->->->->->->->->->-> GUN TYPES <-<-<-<-<-<-<-<-<-<-\n\
    \n\
    ><>< GUN TYPES ><><\n\
    \n");

    if (MASTER.TypeCount == 0) {
        printf("    NO GUN TYPES DEFINED\n");

        printf("\n");

        printf("    ><>< COMMANDS ><><\n\n");
        printf("    ADD GUN TYPE: 1\n\n");
        printf("    GO BACK: 2\n\n");

        command = EnterCommand(1, 2);

        switch (command) {
            case 1: 
                AddType();
                printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
                return "TypeStorage";

            case 2: return "Storage";
        }
    } else {

        ListAllTypes(1);

        printf("\n");

        if (MASTER.TypeCount == MAX_TYPES) {
            printf("    ><>< COMMANDS ><><\n");
            printf("\n");
            printf("    REMOVE GUN TYPE: 1\n");
            printf("    EDIT GUN TYPE NAME: 2\n");
            printf("    ADD AMMO: 3\n");
            printf("    EDIT AMMO NAME: 4\n");
            printf("    EDIT AMMO AIR FRICTION: 5\n");
            printf("    ADD AMMO CHARGE: 6\n");
            printf("    EDIT AMMO CHARGE: 7\n");
            printf("\n");
            printf("    GO BACK: 8\n\n");

            command = EnterCommand(1, 8) + 1;  

        } else {
            printf("    ><>< COMMANDS ><><\n");
            printf("\n");
            printf("    ADD GUN TYPE: 1\n");
            printf("    REMOVE GUN TYPE: 2\n");
            printf("    EDIT GUN TYPE NAME: 3\n");
            printf("    ADD AMMO: 4\n");
            printf("    EDIT AMMO NAME: 5\n");
            printf("    EDIT AMMO AIR FRICTION: 6\n");
            printf("    ADD AMMO CHARGE: 7\n");
            printf("    EDIT AMMO CHARGE: 8\n");
            printf("\n");
            printf("    GO BACK: 9\n\n");

            command = EnterCommand(1, 9);

        }


        int type, ammo, charge, len, test;
        double AirFriction;
        char TypeName[50], AmmoName[50], Answer;

        switch (command) {
            case 1: // Add gun type
                AddType();
                return "TypeStorage";

            case 2: // Remove gun type
                
                while (true) {
                    type = EnterType();
                    clear();

                    while (true) {
                        printf("    ARE YOU SURE YOU WISH TO REMOVE %s? (Y/N): ", MASTER.Types[type - 1].Name);
                        scanf("%c", &Answer);
                        clear();

                        if (Answer == 'Y') {
                            break;
                        } else if (Answer != 'N') {
                            printf("    ERROR: ANSWER WAS NOT Y OR N!\n\n");
                        } else {
                            break;
                        }
                    }

                    printf("Test\n");

                    if (Answer == 'Y') {
                        break;
                    }
                }

                strcpy(MASTER.Types[type - 1].Name, "\0");

                for (int i = 0; i < MASTER.Types[type - 1].AmmoCount; i++) {
                    strcpy(MASTER.Types[type - 1].Ammo[i].Name, "\0");
                    MASTER.Types[type - 1].Ammo[i].AirFriction = 0;

                    for (int n = 0; n < MASTER.Types[type - 1].Ammo[i].ChargeCount; n++) {
                        MASTER.Types[type - 1].Ammo[i].Charge[n] = 0;
                        MASTER.Types[type - 1].Ammo[i].ChargeMaxRange[n] = 0;
                    }
                }

                MASTER.Types[type - 1].AmmoCount = 0;
                
                // Move back all other types one place if they had
                // a larger id than the removed type so no gaps exist.
                for (int i = type; i < MASTER.TypeCount; i++) {
                    MASTER.Types[i - 1] = MASTER.Types[i];
                }

                MASTER.TypeCount--;

                return "TypeStorage";

            case 3: // Edit gun type name
                type = EnterType();

                while (true) {
                    printf("    ENTER NEW TYPE NAME (MAX 50 CHARACTERS): ");
                    scanf("%50s", &TypeName);
                    clear();

                    printf("    NEW STORED TYPE NAME: %s\n", TypeName);
                    printf("    IS THE NEW STORED NAME CORRECT? (Y/N): ");
                    scanf("%c", &Answer);
                    printf("\n");

                    if (Answer == 'Y') {
                        break;
                    } else if (Answer != 'N') {
                        printf("    ERROR: ANSWER WAS NOT Y OR N!\n\n");
                    }
                }

                strcpy(MASTER.Types[type - 1].Name, TypeName);

                return "TypeStorage";

            case 4: // Add ammo type to gun type
                type = EnterType();

                AddAmmo(type);

                while (true) {
                    
                    printf("    DO YOU WISH TO ADD ANOTHER AMMO TYPE TO THIS GUN TYPE? (Y/N): ");
                    scanf("%c", &Answer);
                    clear();

                    if (Answer == 'Y') {
                        AddAmmo(type);
                    } else if (Answer == 'N') {
                        break;
                    } else {
                        printf("    ERROR: ANSWER WAS NOT Y OR N!\n\n");
                    }   
                }

                return "TypeStorage";

            case 5: // Edit ammo type name
                type = EnterType();
                ammo = EnterAmmo(type);

                while (true) {
                    printf("    ENTER NEW AMMO TYPE NAME (MAX 50 CHARACTERS): ");
                    scanf("%50s", &AmmoName);
                    clear();

                    printf("    NEW STORED AMMO TYPE NAME: %s\n", AmmoName);
                    printf("    IS THE NEW STORED NAME CORRECT? (Y/N): ");
                    scanf("%c", &Answer);
                    printf("\n");

                    if (Answer == 'Y') {
                        break;
                    }
                }

                strcpy(MASTER.Types[type - 1].Ammo[ammo - 1].Name, AmmoName);

                return "TypeStorage";

            case 6: // Edit ammo type air friction
                type = EnterType();
                
                while (true) {
                    ammo = EnterAmmo(type);

                    while (true) {
                        while (true) {
                            printf("    ENTER AMMO AIR FRICTION: ");
                            scanf("%lf", &AirFriction);
                            clear();

                            if (AirFriction <= 0) {
                                break;
                            } else {
                                printf("    ERROR: AIR FRICTION MUST BE LESS THAN OR EQUAL TO 0\n\n");
                            }
                        }

                        printf("    STORED AMMO AIR FRICTION: %lf\n", AirFriction);
                        printf("    IS THE STORED AMMO AIR FRICTION CORRECT? (Y/N): ");
                        scanf("%c", &Answer);
                        printf("\n");

                        if (Answer == 'Y') {
                            break;
                        } else if (Answer != 'N') {
                            printf("    ERROR: ANSWER WAS NOT Y OR N!\n\n");
                        }
                    }

                    if (Answer == 'Y') {
                        break;
                    }

                    MASTER.Types[type - 1].Ammo[ammo - 1].AirFriction = AirFriction;
                }

                return "TypeStorage";

            case 7: // Add charge to ammo type
               
                type = EnterType();

                while (true) {
                    ammo = EnterAmmo(type);

                    if (MASTER.Types[type - 1].Ammo[ammo - 1].ChargeCount >= MAX_CHARGES) {
                        printf("    ERROR: AMMO HAS MAXIMUM AMOUNT OF CHARGES!\n\n");
                    } else {
                        break;
                    }
                }


                AddCharge(type, ammo);

                while (true) {

                    clear();

                    printf("    DO YOU WISH TO ADD ANOTHER CHARGE? (MAX %d) (Y/N): ", MAX_CHARGES);
                    scanf("%c", &Answer);
                    printf("\n");

                    if (Answer == 'N') {
                        break;
                    } else if (Answer == 'Y') {
                        clear();
                        AddCharge(type, ammo);
                    } else {
                        printf("    ERROR: ANSWER WAS NOT Y OR N!\n\n");
                    }

                }

                return "TypeStorage";

            case 8: // Edit ammo type charge
                type = EnterType();
                ammo = EnterAmmo(type);

                while (true) {
                    printf("    ENTER CHARGE: ");
                    scanf("%d", &charge);
                    printf("\n");

                    if (charge > 0 && charge <= MASTER.Types[type - 1].Ammo[ammo - 1].ChargeCount) {
                        break;
                    } else {
                        printf("    ERROR: CHARGE NOT DEFINED\n\n");
                    }
                }

                printf("    ENTER NEW MUZZLE VELOCITY FOR CHARGE %d: ", charge);
                scanf("%lf", &MASTER.Types[type - 1].Ammo[ammo - 1].Charge[charge - 1]);

                return "TypeStorage";

            case 9:
                return "Storage";
        }
    }
}

char *GunStoragePage(void) {
    
    printf("\
    ->->->->->->->->->-> GUN STORAGE <-<-<-<-<-<-<-<-<-<-\n\
    \n\
    ><>< GUNS ><><\n\
    \n");

    if (MASTER.TypeCount == 0) {
        printf("    NO GUN TYPES ARE DEFINED THEREFORE NO GUNS\n");
        printf("    ARE DEFINED NOR CAN NEW GUNS BE DEFINED\n");
        printf("\n");
        printf("    ><>< COMMANDS ><><\n\n");
        printf("    GO BACK: 1\n\n");

        int command = EnterCommand(1, 1);

        switch (command) {
            case 1: return "Storage";
        }

    } else if (MASTER.GunCount == 0) {

        printf("    NO GUNS DEFINED\n");
        printf("\n");
        printf("    ><>< COMMANDS ><><\n\n");
        printf("    ADD GUN: 1\n");
        printf("    GO BACK: 2\n");
        printf("\n\n");

        int command = EnterCommand(1, 2);

        switch (command) {
            case 1:
                AddGun();
                return "GunStorage";
            case 2: 
                return "Storage";
        }

    } else {
        
        for (int Gun = 0; Gun < MASTER.GunCount; Gun++) {
            printf("    GUN %d:    TYPE: %c,    GRID: %10s,    ELEVATION: %ld\n", Gun + 1, MASTER.Types[MASTER.Gun[Gun].Type].Name, MASTER.Gun[Gun].Grid, MASTER.Gun[Gun].z);
        }

        printf("\n");

        int command;

        if (MASTER.GunCount == MAX_GUNS) {
            printf("    ><>< COMMANDS ><><\n\n");
            printf("    REMOVE GUN: 1\n");
            printf("    EDIT GUN GRID: 2\n");
            printf("    EDIT GUN ELEVATION: 3\n");
            printf("    EDIT GUN TYPE: 4\n");
            printf("    GO BACK: 5\n\n");

            command = EnterCommand(1, 5) + 1;
        } else {
            printf("    ><>< COMMANDS ><><\n\n");
            printf("    ADD GUN: 1\n");
            printf("    REMOVE GUN: 2\n");
            printf("    EDIT GUN GRID: 3\n");
            printf("    EDIT GUN ELEVATION: 4\n");
            printf("    EDIT GUN TYPE: 5\n");
            printf("    GO BACK: 6\n\n");

            command = EnterCommand(1, 6);
        }

        int GunID, type, len;
        long int Elevation, x, y;
        char Grid[10], Answer;

        switch (command) {
            case 1: // Add gun
                AddGun();
                return "GunStorage";

            case 2: // Remove gun
                
                clear();

                while (true) {
                    GunID = EnterGunID();

                    printf("    CONFIRM REMOVE GUN %d (Y/N): ", GunID);
                    scanf("%c", &Answer);
                    clear();

                    if (Answer == 'Y') {
                        break;
                    } else if (Answer == 'N') {
                        return "GunStorage";
                    } else {
                        printf("    ERROR: ANSWER WAS NOT Y OR N!\n\n");
                    }
                }

                if (GunID < MASTER.GunCount) {

                    MASTER.Gun[GunID - 1] = (struct Gun) {'\0', 0, 0, 0, 0};

                    for (int Gun = GunID; Gun < MASTER.GunCount; Gun++) {
                        
                        MASTER.Gun[Gun - 1] = MASTER.Gun[Gun];
                    }

                    MASTER.GunCount--;
                }                
            
                return "GunStorage";

            case 3: // Edit gun grid
                GunID = EnterGunID();

                while (true) {
                    printf("    ENTER NEW GRID FOR GUN %d (MAX 10 DIGITS, MIN 2 DIGITS): ", GunID);
                    scanf("%10c", &Grid);
                    printf("\n");

                    printf("    CONFIRM GRID %c IS CORRECT (Y/N): ", Grid);
                    scanf("%c", &Answer);
                    clear();

                    if (Answer == 'Y') {
                        break;
                    } else if (Answer != 'N') {
                        printf("    ERROR: ANSWER WAS NOT Y OR N!\n\n");
                    }
                }

                GridToCoordinates(Grid, &x, &y);

                MASTER.Gun[GunID - 1] = (struct Gun) {x, y, MASTER.Gun[GunID - 1].z, MASTER.Gun[GunID - 1].Type};

                return "GunStorage";

            case 4: // Edit gun elevation
                GunID = EnterGunID();
                
                printf("    ENTER NEW ELEVATION FOR GUN %d: ", GunID);
                scanf("%ld", &Elevation);
                clear();

                MASTER.Gun[GunID - 1].z = Elevation;

                return "GunStorage";

            case 5: // Edit gun type
                GunID = EnterGunID();

                ListAllTypes(0);
                type = EnterType();

                MASTER.Gun[GunID - 1].Type = type - 1;

                return "GunStorage";

            case 6:
                return "Storage";
        }
    }
}

char *TargetStoragePage(void) {

    int command;

    printf("    ->->->->->->->->->-> TARGET STORAGE <-<-<-<-<-<-<-<-<-<-\n\n");
    printf("    ><>< TARGETS ><><\n\n");

    if (MASTER.TargetCount == 0) {
        printf("    NO TARGETS DEFINED\n\n");
        printf("    ><>< COMMANDS ><><\n\n");
        printf("    ADD TARGET: 1\n");
        printf("    GO BACK: 2\n\n");

        command = EnterCommand(1, 2);

        switch (command) {
            case 1: 
                AddTarget();
                return "TargetStorage";

            case 2: 
                return "Directory";
        }
    } else {

        for (int Target = 0; Target < MASTER.TargetCount; Target++) {
            printf("    TARGET %d:    GRID: %10s,    ELEVATION: %ld\n", Target + 1, MASTER.Target[Target].Grid, MASTER.Target[Target].z);
        }

        printf("\n");

        if (MASTER.TargetCount == MAX_TARGETS) {
            printf("    ><>< COMMANDS ><><\n\n");
            printf("    REMOVE TARGET: 1\n");            
            printf("    EDIT TARGET GRID: 2\n");
            printf("    EDIT TARGET ELEVATION: 3\n");
            printf("    GO BACK: 4\n\n");

            command = EnterCommand(1, 4) + 1;

        } else {
            printf("    ><>< COMMANDS ><><\n\n");
            printf("    ADD TARGET: 1\n");
            printf("    REMOVE TARGET: 2\n");
            printf("    EDIT TARGET GRID: 3\n");
            printf("    EDIT TARGET ELEVATION: 4\n");
            printf("    GO BACK: 5\n\n");

            command = EnterCommand(1, 5);

        }

        int TargetID;
        long int x, y, z;
        char Grid[10], Answer;

        switch (command) {
            case 1: // Add target
                AddTarget();
                return "TargetStorage";

            case 2: // Remove target
                
                while (true) {
                    TargetID = EnterTargetID();

                    printf("    ARE YOU SURE YOU WISH TO REMOVE TARGET %d? (Y/N): ", TargetID);
                    scanf("%1c", &Answer);

                    if (Answer == 'Y') {
                        return "TargetStorage";
                    } else if (Answer != 'N') {
                        printf("    ERROR: ANSWER WAS NOT Y OR N!\n\n");
                    }
                }

                MASTER.Target[TargetID - 1] = (struct Target) {0, 0, 0};

                for (int target = TargetID; target < MASTER.TargetCount; target++) {
                    MASTER.Target[target - 1] = MASTER.Target[target];
                }

                MASTER.TargetCount--;

                return "TargetStorage";

            case 3: // Edit target grid
                TargetID = EnterTargetID();

                while (true) {

                    printf("    ENTER NEW GRID (MAX 10 DIGITS, MIN 2 DIGITS): ");
                    scanf("%10s", &Grid);
                    printf("\n");

                    if (strlen(Grid) == 0) {
                        *Grid = '0';
                    }

                    printf("    IS GRID %s CORRECT? (Y/N): ", &Grid);
                    scanf("%1c", &Answer);
                    printf("\n");

                    if (Answer == 'Y') {
                        break;
                    } else if (Answer != 'N') {
                        printf("    ERROR: ANSWER WAS NOT Y OR N!\n\n");
                    }
                }

                GridToCoordinates(Grid, &x, &y);

                strcpy(MASTER.Target[TargetID - 1].Grid, Grid);
                MASTER.Target[TargetID - 1].x = x;
                MASTER.Target[TargetID - 1].x = y;
                
                return "TargetStorage";

            case 4: // Edit target elevation
                TargetID = EnterTargetID();

                while (true) {
                    printf("    ENTER NEW ELEVATION: ");
                    scanf("%ld", &z);
                    printf("\n");

                    clear();

                    printf("    IS ELEVATION %ld CORRECT? (Y/N): ", z);
                    scanf("%1c", &Answer);
                    printf("\n");

                    clear();

                    if (Answer == 'Y') {
                        break;
                    } else if (Answer != 'N') {
                        printf("    ANSWER WAS NOT Y OR N!\n\n");
                    }
                }

                MASTER.Target[TargetID - 1].z = z;

            case 5: return "Directory";
        }
    }
}

char *FireMissionPage(void) {

}

char *GuidePage(void) {

}
