
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
void starting(void) {
  resetgame(0);
  SpuSetKey(SPU_ON, SPU_04CH);

  if (customnightactivated == 0) {
    freddylocationframe = 300;
    bonnielocationframe = 300;
    chicalocationframe = 300;
    foxylocationframe = 300;
    freddylocationframelock = 300;
    bonnielocationframelock = 300;
    chicalocationframelock = 300;
    foxylocationframelock = 300;
    foxylockeduration = 16;
    convertion = 60;
    customAM = 12;
    charge = 100;
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

void SaveGame() {

    MemCardDeleteFile(16*currentCard,SAVENAME);

    SAVEHDR header;

    header.id[0]='S'; header.id[1]='C'; // ID must always say SC
    header.type     = 0x11;                 // 1 frame icon
    header.size     = 1;                    // 1 block
        
    // Convert save title from ASCII to SJIS
    asc2sjis(SAVETITLE, header.title);
    
    // Copy icon's CLUT to the header
    memcpy(header.clut, saveIcon_clut, 32);

    // Open save block for writing. If it doesn't exist, create it.

    if (MemCardCreateFile(16*currentCard, SAVENAME, 1) == 0x07) { // Is memory card full?
        
        //return back
    }
    
    // Open the created file
    MemCardOpen(16*currentCard, SAVENAME, O_WRONLY);

    // Write the header
    MemCardWriteData((u_long*)&header, 128*0, 128);
    while(MemCardSync(1, &cardCmd, &slotResult[0]) == 0);
    
    // Write the icon frames
    MemCardWriteData((u_long*)&saveIcon_image, 128*1, 256);
    while(MemCardSync(1, &cardCmd, &slotResult[0]) == 0);

    // Write thingies
    MemCardWriteData((u_long*)&night, 128*3, 256);
    while(MemCardSync(1, &cardCmd, &slotResult[0]) == 0);
    
    //Close the created file
    MemCardClose();
}

void LoadGame() {
    MemCardOpen(16*currentCard, SAVENAME, O_RDONLY);

    night = MemCardReadData((u_long*)&night, 128*3, 128);
    while(MemCardSync(1, &cardCmd, &slotResult[0]) == 0);
    
    // Done, close file
    MemCardClose();
}
void Corrupt() {
    /*
        HELL IS COMING

        CORRUPT THE PLAYSTATION

        PREPARE FOR OUR ARRIVING

        WE'RE COMING FOR YOU, SON
    */
    memcpy(goldenfreddypixelGarbagething);


   loadFile = (char*)goldenfreddypixelGarbagething;
   CdSearchFile( &filePos, loadFile);
   dataBuffer = malloc( BtoS(filePos.size) * CD_SECTOR_SIZE );
   CdControl(CdlSetloc, (u_char *)&filePos.pos, CtrlResult);
   // Read data and load it to dataBuffer
   CDreadOK = CdRead( (int)BtoS(filePos.size), (u_long *)dataBuffer, CdlModeSpeed );
   CDreadResult = CdReadSync(0, 0);
   LoadTexture(dataBuffer, &officeMIDDLE); 

    LoadTexture(_binary_tim_office_officeLEFT_tim_start, &officeLEFT);
    LoadTexture(_binary_tim_office_officeRIGHT_tim_start, &officeRIGHT);
    LoadTexture(_binary_tim_FAM_tim_start, &fiveam); 
    LoadTexture(_binary_tim_AM_tim_start, &fiveam); 
    LoadTexture(_binary_tim_office_fan_1_tim_start, &fan);

}