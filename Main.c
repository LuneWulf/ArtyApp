#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
// #include "raylib\raylib\src\raylib.h"
// Will probably make a GUI in the future, idk...

#include "include/Structs.c"
#include "include/Tools.c"
#include "include/Pages.c"

char *NextPage = NULL;

void PageMachine(char *Page) {
    
    int number = StrToInt(Page);

    // The number used as the case is the sum of the ASCII 
    // decimal value of the characters in the page name without the 'Page' part
    switch (number) {
        
        // "Intro"
        case 524:  RecordLog("Program Launched");
                   Page = introPage();
                   break;

        // "Directory"
        case 949:  RecordLog("Entered Directory");
                   Page = DirectoryPage();
                   break;

        // "QuickFireMission"
        case 1637: RecordLog("Entered Quick Fire Mission");
                   Page = QuickFireMissionPage();
                   break;
           
        // "QuickFireMissionCommands"
        case 2455: RecordLog("Entered Quick Fire Mission Commands");
                   Page = QuickFireMissionCommandsPage();
                   break;

        // "Settings"
        case 849:  RecordLog("Entered Settings");
                   Page = SettingsPage();
                   break;

        // "Storage"
        case 725:  RecordLog("Entered Storage");
                   Page = StoragePage();
                   break;

        // "TypeStorage"
        case 1143: RecordLog("Entered Type Storage");
                   Page = TypeStoragePage();
                   break;

        // "GunStorage"
        case 1023: RecordLog("Entered Gun Storage");
                   Page = GunStoragePage();
                   break;

        // "TargetStorage"
        case 1340: RecordLog("Entered Target Storage");
                   Page = TargetStoragePage();
                   break;

        // "FireMission"
        case 1128: exit(0);
        //case 1128: RecordLog("Entered Fire Mission");
        //           Page = FireMissionPage();
        //           break;

        // "Guide"
        case 494: exit(0);
        //case 494:  RecordLog("Entered Guide");
        //           Page = GuidePage();
        //           break;
    }

    NextPage = Page;
}

int main(void) {

    FILE *Record = fopen("Record.txt", "r");
    FILE *OldRecord = fopen("Old_Record.txt", "r");
    
    if (Record != NULL) {
        if (OldRecord != NULL) {
            remove("Old_Record.txt");
        }

        rename("Record.txt", "Old_Record.txt");
    }

    fclose(Record);
    fclose(OldRecord);

    initStructs();

    PageMachine("Intro");   

    while (true) {

        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");

        PageMachine(NextPage);

    }

    return 0;
}
