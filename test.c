#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "lib.c"


#define MAX_TYPESTORES 5
#define MAX_TYPES 5
#define MAX_AMMO 5
#define MAX_CHARGES 20

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

struct MASTER {
    int TypeStoreCount;
    struct TypeStorage TypeStores[MAX_TYPESTORES];
};

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

int main(void) {

    struct MASTER MASTER;

    initStorages(&MASTER);

    AddType(&MASTER, 0);

    ListAllTypes(&MASTER);

    ListAllAmmo(&MASTER, 0, 0);

    return 0;
}