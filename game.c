/*
    TO FIX :

    FIXED ? (it is not doing that anymore but I'm not sure if it's fixed) : 

    TO FIX ON THE PS1 :

    TO MAKE (doing ideas/partially implemented things) : 

    TO DO (only ideas) :
    - Test the game on different hardware than PC and SCPH-9002 PS1

    OTHER (info) :

    Coming back there after more than 5 months to do a little cleanup is kind of weird.
    It's like going back in time, when you were still a beginner, struggling about errors and problems you now know how to deal with.
    After all these projects, all of these ports, it's really weird to go back to see the prototype.
    The one that started it all.

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
        22,
        0,
        {   //Static.xa = 3,216
            // channel 5
            // id   size   file  channel start end cursor
            {   0,  2747136,   1,     5,     0,   9400,  -1 }, //Intro.xa
            {   1,  2490176,   1,     5,     10896,   19432,  -1 }, //ambiance1.xa
            // channel 6                 
            {   2,  488224,   1,     6 ,   0,   1664, -1  }, //6am.xa
            {   3,  932064,   1,     6 ,   3168, 6344, -1  }, //Poweroutage.xa
            {   4,  971776,   1,     6 ,   7840, 11160, -1  }, //Mascottune.xa
            {   5,  2856928,   1,     6 ,   12656, 22432, -1  }, //ambiance2.xa
            // Channel 7
            {   6,  941408,   1,     7 ,   0, 3216, -1  }, //static.xa NOUBLIE PAS D'INCLURE LE SILENCE (à retirer ? -3192) +1,496
            {   7,  2476160,   1,     7 ,   4712, 13184, -1  }, //Ambiance3.xa 
            {   8,  8834752,   1,     7 ,   14680, 45028, -1  }, //Phone Guy Night 1.xa 
            //Channel 8
            {   9,  4307584,   1,     8 ,   0, 14752, -1  }, //Phone Guy Night 2.xa 
            {   10, 3041472,   1,     8 ,   16248, 26657, -1  }, //Phone Guy Night 3.xa  10408
            {   11, 2590624,   1,     8 ,   28152, 37016, -1  }, //Phone Guy Night 4.xa 
            {   12, 1702944,   1,     8 ,   38512, 44346, -1  }, //Phone Guy Night 5.xa 
            //Channel 9
            {   13, 2721440,   1,     9 ,   0, 9312, -1  }, //Music Box.xa 
            {   14, 2207520,   1,     9 ,   10808, 18360, -1  }, //phone guy lol (rizz freddy).xa 
            {   15, 696128,   1,     9 ,   19856, 22232, -1  }, //golden freddy screamer.xa 
            {   16, 677440,   1,     9 ,   23728, 26040, -1  }, //puppet music.xa 
            {   17, 425152,   1,     9 ,   27536, 28984, -1  }, //piratesong.xa 
            {   18, 4606592,   1,     9 ,   30480, 46248, -1  }, //funny music box.xa 
            //Channel 10
            {   19, 3237696,   1,     10 ,   0, 11080, -1  }, //Mixed ambiance 1
            {   20, 3078848,   1,     10 ,   14296, 24832, -1  }, //Mixed ambiance 2
            {   21, 3602112,   1,     10 ,   28048, 40376, -1  } //Mixed ambiance 3
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

void resetgame(int hardreset);
void print(int number);
int Ran(int max);
void debugPrintVanilla(void);
void animatronicdebugPrint(void);
void screamer(void);
void gameoverprint(void);
void printNightInfo(void);
void menuselectionfunc(void);
void debugPrint(void);
void doorFunc(int number);
void chargeNtimeFunc(void);
void controllerinput(void);
void LightFunc(void);
void doorFuncX(void);
void CameraFunc(void);
void lightsout(void);
void gamevictory(void);
void menuPrint(void);
void animatronicFunc(int init);
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

void starting(void) {
  resetgame(0);
  SpuSetKey(SPU_ON, SPU_04CH);

  if (customnightactivated == 0) {
    freddylocationframe = 300;
    bonnielocationframe = 300;
    chicalocationframe = 300;
    foxylocationframe = 300;
    convertion = 60;
    customAM = 12;
  }
  if (initstuff == 1) {clearVRAMMenu();} else {clearVRAMScreamer();}

  LoadTexture(_binary_tim_load_tim_start, &load);
  
    if (night == 7) {
        if (hellnight == 1) {foxylockeduration = 6;}
        if (impossiblenight == 1) {foxylockeduration = 3;}
    }

  musicframes = 0;
  if (enablephoneguystr[1] == 'N') {enablephoneguy = 1;} else {enablephoneguy = 0;}//I dunno why but it keep resetting it 

  if (fastnights) {FrameCounterlimit = FrameCounterlimit / 2;}

  AM = customAM;
  charge = customcharge;
  FrameCounterlimit = convertion;
  FrameCounterlimit = FrameCounterlimit * 60; //60 seconds * 60 fps = 3600 frames, maybe it would cause issues with 30 fps ??
  CdControlF(CdlPause,0);
  if (weirdnight == 0 && (customnightactivated == 0 || hellnight || impossiblenight)) {
    animatronicFunc(1);
  }
}
int main(void) {
    //controller
    TILE * PADL;                    // Tile primitives
    TILE * TRIGGERL;
    TILE * PADR;
    TILE * TRIGGERR;
    TILE * START, * SELECT;

    init();

    //SPU
    u_long spu_address;
    spuSetup(&spuSettings);
    // Init sound settings
    initSnd();

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

    while (1)
    {   
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
                if (customnightchanger != 0) {
                    night = customnightchanger;
                    customnightchanger = 0;
                    nightcheated = true;
                }

                starting();
                fadeoffice = 128;

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
            if (goldenfreddiedframes == 220) {
                sample = 15;
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
            }
            if (goldenfreddiedframes > 370) {
                makepoly(13);
            }
            if (goldenfreddiedframes == 375) {
                makepoly(6);
            }

            if (dead == 1) {
                if (screamersetsound == 0) {
                    sample = 6;
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

            if (light1) {
                Ran(100);
                if (RAN <= 20) {
                    LoadTexture(_binary_tim_office_officeLEFT_tim_start, &officeLEFT);
                    SpuSetKey(SPU_OFF, SPU_01CH);
                } else {
                    if (SpuGetKeyStatus(SPU_01CH) == SPU_OFF) {SpuSetKey(SPU_ON, SPU_01CH);}
                    if (!(bonnieDoor)) {LoadTexture(_binary_tim_office_officeLEFTlight_tim_start, &officeLEFTlight);} else {LoadTexture(_binary_tim_office_officeLEFTlightbonnie_tim_start, &officeLEFTlight);}
                }
            }
            if (light2) {
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
                                    sample = 5;
                                    fivesecondframe = 3912; //Ambiance 2
                                break;
                                case 3:
                                    sample = 7;
                                    fivesecondframe = 3390; //Ambiance 3
                                break;
                                case 4:
                                    if (foxylocation < 2) {
                                        sample = 17;
                                        fivesecondframe = 510; //Foxy 

                                    } else {
                                        ambiancenum = Ran(5);
                                    }
                                break;
                                case 5:
                                    sample = 4;
                                    fivesecondframe = 1290; //Circus 
                                break;
                                case 6:
                                    sample = 19;
                                    fivesecondframe = 4440; //Mixed ambiance 1
                                break;
                                case 7:
                                    sample = 20;
                                    fivesecondframe = 4200; //Mixed ambiance 2
                                break;
                                case 8:
                                    sample = 21;
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
                    sample = 3;
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
                    sample = 14; //Why do you tryna rizz freddy ??
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
                    sample = 8;
                }
                if (night == 2) {
                    phoneguytalking = 5880;
                    phoneguytalkingconst = 5880;
                    sample = 9;
                }
                if (night == 3) {
                    phoneguytalking = 4080;
                    phoneguytalkingconst = 4080;
                    sample = 10;
                }
                if (night == 4) {
                    phoneguytalking = 3540;
                    phoneguytalkingconst = 3540;
                    sample = 11;
                }
                if (night == 5) {
                    phoneguytalking = 2160;
                    phoneguytalkingconst = 2160;
                    sample = 12;
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
                    sample = 12;
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

                timeoncam++; //For score system

                cameraloc();

                if (curcam[0] == '6' && curcam[1] == ' ') {
                    if (puppetmusic == 0) {
                        Ran(500);
                        if (RAN == 1) {
                            if (camera == 1 && phoneguytalking == 0 && ambiancesound == 0) {
                                // Set sample ID for playback
                                sample = 16;
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
                sample = 3;
                filter.chan = soundBank.samples[sample].channel;
                filter.file = soundBank.samples[sample].file;
                CdControlF(CdlSetfilter, (u_char *)&filter);

                soundBank.samples[sample].cursor = 0;
                lightsout();
            }
            if (AM == 6 && FrameCounter == 0) {
                sample = 2;
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

            if (fivetosixamframes > 500 && blinkicon > 30 && fivetosixamframes < 819){
                FntPrint("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n             score : %d !", score);
            }
            if (fivetosixamframes > 600 && blinkicon > 30 && fivetosixamframes < 819) {
                    if (score > highscore) {

                        highscore = score;

                        highscorehit = 1;
                        SpuSetKey(SPU_ON, SPU_05CH);
                    } 
                    if (highscorehit == 1) {
                        FntPrint("\n              NEW HIGHSCORE");
                    } else {
                        if (score == 0) {FntPrint("\n                   ...");}
                        if (score > 0 && score <= 10000) {FntPrint("\n                 Ew...");}
                        if (score >= 15000 && score <= 18000) {FntPrint("\n               Good !");}
                        if (score > 18000 && score < 22000) {FntPrint("\n                Great !!");}
                        if (score >= 22000) {FntPrint("\n               AWESOME !!!");}
                    }

                if (freddydifficulty > 10 && bonniedifficulty > 10 && chicadifficulty > 10 && foxydifficulty > 10) {
                    FntPrint("\n            %d / %d / %d / %d", freddydifficulty, bonniedifficulty, chicadifficulty, foxydifficulty);
                } else {
                    FntPrint("\n             %d / %d / %d / %d", freddydifficulty, bonniedifficulty, chicadifficulty, foxydifficulty);
                }
            }
            if (fivetosixamframes > 819) {
                if (night == 5 || night == 6 || night == 7) {
                    nextnightframes++;
                    if (nextnightframes == 1) {
                        if (customnextnightactivation == 0) {
                            sample = 13; //Sample is for the music playing, 13 normal, 18 funky
                        }
                        else {
                            sample = 18;
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
                    sample = 13;
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
            if (staticframes == 2) {
            }
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
void chargeNtimeFunc(void) {
    FrameCounter++;

    Glitch++;
    Glitch = Glitch + 3 * 8;
    if (Glitch > 1987) {Glitch = Glitch - 987;}

    if (FrameCounter == FrameCounterlimit) {
        AM++;
        if (powermanagementhour > 13) { // U should use ~10% per hour 
            powermanagementtotal = powermanagementhour;
        }
        powermanagementhour = 0;
        if (AM == 13) {
            AM = 1;
        }
        FrameCounter = 0;
    }

    ChargeCounter = ChargeCounter - usage;
    usage = defaultusage;

        if (ChargeCounter <= 0 && unlimitedpower == 0) {
            charge = charge - 1;
            ChargeCounter = 596;
            powermanagementhour++;
        }
    if (weirdnight == 1 && AM == 3) {
        surusage = 1;
    }
    if (weirdnight == 1 && AM == 4) {
        cantlight = 1;
        cantdoor = 1;
        surusage = 2;
    }
    if (weirdnight == 1 && AM == 5) {
        FrameCounterlimit = 36000;
        surusage = 3;
    } 
}
void resetgame(int hardreset) {
    if (hardreset == 1) {
        freddydifficulty = 0;
        bonniedifficulty = 0;
        chicadifficulty = 0;
        foxydifficulty = 0;
    }
    freddylocation = 0;
    freddylocationframe = 181;
    bonnielocation = 0;
    bonnielocationframe = 298;
    bonnieliljumpscare = 0;
    freddyliljumpscare = 0;
    chicalocation = 0;
    chicalocationframe = 299;
    foxylocation = 0;
    foxylocationframe = 301;
    foxywaiting = 500;
    foxyrunningframes = 0;
    foxylocked = 0;
    ranfoxy = 0;
    foxysknock = 0;
    foxyknockframe = 0;
    foxydrainpower = 1;
    bonnieDoor = 0;
    chicaDoor = 0;
    noisedoorbonnie = 0;
    noisedoorchica = 0;

    cantlight = 0;
    cantdoor = 0;
    cantlightR = 0;
    cantdoorR = 0;
    cantlightL = 0;
    cantdoorL = 0;

    door = 0; //0 is left, 1 is right
    doorclosedL = 0; //0 is no, 1 is yes
    doorclosedR = 0; //0 is no, 1 is yes

    light1 = 0;
    light2 = 0;
    lightframe = 0;

    camera = 0;
    curcam[0] = '1';
    curcam[1] = 'A';
    puppetmusic = 0;

    noisefootstep = 0;
    framenoisefootstep = 0;

    fivesecondframe = 300;

    islightsout = 0;
    lightsoutinit = 0;
    musicboxactivated = 0;
    musicboxappearanceframe = 0;
    musicboxappearancechance = 20;
    musicboxinit = 0;
    freddyglowing = 0;
    glowvar = 128;
    blackoutactivated = 0;
    blackoutappearanceframe = 0;
    blackoutappearancechance = 20;
    blackoutinit = 0;
    blackoutscreamerappearanceframe = 0;
    blackoutscreamerappearancechance = 20;
    surusage = 0;

    goldenfreddylocation = 0;
    goldenfreddyframes = 0;
    goldenfreddychances = 5000;

    isalreadydead = 0;
    isalreadydeadlow = 0;
    framedeadpossi = 60;
    lastsecondsframes = 1800;

    screamersetsound = 0;
    screamerframes = 47;
    spriteframes = 2;
    spritesheet = 0;

    dead = 0;
    deadfrom = 0;

    nightwon = 0;

    fadeoffice = 128;

    nextnightframes = 0;
    customnextnightactivation = 0;
    staticframessheet = 0;
    MovVectorstatic.vx = -40;

    staticframes = 600;

    score = 0;
    highscorehit = 0;
    blockedanimatronic = 0;
    powermanagementtotal = 0;

    isingame = 0;

    #define OTLEN 8                    // Ordering Table Length 

    u_long ot[2][OTLEN];               // double ordering table of length 8 * 32 = 256 bits / 32 bytes

    char primbuff[2][32768];     // double primitive buffer of length 32768 * 8 =  262.144 bits / 32,768 Kbytes

    char *nextpri = primbuff[0];       // pointer to the next primitive in primbuff. Initially, points to the first bit of primbuff[0]

    #define COUNT_OF(x) (sizeof(x) / sizeof(0[x]))

    AM = 12;
    FrameCounter = 0;
    ChargeCounter = 596;
    usage = 1;
    charge = 100;
    defaultusage = 1;

    mutedcall = 0;
}
void print(int number) {
    if (charge > 0) {
        if (camera == 0) {
            if (number == 1) { //Basic debug (without access to camera)
                FntPrint("AM : %d, current RAN : %d", AM, RAN);  // print time
                FntPrint("\nCurrent Usage: %d Current Charge : %d", usage, charge); //print battery
                FntPrint("\nCurrent battery frame: %d", ChargeCounter);
                if (door == 0) { //print doors
                    FntPrint("\nleft Door: %d left Light: %d", doorclosedL, light1);
                }
                if (door == 1) {
                    FntPrint("\nRight Door: %d Right Light: %d", doorclosedR, light2);
                }
                FntPrint("\n\nphoneguytalking %d, ambiancechance %d, fivesecondframe %d, ambiancenum %d", phoneguytalking, ambiancechance, fivesecondframe, ambiancenum); //print cam     

            }
        }
        if (number == 3) { //Vanilla debug (with access to camera)
            if (camera == 0) {
                FntPrint("\n");
            }
            FntPrint("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n%d AM, ", AM);  // print time
            FntPrint("Night %d", night);
            if (night != 7) {
                FntPrint("\nCharge : %d \nUsage: %d\n", charge, usage);
            } else {
                FntPrint("\nCharge : %d \nUsage: %d \n", Glitch, usage);
            }
        }
        if (camera == 1 && number != 2) {
            FntPrint("Current Camera :          %s,%s", curcam, curcamname);  // print time
        }
        if (number == 2) { //Animatronic debug (with access to camera)
            FntPrint("%d AM, %d/100, %d usage, IAD %d, IADL %d\n",AM, charge, usage, isalreadydead, isalreadydeadlow);
            FntPrint("freddylocationframe %d, location %d,\n",freddylocationframe, freddylocation);
            FntPrint("\nbonnielocationframe %d & location %d,\n", bonnielocationframe, bonnielocation);
            FntPrint("  chicalocationframe %d & location %d,\nfoxylocationframe %d & location %d. waiting %d & running %d\n",chicalocationframe, chicalocation, foxylocationframe, foxylocation, foxywaiting, foxyrunningframes);
            FntPrint("F AI %d, B AI %d, C AI %d,\nFo AI %d",freddydifficulty, bonniedifficulty, chicadifficulty, foxydifficulty);
        }
    }
}
void printNightInfo(void) { //print night information (1st, 2nd, 3rd, etc)
    if (night == 1) {
        FntPrint("\n\n\n\n\n\n\n\n\n               %d:00 AM\n\n              1st  night", AM); 
    }
    if (night == 2) {
        FntPrint("\n\n\n\n\n\n\n\n\n               %d:00 AM\n\n              2nd  night", AM); 
    }
    if (night == 3) {
        FntPrint("\n\n\n\n\n\n\n\n\n               %d:00 AM\n\n              3rd  night", AM); 
    }
    if (night == 4) {
        FntPrint("\n\n\n\n\n\n\n\n\n               %d:00 AM\n\n              4th  night", AM);
    }
    if (night == 5) {
        FntPrint("\n\n\n\n\n\n\n\n\n               %d:00 AM\n\n              5th  night", AM);
    }
    if (night == 6) {
        FntPrint("\n\n\n\n\n\n\n\n\n               %d:00 AM\n\n              6th  night", AM);
    }
    if (night == 7) {
        if (hellnight == 1) {
            FntPrint("\n\n\n\n\n\n\n\n\n               %d:00 AM\n\n           You're not ready\n\n     for what is going to happen.", AM); 
        }
        if (impossiblenight == 1) {
            FntPrint("\n\n\n\n\n\n\n\n\n               %dLCPZOW\n\n           IUYeJZZD pOD APMCV\n\n     PPP OWM SA KJMEF KL VCNBWQD", AM);
        }
    }
    if (customnightactivated == 1) {FntPrint("\n\n             Custom night");} 
    if (activatedmenudebug == 1) {FntPrint("\n\n              Debug Mode");}  // debug time
    if (cheating == 1) {FntPrint("\n\n            Cheat Activate");}  // cheat time
}
void menuselectionfunc(void) { //LONG asf lmaoo
    if (pad & PADLup) {
        if (limiterpadup == 0) {
            if (menuselection > 1) {
                menuselection--;
            }
            else {
                menuselection = menuselectionmax;
            }
            SpuSetKey(SPU_ON, SPU_04CH);
            limiterpadup = 1;
        }
    }
    if (pad & PADLdown) {
        if (limiterpaddown == 0) {
            if (menuselection < menuselectionmax) {
                menuselection++;
            }
            else {
                menuselection = 1;
            }
            SpuSetKey(SPU_ON, SPU_04CH);
            limiterpaddown = 1;
        }
    }
    if (!(pad & PADLright)) {limiterpadright = 0;}
    if (!(pad & PADLleft)) {limiterpadleft = 0;}
    if (!(pad & PADLdown)) {limiterpaddown = 0;}
    if (!(pad & PADLup)) {limiterpadup = 0;}
    if (!(pad & PADstart)) {limiterstart = 0;}
    if (!(pad & PADRdown)) {limiterbuttondown = 0;}

    if (maincustomnightmenu == 0 && extramenu == 0 && infoscreen == 0 && unlockssubmenu == 0 && AISetmenu == 0 && chargemenu == 0 && advancedmenu == 0) { 
        if (isingame) {
            if (menuselection == 1) {//Continue night
                if (pad & PADstart) {
                    menu = 2;
                    returnedingame = 1;
                } 
            }

            if (menuselection == 2) {//Abandon night
                if (pad & PADstart && limiterstart == 0) {
                    resetgame(0);
                    limiterstart++;
                    menuselection = 3;
                    if (activatedmenudebug == 0) {menuselectionmax = 4;} else {menuselectionmax = 5;}
                    
                } 
            }
        } else {
            if (menuselection == 1) {//"Starting" night
                if (pad & PADstart) {
                    night = 1;
                    helpwantedposter = 1;
                } 
            }

            if (menuselection == 2) { //Continue nights
                if (pad & PADstart) {
                    loadingframe = 360;
                    menu = 1;
                }//Or...
                if (pad & PADRup && pad & PADRright && pad & PADR1 && pad & PADL2 && activatedmenudebug == 0) //Activate debug !
                {
                    activatedmenudebug = 1;
                    menuselectionmax = menuselectionmax + 1;
                }
            }

            if (menuselection == 3) { //EXTRA MENU
                if (pad & PADstart) {
                    if (limiterstart == 0) {
                        extramenu = 1;
                        menuselection = 1;
                        limiterstart++;
                        if (activatedmenudebug == 0) {
                            menuselectionmax = 5;
                        }
                        if (activatedmenudebug == 1) {
                            menuselectionmax = 6;
                        }
                    }
                }
            }
            if (menuselection == 4) { //CUSTOM NIGHT MENU
                if (pad & PADstart) {
                    if (limiterstart == 0) {
                        maincustomnightmenu = 1;
                        menuselection = 1;
                        menuselectionmax = 6;
                        limiterstart++;
                    }
                }
            }

            if (activatedmenudebug == 1) {
                if (menuselection == 5) {
                    if (pad & PADLright) {
                        if (limiterpadright == 0) {
                            printnumber++;
                            if (printnumber > 3) {printnumber = 1;}
                            limiterpadright = 1;
                        }
                    }
                }
                if (!(pad & PADLright)) {limiterpadright = 0;}
            }
            if (!(pad & PADstart)) {limiterstart = 0;}
        }
    }

    if (maincustomnightmenu == 1) {
        if (menuselection == 1) {
            if (pad & PADLright) {
                if (limiterpadright == 0) {
                    customnightchanger++;
                    if (customnightchanger > 6) {customnightchanger = 1;}
                    limiterpadright = 1;
                }
            }
            if (pad & PADLleft) {
                if (limiterpadleft == 0) {
                    customnightchanger--;
                    if (customnightchanger < 1) {customnightchanger = 6;}
                    limiterpadleft = 1;
                }
            } //Change night's var
        }

        if (menuselection == 2) { // AI SET MENU
            if (pad & PADstart) {
                if (limiterstart == 0) {
                    maincustomnightmenu = 0;
                    AISetmenu = 1;
                    menuselection = 6;
                    menuselectionmax = 6;
                    limiterstart = 1;
                }
            }
        }
        if (menuselection == 3) { // CHARGE MENU
            if (pad & PADstart) {
                if (limiterstart == 0) {
                    maincustomnightmenu = 0;
                    chargemenu = 1;
                    menuselection = 4;
                    menuselectionmax = 4;
                    limiterstart = 1;
                }
            }
        }
        if (menuselection == 4) { // ADV MENU
            if (pad & PADstart) {
                if (limiterstart == 0) {
                    maincustomnightmenu = 0;
                    advancedmenu = 1;
                    menuselection = 4;
                    menuselectionmax = 4;
                    limiterstart = 1;
                }
            }
        }
        if (menuselection == 5) { // LAUNCH NIGHT
            if (pad & PADstart) {
              if (limiterstart == 0) {
                menu = 1;
                customnightactivated = 1;
              }
            }
        }
        if (menuselection == 6) { // RETURN TO MAIN MENU
            if (pad & PADstart) {
                if (limiterstart == 0)  {
                    maincustomnightmenu = 0;
                    menuselection = 4;
                    limiterstart++;
                    if (activatedmenudebug == 0) {menuselectionmax = 4;}
                    else {menuselectionmax = 5;}
                }
            }
        }
    }
    if (AISetmenu == 1) {
        if (menuselection == 1) {
            if (pad & PADLright) { //Freddy
                if (limiterpadright == 0) {
                    freddydifficulty++;
                    if (freddydifficulty > 20) {freddydifficulty = 0;}
                    limiterpadright = 1;
                }
            }
            if (pad & PADLleft) { //Freddy
                if (limiterpadleft == 0) {
                    freddydifficulty--;
                    if (freddydifficulty < 0) {freddydifficulty = 20;}
                    limiterpadleft = 1;
                }
            }
        }
        if (menuselection == 2) {
            if (pad & PADLright) { //Bonnie
                if (limiterpadright == 0) {
                    bonniedifficulty++;
                    if (bonniedifficulty > 20) {bonniedifficulty = 0;}
                    limiterpadright = 1;
                }
            }
            if (pad & PADLleft) { //Bonnie
                if (limiterpadleft == 0) {
                    bonniedifficulty--;
                    if (bonniedifficulty < 0) {bonniedifficulty = 20;}
                    limiterpadleft = 1;
                }
            }
        }
        if (menuselection == 3) {
            if (pad & PADLright) { //Chica
                if (limiterpadright == 0) {
                    chicadifficulty++;
                    if (chicadifficulty > 20) {chicadifficulty = 0;}
                    limiterpadright = 1;
                }
            }
            if (pad & PADLleft) { //Chica
                if (limiterpadleft == 0) {
                    chicadifficulty--;
                    if (chicadifficulty < 0) {chicadifficulty = 20;}
                    limiterpadleft = 1;
                }
            }
        }
        if (menuselection == 4) {
            if (pad & PADLright) { //Foxy
                if (limiterpadright == 0) {
                    foxydifficulty++;
                    if (foxydifficulty > 20) {foxydifficulty = 0;}
                    limiterpadright = 1;
                }
            }
            if (pad & PADLleft) { //Foxy
                if (limiterpadleft == 0) {
                    foxydifficulty--;
                    if (foxydifficulty < 0) {foxydifficulty = 20;}
                    limiterpadleft = 1;
                }
            }
        }
        if (menuselection == 5) {
            if (pad & PADLleft) {
                if (limiterpadleft == 0) {
                    presetselector--;
                    if (presetselector < 1) {presetselector = 1;}
                    limiterpadleft = 1;
                }
            }
            if (pad & PADLright) {
                if (limiterpadright == 0) {
                    presetselector++;
                    if (presetselector > 7) {presetselector = 7;}
                    limiterpadright = 1;
                }
            }
        }
        if (menuselection == 6) {
            if (pad & PADstart) {
                if (limiterstart == 0) {
                    maincustomnightmenu = 1;
                    AISetmenu = 0;
                    menuselection = 2;
                    menuselectionmax = 6;
                    limiterstart++;
                }
            }
        }
        if (presetselector == 1) {
            presetselectorstr[0] = 'C';
            presetselectorstr[1] = 'u';
            presetselectorstr[2] = 's';
            presetselectorstr[3] = 't';
            presetselectorstr[4] = 'o';
            presetselectorstr[5] = 'm';
            presetselectorstr[6] = ' ';
        }
        if (presetselector > 1 && presetselector < 7) {
            presetselectorstr[0] = 'N';
            presetselectorstr[1] = 'i';
            presetselectorstr[2] = 'g';
            presetselectorstr[3] = 'h';
            presetselectorstr[4] = 't';
            presetselectorstr[5] = ' ';
            if (presetselector == 2) {
                presetselectorstr[6] = '2';
                freddydifficulty = 0;
                bonniedifficulty = 3;
                chicadifficulty = 1;
                foxydifficulty = 1;
            }
            if (presetselector == 3) {
                presetselectorstr[6] = '3';
                freddydifficulty = 1;
                bonniedifficulty = 0;
                chicadifficulty = 5;
                foxydifficulty = 2;
            }
            if (presetselector == 4) {
                presetselectorstr[6] = '4';
                freddydifficulty = 2;
                bonniedifficulty = 2;
                chicadifficulty = 4;
                foxydifficulty = 6;
            }
            if (presetselector == 5) {
                presetselectorstr[6] = '5';
                freddydifficulty = 3;
                bonniedifficulty = 5;
                chicadifficulty = 7;
                foxydifficulty = 5;
            }
            if (presetselector == 6) {
                presetselectorstr[6] = '6';
                freddydifficulty = 4;
                bonniedifficulty = 10;
                chicadifficulty = 12;
                foxydifficulty = 16;
            }
        }
        if (presetselector == 7) {
            presetselectorstr[0] = '4';
            presetselectorstr[1] = '/';
            presetselectorstr[2] = '2';
            presetselectorstr[3] = '0';
            presetselectorstr[4] = ' ';
            presetselectorstr[5] = ' ';
            presetselectorstr[6] = ' ';
            freddydifficulty = 20;
            bonniedifficulty = 20;
            chicadifficulty = 20;
            foxydifficulty = 20;
        }
    }
    if (chargemenu == 1) {
        advancedmenu = 0;
        if (menuselection == 1) {
            //Charge
            //For more slowed down ones
            if (pad & PADLright) {
                if (limiterpadright == 0) {
                    customcharge++;
                    if (customcharge > 100) {customcharge = 0;}
                    limiterpadright = 1;
                }
            }
            if (pad & PADLleft) {
                if (limiterpadleft == 0) {
                    customcharge--;
                    if (customcharge < 0) {customcharge = 100;}
                    limiterpadleft = 1;
                }
            }
            //For quick changes
            if (pad & PADL1) {
                customcharge++;
                if (customcharge > 100) {customcharge = 0;}
            }
            if (pad & PADR1) {
                customcharge--;
                if (customcharge < 0) {customcharge = 100;}
            }
        }
        if (menuselection == 2) {
            //AM
            if (pad & PADLright) {
                if (limiterpadright == 0) {
                    customAM++;
                    if (customAM < 12 && customAM > 6) {customAM = 12;}
                    if (customAM > 12) {customAM = 0;}
                    limiterpadright = 1;
                }
            }
            if (pad & PADLleft) {
                if (limiterpadleft == 0) {
                    customAM--;
                    if (customAM < 12 && customAM > 6) {customAM = 6;}
                    if (customAM < 0) {customAM = 12;}
                    limiterpadleft = 1;
                }
            }
        }
        if (menuselection == 3) {
            //FrameCounterlimit (via the convertion var)
            if (pad & PADLright) {
                if (limiterpadright == 0) {
                    convertion++;
                    limiterpadright = 1;
                }
            }
            if (pad & PADLleft) {
                if (limiterpadleft == 0) {
                    convertion--;
                    if (convertion < 0) {convertion = 0;}
                    limiterpadleft = 1;
                }
            }
            //For quick change
            if (pad & PADR1) {
                convertion++;
            }
            if (pad & PADL1) {
                convertion--;
                if (convertion < 0) {convertion = 0;}
            }
            //For reset
            if (pad & PADstart) {
                convertion = 60;
            }
            //For 0
            if (pad & PADselect) {
                convertion = 0;
            }
            //For 120
            if (pad & PADstart && pad & PADselect) {
                convertion = 120;
            }
        }
        if (menuselection == 4) {
            if (pad & PADstart) {
                if (limiterstart == 0) {
                    maincustomnightmenu = 1;
                    chargemenu = 0;
                    menuselection = 3;
                    menuselectionmax = 6;
                    limiterstart++;
                }
            }
        }
    }
    if (advancedmenu == 1) {
        if (menuselection == 1) {
            if (pad & PADRright) { //Foxy 
                foxylocationframelock++;
            }
            if (pad & PADRleft) { //Foxy 
                foxylocationframelock--;
                if (foxylocationframelock < 1) {foxylocationframelock = 1;}
            }
            if (pad & PADLright) { //Freddy 
                freddylocationframelock++;
            }
            if (pad & PADLleft) { //Freddy 
                freddylocationframelock--;
                if (freddylocationframelock < 1) {freddylocationframelock = 1;}
            }
            if (pad & PADL1) { //Bonnie 
                bonnielocationframelock--;
                if (bonnielocationframelock < 1) {bonnielocationframelock = 1;}
            }
            if (pad & PADL2) { //Bonnie 
                bonnielocationframelock++;
            }
            if (pad & PADR1) { //Chica 
                chicalocationframelock--;
                if (chicalocationframelock < 1) {chicalocationframelock = 1;}
            }
            if (pad & PADR2) { //Chica 
                chicalocationframelock++;
            }
            if (pad & PADstart) {
                freddylocationframe = 181;
                bonnielocationframe = 298;
                chicalocationframe = 299;
                foxylocationframe = 301;
                freddylocationframelock = 181;
                bonnielocationframelock = 298;
                chicalocationframelock = 299;
                foxylocationframelock = 301;
            }
        }
        if (menuselection == 2) {
            if (pad & PADLleft) {
                if (limiterpadleft == 0) {
                    defaultusage--;
                    limiterpadleft++;
                    if (defaultusage < 0) {defaultusage = 0;}
                }
            }
            if (pad & PADLright) {
                if (limiterpadright == 0) {
                    defaultusage++;
                    limiterpadright++;
                }
            }
            if (pad & PADstart) {
                defaultusage = 1;
            }
        }
        if (menuselection == 3) { 
            if (pad & PADLleft) {
                if (limiterpadleft == 0) {
                    foxylockeduration--;
                    limiterpadleft++;
                    if (foxylockeduration < 1) {foxylockeduration = 1;}
                }
            }
            if (pad & PADLright) {
                if (limiterpadright == 0) {
                    foxylockeduration++;
                    limiterpadright++;
                }
            }
            if (pad & PADstart) {
                foxylockeduration = 16;
            }
        }
        if (menuselection == 4) {
            if (pad & PADstart) {
                if (limiterstart == 0) {
                    maincustomnightmenu = 1;
                    advancedmenu = 0;
                    menuselection = 4;
                    menuselectionmax = 6;
                    limiterstart++; 
                }
            }
        }
    }
    if (extramenu == 1) {
        if (menuselection == 1) { //Phone guy
            if (pad & PADRdown) {
                if (limiterbuttondown == 0) {
                    enablephoneguy++;
                    enablephoneguystr[0] = 'O';
                    enablephoneguystr[1] = 'N';
                    enablephoneguystr[2] = ' ';
                    if (enablephoneguy > 1) {
                        enablephoneguy = 0;
                        enablephoneguystr[0] = 'O';
                        enablephoneguystr[1] = 'F';
                        enablephoneguystr[2] = 'F';
                    }
                    limiterbuttondown = 1;
                }
            }
        }
        if (menuselection == 2) { //Unlocks menu
            if (pad & PADstart) {
                if (limiterstart == 0) {
                    extramenu = 0;
                    unlockssubmenu = 1;
                    menuselection = 1;
                    menuselectionmax = 4;
                    limiterstart = 1;
                }
            }
        }
        if (menuselection == 3) { //Informations on the game
            if (pad & PADstart) {
                if (limiterstart == 0) {
                    extramenu = 0;
                    infoscreen = 1;
                    menuselection = 1;
                    menuselectionmax = 1;
                    limiterstart = 1;
                }
            }
        }
        if (menuselection == 4) {//Two players mode
            if (pad & PADRdown) {
                if (limiterbuttondown == 0) {
                    twoplayermode++;
                    if (twoplayermode > 1) {twoplayermode = 0;}
                    
                    if (twoplayermode == 0) {
                        twoplayermodestr[1] = 'F';
                        twoplayermodestr[2] = 'F';
                    } else {
                        twoplayermodestr[1] = 'N';
                        twoplayermodestr[2] = ' ';
                    }
                    limiterbuttondown = 1;
                }
            }
        }
        if (menuselection == 5) { //Return
            if (pad & PADstart) {
                if (limiterstart == 0)  {
                    extramenu = 0;
                    menuselection = 3;
                    limiterstart++;
                    if (activatedmenudebug == 0) {menuselectionmax = 4;}
                    else {menuselectionmax = 5;}
                }
            }
        }
        if (menuselection == 6) { //Weird night
            if (pad & PADstart) {
                weirdnight = 1;
                enablephoneguy = 1;
                enablephoneguystr[1] = 'N';
                enablephoneguystr[2] = ' ';
                SpuSetKey(SPU_ON, SPU_04CH);
            }
        }
    }
    if (infoscreen == 1) {
        if (menuselection == 1) {
            if (pad & PADstart) {
                if (limiterstart == 0) {
                    extramenu = 1;
                    infoscreen = 0;
                    menuselection = 1;
                    if (activatedmenudebug == 0) {
                        menuselectionmax = 5;
                    }
                    if (activatedmenudebug == 1) {
                        menuselectionmax = 6;
                    }
                    limiterstart = 1;
                }
            }
        }
    }
    if (unlockssubmenu == 1) {
        if (menuselection == 1) {
            if (pad & PADRdown) {
                if (limiterbuttondown == 0) {
                    unlimitedpower++;
                    unlimitedpowerstr[0] = 'O';
                    unlimitedpowerstr[1] = 'N';
                    unlimitedpowerstr[2] = ' ';
                    if (unlimitedpower > 1) {
                        unlimitedpower = 0;
                        unlimitedpowerstr[0] = 'O';
                        unlimitedpowerstr[1] = 'F';
                        unlimitedpowerstr[2] = 'F';
                    }
                    cheating = 1;
                    limiterbuttondown = 1;
                }
            }
        }
        if (menuselection == 2) {
            if (pad & PADRdown) {
                if (limiterbuttondown == 0) {
                    fastnights++;
                    fastnightsstr[0] = 'O';
                    fastnightsstr[1] = 'N';
                    fastnightsstr[2] = ' ';
                    if (fastnights > 1) {
                        fastnights = 0;
                        fastnightsstr[0] = 'O';
                        fastnightsstr[1] = 'F';
                        fastnightsstr[2] = 'F';
                    }
                    cheating = 1;
                    limiterbuttondown = 1;
                }
            }
        }
        if (menuselection == 3) {
            if (pad & PADRdown) {
                if (limiterbuttondown == 0) {
                    radar++;
                    radarstr[0] = 'O';
                    radarstr[1] = 'N';
                    radarstr[2] = ' ';
                    if (radar > 1) {
                        radar = 0;
                        radarstr[0] = 'O';
                        radarstr[1] = 'F';
                        radarstr[2] = 'F';
                    }
                    cheating = 1;
                    limiterbuttondown = 1;
                }
            }
        }
        if (menuselection == 4) {
            if (pad & PADstart) {
                if (limiterstart == 0) {
                    extramenu = 1;
                    unlockssubmenu = 0;
                    menuselection = 1;
                    if (activatedmenudebug == 0) {
                        menuselectionmax = 5;
                    }
                    if (activatedmenudebug == 1) {
                        menuselectionmax = 6;
                    }
                    limiterstart = 1;
                }
            }
        }
    }
}
void menuPrint(void) {
    if (maincustomnightmenu == 0 && extramenu == 0 && infoscreen == 0 && unlockssubmenu == 0 && AISetmenu == 0 && chargemenu == 0 && advancedmenu == 0) {
        if (isingame) {
            FntPrint("   Five\n\n   Nights\n\n   at\n\n   Freddy's\n\n   Pause Menu\n\n\n");  // print time

            if (menuselection == 1) {FntPrint(">> Continue Night %d\n\n", night);}
            else {FntPrint("   Continue Night %d\n\n", night);}

            if (menuselection == 2) {FntPrint(">> Abandon The Night \n\n");}
            else {FntPrint("   Abandon The Night \n\n");}
        } else {

            FntPrint("   Five\n\n   Nights\n\n   at\n\n   Freddy's\n\n\n");  // print time

            if (menuselection == 1) {FntPrint(">> New Game\n\n");}
            else {FntPrint("   New Game\n\n");}

            if (menuselection == 2) {FntPrint(">> Continue Night %d\n\n", night);}
            else {FntPrint("   Continue Night %d\n\n", night);}

            if (menuselection == 3) {FntPrint(">> Extra menu \n\n");}
            else {FntPrint("   Extra menu \n\n");}

            if (menuselection == 4) {FntPrint(">> Custom Night \n\n");}
            else {FntPrint("   Custom Night \n\n");}

            if (activatedmenudebug == 1) {
                if (menuselection == 5) {FntPrint(">> Debugprint %d\n\n", printnumber);}
                else {FntPrint("   Debugprint \n\n");}
            }
        }
    }
    if (maincustomnightmenu == 1) {
        FntPrint("   Custom\n\n   Night\n\n\n");  // print time

        FntPrint("   Welcome! What do you want to modify?\n\n\n\n");

        if (menuselection == 1) {FntPrint(">> Night set : %d\n\n", customnightchanger);}
        else {FntPrint("   Night set : %d\n\n", customnightchanger);}
        if (menuselection == 2) {FntPrint(">> Set AI levels\n\n");}
        else {FntPrint("   Set AI levels\n\n");}
        if (menuselection == 3) {FntPrint(">> Set Charge, Timer, ect.\n\n");}
        else {FntPrint("   Set Charge, Timer, ect.\n\n");}
        if (menuselection == 4) {FntPrint(">> Advanced settings\n\n");}
        else {FntPrint("   Advanced settings\n\n");}
        if (menuselection == 5) {FntPrint(">> Launch custom night\n\n");}
        else {FntPrint("   Launch custom night\n\n");}
        if (menuselection == 6) {FntPrint(">> Return to main menu\n\n");}
        else {FntPrint("   Return to main menu\n\n");}
    }
    if (AISetmenu == 1) {
        FntPrint("   Custom\n\n   Night\n\n\n");  // print time
        FntPrint("   Set Ai Level Menu\n\n\n");
        if (menuselection == 1) {FntPrint(">> Freddy : %d\n\n", freddydifficulty );}
        else {FntPrint("   Freddy : %d\n\n", freddydifficulty );}
        if (menuselection == 2) {FntPrint(">> Bonnie : %d\n\n", bonniedifficulty );}
        else {FntPrint("   Bonnie : %d\n\n", bonniedifficulty );}
        if (menuselection == 3) {FntPrint(">> Chica : %d\n\n", chicadifficulty );}
        else {FntPrint("   Chica : %d\n\n", chicadifficulty );}
        if (menuselection == 4) {FntPrint(">> Foxy : %d\n\n", foxydifficulty );}
        else {FntPrint("   Foxy : %d\n\n", foxydifficulty );}
        if (menuselection == 5) {FntPrint(">> Preset : %s\n\n", presetselectorstr);}
        else {FntPrint("   Preset : %s\n\n",presetselectorstr);}
        if (menuselection == 6) {FntPrint(">> Return to Custom night menu\n\n");}
        else {FntPrint("   Return to Custom night menu\n\n");}
        if (freddydifficulty == 1 && bonniedifficulty == 9 && chicadifficulty == 8 && foxydifficulty == 7) {
            Ran(4004);
            if (RAN == 1) {FntPrint("   no\n\n");}
            if (RAN == 2) {FntPrint("   dont\n\n");}
            if (RAN == 3) {FntPrint("   never\n\n");}
            if (RAN == 4) {FntPrint("   its me\n\n");}
            if (RAN == 5) {FntPrint("   regrets\n\n");}
            if (RAN == 6) {FntPrint("   \n\n       no\n\n");}
            if (RAN == 7) {FntPrint("   \n\n       dont\n\n");}
            if (RAN == 8) {FntPrint("   \n\n       never\n\n");}
            if (RAN == 9) {FntPrint("   \n\n       its me\n\n");}
            if (RAN == 10) {FntPrint("   \n\n       regrets\n\n");}
        }
    }
    if (chargemenu == 1) {
        FntPrint("   Custom\n\n   Night\n\n\n");  // print time
        FntPrint("   Set Charge, timer, ect Menu\n\n\n");

        if (menuselection == 1) {FntPrint(">> Set charge (not infinite) %d\n\n", customcharge );}
        else {FntPrint("   Set charge (not infinite) %d\n\n", customcharge );}
        if (menuselection == 2) {FntPrint(">> Set beginning AM %d\n\n", customAM );}
        else {FntPrint("   Set beginning AM %d\n\n", customAM );}
        if (menuselection == 3) {FntPrint(">> 1 Hour = %d seconds in game\n\n", convertion );}
        else {FntPrint("   1 Hour = %d seconds in game\n\n", convertion );}
        if (menuselection == 4) {FntPrint(">> Return to Custom night menu\n\n");}
        else {FntPrint("   Return to Custom night menu\n\n");}
        //Maybe put end AM
    }
    if (advancedmenu == 1) {
        FntPrint("   Custom\n\n   Night\n\n\n");  // print time
        FntPrint("   Advanced Settings Menu\n\n\n");

        if (menuselection == 1) {FntPrint(">> Cooldown FBCFo : %d %d %d %d\n\n", freddylocationframelock, bonnielocationframelock, chicalocationframelock, foxylocationframelock );}
        else {FntPrint("   Cooldown of animatronics : ...\n\n" );}
        if (menuselection == 2) {FntPrint(">> Set default usage %d\n\n", defaultusage );}
        else {FntPrint("   Set default usage %d\n\n", defaultusage );}
        if (menuselection == 3) {FntPrint(">> Foxy Locked duration %d seconds\n\n", foxylockeduration);}
        else {FntPrint("   Foxy Locked duration %d seconds\n\n", foxylockeduration);}
        if (menuselection == 4) {FntPrint(">> Return to Custom night menu\n\n");}
        else {FntPrint("   Return to Custom night menu\n\n");}
    }
    if (extramenu == 1) {
        FntPrint("   Extra\n\n   Menu\n\n\n");  // print time

        if (menuselection == 1) {FntPrint(">> Enable phone guy ? %s\n\n", enablephoneguystr);}
        else {FntPrint("   Enable phone guy ? %s\n\n", enablephoneguystr);}

        if (menuselection == 2) {FntPrint(">> Unlocks menu\n\n");}
        else {FntPrint("   Unlocks menu\n\n");}

        if (menuselection == 3) {FntPrint(">> Info screen\n\n");}
        else {FntPrint("   Info screen\n\n");}

        if (menuselection == 4) {FntPrint(">> Two Player Mode : %s\n\n", twoplayermodestr);}
        else {FntPrint("   Two Player Mode : %s\n\n", twoplayermodestr);}

        if (menuselection == 5) {FntPrint(">> Return to main menu\n\n");}
        else {FntPrint("   Return to main menu\n\n");}

        if (activatedmenudebug == 1) {
            if (menuselection == 6) {FntPrint(">> Toggle weird night\n\n");}
            else {FntPrint("   Toggle weird night\n\n");}
        }
    }
    if (infoscreen == 1) {
        FntPrint("            Information Screen\n\n");

        FntPrint("    Five Night at Freddy's has been \n   released by Scott Cawton on 2014,\nand has been ported on the PS1 by Soeiz.\n            Thank you, Scott, \n For making our childhood a lot better.\n\n");

        FntPrint(">> Back                       V1.2.6 \n"); //Don't even need to do condition, there's only one
        /* It doesn't want :(
        FntPrint("                 What's New ?\n"); 
        FntPrint("V1.0.1 :\n   - added the help wanted screen\n   - changed a lot of images\n   - cleaned code\n   "); */
    }
    if (unlockssubmenu == 1) {
        FntPrint("   Unlocks\n\n   Menu\n\n\n");  // print time

        if (menuselection == 1) {FntPrint(">> Unlimited Power : %s\n\n", unlimitedpowerstr);}
        else {FntPrint("   Unlimited Power : %s\n\n", unlimitedpowerstr);}

        if (menuselection == 2) {FntPrint(">> Fast Nights : %s\n\n", fastnightsstr);}
        else {FntPrint("   Fast Nights : %s\n\n", fastnightsstr);}

        if (menuselection == 3) {FntPrint(">> Radar Map : %s\n\n", radarstr);}
        else {FntPrint("   Radar Map : %s\n\n", radarstr);}

        if (menuselection == 4) {FntPrint(">> Back \n\n");}
        else {FntPrint("   Back \n\n");}
    }
}
void gameoverprint(void) {
    FntPrint("\n\n      Congrats! You just... Died.\nGo on and press start to try your luck                 again !\n");
    if (activatedmenudebug == 1) {
        FntPrint("             Killer : %d",deadfrom);
    }
}
void controllerinput(void) {
    if (charge > 0) {
        if (camera == 0) {
            if(pad & PADLup || pad >> 16 & PADLup && twoplayermode == 1) { //Up
                if (limiterbop == 1) {return;}
                if (MovVectorofficemiddle.vx > -65) {
                    SpuSetKey(SPU_ON, SPU_07CH);
                    limiterbop = 1; 
                }
            }
            if(!(pad & PADLup || pad >> 16 & PADLup && twoplayermode == 1)) {limiterbop = 0;}

            if(pad & PADRdown || pad >> 16 & PADRdown && twoplayermode == 1) { //Cross
                if (limiter3 == 1) {return;}
                doorFuncX();
            }
            if(!(pad & PADRdown || pad >> 16 & PADRdown && twoplayermode == 1)) {limiter3 = 0;}

            if(pad & PADRright || pad >> 16 & PADRright && twoplayermode == 1) { //Circle
                if (limiter2 == 1) {return;}
                LightFunc();
            }
            if(!(pad & PADRright || pad >> 16 & PADRright && twoplayermode == 1)) {limiter2 = 0;}

            if (pad & PADstart || pad >> 16 & PADstart && twoplayermode == 1) {returnframes++;}
            if (!(pad & PADstart || pad >> 16 & PADstart && twoplayermode == 1)) {
                if (returnframes != 0) {
                    returnframes = 0;
                    returnbasevolume = 0x1800;
                    SpuSetVoiceVolume(4, returnbasevolume, returnbasevolume);
                }
            }
        }

        if(pad & PADR1 || pad >> 16 & PADR1 && twoplayermode == 1) { //R1
            if (camlimiter == 1) {return;}
            CameraFunc();
        }
        if(!(pad & PADR1 || pad >> 16 & PADR1 && twoplayermode == 1)) {camlimiter = 0;}
    }

    //Left
    if(pad & PADLleft || pad >> 16 & PADLleft && twoplayermode == 1) {doorFunc(0);}
    //Right
    if(pad & PADLright || pad >> 16 & PADLright && twoplayermode == 1) {doorFunc(1);}        
}
void animatronicFunc(int init) {
    if (init == 1) {
        if (night == 1 && FrameCounter == 0) { //Setting difficulties
            freddydifficulty = 0;
            bonniedifficulty = 0;
            chicadifficulty = 0;
            foxydifficulty = 0;
        }
        if (night == 2 && FrameCounter == 0) { 
            freddydifficulty = 0;
            bonniedifficulty = 3;
            chicadifficulty = 1;
            foxydifficulty = 1;
        }
        if (night == 3 && FrameCounter == 0) { 
            freddydifficulty = 1;
            bonniedifficulty = 0;
            chicadifficulty = 5;
            foxydifficulty = 2;
        }
        if (night == 4 && FrameCounter == 0) { 
            freddydifficulty = 1 + (Ran(3) - 1); //Meaning that we can get from 0~2 with 1~3 - 1
            bonniedifficulty = 2;
            chicadifficulty = 4;
            foxydifficulty = 6;
        }
        if (night == 5 && FrameCounter == 0) { 
            freddydifficulty = 3;
            bonniedifficulty = 5;
            chicadifficulty = 7;
            foxydifficulty = 5;
        }
        if (night == 6 && FrameCounter == 0) { 
            freddydifficulty = 4;
            bonniedifficulty = 10;
            chicadifficulty = 12;
            foxydifficulty = 16;
        }
        if (weirdnight == 1) {
            freddydifficulty = 0;
            bonniedifficulty = 0;
            chicadifficulty = 0;
            foxydifficulty = 0;
        }
        if (hellnight) {
            freddydifficulty = 20;
            bonniedifficulty = 20;
            chicadifficulty = 20;
            foxydifficulty = 20;
            FrameCounterlimit = 21600; //It basically do 6 minutes
        }
    } else {
        if (activatedmenudebug == 0 && weirdnight == 0) {
            if (AM == 2 && FrameCounter == 0) { //Apparently, their AI level increases at these hours 
                bonniedifficulty++;
                chicadifficulty++;
                foxydifficulty++;
            }
            if (AM == 3 && FrameCounter == 0 || AM == 4 && FrameCounter == 0) {
                bonniedifficulty++;
                if (night != 5) {
                    bonniedifficulty++;
                }
                chicadifficulty++;
                foxydifficulty++;
            }  
    }

    if (charge > 0) {
        if (bonnieDoor == 1) {
                if (bonnieDoorinit == 0) {
                    if (light1 == 1) {LightFunc();}
                    bonnieDoorinit++;
                }
                if (light1 == 1 && noisedoorbonnie == 0) {
                    noisedoorbonnie = 1;
                    SpuSetKey(SPU_ON,SPU_05CH);
                }
                if (bonnielocation == 8) {
                    if (doorclosedL == 1) {
                        if (light1 == 1) {LightFunc();}
                        bonnieDoor = 0;
                        bonnielocation = 1;
                        blockedanimatronic++;
                        noisedoorbonnie = 0;
                    } else {
                        if (light1 == 1) {LightFunc();}
                        cantdoorL = 1;
                        cantlightL = 1;
                        deadfrom = 2;
                    }
                }
        } 
        if (chicaDoor == 1) {
                if (chicaDoorinit == 0) {
                    if (light2 == 1) {LightFunc();}
                    chicaDoorinit++;
                }
                if (light2 == 1 && noisedoorchica == 0) {
                    noisedoorchica = 1;
                    SpuSetKey(SPU_ON,SPU_05CH);
                }
                if (chicalocation == 9) {
                    if (doorclosedR == 1 ) {
                        if (light2 == 1) {LightFunc();}
                        chicaDoor = 0;
                        chicalocation = 1;
                        blockedanimatronic++;
                        noisedoorchica = 0;
                    } else {
                        if (light2 == 1) {LightFunc();}
                        cantdoorR = 1;
                        cantlightR = 1;
                        deadfrom = 3;
                    }
                }
        } 

        if (isalreadydead == 1) {
                lastsecondsframes--;
                if (camera == 0) {lastsecondsframes = 0;}
                if (lastsecondsframes == 1001) {
                    //Sound moaning ? 
                }
                if (lastsecondsframes == 480) {
                    //Second moaning ?
                }
                if (lastsecondsframes == 0) {
                    dead = 1;
                }
        }
        if (isalreadydeadlow == 1) { //Usually for freddy only
                if (camera == 0) {
                    dead = 1;
                    deadfrom = 1;
                }
        }

        freddylocationframe--; 
        bonnielocationframe--;
        chicalocationframe--;
        if (ranfoxy == 0) {
            foxylocationframe--;
        }

        if (freddylocationframe < 0 && freddydifficulty != 0) {
            Ran(20); //Roll time !!!!!!!
            if (freddydifficulty > RAN && isalreadydeadlow == 0) { //If freddy's AI level is superior to the current RAN, ...
                if (freddylocation == 5) {
                    freddyanticipation = 1;
                } else {
                    if (camera == 0) {
                        freddylocation++;
                        noisefootstepF = 1;
                    }
                }
            }
            if (night == 7) {if(hellnight == 1) {freddylocationframe = 92;} else {freddylocationframe = 46;}} else {freddylocationframe = freddylocationframelock;}
            if (freddylocation > 7) { //7 (final animatronic's pos) is when he's supposed to either kill you, or...
                freddylocation = 4; //Return
                blockedanimatronic++;
                noisefootstepF = 1;
            }
        }
        if (bonnielocationframe < 0 && bonniedifficulty != 0) {
            Ran(20);
            if (bonniedifficulty > RAN) {
                if (bonnielocation < 8) {
                    bonnieonetimeskip = 0;
                    bonnielocation++;  
                    if (bonnieonetimeskip == 0) {
                        Ran(bonnielocation);
                        if (bonnielocation == 1 && RAN%2 == 0) {bonnielocation++;}
                        if (bonnielocation == 2 && RAN%2 != 0) {bonnielocation++;}
                        if (bonnielocation == 3 && RAN%2 != 0) {bonnielocation++;}
                        if (bonnielocation == 4 && RAN%2 == 0) {bonnielocation++;}
                        if (bonnielocation == 5 && RAN%2 == 0) {bonnielocation++;}   
                        bonnieonetimeskip = 1; //It's for making them skip certain locations, like in the OG Game. 
                    } 
                    noisefootstep = 1;
                    noisefootstepanimatronic = 1;
                }else {
                    if (deadfrom != 2) {bonnielocation = 1;}
                }
            }   
            if (night == 7) {if(hellnight == 1) {bonnielocationframe = 149;} else {bonnielocationframe = 74;}} else {bonnielocationframe = bonnielocationframelock;}
        }
        if (chicalocationframe < 0 && chicadifficulty != 0) {
            Ran(20);
            if (chicadifficulty > RAN) {
                if (chicalocation < 9) {
                    chicaonetimeskip = 0;
                    chicalocation++;  
                    if (chicaonetimeskip == 0) {
                        Ran(chicalocation);
                        if (chicalocation == 1 && RAN%2 != 0) {chicalocation++;}
                        if (chicalocation == 2 && RAN%2 == 0) {chicalocation++;}
                        if (chicalocation == 3 && RAN%2 != 0) {chicalocation++;}
                        if (chicalocation == 4 && RAN%2 == 0) {chicalocation++;}
                        if (chicalocation == 5 && RAN%2 == 0) {chicalocation++;} 
                        chicaonetimeskip = 1; 
                    }
                    noisefootstep = 1;
                    noisefootstepanimatronic = 2;
                } else {
                    if (deadfrom != 2) {chicalocation = 1;}
                }
            }   
            if (night == 7) {if(hellnight == 1) {chicalocationframe = 150;} else {chicalocationframe = 75;}} else {chicalocationframe = chicalocationframelock;}
            
            if (chicalocation > 9) {
                chicalocation = 1;
            }
        }

        if (camera == 1 && foxylocation < 3) { //"C" only and not "1C" bcs there's only one cam where the letter C is
            foxylocked = 1;
            if (night == 7) {if(hellnight == 1) {Ran(8);} else {Ran(4);}} else {Ran(foxylockeduration);} //Normally, this would be 16. Welp, now it is ! Old value : 8 (taken for the HELL NIGHT)
            ranfoxy = RAN * 60; //FPS
        }
        if (foxylocked == 1) {
            ranfoxy--;
        }
        if (ranfoxy == 0) {foxylocked = 0;}
        if (foxylocationframe < 0 && foxydifficulty != 0) {
            Ran(20);
            if (foxydifficulty > RAN && foxylocation != 3) {foxylocation++;}   
            if (night == 7) {if(hellnight == 1) {foxylocationframe = 151;} else {foxylocationframe = 76;}} else {foxylocationframe = foxylocationframelock;}
            
            if (foxylocation > 4) {return;}
        }
        }
    }
}
void screamer(void) {
    if (camera == 1) {
        CameraFunc();
    }  
    screamerframes--;
    
    if (spriteframes == 0) {
        spritesheet++;
        if (deadfrom == 3) {
            switch(spritesheet) {
                case 1:
                        LoadTexture(_binary_tim_screamers_jumpC_tim_start, &jumpscare);
                break;
                case 2:
                        LoadTexture(_binary_tim_screamers_jumpC2_tim_start, &jumpscare);
                break;
                case 3:
                        LoadTexture(_binary_tim_screamers_jumpC3_tim_start, &jumpscare);
                break;
                case 4:
                        LoadTexture(_binary_tim_screamers_jumpC4_tim_start, &jumpscare);
                break;
                case 5:
                        LoadTexture(_binary_tim_screamers_jumpC5_tim_start, &jumpscare);
                break;
                case 6:
                        LoadTexture(_binary_tim_screamers_jumpC4_tim_start, &jumpscare);
                break;
                case 7:
                        LoadTexture(_binary_tim_screamers_jumpC3_tim_start, &jumpscare);
                break;
                case 8:
                        LoadTexture(_binary_tim_screamers_jumpC2_tim_start, &jumpscare);
                break;
                case 9:
                        LoadTexture(_binary_tim_screamers_jumpC_tim_start, &jumpscare);
                break;
                case 10:
                    SpuSetKey(SPU_OFF, SPU_06CH);
                    menu = 3;
                break;
            }
        }
        if (deadfrom == 2) {
            switch(spritesheet) {
                case 1:
                        LoadTexture(_binary_tim_screamers_jumpB2_tim_start, &jumpscare);
                break;
                case 2:
                        LoadTexture(_binary_tim_screamers_jumpB3_tim_start, &jumpscare);
                break;
                case 3:
                        LoadTexture(_binary_tim_screamers_jumpB4_tim_start, &jumpscare);
                break;
                case 4:
                        LoadTexture(_binary_tim_screamers_jumpB5_tim_start, &jumpscare);
                break;
                case 5:
                        LoadTexture(_binary_tim_screamers_jumpB6_tim_start, &jumpscare);
                break;
                case 6:
                        LoadTexture(_binary_tim_screamers_jumpB7_tim_start, &jumpscare);
                break;
                case 7:
                        LoadTexture(_binary_tim_screamers_jumpB4_tim_start, &jumpscare);
                break;
                case 8:
                        LoadTexture(_binary_tim_screamers_jumpB3_tim_start, &jumpscare);
                break;
                case 9:
                        LoadTexture(_binary_tim_screamers_jumpB2_tim_start, &jumpscare);
                break;
                case 10:
                    SpuSetKey(SPU_OFF, SPU_06CH);
                    menu = 3;
                break;
            }
        }
        if (deadfrom == 1) {
            if (blackoutinit == 0) { //Special, knock you out pretty quickly
                switch(spritesheet) {
                    case 1:
                            LoadTexture(_binary_tim_screamers_jumpF_tim_start, &jumpscare);
                    break;
                    case 2:
                            LoadTexture(_binary_tim_screamers_jumpF2_tim_start, &jumpscare);
                    break;
                    case 3:
                            LoadTexture(_binary_tim_screamers_jumpF3_tim_start, &jumpscare);
                    break;
                    case 4:
                            LoadTexture(_binary_tim_screamers_jumpF4_tim_start, &jumpscare);
                    break;
                    case 5:
                            LoadTexture(_binary_tim_screamers_jumpF5_tim_start, &jumpscare);
                    break;
                    case 6:
                            LoadTexture(_binary_tim_screamers_jumpF6_tim_start, &jumpscare);
                    break;
                    case 7:
                        SpuSetKey(SPU_OFF, SPU_06CH);
                        menu = 3;
                    break;
                }
            } else {
                if (spritesheet == 1) {
                    LoadTexture(_binary_tim_screamers_jumpF20_tim_start, &jumpscare);
                }
                if (spritesheet == 2) {
                    LoadTexture(_binary_tim_screamers_jumpF21_tim_start, &jumpscare);
                }
                if (spritesheet == 3) {
                    LoadTexture(_binary_tim_screamers_jumpF22_tim_start, &jumpscare);
                }
                if (spritesheet == 4) {
                    LoadTexture(_binary_tim_screamers_jumpF24_tim_start, &jumpscare);
                }
                if (spritesheet == 5) {
                    LoadTexture(_binary_tim_screamers_jumpF25_tim_start, &jumpscare);
                }
                if (spritesheet == 6) {
                    LoadTexture(_binary_tim_screamers_jumpF26_tim_start, &jumpscare);
                }
                if (spritesheet == 7) {
                    SpuSetKey(SPU_OFF, SPU_06CH);
                    menu = 3;
                }
            }
        }
        if (deadfrom == 4) {
            if (spritesheet == 1) {
                LoadTexture(_binary_tim_screamers_jumpFO_tim_start, &jumpscare);
            }
            if (spritesheet == 2) {
                LoadTexture(_binary_tim_screamers_jumpFO2_tim_start, &jumpscare);
            }
            if (spritesheet == 3) {
                LoadTexture(_binary_tim_screamers_jumpFO3_tim_start, &jumpscare);
            }
            if (spritesheet == 4) {
                LoadTexture(_binary_tim_screamers_jumpFO4_tim_start, &jumpscare);
            }
            if (spritesheet == 5) {
                LoadTexture(_binary_tim_screamers_jumpFO5_tim_start, &jumpscare);
            }
            if (spritesheet == 6) {
                SpuSetKey(SPU_OFF, SPU_06CH);
                menu = 3;
            }
        }
        if (deadfrom == 2 || deadfrom == 3) {spriteframes = 3;} else {spriteframes = 4;}
        
    } else {spriteframes--;}
    makepoly(14);
    if (screamerframes == 46) {
        SpuSetKey(SPU_OFF, SPU_ALLCH);
        SpuSetKey(SPU_ON, SPU_06CH);
    }
    if (screamerframes == 0) {
        menu = 3;
    }
}
void doorFunc(int number) {door = number;}

void LightFunc(void) {
    if (limiter2 == 0) {
        if (cantlight == 0) {
            if (door == 0) {
                if (cantlightL == 0) {
                    light1++;
                    if (light1 == 1) {
                        light2 = 0;
                        LoadTexture(_binary_tim_office_officeRIGHT_tim_start, &officeRIGHT);
                        SpuSetKey(SPU_ON, SPU_01CH);
                        if (bonnieDoor == 0) {
                            LoadTexture(_binary_tim_office_officeLEFTlight_tim_start, &officeLEFTlight);
                        } else {
                            LoadTexture(_binary_tim_office_officeLEFTlightbonnie_tim_start, &officeLEFTlightbonnie);
                        }
                    }
                    if (light1 >= 2) {
                        light1 = 0;
                        SpuSetKey(SPU_OFF, SPU_01CH);
                        LoadTexture(_binary_tim_office_officeLEFT_tim_start, &officeLEFT);
                    }   
                } else {jamlight = 1;}
            }
            if (door == 1) {
                if (cantlightR == 0) {
                    light2++;
                    if (light2 == 1) {
                        light1 = 0;
                        LoadTexture(_binary_tim_office_officeLEFT_tim_start, &officeLEFT);
                        SpuSetKey(SPU_ON, SPU_01CH);
                        if (chicaDoor == 0) {
                            LoadTexture(_binary_tim_office_officeRIGHTlight_tim_start, &officeRIGHTlight);
                        } else {
                            LoadTexture(_binary_tim_office_officeRIGHTlightchica_tim_start, &officeRIGHTlightchica);
                        }
                    }
                    if (light2 >= 2) {
                        light2 = 0;
                        SpuSetKey(SPU_OFF, SPU_01CH); 
                        LoadTexture(_binary_tim_office_officeRIGHT_tim_start, &officeRIGHT);
                    } 
                } else {jamlight = 1;}
            }
        } else {jamlight = 1;}
        limiter2 = 1;
    }
}
void doorFuncX(void) {
    if (limiter3 == 0) {
        if (cantdoor == 0) {
            if (door == 0) {
                if (cantdoorL == 0) {  
                    SpuSetKey(SPU_ON, SPU_00CH);
                    doorclosedL++;
                    if (doorclosedL == 1) {
                    }
                    if (doorclosedL >= 2) {
                        doorclosedL = 0;
                    }
                } else {jamlight = 1;}
            }
            if (door == 1) {
                if (cantdoorR == 0) {
                    SpuSetKey(SPU_ON, SPU_00CH);
                    doorclosedR++;
                    if (doorclosedR == 1) {
                    }
                    if (doorclosedR >= 2) {
                        doorclosedR = 0;
                    }  
                } else {jamlight = 1;}
            }
        } else {jamlight = 1;}
        limiter3 = 1; 
    }
}
void CameraFunc(void) {
    if (camlimiter == 0) {
        if (cooldowncamera == 0) {
            camera++;
            if (camera == 1) {
                SpuSetKey(SPU_OFF, SPU_02CH);
                SpuSetKey(SPU_ON, SPU_02CH);

                light1 = 0; //Disable lights
                light2 = 0;
                LoadTexture(_binary_tim_office_officeRIGHT_tim_start, &officeRIGHT);
                LoadTexture(_binary_tim_office_officeLEFT_tim_start, &officeLEFT);
                SpuSetKey(SPU_OFF, SPU_01CH);

                if (cantdoorL == 1 || cantdoorR == 1) {isalreadydead = 1;}

                SpuSetVoiceVolume(3, 0x900, 0x900); //Lower down volume of officesound
            }
            if (camera >= 2) {
                camera = 0;
                SpuSetKey(SPU_ON, SPU_02CH);

                SpuSetVoiceVolume(3, 0x1400, 0x1400); //Higher up volume of officesound
            }
            cooldowncamera = 15;
        }
    }
    camlimiter = 1;
}
void lightsout(void) {
    doorFunc(0);
    if (doorclosedL == 1)
    {
        SpuSetKey(SPU_ON, SPU_00CH);
        doorclosedL = 0;
    }
    doorFunc(1);
    if (doorclosedR == 1)
    {
        SpuSetKey(SPU_ON, SPU_00CH);
        doorclosedR = 0;
    }
    SpuSetKey(SPU_OFF, SPU_ALLCH);
    if (camera == 1) {
        CameraFunc();
    }
    islightsout = 1;
}
void gamevictory(void) {
    SpuSetKey(SPU_OFF, SPU_ALLCH);
    if (doorclosedL == 1)
    {
        doorFunc(0);
        doorFuncX();
    }
    if (doorclosedR == 1)
    {
        doorFunc(1);
        doorFuncX();
    }
    if (camera == 1) {
        CameraFunc();
    }

    if (light1 == 1) {door = 0; LightFunc();}

    if (light2 == 1) {door = 1; LightFunc();}

    usage = 0;

    timeoncam = timeoncam / 60; //Divide the var on seconds
    if (timeoncam >= 0 && timeoncam < 60) {timeoncam == 1000;}
    if (timeoncam >= 60 && timeoncam < 120) {timeoncam == 750;}
    if (timeoncam >= 120 && timeoncam < 180) {timeoncam == 500;}
    if (timeoncam >= 180) {timeoncam == 250;}

    powermanagementtotal = powermanagementtotal * 30;

    score = score + (50 * charge) + (200 * freddydifficulty) + (200 * bonniedifficulty) + (200 * chicadifficulty) + (200 * foxydifficulty) + (150 * blockedanimatronic) + timeoncam - powermanagementtotal;

    FrameCounter++;
}