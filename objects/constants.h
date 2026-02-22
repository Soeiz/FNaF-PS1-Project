#include <sys/types.h>
#include <sys/file.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include <kernel.h>
#include <libgte.h>
#include <libetc.h>
#include <libgpu.h>     
#include <libsnd.h>     
#include <libspu.h>     
#include <rand.h>       
#include <libapi.h>    
#include <libmcrd.h>    

#include <libcd.h>
#include <malloc.h>

#include <libpress.h>

//Loading Data

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

//SPU System
            
    // Number of VAG files to load
        #define VAG_NBR 16
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

//Basic things

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

//Music / Sounds things
    // SPU attributes
    SpuCommonAttr spuSettings;

    // XA
    #define CD_SECTOR_SIZE 1204
    // XA
    // Sector offset for XA data 4: simple speed, 8: double speed
    #define XA_CHANNELS 8
    #define XA_CDSPEED XA_CHANNELS >> 2
    // Number of XA samples ( != # of XA files )
    #define XA_TRACKS 4

    typedef struct XAsound {
        u_int id;
        u_int size;
        // We can find size in sector : size / 2336, start value begins at 23, end value is at start + offset ( (size / 2336)-1 * #channels )
        // subsequent start value have an 8 bytes offset (n-1.end + 8)
        u_char file, channel;
        u_int start, end;
        int cursor;
    } XAsound;

    typedef struct XAbank {
        u_int index;
        int offset;
        XAsound samples[];
    } XAbank;

//General functions 
            
    extern void display(void);
    
    int timesControllerPressed; //Used also for Random, how many times the player has pressed the controllers
    int seedRand; //Frames for random
    int RAN;
    int Ran(int max)
    {
        RAN = (rand()%max);
        if (RAN == 0) {RAN++;}
        return RAN;
    }

    void clearVRAM(int type) {
        /*
            "type" values :
                0 : Regular (almost everything)
                1 : Menu
                2 : Screamer
                4 : Only Chica

        */
        
        RECT rectTL;

        switch(type) {
            case 0:
                setRECT(&rectTL, 0, 0, 960, 256); //Clear all but the font
                ClearImage2(&rectTL, 0, 0, 0);
                setRECT(&rectTL, 0, 256, 1048, 256);
                ClearImage2(&rectTL, 0, 0, 0);
            break;
            case 1:
                setRECT(&rectTL, 700, 0, 260, 511);
                ClearImage2(&rectTL, 0, 0, 0);

            break;
            case 2:
                setRECT(&rectTL, 576, 256, 106, 126); 
                ClearImage2(&rectTL, 0, 0, 0);

            break;
            case 4:
                setRECT(&rectTL, 357, 0, 17, 134); 
                ClearImage2(&rectTL, 0, 0, 0);

            break;
            default: //Default is nothing (to prevent weird things happening)

            break;
        }

        DrawSync(0);
    }

    
//Main 
    int menu = 0;

    int global_alpha = 127; //Every objects are affected by this. If 128, it will get ignored for "local" coloring.

    int font_alpha = 255; //Font COLOR (255 = white)

    int InAndOut_alpha = 0; //Used for fade out & fade in

// Warning Scene
    
    int timer_frame_FFW_warning = 180;

//Two player mode System

    bool twoPlayerMode = false;
    char twoPlayerModeStr[] = "OFF";

//Menu selection System

    bool menuScreenInit = false;

    bool returnedInGame = false;

    bool newGameSelected = false;

    bool helpWantedPoster = false;

    int menu_alpha = 128;

    int timingFreddyLightFrame = 120;
    int freddyFaceChangedChances = 400;

    bool linesactive = false; 
    int linesframes = 0;

    int menuSelection = 2;
    int menuSelectionMax = 4;
    bool cheating = false;
    bool inCustomNight = false;

    bool limiterPadUp, limiterPadDown, limiterPadRight, limiterPadLeft, limiterPadStart, limiterPadCross, limiterPadCircle, limiterbop, limiterPadR1, limiterPadL1 = false;

    bool unlimitedPower = false;
    char unlimitedPowerStr[] = "OFF";

    bool radar = false;
    char radarStr[] = "OFF";

    bool fastNights = false;
    char fastNightsStr[] = "OFF";

    int musicFrames = 3788;

    int currentVolume = 128;

    int currentMenu[2] = {0,0};

    //First index, 0 Is main menu, 1 is extra menu, 2 is custom night menu, 3 is welcome menu.
    /*
        second index (submenu) :

            submenu in extra menu :

            1 : unlocks menu
            2 : Info screen
            3 : Achievements

            submenu in custom night menu :

            1 : AI set menu
            2 : timer menu
            3 : Advanced menu
    */
        //Menu - Timer / Charge selection
        
        int customBattery = 100;

        int customAM = 12;

        int convertionFramesToAM = 60; //Basically, 60 is, in Game, 60 minutes OR 1 hour  
        


        //Menu - AI preset selection System

        int presetSelector = 1;
        char presetSelectorStr[] = "Custom";

        bool achievements[] = {false,false,false,false,false,false,false,false,false,false,false};

        int achievementstest[] = {0,0,0,0,0,0,0,0,0,0};

        char achievementsName[11][15] = {"Night 1", "Night 2", "Night 3", "Night 4", "Night 5", "Night 6", "4/20", "Hell Night", "Golden Fredied", "Freddy Date", "Night 1 Fail"};

        int page = 0;

        /*
            Night1
            Night2
            Night3
            Night4
            Night5
            Night6
            4/20
            Hell Night
            Golden Freddy jumpscare
            "Freddy Date" / FreddyDifficulty == 20


        */

        bool rizzingF = false;
        bool rizzingFDone = false;

        bool fourTwentyDone = false;

        bool goldenfredied = false;

        bool diedOnNight1 = false;

        int Night6State = 0;

        /*
            Night6State:

            - 0: Locked
            - 1: Unlocked, but not done
            - 2: Unlocked and done
        */



//Help Wanted Related

    int HelpWantedFrame = 300;

//Loading Screen Related

    int NightTextFrame = 200;

    bool FirstTimeLoading = true;

//Office Related

    int defaultUsage = 1;
    int currentUsage = 1;

    bool curDoorLook = false; //Indicates which door you have control over. false is left, true is right

    bool doorClosedL = false;
    bool doorClosedR = false;
    
    bool lightL = false;
    bool lightR = false;
    int lightFrameBlink = 0;

    bool jamNoise = false;
    int jamNoiseFrame = 0;

    int leftdoorhello = 1;
    int leftdoorgoodbye = -1;

    int rightdoorhello = 1;
    int rightdoorgoodbye = -1;

    bool cantDoorL = false;
    bool cantDoorR = false;

    int office_alpha = 128; //Basically, the color of the office (128 = normal, 0 = black)

    bool isLightsOut = false;
    int LightsOutPhase = 0;

    /*
        LightsOutPhase has multiple states : 

        - 1 No lights
        - 2 Music Box
        - 3 Black Out

    */

    bool NoLightInit = false;

    int NoLightTOMusicBoxChance = 20;
    int NoLightTOMusicBoxChanceFRAME = 0;

    bool MusicBoxInit = false;

    int MusicBoxTOBlackOutChance = 20;
    int MusicBoxTOBlackOutChanceFRAME = 0;
    int FreddyGlowingFrame = 0;
    int glowVar = 128;

    bool BlackOutInit = false;

    int BlackOutTOJumpscareChance = 20;
    int BlackOutTOJumpscareChanceFRAME = 0;

    int FrameFan = 0;

    int speedoffice = 3;

//Game Related

    int XCoordinates = 10;

    int AM = 12;

    int battery = 100;

    int ChargeCounter = 596; //Basically represent 1 % of battery

    int FrameCounter = 0; //Bascially represent 1 hour / 1 minute

    int FrameCounterlimit = 0; //Used for counting 1 minute

    int night = 1;

    int bestNight = 1; //Used to determine between resets which night you've really beaten, even after pressing "new game"

    bool night6unlock = false;
    bool isOnNight6 = false;

    bool nightWon = false;

    int nextNightFrame = 0;

    bool hellNight = false;
    bool hellNightDone = false;

    bool gotYou = false;

    int AnimatronicWaitingFrame = 0;
    bool isAlreadyDead = false;
    bool isAlreadyDeadLow = false;
    bool dead = false;

    int ScreamerSpriteFrameLength = 3;
    int ScreamerSpriteSheet = 0;

    //Ambiance / Soundtrack Related

        int puppetMusicFrame = 0;

        int ambianceChance = 0;

        int ambianceFrame = 300;

        int ambianceIndex = 0;

        //PhoneGuy

            bool isPhoneGuyTalking = false;

            bool isPhoneGuyEnabled = true;

            int phoneGuyTalkingFrame, phoneGuyTalkingFrameCONST = 0;

            bool MutedCall = false;

    //Camera Related

        bool ITSME_WestHallCorner, ITSME_PirateCove, ITSME_EastHall = false;

        bool isOnCamera = false;

        int cameraGlitchFrame = 0;

        int cooldownSpamCamera = 0; //So that it won't get spammed

        char curCam[2] = "1A";

        char curCamName[16] = "Show Room";

        int blinkIcon = 0; //Used to make blink the animatronics's icons.

        int animatronicsPresenceOnCamera[6] = {0,0,0,0,0,0}; //Freddy, Bonnie, Chica, foxy, GF, Sparky

        /*
    
            if animatronicsPresenceOnCamera[0] == 0 (example), Freddy will not be present.

            if animatronicsPresenceOnCamera[1] == 1, Bonnie will technically present, but not shown.

            if animatronicsPresenceOnCamera[2] == 2, Chica will be present.

        */

    //Animatronics Related

        bool NoiseFootstep = false;
        int FootstepAnimatronicNumber = 0;
        int FootStepFrames = 0;

        //Freddy

            int FreddyLocation = 0;
            int FreddyLocationFrame = 0;
            int FreddyLocationFrameLock = 181;
            int FreddyDifficulty = 0;

            int frameFreddyEnter = 60;
            bool FreddyAnticipation = false;
            bool FreddyNoiseFootstep = false;

        //Bonnie

            int BonnieLocation = 0;
            int BonnieLocationFrame = 0;
            int BonnieLocationFrameLock = 298;
            int BonnieDifficulty = 0;

            bool noiseDoorBonnie = false;
            bool BonnieDoorInit = false;
            bool BonnieIsAtDoor = false;
            bool BonnieOneTimeSkip = false;

        //Chica

            int ChicaLocation = 0;
            int ChicaLocationFrame = 0;
            int ChicaLocationFrameLock = 299;
            int ChicaDifficulty = 0;

            bool noiseDoorChica = false;
            bool ChicaDoorInit = false;
            bool ChicaIsAtDoor = false;
            bool ChicaOneTimeSkip = false;

        //Foxy

            int FoxyLocation = 0;
            int FoxyLocationFrame = 0;
            int FoxyLocationFrameLock = 301;
            int FoxyDifficulty = 0;


            int FoxyLockedFrames = 0;
            int FoxyRunningFrames = 0;
            int FoxyDrainPower = 1;
            int FoxyWaitingToRun = 500;
            bool FoxyKnock = false;
            int FoxyKnockFrames = 0;

        //Sparky (????????)

            int SparkyLocation = 0;

        //Golden Freddy

            bool goldenFreddyPoster = false;
            bool goldenFreddyActivated = false;
            int goldenFreddyFrameUntilDeath = 0;
            bool deadtogoldenfreddy = false;
            bool kaboom = false;

        //1987 menu

            int menu1987 = 0;

        //Screamer related

            int screamerFrame = 0;

            int spriteFrame = 0; //When it reaches 0, a new sprite from the screamer appears.

            int spriteSheet = 0;

    //Fan animation

        int fanFrame = 0;

//Dead Screen

    int staticDeadFrames = 0;
    int staticFrameSheet = 0;

//Good Job screen Related

    int rgbRed = 138;
    int rgbGreen = 128;
    int rgbBlue = 118;
    int rgbIndicator = 0;
    bool funky = false;


//Controller Related

    int pad = 0;

//Debug

    bool DebugActivated = false;

    int debugPrintNumber = 1;

    int deadFrom = 0;


//Display Related

    #define OTLEN 8                    // Ordering Table Length 

    u_long ot[2][OTLEN];               // double ordering table of length 8 * 32 = 256 bits / 32 bytes

    char primbuff[2][32768];     // double primitive buffer of length 32768 * 8 =  262.144 bits / 32,768 Kbytes

    char *nextpri = primbuff[0];       // pointer to the next primitive in primbuff. Initially, points to the first bit of primbuff[0]

    #define COUNT_OF(x) (sizeof(x) / sizeof(0[x]))
