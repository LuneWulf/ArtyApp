#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
//#include "raylib\raylib\src\raylib.h"

// Additional #includes are located at line due to the functions in them using the MASTER struct.

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

char *NextPage = NULL;

void QuickFireMission(int Gun, int Target, int HighLowAngle) {

}

void FireMission(void) {

}

char *introPage(void) {

    char ThrowAway;

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
    scanf("%c", &ThrowAway);

    printf("\n");

    return "Directory";
}

char *DirectoryPage(void) {

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
        case 1: return "QuickFireMission";
        case 2: return "Settings";
        case 3: return "Storage";
        case 4: return "FireMission";
        case 5: return "Guide";
        case 6: Save();
        case 7: 
            Save();
            exit(0);
        case 8: exit(0);
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

                if (value != 1 || value != 0) {
                    printf("    ERROR: VALUE MUST BE EITHER 1 OR 0!\n\n");
                } else {
                    Settings.Ace3Drag = value;
                }
            }

            printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
            SettingsPage();

        case 2:
            
            while (true) {
                printf("    ENTER NEW VALUE FOR ACE3 WEATHER: ");
                scanf("%d", &value);

                if (value =! 1 || value != 0) {
                    printf("    ERROR: VALUE MUST BE EITHER 1 OR 0!\n\n");
                } else {
                    Settings.Ace3Weather = value;
                }
            }

            printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
            SettingsPage();

        case 3: return "Directory";
    }
}

char *StoragePage(void) {

    printf("\
    ->->->->->->->->->-> STORAGE <-<-<-<-<-<-<-<-<-<-\n\
    \n\
    ><>< COMMANDS ><><\n\
    \n\
    TYPE STORAGE: 1\n\
    GUN STORAGE: 2\n\
    TARGET STORAGE: 3\n\
    \n\
    GO BACK: 4\n\n");

    int command = EnterCommand(1, 4);

    switch (command) {
        case 1: return "TypeStorage";
        case 2: return "GunStorage";
        case 3: return "TargetStorage";
        case 4: return "Directory";
    }
}

char *TypeStoragePage(void) {
    
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
        printf("    GO BACK: 2\n");

        int command = EnterCommand(1, 2);

        switch (command) {
            case 1: 
                AddType();
                printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
                TypeStoragePage();
            case 2: return "Storage";
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
        printf("    GO BACK: 9\n");

        int command = EnterCommand(1, 9);

        int type, ammo, charge, len, test;
        long int AirFriction;
        char TypeName[50], AmmoName[50], Answer;

        switch (command) {
            case 1: // Add gun type
                AddType();
                printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
                TypeStoragePage();

            case 2: // Remove gun type
                
                while (true) {
                    type = EnterType();

                    while (true) {
                        printf("    ARE YOU SURE YOU WISH TO REMOVE %s? (Y/N): ", MASTER.Types[type - 1].Name);
                        scanf("%c", &Answer);

                        if (Answer == 'Y') {
                            break;
                        } else if (Answer != 'N') {
                            printf("    ERROR: ANSWER WAS NOT Y OR N!\n\n");
                        } else {
                            break;
                        }
                    }

                    if (Answer == 'Y') {
                        break;
                    }
                }

                // Remove type
                strcpy(MASTER.Types[type - 1].Name, '\0');

                for (int i = 0; i < MASTER.Types[type - 1].AmmoCount; i++) {
                    strcpy(MASTER.Types[type - 1].Ammo[i].Name, '\0');
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

                printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
                TypeStoragePage();

            case 3: // Edit gun type name
                type = EnterType();

                while (true) {
                    printf("    ENTER NEW TYPE NAME (MAX 50 CHARACTERS): ");
                    fgets(TypeName, sizeof(TypeName), stdin);

                    len = strlen(TypeName);
                    if (len > 0 && TypeName[len - 1] == '\n') {
                        TypeName[len - 1] = '\0';
                    }

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

                printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
                TypeStoragePage();

            case 4: // Add ammo type to gun type
                type = EnterType();

                AddAmmo(type);

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

                printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
                TypeStoragePage();

            case 5: // Edit ammo type name
                type = EnterType();
                ammo = EnterAmmo(type);

                while (true) {
                    printf("    ENTER NEW AMMO TYPE NAME (MAX 50 CHARACTERS): ");
                    fgets(AmmoName, sizeof(AmmoName), stdin);

                    len = strlen(AmmoName);
                    if (len > 0 && AmmoName[len - 1] == '\n') {
                        AmmoName[len - 1] = '\0';
                    }

                    printf("    NEW STORED AMMO TYPE NAME: %s\n", AmmoName);
                    printf("    IS THE NEW STORED NAME CORRECT? (Y/N): ");
                    scanf("%c", &Answer);
                    printf("\n");

                    if (Answer == 'Y') {
                        break;
                    }
                }

                strcpy(MASTER.Types[type - 1].Ammo[ammo - 1].Name, AmmoName);

                printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
                TypeStoragePage();

            case 6: // Edit ammo type air friction
                type = EnterType();
                
                while (true) {
                    ammo = EnterAmmo(type);

                    printf("    ENTER NEW AIR FRICTION VALUE: ");
                    scanf("%lf", &AirFriction);
                    printf("\n");

                    if (AirFriction > 0) {
                        printf("    ERROR: AIR FRICTION MUST BE LESS OR EQUAL TO 0");
                    } else {
                        MASTER.Types[type - 1].Ammo[ammo - 1].AirFriction = AirFriction;
                    }
                }

                printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
                TypeStoragePage();

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

                    printf("    DO YOU WISH TO ADD ANOTHER CHARGE? (MAX %d) (Y/N): ", MAX_CHARGES);
                    scanf("%c", &Answer);
                    printf("\n");

                    if (Answer == 'N') {
                        break;
                    } else if (Answer == 'Y') {
                        AddCharge(type, ammo);
                    } else {
                        printf("    ERROR: ANSWER WAS NOT Y OR N!\n\n");
                    }

                }

                TypeStoragePage();

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

                TypeStoragePage();

            case 9:
                return "Storage";
        }
    }
}

char *GunStoragePage(void) {
    
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
        printf("    GO BACK: 1");

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
        printf("\n");

        int command = EnterCommand(1, 2);

        switch (command) {
            case 1:
                AddGun();
                GunStoragePage();
            case 2: 
                return "Storage";
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
            printf("    EDIT GUN TYPE: 4\n");
            printf("    GO BACK: 5\n");
            printf("\n");

            command = EnterCommand(1, 5) + 1;
        } else {
            printf("    ><>< COMMANDS ><><\n\n");
            printf("    ADD GUN: 1\n");
            printf("    REMOVE GUN: 2\n");
            printf("    EDIT GUN GRID: 3\n");
            printf("    EDIT GUN ELEVATION: 4\n");
            printf("    EDIT GUN TYPE: 5\n");
            printf("    GO BACK: 6\n");
            printf("\n");

            command = EnterCommand(1, 6);
        }

        int GunID, type, len;
        long int Elevation, x, y;
        char Grid[10], Answer;

        switch (command) {
            case 1: // Add gun
                AddGun();
                GunStoragePage();

            case 2: // Remove gun
                RemoveGun();
                GunStoragePage();

            case 3: // Edit gun grid
                
                GunID = EnterGunID();

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

                GridToCoordinates(Grid, &x, &y);

                MASTER.Gun[GunID - 1] = (struct Gun) {x, y, MASTER.Gun[GunID - 1].z, MASTER.Gun[GunID - 1].Type};

                GunStoragePage();

            case 4: // Edit gun elevation
                GunID = EnterGunID();
                
                printf("    ENTER NEW ELEVATION FOR GUN %d: ", GunID);
                scanf("%ld", &Elevation);

                MASTER.Gun[GunID - 1].z = Elevation;

                GunStoragePage();

            case 5: // Edit gun type
                GunID = EnterGunID();

                ListAllTypes("");
                type = EnterType();

                MASTER.Gun[GunID - 1].Type = type - 1;

                GunStoragePage();

            case 6:
                return "Storage";
        }
    }
}

char *TargetStoragePage(void) {

}

char *FireMissionPage(void) {

}

char *GuidePage(void) {

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

void PageMachine(char *Page) {
    
    int number = StrToInt(Page);

    // The number used as the case is the sum of the ASCII 
    // decimal value of the characters in the page name without the 'Page' part
    switch (number) {
        
        // "Intro"
        case 524:  Page = introPage();
                   break;

        // "Directory"
        case 949:  Page = DirectoryPage();
                   break;

        // "QuickFireMission"
        //case 1637: Page = QuickFireMissionPage();
        //           break;
           
        // "Settings"
        case 849:  Page = SettingsPage();
                   break;

        // "Storage"
        case 725:  Page = StoragePage();
                   break;

        // "TypeStorage"
        case 1143: Page = TypeStoragePage();
                   break;

        // "GunStorage"
        case 1023: Page = GunStoragePage();
                   break;

        // "TargetStorage"
        case 1340: Page = TargetStoragePage();
                   break;

        // "FireMission"
        case 1128: Page = FireMissionPage();
                   break;

        // "Guide"
        case 494:  Page = GuidePage();
                   break;
    }

    NextPage = Page;
}

int main(void) {

    initStorage();

    PageMachine("Intro");   

    while (true) {

        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");

        PageMachine(NextPage);

    }

    return 0;
}
