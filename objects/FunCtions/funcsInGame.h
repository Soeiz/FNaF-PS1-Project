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
    if (light1) {light1 = 0;}
    if (light2) {light2 = 0;}
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

    FrameCounter++;
}
void chargeNtimeFunc(void) {
    FrameCounter++;

    if (fanframe > 6) {fanframe = 1;} else {fanframe++;}


    if (camera == 0 && charge > 0) {
        switch(fanframe) {
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

    Glitch++;
    Glitch = Glitch + 3 * 8;
    if (Glitch > 1987) {Glitch = Glitch - 987;}

    if (FrameCounter == FrameCounterlimit) {
        AM++;
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
            Ran(6);
            if (RAN == 1) {ChargeCounter = ChargeCounter / 2;} //Because apparently FNAF Ps1 doesn't have power issues. IT HAS NOW HAHAHAHAHAHAH
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