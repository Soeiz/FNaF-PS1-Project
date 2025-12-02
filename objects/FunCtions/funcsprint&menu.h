
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
                    night++;
                    if (night > 6) {night = 1;}
                    limiterpadright = 1;
                }
            }
            if (pad & PADLleft) {
                if (limiterpadleft == 0) {
                    night--;
                    if (night < 1) {night = 6;}
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

                    cheating = 1;

                    if (unlimitedpower > 1) {
                        unlimitedpower = 0;
                        unlimitedpowerstr[0] = 'O';
                        unlimitedpowerstr[1] = 'F';
                        unlimitedpowerstr[2] = 'F';

                        cheating = 0;
                    }
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

                    cheating = 1;

                    if (fastnights > 1) {
                        fastnights = 0;
                        fastnightsstr[0] = 'O';
                        fastnightsstr[1] = 'F';
                        fastnightsstr[2] = 'F';

                        cheating = 0;
                    }
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

                    cheating = 1;

                    if (radar > 1) {
                        radar = 0;
                        radarstr[0] = 'O';
                        radarstr[1] = 'F';
                        radarstr[2] = 'F';

                        cheating = 0;
                    }
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

        if (menuselection == 1) {FntPrint(">> Night set : %d\n\n", night);}
        else {FntPrint("   Night set : %d\n\n", night);}
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
        FntPrint("Achievements unlocked:\n\nBronze: %d\n\nGold: %d\n\nSilver: %d\n\n\n", achievements.bronze, achievements.gold, achievements.silver);
        
        FntPrint(">> Back                       V1.3.0 \n"); //Don't even need to do condition, there's only one
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
    if (freddydifficulty == 1 && bonniedifficulty == 9 && chicadifficulty == 8 && foxydifficulty == 7) {
        Ran(2504);
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
void gameoverprint(void) {
    switch(RAN) {
        default : 
            FntPrint("\n\n      Congrats! You just... Died.\nGo on and press start to try your luck                 again !\n");
        break;
        case 1 : 
            FntPrint("\n\n      Congrats! You just... Died.\nGo on and press start to try your luck                 again !\n");
        break;
        case 2 : 
            FntPrint("\n\n           Hah! You dead!\nGo on and press start to try your luck                 again !\n");
        break;
        case 3 : 
            FntPrint("\n\n               ITS ME");
        break;
        case 4 : 
            FntPrint("\n\n          Screamer on 44px!\nGo on and press start to try your luck                 again !\n");
        break;
        case 5 : 
            FntPrint("\n\n               No luck?\nGo on and press start to try your luck                 again !\n");
        break;
    }

    if (activatedmenudebug == 1) {
        FntPrint("             Killer : %d",deadfrom);
    }
}
