void animatronicLeveling() {

	switch(night) {
		case 1:
	        FreddyDifficulty = 0;
	        BonnieDifficulty = 0;
	        ChicaDifficulty = 0;
	        FoxyDifficulty = 0;

		break;
		case 2:
	        FreddyDifficulty = 0;
	        BonnieDifficulty = 3;
	        ChicaDifficulty = 1;
	        FoxyDifficulty = 1;

		break;
		case 3:
	        FreddyDifficulty = 1;
	        BonnieDifficulty = 0;
	        ChicaDifficulty = 5;
	        FoxyDifficulty = 2;

		break;
		case 4:
	        FreddyDifficulty = 1 + (Ran(3) - 1); //Meaning that we can get from 0~2 with 1~3 - 1
	        BonnieDifficulty = 2;
	        ChicaDifficulty = 4;
	        FoxyDifficulty = 6;

		break;
		case 5:
	        FreddyDifficulty = 3;
	        BonnieDifficulty = 5;
	        ChicaDifficulty = 7;
	        FoxyDifficulty = 5;

		break;
	}

    if (isOnNight6) {
        FreddyDifficulty = 4;
        BonnieDifficulty = 10;
        ChicaDifficulty = 12;
        FoxyDifficulty = 16;

    }
}

void animatronicActions(void) {

    for (int i = 0; i < sizeof(animatronicsPresenceOnCamera)/sizeof(animatronicsPresenceOnCamera[0]); i++) {
        if (animatronicsPresenceOnCamera[i] != animatronicsPresenceOnCameraOLD[i]) {
            cameraGlitchFrame = 300;
        }
        animatronicsPresenceOnCameraOLD[i] = animatronicsPresenceOnCamera[i];
    }

    if (!DebugActivated && !inCustomNight) {
        if (AM == 2 && FrameCounter == 0) {//Apparently, his AI level increases at this hour
            BonnieDifficulty++;
        }
        if (AM == 3 && FrameCounter == 0 || AM == 4 && FrameCounter == 0) { //Apparently, their AI level increases at these hours 
            BonnieDifficulty++;
            ChicaDifficulty++;
            FoxyDifficulty++;
        }
    }

    FreddyLocationFrame--; 
    BonnieLocationFrame--;
    ChicaLocationFrame--;
    if (FoxyLockedFrames == 0) {
        FoxyLocationFrame--;
    }

    if (FreddyAnticipation) { //He's ready to move 
        if (curCam[0] != '4' || curCam[1] != 'B') { //When you don't look at him
            FreddyLocation++;
            FreddyAnticipation = false;
            FreddyNoiseFootstep = true;
        }
    }

    if (FreddyLocation == 6) {

        if (!doorClosedR) {
            if (isOnCamera) {isAlreadyDeadLow = true;}
            Ran(100);
            frameFreddyEnter--;

            if (RAN < 20 && frameFreddyEnter == 0) {
                dead = true;
                deadFrom = 1;
            } else {frameFreddyEnter = 60;}

        } else {FreddyLocation = 4; animatronicsPresenceOnCamera[0] = 0;}

    }

    if (FreddyLocationFrame < 0 && FreddyDifficulty != 0) {
        Ran(20); //Roll time !!!!!!!
        if (FreddyDifficulty > RAN && !isAlreadyDeadLow) { //If freddy's AI level is superior to the current RAN, ...

            switch(FreddyLocation) {
                case 5:
                    FreddyAnticipation = true;
                break;

                case 6:
                    //Nothing, up there
                break;

                default :
                    if (!isOnCamera) {
                        FreddyLocation++;
                        FreddyNoiseFootstep = true;
                    }

                break;
            }
        }
        FreddyLocationFrame = FreddyLocationFrameLock;
    }




    if (BonnieLocationFrame < 0 && BonnieDifficulty != 0) {
        Ran(20);
        if (BonnieDifficulty > RAN) {
            if (BonnieLocation < 8) {
                BonnieOneTimeSkip = 0;
                BonnieLocation++;  
                if (BonnieOneTimeSkip == 0) {
                    Ran(BonnieLocation);
                    if (BonnieLocation == 1 && RAN%2 == 0) {BonnieLocation++;}
                    if (BonnieLocation == 2 && RAN%2 != 0) {BonnieLocation++;}
                    if (BonnieLocation == 3 && RAN%2 != 0) {BonnieLocation++;}
                    if (BonnieLocation == 4 && RAN%2 == 0) {BonnieLocation++;}
                    if (BonnieLocation == 5 && RAN%2 == 0) {BonnieLocation++;}   
                    BonnieOneTimeSkip = true; //It's for making them skip certain locations, like in the OG Game. 
                } 
                NoiseFootstep = true;
                FootstepAnimatronicNumber = 1;
            } else {
                if (deadFrom != 2) {BonnieLocation = 1;}
            }
        }   
        BonnieLocationFrame = BonnieLocationFrameLock;
    }

    if (BonnieIsAtDoor) {
        if (BonnieDoorInit == false) {
            if (lightL) {
                lightL = false;
                LoadTexture(_binary_tim_office_officeLEFT_tim_start, &officeLEFT);
                SpuSetKey(SPU_OFF, SPU_01CH);
            }
            BonnieDoorInit = true;
        }
        if (lightL && !noiseDoorBonnie) {
            noiseDoorBonnie = true;
            SpuSetKey(SPU_ON,SPU_05CH);
        }
        if (BonnieLocation == 8) {
            if (doorClosedL) {
                if (lightL) {
                    lightL = false;
                    LoadTexture(_binary_tim_office_officeLEFT_tim_start, &officeLEFT);
                    SpuSetKey(SPU_OFF, SPU_01CH);
                }
                BonnieIsAtDoor = false;
                BonnieLocation = 1;
                noiseDoorBonnie = false;
                BonnieDoorInit = false;
            } else {
                if (lightL) {
                    lightL = false;
                    LoadTexture(_binary_tim_office_officeLEFT_tim_start, &officeLEFT);
                    SpuSetKey(SPU_OFF, SPU_01CH);
                }
                cantDoorL = true;
                isAlreadyDead = true;
                deadFrom = 2;
            }
        }
    } 

    if (ChicaIsAtDoor) {
        if (ChicaDoorInit == false) {
            if (lightR) {
                lightR = false;
                LoadTexture(_binary_tim_office_officeRIGHT_tim_start, &officeRIGHT);
                SpuSetKey(SPU_OFF, SPU_01CH);
            }
            ChicaDoorInit = true;
        }
        if (lightR && !noiseDoorChica) {
            noiseDoorChica = true;
            SpuSetKey(SPU_ON,SPU_05CH);
        }
        if (ChicaLocation == 9) {
            if (doorClosedR) {
                if (lightR) {
                    lightR = false;
                    LoadTexture(_binary_tim_office_officeRIGHT_tim_start, &officeRIGHT);
                    SpuSetKey(SPU_OFF, SPU_01CH);
                }
                ChicaIsAtDoor = false;
                ChicaLocation = 1;
                noiseDoorChica = false;
                ChicaDoorInit = false;
            } else {
                if (lightR) {
                    lightR = false;
                    LoadTexture(_binary_tim_office_officeRIGHT_tim_start, &officeRIGHT);
                    SpuSetKey(SPU_OFF, SPU_01CH);
                }
                cantDoorR = true;
                isAlreadyDead = true;
                deadFrom = 3;
            }
        }
    } 

    if (ChicaLocationFrame < 0 && ChicaDifficulty != 0) {
        Ran(20);
        if (ChicaDifficulty > RAN) {
            if (ChicaLocation < 9) {
                ChicaOneTimeSkip = 0;
                ChicaLocation++;  
                if (ChicaOneTimeSkip == 0) {
                    Ran(ChicaLocation);
                    if (ChicaLocation == 1 && RAN%2 != 0) {ChicaLocation++;}
                    if (ChicaLocation == 2 && RAN%2 == 0) {ChicaLocation++;}
                    if (ChicaLocation == 3 && RAN%2 != 0) {ChicaLocation++;}
                    if (ChicaLocation == 4 && RAN%2 == 0) {ChicaLocation++;}
                    if (ChicaLocation == 5 && RAN%2 == 0) {ChicaLocation++;} 
                    ChicaOneTimeSkip = 1; 
                }
                NoiseFootstep = 1;
                FootstepAnimatronicNumber = 2;
            } else {
                if (deadFrom != 2) {ChicaLocation = 1;}
            }
        }

        ChicaLocationFrame = ChicaLocationFrameLock;
        if (ChicaLocation > 9) {
            ChicaLocation = 1;
        }
    }
    
    if (isOnCamera && FoxyLocation < 3 && FoxyLockedFrames == 0) { //No matter what camera
        if (hellNight) {FoxyLockedFrames = 25 + Ran(524);} //From 0.41 to a mere 8.74 seconds (https://technicalfnaf.fandom.com/wiki/Foxy_(Fnaf_1))
        else {FoxyLockedFrames = 50 + Ran(999);} //From 0.83 to 17.48 seconds (https://technicalfnaf.fandom.com/wiki/Foxy_(Fnaf_1))
    
    }

    if (FoxyLockedFrames > 0) {
        FoxyLockedFrames--;
    }

    if (FoxyLocationFrame < 0 && FoxyDifficulty != 0) {
        Ran(20);
        if (FoxyDifficulty > RAN && FoxyLocation != 3) {FoxyLocation++;}   
        //if (night == 7) {if(hellnight == 1) {FoxyLocationFrame = 151;} else {FoxyLocationFrame = 76;}} else {FoxyLocationFrame = FoxyLocationFramelock;}

        FoxyLocationFrame = FoxyLocationFrameLock;

        if (FoxyLocation > 4) {return;}
    }
}

void pathAIFunc(void) {
    //PATH
    if (FreddyLocation == 0) { //Stage
            MovVectorfreddy.vx = 0; 
            MovVectorfreddy.vy = -48;
        if (curCam[0] == '1' && curCam[1] == 'A') {
            if (blinkIcon > 30 || radar == 1) {
                animatronicsPresenceOnCamera[0] = 2;
            } else {
                animatronicsPresenceOnCamera[0] = 1;
            }
        } else {
                animatronicsPresenceOnCamera[0] = 0;
        }
    }
    if (FreddyLocation == 1) { //Dining area
        MovVectorfreddy.vx = 10;
        MovVectorfreddy.vy = -13;
        if (curCam[0] == '1' && curCam[1] == 'B') {
            if (blinkIcon > 30 || radar == 1) {
                animatronicsPresenceOnCamera[0] = 2;
                cameraGlitchFrame = 300;
            } else {
                animatronicsPresenceOnCamera[0] = 1;
            }
        } else {
                animatronicsPresenceOnCamera[0] = 0;
        }
    }
    if (FreddyLocation == 2) { //Restrooms (girl)
        MovVectorfreddy.vx = 57;
        MovVectorfreddy.vy = -24;
        if (curCam[0] == '7' && curCam[1] == ' ') {
            if (blinkIcon > 30 || radar == 1) {
                if (ChicaLocation != 2) {
                    animatronicsPresenceOnCamera[0] = 2;
                    cameraGlitchFrame = 300;
                } else {
                    animatronicsPresenceOnCamera[0] = 1;
                }
            } else {
                animatronicsPresenceOnCamera[0] = 1;
            } 
        }
        else {
            animatronicsPresenceOnCamera[0] = 0;
        }
    }
    if (FreddyLocation == 3) { //Kitchen 
        MovVectorfreddy.vx = 44;
        MovVectorfreddy.vy = 9;
        if (curCam[0] == '6' && curCam[1] == ' ') {
            animatronicsPresenceOnCamera[0] = 0;                // no
        } else {
            animatronicsPresenceOnCamera[0] = 0;   
        }
    }
    if (FreddyLocation == 4) { //East Hall
        MovVectorfreddy.vx = 14;
        MovVectorfreddy.vy = 7;
        if (curCam[0] == '4' && curCam[1] == 'A') {
            if (blinkIcon > 30 || radar == 1) {
                if (ChicaLocation != 5 && ChicaLocation != 6) {
                    animatronicsPresenceOnCamera[0] = 2;
                } else {
                    animatronicsPresenceOnCamera[0] = 1;
                }
            } else {
                animatronicsPresenceOnCamera[0] = 0;      
            }
        }
    }
    if (FreddyLocation == 5) { //E. Hall corner
        MovVectorfreddy.vx = 14;
        MovVectorfreddy.vy = 40;
        if (curCam[0] == '4' && curCam[1] == 'B') {
            if (blinkIcon > 30 || radar == 1) {
                animatronicsPresenceOnCamera[0] = 2;
            } else {
                animatronicsPresenceOnCamera[0] = 1;
            }
        } else {
            animatronicsPresenceOnCamera[0] = 0;   
        }
    }
    if (FreddyLocation == 6) { //'Door'
        MovVectorfreddy.vx = 999;
        MovVectorfreddy.vy = 999;
    }

    if (BonnieLocation == 0) { //Stage
            MovVectorbonnie.vx = -10;
            MovVectorbonnie.vy = -50;
        if (curCam[0] == '1' && curCam[1] == 'A') {
            if (blinkIcon > 30 || radar == 1) {
                animatronicsPresenceOnCamera[1] = 2;
            } else {
                animatronicsPresenceOnCamera[1] = 1;
            }
        } else {
            animatronicsPresenceOnCamera[1] = 0;   
        }
    }
    if (BonnieLocation == 1) { //Dining area
        MovVectorbonnie.vx = -20;
        MovVectorbonnie.vy = -21;
        if (curCam[0] == '1' && curCam[1] == 'B') {
            if (blinkIcon > 30 || radar == 1) {
                animatronicsPresenceOnCamera[1] = 2;
            } else {
                animatronicsPresenceOnCamera[1] = 1;
            }
        } else {
            animatronicsPresenceOnCamera[1] = 0;   
        }
    }
    if (BonnieLocation == 2) { //Backstage
        if (curCam[0] == '5' && curCam[1] == ' ') {
            if (blinkIcon > 30 || radar == 1) {
                animatronicsPresenceOnCamera[1] = 2;
            } else {
                animatronicsPresenceOnCamera[1] = 1;
            }
        } else {
            animatronicsPresenceOnCamera[1] = 0;   
        }
    }
    if (BonnieLocation == 3) { //Dining area (closer to cam)
        MovVectorbonnie.vx = -20;
        MovVectorbonnie.vy = -31;
        if (curCam[0] == '1' && curCam[1] == 'B') {
            if (blinkIcon > 30 || radar == 1) {
                animatronicsPresenceOnCamera[1] = 2;
            } else {
                animatronicsPresenceOnCamera[1] = 1;
            }
        } else {
            animatronicsPresenceOnCamera[1] = 0;   
        }
    }
    if (BonnieLocation == 4) { //West Hall
        MovVectorbonnie.vx = -17;
        MovVectorbonnie.vy = 8;
        if (curCam[0] == '2' && curCam[1] == 'A') {
            if (blinkIcon > 30 || radar == 1) {
                animatronicsPresenceOnCamera[1] = 2;
            } else {
                animatronicsPresenceOnCamera[1] = 1;
            }
        } else {
            animatronicsPresenceOnCamera[1] = 0;   
        }
    }
    if (BonnieLocation == 5) { //Supply closet
        MovVectorbonnie.vx = -35;
        MovVectorbonnie.vy = 24;
        if (curCam[0] == '3' && curCam[1] == ' ') {
            if (blinkIcon > 30 || radar == 1) {
                animatronicsPresenceOnCamera[1] = 2;
            } else {
                animatronicsPresenceOnCamera[1] = 1;
            }
        } else {
            animatronicsPresenceOnCamera[1] = 0;   
        }
    }
    if (BonnieLocation == 6) { //W. Hall corner
        MovVectorbonnie.vx = -19;
        MovVectorbonnie.vy = 40;
        if (curCam[0] == '2' && curCam[1] == 'B') {
            if (blinkIcon > 30 || radar == 1) {
                animatronicsPresenceOnCamera[1] = 2;
            } else {
                animatronicsPresenceOnCamera[1] = 1;
            }
        } else {
            animatronicsPresenceOnCamera[1] = 0;   
        }
    }
    if (BonnieLocation == 7) { //Door
        MovVectorbonnie.vx = 999;
        MovVectorbonnie.vy = 999;
        BonnieIsAtDoor = true;
    }

    if (ChicaLocation == 0) { //Stage
            MovVectorchica.vx = 10;
            MovVectorchica.vy = -50;
        if (curCam[0] == '1' && curCam[1] == 'A') {
            if (blinkIcon > 30 || radar == 1) {
                animatronicsPresenceOnCamera[2] = 2;
            } else {
                animatronicsPresenceOnCamera[2] = 1;
            }
        } else {
            animatronicsPresenceOnCamera[2] = 0;   
        }
    }
    if (ChicaLocation == 1) { //Dining area
        MovVectorchica.vx = 8;
        MovVectorchica.vy = -28;
        if (curCam[0] == '1' && curCam[1] == 'B') {
            if (blinkIcon > 30 || radar == 1) {
                animatronicsPresenceOnCamera[2] = 2;
            } else {
                animatronicsPresenceOnCamera[2] = 1;
            }
        } else {
            animatronicsPresenceOnCamera[2] = 0;   
        }
    }
    if (ChicaLocation == 2) { //Restrooms
        MovVectorchica.vx = 45;
        MovVectorchica.vy = -20;
        if (curCam[0] == '7' && curCam[1] == ' ') {
            if (blinkIcon > 30 || radar == 1) {
                animatronicsPresenceOnCamera[2] = 2;
            } else {
                animatronicsPresenceOnCamera[2] = 1;
            }
        } else {
            animatronicsPresenceOnCamera[2] = 0;   
        }
    }
    if (ChicaLocation == 3) { //Dining area (closer to cam)
        MovVectorchica.vx = -15;
        MovVectorchica.vy = -31;
        if (curCam[0] == '1' && curCam[1] == 'B') {
            if (blinkIcon > 30 || radar == 1) {
                animatronicsPresenceOnCamera[2] = 2;
            } else {
                animatronicsPresenceOnCamera[2] = 1;
            }
        } else {
            animatronicsPresenceOnCamera[2] = 0;   
        }
    }
    if (ChicaLocation == 4) { //Kitchen
        MovVectorchica.vx = 35;
        MovVectorchica.vy = 10;
        if (curCam[0] == '6' && curCam[1] == ' ') {
            animatronicsPresenceOnCamera[2] = 0;                  // You can't see her !
        } else {
            animatronicsPresenceOnCamera[2] = 0;            
        }
    }
    if (ChicaLocation == 5){ //East Hall
        MovVectorchica.vx = 16;
        MovVectorchica.vy = 14;
        if (curCam[0] == '4' && curCam[1] == 'A') {
            if (blinkIcon > 30 || radar == 1) {
                animatronicsPresenceOnCamera[2] = 2;
            } else {
                animatronicsPresenceOnCamera[2] = 1;
            }
        } else {
            animatronicsPresenceOnCamera[2] = 0;   
        }
    }
    if (ChicaLocation == 6){ //East Hall (closer)
        MovVectorchica.vx = 16;
        MovVectorchica.vy = 20;
        if (curCam[0] == '4' && curCam[1] == 'A') {
            if (blinkIcon > 30 || radar == 1) {
                animatronicsPresenceOnCamera[2] = 2;
            } else {
                animatronicsPresenceOnCamera[2] = 1;
            }
        } else {
            animatronicsPresenceOnCamera[2] = 0;   
        }
    }
    if (ChicaLocation == 7) { //E. Hall corner
        MovVectorchica.vx = 19;
        MovVectorchica.vy = 40;
        if (curCam[0] == '4' && curCam[1] == 'B') {
            if (blinkIcon > 30 || radar == 1) {
                animatronicsPresenceOnCamera[2] = 2;
            } else {
                animatronicsPresenceOnCamera[2] = 1;
            }
        } else {
            animatronicsPresenceOnCamera[2] = 0;   
        }
    }
    if (ChicaLocation == 8) { //Door
        MovVectorchica.vx = 999; //So that we can't see her in cam
        MovVectorchica.vy = 999;
        ChicaIsAtDoor = true;
    }

    if (FoxyLocation == 0) { //Pirate Cove
        MovVectorfoxy.vx = -45;
        MovVectorfoxy.vy = -9;
        if (curCam[0] == '1' && curCam[1] == 'C') {
            if (blinkIcon > 30 || radar == 1) {
                animatronicsPresenceOnCamera[3] = 2;
            } else {
                animatronicsPresenceOnCamera[3] = 1;
            }
        } else {
            animatronicsPresenceOnCamera[3] = 0;   
        }
    }
    if (FoxyLocation == 1) { //Pirate Cove
        MovVectorfoxy.vx = -40;
        MovVectorfoxy.vy = -9;
        if (curCam[0] == '1' && curCam[1] == 'C') {
            if (blinkIcon > 30 || radar == 1) {
                animatronicsPresenceOnCamera[3] = 2;
            } else {
                animatronicsPresenceOnCamera[3] = 1;
            }
        } else {
            animatronicsPresenceOnCamera[3] = 0;   
        }
    }
    if (FoxyLocation == 2) { //Pirate Cove (out)
        MovVectorfoxy.vx = -30;
        MovVectorfoxy.vy = -6;
        if (curCam[0] == '1' && curCam[1] == 'C') {
            if (blinkIcon > 30 || radar == 1) {
                animatronicsPresenceOnCamera[3] = 2;
            } else {
                animatronicsPresenceOnCamera[3] = 1;
            }
        } else {
            animatronicsPresenceOnCamera[3] = 0;   
        }
    }
    if (FoxyLocation == 3) { //West Hall
        if (curCam[0] == '2' && curCam[1] == 'A') {
            if (blinkIcon > 30 || radar == 1) {
                animatronicsPresenceOnCamera[3] = 2;
            } else {
                animatronicsPresenceOnCamera[3] = 1;
            }
        } else {
            animatronicsPresenceOnCamera[3] = 0;   
        }
        if (battery > 0 && AM != 6) {
            if (FoxyRunningFrames == 0) {
                MovVectorfoxy.vx = -17;
                MovVectorfoxy.vy = 11;
            }
            FoxyWaitingToRun--;
            if (curCam[0] == '2' && curCam[1] == 'A' || FoxyWaitingToRun == 0) {
                if (FoxyRunningFrames == 0) {
                    FoxyRunningFrames++;
                    SpuSetKey(SPU_ON, SPU_10CH);
                }
            }   
            if (FoxyRunningFrames != 0) { //For not having to put the cam on for foxy to move 
                if (MovVectorfoxy.vy < 36) {
                    FoxyRunningFrames++;
                    if (FoxyRunningFrames%2 == 0)
                    MovVectorfoxy.vy++;
                } else {
                    
                    if (doorClosedL) {
                        if (!(MovVectorleftdoor.vy < -61)) {
                            FoxyLocation = 0;
                            FoxyWaitingToRun = 500;
                            FoxyRunningFrames = 0;
                            FoxyKnock = true;
                            battery -= FoxyDrainPower;
                            FoxyDrainPower = FoxyDrainPower + 5;   
                        }
                    } else {
                        dead = 1;
                        deadFrom = 4;
                    }
                }
            }
        }
    }
    if (SparkyLocation == 0) {
        MovVectorsparky.vx = 999;
        MovVectorsparky.vy = 999;
    }
    if (SparkyLocation == 1) {
        MovVectorsparky.vx = -42;
        MovVectorsparky.vy = -39;
    }
}

void Screamer(void) {
    if (isOnCamera) {isOnCamera = false;}

    screamerFrame++;

    makepoly(7);

    if (screamerFrame == 1) {
        SpuSetKey(SPU_OFF, SPU_ALLCH);
        SpuSetKey(SPU_ON, SPU_06CH);


        //CdControlF(CdlStop,0);

        ChangeMusic(7);
    }

    if (screamerFrame == 47) {
        menu = 4;
    }

    spriteFrame--;

    if (spriteFrame < 1) {

        spriteSheet++;

        if (deadFrom == 2 || deadFrom == 3) {spriteFrame = 3;} else {spriteFrame = 4;}

        switch(deadFrom) {
            case 1:

                if (!BlackOutInit) { //Special, knock you out pretty quickly
                    switch(spriteSheet) {
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
                            menu = 4;
                        break;
                    }
                } else {
                    switch(spriteSheet) {
                        case 1:
                            LoadTexture(_binary_tim_screamers_jumpF20_tim_start, &jumpscare);
                        break;
                        case 2:
                            LoadTexture(_binary_tim_screamers_jumpF21_tim_start, &jumpscare);
                        break;
                        case 3:
                            LoadTexture(_binary_tim_screamers_jumpF22_tim_start, &jumpscare);
                        break;
                        case 4:
                            LoadTexture(_binary_tim_screamers_jumpF24_tim_start, &jumpscare);
                        break;
                        case 5:
                            LoadTexture(_binary_tim_screamers_jumpF25_tim_start, &jumpscare);
                        break;
                        case 6:
                            LoadTexture(_binary_tim_screamers_jumpF26_tim_start, &jumpscare);
                        break;
                        case 7:
                            SpuSetKey(SPU_OFF, SPU_06CH);
                            menu = 4;
                        break;
                    }
                } //Freddy

            break;
            case 2: //Bonnie

                switch(spriteSheet) {
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
                        menu = 4;
                    break;
                }
            break;
            case 3: //Chica
                switch(spriteSheet) {
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
                    case 6:
                        LoadTexture(_binary_tim_screamers_jumpC3_tim_start, &jumpscare);
                    break;
                    case 7:
                        LoadTexture(_binary_tim_screamers_jumpC2_tim_start, &jumpscare);
                    break;
                    case 8:
                        LoadTexture(_binary_tim_screamers_jumpC_tim_start, &jumpscare);
                    break;
                    case 9:
                        SpuSetKey(SPU_OFF, SPU_06CH);
                        menu = 4;
                    break;
                }
            break;
            case 4: //Foxy

                if (spriteSheet == 1) {
                    LoadTexture(_binary_tim_screamers_jumpFO_tim_start, &jumpscare);
                }
                if (spriteSheet == 2) {
                    LoadTexture(_binary_tim_screamers_jumpFO2_tim_start, &jumpscare);
                }
                if (spriteSheet == 3) {
                    LoadTexture(_binary_tim_screamers_jumpFO3_tim_start, &jumpscare);
                }
                if (spriteSheet == 4) {
                    LoadTexture(_binary_tim_screamers_jumpFO4_tim_start, &jumpscare);
                }
                if (spriteSheet == 5) {
                    LoadTexture(_binary_tim_screamers_jumpFO5_tim_start, &jumpscare);
                }
                if (spriteSheet == 6) {
                    SpuSetKey(SPU_OFF, SPU_06CH);
                    menu = 4;
                }
            break;
        }
    }
}

void animatronicWaitForCam(void) {
    AnimatronicWaitingFrame++;

    if (!isOnCamera || AnimatronicWaitingFrame == 1800) {
        dead = true;
    }
}