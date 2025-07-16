#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

// Additional #includes are located at line 76 due to the functions in them using the MASTER struct.

#define MAX_TYPES 25
#define MAX_AMMO 5
#define MAX_CHARGES 20

#define MAX_GUNS 10
#define MAX_TARGETS 50

#define MAX_GUN_GROUPS 10
#define MAX_TARGET_GROUPS 10

struct Ammo {
    char Name[50];
    double AirFriction;
    int ChargeCount;
    long int Charge[MAX_CHARGES];
    long int ChargeMaxRange[MAX_CHARGES];
};

struct Type {
    char Name[50];
    int AmmoCount;
    struct Ammo Ammo[MAX_AMMO];
};

struct Gun {
    long int x;
    long int y;
    long int z;
    int Type;
};

struct Target {
    long int x;
    long int y;
    long int z;
};

struct GunGroup {
    int GunID[MAX_GUNS];
};

struct TargetGroup {
    int TargetID[MAX_TARGETS];
};

struct MASTER {
    int TypeCount;
    struct Type Types[MAX_TYPES];

    int TargetCount;
    struct Target Target[MAX_TARGETS];

    int GunCount;
    struct Gun Gun[MAX_GUNS];

    int GunGroupCount;
    struct GunGroup GunGroup[MAX_GUN_GROUPS];

    int TargetGroupCount;
    struct TargetGroup TargetGroup[MAX_TARGET_GROUPS];
} MASTER;

struct Settings {
    int Ace3Drag;
    int Ace3Weather;
} Settings;

#include "include\Tools.c"
#include "include\TypeManipulation.c"
#include "include\TypeAccess.c"
#include "include\GunManipulation.c"
#include "include\TargetManipulation.c"

int main(void) {

    initStorage();

    int command;

    introPage();

    return 0;
}

void initStorage(void) {
    
    //Initialize all values to either 0, for numbers, or \0, for strings.
    
    MASTER.TypeCount = 0;

    for (int Type = 0; Type < MAX_TYPES; Type++) {
        strcpy(MASTER.Types[Type].Name, "\0");
        MASTER.Types[Type].AmmoCount = 0;

        for (int Ammo = 0; Ammo < MAX_AMMO; Ammo++) {
            strcpy(MASTER.Types[Type].Ammo[Ammo].Name, "\0");
            MASTER.Types[Type].Ammo[Ammo].AirFriction = 0;
            MASTER.Types[Type].Ammo[Ammo].ChargeCount = 0;

            for (int Charge = 0; Charge < MAX_CHARGES; Charge++) {
                MASTER.Types[Type].Ammo[Ammo].Charge[Charge] = 0;
                MASTER.Types[Type].Ammo[Ammo].ChargeMaxRange[Charge] = 0;
            }
        }
    }

    MASTER.TargetCount = 0;

    for (int Target = 0; Target < MAX_TARGETS; Target++) {
        
        MASTER.Target[Target] = (struct Target) {0, 0, 0};
    }

    MASTER.GunCount = 0;

    for (int Gun = 0; Gun < MAX_GUNS; Gun++) {
        
        MASTER.Gun[Gun] = (struct Gun) {0, 0, 0, 0};
    }    

    MASTER.GunGroupCount = 0;

    for (int GunGroup = 0; GunGroup < MAX_GUN_GROUPS; GunGroup++) {
        for (int GunID = 0; GunID < MAX_GUNS; GunID++) {
            MASTER.GunGroup[GunGroup].GunID[GunID] = 0;
        }
    }

    MASTER.TargetGroupCount = 0;

    for (int TargetGroup = 0; TargetGroup < MAX_TARGET_GROUPS; TargetGroup++) {
        for (int TargetID = 0; TargetID < MAX_TARGETS; TargetID++) {
            MASTER.TargetGroup[TargetGroup].TargetID[TargetID] = 0;
        }
    }
}

void QuickFireMission(int Gun, int Target, int HighLowAngle) {

}

void FireMission(void) {

}

int introPage(void) {

    printf("\
                        WELCOME!\n\
    \n\
    THIS PROGRAM IS AN ARTILLERY COMPUTER FOR ARMA 3,\n\
    IT SUPPORTS THE USE OF EITHER ACE3 OR STANDARD\n\
    ARMA 3 PHYSICS.\n\
    \n\
    THIS PROGRAM ALLOWS YOU TO INPUT YOUR GUN TYPES\n\
    AND AMMO TYPES WHICH DEFINE THE MUZZLE VELOCITY\n\
    AND THE AIRFRICTION OF THE ROUND BEING USED.\n\
    \n\
        GUN TYPES AND ASSOCIATED AMMUNITION TYPES ARE\n\
        STORED IN THE FILE NAME GUN_AMMO_TYPES.DAT,\n\
        WHICH CAN EASILY BE EDITED BY YOU IN ANY TEXT\n\
        EDITOR OF YOUR CHOOSING.\n\
    \n\
    FIRE MISSIONS ARE SAVED FOR THE DURATION THAT THE\n\
    PROGRAM IS RUNNING, AFTER WHICH ALL OF THE\n\
    COMPUTED FIRE MISSIONS ARE DISCARDED.\n\
    \n\
    TO AID THE FDC, THE TARGETS CAN BE ASSIGNED TO A\n\
    GUN AUTOMATICALLY OR MANUALLY AND THE COMPUTER\n\
    COMES WITH PRE-DEFINED FIRE METHODS.\n\
    \n\
    FOR ANY QUESTIONS AND/OR CONCERNS PLEASE CONTACT\n\
    ME ON DISCORD _LEMONBOI\n\
    \n");

    printf("    PRESS ENTER TO CONTINUE");
    scanf("%c");

    printf("\n");

    DirectoryPage();
}

int DirectoryPage(void) {

    int command = -1;

    printf("\
    ->->->->->->->->->-> DIRECTORY PAGE <-<-<-<-<-<-<-<-<-<-\n\
    \n\
    ><>< QUICK COMMANDS ><><\n\
    \n\
    CREATE QUICK FIRE MISSION (1 TGT 1 GUN): 1\n\
    \n\
    ><>< PAGE COMMANDS ><><\n\
    \n\
    SETTINGS: 2\n\
    STORAGE: 3\n\
    FIRE MISSION: 4\n\
    GUIDE: 5\n\
    \n\
    ><>< OTHER COMMANDS ><><\n\
    SAVE STORAGE: 6\n\
    SAVE STORAGE AND EXIT PROGRAM: 7\n\
    EXIT PROGRAM WITHOUT SAVING: 8\n");
    

    int command = EnterCommand(1, 8);
    
    switch (command) {
        case 1: QuickFireMissionPage();
        case 2: SettingsPage();
        case 3: StoragePage()
        case 4: FireMissionPage();
        case 5: GuidePage();
        case 6: Save();
        case 7: 
            Save();
            abort();
        case 8: abort();
    }
}

int QuickFireMissionPage(void) {

    int GunID, TgtID, type;

    if (*GunStorage == NULL) {

        char Grid;
        long int Elevation;

        RETURN_ONE:

        printf("    NO GUNS STORED, ADD GUN TO USE:\n\n");
        printf("    ENTER GRID (2 TO 10 DIGIT GRID): ");
        scanf("%s", &Grid);

        long int x, y;
        int test = GridToCoordinates(Grid, &x, &y);

        if (test == 1) goto RETURN_ONE;

        printf("    ENTER ELEVATION (METERS): ")
        scanf("%ld", &Elevation)
        printf("\n")

        while (Elevation > 8849 || Elevation < -10984) {
            printf("    ENTER ELEVATION (METERS): ")
            scanf("%ld", &Elevation)
            printf("\n")

            // Elevation cant be greater than Mt. Everet's or less than The Mariana Trench's...
            if (Elevation > 8849) {
                printf("    ERROR: ELEVATION TO HIGH, MUST NOT BE GREATER THAN 8849 M!");
            } else if (Elevation < -10984) {
                printf("    ERROR: ELEVATION TO LOW, MUST NOT BE LESS THAN -10984 M!")
            }
        }

        if (MASTER.TypeCount == 0) {
            AddType(0);
        } else {
            printf("    CHOOSE TYPE FROM LIST:\n\n");

            ListAllTypes();
            
            RETURN_THREE:

            while (TypeStorage)


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

}

int SettingsPage(void) {
    
    printf("\
    ->->->->->->->->->-> SETTINGS <-<-<-<-<-<-<-<-<-<-\n\
    \n\
    ><>< SETTINGS AND THEIR COMMAND ID ><><\n\
    \n\
    FORMAT: NAME, VALUE: COMMAND ID\n\
    \n\
    VALUE FORMAT: 1 = TRUE, 0 = FALSE\n\
    \n\
    ACE3 DRAG,\t%d:\t1\n\
    ACE3 WEATHER,\t%d:\t2\n\
    \n\
    \n\
    ><>< OTHER COMMANDS ><><\n\
    \n\
    RETURN TO DIRECTORY PAGE: 3\n\n", Settings.Ace3Drag, Settings.Ace3Weather);
    
    int command = EnterCommand(0, 2);

    switch (command) {
        case 1: 
            printf("    ENTER NEW VALUE FOR ACE3 DRAG: ");
            scanf("%d", &Settings.Ace3Drag);
            printf("\n");
            SettingsPage();
        case 2:
            printf("    ENTER NEW VALUE FOR ACE3 WEATHER: ");
            scanf("%d", &Settings.Ace3Weather);
            printf("\n");
            SettingsPage();
        case 3: DirectoryPage();
    }
}

int StoragePage(void) {

    printf("\
    ->->->->->->->->->-> STORAGE <-<-<-<-<-<-<-<-<-<-\n\
    \n\
    ><>< COMMANDS ><><\n\
    \n\
    TYPE STORAGE: 1\n\
    GUN STORAGE: 2\n\
    TARGET STORAGE: 3\n\
    \n\
    RETURN TO DIRECTORY PAGE: 4\n\n");

    int command = EnterCommand(1, 4);

    switch (command) {
        case 1: TypeStoragePage();
        case 2: GunStoragePage();
        case 3: TargetStoragePage();
        case 4: DirectoryPage();
    }
}

int TypeStoragePage(void) {
    
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
        printf("    RETURN TO DIRECTORY PAGE: 2\n");

        int command = EnterCommand(1, 2);

        switch (command) {
            case 1: 
                AddType();
                StoragePage();
            case 2: DirectoryPage();
        }
    } else {

        ListAllTypes("ListAllAmmo");

        printf("\n");

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
        printf("    RETURN TO STORAGE PAGE: 9\n");
        printf("    RETURN TO DIRECTORY PAGE: 10\n");

        int command = EnterCommand(1, 10);

        switch (command) {
            case 1: // Add gun type
                AddType();
                TypeStoragePage();
            case 2: // Remove gun type
            case 3: // Edit gun type name
                int type = EnterType();

                char TypeName;

                while (true) {
                    printf("    ENTER NEW TYPE NAME (MAX 50 CHARACTERS): ");
                    fgets(TypeName, sizeof(TypeName), stdin);

                    size_t len = strlen(TypeName);
                    if (len > 0 && TypeName[len - 1] == '\n') {
                        TypeName[len - 1] = '\0';
                    }

                    printf("    NEW STORED TYPE NAME: %s\n", TypeName);
                    pritnf("    IS THE NEW STORED NAME CORRECT? (Y/N): ");
                    scanf("%c", &Answer);
                    printf("\n");

                    if (Answer == 'Y') {
                        break;
                    }
                }

                MASTER.Types[type - 1].Name = TypeName;
                TypeStoragePage();
            case 4: // Add ammo type to gun type
                int type = EnterType();
                AddAmmo(type);

                char Answer;

                while (true) {
                    
                    printf("    DO YOU WISH TO ADD ANOTHER AMMO TYPE TO THIS GUN TYPE? (Y/N): ");
                    scanf("%c", &Answer);

                    if (Answer == 'Y') {
                        AddAmmo(type);
                    } else if (Answer == 'N') {
                        break;
                    } else {
                        printf("    ERROR: ANSWER WAS NOT Y OR N!\n\n");
                    }   
                }

                TypeStoragePage();
            case 5: // Edit ammo type name
                int type = EnterType();
                int ammo = EnterAmmo();

                char AmmoName[50];

                while (true) {
                    printf("    ENTER NEW AMMO TYPE NAME (MAX 50 CHARACTERS): ");
                    fgets(AmmoName, sizeof(AmmoName), stdin);

                    size_t len = strlen(AmmoName);
                    if (len > 0 && AmmoName[len - 1] == '\n') {
                        AmmoName[len - 1] = '\0';
                    }

                    printf("    NEW STORED AMMO TYPE NAME: %s\n", AmmoName);
                    pritnf("    IS THE NEW STORED NAME CORRECT? (Y/N): ");
                    scanf("%c", &Answer);
                    printf("\n");

                    if (Answer == 'Y') {
                        break;
                    }
                }

                MASTER.Types[type - 1].Ammo[ammo - 1].Name = AmmoName;
                
                TypeStoragePage();
            case 6: // Edit ammo type air friction
                int type = EnterType();
                int ammo = EnterAmmo(type);

                printf("    ENTER NEW AIR FRICTION VALUE: ");
                scanf("%lf", &MASTER.Types[type - 1].Ammo[ammo - 1].AirFriction);
                printf("\n");

                TypeStoragePage();
            case 7: // Add charge to ammo type
                int type = EnterType();
                int ammo = EnterAmmo(type);

                char Answer;

                int test = AddCharge(type, ammo);

                while (true) {

                    // Charge limit exceeded error
                    if (test == -1) {
                        TypeStoragePage();
                    }

                    printf("    DO YOU WISH TO ADD ANOTHER CHARGE? (MAX %d) (Y/N): ", MAX_CHARGES);
                    scanf("%c", &Answer);
                    printf("\n");

                    if (&Answer == 'N') {
                        break;
                    } else if (&Answer == 'Y') {
                        test = AddCharge(type, ammo);
                    } else {
                        printf("    ERROR: ANSWER WAS NOT Y OR N!\n\n");
                    }

                }

                TypeStoragePage();
            case 8: // Edit ammo type charge
                int type = EnterType();
                int ammo = EnterAmmo(type);
                int charge;

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

                TypeStoragePage();
            case 9: // Return to storage page
                StoragePage();
            case 10: // Return to directory page
                DirectoryPage();
        }
    }
}

int GunStoragePage(void) {
    
    printf("\
    ->->->->->->->->->-> GUNS <-<-<-<-<-<-<-<-<-<-\n\
    \n\
    ><>< GUNS ><><\n\
    \n");

    if (MASTER.TypeCount == 0) {
        printf("    NO GUN TYPES ARE DEFINED THEREFORE NO GUNS\n");
        printf("    ARE DEFINED NOR CAN NEW GUNS BE DEFINED\n");
        printf("\n");
        printf("    ><>< COMMANDS ><><\n\n");
        printf("    GO TO TYPE STORAGE PAGE: 1");
        printf("    RETURN TO DIRECTORY PAGE: 2\n");

        int command = EnterCommand(1, 2);

        switch (command) {
            case 1: 
                TypeStoragePage();
            case 2:
                DirectoryPage();
        }
    } else if (MASTER.GunCount == 0) {

        printf("    NO GUNS DEFINED\n");
        printf("\n");
        printf("    ><>< COMMANDS ><><\n\n");
        printf("    ADD GUN: 1\n");
        printf("    RETURN TO STORAGE PAGE: 2\n");
        printf("    RETURN TO DIRECTORY PAGE: 3\n");

        int command = EnterCommand(1, 2);

        switch (command) {
            case 1:
                AddGun();
            case 2: 
                TypeStoragePage();
            case 3:
                DirectoryPage();
        }
    } else {
        
        for (int Gun = 0; Gun < MASTER.GunCount; Gun++) {
            printf("    GUN %d:    TYPE: %c,    GRID: %ld%ld,    ELEVATION: %ld\n", Gun + 1, MASTER.Types[MASTER.Gun[Gun].Type].Name, MASTER.Gun[Gun].x, MASTER.Gun[Gun].y, MASTER.Gun[Gun].z);
        }

        printf("\n");

        int command;

        if (MASTER.GunCount == MAX_GUNS) {
            printf("    ><>< COMMANDS ><><\n\n");
            printf("    REMOVE GUN: 1\n");
            printf("    EDIT GUN GRID: 2\n");
            printf("    EDIT GUN ELEVATION: 3\n");
            printf("    EDIT GUN TYPE: 4\n")
            printf("    RETURN TO STORAGE PAGE: 5\n");
            printf("    RETURN TO DIRECTORY PAGE: 6\n");
            printf("\n");

            command = EnterCommand(1, 6) + 1;
        } else {
            printf("    ><>< COMMANDS ><><\n\n");
            printf("    ADD GUN: 1\n");
            printf("    REMOVE GUN: 2\n");
            printf("    EDIT GUN GRID: 3\n");
            printf("    EDIT GUN ELEVATION: 4\n");
            printf("    EDIT GUN TYPE: 5\n")
            printf("    RETURN TO STORAGE PAGE: 6\n");
            printf("    RETURN TO DIRECTORY PAGE: 7\n");
            printf("\n");

            command = EnterCommand(1, 7);
        }

        switch (command) {
            case 1: // Add gun
                AddGun();
                GunStoragePage();
            case 2: // Remove gun
                RemoveGun();
                GunStoragePage();
            case 3: // Edit gun grid
                int GunID = EnterGunID();

                char Grid[10];
                char Answer;

                while (true) {
                    printf("    ENTER NEW GRID FOR GUN %d (MAX 10 DIGITS, MIN 2 DIGITS): ", GunID);
                    scanf("%10c", &Grid);
                    printf("\n");

                    printf("    CONFIRM GRID %c IS CORRECT (Y/N): ", Grid);
                    scanf("%c", &Answer);

                    if (Answer == 'Y') {
                        break;
                    } else if (Answer != 'N') {
                        printf("    ERROR: ANSWER WAS NOT Y OR N!\n\n");
                    }
                }

                long int x, y;

                GridToCoordinates(Grid, &x, &y);

                MASTER.Gun[GunID - 1] = (struct Gun) {x, y, MASTER.Gun[GunID - 1].z, MASTER.Gun[GunID - 1].type};

                GunStoragePage();
            case 4: // Edit gun elevation

            case 5: // Edit gun type

            case 6: // Return to storage page
                TypeStoragePage();
            case 7: // Return to directory page
                DirectoryPage();
        }
    }
}

int TargetStoragePage(void) {

}

int FireMissionPage(void) {

}

int GuidePage(void) {

}
