void menuPrint(void) {
    //FntPrint("\n\n\n\n\n\n\n\n\n\n\n\n"); 
    switch(currentMenu[0]) {
        case 0:
            FntPrint("   Five\n\n   Nights\n\n   at\n\n   Freddy's\n\n\n");  // print time

            if (menuSelection == 1) {FntPrint(">> New Game\n\n");}
            else {FntPrint("   New Game\n\n");}

            if (menuSelection == 2) {FntPrint(">> Continue Night %d\n\n", night);}
            else {FntPrint("   Continue Night %d\n\n", night);}

            if (Night6State > 0) {

                if (Night6State == 2) {
                    if (menuSelection == 3) {FntPrint(">> Night 6 (Beaten)\n\n");} 
                    else {FntPrint("   Night 6 (Beaten)\n\n");}

                } else {

                    if (menuSelection == 3) {FntPrint(">> Night 6\n\n");} 
                    else {FntPrint("   Night 6\n\n");}
                }


            }

            if (menuSelection == 3 + night6unlock) {FntPrint(">> Extra menu \n\n");}
            else {FntPrint("   Extra menu \n\n");}

            if (menuSelection == 4 + night6unlock) {FntPrint(">> Custom Night \n\n");}
            else {FntPrint("   Custom Night \n\n");}

            if (DebugActivated) {
                FntPrint("   Debugprint Enabled \n\n");
            }
        break;
        case 1:
            switch(currentMenu[1]) {
                case 0:
                    FntPrint("   Extra\n\n   Menu\n\n\n");  // print time

                    if (menuSelection == 1) {FntPrint(">> Cheats Menu\n\n");}
                    else {FntPrint("   Cheats Menu\n\n");}

                    if (menuSelection == 2) {FntPrint(">> Info screen\n\n");}
                    else {FntPrint("   Info screen\n\n");}

                    if (menuSelection == 3) {FntPrint(">> Achievement Menu\n\n");}
                    else {FntPrint("   Achievement Menu\n\n");}

                    if (menuSelection == 4) {FntPrint(">> Two Player Mode : %s\n\n", twoPlayerModeStr);}
                    else {FntPrint("   Two Player Mode : %s\n\n", twoPlayerModeStr);}

                    if (menuSelection == 5) {FntPrint(">> Return to main menu\n\n");}
                    else {FntPrint("   Return to main menu\n\n");}

                break;

                case 1:  //Cheats
                    FntPrint("   Cheats\n\n   Menu\n\n\n");  // print time

                    if (menuSelection == 1) {FntPrint(">> Unlimited Power : %s\n\n", unlimitedPowerStr);}
                    else {FntPrint("   Unlimited Power : %s\n\n", unlimitedPowerStr);}

                    if (menuSelection == 2) {FntPrint(">> Fast Nights : %s\n\n", fastNightsStr);}
                    else {FntPrint("   Fast Nights : %s\n\n", fastNightsStr);}

                    if (menuSelection == 3) {FntPrint(">> Radar Map : %s\n\n", radarStr);}
                    else {FntPrint("   Radar Map : %s\n\n", radarStr);}

                    if (menuSelection == 4) {FntPrint(">> Back \n\n");}
                    else {FntPrint("   Back \n\n");}

                break;

                case 2:  //Informations

                    FntPrint("            Information Screen\n\n");

                    FntPrint("    Five Night at Freddy's has been \n   released by Scott Cawton on 2014,\nand has been ported on the PS1 by Soeiz.\n            Thank you, Scott, \n For making our childhood a lot better.\n\n");

                    FntPrint(">> Back                     V1.0.0 RE \n"); 
                break;

                case 3:  //Achievements 

                    FntPrint("    Achievements Menu : %s\n\n", achievementsName[page]);



                    switch(page) {
                        case 0:
                            FntPrint("               X Exit        (R1) Next \n\n"); 
                        break;
                        case 10:
                            FntPrint("L1 Previous            X Exit            \n\n"); 
                        break;
                        default:
                            FntPrint("L1 Previous       X Exit         R1 Next \n\n"); 
                        break;
                    }

                    if (achievements[page]) {FntPrint("Achievement unlocked! \n\n");} else {FntPrint("Achievement locked. \n\n");}

                    switch(page) {
                        case 0: //Night 1
                            FntPrint("Beat Night 1. Nothing too crazy, right?");
                        break;
                        case 1: //Night 2
                            FntPrint("Beat Night 2. You have to press buttons now.");
                        break;
                        case 2: //Night 3
                            FntPrint("Beat Night 3. Ouuh Freddy Scary!");
                        break;
                        case 3: //Night 4
                            FntPrint("Beat Night 4. Who's that guy that's running?!");
                        break;
                        case 4: //Night 5
                            FntPrint("Beat Night 5. Okay, now we're talking.");
                        break;
                        case 5: //Night 6
                            FntPrint("Beat Night 6. It sure is harder than night 1. ");
                        break;
                        case 6: //4/20
                            FntPrint("Beat 4 / 20. \"OOOH MY GOD ! OOOOH I DID IT!\"");
                        break;
                        case 7: //Hell night
                            FntPrint("Beat Hell night. THIS is hard! ");
                        break;
                        case 8: //Golden Fredied
                            FntPrint("Get killed by Golden Freddy. \nHope you didn't cheat on that one.");
                        break;
                        case 9: //Freddy date
                            FntPrint("Bring Freddy to a date. Love is in the air! Did you treat him well?");
                        break;
                        case 10: //Died on Night 1
                            FntPrint("Die on Night 1. What? Why? How?? \nWere you scared ?");
                        break;
                    }   






                break;
            }

        break;
        case 2:
            
            FntPrint("   Custom\n\n   Night\n\n\n");  // print time
            switch(currentMenu[1]) {
                case 0:

                    if (!gotYou) {FntPrint("   Welcome! What do you want to modify?\n\n\n\n");} else {FntPrint("   Hah hah! Got you!\n\n\n\n");}

                    if (menuSelection == 1) {FntPrint(">> Set AI levels\n\n");}
                    else {FntPrint("   Set AI levels\n\n");}

                    if (menuSelection == 2) {FntPrint(">> Set Charge, Timer, ect.\n\n");}
                    else {FntPrint("   Set Charge, Timer, ect.\n\n");}

                    if (menuSelection == 3) {FntPrint(">> Advanced settings\n\n");}
                    else {FntPrint("   Advanced settings\n\n");}

                    if (menuSelection == 4) {FntPrint(">> Launch custom night\n\n");}
                    else {FntPrint("   Launch custom night\n\n");}

                    if (menuSelection == 5) {FntPrint(">> Return to main menu\n\n");}
                    else {FntPrint("   Return to main menu\n\n");}

                break;

                case 1: //AI levels

                    FntPrint("   Set Ai Level Menu\n\n\n");

                    if (menuSelection == 1) {FntPrint(">> Freddy : %d\n\n", FreddyDifficulty );}
                    else {FntPrint("   Freddy : %d\n\n", FreddyDifficulty );}

                    if (menuSelection == 2) {FntPrint(">> Bonnie : %d\n\n", BonnieDifficulty );}
                    else {FntPrint("   Bonnie : %d\n\n", BonnieDifficulty );}

                    if (menuSelection == 3) {FntPrint(">> Chica : %d\n\n", ChicaDifficulty );}
                    else {FntPrint("   Chica : %d\n\n", ChicaDifficulty );}

                    if (menuSelection == 4) {FntPrint(">> Foxy : %d\n\n", FoxyDifficulty );}
                    else {FntPrint("   Foxy : %d\n\n", FoxyDifficulty );}

                    if (menuSelection == 5) {FntPrint(">> Return to Custom night menu\n\n");}
                    else {FntPrint("   Return to Custom night menu\n\n");}

                    if (FreddyDifficulty == 1 && BonnieDifficulty == 9 && ChicaDifficulty == 8 && FoxyDifficulty == 7) {
                        Ran(1504);
                        if (RAN == 1) {FntPrint("   no\n\n");}
                        if (RAN == 2) {FntPrint("   dont\n\n");}
                        if (RAN == 3) {FntPrint("   never\n\n");}
                        if (RAN == 4) {FntPrint("   its me\n\n");}
                        if (RAN == 5) {FntPrint("   regrets\n\n");}
                        if (RAN == 6) {FntPrint("   \n\n       no\n\n");}
                        if (RAN == 7) {FntPrint("   \n\n       dont\n\n");}
                        if (RAN == 8) {FntPrint("   \n\n       never\n\n");}
                        if (RAN == 9) {FntPrint("   \n\n       its me\n\n");}
                    }

                break;

                case 2: //Timer / charge etc

                    FntPrint("   Set Timer, charge, AM\n\n\n");

                    if (menuSelection == 1) {FntPrint(">> Set charge (not infinite) %d\n\n", customBattery );}
                    else {FntPrint("   Set charge (not infinite) %d\n\n", customBattery );}

                    if (menuSelection == 2) {FntPrint(">> Set beginning AM %d\n\n", customAM );}
                    else {FntPrint("   Set beginning AM %d\n\n", customAM );}

                    if (menuSelection == 3) {FntPrint(">> 1 Hour = %d seconds in game\n\n", convertionFramesToAM );}
                    else {FntPrint("   1 Hour = %d seconds in game\n\n", convertionFramesToAM );}

                    if (menuSelection == 4) {FntPrint(">> Return to Custom night menu\n\n");}
                    else {FntPrint("   Return to Custom night menu\n\n");}
                break;
                
                case 3: //Advanced Menu

                    FntPrint("   Advanced Settings Menu\n\n\n");

                    if (menuSelection == 1) {FntPrint(">> Cooldown of Freddy : %d \n\n", FreddyLocationFrameLock);}
                    else {FntPrint("   Cooldown of Freddy : %d \n\n", FreddyLocationFrameLock);}

                    if (menuSelection == 2) {FntPrint(">> Cooldown of Bonnie : %d \n\n", BonnieLocationFrameLock);}
                    else {FntPrint("   Cooldown of Bonnie : %d \n\n", BonnieLocationFrameLock);}

                    if (menuSelection == 3) {FntPrint(">> Cooldown of Chica : %d \n\n", ChicaLocationFrameLock);}
                    else {FntPrint("   Cooldown of Chica : %d \n\n", ChicaLocationFrameLock);}

                    if (menuSelection == 4) {FntPrint(">> Cooldown of Foxy : %d \n\n", FoxyLocationFrameLock);}
                    else {FntPrint("   Cooldown of Foxy : %d \n\n", FoxyLocationFrameLock);}

                    if (menuSelection == 5) {FntPrint(">> Return to Custom night menu\n\n");}
                    else {FntPrint("   Return to Custom night menu\n\n");}
                break;

            }
            
        break;
        case 3:
            FntPrint("               Welcome!\n\n");

            FntPrint("A file of Five Night at Freddy's 1 has \nBeen created on your Memory Card.\n\nHello ! You might want to check the\nDescription of the gamejolt page\nTo be informed about controls.\n\n             Good Nights!\n             Press  start");
        break;
    }
}

void InGamePrintFunc(void) {
    if (!DebugActivated) {

        if (!hellNight) { 
            FntPrint("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n           %d",battery); 

            if (isOnCamera) {FntPrint("             %s",curCamName);}
        }

        

        return;
    }

    switch(debugPrintNumber) {
        case 1:
            FntPrint("           ANIMATRONIC DEBUG\n");
            FntPrint("Location: F%d, B%d, C%d, Fo%d\n", FreddyLocation, BonnieLocation, ChicaLocation, FoxyLocation);
            FntPrint("FrameLoc: F%d, B%d, C%d, Fo%d\n", FreddyLocationFrame, BonnieLocationFrame, ChicaLocationFrame, FoxyLocationFrame);
            FntPrint("FoxyLocked %d, BAT %d", FoxyLockedFrames, battery);
        break;
    }
}