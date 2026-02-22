//Reset the variables of the game.
//True for "real" reset, like turning off and on.
void resetGame(bool hardreset) {

    if (hardreset) {
        clearVRAM(0);

        SpuSetKey(SPU_OFF, SPU_ALLCH);

        LoadTexture(_binary_tim_menus_WARNING_tim_start,&warning);

        LoadTexture(_binary_tim_menus_STATIC_tim_start,&statictitle);

        page = 0;

        global_alpha = 127; //Every objects are affected by this. If 128, it will get ignored for "local" coloring.

        font_alpha = 255; //Font COLOR (255 = white)

        InAndOut_alpha = 0; //Used for fade out & fade in

        currentMenu[0] = 0;

        currentMenu[1] = 0;

        timer_frame_FFW_warning = 180;

        menu = 0;

        returnedInGame = false;

        blinkIcon = 0;

        XCoordinates = 10;

        newGameSelected = false;

        helpWantedPoster = false;

        timer_frame_FFW_warning = 180;

        global_alpha = 127;

        musicFrames = 3788;

        goldenFreddyPoster = false;
        goldenFreddyActivated = false;
        deadtogoldenfreddy = false;
        kaboom = false;
        goldenFreddyFrameUntilDeath = 0;

        menuScreenInit = false;

        FirstTimeLoading = true;

        hellNight = false;

        DebugActivated = false;
    }

    sprintf(curCam, "1A");

    sprintf(curCamName, "Show Room");

    NoLightInit = false;

    NoLightTOMusicBoxChance = 20;
    NoLightTOMusicBoxChanceFRAME = 0;

    MusicBoxInit = false;

    MusicBoxTOBlackOutChance = 20;
    MusicBoxTOBlackOutChanceFRAME = 0;
    FreddyGlowingFrame = 0;
    glowVar = 128;

    BlackOutInit = false;

    BlackOutTOJumpscareChance = 20;
    BlackOutTOJumpscareChanceFRAME = 0;

    isLightsOut = false;
    LightsOutPhase = 0;

    cantDoorL = false;
    cantDoorR = false;

    defaultUsage = 1;

    AM = 12;

    battery = 100;

    ChargeCounter = 596;

    FrameCounter = 0; 

    isAlreadyDead = false;

    isAlreadyDeadLow = false;

    dead = false;

    doorClosedL = false;

    doorClosedR = false;

    lightR = false;

    lightL = false;

    deadFrom = false;

    nightWon = false;

    nextNightFrame = 0;

    ScreamerSpriteFrameLength = 3;
    
    ScreamerSpriteSheet = 0;

    isPhoneGuyTalking = false;

    isPhoneGuyEnabled = true;

    phoneGuyTalkingFrame, phoneGuyTalkingFrameCONST = 0;

    MutedCall = false;

    NightTextFrame = 200;

    global_alpha = 128;

    InAndOut_alpha = 128;

    if (!inCustomNight) {
        FreddyDifficulty = 0;
        BonnieDifficulty = 0;
        ChicaDifficulty = 0;
        FoxyDifficulty = 0;

        FreddyLocationFrameLock = 181;
        BonnieLocationFrameLock = 298;
        ChicaLocationFrameLock = 299;
        FoxyLocationFrameLock = 301;

    }

    //Freddy

        FreddyLocation = 0;
        FreddyLocationFrame = 181;

        frameFreddyEnter = 60;
        FreddyAnticipation = false;
        FreddyNoiseFootstep = false;

    //Bonnie

        BonnieLocation = 0;
        BonnieLocationFrame = 298;

        noiseDoorBonnie = false;
        BonnieDoorInit = false;
        BonnieIsAtDoor = false;
        BonnieOneTimeSkip = false;

    //Chica

        ChicaLocation = 0;
        ChicaLocationFrame = 299;

        noiseDoorChica = false;
        ChicaDoorInit = false;
        ChicaIsAtDoor = false;
        ChicaOneTimeSkip = false;

    //Foxy

        FoxyLocation = 0;
        FoxyLocationFrame = 301;


        FoxyLockedFrames = 0;
        FoxyRunningFrames = 0;
        FoxyDrainPower = 1;
        FoxyWaitingToRun = 500;
        FoxyKnock = false;
        FoxyKnockFrames = 0;

    //Sparky (????????)

        SparkyLocation = 0;

    //Screamer related

        screamerFrame = 0;

        spriteFrame = 0; //When it reaches 0, a new sprite from the screamer appears.

        spriteSheet = 0;

    staticDeadFrames = 0;
    staticFrameSheet = 0;

    CdControlF(CdlPause,0);

}

void starting(void) {
    srand(seedRand * timesControllerPressed);

    if (!inCustomNight) {
        FreddyLocationFrameLock = 181;
        BonnieLocationFrameLock = 298;
        ChicaLocationFrameLock = 299;
        FoxyLocationFrameLock = 301;
        convertionFramesToAM = 60;
        customAM = 12;
        battery = 100;

        animatronicLeveling();

        FrameCounterlimit = 60;

    } else {

        if (!rizzingF) {

            isPhoneGuyEnabled = false;
            MutedCall = true;

        }

        AM = customAM;

        battery = customBattery;

        FrameCounterlimit = convertionFramesToAM;


    }

    if (isOnNight6) {
        isPhoneGuyEnabled = false;
        MutedCall = true;
    }

    FreddyLocationFrame = FreddyLocationFrameLock;
    BonnieLocationFrame = BonnieLocationFrameLock;
    ChicaLocationFrame = ChicaLocationFrameLock;
    FoxyLocationFrame = FoxyLocationFrameLock;
        
    FrameCounterlimit = FrameCounterlimit * 60; //60 seconds * 60 fps = 3600 frames, maybe it would cause issues with 30 fps ??

    CdControlF(CdlPause,0);

    if (FirstTimeLoading) {

        clearVRAM(1);

        LoadImageObject("OMID", &officeMIDDLE);

        LoadImageObject("OMIDNO", &officeMIDDLEnolight);

        LoadImageObject("GAMEOVER", &gameover);

        LoadImageObject("LAYOUT", &layout);

        LoadImageObject("DOORS", &doors);

        LoadImageObject("GOL", &officegoldenfreddy);

        LoadImageObject("STATIC", &statics);

        LoadImageObject("FRSNEAK", &freddysneak);

        CdControlF(CdlPause,0);
        CdSearchFile( &XAPos, loadXA);
        soundBank.offset = CdPosToInt(&XAPos.pos);
        XAsetup();

        FirstTimeLoading = false;
    }

    LoadTexture(_binary_tim_office_officeLEFT_tim_start, &officeLEFT);

    LoadTexture(_binary_tim_office_officeRIGHT_tim_start, &officeRIGHT);

    LoadTexture(_binary_tim_office_littlechica_tim_start, &officeRIGHTlightchica);

    LoadTexture(_binary_tim_office_text_powerleft_tim_start, &powerleft);

    LoadTexture(_binary_tim_office_text_usage_tim_start, &usage);

    LoadTexture(_binary_tim_office_text_usagebars_tim_start, &usagebars);

    LoadTexture(_binary_tim_AM_office_12_tim_start, &AMoffice);

    LoadTexture(_binary_tim_office_text_night_tim_start, &nightoffice);

    LoadTexture(_binary_tim_office_text_nightsnumber_tim_start, &nightnumberoffice);

    LoadTexture(_binary_tim_office_mutecall_tim_start, &mutecall);

    LoadTexture(_binary_tim_AM_FAM_tim_start, &fiveam); 

    LoadTexture(_binary_tim_AM_AM_tim_start, &fiveam); 

    LoadTexture(_binary_tim_rect_tim_start, &rect);

    SpuSetKey(SPU_ON, SPU_03CH);

    NightTextFrame = 200;

    if (rizzingF) {
        FreddyLocationFrameLock = 100; 

    }

    if (hellNight) {
        FreddyDifficulty = 20;
        BonnieDifficulty = 20;
        ChicaDifficulty = 20;
        FoxyDifficulty = 20;

        FoxyLocationFrameLock = 150;
        ChicaLocationFrameLock = 149;
        BonnieLocationFrameLock = 149;
        FreddyLocationFrameLock = 90; //I'm fast ASF boy

        AM = 5;

        convertionFramesToAM = 300;
        cheating = false;
        fastNights = false; //Don't care about radar ; Just want them to SUFFER
        unlimitedPower = false;

        FrameCounterlimit = 21600; //It basically do 6 minutes

    }

}

void timeFunc(void) {
    FrameCounter++;

    if (FrameCounter == 1) {
        switch(AM) {
            case 1:
                LoadTexture(_binary_tim_AM_office_1_tim_start, &AMoffice);
            break;
            case 2:
                LoadTexture(_binary_tim_AM_office_2_tim_start, &AMoffice);
            break;
            case 3:
                LoadTexture(_binary_tim_AM_office_3_tim_start, &AMoffice);
            break;
            case 4:
                LoadTexture(_binary_tim_AM_office_4_tim_start, &AMoffice);
            break;
            case 5:
                LoadTexture(_binary_tim_AM_office_5_tim_start, &AMoffice);
            break;
        }

    }

    if (FrameCounter == FrameCounterlimit && AM != 6) {
        AM++;
        if (AM == 13) {
            AM = 1;
        }

        FrameCounter = 0;
    }
}

void chargeFunc(void) {

    ChargeCounter -= currentUsage;

    //As the wiki says, it takes 0.1 % of a battery each X seconds after night 1. (https://technicalfnaf.fandom.com/wiki/Power_Mechanics_(Fnaf_1))

    switch(night) {
        case 2:
            if (FrameCounter % 360 == 1) { //Every 6 seconds
                ChargeCounter -= 59; //10% of a battery
            }
        break;
        case 3:
            if (FrameCounter % 300 == 1) { //Every 5 seconds
                ChargeCounter -= 59; //10% of a battery
            }
        break;
        case 4:
            if (FrameCounter % 240 == 1) { //Every 4 seconds
                ChargeCounter -= 59; //10% of a battery
            }
        break;
        default: //Englobes night 5 to 7
            if (FrameCounter % 180 == 1) { //Every 3 seconds
                ChargeCounter -= 59; //10% of a battery
            }
        break;
    }

    setUV4(polyusagebar, 152, 224, 152, 255, 152 + (20*currentUsage), 224, 152 + (20*currentUsage), 255); 
    VertPosusagebar[2].vx = 4 * currentUsage;
    VertPosusagebar[3].vx = 4 * currentUsage;

    currentUsage = defaultUsage + doorClosedL + doorClosedR + lightL + lightR + isOnCamera;

    if (ChargeCounter <= 0 && !unlimitedPower) {

        battery--;

        ChargeCounter = 596;
    }
}

void fanFunc(void) {

    if (fanFrame > 6) {fanFrame = 1;} else {fanFrame++;}


    if (!isOnCamera) {
        switch(fanFrame) {
            case 2:
                LoadTexture(_binary_tim_office_fan_1_tim_start, &fan);
            break;
            case 4:
                LoadTexture(_binary_tim_office_fan_2_tim_start, &fan);
            break;
            case 6:
                LoadTexture(_binary_tim_office_fan_3_tim_start, &fan);
            break;

        }
    }
}

void jamNoiseFunc(void) {

    jamNoiseFrame++;

    if (jamNoiseFrame == 1) {SpuSetKey(SPU_ON, SPU_12CH);}

    if (jamNoiseFrame == 5) {
        SpuSetKey(SPU_ON, SPU_12CH);
        jamNoise = false;
        jamNoiseFrame = 0;
    }
}

void CameraTriggerFunc(void) {

    if (deadtogoldenfreddy) {

        kaboom = true;

        achievements[8] = true;

        goldenfredied = true;

        MemoryCardSave();

        return;
    }


    if (cooldownSpamCamera > 0) {return;} else {cooldownSpamCamera = 15;}

    Ran(100);

    if (RAN == 1) {
        ITSME_PirateCove = true;
    } else {
        ITSME_PirateCove = false;
    }
    if (RAN == 2) {
        ITSME_EastHall = true;
    } else {
        ITSME_EastHall = false;
    }
    if (RAN == 3) {
        ITSME_WestHallCorner = true;
    } else {
        ITSME_WestHallCorner = false;
    }

    Ran(32769);

    if (RAN == 10) {goldenFreddyPoster = true;}

    

    isOnCamera = !isOnCamera;

    SpuSetKey(SPU_ON, SPU_02CH);

    if (isOnCamera) {


        lightL = lightR = false;

        if (goldenFreddyActivated) {goldenFreddyActivated = false; goldenFreddyPoster = false;}

        LoadTexture(_binary_tim_office_officeRIGHT_tim_start, &officeRIGHT);
        LoadTexture(_binary_tim_office_officeLEFT_tim_start, &officeLEFT);
        SpuSetKey(SPU_OFF, SPU_01CH);

        SpuSetVoiceVolume(3, 0x900, 0x900); //Lower down volume of officesound
    } else {

        if (isAlreadyDeadLow) {
            dead = true;
            deadFrom = 1;
        }

        SpuSetVoiceVolume(3, 0x1400, 0x1400); //Higher up volume of officesound
    }
}

void LightsOut(void) {
    SpuSetKey(SPU_OFF, SPU_ALLCH);

    if (doorClosedL){
        SpuSetKey(SPU_ON, SPU_00CH);
        doorClosedL = false;
    }

    if (doorClosedR){
        SpuSetKey(SPU_ON, SPU_00CH);
        doorClosedR = false;
    }

    if (isOnCamera) {
        CameraTriggerFunc();
    }
    if (lightL) {lightL = false;}

    if (lightR) {lightR = false;}

    isLightsOut = true;
}

void LightsOutFunc(void) {
    switch(LightsOutPhase) {
        case 1:
            if (!NoLightInit) {
                NoLightInit = true;

                LoadTexture(_binary_tim_office_officeLEFTnolight_tim_start, &officeLEFTnolight);//Loading office
                LoadTexture(_binary_tim_office_officeMIDDLEnolight_tim_start, &officeMIDDLEnolight); 
                LoadTexture(_binary_tim_office_officeRIGHTnolight_tim_start, &officeRIGHTnolight);
            }
            if (NoLightInit) {
                NoLightTOMusicBoxChanceFRAME++;

                if (NoLightTOMusicBoxChanceFRAME == 300) {
                    Ran(100); 
                    if (NoLightTOMusicBoxChance > RAN) {

                        LightsOutPhase++; //Move to music box 
                    } else {

                        NoLightTOMusicBoxChanceFRAME = 0;
                        NoLightTOMusicBoxChance += 20;

                        if (NoLightTOMusicBoxChance == 100) {
                            LightsOutPhase++; //Move to music box 
                        }   
                    }
                }


            }
        

        break;
        case 2:
            if (!MusicBoxInit) {
                MusicBoxInit = true;
                ChangeMusic(14);
            }
            if (MusicBoxInit) {
                MusicBoxTOBlackOutChanceFRAME++;

                if (MusicBoxTOBlackOutChanceFRAME == 300) {
                    Ran(100); 
                    if (MusicBoxTOBlackOutChance > RAN) {

                        LightsOutPhase++; //Move to BlackOut
                    } else {

                        MusicBoxTOBlackOutChanceFRAME = 0;
                        MusicBoxTOBlackOutChance += 20;

                        if (MusicBoxTOBlackOutChance == 100) {
                            LightsOutPhase++; //Move to music box 
                        }   
                    }
                }

                FreddyGlowingFrame++;
                if (FreddyGlowingFrame > 53) {FreddyGlowingFrame = 0;}

                if (FreddyGlowingFrame % 2 == 1) {
                    glowVar = 64;
                }
                if (FreddyGlowingFrame % 3 == 1) {
                    glowVar = 0;
                }
                if (FreddyGlowingFrame % 5 == 1) {
                    glowVar = 128;
                }
            }
        break;
        case 3:
            if (!BlackOutInit) {
                //Deactivate Everything
                CdControlF(CdlPause,0);

                SpuSetKey(SPU_ON, SPU_11CH);

                BlackOutInit = true;
            }
            if (BlackOutInit) {
                BlackOutTOJumpscareChanceFRAME++;

                if (BlackOutTOJumpscareChanceFRAME == 120) {
                    Ran(100);
                    if (BlackOutTOJumpscareChanceFRAME > RAN) {
                        dead = true;
                        deadFrom = 1;

                    } else {
                        BlackOutTOJumpscareChanceFRAME = 0;

                        Ran(7);
                        if (RAN == 1) {
                            NoiseFootstep = true;
                            FootstepAnimatronicNumber = 1;
                        } 
                    }
                }
            }
        break;
    }
}

void NightWonFunc(void) {

    if (office_alpha > 0) { office_alpha--; }

    nextNightFrame++;

    if (nextNightFrame < 240 && nextNightFrame > 120) {
        if (nextNightFrame %7 == 1) {
            MovVectorfiveam.vy--;
        }
    }
    if (nextNightFrame == 240) {LoadTexture(_binary_tim_AM_SAM_tim_start, &sixam); MovVectorfiveam.vy = 0;}
    if (nextNightFrame > 240 && nextNightFrame < 400) {
        if (nextNightFrame %15 == 1) {
            MovVectorfiveam.vy--;
        }
    }
    if (nextNightFrame == 400){
        MovVectorfiveam.vy--;

    }

    if (nextNightFrame < 819) {
        makepoly(10);

        if (nextNightFrame > 400) {


            //Achievements prints
           if (blinkIcon > 30) {

                FntPrint("\n\n\n\n\n\n\n\n\n\n\n\n\n\n");

                if (rizzingF) {
                    FntPrint("        Achievement \"Freddy\" Done!\n");
                    rizzingFDone = true;
                }

                if (hellNight) {
                    FntPrint("        Achievement \"Hell Night\" Done!\n");
                    hellNightDone = true;
                }
                if (FreddyDifficulty == 20 && BonnieDifficulty == 20 && ChicaDifficulty == 20 && FoxyDifficulty == 20) {
                    FntPrint("          Achievement \"4/20\" Done!");
                    fourTwentyDone = true;
                }
            }
        }
    }

    if (nextNightFrame > 819) {

        if (customBattery == 99 && customAM == 5 && convertionFramesToAM == 5) {

            resetGame(0);
            nextNightFrame = 0;
            menu = 2;
            night = 7;
            hellNight = true;
        }

        if (night < 5 && !inCustomNight) {

            night++;

            nextNightFrame = 0;
            resetGame(0);
            menu = 2; //Load Directly into next night

            if (night > bestNight) {bestNight = night;}

            MemoryCardSave();

        } else { //If night is 5 / 6 / Custom Night

            

            if (nextNightFrame == 820) {

                if (night == 5) {if (Night6State == 0) {Night6State++;}}

                if (night == 6) {if (Night6State == 1) {Night6State++;}}

                if (night != 7) {Ran(250);}

                if (hellNight) {Ran(10);}

                if (RAN == 1) {  //14 normal, 19 funky
                    ChangeMusic(19);
                    funky = true;

                    limiterPadStart = false;

                } else {
                    ChangeMusic(14);
                    global_alpha = 0;
                    limiterPadStart = false;
                }

            }
            makepoly(11);

            if (hellNight) {
                FntPrint(" Hey ! I never tested the night.\n Glad you did it for me ! \n Anyway, Thank you for playing \n This port of FNAF on Playstation!\n (now you can go complete your \n set on FNAF 2 and 3)");
                ChangeFontColor(250,100,100);
            }

            if (limiterPadStart) {
                if (global_alpha != 0) {global_alpha -= 2;} else {
                    resetGame(0); 
                    menu = 1; 

                    if (night == 7) {night = 6;}

                    returnedInGame = true;
                    LoadTexture(_binary_tim_menus_STATIC_tim_start,&statictitle);
                    ChangeMusic(0);
                    musicFrames = 0;
                    ChangeFontColor(255,255,255);

                    MemoryCardSave();
                }
            } else {
                if (global_alpha != 128) {global_alpha += 2;}
            }

            if (pad & PADstart && !limiterPadStart) {
                limiterPadStart = true;
            }
        }
    }
}

void DeathByCrash(void) {
    SpuSetKey(SPU_OFF, SPU_ALLCH);
    SpuSetKey(SPU_ON, SPU_9CH);

    cantDoorL = true;
    cantDoorR = true;

    deadtogoldenfreddy = true;

    LoadImageObject("GOLF", &freddy);

}

void CheckForSpecialLevels(void) {
    if (FreddyDifficulty == 20 && BonnieDifficulty == 0 && ChicaDifficulty == 0 && FoxyDifficulty == 0) {
        rizzingF = true;
    }
}

void CheckAchievements(void) {
    if (cheating) {return;}

    if (night < 7 && !inCustomNight) {
        achievements[night-1] = true;
    }

    if (isOnNight6) {Night6State = 2; achievements[7] = true;}

    if (inCustomNight) {

        if (FreddyDifficulty == 20 && BonnieDifficulty == 20 && ChicaDifficulty == 20 && FoxyDifficulty == 20) {
            achievements[6] = true;
        }

        if (rizzingF) {
            achievements[9] = true;
        }

    }


}