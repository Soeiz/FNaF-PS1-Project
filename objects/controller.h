void controllerInput(void) {
    
    if (pad & PADstart || pad >> 16 & PADstart && twoPlayerMode == 1) {
        switch(menu) {
            case 0:
                timer_frame_FFW_warning = 0;
            break; //Warning Screen
            case 1:
                if (helpWantedPoster) {
                    srand(HelpWantedFrame); //I need this for random !§§

                    HelpWantedFrame = 0;

                }
            break; //Help Wanted Screen
        }

    }
}

void presetSelectionSet(void) {
    switch(presetSelector) {
        case 1:
            sprintf(presetSelectorStr,"Custom");
        break;

        case 2:
            sprintf(presetSelectorStr,"4 / 20");

            FreddyDifficulty = 20;
            BonnieDifficulty = 20;
            ChicaDifficulty = 20;
            FoxyDifficulty = 20;
        break;
    }
}
void menuSelectionFunc(void) {
    if (pad & PADLup) {
        if (!limiterPadUp) {
            if (menuSelection > 1) {
                menuSelection--;
            }
            else {
                menuSelection = menuSelectionMax;
            }
            //SpuSetKey(SPU_ON, SPU_03CH);
            limiterPadUp = true;
        }
        timesControllerPressed++;
    }
    if (pad & PADLdown) {
        if (!limiterPadDown) {
            if (menuSelection < menuSelectionMax) {
                menuSelection++;
            }
            else {
                menuSelection = 1;
            }
            //SpuSetKey(SPU_ON, SPU_03CH);
            limiterPadDown = true;
        }
        timesControllerPressed++;
    }
    if (!(pad & PADLright)) {limiterPadRight = false;}
    if (!(pad & PADLleft)) {limiterPadLeft = false;}
    if (!(pad & PADLdown)) {limiterPadDown = false;}
    if (!(pad & PADLup)) {limiterPadUp = false;}
    if (!(pad & PADstart)) {limiterPadStart = false;}
    if (!(pad & PADRdown)) {limiterPadCross = false;}
    if (!(pad & PADR1)) {limiterPadR1 = false;}
    if (!(pad & PADL1)) {limiterPadL1 = false;}

    switch(currentMenu[0]) {
        case 0:
            if (menuSelection == 1) {//"Starting" night
                if (pad & PADstart) {
                    if (limiterPadStart) {return;}
                    night = 1;
                    newGameSelected = true;
                    inCustomNight = false;
                    isOnNight6 = false;
                } 
            }

            if (menuSelection == 2) { //Continue nights
                if (pad & PADstart) {
                    if (limiterPadStart) {return;}

                    NightTextFrame = 300;

                    menu = 2;

                    inCustomNight = false;

                    isOnNight6 = false;

                    global_alpha = InAndOut_alpha = 128;

                    
                    SpuSetKey(SPU_ON, SPU_04CH);
                    CdControlF(CdlPause,0);

                    loadTextureNightAnnouncement();
                }//Or...

                //Activate debug !
                if (pad & PADRup && pad & PADRright && pad & PADR1 && pad & PADL2 && !DebugActivated) {
                    DebugActivated = true;
                    menuSelectionMax = menuSelectionMax + 1;

                    Night6State = 2;
                }
            }

            if (Night6State > 0) {

                if (menuSelection == 3) {
                    if (pad & PADstart) {
                        if (limiterPadStart) {return;}
                        NightTextFrame = 300;
                        menu = 2;

                        isOnNight6 = true;

                        inCustomNight = false;

                        global_alpha = InAndOut_alpha = 128;

                        
                        SpuSetKey(SPU_ON, SPU_04CH);
                        CdControlF(CdlPause,0);

                        loadTextureNightAnnouncement();
                    }
                }

                if (menuSelection == 4) { //EXTRA MENU
                    if (pad & PADstart) {
                        if (limiterPadStart) {return;}

                        currentMenu[0] = 1;
                        currentMenu[1] = 0;
                        menuSelection = 1;
                        
                        menuSelectionMax = 5;
                    }
                }
                
                if (menuSelection == 5) { //CUSTOM NIGHT MENU
                    if (pad & PADstart) {
                        if (limiterPadStart) {return;}

                        currentMenu[0] = 2;
                        menuSelection = 1;
                        menuSelectionMax = 5;
                        
                    }
                }

            } else {

                if (menuSelection == 3) { //EXTRA MENU
                    if (pad & PADstart) {
                        if (limiterPadStart) {return;}

                        currentMenu[0] = 1;
                        currentMenu[1] = 0;
                        menuSelection = 1;
                        
                        menuSelectionMax = 5;
                    }
                }
                
                if (menuSelection == 4) { //CUSTOM NIGHT MENU
                    if (pad & PADstart) {
                        if (limiterPadStart) {return;}

                        currentMenu[0] = 2;
                        menuSelection = 1;
                        menuSelectionMax = 5;
                        
                    }
                }

            }

        break;
        case 1:
            switch(currentMenu[1]) {
                case 0:
                    if (menuSelection == 1) { //Cheats Menu
                        if (pad & PADstart) {
                            if (limiterPadStart) { return; }

                            currentMenu[1] = 1;
                            menuSelection = 1;
                            menuSelectionMax = 4;
                        }
                    }
                    if (menuSelection == 2) { //Informations on the game
                        if (pad & PADstart) {
                            if (limiterPadStart) { return;}

                            currentMenu[1] = 2;
                            menuSelection = 1;
                            menuSelectionMax = 1;
                        }
                    }
                    if (menuSelection == 3) { //Achievements Menu
                        if (pad & PADstart) {
                            if (limiterPadStart) { return;}

                            currentMenu[1] = 3;
                            menuSelection = 1;
                            menuSelectionMax = 1;
                        }
                    }
                    if (menuSelection == 4) {//Two players mode
                        if (pad & PADstart) {
                            if (limiterPadStart) { return;}

                            twoPlayerMode = !twoPlayerMode;

                            if (twoPlayerMode) {
                                sprintf(twoPlayerModeStr, "ON");
                            } else {
                                sprintf(twoPlayerModeStr, "OFF");
                            }
                        }
                    }
                    if (menuSelection == 5) { //Return
                        if (pad & PADstart) {
                            if (limiterPadStart)  { return; }

                            currentMenu[0] = 0;
                            if (night6unlock) {menuSelection = 4;} else {menuSelection = 3;}
                            if (DebugActivated || night6unlock) {menuSelectionMax = 5;}
                            else {menuSelectionMax = 4;}
                        }
                    }
                break;
                case 1:
                    if (menuSelection == 1) { //Unlimited Power
                        if (pad & PADstart) {
                            if (limiterPadStart) { return; }

                            unlimitedPower = !unlimitedPower;

                            if (unlimitedPower) {
                                sprintf(unlimitedPowerStr, "ON");
                            } else {
                                sprintf(unlimitedPowerStr, "OFF");
                            }
                        }
                    }
                    if (menuSelection == 2) { //Fast nights
                        if (pad & PADstart) {
                            if (limiterPadStart) { return;}

                            fastNights = !fastNights;

                            if (fastNights) {
                                sprintf(fastNightsStr, "ON");
                            } else {
                                sprintf(fastNightsStr, "OFF");
                            }
                        }
                    }
                    if (menuSelection == 3) { //Radar
                        if (pad & PADstart) {
                            if (limiterPadStart) { return;}

                            radar = !radar;

                            if (radar) {
                                sprintf(radarStr, "ON");
                            } else {
                                sprintf(radarStr, "OFF");
                            }
                        }
                    }
                    if (menuSelection == 4) { //Return
                        if (pad & PADstart) {
                            if (limiterPadStart)  { return; }

                            currentMenu[1] = 0;
                            menuSelection = 1;
                            menuSelectionMax = 5;
                        }
                    }

                break;
                case 2:
                    if (pad & PADstart) {
                        if (limiterPadStart) { return;}

                        currentMenu[1] = 0;
                        menuSelection = 2;
                        menuSelectionMax = 5;

                    }


                break;
                case 3:
                    if (pad & PADRdown) {
                        if (limiterPadStart) { return;}

                        currentMenu[1] = 0;
                        menuSelection = 3;
                        menuSelectionMax = 5;

                    }

                    if (pad & PADR1) {
                        if (limiterPadR1) { return;}

                        if (page < 10) {page++;}

                    }

                    if (pad & PADL1) {
                        if (limiterPadL1) { return;}

                        if (page > 0) {page--;}

                    }


                break;
            }
        break;
        case 2:
            switch(currentMenu[1]) {
                case 0: 
                    if (menuSelection == 1) {//To AI Set menu
                        if (pad & PADstart) {
                            if (limiterPadStart) { return;}

                            currentMenu[1] = 1;

                            menuSelection = 1;
                            menuSelectionMax = 5;
                        }
                    }
                    if (menuSelection == 2) {//To Timer Menu
                        if (pad & PADstart) {
                            if (limiterPadStart) { return;}

                            currentMenu[1] = 2;

                            menuSelection = 1;
                            menuSelectionMax = 4;
                        }
                    }
                    if (menuSelection == 3) {//To Advance Menu
                        if (pad & PADstart) {
                            if (limiterPadStart) { return;}

                            currentMenu[1] = 3;

                            menuSelection = 1;
                            menuSelectionMax = 5;
                        }
                    }
                    if (menuSelection == 4) {//Launch Custom night
                        if (pad & PADstart) {
                            if (limiterPadStart) { return;}

                            menu = 2;

                            global_alpha = InAndOut_alpha = 128;



                            inCustomNight = true;
                        }
                    }
                    if (menuSelection == 5) {//Return to Main menu
                        if (pad & PADstart) {
                            if (limiterPadStart)  { return; }

                            currentMenu[0] = 0;
                            if (night6unlock) {menuSelection = 5;} else {menuSelection = 4;}
                            if (DebugActivated || night6unlock) {menuSelectionMax = 5;}
                            else {menuSelectionMax = 4;}
                        }
                    }
                break;
                case 1: //AI Set Menu

                    if (menuSelection == 1) {
                        if (pad & PADLright) { //Freddy
                            if (limiterPadRight) { return;}

                            FreddyDifficulty++;
                            if (FreddyDifficulty > 20) {FreddyDifficulty = 0;}
                        }
                        if (pad & PADLleft) { //Freddy
                            if (limiterPadLeft) { return;}

                            FreddyDifficulty--;
                            if (FreddyDifficulty < 0) {FreddyDifficulty = 20;}
                        }
                    }

                    if (menuSelection == 2) {
                        if (pad & PADLright) { //Bonnie
                            if (limiterPadRight) { return;}

                            BonnieDifficulty++;
                            if (BonnieDifficulty > 20) {BonnieDifficulty = 0;}
                        }
                        if (pad & PADLleft) { //Bonnie
                            if (limiterPadLeft) { return;}

                            BonnieDifficulty--;
                            if (BonnieDifficulty < 0) {BonnieDifficulty = 20;}
                        }
                    }

                    if (menuSelection == 3) {
                        if (pad & PADLright) { //Chica
                            if (limiterPadRight) { return;}

                            ChicaDifficulty++;
                            if (ChicaDifficulty > 20) {ChicaDifficulty = 0;}
                        }
                        if (pad & PADLleft) { //Chica
                            if (limiterPadLeft) { return;}

                            ChicaDifficulty--;
                            if (ChicaDifficulty < 0) {ChicaDifficulty = 20;}
                        }
                    }

                    if (menuSelection == 4) {
                        if (pad & PADLright) { //Foxy
                            if (limiterPadRight) { return;}

                            FoxyDifficulty++;
                            if (FoxyDifficulty > 20) {FoxyDifficulty = 0;}
                        }
                        if (pad & PADLleft) { //Foxy
                            if (limiterPadLeft) { return;}

                            FoxyDifficulty--;
                            if (FoxyDifficulty < 0) {FoxyDifficulty = 20;}
                        }
                    }

                    if (menuSelection == 5) {//Return to Custom Night
                        if (pad & PADstart) {
                            if (limiterPadStart)  { return; }

                            currentMenu[1] = 0;
                            menuSelection = 1;
                            menuSelectionMax = 5;
                        }
                    }
                break;
                case 2: //Timer Menu

                    if (menuSelection == 1) { //Charge
                        //For more slowed down changement
                        if (pad & PADLright) {
                            if (limiterPadRight) {return;}

                            customBattery++;
                            if (customBattery > 100) {customBattery = 0;}

                        }
                        if (pad & PADLleft) {
                            if (limiterPadLeft) {return;}

                            customBattery--;
                            if (customBattery < 0) {customBattery = 100;}
                        }

                        //For quick changes
                        if (pad & PADL1) {
                            customBattery++;
                            if (customBattery > 100) {customBattery = 0;}
                        }
                        if (pad & PADR1) {
                            customBattery--;
                            if (customBattery < 0) {customBattery = 100;}
                        }
                    }
                    if (menuSelection == 2) { //AM Change
                        
                        if (pad & PADLright) {
                            if (limiterPadRight) { return;}

                            customAM++;
                            if (customAM < 12 && customAM > 6) {customAM = 12;}
                            if (customAM > 12) {customAM = 0;}
                        }
                        if (pad & PADLleft) {
                            if (limiterPadLeft) { return;}

                            customAM--;
                            if (customAM < 12 && customAM > 6) {customAM = 6;}
                            if (customAM < 0) {customAM = 12;}
                        }
                    }
                    if (menuSelection == 3) { //convertionFramesToAM --- How much time an hour is

                        if (pad & PADLright) {

                            convertionFramesToAM++;
                        }
                        if (pad & PADLleft) {

                            convertionFramesToAM--;
                            if (convertionFramesToAM < 0) {convertionFramesToAM = 0;}
                        }

                        //For reset
                        if (pad & PADstart) {
                            convertionFramesToAM = 60;
                        }

                        //For 0
                        if (pad & PADselect) {
                            convertionFramesToAM = 0;
                        }

                        //For 120
                        if (pad & PADstart && pad & PADselect) {
                            convertionFramesToAM = 120;
                        }
                    }
                    if (menuSelection == 4) {
                        if (pad & PADstart) {
                            if (limiterPadStart) { return;}

                            currentMenu[1] = 0;

                            menuSelection = 1;
                            menuSelectionMax = 5;
                        }
                    }
                break;
                case 3: //Advance Menu
                    if (menuSelection == 1) {

                        if (pad & PADLright) {

                            FreddyLocationFrameLock++;
                        }
                        if (pad & PADLleft) {

                            FreddyLocationFrameLock--;
                            if (FreddyLocationFrameLock < 0) {FreddyLocationFrameLock = 0;}
                        }
 
                        //For reset
                        if (pad & PADstart) {
                            FreddyLocationFrameLock = 181;
                        }

                    }
                    if (menuSelection == 2) {

                        if (pad & PADLright) {

                            BonnieLocationFrameLock++;
                        }
                        if (pad & PADLleft) {

                            BonnieLocationFrameLock--;
                            if (BonnieLocationFrameLock < 0) {BonnieLocationFrameLock = 0;}
                        }
 
                        //For reset
                        if (pad & PADstart) {
                            BonnieLocationFrameLock = 298;
                        }
                        
                    }
                    if (menuSelection == 3) {

                        if (pad & PADLright) {
                            ChicaLocationFrameLock++;
                        }
                        if (pad & PADLleft) {

                            ChicaLocationFrameLock--;
                            if (ChicaLocationFrameLock < 0) {ChicaLocationFrameLock = 0;}
                        }
 
                        //For reset
                        if (pad & PADstart) {
                            ChicaLocationFrameLock = 299;
                        }
                        
                    }
                    if (menuSelection == 4) {
                        
                        if (pad & PADLright) {

                            FoxyLocationFrameLock++;
                        }
                        if (pad & PADLleft) {

                            FoxyLocationFrameLock--;
                            if (FoxyLocationFrameLock < 0) {FoxyLocationFrameLock = 0;}
                        }
 
                        //For reset
                        if (pad & PADstart) {
                            FoxyLocationFrameLock = 301;
                        }
                        
                    }
                    if (menuSelection == 5) {
                        if (pad & PADstart) {
                            if (limiterPadStart)  { return; }

                            currentMenu[1] = 0;
                            menuSelection = 1;
                            menuSelectionMax = 5;
                        }
                        
                    }
                break;

            }

        break;
        case 3:
            if (pad & PADstart) {
                currentMenu[0] = 0;
            }//Or...

        break;
    }
    //Used to trigger the "LimiterPad"s :
    
    if (pad & PADstart) {
        limiterPadStart = true;
        timesControllerPressed++;
    }
    if (pad & PADLleft) {
        limiterPadLeft = true;
        timesControllerPressed++;
    }
    if (pad & PADLright) {
        limiterPadRight = true;
        timesControllerPressed++;
    }
    if (pad & PADR1) {
        limiterPadR1 = true;
        timesControllerPressed++;
    }
    if (pad & PADL1) {
        limiterPadL1 = true;
        timesControllerPressed++;
    }
}

void MoveFunction(void) {

    doorsMove();

    if (XCoordinates > 10) {
        if (curDoorLook == true) {curDoorLook = false;}
    }
    if (XCoordinates < -10) {
        if (curDoorLook == false) {curDoorLook = true;}
    }

    if (pad & PADRup || pad >> 16 & PADRup) {speedoffice = 6;} else {speedoffice = 3;}

    if(pad & PADLleft || pad >> 16 & PADLleft && twoPlayerMode) {
        if (XCoordinates < 80) {
            XCoordinates += speedoffice;
        }
    }


    if(pad & PADLright || pad >> 16 & PADLright && twoPlayerMode) {
        if (XCoordinates > -115) {
            XCoordinates -= speedoffice;
        }
    } 

    MovVectorofficemiddle.vx = XCoordinates;
    MovVectorleftdoor.vx = XCoordinates - 145;
    MovVectorrightdoor.vx = XCoordinates + 138;
    MovVectorfan.vx = XCoordinates;
    MovVectorofficegolden.vx = XCoordinates - 90;
    MovVectorfreddylightsout.vx = XCoordinates - 120;
    MovVectorchicawindow.vx = XCoordinates + 84;
}

void ControllerOfficeFunction(void) {

    if (!(pad & PADRdown)) {limiterPadCross = false;}

    if (!(pad & PADRright)) {limiterPadCircle = false;}

    if (!(pad & PADLup)) {limiterbop = false;}

    if(!(pad & PADR1 || pad >> 16 & PADR1)) {limiterPadR1 = false;}

    //Poking freddy fazbear noze
    if(pad & PADLup || pad >> 16 & PADLup && twoPlayerMode) { //Up

        if (limiterbop) {return;} else {limiterbop = true;}

        if (MovVectorofficemiddle.vx > -65) {
            SpuSetKey(SPU_ON, SPU_07CH);
        }
    }

    //CAMERA TRIGGER
    if(pad & PADR1 || pad >> 16 & PADR1) { //R1

        if (limiterPadR1 == true) {return;} else {limiterPadR1 = true;}

        CameraTriggerFunc();
    }
    

    //DOORS
    if (pad & PADRdown) {

        if (limiterPadCross) {return;} else {limiterPadCross = true;}

        if (curDoorLook) { 
            //Right door

            if (cantDoorR) {jamNoise = true; return;}

            SpuSetKey(SPU_ON, SPU_00CH);

            doorClosedR = !doorClosedR; 
            return;
        }

        //Left door

        if (cantDoorL) {jamNoise = true; return;}

        SpuSetKey(SPU_ON, SPU_00CH);
        
        doorClosedL = !doorClosedL; 
        
    } 

    //LIGHTS
    if (pad & PADRright) {

        if (limiterPadCircle) {return;} else {limiterPadCircle = true;}

        if (cantDoorL) {jamNoise = true; return;}

        //Left door
        if (!curDoorLook) { 
            lightL = !lightL;
            if (lightR) {
                lightR = false;
                LoadTexture(_binary_tim_office_officeRIGHT_tim_start, &officeRIGHT);
            }

            if (lightL) {

                SpuSetKey(SPU_ON, SPU_01CH);

                if (BonnieIsAtDoor) {
                    LoadTexture(_binary_tim_office_officeLEFTlightbonnie_tim_start, &officeLEFTlightbonnie);
                } else {
                    LoadTexture(_binary_tim_office_officeLEFTlight_tim_start, &officeLEFTlight);
                }

            } else {
                LoadTexture(_binary_tim_office_officeLEFT_tim_start, &officeLEFT);

                SpuSetKey(SPU_OFF, SPU_01CH);
            }

            return; //If we don't return right now, it'll do both right AND left
        }

        if (cantDoorR) {jamNoise = true; return;}

        //Right door
        lightR = !lightR;
        if (lightL) {
            lightL = false;
            LoadTexture(_binary_tim_office_officeLEFT_tim_start, &officeLEFT);
        }

        if (lightR) {

            SpuSetKey(SPU_ON, SPU_01CH);

            LoadTexture(_binary_tim_office_officeRIGHTlight_tim_start, &officeRIGHTlight);

        } else {
            LoadTexture(_binary_tim_office_officeRIGHT_tim_start, &officeRIGHT);

            SpuSetKey(SPU_OFF, SPU_01CH);
        }

    }
}

void ControllerCameraFunction(void) {

    if(!(pad & PADR1 || pad >> 16 & PADR1)) {limiterPadR1 = false;}

    if (!(pad & PADLdown || pad >> 16 & PADLdown) && limiterPadDown) {limiterPadDown = false;}

    if (!(pad & PADLup || pad >> 16 & PADLup) && limiterPadUp) {limiterPadUp = false;}

    if (!(pad & PADLright || pad >> 16 & PADLright) && limiterPadRight) {limiterPadRight = false;}

    if (!(pad & PADLleft || pad >> 16 & PADLleft) && limiterPadLeft) {limiterPadLeft = false;}

    if (curCam[0] == '1') {

        if (curCam[1] == 'A') {

            if (!limiterPadDown && pad & PADLdown || !limiterPadDown && pad >> 16 & PADLdown && twoPlayerMode) { 
                curCam[0] = '1';
                curCam[1] = 'B';
                SpuSetKey(SPU_ON, SPU_04CH);
                limiterPadDown = true;
            }
        }

        if (curCam[1] == 'B') {

            if (!limiterPadUp && pad & PADLup || !limiterPadUp && pad >> 16 & PADLup && twoPlayerMode) {
                curCam[0] = '1';
                curCam[1] = 'A';
                SpuSetKey(SPU_ON, SPU_04CH);
                limiterPadUp = true;
            }

            if (!limiterPadDown && pad & PADLdown || !limiterPadDown && pad >> 16 & PADLdown && twoPlayerMode) { 
                curCam[0] = '1';
                curCam[1] = 'C';
                SpuSetKey(SPU_ON, SPU_04CH);
                limiterPadDown = true;
            }

            if (!limiterPadLeft && pad & PADLleft || !limiterPadLeft && pad >> 16 & PADLleft && twoPlayerMode) { 
                curCam[0] = '5';
                curCam[1] = ' ';
                SpuSetKey(SPU_ON, SPU_04CH);
                limiterPadLeft = true;
            }

            if (!limiterPadRight && pad & PADLright || !limiterPadRight && pad >> 16 & PADLright && twoPlayerMode) { 
                curCam[0] = '7';
                curCam[1] = ' ';
                SpuSetKey(SPU_ON, SPU_04CH);
                limiterPadRight = true;
            }
        }
        if (curCam[1] == 'C') {

            if (!limiterPadUp && pad & PADLup || !limiterPadUp && pad >> 16 & PADLup && twoPlayerMode) { 
                curCam[0] = '1';
                curCam[1] = 'B';
                SpuSetKey(SPU_ON, SPU_04CH);
                limiterPadUp = true;
            }

            if (!limiterPadDown && pad & PADLdown || !limiterPadDown && pad >> 16 & PADLdown && twoPlayerMode) { 
                curCam[0] = '3';
                curCam[1] = ' ';
                SpuSetKey(SPU_ON, SPU_04CH);
                limiterPadDown = true;
            }

            if (!limiterPadLeft && pad & PADLleft || !limiterPadLeft && pad >> 16 & PADLleft && twoPlayerMode) { 
                curCam[0] = '5';
                curCam[1] = ' ';
                SpuSetKey(SPU_ON, SPU_04CH);
                limiterPadLeft = true;
            }
        }
    }
    if (curCam[0] == '2') {
        if (curCam[1] == 'A') {

            if (!limiterPadUp && pad & PADLup || !limiterPadUp && pad >> 16 & PADLup && twoPlayerMode) { 
                curCam[0] = '3';
                curCam[1] = ' ';
                SpuSetKey(SPU_ON, SPU_04CH);
                limiterPadUp = true;
            }

            if (!limiterPadDown && pad & PADLdown || !limiterPadDown && pad >> 16 & PADLdown && twoPlayerMode) { 
                curCam[0] = '2';
                curCam[1] = 'B';
                SpuSetKey(SPU_ON, SPU_04CH);
                limiterPadDown = true;
            }

            if (!limiterPadRight && pad & PADLright || !limiterPadRight && pad >> 16 & PADLright && twoPlayerMode) { 
                curCam[0] = '4';
                curCam[1] = 'A';
                SpuSetKey(SPU_ON, SPU_04CH);
                limiterPadRight = true;
            }

        }
        if (curCam[1] == 'B') {

            if (!limiterPadUp && pad & PADLup || !limiterPadUp && pad >> 16 & PADLup && twoPlayerMode) { 
                curCam[0] = '2';
                curCam[1] = 'A';
                SpuSetKey(SPU_ON, SPU_04CH);
                limiterPadUp = true;
            }

            if (!limiterPadRight && pad & PADLright || !limiterPadRight && pad >> 16 & PADLright && twoPlayerMode) { 
                curCam[0] = '4';
                curCam[1] = 'B';
                SpuSetKey(SPU_ON, SPU_04CH);
                limiterPadRight = true;
            }
        }
    }
    if (curCam[0] == '3') {
        if (!limiterPadUp && pad & PADLup || !limiterPadUp && pad >> 16 & PADLup && twoPlayerMode) { 
            curCam[0] = '1';
            curCam[1] = 'C';
            SpuSetKey(SPU_ON, SPU_04CH);
            limiterPadUp = true;
        }

        if (!limiterPadDown && pad & PADLdown || !limiterPadDown && pad >> 16 & PADLdown && twoPlayerMode) { 
            curCam[0] = '2';
            curCam[1] = 'A';
            SpuSetKey(SPU_ON, SPU_04CH);
            limiterPadDown = true;
        }

        if (!limiterPadRight && pad & PADLright || !limiterPadRight && pad >> 16 & PADLright && twoPlayerMode) { 
            curCam[0] = '6';
            curCam[1] = ' ';
            SpuSetKey(SPU_ON, SPU_04CH);
            limiterPadRight = true;
        }
    }
    if (curCam[0] == '4') {
        if (curCam[1] == 'A') {

            if (!limiterPadLeft && pad & PADLleft || !limiterPadLeft && pad >> 16 & PADLleft && twoPlayerMode) { 
                curCam[0] = '2';
                curCam[1] = 'A';
                SpuSetKey(SPU_ON, SPU_04CH);
                limiterPadLeft = true;
            }

            if (!limiterPadDown && pad & PADLdown || !limiterPadDown && pad >> 16 & PADLdown && twoPlayerMode) { 
                curCam[0] = '4';
                curCam[1] = 'B';
                SpuSetKey(SPU_ON, SPU_04CH);
                limiterPadDown = true;
            }

            if (!limiterPadUp && pad & PADLup || !limiterPadUp && pad >> 16 & PADLup && twoPlayerMode) { 
                curCam[0] = '6';
                curCam[1] = ' ';
                SpuSetKey(SPU_ON, SPU_04CH);
                limiterPadUp = true;
            }
        }
        if (curCam[1] == 'B') {

            if (!limiterPadLeft && pad & PADLleft || !limiterPadLeft && pad >> 16 & PADLleft && twoPlayerMode) { 
                curCam[0] = '2';
                curCam[1] = 'B';
                SpuSetKey(SPU_ON, SPU_04CH);
                limiterPadLeft = true;
            }

            if (!limiterPadUp && pad & PADLup || !limiterPadUp && pad >> 16 & PADLup && twoPlayerMode) { 
                curCam[0] = '4';
                curCam[1] = 'A';
                SpuSetKey(SPU_ON, SPU_04CH);
                limiterPadUp = true;
            }

        }
    }
    if (curCam[0] == '5') {

        if (!limiterPadRight && pad & PADLright || !limiterPadRight && pad >> 16 & PADLright && twoPlayerMode) { 
            curCam[0] = '1';
            curCam[1] = 'B';
            SpuSetKey(SPU_ON, SPU_04CH);
            limiterPadRight = true;
        }

        if (!limiterPadDown && pad & PADLdown || !limiterPadDown && pad >> 16 & PADLdown && twoPlayerMode) { 
            curCam[0] = '1';
            curCam[1] = 'C';
            SpuSetKey(SPU_ON, SPU_04CH);
            limiterPadDown = true;
        }
    }
    if (curCam[0] == '6') {

        if (!limiterPadLeft && pad & PADLleft || !limiterPadLeft && pad >> 16 & PADLleft && twoPlayerMode) { 
            curCam[0] = '3';
            curCam[1] = ' ';
            SpuSetKey(SPU_ON, SPU_04CH);
            limiterPadLeft = true;
        }
        if (!limiterPadUp && pad & PADLup || !limiterPadUp && pad >> 16 & PADLup && twoPlayerMode) { 
            curCam[0] = '7';
            curCam[1] = ' ';
            SpuSetKey(SPU_ON, SPU_04CH);
            limiterPadUp = true;
        }
        if (!limiterPadDown && pad & PADLdown || !limiterPadDown && pad >> 16 & PADLdown && twoPlayerMode) { 
            curCam[0] = '4';
            curCam[1] = 'A';
            SpuSetKey(SPU_ON, SPU_04CH);
            limiterPadDown = true;
        }
    }
    if (curCam[0] == '7') {

        if (!limiterPadLeft && pad & PADLleft || !limiterPadLeft && pad >> 16 & PADLleft && twoPlayerMode) { 
            curCam[0] = '1';
            curCam[1] = 'B';
            SpuSetKey(SPU_ON, SPU_04CH);
            limiterPadLeft = true;
        }

        if (!limiterPadDown && pad & PADLdown || !limiterPadDown && pad >> 16 & PADLdown && twoPlayerMode) { 
            curCam[0] = '6';
            curCam[1] = ' ';
            SpuSetKey(SPU_ON, SPU_04CH);
            limiterPadDown = true;
        }
    }

    //CAMERA TRIGGER
    if(pad & PADR1 || pad >> 16 & PADR1) { //R1

        if (limiterPadR1 == true) {return;} else {limiterPadR1 = true;}

        CameraTriggerFunc();
    }
}
