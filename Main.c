#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
//#include "raylib\raylib\src\raylib.h"



// Additional #includes are located at line 79 and 99 due to the functions in them using the MASTER struct.


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
    char Grid[10];
    int AmmoCount;
    struct Ammo Ammo[MAX_AMMO];
};

struct Gun {
    char Grid[10];    
    long int x;
    long int y;
    long int z;
    int Type;
};

struct Target {
    char Grid[10];
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

char *NextPage = NULL;


//---------------------------------------------------


#include "include\Tools.c"
#include "include\TypeManipulation.c"
#include "include\TypeAccess.c"
#include "include\GunManipulation.c"
#include "include\TargetManipulation.c"


//---------------------------------------------------


void QuickFireMission(int Gun, int Target, int HighLowAngle) {

}

void FireMission(void) {

}


//---------------------------------------------------


#include "include\Pages.c"


//---------------------------------------------------


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
        
        MASTER.Target[Target] = (struct Target) {'\0', 0, 0, 0};
    }

    MASTER.GunCount = 0;

    for (int Gun = 0; Gun < MAX_GUNS; Gun++) {
        
        MASTER.Gun[Gun] = (struct Gun) {'\0', 0, 0, 0, 0};
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
        case 1637: exit(0);
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
        case 1128: exit(0);
        //case 1128: Page = FireMissionPage();
        //           break;

        // "Guide"
        case 494: exit(0);
        //case 494:  Page = GuidePage();
        //           break;
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
