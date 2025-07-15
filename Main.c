#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lib.c"
#include <math.h>

#define MAX_TYPESTORES 5
#define MAX_TYPES 5
#define MAX_AMMO 5
#define MAX_CHARGES 20

#define MAX_GUNS 10;
#define MAX_TARGETS 50;

struct Ammo {
    char Name[50];
    double AirFriction;
    long int Charge[MAX_CHARGES];
};

struct Type {
    char Name[50];
    int AmmoCount;
    struct Ammo Ammo[MAX_AMMO];
};

struct TypeStorage {
    int TypeCount;
    struct Type Types[MAX_TYPES];
};

struct Gun {
    long int x;
    long int y;
    long int z;
    int Type;
    int Ammo;
    int Charge;
};

struct Target {
    long int x;
    long int y;
    long int z;
};

struct MASTER {
    int TypeStoreCount;
    struct TypeStorage TypeStores[MAX_TYPESTORES];

    int TargetCount;
    struct Target Targets[MAX_TARGETS];

    int GunCount;
    struct Gun Guns[MAX_GUNS];
} MASTER;

/* OLD STRUCT
struct Gun {
    int id;
    long int x;
    long int y;
    long int z;
    struct Type *Type;
};
*/

long int StrToLI(char *string);

int GridToCoordinates(char grid[], long int *x, long int *y);

void DisMillsToCoordinates(int distance, int direction, char *CurrentGrid, long int *x, long int *y);

long int MillsFromCoordinate(long int dx, long int dy);

void GridsToDisMills(char *GridOne, char *GridTwo, long int *Distance, long int *Direction); 

void AddAmmo(struct MASTER *MASTER, int TypeStore, int Type);

int AddType(struct MASTER *MASTER, int TypeStore);

void initStorages(struct MASTER *MASTER);

void AddGun(long int x, long int y, long int Elevation, int type, int ammo, struct Gun *Storage);

void RemoveGun(int id, struct Gun *Storage);

void ListAllTypes(struct MASTER *MASTER);

void ListAllAmmo(struct MASTER *MASTER, int TypeStore, int Type);

// !PLACEHOLDER - NOT FINISHED!
void QuickFireMission(struct Gun *GunStorage, struct Tgt *TgtStorage, int Angle);

int main(void) {

    initStorages(&MASTER);

    int command;

    struct Gun *GunStorage = NULL;
    struct Tgt *TgtStorage = NULL;

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

    MAIN:

    printf("\
    ->->->->->->->->->-> MAIN PAGE <-<-<-<-<-<-<-<-<-<-\n\
    \n\
    ><>< QUICK COMMANDS ><><\n\
    \n\
    CREATE FIRE MISSION (1 TGT 1 GUN): 0\n\
    \n\
    ><>< PAGE COMMANDS ><><\n\
    \n\
    SETTINGS: 1\n\
    GUNS: 2\n\
    TGTS: 3\n\
    FIRE MISSION: 4\n\
    GUIDE: 5\n\n");

    RETRY:

    printf("    ENTER COMMAND: ");
    scanf("%d", &command);
    printf("\n\n")

    switch (command) {
        case 0:

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

                if (MASTER.TypeStoreCount == 0) {
                    AddType(&MASTER, 0);
                } else {
                    printf("    CHOOSE TYPE FROM LIST:\n\n");

                    ListAllTypes(&MASTER);
                    
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



                AddGun(Grid, Elevation, type, ammo, GunStorage)

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


        case 5: goto GUIDE;
        case 4: goto FIREMISSION;
        case 3: goto TGTS;
        case 2: goto GUNS;
        case 1: goto SETTINGS;
        case default:
            printf("    !ERROR: UNKNOWN COMMAND!\n\n");
            goto RETRY;
    }

    SETTINGS:

    printf("\
    ->->->->->->->->->-> SETTINGS <-<-<-<-<-<-<-<-<-<-\n\
    \n\
    SETTINGS:\n\
    \n\
    (1 FOR TRUE, 0 FOR FALSE)\n\
    \n\
    1: ACE3 DRAG   =   %d\n\
    2: ACE3 WEATHER    =   %d\n\
    ")

    GUNS:

        GUNDATA:

        TYPESAMMO:

    TGTS:

        TGTDATA:

        GROUPS: //?possibly?

    FIREMISSION:

    GUIDE:

    return 0;
}

long int StrToLI(char *string) {
    int size = strlen(string);
    long int number = 0;

    for (int i = 0; i < size; i++) {
        number = number + (long int) ((*(string + i) - 48) * power(10, size - i - 1));
        //printf("number: %ld, added: %ld\n", number, (long int) ((*(string + i) - 48) * pow(10, size - i - 1)));
        //printf("%f\n", power(10, size - i - 1));
        //printf("size: %d\n", size);
    }

    return number;
}

int GridToCoordinates(char grid[], long int *x, long int *y) {

    int size = strlen(grid);

    //printf("size %d\n", size);

    // is size even
    float even = (float) size / (float) 2 - size / 2;
    if (even != 0) {
        char *temp = malloc(sizeof(char) * (size + 1));
        temp[0] = '0';
        for (int i = 0; i < size; i++) {
            temp[i + 1] = grid[i];

            //printf("%c %c\n", temp[i + 1], grid[i]);
        }

        //printf("%s\n", temp);

        size++;
        for (int i = 0; i < size; i++) {
            grid[i] = temp[i];
        }

        //printf("%s\n", grid);
    }

    //printf("size %d\n", size);
    

    if (size > 10) {
        printf("\n\nERROR: GRID OUT OF BOUNDS, MUST BE 10-DIGIT OR LOWER\n");
        *x = -1;
        return 1;
    } else if (size < 0) {
        printf("\n\nERROR: GRID OUT OF BOUNDS, MUST BE 2-DIGIT OR GREATER\n");
        *x = -1;
        return 1;
    } else {
        int middle = size / 2;
        char *X = malloc(sizeof(char)*middle);
        char *Y = malloc(sizeof(char)*middle);
        for (int i = 0; i < size; i++) {
            if (i < middle) {
                *(X + i) = grid[i];
            } else {
                *(Y + i - middle) = grid[i];
            }
        }

        *(X + middle) = '\0';
        *(Y + middle) = '\0';

        //printf("test\n");

        //printf("%s, %s\n", X, Y);

        //Assign x and y and scale such that its unit is in meters.
        *x = StrToLI(X) * power(10, 5 - middle);
        *y = StrToLI(Y) * power(10, 5 - middle);

        //printf("x: %ld, y: %ld\n", *x, *y);
        return 0;
    }
}

void DisMillsToCoordinates(int distance, int direction, char *CurrentGrid, long int *x, long int *y) {
    float radians = (float) direction * M_PI / (float) (3200);

    GridToCoordinates(CurrentGrid, x, y);

    //printf("Radians: %f, pi: %f, direction: %ld\n", radians, M_PI, (direction * 3200));
    //printf("cos: %f, sin: %f", cos(radians) * (double) distance, sin(radians) * (double) distance);

    *x += round(cos(radians) * (double) distance);
    *y += round(sin(radians) * (double) distance);
}

long int MillsFromCoordinate(long int dx, long int dy) {
    
    long int mills = (atan((double) dy / (double) dx) * 6400) / (2 * M_PI);

    if (dx < 0) {
        if (mills < 0) {
            mills += 6400;
        } else {
            mills += 3200;
        }
    } else if (dx > 0) {
        if (mills < 0) {
            mills += 3200;
        }
    } else {
        if (mills < 0) {
            mills += 6400;
        }
    }

    return mills;
}

void GridsToDisMills(char *GridOne, char *GridTwo, long int *Distance, long int *Direction) {
    long int x_1, x_2, y_1, y_2;

    GridToCoordinates(GridOne, &x_1, &y_1);
    GridToCoordinates(GridTwo, &x_2, &y_2);

    *Distance = hypot((double) (x_1 - x_2), (double) (y_1 - y_2));

    *Direction = MillsFromCoordinate(x_1 - x_2, y_1 - y_2);
} 

void AddAmmo(struct MASTER *MASTER, int TypeStore, int Type) {
    
    double AirFriction;

    char AmmoName[50];

    printf("    ENTER AMMO NAME: ");
    fgets(AmmoName, sizeof(AmmoName), stdin);

    size_t len = strlen(AmmoName);
    if (len > 0 && AmmoName[len - 1] == '\n') {
        AmmoName[len - 1] = '\0';
    }

    strcpy(MASTER->TypeStores[TypeStore].Types[MASTER->TypeStores[TypeStore].TypeCount].Ammo[MASTER->TypeStores[TypeStore].Types[Type].AmmoCount].Name, AmmoName);

    ERRORAIRFRICTION:

    printf("    ENTER AMMO AIR FRICTION: ");
    scanf("%lf", &AirFriction);

    if (AirFriction > 0) {
        printf("    ERROR: AIR FRICTION MUST BE LESS THAN OR EQUAL TO 0\n");
        goto ERRORAIRFRICTION;
    }

    MASTER->TypeStores[TypeStore].Types[Type].Ammo[MASTER->TypeStores[TypeStore].Types[Type].AmmoCount].AirFriction = AirFriction;

    int ChargeCount;

    printf("\n    NOW DEFINE CHARGE VELOCITIES, MAX 20 CHARGES!\n");
    printf("    TO STOP DEFINING CHARGES ENTER -1 INSTEAD OF A VELOCITY\n");
    printf("    MINIMUM OF 1 CHARGE:\n\n");

    for (int i = 0; i < 20; i++, ChargeCount++) {
        
        long int TempVel = 0;

        ERRORMUZVEL:

        printf("    ENTER CHARGE %d MUZZLE VELOCITY: ", i+1);
        scanf("%ld", &TempVel);

        if (i != 0 && TempVel == -1) {
            break;
        } else if (TempVel <= 0) {
            printf("    ERROR: INVALID CHARGE MUZZLE VELOCITY!\n");
            goto ERRORMUZVEL;
        }

        MASTER->TypeStores[TypeStore].Types[Type].Ammo[MASTER->TypeStores[TypeStore].Types[Type].AmmoCount].Charge[i] = TempVel;
    }

    MASTER->TypeStores[TypeStore].Types[Type].AmmoCount++;
}

int AddType(struct MASTER *MASTER, int TypeStore) {

    
    //Check if storage is full then check the next.

    while (MASTER->TypeStores[TypeStore].TypeCount >= 5 && TypeStore < MAX_TYPESTORES) {
        if (MASTER->TypeStores[TypeStore].TypeCount >= 5) {
            TypeStore++;
        }
    }

    if (TypeStore == MAX_TYPESTORES) {
        return -1;
    }

    char TypeName[50];

    printf("    ENTER TYPE NAME: ");
    fgets(TypeName, sizeof(TypeName), stdin);

    size_t len = strlen(TypeName);
    if (len > 0 && TypeName[len - 1] == '\n') {
        TypeName[len - 1] = '\0';
    }

    strcpy(MASTER->TypeStores[TypeStore].Types[MASTER->TypeStores[TypeStore].TypeCount].Name, TypeName);

    printf("\n    DEFINE A NEW AMMO TYPE FOR THE NEW TYPE:\n");

    AddAmmo(MASTER, MASTER->TypeStores[TypeStore].TypeCount, MASTER->TypeStoreCount);

    char Answer;

    printf("\n    DO YOU WISH TO ADD MORE AMMO TYPES? (MAX 5 AMMO TYPES PER TYPE) (Y/N): ");
    scanf(" %c", &Answer);

    for (int i = 0; i < 4 && Answer == 'Y'; i++) {
        
        while(getchar() != '\n');
        AddAmmo(MASTER, MASTER->TypeStores[TypeStore].TypeCount, MASTER->TypeStoreCount);

        ERRORANSWERYN:

        printf("    DO YOU WISH TO ADD ANOTHER AMMO TYPE? (Y/N): ");
        scanf(" %c", &Answer);

        if (Answer != 'Y' && Answer != 'N') {
            printf("    ERROR: ANSWER WAS NOT Y OR N!\n\n");
            goto ERRORANSWERYN;            
        }
    }

    MASTER->TypeStoreCount++;
    MASTER->TypeStores[TypeStore].TypeCount++;

}

void initStorages(struct MASTER *MASTER) {
    MASTER->TypeStoreCount = 0;

    for (int TypeStore = 0; TypeStore < MAX_TYPESTORES; TypeStore++) {
        MASTER->TypeStores[TypeStore].TypeCount = 0;

        for (int Type = 0; Type < MAX_TYPES; Type++) {
            strcpy(MASTER->TypeStores[TypeStore].Types[Type].Name, "\0");
            MASTER->TypeStores[TypeStore].Types[Type].AmmoCount = 0;

            for (int Ammo = 0; Ammo < MAX_AMMO; Ammo++) {
                strcpy(MASTER->TypeStores[TypeStore].Types[Type].Ammo[Ammo].Name, "\0");
                MASTER->TypeStores[TypeStore].Types[Type].Ammo[Ammo].AirFriction = 0;

                for (int Charge = 0; Charge < MAX_CHARGES; Charge++) {
                    MASTER->TypeStores[TypeStore].Types[Type].Ammo[Ammo].Charge[Charge] = 0;
                }
            }
        }
    }
}

void AddGun(long int x, long int y, long int Elevation, int type, int ammo, struct Gun *Storage) {

    int gunAmount = sizeof(*Storage)/sizeof(struct Gun) + 1;

    struct Gun *temp = malloc(sizeof(struct Gun) * (gunAmount - 1));

    for (int i = 0; i < (gunAmount - 1); i++) {
        temp[i].id = Storage[i].id;
        temp[i].x = Storage[i].x;
        temp[i].y = Storage[i].y;
        temp[i].z = Storage[i].z;
        temp[i].type = Storage[i].type;
        temp[i].ammo = Storage[i].ammo;
    }

    void *test = realloc(Storage, sizeof(struct Gun) * gunAmount);

    if (test == NULL) {
        printf("    ERROR: REALLOC FAILED L. 169");
    }

    for (int i = 0; i < (gunAmount - 1); i++) {
        Storage[i].id = temp[i].id;
        Storage[i].x = temp[i].x;
        Storage[i].y = temp[i].y;
        Storage[i].z = temp[i].z;
        Storage[i].type = temp[i].type;
        Storage[i].ammo = temp[i].ammo;  
    }

    free(temp);

    Storage[gunAmount - 1].id = gunAmount;
    Storage[gunAmount - 1].x = x;
    Storage[gunAmount - 1].y = y;
    Storage[gunAmount - 1].z = Elevation;
    Storage[gunAmount - 1].type = type;
    Storage[gunAmount - 1].ammo = type;
}

void RemoveGun(int id, struct Gun *Storage) {
    int size = sizeof(Storage)/sizeof(struct Gun);
    
    struct Gun *temp = malloc(sizeof(struct Gun) * (size - 1));

    for (int i = 0, n = 0; i < size; i++) {
        if (i != id) {
            temp[n].id = n;
            temp[n].x = Storage[i].x;
            temp[n].y = Storage[i].y;
            temp[n].z = Storage[i].z;
            temp[n].type = Storage[i].type;
            temp[n].ammo = Storage[i].ammo;

            n++;
        }
    }

    void *test = realloc(Storage, sizeof(struct Gun) * (size - 1));

    if (test == NULL) {
        printf("    ERROR: REALLOC FAILED L. 208");
    }

    for (int i = 0; i < size - 1; i++) {
        Storage[i].id = temp[i].id;
        Storage[i].x = temp[i].x;
        Storage[i].y = temp[i].y;
        Storage[i].z = temp[i].z;
        Storage[i].type = temp[i].type;
        Storage[i].ammo = temp[i].ammo;    
    }

    free(temp);
}

void ListAllTypes(struct MASTER *MASTER) {

    if (MASTER->TypeStores[0].TypeCount == 0) {
        printf("    NO TYPES DEFINED\n\n");
        return;
    }

    for (int TypeStorage = 0; TypeStorage < MAX_TYPESTORES && MASTER->TypeStores[TypeStorage].TypeCount != 0; TypeStorage++) {
        printf("----TYPESTORAGE ID: %d\n\n", TypeStorage + 1);

        for (int Type = 0; Type < MAX_TYPES && MASTER->TypeStores[TypeStorage].Types[Type].AmmoCount != 0; Type++) {
            printf("    TYPE NAME: %s,\tTYPE ID: %d\n", MASTER->TypeStores[TypeStorage].Types[Type].Name, Type + 1);
        }
    }

    printf("\n");
}

void ListAllAmmo(struct MASTER *MASTER, int TypeStore, int Type) {

    if (MASTER->TypeStores[TypeStore].Types[Type].AmmoCount == 0) {
        printf("    NO AMMO DEFINED\n");
        return;
    }

    for (int Ammo = 0; Ammo < MASTER->TypeStores[TypeStore].Types[Type].AmmoCount; Ammo++) {
        printf("    AMMO NAME: %s, AMMO ID: %d, AMMO AIR FRICTION: %lf, CHARGES:\n", MASTER->TypeStores[TypeStore].Types[Type].Ammo[Ammo].Name, Ammo + 1, MASTER->TypeStores[TypeStore].Types[Type].Ammo[Ammo].AirFriction);
        
        for (int Charge = 0; Charge < MAX_CHARGES && MASTER->TypeStores[TypeStore].Types[Type].Ammo[Ammo].Charge[Charge] != 0; Charge++) {
            printf("        CHARGE: %d, VELOCITY: %ld\n", Charge + 1, MASTER->TypeStores[TypeStore].Types[Type].Ammo[Ammo].Charge[Charge]);
        }

        printf("\n");
    }

}

// !PLACEHOLDER - NOT FINISHED!
void QuickFireMission(struct Gun *GunStorage, struct Tgt *TgtStorage, int Angle) {

}
