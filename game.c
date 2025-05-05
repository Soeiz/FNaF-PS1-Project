/*
    TO FIX :

    FIXED ? (it is not doing that anymore but I'm not sure if it's fixed) : 

    TO FIX ON THE PS1 :

    TO MAKE (doing ideas/partially implemented things) : 

    TO DO (only ideas) :
    - Test the game on different hardware than PC and SCPH-9002 PS1

    OTHER (info) :

    

    V1.2.6
*/

int FrameCounter = 0;
int customAM = 12;

int AM = 12;

int ChargeCounter = 596;
int usage = 1;
int charge = 100;

int customcharge = 100;

int night = 1;

int debug = 3; //1 is for debug without cam, 2 is animatronic debug, 3 is only little things -- vanilla

#include "objects/constant.h"
#include "objects/objects.h"
#include "objects/camera.h"
#include "objects/PATH.h"
#include "objects/asc2sjis.h"

//Made all of the var declarations that I won't change alot into constant.h

// extern VAG files
extern u_char _binary_vag_Door_vag_start;
extern u_char _binary_vag_light_vag_start;
extern u_char _binary_vag_Monitor_vag_start;
extern u_char _binary_vag_officesound_vag_start;
extern u_char _binary_vag_click_vag_start;
extern u_char _binary_vag_noisedoor_vag_start;
extern u_char _binary_vag_screamer_vag_start;
extern u_char _binary_vag_honk_vag_start;
extern u_char _binary_vag_Footstep_vag_start;
extern u_char _binary_vag_knock_vag_start;
extern u_char _binary_vag_footstepfoxy_vag_start;
extern u_char _binary_vag_lightout_vag_start;
extern u_char _binary_vag_jamlight_vag_start;
extern u_char _binary_vag_footstep2_vag_start;

// soundBank
VAGsound vagsoundBank[VAG_NBR] = {
      { &_binary_vag_Door_vag_start,
        SPU_00CH, 0 },  
      { &_binary_vag_light_vag_start,
        SPU_01CH, 0 },   
      { &_binary_vag_Monitor_vag_start,
        SPU_02CH, 0 },   
      { &_binary_vag_officesound_vag_start,
        SPU_03CH, 0 },
      { &_binary_vag_click_vag_start,
        SPU_04CH, 0 },
      { &_binary_vag_noisedoor_vag_start,
        SPU_05CH, 0 },
      { &_binary_vag_screamer_vag_start,
        SPU_06CH, 0 },
      { &_binary_vag_honk_vag_start,
        SPU_07CH, 0 },
      { &_binary_vag_Footstep_vag_start,
        SPU_08CH, 0 },
      { &_binary_vag_knock_vag_start,
        SPU_09CH, 0 },
      { &_binary_vag_footstepfoxy_vag_start,
        SPU_10CH, 0 },
      { &_binary_vag_lightout_vag_start,
        SPU_11CH, 0 },
      { &_binary_vag_jamlight_vag_start,
        SPU_12CH, 0 },
      { &_binary_vag_footstep2_vag_start,
        SPU_13CH, 0 }
};
// XA
// SPU attributes
SpuCommonAttr spuSettings;
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

XAbank soundBank = {
        23,
        0,
        {   //Static.xa = 1,496
            // channel 5
            // id   size   file  channel start end cursor
            {   0,  2747136,   1,     5,     0,   9400,  -1 }, //Intro.xa
            {   1,  2490176,   1,     5,     10896,   19432,  -1 }, //ambiance1.xa
            {   2,  971776,   1,     5,     20928,   24248,  -1 }, //CircusCursed.xa 
            // channel 6                 
            {   3,  488224,   1,     6 ,   0,   1664, -1  }, //6am.xa
            {   4,  932064,   1,     6 ,   3168, 6344, -1  }, //Poweroutage.xa
            {   5,  971776,   1,     6 ,   7840, 11160, -1  }, //Mascottune.xa / Circus.xa
            {   6,  2856928,   1,     6 ,   12656, 22432, -1  }, //ambiance2.xa
            // Channel 7
            {   7,  941408,   1,     7 ,   0, 3216, -1  }, //static.xa NOUBLIE PAS D'INCLURE LE SILENCE (à retirer ? -3192) +1,496
            {   8,  2476160,   1,     7 ,   4712, 13184, -1  }, //Ambiance3.xa 
            {   9,  8834752,   1,     7 ,   14680, 45028, -1  }, //Phone Guy Night 1.xa 
            //Channel 8
            {   10,  4307584,   1,     8 ,   0, 14752, -1  }, //Phone Guy Night 2.xa 
            {   11, 3041472,   1,     8 ,   16248, 26657, -1  }, //Phone Guy Night 3.xa  10408
            {   12, 2590624,   1,     8 ,   28152, 37016, -1  }, //Phone Guy Night 4.xa 
            {   13, 1702944,   1,     8 ,   38512, 44346, -1  }, //Phone Guy Night 5.xa 
            //Channel 9
            {   14, 2721440,   1,     9 ,   0, 9312, -1  }, //Music Box.xa 
            {   15, 2207520,   1,     9 ,   10808, 18360, -1  }, //phone guy lol (rizz freddy).xa 
            {   16, 696128,   1,     9 ,   19856, 22232, -1  }, //golden freddy screamer.xa 
            {   17, 677440,   1,     9 ,   23728, 26040, -1  }, //puppet music.xa 
            {   18, 425152,   1,     9 ,   27536, 28984, -1  }, //piratesong.xa 
            {   19, 4606592,   1,     9 ,   30480, 46248, -1  }, //funny music box.xa 
            //Channel 10
            {   20, 3237696,   1,     10 ,   0, 11080, -1  }, //Mixed ambiance 1
            {   21, 3078848,   1,     10 ,   14296, 24832, -1  }, //Mixed ambiance 2
            {   22, 3602112,   1,     10 ,   28048, 40376, -1  } //Mixed ambiance 3
        }
};
// XA file to load
static char * loadXA = "\\INTER8.XA;1";
// File informations : pos, size, name
CdlFILE XAPos = {0};
// CD filter
CdlFILTER filter;
// File position in m/s/f
CdlLOC  loc;

// Prototypes
void display(void);
void initSnd(void);
u_long sendVAGtoSPU(unsigned int VAG_data_size, u_char *VAG_data);
void setVoiceAttr(unsigned int pitch, long channel, unsigned long soundAddr );
u_long setSPUtransfer(VAGsound * sound);

/*
void FntColor(CVECTOR fgcol, CVECTOR bgcol )
{
    // The debug font clut is at tx, ty + 128
    // tx = bg color
    // tx + 1 = fg color
    // We can override the color by drawing a rect at these coordinates
    // 
    // Define 1 pixel at 960,128 (background color) and 1 pixel at 961, 128 (foreground color)
    RECT fg = { FONTX+1, FONTY + 128, 1, 1 };
    RECT bg = { FONTX, FONTY + 128, 1, 1 };
    // Set colors
    ClearImage(&fg, fgcol.r, fgcol.g, fgcol.b);
    ClearImage(&bg, bgcol.r, bgcol.g, bgcol.b);
}
*/
void LoadTexture(u_long * tim, TIM_IMAGE * tparam){     // This part is from Lameguy64's tutorial series : lameguy64.net/svn/pstutorials/chapter1/3-textures.html login/pw: annoyingmous
        OpenTIM(tim);                                   // Open the tim binary data, feed it the address of the data in memory
        ReadTIM(tparam);                                // This read the header of the TIM data and sets the corresponding members of the TIM_IMAGE structure
        
        LoadImage(tparam->prect, tparam->paddr);        // Transfer the data from memory to VRAM at position prect.x, prect.y
        DrawSync(0);                                    // Wait for the drawing to end

        if (tparam->mode & 0x8){ // check 4th bit       // If 4th bit == 1, TIM has a CLUT
            LoadImage(tparam->crect, tparam->caddr);    // Load it to VRAM at position crect.x, crect.y
            DrawSync(0);                                // Wait for drawing to end
        }
}

#include "objects/FunCtions/funcsInGame.h"
#include "objects/FunCtions/otherFuncs.h"
#include "objects/FunCtions/funcsprint&menu.h"

void init(void)
{   
    ResetCallback();
    ResetGraph(0);

    // Initialize and setup the GTE
    
    InitGeom();
    SetGeomOffset(CENTERX,CENTERY);
    SetGeomScreen(CENTERX);

    SetDefDispEnv(&disp[0], 0, 0         , SCREENXRES, SCREENYRES);     // Set display area for both &disp[0] and &disp[1]
    SetDefDispEnv(&disp[1], 0, SCREENYRES, SCREENXRES, SCREENYRES);     // &disp[0] is on top  of &disp[1]
    SetDefDrawEnv(&draw[0], 0, SCREENYRES, SCREENXRES, SCREENYRES);     // Set draw for both &draw[0] and &draw[1]
    SetDefDrawEnv(&draw[1], 0, 0         , SCREENXRES, SCREENYRES);     // &draw[0] is below &draw[1]
    // Set video mode
    if (VMODE){ SetVideoMode(MODE_PAL);}
    SetDispMask(1);                 // Display on screen    
    setRGB0(&draw[0], 0, 0, 0); // set color for first draw area
    setRGB0(&draw[1], 0, 0, 0); // set color for second draw area
    draw[0].isbg = 1;               // set mask for draw areas. 1 means repainting the area with the RGB color each frame 
    draw[1].isbg = 1;
    PutDispEnv(&disp[db]);          // set the disp and draw environnments
    PutDrawEnv(&draw[db]);
    //FntLoad(FONTX, FONTY);                // Load font to vram at FONTX,FONTY
    //FntOpen(100, 100, 48, 20, 0, 12 );    // FntOpen(x, y, width, height,  black_bg, max. nbr. chars)
    //FntColor(fntColor, fntColorBG);
    FntLoad(960, 0);
    FntOpen(MARGINX, SCREENYRES - MARGINY - FONTSIZE, SCREENXRES - MARGINX * 2, FONTSIZE, 0, 280 );
}

void display(void) {
    DrawSync(0);                    // Wait for all drawing to terminate
    VSync(0);                       // Wait for the next vertical blank
    PutDispEnv(&disp[db]);          // set alternate disp and draw environnments
    PutDrawEnv(&draw[db]);  
    DrawOTag(&ot[db][OTLEN - 1]);
    db = !db;                       // flip db value (0 or 1)
    nextpri = primbuff[db];
}


// Audio initialisation & functions
void initSnd(void){
    SpuInitMalloc(MALLOC_MAX, spu_malloc_rec);                      // Maximum number of blocks, mem. management table address.
    commonAttributes.mask = (SPU_COMMON_MVOLL | SPU_COMMON_MVOLR);  // Mask which attributes to set
    commonAttributes.mvol.left  = 0x3fff;                           // Master volume left
    commonAttributes.mvol.right = 0x3fff;                           // see libref47.pdf, p.1058
    commonAttributes.cd.volume.left = 0x6000;
    commonAttributes.cd.volume.right = 0x6000;
    // Apply settings
    SpuSetCommonAttr(&commonAttributes);                            // set attributes
    SpuSetIRQ(SPU_OFF);
    SpuSetKey(SpuOff, SPU_ALLCH);
}
void spuSetup(SpuCommonAttr * spuSettings)
{
    // Init Spu
    SpuInit();
    // Set master & CD volume to max
    spuSettings->mask = (SPU_COMMON_MVOLL | SPU_COMMON_MVOLR | SPU_COMMON_CDVOLL | SPU_COMMON_CDVOLR | SPU_COMMON_CDMIX);
    spuSettings->mvol.left  = 0x6000;
    spuSettings->mvol.right = 0x6000;
    spuSettings->cd.volume.left = 0x6000;
    spuSettings->cd.volume.right = 0x6000;
    // Enable CD input ON
    spuSettings->cd.mix = SPU_ON;
    // Apply settings
    SpuSetCommonAttr(spuSettings);
    // Set transfer mode 
    SpuSetTransferMode(SPU_TRANSFER_BY_DMA);
}

void XAsetup()
{   
    u_char param[4];
    // ORing the parameters we need to set ; drive speed,  ADPCM play, Subheader filter, sector size
    // If using CdlModeSpeed(Double speed), you need to load an XA file that has 8 channels.
    // In single speed, a 4 channels XA is to be used.
    param[0] = CdlModeSpeed|CdlModeRT|CdlModeSF|CdlModeSize1;
    // Issue primitive command to CD-ROM system (Blocking-type)
    // Set the parameters above
    CdControlB(CdlSetmode, param, 0);
    // Pause at current pos
    CdControlF(CdlPause,0);
}

u_long sendVAGtoSPU(unsigned int VAG_data_size, u_char *VAG_data){
    u_long transferred;
    SpuSetTransferMode(SpuTransByDMA);                              // DMA transfer; can do other processing during transfer
    transferred = SpuWrite (VAG_data + sizeof(VAGhdr), VAG_data_size);     // transfer VAG_data_size bytes from VAG_data  address to sound buffer
    SpuIsTransferCompleted (SPU_TRANSFER_WAIT);                     // Checks whether transfer is completed and waits for completion
    return transferred;
}

void setVoiceAttr(unsigned int pitch, long channel, unsigned long soundAddr ){
    voiceAttributes.mask=                                   //~ Attributes (bit string, 1 bit per attribute)
    (
      SPU_VOICE_VOLL |
      SPU_VOICE_VOLR |
      SPU_VOICE_PITCH |
      SPU_VOICE_WDSA |
      SPU_VOICE_ADSR_AMODE |
      SPU_VOICE_ADSR_SMODE |
      SPU_VOICE_ADSR_RMODE |
      SPU_VOICE_ADSR_AR |
      SPU_VOICE_ADSR_DR |
      SPU_VOICE_ADSR_SR |
      SPU_VOICE_ADSR_RR |
      SPU_VOICE_ADSR_SL
    );
    voiceAttributes.voice        = channel;                 //~ Voice (low 24 bits are a bit string, 1 bit per voice )
    voiceAttributes.volume.left  = 0x0;                  //~ Volume 
    voiceAttributes.volume.right = 0x0;                  //~ Volume
    voiceAttributes.pitch        = pitch;                   //~ Interval (set pitch)
    voiceAttributes.addr         = soundAddr;               //~ Waveform data start address
    voiceAttributes.a_mode       = SPU_VOICE_LINEARIncN;    //~ Attack rate mode  = Linear Increase - see libref47.pdf p.1091
    voiceAttributes.s_mode       = SPU_VOICE_LINEARIncN;    //~ Sustain rate mode = Linear Increase
    voiceAttributes.r_mode       = SPU_VOICE_LINEARDecN;    //~ Release rate mode = Linear Decrease
    voiceAttributes.ar           = 0x0;                     //~ Attack rate
    voiceAttributes.dr           = 0x0;                     //~ Decay rate
    voiceAttributes.rr           = 0x0;                     //~ Release rate
    voiceAttributes.sr           = 0x0;                     //~ Sustain rate
    voiceAttributes.sl           = 0xf;                     //~ Sustain level
    SpuSetVoiceAttr(&voiceAttributes);                      // set attributes
    SpuSetVoiceVolume(0, 0x1800, 0x1800);//Door
    SpuSetVoiceVolume(1, 0x1800, 0x1800);//light sound
    SpuSetVoiceVolume(2, 0x1800, 0x1800);//Monitor
    SpuSetVoiceVolume(3, 0x1400, 0x1400); //Officesound
    SpuSetVoiceVolume(4, 0x1800, 0x1800);//click
    SpuSetVoiceVolume(5, 0x1800, 0x1800);//Door noise
    SpuSetVoiceVolume(6, 0x4000, 0x4000);//Screamer
    SpuSetVoiceVolume(7, 0x1800, 0x1800);//Honk
    SpuSetVoiceVolume(8, 0x1000, 0x1000); //Footstep
    SpuSetVoiceVolume(11, 0x1000, 0x1000); //Footstep2
    SpuSetVoiceVolume(9, 0x2000, 0x2000); //Foxy's knocks
    SpuSetVoiceVolume(10, 0x1800, 0x1800); //Foxy's footsteps
    SpuSetVoiceVolume(11, 0x4000, 0x4000); //Light out
    SpuSetVoiceVolume(12, 0x6000, 0x6000); //Light jammed
}

u_long setSPUtransfer(VAGsound * sound){
    // Return spu_address
    u_long transferred, spu_address;
    u_int pitch;
    const VAGhdr * VAGheader = (VAGhdr *) sound->VAGfile;
    pitch = (SWAP_ENDIAN32(VAGheader->samplingFrequency) << 12) / 44100L; 
    spu_address = SpuMalloc(SWAP_ENDIAN32(VAGheader->dataSize));                // Allocate an area of dataSize bytes in the sound buffer. 
    SpuSetTransferStartAddr(spu_address);                                       // Sets a starting address in the sound buffer
    transferred = sendVAGtoSPU(SWAP_ENDIAN32(VAGheader->dataSize), sound->VAGfile);
    setVoiceAttr(pitch, sound->spu_channel, spu_address); 
    // Return 1 if ok, size transferred else.
    //~ if (transferred == SWAP_ENDIAN32(VAGheader->dataSize)){
        //~ return 1;
        //~ }
    //~ return transferred;
    return spu_address;
}

// Converts strings from 8-bit ASCII characters to 16-bit Shift-JIS character encoding
void asc2sjis(char *asctext, u_short *sjistext) {
    
    // A small function to simplify the use of the ascii2sjis() function in asc2sjis.c
    
    int  i;
    char *ptr;
    
    union {
        u_short code;
        struct {
            char low;
            char high;
        } k_word;
    } kanji;
    
    for (i=0, ptr=(u_char*)sjistext; asctext[i] != 0x00; i++) {
        kanji.code  = ascii2sjis(asctext[i]);
        *ptr++ = kanji.k_word.high;
        *ptr++ = kanji.k_word.low;
    }
    
    sjistext[i] = 0x00;
    
}

int main(void) {
    //controller
    TILE * PADL;                    // Tile primitives
    TILE * TRIGGERL;
    TILE * PADR;
    TILE * TRIGGERR;
    TILE * START, * SELECT;

    init();

    MemCardInit(0);
    MemCardStart();

    //SPU
    u_long spu_address;
    spuSetup(&spuSettings);
    // Init sound settings
    initSnd();

    //Controlling CD Volume 
    CdlATV cd_vol;

    PadInit(0);                     // Initialize pad.  Mode is always 0

    for (u_short vag = 0; vag < VAG_NBR; vag++ ){
        vagsoundBank[vag].spu_address = setSPUtransfer(&vagsoundBank[vag]);
    }


    // Init CD system
    CdInit();

    // Init heap
    InitHeap((u_long *)ramAddr, sizeof(ramAddr));

    int sample = -1;

    clearVRAM();

    //LoadGame();

    while (1) {   

        //if (createsave) {}
        ClearOTagR(ot[db], OTLEN);
        
        pad = PadRead(0);
        // if sample is set
        if (sample != -1 ){
            // Begin XA file playback...
            // if sample's cursor is 0
            if (soundBank.samples[sample].cursor == 0){
                // Convert sector number to CD position in min/second/frame and set CdlLOC accordingly.
                CdIntToPos( soundBank.samples[sample].start + soundBank.offset , &loc);
                // Send CDROM read command
                CdControlF(CdlReadS, (u_char *)&loc);
                // Set playing flag
            }
            // if sample's cursor is close to sample's end position, stop playback
            if ((soundBank.samples[sample].cursor += XA_CDSPEED) >= soundBank.samples[sample].end - soundBank.samples[sample].start  ){
                CdControlF(CdlStop,0);
                soundBank.samples[sample].cursor = -1;
                sample = -1;
            }
        }

        if (blinkicon < 61) {blinkicon++;}
        if (blinkicon == 60) {blinkicon = 0;}

        if (menu == 0) { //Menu Screen
            if (helpwantedposter == 0) {
                menuPrint();

                menuselectionfunc();

                if (ambiancenum > 8) {ambiancenum = 1;} else {ambiancenum++;} //For random ambiance sounds IG

                if (musicframes == 3788){
                    sample = 0;
                    filter.chan = soundBank.samples[sample].channel;
                    filter.file = soundBank.samples[sample].file;
                    CdControlF(CdlSetfilter, (u_char *)&filter);

                    soundBank.samples[sample].cursor = 0;
                    musicframes = 0;
                } else {musicframes++;}

                if (freddylightframe > 500) {
                    freddylightframe = 0;
                }
      
            }
            if (helpwantedposter == 1) {
                loadingframe++;

                if (loadingframe == 1) {
                    musicframes = 3787;
                    if (ambiancenum > 8) {ambiancenum = 1;}
                }
                if (loadingframe < 360) {

                    //Help wanted bg
                    makepoly(2);

                    if (loadingframe > 100) {
                        if (pad & PADstart) {
                            loadingframe = 360;
                        }
                    }
                }
                if (loadingframe > 240) {
                    if (fadeoffice < 128) {fadeoffice++;}

                    setRGB0(polyhelpwanted, 128 - fadeoffice, 128 - fadeoffice, 128 - fadeoffice);   
                } else {
                    if (fadeoffice > 0) {fadeoffice--;}

                    setRGB0(polyhelpwanted, 128 - fadeoffice, 128 - fadeoffice, 128 - fadeoffice);   
                }
                if (loadingframe > 360) {
                    menu = 1;
                    helpwantedposter = 0;
                }
            }
            if (menuscreeninit == 0) {
                loadFile = "\\FREDDY.TIM;1";
                CdSearchFile( &filePos, loadFile);
                dataBuffer = malloc( BtoS(filePos.size) * CD_SECTOR_SIZE );
                CdControl(CdlSetloc, (u_char *)&filePos.pos, CtrlResult);
                // Read data and load it to dataBuffer
                CDreadOK = CdRead( (int)BtoS(filePos.size), (u_long *)dataBuffer, CdlModeSpeed );
                CDreadResult = CdReadSync(0, 0);
                LoadTexture(dataBuffer, &freddy); 
                free(dataBuffer);
                loadFile = "\\FREDDY2.TIM;1";
                CdSearchFile( &filePos, loadFile);
                dataBuffer = malloc( BtoS(filePos.size) * CD_SECTOR_SIZE );
                CdControl(CdlSetloc, (u_char *)&filePos.pos, CtrlResult);
                // Read data and load it to dataBuffer
                CDreadOK = CdRead( (int)BtoS(filePos.size), (u_long *)dataBuffer, CdlModeSpeed );
                CDreadResult = CdReadSync(0, 0);
                LoadTexture(dataBuffer, &freddy2); 
                free(dataBuffer);
                loadFile = "\\GJFIV.TIM;1";
                CdSearchFile( &filePos, loadFile);
                dataBuffer = malloc( BtoS(filePos.size) * CD_SECTOR_SIZE );
                CdControl(CdlSetloc, (u_char *)&filePos.pos, CtrlResult);
                // Read data and load it to dataBuffer
                CDreadOK = CdRead( (int)BtoS(filePos.size), (u_long *)dataBuffer, CdlModeSpeed );
                CDreadResult = CdReadSync(0, 0);
                LoadTexture(dataBuffer, &goodjob); 
                free(dataBuffer);
                if (initstuff == 0) {
                    loadFile = "\\HWANTED.TIM;1";
                    CdSearchFile( &filePos, loadFile);
                    dataBuffer = malloc( BtoS(filePos.size) * CD_SECTOR_SIZE );
                    CdControl(CdlSetloc, (u_char *)&filePos.pos, CtrlResult);
                    // Read data and load it to dataBuffer
                    CDreadOK = CdRead( (int)BtoS(filePos.size), (u_long *)dataBuffer, CdlModeSpeed );
                    CDreadResult = CdReadSync(0, 0);
                    LoadTexture(dataBuffer, &helpwanted); 
                    free(dataBuffer);
                    initstuff++;
                }
                CdControlF(CdlPause,0);
                          
                // Load XA file from cd
                // Find XA file pos
                CdSearchFile( &XAPos, loadXA);
                // Set cd head to start of file
                soundBank.offset = CdPosToInt(&XAPos.pos);
                // Set cd XA playback parameters and pause cd
                XAsetup();
                // Keep track of XA Sample currently playing

                menuscreeninit = 1;
                musicframes = 3778;
            }
            if (menuscreeninit == 1) {

                seedtitle++;
                if (nofreddy == 0) {
                    //TIM freddy
                    makepoly(1);
                } 
            }
        }//Menu Screen
        if (menu == 1) { //Loading/Starting night screen
            loadingframe++;
            if (loadingframe < 360) {loadingframe = 360;}
            if (loadingframe < 560 && loadingframe > 360) {printNightInfo();} else {makepoly(13);}
            if (loadingframe == 362) {

                starting();
                fadeoffice = 128;
                //SaveGame();

            }
            if (loadingframe == 500) {
                Ran(10000);
                if (freddydifficulty == 1 && bonniedifficulty == 9 && chicadifficulty == 8 && foxydifficulty == 7 || RAN == 1) {
                    goldenfreddied = 1;
                    fadeoffice = 0;
                } else {
                    if (night == 6) {
                        LoadTexture(_binary_tim_GJSIX_tim_start, &goodjob); 
                    }
                    if (night == 7) {
                        LoadTexture(_binary_tim_GJSEV_tim_start, &goodjob); 
                    }
                }
            }
            if (loadingframe == 560) {
                if (goldenfreddied == 0 && initstuff == 1) {
                    LoadTexture(_binary_tim_office_officeLEFT_tim_start, &officeLEFT);//Loading rest of the things
                    LoadTexture(_binary_tim_office_officeRIGHT_tim_start, &officeRIGHT);
                    LoadTexture(_binary_tim_FAM_tim_start, &fiveam); 
                    LoadTexture(_binary_tim_AM_tim_start, &fiveam); 
                    LoadTexture(_binary_tim_office_mutecall_tim_start, &mutecall);

                    LoadTexture(_binary_tim_office_fan_1_tim_start, &fan);
                }
                usage = defaultusage;
            }
            if (loadingframe == 562) {
                if (initstuff == 1) {
                    loadFile = "\\OMID.TIM;1";
                    CdSearchFile( &filePos, loadFile);
                    dataBuffer = malloc( BtoS(filePos.size) * CD_SECTOR_SIZE );
                    CdControl(CdlSetloc, (u_char *)&filePos.pos, CtrlResult);
                    // Read data and load it to dataBuffer
                    CDreadOK = CdRead( (int)BtoS(filePos.size), (u_long *)dataBuffer, CdlModeSpeed );
                    CDreadResult = CdReadSync(0, 0);
                    LoadTexture(dataBuffer, &officeMIDDLE); 
                    free(dataBuffer);
                    loadFile = "\\OMIDNO.TIM;1";
                    CdSearchFile( &filePos, loadFile);
                    dataBuffer = malloc( BtoS(filePos.size) * CD_SECTOR_SIZE );
                    CdControl(CdlSetloc, (u_char *)&filePos.pos, CtrlResult);
                    // Read data and load it to dataBuffer
                    CDreadOK = CdRead( (int)BtoS(filePos.size), (u_long *)dataBuffer, CdlModeSpeed );
                    CDreadResult = CdReadSync(0, 0);
                    LoadTexture(dataBuffer, &officeMIDDLEnolight); 
                    free(dataBuffer);
                    loadFile = "\\GAMEOVER.TIM;1";
                    CdSearchFile( &filePos, loadFile);
                    dataBuffer = malloc( BtoS(filePos.size) * CD_SECTOR_SIZE );
                    CdControl(CdlSetloc, (u_char *)&filePos.pos, CtrlResult);
                    // Read data and load it to dataBuffer
                    CDreadOK = CdRead( (int)BtoS(filePos.size), (u_long *)dataBuffer, CdlModeSpeed );
                    CDreadResult = CdReadSync(0, 0);
                    LoadTexture(dataBuffer, &gameover); 
                    free(dataBuffer);
                    loadFile = "\\GOL.TIM;1";
                    CdSearchFile( &filePos, loadFile);
                    dataBuffer = malloc( BtoS(filePos.size) * CD_SECTOR_SIZE );
                    CdControl(CdlSetloc, (u_char *)&filePos.pos, CtrlResult);
                    // Read data and load it to dataBuffer
                    CDreadOK = CdRead( (int)BtoS(filePos.size), (u_long *)dataBuffer, CdlModeSpeed );
                    CDreadResult = CdReadSync(0, 0);
                    LoadTexture(dataBuffer, &officegoldenfreddy); 
                    free(dataBuffer);
                    loadFile = "\\LAYOUT.TIM;1";
                    CdSearchFile( &filePos, loadFile);
                    dataBuffer = malloc( BtoS(filePos.size) * CD_SECTOR_SIZE );
                    CdControl(CdlSetloc, (u_char *)&filePos.pos, CtrlResult);
                    // Read data and load it to dataBuffer
                    CDreadOK = CdRead( (int)BtoS(filePos.size), (u_long *)dataBuffer, CdlModeSpeed );
                    CDreadResult = CdReadSync(0, 0);
                    LoadTexture(dataBuffer, &layout); 
                    free(dataBuffer);
                    loadFile = "\\DOORS.TIM;1";
                    CdSearchFile( &filePos, loadFile);
                    dataBuffer = malloc( BtoS(filePos.size) * CD_SECTOR_SIZE );
                    CdControl(CdlSetloc, (u_char *)&filePos.pos, CtrlResult);
                    // Read data and load it to dataBuffer
                    CDreadOK = CdRead( (int)BtoS(filePos.size), (u_long *)dataBuffer, CdlModeSpeed );
                    CDreadResult = CdReadSync(0, 0);
                    LoadTexture(dataBuffer, &doors); 
                    free(dataBuffer);
                    loadFile = "\\STATIC.TIM;1";
                    CdSearchFile( &filePos, loadFile);
                    dataBuffer = malloc( BtoS(filePos.size) * CD_SECTOR_SIZE );
                    CdControl(CdlSetloc, (u_char *)&filePos.pos, CtrlResult);
                    // Read data and load it to dataBuffer
                    CDreadOK = CdRead( (int)BtoS(filePos.size), (u_long *)dataBuffer, CdlModeSpeed );
                    CDreadResult = CdReadSync(0, 0);
                    LoadTexture(dataBuffer, &statics); 
                    free(dataBuffer);
                    loadFile = "\\FRSNEAK.TIM;1";
                    CdSearchFile( &filePos, loadFile);
                    dataBuffer = malloc( BtoS(filePos.size) * CD_SECTOR_SIZE );
                    CdControl(CdlSetloc, (u_char *)&filePos.pos, CtrlResult);
                    // Read data and load it to dataBuffer
                    CDreadOK = CdRead( (int)BtoS(filePos.size), (u_long *)dataBuffer, CdlModeSpeed );
                    CDreadResult = CdReadSync(0, 0);
                    LoadTexture(dataBuffer, &freddysneak); 
                    free(dataBuffer);

                    CdControlF(CdlPause,0);
                    CdSearchFile( &XAPos, loadXA);
                    soundBank.offset = CdPosToInt(&XAPos.pos);
                    XAsetup();
                    initstuff++;
                }
            }
           if (loadingframe > 630) {
                if (initstuff == 2) {
                    initstuff++;
                }
           }
            if (loadingframe > 660) {
                menu = 2;
                if (goldenfreddied == 0) {
                    SpuSetKey(SPU_ON, SPU_03CH);
                }
                loadingframe = 0;
            }
        }//Loading/Starting night screen
        if (menu == 2) { //Gameplay Screen
            if (goldenfreddied == 0) {
                if (nightwon == 0) {
                    print(printnumber);
                    chargeNtimeFunc();   
                }
            } else {goldenfreddiedframes++;}

            if (goldenfreddiedframes > 90) {
                LoadTexture(_binary_tim_itsme_tim_start, &itsme);
                if (fadeoffice != 128) {fadeoffice++;}
            }
            if (goldenfreddiedframes == 280) {
                enablephoneguy = 0;
                sample = 2;
                fivesecondframe = 12900000; //Circus CURSED 
                filter.chan = soundBank.samples[sample].channel;
                filter.file = soundBank.samples[sample].file;
                CdControlF(CdlSetfilter, (u_char *)&filter);
                soundBank.samples[sample].cursor = 0;
            }
            if (goldenfreddiedframes == 360) {
                LoadTexture(_binary_tim_office_officeLEFT_tim_start, &officeLEFT);
                LoadTexture(_binary_tim_office_officeRIGHT_tim_start, &officeRIGHT);
                LoadTexture(_binary_tim_office_officeMIDDLE_tim_start, &officeMIDDLE);
                LoadTexture(_binary_tim_FAM_tim_start, &fiveam); 
                LoadTexture(_binary_tim_AM_tim_start, &fiveam); 
                SpuSetKey(SPU_ON, SPU_10CH);
            }
            if (goldenfreddiedframes > 370 && goldenfreddiedframes < 1560) {
                goldenfreddypixelGarbagething += 2;
                FntPrint("%s %s %s %s\n",goldenfreddypixelGarbagething,goldenfreddypixelGarbagething,goldenfreddypixelGarbagething,goldenfreddypixelGarbagething);
                FntPrint("%s %s %s %s\n",goldenfreddypixelGarbagething,goldenfreddypixelGarbagething,goldenfreddypixelGarbagething,goldenfreddypixelGarbagething);
                FntPrint("%s %s %s %s\n",goldenfreddypixelGarbagething,goldenfreddypixelGarbagething,goldenfreddypixelGarbagething,goldenfreddypixelGarbagething);
                FntPrint("%s %s %s %s\n",goldenfreddypixelGarbagething,goldenfreddypixelGarbagething,goldenfreddypixelGarbagething,goldenfreddypixelGarbagething);
                FntPrint("%s %s %s %s\n",goldenfreddypixelGarbagething,goldenfreddypixelGarbagething,goldenfreddypixelGarbagething,goldenfreddypixelGarbagething);
                FntPrint("%s %s %s %s\n",goldenfreddypixelGarbagething,goldenfreddypixelGarbagething,goldenfreddypixelGarbagething,goldenfreddypixelGarbagething);
                if (goldenfreddiedframes % 64 == 0) {
                    SpuSetKey(SPU_ON, SPU_10CH);
                    SpuSetKey(SPU_ON, SPU_09CH);
                }
            } else {
                if (SpuGetKeyStatus(SPU_10CH) == SPU_ON) {SpuSetKey(SPU_OFF, SPU_10CH);}
                if (SpuGetKeyStatus(SPU_09CH) == SPU_ON) {SpuSetKey(SPU_OFF, SPU_09CH);}
            }
            if (goldenfreddiedframes > 1560) {
                Corrupt();
            }

            if (dead == 1) {
                if (screamersetsound == 0) {
                    sample = 7;
                    filter.chan = soundBank.samples[sample].channel;
                    filter.file = soundBank.samples[sample].file;
                    CdControlF(CdlSetfilter, (u_char *)&filter);
                    soundBank.samples[sample].cursor = 0;
                    screamersetsound++;
                }
                screamer();
            } else {
                if (goldenfreddied == 0) {
                    if (AM != 6) {
                        animatronicFunc(0);
                        controllerinput();
                    }
                }
            }
            if (activatedmenudebug == 1 && pad & PADR1 && pad & PADRup && pad & PADRright && pad & PADL2) {
                AM = 5;
                FrameCounter = FrameCounterlimit - 80;
            }

            if (light1 && charge > 0) {
                Ran(100);
                if (RAN <= 20) {
                    LoadTexture(_binary_tim_office_officeLEFT_tim_start, &officeLEFT);
                    SpuSetKey(SPU_OFF, SPU_01CH);
                } else {
                    if (SpuGetKeyStatus(SPU_01CH) == SPU_OFF) {SpuSetKey(SPU_ON, SPU_01CH);}
                    if (!(bonnieDoor)) {LoadTexture(_binary_tim_office_officeLEFTlight_tim_start, &officeLEFTlight);} else {LoadTexture(_binary_tim_office_officeLEFTlightbonnie_tim_start, &officeLEFTlight);}
                }
            }
            if (light2 && charge > 0) {
                Ran(100);
                if (RAN <= 20) {
                    LoadTexture(_binary_tim_office_officeRIGHT_tim_start, &officeRIGHT);
                    SpuSetKey(SPU_OFF, SPU_01CH);
                } else {
                    if (SpuGetKeyStatus(SPU_01CH) == SPU_OFF) {SpuSetKey(SPU_ON, SPU_01CH);}
                    if (!(chicaDoor)) {LoadTexture(_binary_tim_office_officeRIGHTlight_tim_start, &officeLEFTlight);} else {LoadTexture(_binary_tim_office_officeRIGHTlightchica_tim_start, &officeLEFTlight);}
                }
            }

            if (fivesecondframe == 0) {
                if (charge > 0 && puppetmusic == 0) {
                    if (phoneguytalking == 0) {
                        Ran(15);
                        if (ambiancechance > RAN) {
                            ambiancechance = 1;

                            switch(ambiancenum) {
                                case 1:
                                    sample = 1;
                                    fivesecondframe = 3402; //Ambiance 1
                                break;
                                case 2:
                                    sample = 6;
                                    fivesecondframe = 3912; //Ambiance 2
                                break;
                                case 3:
                                    sample = 8;
                                    fivesecondframe = 3250; //Ambiance 3
                                break;
                                case 4:
                                    if (foxylocation < 2) {
                                        sample = 18;
                                        fivesecondframe = 510; //Foxy 

                                    } else {
                                        ambiancenum = Ran(5);
                                    }
                                break;
                                case 5:
                                    sample = 5;
                                    fivesecondframe = 1290; //Circus 
                                break;
                                case 6:
                                    sample = 20;
                                    fivesecondframe = 4440; //Mixed ambiance 1
                                break;
                                case 7:
                                    sample = 21;
                                    fivesecondframe = 4200; //Mixed ambiance 2
                                break;
                                case 8:
                                    sample = 22;
                                    fivesecondframe = 4920; //Mixed ambiance 2
                                break;
                            }
                            filter.chan = soundBank.samples[sample].channel;
                            filter.file = soundBank.samples[sample].file;
                            CdControlF(CdlSetfilter, (u_char *)&filter);
                            soundBank.samples[sample].cursor = 0;
                        } else {
                            ambiancesound = 0;
                            fivesecondframe = 300;
                            ambiancechance += 2;
                            ambiancenum++;
                            if (ambiancenum > 8) {ambiancenum = 1;}
                        }   
                    }
                } 
            }

            if (fivesecondframe > 0) {fivesecondframe--;}

            if (foxysknock == 1) {
                foxyknockframe++;
                if (foxyknockframe == 1) {SpuSetKey(SPU_ON, SPU_09CH);}
                if (foxyknockframe == 41) {SpuSetKey(SPU_ON, SPU_09CH);}
                if (foxyknockframe == 81) {SpuSetKey(SPU_ON, SPU_09CH);}
                if (foxyknockframe == 121) {
                    SpuSetKey(SPU_ON, SPU_09CH);
                    foxysknock--;
                    foxyknockframe = 0;
                }
            }
            if (noisefootstep == 1) {
                framenoisefootstep++;
                int noise;
                if (framenoisefootstep == 1) {
                    if (noisefootstepanimatronic == 1) { //Bonnie
                        noise = noise + bonnielocation * 300;
                    }
                    if (noisefootstepanimatronic == 2) { //Chica
                        noise = noise + chicalocation * 300; // chicalocation == 1 -> +300, == 7 -> +1400
                    }
                    if (noisefootstepanimatronic == 3) { //Freddy (when in office)
                        noise = noise + 8000;
                    }
                    SpuSetVoiceVolume(8, noise, noise);
                    SpuSetKey(SPU_ON, SPU_08CH);
                }
                if (framenoisefootstep == 60) {
                    SpuSetVoiceVolume(8, noise - 600, noise - 600); //For making it quieter
                    SpuSetKey(SPU_ON, SPU_08CH);
                    noisefootstep--;
                    framenoisefootstep = 0;
                    noise = 0;
                }
            }

            if (noisefootstepF == 1) {
                int noisef;
                noisef = 0x800;
                noisef = noisef + freddylocation * 1500;
                SpuSetVoiceVolume(13, noisef, noisef);
                SpuSetKey(SPU_ON, SPU_13CH);
                noisefootstepF--;
                noisef = 0;
            }
            if (jamlight == 1) {
                jamlightframes++;
                if (jamlightframes == 1) {SpuSetKey(SPU_ON, SPU_12CH);}
                if (jamlightframes == 5) {
                    SpuSetKey(SPU_ON, SPU_12CH);
                    jamlight--;
                    jamlightframes = 0;
                }
            }

            if (dead == 0 && nightwon == 0) {

                if (MovVectorofficemiddle.vx > 10) {
                    if (door == 1) {door = 0;}
                }
                if (MovVectorofficemiddle.vx < -10) {
                    if (door == 0) {door = 1;}
                }

                if (doorclosedL == 1 && MovVectorleftdoor.vy < -61) {
                    leftdoorgoodbye++;
                    MovVectorleftdoor.vy = MovVectorleftdoor.vy + leftdoorgoodbye;
                } else {leftdoorgoodbye = 1;}
                if (doorclosedL == 0 && MovVectorleftdoor.vy > -190) {
                    leftdoorgoodbye2--;
                    MovVectorleftdoor.vy = MovVectorleftdoor.vy + leftdoorgoodbye2;
                } else {leftdoorgoodbye2 = -1;}

                if (doorclosedR == 1 && MovVectorrightdoor.vy < -61) {
                    rightdoorgoodbye++;
                    MovVectorrightdoor.vy = MovVectorrightdoor.vy + rightdoorgoodbye;
                } else {rightdoorgoodbye = 1;}
                if (doorclosedR == 0 && MovVectorrightdoor.vy > -190) {
                    rightdoorgoodbye2--;
                    MovVectorrightdoor.vy = MovVectorrightdoor.vy + rightdoorgoodbye2;
                } else {rightdoorgoodbye2 = -1;}

                if (pad & PADRup || pad >> 16 & PADRup) {speedoffice = 6;} else {speedoffice = 3;}

                if(pad & PADLleft || pad >> 16 & PADLleft && twoplayermode == 1) {
                    if (MovVectorofficemiddle.vx < 80) {
                        MovVectorofficemiddle.vx = MovVectorofficemiddle.vx + speedoffice;
                        MovVectorfreddylightsout.vx = MovVectorfreddylightsout.vx + speedoffice;
                        MovVectorleftdoor.vx = MovVectorleftdoor.vx + speedoffice;
                        MovVectorrightdoor.vx = MovVectorrightdoor.vx + speedoffice;
                        MovVectorofficegolden.vx = MovVectorofficegolden.vx + speedoffice;
                    }
                } // left ;)
                if(pad & PADLright || pad >> 16 & PADLright && twoplayermode == 1) {
                    if (MovVectorofficemiddle.vx > -115) {
                        MovVectorofficemiddle.vx = MovVectorofficemiddle.vx - speedoffice;
                        MovVectorfreddylightsout.vx = MovVectorfreddylightsout.vx - speedoffice;
                        MovVectorleftdoor.vx = MovVectorleftdoor.vx - speedoffice;
                        MovVectorrightdoor.vx = MovVectorrightdoor.vx - speedoffice;
                        MovVectorofficegolden.vx = MovVectorofficegolden.vx - speedoffice;
                    }
                } // right :) 
            }
            if (AM == 12 && FrameCounter == 1) { //Init Gameplay
                CdControlF(CdlPause,0);
                //Check if a stupidass mf put charge at 0%
                //me
                if (charge == 0) {
                    sample = 4;
                    filter.chan = soundBank.samples[sample].channel;
                    filter.file = soundBank.samples[sample].file;
                    CdControlF(CdlSetfilter, (u_char *)&filter);

                    soundBank.samples[sample].cursor = 0;

                    usage = 0;
                    lightsout();
                }
                if ((freddydifficulty == 20 && bonniedifficulty == 0 && chicadifficulty == 0 && foxydifficulty == 0) && hellnight == 0) {
                    phoneguytalking = 2880;
                    phoneguytalkingconst = 2880;
                    sample = 15; //Why do you tryna rizz freddy ??
                    filter.chan = soundBank.samples[sample].channel;
                    filter.file = soundBank.samples[sample].file;
                    CdControlF(CdlSetfilter, (u_char *)&filter);
                    soundBank.samples[sample].cursor = 0;
                    enablephoneguy = 0;
                }
            }
            if (enablephoneguy == 1 && charge > 0 && goldenfreddied == 0) {
                if (night == 1) {
                    phoneguytalking = 12060;
                    phoneguytalkingconst = 12060;
                    sample = 9;
                }
                if (night == 2) {
                    phoneguytalking = 5880;
                    phoneguytalkingconst = 5880;
                    sample = 10;
                }
                if (night == 3) {
                    phoneguytalking = 4080;
                    phoneguytalkingconst = 4080;
                    sample = 11;
                }
                if (night == 4) {
                    phoneguytalking = 3540;
                    phoneguytalkingconst = 3540;
                    sample = 12;
                }
                if (night == 5) {
                    phoneguytalking = 2160;
                    phoneguytalkingconst = 2160;
                    sample = 13;
                }
                if (night != 6) {
                    filter.chan = soundBank.samples[sample].channel;
                    filter.file = soundBank.samples[sample].file;
                    CdControlF(CdlSetfilter, (u_char *)&filter);
                    soundBank.samples[sample].cursor = 0;
                }
                enablephoneguy = 0;
            }
            if (phoneguytalking > 0) {phoneguytalking--;}

            if (hellnight == 1) {
                if (FrameCounter == 10 || FrameCounter == 3600 || FrameCounter == 7200 || FrameCounter == 10800 || FrameCounter == 14400) {
                    phoneguytalking = 2160;
                    sample = 13;
                    filter.chan = soundBank.samples[sample].channel;
                    filter.file = soundBank.samples[sample].file;
                    CdControlF(CdlSetfilter, (u_char *)&filter);
                    soundBank.samples[sample].cursor = 0;  

                    //This is for indicating the hour, since that single hour is 6 hours IG
                }
            }

            if (goldenfreddyframes == 0 && camera == 1) { 
                goldenfreddychances = 1000;
                if (itsmepiratecove == 1) {goldenfreddychances = goldenfreddychances / 2;}
                if (itsmeehallcorner == 1) {goldenfreddychances = goldenfreddychances / 2;}
                if (itsmeehall == 1) {goldenfreddychances = goldenfreddychances / 2;}
                if (bonnieliljumpscare == 1) {goldenfreddychances = goldenfreddychances / 2;}
                if (freddyliljumpscare == 1) {goldenfreddychances = goldenfreddychances / 2;}
                
                Ran(goldenfreddychances);
                if (RAN == 1) {
                    MovVectorgoldenf.vx = 0;
                    MovVectorgoldenf.vy = 30;
                    goldenfreddyactivated = 1;
                }
                goldenfreddyframes = 60;
            } 
            if (goldenfreddyframes > 0){
                goldenfreddyframes--;
                if (camera == 0) {
                    goldenfreddyframes = 0;
                }
            } else {
                MovVectorgoldenf.vx = 999;
                MovVectorgoldenf.vy = 999;
            }

            if (curcam[0] == '5') {
                Ran(1000);
                if (RAN == 1 && sparkyframes == 0) {
                    sparkylocation = 1;
                } else {sparkylocation = 0;}
                sparkyframes = 60;
            }

            if (sparkyframes > 0) {
                sparkyframes--;
                if (camera == 0 || curcam[0] != '5') {
                    sparkyframes = 0;
                }
            } else {
                sparkylocation = 0;
            }
            if (camera == 1) { //Cam things

                cameraloc();

                if (curcam[0] == '6' && curcam[1] == ' ') {
                    if (puppetmusic == 0) {
                        Ran(500);
                        if (RAN == 1) {
                            if (camera == 1 && phoneguytalking == 0 && ambiancesound == 0) {
                                // Set sample ID for playback
                                sample = 17;
                                // Change file/channel in the filter struct
                                filter.chan = soundBank.samples[sample].channel;
                                filter.file = soundBank.samples[sample].file;
                                // Set filter
                                CdControlF(CdlSetfilter, (u_char *)&filter);
                
                                soundBank.samples[sample].cursor = 0;
                            }
                        }
                        puppetmusic = 960;
                    }                        
                }
            }
            if (camera == 0) {
                itsmeehallcorner = 0;
                itsmeehallcornercooldown = 0;
                itsmeehall = 0;
                itsmeehallcooldown = 0;
                itsmepiratecove = 0;
                itsmepiratecovecooldown = 0;
                bonnieliljumpscarecooldown = 0;
                bonnieliljumpscare = 0;
                freddyliljumpscare = 0;
                freddyliljumpscarecooldown = 0;

                if (goldenfreddyactivated == 1) {
                    nolongerincam = 1;
                    Ran(goldenfreddychancescrash);
                    if (RAN == 1) {
                        SpuSetKey(SPU_OFF, SPU_ALLCH);
                        SpuSetKey(SPU_ON, SPU_10CH);
                        SpuSetKey(SPU_ON, SPU_9CH);

                        loadFile = "\\E.DAT;1";
                        CdSearchFile( &filePos, loadFile);
                        dataBuffer = malloc( BtoS(filePos.size) * CD_SECTOR_SIZE );
                        CdControl(CdlSetloc, (u_char *)&filePos.pos, CtrlResult);
                        CDreadOK = CdRead( (int)BtoS(filePos.size), (u_long *)dataBuffer, CdlModeSpeed );
                        CDreadResult = CdReadSync(0, 0);
                        LoadTexture(dataBuffer, &officegoldenfreddy); //Crash time :'3
                        goldenfreddychancescrash = 1;

                    } else {goldenfreddychancescrash--;} //Each frame, it will do a rand.
                }
            }
            if (cooldowncamera > 0) {cooldowncamera--;}

            if (phoneguytalkingconst - 1620 < phoneguytalking && mutedcall == 0 && AM != 6) {
              polymutecall = (POLY_FT4 *)nextpri;                 
                      
              RotMatrix(&RotVectormutecall, &PolyMatrixmutecall);    
              TransMatrix(&PolyMatrixmutecall, &MovVectormutecall);  
              ScaleMatrix(&PolyMatrixmutecall, &ScaleVectormutecall);
              
              SetRotMatrix(&PolyMatrixmutecall);                  
              SetTransMatrix(&PolyMatrixmutecall);                
              
              setClut(polymutecall, 960, 200);
  
                    setRGB0(polymutecall, 128, 128, 128); 

              setPolyFT4(polymutecall);                           
              
              polymutecall->tpage = getTPage(mutecall.mode&0x3, 0, 832, 256); 
              
              
              RotTransPers4(
                          &VertPosmutecall[0],      &VertPosmutecall[1],      &VertPosmutecall[2],      &VertPosmutecall[3],
                          (long*)&polymutecall->x0, (long*)&polymutecall->x1, (long*)&polymutecall->x2, (long*)&polymutecall->x3,
                          &polydepth,
                          &polyflag
                          );                               
              
              setUV4(polymutecall, 120, 0, 120, 33, 254, 0, 254, 33);
                  
              addPrim(ot[db], polymutecall);                       
              
              nextpri += sizeof(POLY_FT4);    

              if (pad & PADselect || pad >> 16 & PADselect) {
                mutedcall = 1;
                CdControlF(CdlPause,0);
                phoneguytalking = 0;
              }
            }
            if (camera == 1 && goldenfreddyactivated == 1 && nolongerincam == 1) {
                goldenfreddyactivated = 0;
                goldenfreddychancescrash = 2000;
                nolongerincam = 0;
            }

            if (surusage > 0) {
                usage = usage + surusage;
            }
            
            if (puppetmusic >= 1) {
                if (camera == 0 || curcam[0] != '6') {
                    if (sample == 16) {
                        CdControlF(CdlPause,0);
                        puppetmusic = 0; 
                        sample = 0;
                   }
                }
                puppetmusic--;
            }

            if (freddyanticipation == 1) { //He's ready to move 
                if (curcam[0] != '4' || curcam[1] != 'B') {
                    freddylocation++;
                    freddyanticipation = 0;
                    noisefootstepF = 1;
                }
            }

            if (charge > 0 || AM < 6) {usage = usage + camera + light1 + light2 + doorclosedR + doorclosedL;}

            if (charge < 1 && usage > 0) {
                defaultusage = 0;
                sample = 4;
                filter.chan = soundBank.samples[sample].channel;
                filter.file = soundBank.samples[sample].file;
                CdControlF(CdlSetfilter, (u_char *)&filter);

                soundBank.samples[sample].cursor = 0;
                lightsout();
            }
            if (AM == 6 && FrameCounter == 0) {
                sample = 3;
                filter.chan = soundBank.samples[sample].channel;
                filter.file = soundBank.samples[sample].file;
                CdControlF(CdlSetfilter, (u_char *)&filter);
                soundBank.samples[sample].cursor = 0;
                nightwon = 1;
            }

            if (fivetosixamframes < 820 && AM == 6) {

                if (SpuGetKeyStatus(SPU_03CH) == SPU_ON) {SpuSetKey(SPU_OFF, SPU_03CH);}

                if (fivetosixamframes == 1) {
                    if (night != 7) {Ran(250);}
                    else {Ran(50);} //For more fun 
                    if (RAN == 1) {
                        customnextnightactivation = 1;
                    }
                    gamevictory();
                }
                  if (fadeoffice > 0) {
                    fadeoffice--;

                    if (camera == 0) { 
                      setRGB0(polyofficeright, fadeoffice, fadeoffice, fadeoffice); 
                      setRGB0(polyofficemiddle, fadeoffice, fadeoffice, fadeoffice);  
                      setRGB0(polyfan, fadeoffice, fadeoffice, fadeoffice);                
                      setRGB0(polyofficeleft, fadeoffice, fadeoffice, fadeoffice);        
                    }

                    setRGB0(polyfiveam, 128 - fadeoffice, 128 - fadeoffice, 128 - fadeoffice);    
                    setRGB0(polyam, 128 - fadeoffice, 128 - fadeoffice, 128 - fadeoffice);    
                  } else {
                    setRGB0(polyfiveam, 128, 128, 128);   
                    setRGB0(polyam, 128, 128, 128);   
                    if (camera == 0) { 
                      setRGB0(polyofficeright, 0, 0, 0); 
                      setRGB0(polyofficemiddle, 0, 0, 0);               
                      setRGB0(polyofficeleft, 0, 0, 0); 
                      setRGB0(polyfan, 0, 0, 0);           
                    }

                    if (camera == 1) {
                      CameraFunc();
                    }
                }
                fivetosixamframes++;

                if (fivetosixamframes == 120) {LoadTexture(_binary_tim_rect_tim_start, &rect);}

                makepoly(10);
                if (fivetosixamframes < 240 && fivetosixamframes > 120) {
                    if (fivetosixamframes %4 == 0) {
                        MovVectorfiveam.vy--;
                    }
                }
                if (fivetosixamframes == 240) {LoadTexture(_binary_tim_SAM_tim_start, &sixam); MovVectorfiveam.vy = 25;}
                if (fivetosixamframes > 240 && fivetosixamframes < 400) {
                    if (fivetosixamframes %7 == 0) {
                        MovVectorfiveam.vy--;
                    }
                }
                if (fivetosixamframes == 400){
                    MovVectorfiveam.vy--;
                }
            }

            if (fivetosixamframes > 819) {
                if (night == 5 || night == 6 || night == 7) {
                    nextnightframes++;
                    if (nextnightframes == 1) {
                        if (customnextnightactivation == 0) {
                            sample = 14; //Sample is for the music playing, 14 normal, 19 funky
                        }
                        else {
                            sample = 19;
                            rgbred = 135;
                            rgbgreen = 79;
                            rgbblue = 79;
                        }
                        filter.chan = soundBank.samples[sample].channel;
                        filter.file = soundBank.samples[sample].file;
                        CdControlF(CdlSetfilter, (u_char *)&filter);

                        soundBank.samples[sample].cursor = 0;
                    }
                    makepoly(11);

                    if (night == 7) {
                        if (hellnight == 1) {
                            FntPrint(" Whoa, I wouldn't know you'd do that !\n   That single hour was wild, huh ?\n    Anyways, Thanks for playing\n    this port that I loved making!\n If you have questions in regards of the       port, you can contact me !\n       See you on the flip side !");
                        }           
                        if (impossiblenight == 1) {
                            FntPrint("  ...What ? How ? You wasn't supposed\n   To win this, it was impossible...?\n    Well, I dunno what to say..\n    Good job I guess ? And stop it\n Like Right now, stop the console or the       emulator because there's\n       Nothing left to see or do...");
                        }         
                    }

                    if (pad & PADstart && night != 7 || nextnightframes == 3700 && night != 7 && customnextnightactivation == 0|| nextnightframes == 6040 && night != 7 && customnextnightactivation == 1) {
                        if (night != 6) {
                            night++;
                        }
                        if (customcharge == 99 && customAM == 5 && night == 6) {
                            night++;
                            hellnight = 1;
                            convertion = 300;
                            activatedmenudebug = 0;
                            enablephoneguy = 1;
                            enablephoneguystr[1] = 'N';
                            cheating = 0;
                            fastnights = 0;
                            //printnumber = 3;
                        } 
                        fivetosixamframes = 0;
                        nextnightframes = 0;
                        weirdnight = 0;
                        resetgame(0);
                        menu = 1;
                    } 
                    
                    if (night == 7 && nextnightframes > 4100 && impossiblenight == 1) {CdControlF(CdlPause, 0);} //Just for not having the rrrinngg thing
                    if (night == 7 && nextnightframes > 8100 && impossiblenight == 1) {
                        FntPrint("\n           ...Unless ?");
                        if (pad & PADstart) {
                            freddydifficulty = 1;
                            bonniedifficulty = 9;
                            chicadifficulty = 8;
                            foxydifficulty = 7;
                            menu = 1;
                        }
                    } //...Unless ?

                    if (night == 7 && nextnightframes > 4600) {
                        if (hellnight == 1) {
                            FntPrint("\n           Ready for round 2 ?");
                            if (pad & PADstart) {
                                cheating = 0;
                                fastnights = 0;
                                printnumber = 3;
                                fivetosixamframes = 0;
                                nextnightframes = 0;
                                weirdnight = 0;
                                hellnight = 0;
                                activatedmenudebug = 0;
                                impossiblenight = 1;
                                resetgame(0);
                                menu = 1;
                            }
                        }
                    }  
                } else {
                    night++;
                    fivetosixamframes = 0;
                    nextnightframes = 0;
                    weirdnight = 0;
                    resetgame(0);
                    menu = 1; //Load into next night
                }
            }

            if (returnframes == 60 || returnframes == 120 || returnframes == 180) {
                returnbasevolume  = returnbasevolume + 2000;
                SpuSetVoiceVolume(4, returnbasevolume, returnbasevolume);
                SpuSetKey(SPU_ON, SPU_04CH);
            }
            if (returnframes == 210) {
                isingame = 1;
                SpuSetKey(SPU_OFF, SPU_ALLCH);
                returnbasevolume = 0x1800;
                SpuSetVoiceVolume(4, returnbasevolume, returnbasevolume);
                menuselection = 3;
                menuselectionmax = 2;
                returnframes = 0;
                menu = 0;
                nofreddy = 1;
            }
            if (returnedingame) {
                CdControlF(CdlPause,0);
                SpuSetKey(SPU_ON, SPU_03CH);
                returnedingame = 0;
            }
            if (weirdnight == 1 && AM >= 4 && AM <= 6) {

                setRGB0(polyfreddy, 0, 0, 0);          
                setRGB0(polybonnie, 0, 0, 0);          
                setRGB0(polychica, 0, 0, 0);           
                setRGB0(polyfoxy, 0, 0, 0);            
            }

            if (cantlightL == 1) {
                light1 = 0;
            }
            if (cantlightR == 1) {
                light2 = 0;
            }

            //When no power (skill issue ? Or testing purpose ?)
            if (islightsout == 1) {
                if (lightsoutinit == 0) {//Init phase 1 
                    //blablabla
                    LoadTexture(_binary_tim_office_officeLEFTnolight_tim_start, &officeLEFTnolight);//Loading office
                    LoadTexture(_binary_tim_office_officeMIDDLEnolight_tim_start, &officeMIDDLEnolight); 
                    LoadTexture(_binary_tim_office_officeRIGHTnolight_tim_start, &officeRIGHTnolight);
                    lightsoutinit++;
                }
                if (musicboxappearanceframe == 300) {
                    Ran(100); 
                    if (weirdnight == 0 && musicboxappearancechance > RAN) {
                        musicboxactivated = 1;
                        islightsout = 0;
                    } else {
                        musicboxappearanceframe = 0;
                        musicboxappearancechance = musicboxappearancechance + 20;
                        if (musicboxappearancechance == 100) {
                            if (weirdnight == 1) {
                                AM = 5;
                                FrameCounter = 35500;
                                blackoutactivated = 1;
                            }else {
                                musicboxactivated = 1;
                                islightsout = 0;
                            }
                        }
                    }
                } else {musicboxappearanceframe++;}
            }
            if (musicboxactivated == 1) {
                if (musicboxinit == 0) {//Init phase 2 
                    //blablabla
                    sample = 14;
                    filter.chan = soundBank.samples[sample].channel;
                    filter.file = soundBank.samples[sample].file;
                    CdControlF(CdlSetfilter, (u_char *)&filter);

                    soundBank.samples[sample].cursor = 0;
                    musicboxinit++;
                }
                if (blackoutappearanceframe == 300) {
                    Ran(100); 
                    if (blackoutappearancechance > RAN) {
                        blackoutactivated = 1;
                        musicboxactivated = 0;
                    } else {
                        blackoutappearanceframe = 0;
                        blackoutappearancechance = blackoutappearancechance + 20;
                        if (blackoutappearancechance == 100) {
                            blackoutactivated = 1;
                            musicboxactivated = 0;
                        }
                    }
                } else {blackoutappearanceframe++;}
                freddyglowing++;
                if (freddyglowing > 53) {freddyglowing = 0;}

                if (freddyglowing == 2 || freddyglowing == 4 || freddyglowing == 8 || freddyglowing == 12 || freddyglowing == 16 || freddyglowing == 20 || freddyglowing == 24 || freddyglowing == 30 || freddyglowing == 36 || freddyglowing == 41 || freddyglowing == 47 || freddyglowing == 51) {
                    glowvar = 64;
                }
                if (freddyglowing == 3 || freddyglowing == 9 || freddyglowing == 17 || freddyglowing == 25 || freddyglowing == 37 || freddyglowing == 48) {
                    glowvar = 0;
                }
                if (freddyglowing == 5 || freddyglowing == 13 || freddyglowing == 21 || freddyglowing == 31 || freddyglowing == 42 || freddyglowing == 52) {
                    glowvar = 128;
                }
            }
            if (blackoutactivated == 1) {
                if (blackoutinit == 0) {//Init phase 3 
                    //blablabla
                    //Deactivate all sprites
                    CdControlF(CdlPause,0);
                    glowvar = 0;
                    blackoutinit++;
                    SpuSetKey(SPU_ON, SPU_11CH);
                }
                if (blackoutscreamerappearanceframe == 120) {
                    Ran(100); 
                    if (blackoutscreamerappearancechance > RAN) {
                        if (weirdnight == 0) {
                            dead = 1;
                            deadfrom = 1;
                            screamer(); //HA you DED
                        }
                    } else {
                        blackoutscreamerappearanceframe = 0;
                        Ran(7);
                        if (RAN == 1) {
                            noisefootstep = 1;
                            noisefootstepanimatronic = 3;
                        } 
                    }
                } else {blackoutscreamerappearanceframe++;}
            }

            if (goldenfreddied == 1) { //freddy's face ? No 
                makepoly(3);
            }
            if (camera == 0) {
                if (musicboxactivated == 1) {
                    makepoly(4);
                }

                if (blackoutactivated == 0 && goldenfreddied == 0 && camera == 0) {

                    if (goldenfreddyactivated == 1) {
                        makepoly(5);
                    }
                    if (dead == 0) {
                        makepoly(6);
                        setRGB0(polyofficeright, fadeoffice, fadeoffice, fadeoffice); 
                        setRGB0(polyofficemiddle, fadeoffice, fadeoffice, fadeoffice);               
                        setRGB0(polyofficeleft, fadeoffice, fadeoffice, fadeoffice);   
                        setRGB0(polyfan, fadeoffice, fadeoffice, fadeoffice);                  
                    }
                }
            }
            if (camera == 1) {       
                //camera's grey or green
                polycamgreyogreen = (POLY_F4 *)nextpri;     
                        
                RotMatrix(&RotVectorpolycamgreyogreen, &PolyMatrixpolycamgreyogreen);    
                TransMatrix(&PolyMatrixpolycamgreyogreen, &MovVectorpolycamgreyogreen);
                ScaleMatrix(&PolyMatrixpolycamgreyogreen, &ScaleVectorpolycamgreyogreen);  
                
                SetRotMatrix(&PolyMatrixpolycamgreyogreen);            
                SetTransMatrix(&PolyMatrixpolycamgreyogreen);          
                
                setPolyF4(polycamgreyogreen);                          
                
                RotTransPers4(
                            &VertPospolycamgreyogreen[0],      &VertPospolycamgreyogreen[1],      &VertPospolycamgreyogreen[2],      &VertPospolycamgreyogreen[3],
                            (long*)&polycamgreyogreen->x0, (long*)&polycamgreyogreen->x1, (long*)&polycamgreyogreen->x2, (long*)&polycamgreyogreen->x3,
                            &polydepth,
                            &polyflag
                            );                               

                addPrim(ot[db], polycamgreyogreen);        

                setRGB0(polycamgreyogreen, 157, 184, 3);    
                
                nextpri += sizeof(POLY_F4);                

                polylayout = (POLY_FT4 *)nextpri;              
                        
                RotMatrix(&RotVectorlayout, &PolyMatrixlayout);
                TransMatrix(&PolyMatrixlayout, &MovVectorlayout);  
                ScaleMatrix(&PolyMatrixlayout, &ScaleVectorlayout);
                
                SetRotMatrix(&PolyMatrixlayout);                   
                SetTransMatrix(&PolyMatrixlayout);                 
                
                setPolyFT4(polylayout);                     

                setClut(polylayout,960,196);       
                
                polylayout->tpage = getTPage(layout.mode&0x3, 0, 640, 0); 
                
                setRGB0(polylayout, 128, 128, 128);         
                
                RotTransPers4(
                            &VertPoslayout[0],      &VertPoslayout[1],      &VertPoslayout[2],      &VertPoslayout[3],
                            (long*)&polylayout->x0, (long*)&polylayout->x1, (long*)&polylayout->x2, (long*)&polylayout->x3,
                            &polydepth,
                            &polyflag
                            );                               
                
                setUV4(polylayout, 0, 0, 0, 229, 229, 0, 229, 229);  
                    

                addPrim(ot[db], polylayout);                  
                
                nextpri += sizeof(POLY_FT4);             

                //icon for camera
                if (animatronicscamera[0] == 2) {
                    polyfreddy = (POLY_F4 *)nextpri;      

                    setRGB0(polyfreddy, 56, 34, 23);
                            
                    RotMatrix(&RotVectoreveryone, &PolyMatrixfreddy);
                    TransMatrix(&PolyMatrixfreddy, &MovVectorfreddy);  
                    ScaleMatrix(&PolyMatrixfreddy, &ScaleVectoreveryone);
                    
                    SetRotMatrix(&PolyMatrixfreddy);                   
                    SetTransMatrix(&PolyMatrixfreddy);                 
                    
                    setPolyF4(polyfreddy);                             
                    
                    RotTransPers4(
                                &VertPoseveryone[0],      &VertPoseveryone[1],      &VertPoseveryone[2],      &VertPoseveryone[3],
                                (long*)&polyfreddy->x0, (long*)&polyfreddy->x1, (long*)&polyfreddy->x2, (long*)&polyfreddy->x3,
                                &polydepth,
                                &polyflag
                                );                                 
                    addPrim(ot[db], polyfreddy);                   
                    
                    nextpri += sizeof(POLY_F4);                    
                }
                if (animatronicscamera[1] == 2) {
                    //BONNIE 
                    polybonnie = (POLY_F4 *)nextpri;        

                    setRGB0(polybonnie, 0, 21, 90); 

                    RotMatrix(&RotVectoreveryone, &PolyMatrixbonnie);
                    TransMatrix(&PolyMatrixbonnie, &MovVectorbonnie);  
                    ScaleMatrix(&PolyMatrixbonnie, &ScaleVectoreveryone);
                    
                    SetRotMatrix(&PolyMatrixbonnie);                   
                    SetTransMatrix(&PolyMatrixbonnie);                 
                    
                    setPolyF4(polybonnie);                             
                    
                    RotTransPers4(
                                &VertPoseveryone[0],      &VertPoseveryone[1],      &VertPoseveryone[2],      &VertPoseveryone[3],
                                (long*)&polybonnie->x0, (long*)&polybonnie->x1, (long*)&polybonnie->x2, (long*)&polybonnie->x3,
                                &polydepth,
                                &polyflag
                                );                                 
                    
                    addPrim(ot[db], polybonnie);                   
                    
                    nextpri += sizeof(POLY_F4);               
                }

                if (animatronicscamera[2] == 2) {     
                    //CHICA
                    polychica = (POLY_F4 *)nextpri;    

                    setRGB0(polychica, 128, 115, 41);
                            
                    RotMatrix(&RotVectoreveryone, &PolyMatrixchica);  
                    TransMatrix(&PolyMatrixchica, &MovVectorchica);
                    ScaleMatrix(&PolyMatrixchica, &ScaleVectoreveryone);
                    
                    SetRotMatrix(&PolyMatrixchica);                  
                    SetTransMatrix(&PolyMatrixchica);                
                    
                    setPolyF4(polychica);                            
                    
                    RotTransPers4(
                                &VertPoseveryone[0],      &VertPoseveryone[1],      &VertPoseveryone[2],      &VertPoseveryone[3],
                                (long*)&polychica->x0, (long*)&polychica->x1, (long*)&polychica->x2, (long*)&polychica->x3,
                                &polydepth,
                                &polyflag
                                );                                 
                    
                    addPrim(ot[db], polychica);                    
                    
                    nextpri += sizeof(POLY_F4);                    
                }

                if (animatronicscamera[3] == 2) {
                    //FOXY
                    polyfoxy = (POLY_F4 *)nextpri;

                    setRGB0(polyfoxy, 97, 20, 20);       

                    RotMatrix(&RotVectoreveryone, &PolyMatrixfoxy);    
                    TransMatrix(&PolyMatrixfoxy, &MovVectorfoxy);  
                    ScaleMatrix(&PolyMatrixfoxy, &ScaleVectoreveryone);
                    
                    SetRotMatrix(&PolyMatrixfoxy);                 
                    SetTransMatrix(&PolyMatrixfoxy);               
                    
                    setPolyF4(polyfoxy);                           
                    
                    OTz = RotTransPers4(
                                &VertPoseveryone[0],      &VertPoseveryone[1],      &VertPoseveryone[2],      &VertPoseveryone[3],
                                (long*)&polyfoxy->x0, (long*)&polyfoxy->x1, (long*)&polyfoxy->x2, (long*)&polyfoxy->x3,
                                &polydepth,
                                &polyflag
                                );                                 
                    
                    addPrim(ot[db], polyfoxy);                     
                    
                    nextpri += sizeof(POLY_F4);                    
                }

                if (animatronicscamera[4] == 2) {
                    //Golden freddy
                    polygoldenf = (POLY_F4 *)nextpri;              
                            
                    RotMatrix(&RotVectoreveryone, &PolyMatrixgoldenf);    
                    TransMatrix(&PolyMatrixgoldenf, &MovVectorgoldenf);  
                    ScaleMatrix(&PolyMatrixgoldenf, &ScaleVectoreveryone);
                    
                    SetRotMatrix(&PolyMatrixgoldenf);                    
                    SetTransMatrix(&PolyMatrixgoldenf);                  
                    
                    setPolyF4(polygoldenf);                          
                    setRGB0(polygoldenf,204,204,0);
                    OTz = RotTransPers4(
                                &VertPoseveryone[0],      &VertPoseveryone[1],      &VertPoseveryone[2],      &VertPoseveryone[3],
                                (long*)&polygoldenf->x0, (long*)&polygoldenf->x1, (long*)&polygoldenf->x2, (long*)&polygoldenf->x3,
                                &polydepth,
                                &polyflag
                                );                                 
                    
                    addPrim(ot[db], polygoldenf);                  
                    
                    nextpri += sizeof(POLY_F4);                 
                }   

                if (animatronicscamera[5] == 2) {
                    //sparky
                    polysparky = (POLY_F4 *)nextpri;               
                            
                    RotMatrix(&RotVectoreveryone, &PolyMatrixsparky);
                    TransMatrix(&PolyMatrixsparky, &MovVectorsparky);  
                    ScaleMatrix(&PolyMatrixsparky, &ScaleVectoreveryone);
                    
                    SetRotMatrix(&PolyMatrixsparky);                   
                    SetTransMatrix(&PolyMatrixsparky);                 
                    
                    setPolyF4(polysparky);                             
                    setRGB0(polysparky,77,59,45);
                    OTz = RotTransPers4(
                                &VertPoseveryone[0],      &VertPoseveryone[1],      &VertPoseveryone[2],      &VertPoseveryone[3],
                                (long*)&polysparky->x0, (long*)&polysparky->x1, (long*)&polysparky->x2, (long*)&polysparky->x3,
                                &polydepth,
                                &polyflag
                                );                                 
                    
                    addPrim(ot[db], polysparky);                   
                    
                    nextpri += sizeof(POLY_F4);                    
                }   
    
            }
            pathfunc();
        }//Gameplay Screen
        if (menu == 3) { //Game over screen. ALWAYS BEGIN WITH THE STATIC
            if (staticframes > 1) {
                makepoly(15);
                if (staticframessheet == 8) {
                    staticframessheet = 0;
                    MovVectorstatic.vx = MovVectorstatic.vx - 16;
                } else {
                    staticframessheet++;
                    MovVectorstatic.vx = MovVectorstatic.vx + 2;
                }
                if (staticframessheet == 0) {
                }
            }
            if (staticframes == 2) {Ran(6);} //For random death message
            if (staticframes < 1) {
                seedtitle++;

                gameoverprint();

                makepoly(12);

                if (pad & PADstart) {
                    Ran(10000);
                    if (RAN == 1) {
                        goldenfreddied = 1;
                    }

                    resetgame(0);
                    menu = 1;
                }
            } else{staticframes--;}
        }
        FntFlush(-1); //Draw
        display(); //Always here        
    }
    return 0;
}