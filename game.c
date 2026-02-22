/*

    Five Night at Freddy's 1 on the Playstation 1 

    Remade from scratch



    Report(s) : 

        TO FIX :
    
        TO FIX (PS1 related) :
            -


        FIXED ? : 
            - Night 7 where it doesn't matter what you pick as AI
            - CurrentUsage with bars act weird (Might not fix)
            - MemCardAccept mess with variables ??? (temp fix)


        TODO :

        
        OTHER :
            - Made with PsyQ + Nugget (https://github.com/ABelliqueux/nolibgs_hello_worlds)

            - Wanted to implement an "anticheat" system. But I think it'd be better to let people choose what they want to do : Earn it the good way, or the bad way. 
                (At least, I fixed problems the players were "cheesing")

    1.0.0
*/

#include "objects/constants.h"
#include "objects/basicFunctions.h"
#include "objects/images.h"
#include "objects/music-sounds.h"
#include "objects/AI.h"
#include "objects/MemoryCard.h"
#include "objects/otherFunctions.h"
#include "objects/controller.h"
#include "objects/printFuncs.h"


int main(void) {

    //controller
    TILE * PADL;                    // Tile primitives
    TILE * TRIGGERL;
    TILE * PADR;
    TILE * TRIGGERR;
    TILE * START, * SELECT;

    init();
    // Init CD system
    CdInit();
    // Init heap
    InitHeap((u_long *)ramAddr, sizeof(ramAddr));
    //Init SPU
    u_long spu_address;
    spuSetup(&spuSettings);
    // Init sound settings
    initSnd();
    //Memory card
    MemCardInit(0);
    MemCardStart();
    MemoryCardCheck();
    //Init Pad
    PadInit(0);

    resetGame(true);

    if (MemoryCardState == 2) {currentMenu[0] = 3;} //Meaning that it's the first time someone boots into fnaf ps1. 

    //Load every sounds
    for (u_short vag = 0; vag < VAG_NBR; vag++ ){
        vagsoundBank[vag].spu_address = setSPUtransfer(&vagsoundBank[vag]);
    }

    //Set music index
    int sample = -1;

    clearVRAM(0);

    LoadTexture(_binary_tim_menus_WARNING_tim_start,&warning);

    LoadTexture(_binary_tim_menus_STATIC_tim_start,&statictitle);

    LoadTexture(_binary_tim_menus_star_tim_start, &star);

    while(1) {  

        ClearOTagR(ot[db], OTLEN);
        
        pad = PadRead(0);
        
        MusicControl();
        imageAlphaControl();
        controllerInput();

        if (blinkIcon == 60) {blinkIcon = 0;} else {blinkIcon++;}

        switch(menu) {
            //Warning Screen
            case 0:
                makepoly(0);

                if (timer_frame_FFW_warning < 0) {
                    global_alpha = 0;
                } else {
                    timer_frame_FFW_warning--;
                }

                if (InAndOut_alpha == 0) {

                    menu = 1;

                    global_alpha = 128;
                }

            break;
            //Menu Screen
            case 1:
                seedRand++;

                if (musicFrames > 3788){
                    musicFrames = 0;
                    ChangeMusic(0);
                } else {musicFrames++;} //(Re)load the title music

                if (!menuScreenInit) { //Init
                    LoadImageObject("FREDDY", &freddy);

                    LoadImageObject("FREDDY2", &freddy2);
                    
                    LoadImageObject("GJFIV", &goodjob);

                    LoadImageObject("HWANTED", &helpwanted);

                    CdControlF(CdlPause,0);
                            
                    // Load XA file from cd
                    // Find XA file pos
                    CdSearchFile( &XAPos, loadXA);
                    // Set cd head to start of file
                    soundBank.offset = CdPosToInt(&XAPos.pos);
                    // Set cd XA playback parameters and pause cd
                    XAsetup();
                    // Keep track of XA Sample currently playing

                    menuScreenInit = true;
                    musicFrames = 3778;


                    // Temporary fixes because of MemCardAccept messing with me and vars 

                    FirstTimeLoading = true; 
                    XCoordinates = 10;

                } //After Init

                if (!helpWantedPoster) {
                    makepoly(1); //Freddy's Face

                    menuPrint();

                    menuSelectionFunc();
                }

                if (newGameSelected) {
                    if (global_alpha > 0) {
                        global_alpha -= 2;

                        ChangeFontColor(global_alpha*2,global_alpha*2,global_alpha*2);
                    } else {
                        helpWantedPoster = true; 
                        newGameSelected = false;
                    }
                }

                if (helpWantedPoster) {
                    makepoly(2);

                    if (HelpWantedFrame < 0) {
                        global_alpha = 0;
                    } else {
                        HelpWantedFrame--;

                        if (global_alpha != 127) { global_alpha = 127;}
                    }

                    if (global_alpha == 0 && InAndOut_alpha == 0) {

                        menu = 2;
                        
                        global_alpha = InAndOut_alpha = 128;

                        HelpWantedFrame = 300;

                        
                    }
                }
            break;
            //Loading / Starting night Screen
            case 2:

                if (inCustomNight) { CheckForSpecialLevels(); }

                if (DebugActivated) { 
                    if (global_alpha > 0) {global_alpha = 0;} 
                    isPhoneGuyEnabled = false;
                    MutedCall = true;
                }

                if (NightTextFrame == 199) {
                    SpuSetKey(SPU_ON, SPU_04CH);
                    CdControlF(CdlPause,0);

                    loadTextureNightAnnouncement();
                }

                if (NightTextFrame < 0) {
                    global_alpha = 0;

                } else {
                    NightTextFrame--;

                }

                if (InAndOut_alpha > 10) { //10, so it can show the loading image before starting loading
                    makepoly(3);

                    if (inCustomNight && blinkIcon > 30) {

                        if (hellNight) {FntPrint("\n\n\n\n\n\n\n\n\n\n\n\n\n\n              Hell Night");} else {FntPrint("\n\n\n\n\n\n\n\n\n\n\n\n\n\n             Custom Night");}

                    }
                } else {
                    makepoly(4);
                }

                if (InAndOut_alpha == 0) {

                    //FreddyDifficulty = 20;

                    //AM = 5;

                    //FrameCounter = FrameCounterlimit - 180;

                    if (FreddyDifficulty == 1 && BonnieDifficulty == 9 && ChicaDifficulty == 8 && FoxyDifficulty == 7) {
                        deadFrom = 1;
                        gotYou = true;
                        Screamer();
                    } else {
                        menu = 3;

                        starting();

                        //ChicaLocation = 8;

                    }

                    global_alpha = 128;

                    office_alpha = 128;
                }

                    
            break;
            //Gameplay Screen
            case 3:

                battery = 100;

                if (AM == 6 && FrameCounter == 0) {

                    CdControlF(CdlPause,0);

                    ChangeMusic(3);

                    nightWon = true;

                    LightsOut(); //Same thing as when there's no battery left

                    CheckAchievements();
                }

                if (kaboom) {
                    SpuSetKey(SPU_ON,SPU_06CH);

                    resetGame(true);
                    
                }


                if (nightWon) {NightWonFunc();}

                pathAIFunc();

                if (battery > 0 && !nightWon) {displayHUD(); InGamePrintFunc(); fanFunc(); animatronicActions();}

                if (!deadtogoldenfreddy) {
                    chargeFunc();

                    timeFunc();

                }

                if (NoiseFootstep) {NoiseFootstepFunc();}

                if (FreddyNoiseFootstep) {NoiseFootstepFreddyFunc();}

                if (dead) {Screamer();}

                if (battery < 1 && currentUsage > 0) {
                    CdControlF(CdlPause,0);
                    defaultUsage = 0;
                    ChangeMusic(4);
                    LightsOut();
                    LightsOutPhase = 1;
                }

                if (cooldownSpamCamera > 0) {cooldownSpamCamera--;}

                if (jamNoise) {jamNoiseFunc();}

                if (FoxyKnock) {KnockingSoundFunc();}

                if (!isLightsOut) { 

                    if (!hellNight) { AmbianceMusics(); }

                    PhoneGuyFunc();
                }

                CameraGlitch();

                if (isOnCamera) {

                    ControllerCameraFunction();

                    CameraSelectionDisplay();

                    makepoly(6);

                    if (isAlreadyDead) {animatronicWaitForCam();}


                } else {

                    if (goldenFreddyActivated) {

                        goldenFreddyFrameUntilDeath++;

                        Ran(2000);

                        if (goldenFreddyFrameUntilDeath - 60 > RAN) {
                            goldenFreddyActivated = false;
                            
                            DeathByCrash();
                        }

                    }

                    if (lightL || lightR) {
                        lightFlicker();
                    }

                    MoveFunction(); 

                    if (!isLightsOut) { 
                        ControllerOfficeFunction();

                    } else {

                        LightsOutFunc();

                    }
                    
                    if (!BlackOutInit && office_alpha > 0) {
                        makepoly(5);

                        setRGB0(polyofficeright, office_alpha, office_alpha, office_alpha); 
                        setRGB0(polyofficemiddle, office_alpha, office_alpha, office_alpha);          
                        setRGB0(polyofficeleft, office_alpha, office_alpha, office_alpha);   
                        setRGB0(rightdoor, office_alpha, office_alpha, office_alpha); 
                        setRGB0(leftdoor, office_alpha, office_alpha, office_alpha);     

                        if (office_alpha > 196) {
                            setRGB0(polyfan, 88 - office_alpha, 88 - office_alpha, 88 - office_alpha);   
                        } else {
                            setRGB0(polyfan, office_alpha, office_alpha, office_alpha);     
                        }

                    }
                }
            break;
            //Game Over Screen
            case 4:
                staticDeadFrames++;

                if (staticDeadFrames < 559) {
                    staticFrameSheet++;

                    makepoly(8);

                    if (staticFrameSheet == 8) {
                        staticFrameSheet = 0;
                        MovVectorstatic.vx -= 14;
                    } else {
                        MovVectorstatic.vx += 2;
                    }   
                }

                if (staticDeadFrames == 559) {
                    MovVectorstatic.vx = -40;

                    if (night == 1) {diedOnNight1 = true; achievements[10] = true; MemoryCardSave();}
                }

                if (staticDeadFrames > 559) {
                    makepoly(9);

                    if (pad & PADstart) {

                        if (FreddyDifficulty == 1 && BonnieDifficulty == 9 && ChicaDifficulty == 8 && FoxyDifficulty == 7) {
                            menu = 1;
                            FreddyDifficulty = 0;
                            BonnieDifficulty = 0;
                            ChicaDifficulty = 0;
                            FoxyDifficulty = 0;
                            musicFrames = 3788;
                        } else {
                            resetGame(0);
                            menu = 2;
                        }

                    }
                    if (pad & PADselect) {
                        menu = 1;
                        returnedInGame = true;
                    }
                }
            break;

            default:
                menu = 0; //We don't want the player to get locked
            break;
        }

        FntFlush(-1); //Draw
        display(); //Always here   
    }
    return 0;
}