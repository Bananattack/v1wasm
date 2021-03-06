struct chrrec {
    char fname[13];
};

struct entitydata {
    int x, y;                              // starting/current location
    unsigned char chrindex, movecode;      // CHR index / movement pattern code
    unsigned char activmode, obsmode;      // activation mode, obstruction mode
    unsigned int actscript, movescript;    // script references
    unsigned char spedm, spedd;            // entity speed multiplier/divisor
    unsigned short data1, data2,           // Misc data entries
             data3, data4;           // More misc data
    char entitydesc[20];                   // Editing description
};

extern struct chrrec chrlist[100];           // CHR list
extern struct entitydata entity[100];        // Entity data
extern int entities;                         // number of active entities

int EntityAt(int ex, int ey);
void ProcessSpeedAdjEntity(int i);

void GetNextCommand(int i);
void MoveDown(int i);
void MoveLeft(int i);
void MoveRight(int i);
void MoveUp(int i);
