#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#include "Tools.c"
#include "Structs.c"
#include "GunManipulation.c"
#include "TargetManipulation.c"
#include "TypeManipulation.c"
#include "TypeAccess.c"
#include "Ballistics.c"

#ifndef PAGES_H

#define PAGES_H

char *introPage(void) {

    char ThrowAway;

    printf("                        WELCOME!\n\n");
    printf("    THIS PROGRAM IS AN ARTILLERY COMPUTER FOR ARMA 3,\n");
    printf("    IT SUPPORTS THE USE OF EITHER ACE3 OR STANDARD\n");
    printf("    ARMA 3 PHYSICS.\n\n");
    printf("    THIS PROGRAM ALLOWS YOU TO INPUT YOUR GUN TYPES\n");
    printf("    AND AMMO TYPES WHICH DEFINE THE MUZZLE VELOCITY\n");
    printf("    AND THE AIR FRICTION OF THE ROUND BEING USED.\n\n");
    printf("    N   GUN TYPES AND ASSOCIATED AMMUNITION TYPES ARE\n");    
    printf("    O   STORED IN THE FILE NAME TYPES&AMMO.DAT, WHICH\n");
    printf("    T   CAN EASILY BE EDITED BY YOU IN ANY TEXT\n");
    printf("    E   EDITOR OF YOUR CHOOSING.\n\n");
    printf("    SAVED FIRE MISSIONS ARE SAVED WHILST THE PROGRAM\n");
    printf("    IS RUNNING, AFTER WHICH ALL OF THE FIRE MISSIONS\n");
    printf("    ARE DISCARDED.\n\n");
    printf("    TO AID THE FDC, THE TARGETS CAN BE ASSIGNED TO A\n");
    printf("    GUN AUTOMATICALLY OR MANUALLY AND THE COMPUTER\n");
    printf("    COMES WITH PRE-DEFINED FIRE METHODS.\n\n");
    printf("    PLEASE MESSAGE ME ON DISCORD @ _LEMONBOI WITH ANY\n");
    printf("    QUESTIONS, CONCERNS OR SUGGESTIONS\n\n");

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

    int command = Inputint("ENTER COMMAND: ", 1, 9);
    
    switch (command) {
        case 1: return "QuickFireMission";
        case 2: return "Settings";
        case 3: return "Storage";
        case 4: return "FireMission";
        case 5: return "Guide";
        case 6: Load();
        case 7: Save();
                return "Directory";
        case 8: 
                Save();
                exit(0);
        case 9: exit(0);
    }
}

char *QuickFireMissionPage(void) {

    printf("    ->->->->->->->->->-> QUICK FIRE MISSION PAGE <-<-<-<-<-<-<-<-<-<-\n\n");
    
    if (MASTER.TypeCount == 0) {
        printf("    ><>< NO TYPES DEFINED, DEFINE NEW TYPE ><><\n\n");
        
        AddType();

        if(MASTER.TypeCount == 0) {
            return "Directory";
        }

        printf("    ><>< NO GUNS DEFINED, DEFINE NEW GUN ><><\n\n");

        AddGun();

    } else if (MASTER.GunCount == 0) {
        printf("    ><>< NO GUNS DEFINED, DEFINE NEW GUN ><><\n\n");
        
        AddGun();
    }

    if (MASTER.TargetCount == 0) {
        printf("    ><>< NO TARGETS DEFINED, DEFINE NEW TARGET ><><\n\n");
    
        AddTarget();
    }

    printf("    ><>< SELECT GUN AND AMMO FROM THE LIST FOR THE FIRE MISSION ><><\n\n");

    for (int Gun = 0; Gun < MASTER.GunCount; Gun++) {
        printf("    GUN ID: %d,    GRID: %s,    TYPE: %s,    AMMO:\n", Gun + 1, MASTER.Gun[Gun].Grid, MASTER.Types[MASTER.Gun[Gun].Type].Name);

        for (int Ammo = 0; Ammo < MASTER.Types[MASTER.Gun[Gun].Type].AmmoCount; Ammo++) {
            printf("    AMMO ID: %d,    NAME: %s\n", Ammo + 1, MASTER.Types[MASTER.Gun[Gun].Type].Ammo[Ammo].Name);
        }
    }

    int GunID = Inputint("ENTER GUN ID: ", 1, MASTER.GunCount);

    int AmmoID = Inputint("ENTER AMMO ID: ", 1, MASTER.Types[MASTER.Gun[GunID - 1].Type].AmmoCount);

    printf("    ><>< SELECT CHARGE FROM THE LIST FOR THE FIRE MISSION ><><\n\n");

    for (int Charge = 0; Charge < MASTER.Types[MASTER.Gun[GunID - 1].Type].Ammo[AmmoID - 1].ChargeCount; Charge++) {
        printf("    CHARGE ID: %d,    MAX RANGE: %f\n", Charge + 1, MASTER.Types[MASTER.Gun[GunID].Type].Ammo[AmmoID].ChargeMaxRange[Charge]);
    }

    printf("\n");

    int ChargeID = Inputint("ENTER CHARGE ID: ", 1, MASTER.Types[MASTER.Gun[GunID - 1].Type].Ammo[AmmoID - 1].ChargeCount);

    printf("    ><>< SELECT TARGET FROM LIST FOR THE FIRE MISSION ><><\n\n");

    for (int Target = 0; Target < MASTER.TargetCount; Target++) {
        printf("    TARGET ID: %d,    GRID: %s\n", Target + 1, MASTER.Target[Target].Grid);
    }   

    printf("\n");

    int TargetID = Inputint("ENTER TARGET ID: ", 1, MASTER.TargetCount);

    printf("    ><>< SELECT HIGH OR LOW ANGLE OF FIRE ><><\n\n");

    int HighLow = Inputint("ENTER 1 FOR HIGH ANGLE, 0 FOR LOW ANGLE: ", 0, 1);

    float GunAlt = MASTER.Gun[GunID - 1].z;
    float TargetAlt = MASTER.Target[TargetID - 1].z;
    float Direction;
    float Range;

    GridsToDisMills(MASTER.Gun[GunID - 1].Grid, MASTER.Target[TargetID - 1].Grid, &Range, &Direction);
    
    int TypeID = MASTER.Gun[GunID - 1].Type;

    float Elevation = 800;

    while (true) {
        
        Data = Simulate(GunAlt, TargetAlt, Direction, TypeID, AmmoID, ChargeID, Elevation, 0);

        double dR = Range - Data.Distance;

        if (dR < 0)
            dR = -dR;

        if (dR < 0.5)
            break;

        if (HighLow == 1) {
            if (dR < 5) {
                Elevation += 0.01;
            } else if (dR < 100) {
                Elevation += 0.1;
            } else if (dR < 250) {
                Elevation += 0.5;
            } else if (dR < 1000) {
                Elevation += 1;
            } else {
                Elevation += 5;
            }
        } else if (HighLow == 0) {
            if (dR < 5) {
                Elevation -= 0.01;
            } else if (dR < 100) {
                Elevation -= 0.1;
            } else if (dR < 250) {
                Elevation -= 0.5;
            } else if (dR < 1000) {
                Elevation -= 1;
            } else {
                Elevation -= 5;
            }
        }

        
        if (Elevation <= 0 || Elevation >= 1600) {
            RecordLog("Simulation FAIL, elevation <= 0 OR elevation >= 1600");
            break;
        }
    }

    printf("    FIRE MISSION, GUN %d TO TARGET %d:\n", GunID++, TargetID++);
    printf("    TOF: %.1f SECONDS\n", Data.ToF);
    printf("    AZIMUTH: %.1f MILLS\n", Data.Direction);
    printf("    ELEVATION: %.1f MILLS\n", Data.Elevation);
    printf("    MAX ALTITUDE: %.1f METERS\n\n", Data.MaxAlt);

}

char *QuickFireMissionCommandsPage(void) {

    int Command;

    if (MISSIONS.MissionCount < MAX_SAVED_MISSIONS) {
        printf("    ><>< COMMANDS ><><\n\n");
        printf("    SAVE FIRE MISSION (NR. %d OUT OF MAX %d): 1\n", MISSIONS.MissionCount, MAX_SAVED_MISSIONS);
        printf("    NEW QUICK FIRE MISSION: 2\n");
        printf("    DIRECTORY PAGE: 3\n\n");

        Command = Inputint("ENTER COMMAND: ", 1, 3);
        
    } else {
        printf("    ><>< COMMANDS ><><\n\n");
        printf("    NEW QUICK FIRE MISSION: 1\n");
        printf("    DIRECTORY PAGE: 2\n\n");

        Command = Inputint("ENTER COMMAND: ", 1, 2) + 1;
    }

    char MissionName[50];

    switch (Command) {
        case 1: 
            InputString("ENTER MISSION NAME (MAX 50 CHARACTERS): ", MissionName);

            MISSIONS.Mission[MISSIONS.MissionCount] = Data;
            strcpy(MISSIONS.Mission[MISSIONS.MissionCount].Name, MissionName);

            return "QuickFireMissionCommands";

        case 2: return "QuickFireMission";
        case 3: return "Directory";
    }
}

char *SettingsPage(void) {
    
    printf("    ->->->->->->->->->-> SETTINGS <-<-<-<-<-<-<-<-<-<-\n\n");
    printf("    ><>< SETTINGS AND THEIR COMMAND ID ><><\n\n");
    printf("    FORMAT: NAME, VALUE: COMMAND ID\n\n");
    printf("    VALUE FORMAT: 1 = TRUE, 0 = FALSE\n\n");
    printf("    ACE3 DRAG,    %d:    1\n", Settings.Ace3Drag);
    printf("    ACE3 WEATHER,    %d:    2\n\n\n", Settings.Ace3Weather);
    printf("    ><>< OTHER COMMANDS ><><\n\n");
    printf("    GO BACK: 3\n\n");
    
    int command = Inputint("ENTER COMMAND: ", 1, 3);

    int value;

    switch (command) {
        case 1: 
            
            while (true) {
                printf("    ENTER NEW VALUE FOR ACE3 DRAG: ");
                scanf("%d", &value);
                clear();

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
                clear();

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

    int command = Inputint("ENTER COMMAND: ", 1, 4);

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

        command = Inputint("ENTER COMMAND: ", 1, 2);

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
            printf("    REMOVE AMMO: 4\n");
            printf("    EDIT AMMO NAME: 5\n");
            printf("    EDIT AMMO AIR FRICTION: 6\n");
            printf("    LIST AMMO CHARGES: 7\n");
            printf("    ADD AMMO CHARGE: 8\n");
            printf("    REMOVE AMMO CHARGE: 9\n");
            printf("    EDIT AMMO CHARGE: 10\n");
            printf("\n");
            printf("    GO BACK: 11\n\n");

            command = Inputint("ENTER COMMAND: ", 1, 11) + 1;

        } else {
            printf("    ><>< COMMANDS ><><\n");
            printf("\n");
            printf("    ADD GUN TYPE: 1\n");
            printf("    REMOVE GUN TYPE: 2\n");
            printf("    EDIT GUN TYPE NAME: 3\n");
            printf("    ADD AMMO: 4\n");
            printf("    REMOVE AMMO: 5\n");
            printf("    EDIT AMMO NAME: 6\n");
            printf("    EDIT AMMO AIR FRICTION: 7\n");
            printf("    LIST AMMO CHARGES: 8\n");
            printf("    ADD AMMO CHARGE: 9\n");
            printf("    REMOVE AMMO CHARGE: 10\n");
            printf("    EDIT AMMO CHARGE: 11\n");
            printf("\n");
            printf("    GO BACK: 12\n\n");

            command = Inputint("ENTER COMMAND: ", 1, 12);

        }


        int type, ammo, charge, len, test;
        double AirFriction;
        char TypeName[50], AmmoName[50], Answer;

        switch (command) {
            case 1: // Add gun type
                
                AddType();
                return "TypeStorage";

            case 2: // Remove gun type
                
                while (Answer != 'Y') {
                    
                    type = Inputint("ENTER TYPE ID TO REMOVE (ENTER 0 TO CANCEL): ", 0, MASTER.TypeCount);

                    if (type == 0) {
                        return "TypeStorage";
                    }

                    Answer = Confirm("ARE YOU SURE YOU WISH TO REMOVE THIS TYPE? (Y/N): ");
                }

                RemoveType(type);

                return "TypeStorage";

            case 3: // Edit gun type name
                
                type = Inputint("ENTER TYPE ID: ", 1, MASTER.TypeCount);

                InputString("ENTER NEW TYPE NAME: ", TypeName);

                strcpy(MASTER.Types[type - 1].Name, TypeName);

                return "TypeStorage";

            case 4: // Add ammo type to gun type
                
                type = Inputint("ENTER TYPE ID: ", 1, MASTER.TypeCount);

                AddAmmo(type, false);

                while (true) {
                    printf("    DO YOU WISH TO ADD ANOTHER AMMO TYPE TO THIS GUN TYPE? (Y/N): ");
                    scanf("%c", &Answer);

                    if (Answer == 'Y') {
                        test = AddAmmo(type, true);
                        if (test == 0) {
                            break;
                        }
                    } else if (Answer == 'N') {
                        break;
                    } else {
                        printf("    ERROR: ANSWER WAS NOT Y OR N!\n\n");
                    }   
                }

                return "TypeStorage";

            case 5: // Remove ammo type
                 
                type = Inputint("ENTER TYPE ID (ENTER 0 TO CANCEL): ", 0, MASTER.TypeCount);

                if (type == 0) {
                    return "TypeStorage";
                }

                while (Answer != 'Y') {

                    ammo = Inputint("ENTER AMMO ID (ENTER 0 TO CANCEL): ", 0, MASTER.Types[type - 1].AmmoCount);

                    if (ammo == 0) {
                        return "TypeStorage";
                    }

                    Answer = Confirm("ARE YOU SURE YOU WISH TO REMOVE THIS AMMO? (Y/N): ");
                }

                RemoveAmmo(type, ammo, true);
                
                return "TypeStorage";

            case 6: // Edit ammo type name
                
                type = Inputint("ENTER TYPE ID: ", 1, MASTER.TypeCount);

                ammo = Inputint("ENTER AMMO ID: ", 1, MASTER.Types[type - 1].AmmoCount);

                InputString("ENTER NEW AMMO TYPE NAME (MAX 50 CHARACTERS): ", AmmoName);

                strcpy(MASTER.Types[type - 1].Ammo[ammo - 1].Name, AmmoName);

                return "TypeStorage";

            case 7: // Edit ammo type air friction

                type = Inputint("ENTER TYPE ID: ", 1, MASTER.TypeCount);

                ammo = Inputint("ENTER AMMO ID: ", 1, MASTER.Types[type - 1].AmmoCount);

                AirFriction = Inputfloat("ENTER NEW AMMO AIR FRICTION: ", -100, 0);

                MASTER.Types[type - 1].Ammo[ammo - 1].AirFriction = AirFriction;

                return "TypeStorage";

            case 8: // List ammo charges

                type = Inputint("ENTER TYPE ID: ", 1, MASTER.TypeCount);

                ammo = Inputint("ENTER AMMO ID: ", 1, MASTER.Types[type - 1].AmmoCount);

                ListCharges(type, ammo);

                Inputint("TO GO BACK ENTER 1: ", 1, 1);

                return "TypeStorage";

            case 9: // Add charge to ammo type
               
                type = Inputint("ENTER TYPE ID: ", 1, MASTER.TypeCount);

                while (true) {
                    ammo = Inputint("ENTER AMMO ID: ", 1, MASTER.Types[type - 1].AmmoCount);
                    clear();

                    if (MASTER.Types[type - 1].Ammo[ammo - 1].ChargeCount >= MAX_CHARGES) {
                        printf("    AMMO HAS MAX AMOUNT OF CHARGES (%d)", MAX_CHARGES);
                    } else{
                        break;
                    }
                }

                AddCharge(type, ammo, false);

                while (MASTER.Types[type - 1].Ammo[ammo - 1].ChargeCount < MAX_CHARGES) {

                    printf("    DO YOU WISH TO ADD ANOTHER CHARGE? (MAX %d) (Y/N): ", MAX_CHARGES);
                    scanf("%c", &Answer);
                    printf("\n");
                    clear();

                    if (Answer == 'N') {
                        break;
                    } else if (Answer == 'Y') {
                        AddCharge(type, ammo, true);
                    } else {
                        printf("    ERROR: ANSWER WAS NOT Y OR N!\n\n");
                    }
                }

                return "TypeStorage";

            case 10: // Remove ammo type charge

                type = Inputint("ENTER TYPE ID: ", 1, MASTER.TypeCount);

                ammo = Inputint("ENTER AMMO ID: ", 1, MASTER.Types[type - 1].AmmoCount);

                ListCharges(type, ammo);

                charge = Inputint("ENTER CHARGE: ", 1, MASTER.Types[type - 1].Ammo[ammo - 1].ChargeCount);
                
                RemoveCharge(type, ammo, charge, true);

                return "TypeStorage";

            case 11: // Edit ammo type charge
                
                type = Inputint("ENTER TYPE ID: ", 1, MASTER.TypeCount);

                ammo = Inputint("ENTER AMMO ID: ", 1, MASTER.Types[type - 1].AmmoCount);

                ListCharges(type, ammo);

                charge = Inputint("ENTER CHARGE: ", 1, MASTER.Types[type - 1].Ammo[ammo - 1].ChargeCount);

                printf("    ENTER NEW MUZZLE VELOCITY FOR CHARGE %d: ", charge);
                scanf("%lf", &MASTER.Types[type - 1].Ammo[ammo - 1].Charge[charge - 1]);

                return "TypeStorage";

            case 12:
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

    int Command;

    if (MASTER.TypeCount == 0) {
        printf("    NO GUN TYPES ARE DEFINED THEREFORE NO GUNS\n");
        printf("    ARE DEFINED NOR CAN NEW GUNS BE DEFINED\n");
        printf("\n");
        printf("    ><>< COMMANDS ><><\n\n");
        printf("    GO BACK: 1\n\n");

        Command = Inputint("ENTER COMMAND: ", 1, 1);

        switch (Command) {
            case 1: return "Storage";
        }

    } else if (MASTER.GunCount == 0) {

        printf("    NO GUNS DEFINED\n");
        printf("\n");
        printf("    ><>< COMMANDS ><><\n\n");
        printf("    ADD GUN: 1\n");
        printf("    GO BACK: 2\n");
        printf("\n\n");

        Command = Inputint("ENTER COMMAND: ", 1, 2);

        switch (Command) {
            case 1:
                
                AddGun();
                return "GunStorage";

            case 2: 

                return "Storage";
        }

    } else {
        
        for (int Gun = 0; Gun < MASTER.GunCount; Gun++) {
            printf("    GUN %d:    TYPE: %s,    GRID: %s,    HEIGHT ASL: %.f\n", Gun + 1, MASTER.Types[MASTER.Gun[Gun].Type - 1].Name, MASTER.Gun[Gun].Grid, MASTER.Gun[Gun].z);
        }

        printf("\n");

        if (MASTER.GunCount == MAX_GUNS) {
            printf("    ><>< COMMANDS ><><\n\n");
            printf("    REMOVE GUN: 1\n");
            printf("    EDIT GUN GRID: 2\n");
            printf("    EDIT GUN HEIGHT ASL: 3\n");
            printf("    EDIT GUN TYPE: 4\n");
            printf("    GO BACK: 5\n\n");

            Command = Inputint("ENTER COMMAND: ", 1, 5) + 1;

        } else {
            printf("    ><>< COMMANDS ><><\n\n");
            printf("    ADD GUN: 1\n");
            printf("    REMOVE GUN: 2\n");
            printf("    EDIT GUN GRID: 3\n");
            printf("    EDIT GUN HEIGHT ASL: 4\n");
            printf("    EDIT GUN TYPE: 5\n");
            printf("    GO BACK: 6\n\n");

            Command = Inputint("ENTER COMMAND: ", 1, 6);
        }

        int GunID, type, len;
        float Height;
        char Grid[11];

        switch (Command) {
            case 1: // Add gun
                
                AddGun();
                return "GunStorage";

            case 2: // Remove gun
                
                GunID = Inputint("ENTER GUN ID (ENTER 0 TO CANCEL): ", 0, MASTER.GunCount);

                if (GunID == 0) {
                    return "GunStorage";
                }

                RemoveGun(GunID);

                return "GunStorage";

            case 3: // Edit gun grid
                
                GunID = Inputint("ENTER GUN ID: ", 1, MASTER.GunCount);

                InputString("ENTER NEW GRID (MAX 10 DIGITS, MIN 2 DIGITS): ", Grid);

                strcpy(MASTER.Gun[GunID - 1].Grid, Grid);

                return "GunStorage";

            case 4: // Edit gun height ASL
                
                GunID = Inputint("ENTER GUN ID: ", 1, MASTER.GunCount);
                
                Height = Inputfloat("ENTER NEW GUN HEIGHT ASL: ", -1000, 10000);

                MASTER.Gun[GunID - 1].z = Height;

                return "GunStorage";

            case 5: // Edit gun type
                
                GunID = Inputint("ENTER GUN ID: ", 1, MASTER.GunCount);

                ListAllTypes(0);

                type = Inputint("ENTER TYPE ID: ", 1, MASTER.TypeCount);

                MASTER.Gun[GunID - 1].Type = type - 1;

                return "GunStorage";

            case 6:
                return "Storage";
        }
    }
}

char *TargetStoragePage(void) {

    int Command;

    printf("    ->->->->->->->->->-> TARGET STORAGE <-<-<-<-<-<-<-<-<-<-\n\n");
    printf("    ><>< TARGETS ><><\n\n");

    if (MASTER.TargetCount == 0) {
        printf("    NO TARGETS DEFINED\n\n");
        printf("    ><>< COMMANDS ><><\n\n");
        printf("    ADD TARGET: 1\n");
        printf("    GO BACK: 2\n\n");

        Command = Inputint("ENTER COMMAND: ", 1, 2);

        switch (Command) {
            case 1: 
                AddTarget();
                return "TargetStorage";

            case 2: 
                return "Directory";
        }
    } else {

        for (int Target = 0; Target < MASTER.TargetCount; Target++) {
            printf("    TARGET %d:    GRID: %10s,    HEIGHT ASL: %f\n", Target + 1, MASTER.Target[Target].Grid, MASTER.Target[Target].z);
        }

        printf("\n");

        if (MASTER.TargetCount >= MAX_TARGETS) {
            printf("    ><>< COMMANDS ><><\n\n");
            printf("    REMOVE TARGET: 1\n");            
            printf("    EDIT TARGET GRID: 2\n");
            printf("    EDIT TARGET HEIGHT ASL: 3\n");
            printf("    GO BACK: 4\n\n");

            Command = Inputint("ENTER COMMAND: ", 1, 4) + 1;

        } else {
            printf("    ><>< COMMANDS ><><\n\n");
            printf("    ADD TARGET: 1\n");
            printf("    REMOVE TARGET: 2\n");
            printf("    EDIT TARGET GRID: 3\n");
            printf("    EDIT TARGET HEIGHT ASL: 4\n");
            printf("    GO BACK: 5\n\n");

            Command = Inputint("ENTER COMMAND: ", 1, 5);

        }

        int TargetID;
        float Height;
        char Grid[11];

        switch (Command) {
            case 1: // Add target
                
                AddTarget();
                return "TargetStorage";

            case 2: // Remove target
                
                TargetID = Inputint("ENTER TARGET ID (ENTER 0 TO CANCEL): ", 1, MASTER.TargetCount);

                if (TargetID == 0) {
                    return "TargetStorage";
                }

                RemoveTarget(TargetID);

                return "TargetStorage";

            case 3: // Edit target grid
                
                TargetID = Inputint("ENTER TARGET ID (ENTER 0 TO CANCEL): ", 1, MASTER.TargetCount);

                InputString("ENTER NEW TARGET GRID (MAX 10 DIGITS, MIN 2 DIGITS): ", Grid);

                strcpy(MASTER.Target[TargetID - 1].Grid, Grid);
                
                return "TargetStorage";

            case 4: // Edit target elevation
                
                TargetID = Inputint("ENTER TARGET ID (ENTER 0 TO CANCEL): ", 1, MASTER.TargetCount);

                Height = Inputfloat("ENTER NEW TARGET HEIGHT ASL", -1000, 10000);

                MASTER.Target[TargetID - 1].z = Height;

            case 5: 
                return "Directory";
        }
    }
}

char *FireMissionStoragePage(void) {
}

char *FireMissionPage(void) {

}

char *GuidePage(void) {

}


#endif
