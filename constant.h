#include <sys/types.h>
#include <stdio.h>

#include <libgte.h>
#include <libetc.h>
#include <libgpu.h>
#include <libsnd.h>
#include <libspu.h>
#include <rand.h>
#include <libapi.h>

#include <libcd.h>
#include <malloc.h>

#define BtoS(len) ( ( len + CD_SECTOR_SIZE - 1 ) / CD_SECTOR_SIZE ) 
// Name of file to load
static char * loadFile;
// libcd's CD file structure contains size, location and filename
CdlFILE filePos = {0};
//~ struct EXEC * exeStruct;
// Define start address of allocated memory
// Let's use an array so we don't have to worry about using a memory segment that's already in use.
static unsigned char ramAddr[0x40000]; // https://discord.com/channels/642647820683444236/663664210525290507/864936962199781387
// We could also set a memory address manually, but we have to make sure this won't get in the way of other routines.
// void * ramAddr = (void *)0x80030D40; 
// Load data to this buffer
u_long * dataBuffer;              
// Those are not strictly needed, but we'll use them to see the commands results.
// They could be replaced by a 0 in the various functions they're used with.
u_char CtrlResult[8];
// Value returned by CDread() - 1 is good, 0 is bad
int CDreadOK = 0;
// Value returned by CDsync() - Returns remaining sectors to load. 0 is good.
int CDreadResult = 0;

CVECTOR fntColorBG = { 0, 0, 0 };
CVECTOR fntColor = { 255, 255, 255 };

#define FONTX   960
#define FONTY   0

#define TRUECOL 1               // 0 : 16bpp, 1: 24bpp

#define VMODE 0                 // Video Mode : 0 : NTSC, 1: PAL
#define SCREENXRES 320          // Screen width
#define SCREENYRES 240          // Screen height
#define CENTERX SCREENXRES/2    // Center of screen on x 
#define CENTERY SCREENYRES/2    // Center of screen on y

#define MARGINX 0                // margins for text display
#define MARGINY 40

#define FONTSIZE 25 * 7           // Text Field Height
DISPENV disp[2];                 // Double buffered DISPENV and DRAWENV
DRAWENV draw[2];
short db = 0;                      // index of which buffer is used, values 0, 1

// Number of VAG files to load
#define VAG_NBR 14
#define MALLOC_MAX VAG_NBR            // Max number of time we can call SpuMalloc

// convert Little endian to Big endian
#define SWAP_ENDIAN32(x) (((x)>>24) | (((x)>>8) & 0xFF00) | (((x)<<8) & 0x00FF0000) | ((x)<<24))
// Memory management table ; allow MALLOC_MAX calls to SpuMalloc() - libref47.pdf p.1044

char spu_malloc_rec[SPU_MALLOC_RECSIZ * (MALLOC_MAX + 1)]; 

// Custom struct to handle VAG files
typedef struct VAGsound {
    u_char * VAGfile;        // Pointer to VAG data address
    u_long spu_channel;      // SPU voice to playback to
    u_long spu_address;      // SPU address for memory freeing spu mem
} VAGsound;

// VAG header struct (see fileformat47.pdf, p.209)
typedef struct VAGhdr {                // All the values in this header must be big endian
        char id[4];                    // VAGp         4 bytes -> 1 char * 4
        unsigned int version;          // 4 bytes
        unsigned int reserved;         // 4 bytes
        unsigned int dataSize;         // (in bytes) 4 bytes
        unsigned int samplingFrequency;// 4 bytes
        char  reserved2[12];           // 12 bytes -> 1 char * 12
        char  name[16];                // 16 bytes -> 1 char * 16
        // Waveform data after that
} VAGhdr;

// SPU settings
SpuCommonAttr commonAttributes;          // structure for changing common voice attributes
SpuVoiceAttr  voiceAttributes ;          // structure for changing individual voice attributes   

extern void display(void);

int RAN;
int Ran(int max)
{
    RAN = (rand()%max);
    if (RAN == 0) {RAN++;}
    return 0;
} // MY SAVIOR !!!!!!!

void clearVRAMMenu(void)
{
    RECT rectTL;
    setRECT(&rectTL, 700, 0, 260, 511); //Clear all but the font
    ClearImage2(&rectTL, 0, 0, 0);
    DrawSync(0);
}

void clearVRAM(void)
{
    RECT rectTL;
    setRECT(&rectTL, 0, 0, 960, 256); //Clear all but the font
    ClearImage2(&rectTL, 0, 0, 0);
    setRECT(&rectTL, 0, 256, 1048, 256);
    ClearImage2(&rectTL, 0, 0, 0);
    DrawSync(0);
}

int initstuff = 0;

int pad = 0;    

int frames = 500;

int menuscreeninit = 0;
int menu = 0;
int maincustomnightmenu = 0;
int AISetmenu = 0;
int chargemenu = 0;
int advancedmenu = 0;
int freddyfacechanged = 0;
int freddyfacechangedchances = 400;
int helpwantedposter = 0;

int freddylocationframelock = 181;
int bonnielocationframelock = 298;
int chicalocationframelock = 299;
int foxylocationframelock = 301;

int presetselector = 1;
int presetselectorlimiterright = 0;
int presetselectorlimiterleft = 0;
char presetselectorstr[] = "Custom";

int menuselection = 2;
int menuselectionmax = 4;
int musicframes = 3788;
int limitermenuL = 0;
int limitermenuR = 0;
int freddylightframe = 0;
int activatedmenudebug = 0;
int printnumber = 3;
int FrameCounterlimiterup = 0;
int FrameCounterlimiterdown = 0;
int FrameCounterlimit = 0;
int convertion = 60;
int extramenu = 0;
int infoscreen = 0;
int bonniestared = 0;
int seedtitle = 0;
int unlimitedpower = 0;
char unlimitedpowerstr[] = "OFF";
char radarstr[] = "OFF";
char fastnightsstr[] = "OFF";
int radar = 0;
int unlockssubmenu = 0;
int limiterunlimitedpower = 0;
int limiterfastnights = 0;
int limiterradar = 0;
int fastnights = 0;
int cheating = 0;
int savemenu = 0;
int defaultusage = 1;

int twoplayermode = 0;
char twoplayermodestr[] = "OFF";
int twoplayermodelimiter = 0;

int loadingframe = 0;
int goldenfreddied = 0;
int goldenfreddiedframes = 0;
int weirdnight = 0;
int hellnight = 0;
int impossiblenight = 0;
int Glitch = 0;

int limiterpadright = 0;
int limiterpadleft = 0;
int limiterpaddown = 0;
int limiterpadup = 0;
int limiterbuttondown = 0;
int limiterstart = 0;

int freddylocation = 0;
int freddylocationframe = 181;
int freddyanticipation = 0;
int freddycountdownactivation = 0;
int freddycountdown = -1;
int freddydifficulty = 0;
int freddyliljumpscare = 0;
int freddyliljumpscarecooldown = 0;
int bonnielocation = 0;
int bonnieliljumpscare = 0;
int bonnieliljumpscarecooldown = 0;
int bonnielocationframe = 298;
int bonniedifficulty = 0;
int bonnieonetimeskip = 0;
int chicalocation = 0;
int chicalocationframe = 299;
int chicadifficulty = 0;
int chicaonetimeskip = 0;
int foxylocation = 0;
int foxylocationframe = 301;
int foxywaiting = 500;
int foxyrunningframes = 0;
int foxydifficulty = 0;
int foxylocked = 0;
int foxylockeduration = 16;
int ranfoxy = 0;
int foxysknock = 0;
int foxyknockframe = 0;
int foxydrainpower = 1;
int bonnieDoor = 0;
int chicaDoor = 0;
int bonnieDoorinit = 0;
int chicaDoorinit = 0;
int noisedoorbonnie = 0;
int noisedoorchica = 0;
int surusage = 0;
int goldenfreddylocation = 0;
int goldenfreddyframes = 0;
int goldenfreddychances = 500;
int goldenfreddyactivated = 0;
int goldenfreddychancescrash = 2000;
int nolongerincam = 0;

int sparkylocation = 0;
int sparkyframes = 0;

int door = 0; //0 is left, 1 is right
int doorclosedL = 0; //0 is no, 1 is yes
int doorclosedR = 0; //0 is no, 1 is yes
int leftdoorgoodbye = 1;
int leftdoorgoodbye2 = -1;
int rightdoorgoodbye = 1;
int rightdoorgoodbye2 = -1;
int jamlight = 0;
int jamlightframes = 0;
int cantlight = 0;
int cantdoor = 0;
int cantlightR = 0;
int cantdoorR = 0;
int cantlightL = 0;
int cantdoorL = 0;
int speedoffice = 3;

int light1 = 0;
int light2 = 0;
int lightframe = 0;

int camlimiter = 0;
int limiter2 = 0;
int limiter3 = 0;
int limiterbop = 0;

int animatronicscamera[6] = {0,0,0,0,0,0}; //Freddy, Bonnie, Chica, foxy, GF, Sparky
int camera = 0;
int cooldowncamera = 0;
char curcam[2] = "1A";
char curcamname[16] = "Show Stage";
int limitercameraD = 0;
int limitercameraU = 0;
int limitercameraR = 0;
int limitercameraL = 0;
int puppetmusic = 0;
int itsmepiratecove = 0;
int itsmepiratecovecooldown = 0;
int itsmeehallcorner = 0;
int itsmeehallcornercooldown = 0;
int itsmeehall = 0;
int itsmeehallcooldown = 0;
int blinkicon = 0;
int foxymusic = 0;
int foxymusicframe = 540;

/*
Rest of something I'd have liked to do, the "return" thing.
int returnframes = 0;
int returnbasevolume = 0x1800;
*/ 
int noisefootstep = 0;
int framenoisefootstep = 0;
int noisefootstepanimatronic = 0;

int noisefootstepF = 0;
int framenoisefootstepF = 0;

int tensecondframe = 600;
int ambiancesound = 1;
int ambiancechance = 1;
int ambiancenum = 3;

int mascottune = 0;
int musicmascottune = 1248;

int enablephoneguy = 1;
char enablephoneguystr[] = "ON";
int limiterphoneguy = 0;
int phoneguytalking = 0;

int islightsout = 0;
int lightsoutinit = 0;

int musicboxactivated = 0;
int musicboxappearanceframe = 0;
int musicboxappearancechance = 20;
int musicboxinit = 0;
int freddyglowing = 0;
int glowvar = 128;

int blackoutactivated = 0;
int blackoutappearanceframe = 0;
int blackoutappearancechance = 20;
int blackoutinit = 0;

int blackoutscreamerappearanceframe = 0;
int blackoutscreamerappearancechance = 20;

int isalreadydead = 0;
int isalreadydeadlow = 0;
int framedeadpossi = 60;
int lastsecondsframes = 1800;
int screamersetsound = 0;
int screamerframes = 47;
int dead = 0;
int deadfrom = 0;
int spriteframes = 3;
int spritesheet = 0;

int fivetosixamframes = 0;
int nextnightframes = 0;
int customnextnightactivation = 0;
int staticframessheet = 0;

//Specific for the special ending
int rgbred = 128;
int rgbgreen = 128;
int rgbblue = 128;
int rgbindicator = 0;

int staticframes = 600;

int nightwon = 0;

int score = 0;
int blockedanimatronic = 0;
int timeoncam = 0;
int powermanagementhour = 0;
int powermanagementtotal = 0;

int fadeoffice = 128;

#define OTLEN 8                    // Ordering Table Length 

u_long ot[2][OTLEN];               // double ordering table of length 8 * 32 = 256 bits / 32 bytes

char primbuff[2][32768];     // double primitive buffer of length 32768 * 8 =  262.144 bits / 32,768 Kbytes

char *nextpri = primbuff[0];       // pointer to the next primitive in primbuff. Initially, points to the first bit of primbuff[0]

#define COUNT_OF(x) (sizeof(x) / sizeof(0[x]))