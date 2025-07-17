float power(float x, int y);

// Converts a string to the sum of the characters decimal value
int StrToInt(char *string);

// Converts a string of numbers to a long integer
long int NumberStrToLI(char *string);

int GridToCoordinates(char grid[], long int *x, long int *y);

void DisMillsToCoordinates(int distance, int direction, char *CurrentGrid, long int *x, long int *y);

long int MillsFromCoordinate(long int dx, long int dy);

void GridsToDisMills(char *GridOne, char *GridTwo, long int *Distance, long int *Direction);

void Save(void);

int ExitWithoutSaving(void);

int EnterCommand(int Min, int Max);

int EnterType(void);

int EnterAmmo(int type);

int EnterGunID(void);