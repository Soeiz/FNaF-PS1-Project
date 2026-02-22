int sample = -1;

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
    extern u_char _binary_vag_freddy1short_vag_start;
    extern u_char _binary_vag_freddy2short_vag_start;
    extern u_char _binary_vag_CameraGlitching_vag_start;

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
        { &_binary_vag_freddy1short_vag_start,
            SPU_13CH, 0 },
        { &_binary_vag_freddy2short_vag_start,
            SPU_14CH, 0 },
        { &_binary_vag_CameraGlitching_vag_start,
            SPU_15CH, 0 }
    };

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

    void spuSetup(SpuCommonAttr * spuSettings) {
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
            {   22, 3632480,   1,     10 ,   28048, 40480, -1  } //Mixed ambiance 3
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

void XAsetup() {   
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

void MusicControl(void) {


    //Controlling CD Volume 
    CdlATV cd_vol;

    CdMix(&cd_vol);

    cd_vol.val0 = cd_vol.val2 = currentVolume;

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
}

void ChangeMusic(int music) {
  sample = music;
  filter.chan = soundBank.samples[sample].channel;
  filter.file = soundBank.samples[sample].file;
  CdControlF(CdlSetfilter, (u_char *)&filter);
  soundBank.samples[sample].cursor = 0;
}

void KnockingSoundFunc(void) {
    FoxyKnockFrames++;
    if ((FoxyKnockFrames - 1) % 40 == 1) {
        SpuSetKey(SPU_ON, SPU_09CH);
    }
    if (FoxyKnockFrames == 121) {
        FoxyKnock = false;
        FoxyKnockFrames = 0;
    }
}

void AmbianceMusics(void) {
    if (ambianceFrame != 0) { ambianceFrame--; return;}

    if (puppetMusicFrame == 0) {

        if (phoneGuyTalkingFrame > 0) { return;}

        Ran(15);

        if (ambianceChance > RAN) {

            ambianceChance = 1;

            switch(ambianceIndex) {
                case 1:

                    int condition = 0;

                    condition += (BonnieLocation > 3);
                    condition += (ChicaLocation > 4);
                    condition += (FoxyLocation > 1);

                    switch(condition) {
                        case 0:
                            //Originally currentVolume = 0 But I'll just apply another music to it
                            ambianceIndex = Ran(7);
                        break;
                        case 1:
                            currentVolume = 38;
                        break;
                        case 2:
                            currentVolume = 64;
                        break;
                        case 3:
                            currentVolume = 96;
                        break;
                    }


                    if (deadFrom == 1) { //IF FREDDY IS IN OFFICE
                        currentVolume = 128;
                    }

                    if (deadFrom == 1 || condition > 0) {
                        sample = 1;
                        ambianceFrame = 3302; //Ambiance 1
                    }

                break;
                case 2:
                    sample = 6;
                    ambianceFrame = 3912; //Ambiance 2
                break;
                case 3:
                    sample = 8;
                    ambianceFrame = 3000; //Ambiance 3
                break;
                case 4: //Will have to change
                    if (FoxyLocation < 2) {
                        sample = 18;
                        ambianceFrame = 510; //Foxy 

                    } else {
                        ambianceIndex = Ran(8);
                    }
                break;
                case 5:
                    sample = 5;
                    ambianceFrame = 1290; //Circus 
                break;
                case 6:
                    sample = 20;
                    ambianceFrame = 4440; //Mixed ambiance 1
                break;
                case 7:
                    sample = 21;
                    ambianceFrame = 4200; //Mixed ambiance 2
                break;
                case 8:
                    sample = 22;
                    ambianceFrame = 4980; //Mixed ambiance 3 (Ambiance 1 + other)

                    condition = 0;

                    condition += (BonnieLocation > 3);
                    condition += (ChicaLocation > 4);
                    condition += (FoxyLocation > 1);

                    switch(condition) {
                        case 0:
                            //Originally currentVolume = 0 But I'll just apply another music to it
                            ambianceIndex = Ran(7);
                        break;
                        case 1:
                            currentVolume = 38;
                        break;
                        case 2:
                            currentVolume = 64;
                        break;
                        case 3:
                            currentVolume = 96;
                        break;
                    }


                    if (deadFrom == 1) { //IF FREDDY IS IN OFFICE
                        currentVolume = 128;
                    }

                break;
            }

            ChangeMusic(sample);

        } else {

            ambianceFrame = 300;
            ambianceChance += 5;
            ambianceIndex++;
            if (ambianceIndex > 8) {ambianceIndex = 1;}
        } 
    } 
}

void PhoneGuyFunc(void) {

    if (hellNight) {

        if (FrameCounter == 10 || FrameCounter == 3600 || FrameCounter == 7200 || FrameCounter == 10800 || FrameCounter == 14400) {

            isPhoneGuyTalking = 2160;

            ChangeMusic(13);

            //This is for indicating the hour, since that single hour is 6 hours IG
        }

        return;
    }
    if (isPhoneGuyEnabled && battery > 0 && menu == 3) {


        if (inCustomNight) {
            if (rizzingF) {
                
                phoneGuyTalkingFrameCONST = 2780;

                phoneGuyTalkingFrame = phoneGuyTalkingFrameCONST;

                ChangeMusic(15);

                isPhoneGuyEnabled = false;

                return;   
            }
        }

        switch(night) {
            case 1:
                phoneGuyTalkingFrameCONST = 12060;
                sample = 9;
            break;
            case 2:
                phoneGuyTalkingFrameCONST = 5880;
                sample = 10;
            break;
            case 3:
                phoneGuyTalkingFrameCONST = 4080;
                sample = 11;
            break;
            case 4:
                phoneGuyTalkingFrameCONST = 3540;
                sample = 12;
            break;
            case 5:
                phoneGuyTalkingFrameCONST = 2160;
                sample = 13;
            break;
        }

        phoneGuyTalkingFrame = phoneGuyTalkingFrameCONST;

        filter.chan = soundBank.samples[sample].channel;
        filter.file = soundBank.samples[sample].file;
        CdControlF(CdlSetfilter, (u_char *)&filter);
        soundBank.samples[sample].cursor = 0;

        isPhoneGuyEnabled = false;
    }

    if (phoneGuyTalkingFrame > 0) {phoneGuyTalkingFrame--;}

    if (phoneGuyTalkingFrameCONST - 1620 < phoneGuyTalkingFrame && !MutedCall && AM != 6) {
        polymutecall = (POLY_FT4 *)nextpri;                 
                
        RotMatrix(&RotVectormutecall, &PolyMatrixmutecall);    
        TransMatrix(&PolyMatrixmutecall, &MovVectormutecall);  
        ScaleMatrix(&PolyMatrixmutecall, &ScaleVectormutecall);
        
        SetRotMatrix(&PolyMatrixmutecall);                  
        SetTransMatrix(&PolyMatrixmutecall);                
        
        setClut(polymutecall, 960, 200);
  
        setRGB0(polymutecall, 108, 108, 108); 

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
            MutedCall = true;
            CdControlF(CdlStop,0);
            phoneGuyTalkingFrame = 0;
        }
    }
}

void NoiseFootstepFunc(void) {
    FootStepFrames++;

    int noise;

    switch(FootStepFrames) {
        case 1:
            if (FootstepAnimatronicNumber == 1) { //Bonnie
                noise = BonnieLocation * 600;
            }
            if (FootstepAnimatronicNumber == 2) { //Chica
                noise = ChicaLocation * 600; // chicalocation == 1 -> +300, == 7 -> +1400
            }

            SpuSetVoiceVolume(8, noise, noise);
            SpuSetKey(SPU_ON, SPU_08CH);
        break;
        
        case 60:
            SpuSetKey(SPU_ON, SPU_08CH);
            NoiseFootstep = false;
            FootStepFrames = 0;
            noise = 0;
        break;
    }
}

void NoiseFootstepFreddyFunc(void) {

    FootStepFrames++;

    int noise;

    noise = FreddyLocation * 1500;

    Ran(3);

    switch(RAN) {
        case 1:

            SpuSetVoiceVolume(13, noise, noise);

            SpuSetKey(SPU_ON, SPU_13CH);
        break;
        case 2:

            SpuSetVoiceVolume(14, noise, noise);

            SpuSetKey(SPU_ON, SPU_14CH);
        break;

    }

    FreddyNoiseFootstep = false;

}

void CameraGlitch(void) {
    if (cameraGlitchFrame > 0) {
        cameraGlitchFrame--;

        Ran(6);

        if (RAN == 1) {
            if (SpuGetKeyStatus(SPU_15CH) == SPU_OFF) {SpuSetKey(SPU_ON, SPU_15CH);}
        }
    }
}