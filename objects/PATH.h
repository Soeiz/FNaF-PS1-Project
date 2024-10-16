void pathfunc(void) {
    //Finally know another way to store that piece of (shit) code
    //PATH
    if (freddylocation == 0) { //Stage
            MovVectorfreddy.vx = 0; 
            MovVectorfreddy.vy = -48;
        if (curcam[0] == '1' && curcam[1] == 'A') {
            if (blinkicon > 30 || radar == 1) {
                animatronicscamera[0] = 2;
            } else {
                animatronicscamera[0] = 1;
            }
        } else {
                animatronicscamera[0] = 0;
        }
        if (bonnielocation != 0 && chicalocation != 0) {
            if (curcam[0] == '1' && curcam[1] == 'A' && freddyliljumpscare == 0 && freddyliljumpscarecooldown == 0) {
                Ran(100);
                if (RAN == 1) {
                    freddyliljumpscare = 1;
                } else {
                    freddyliljumpscare = 0;
                }
                freddyliljumpscarecooldown = 1;
            }
            if (freddyliljumpscare == 1) {MovVectorfreddy.vx = -10;} else {MovVectorfreddy.vx = 0;}
        }
    }
    if (freddylocation == 1) { //Dining area
        MovVectorfreddy.vx = 10;
        MovVectorfreddy.vy = -13;
        if (curcam[0] == '1' && curcam[1] == 'B') {
            if (blinkicon > 30 || radar == 1) {
                animatronicscamera[0] = 2;
            } else {
                animatronicscamera[0] = 1;
            }
        } else {
                animatronicscamera[0] = 0;
        }
    }
    if (freddylocation == 2) { //Restrooms (girl)
        MovVectorfreddy.vx = 57;
        MovVectorfreddy.vy = -24;
        if (curcam[0] == '7' && curcam[1] == ' ') {
            if (blinkicon > 30 || radar == 1) {
                if (chicalocation != 2) {
                    animatronicscamera[0] = 2;
                } else {
                    animatronicscamera[0] = 1;
                }
            } else {
                animatronicscamera[0] = 1;
            } 
        }
        else {
            animatronicscamera[0] = 0;
        }
    }
    if (freddylocation == 3) { //Kitchen 
        MovVectorfreddy.vx = 44;
        MovVectorfreddy.vy = 9;
        if (curcam[0] == '6' && curcam[1] == ' ') {
            animatronicscamera[0] = 0;                // no
        } else {
            animatronicscamera[0] = 0;   
        }
    }
    if (freddylocation == 4) { //East Hall
        MovVectorfreddy.vx = 14;
        MovVectorfreddy.vy = 7;
        if (curcam[0] == '4' && curcam[1] == 'A') {
            if (blinkicon > 30 || radar == 1) {
                if (chicalocation != 5 && chicalocation != 6) {
                    animatronicscamera[0] = 2;
                } else {
                    animatronicscamera[0] = 1;
                }
            } else {
                animatronicscamera[0] = 0;      
            }
        }
    }
    if (freddylocation == 5) { //E. Hall corner
        MovVectorfreddy.vx = 14;
        MovVectorfreddy.vy = 40;
        if (curcam[0] == '4' && curcam[1] == 'B') {
            if (blinkicon > 30 || radar == 1) {
                animatronicscamera[0] = 2;
            } else {
                animatronicscamera[0] = 1;
            }
        } else {
            animatronicscamera[0] = 0;   
        }
    }
    if (freddylocation == 6) { //'Door'
        MovVectorfreddy.vx = 999;
        MovVectorfreddy.vy = 999;
        if (doorclosedR == 0) {
            if (camera == 1) {isalreadydeadlow = 1;}
            Ran(100);
            framedeadpossi--;
            if (RAN < 20 && framedeadpossi == 0) {
                dead = 1;
                deadfrom = 1;
            } else {framedeadpossi = 60;}
        } else {freddylocation = 4;}
    }

    if (bonnielocation == 0) { //Stage
            MovVectorbonnie.vx = -10;
            MovVectorbonnie.vy = -50;
        if (curcam[0] == '1' && curcam[1] == 'A') {
            if (blinkicon > 30 || radar == 1) {
                animatronicscamera[1] = 2;
            } else {
                animatronicscamera[1] = 1;
            }
        } else {
            animatronicscamera[1] = 0;   
        }
    }
    if (bonnielocation == 1) { //Dining area
        MovVectorbonnie.vx = -20;
        MovVectorbonnie.vy = -21;
        if (curcam[0] == '1' && curcam[1] == 'B') {
            if (blinkicon > 30 || radar == 1) {
                animatronicscamera[1] = 2;
            } else {
                animatronicscamera[1] = 1;
            }
        } else {
            animatronicscamera[1] = 0;   
        }
    }
    if (bonnielocation == 2) { //Backstage
        if (curcam[0] == '5' && curcam[1] == ' ') {
            if (blinkicon > 30 || radar == 1) {
                animatronicscamera[1] = 2;
            } else {
                animatronicscamera[1] = 1;
            }
        } else {
            animatronicscamera[1] = 0;   
        }
        if (camera == 1) {
            if (curcam[0] == '5' && bonnieliljumpscare == 0 && bonnieliljumpscarecooldown == 0) {
                Ran(100);
                if (RAN == 1) {
                    bonnieliljumpscare = 1;
                } else {
                    bonnieliljumpscare = 0;
                }
                bonnieliljumpscarecooldown = 1;
            }
        }
        if (bonnieliljumpscare == 1) {
            MovVectorbonnie.vx = -45;
            MovVectorbonnie.vy = -33;
        } else {
            MovVectorbonnie.vx = -45;
            MovVectorbonnie.vy = -39;
        }
    }
    if (bonnielocation == 3) { //Dining area (closer to cam)
        MovVectorbonnie.vx = -20;
        MovVectorbonnie.vy = -31;
        if (curcam[0] == '1' && curcam[1] == 'B') {
            if (blinkicon > 30 || radar == 1) {
                animatronicscamera[1] = 2;
            } else {
                animatronicscamera[1] = 1;
            }
        } else {
            animatronicscamera[1] = 0;   
        }
    }
    if (bonnielocation == 4) { //West Hall
        MovVectorbonnie.vx = -17;
        MovVectorbonnie.vy = 8;
        if (curcam[0] == '2' && curcam[1] == 'A') {
            if (blinkicon > 30 || radar == 1) {
                animatronicscamera[1] = 2;
            } else {
                animatronicscamera[1] = 1;
            }
        } else {
            animatronicscamera[1] = 0;   
        }
    }
    if (bonnielocation == 5) { //Supply closet
        MovVectorbonnie.vx = -35;
        MovVectorbonnie.vy = 24;
        if (curcam[0] == '3' && curcam[1] == ' ') {
            if (blinkicon > 30 || radar == 1) {
                animatronicscamera[1] = 2;
            } else {
                animatronicscamera[1] = 1;
            }
        } else {
            animatronicscamera[1] = 0;   
        }
    }
    if (bonnielocation == 6) { //W. Hall corner
        MovVectorbonnie.vx = -19;
        MovVectorbonnie.vy = 40;
        if (curcam[0] == '2' && curcam[1] == 'B') {
            if (blinkicon > 30 || radar == 1) {
                animatronicscamera[1] = 2;
            } else {
                animatronicscamera[1] = 1;
            }
        } else {
            animatronicscamera[1] = 0;   
        }
    }
    if (bonnielocation == 7) { //Door
        MovVectorbonnie.vx = 999;
        MovVectorbonnie.vy = 999;
        bonnieDoor = 1;
    }

    if (chicalocation == 0) { //Stage
            MovVectorchica.vx = 10;
            MovVectorchica.vy = -50;
        if (curcam[0] == '1' && curcam[1] == 'A') {
            if (blinkicon > 30 || radar == 1) {
                animatronicscamera[2] = 2;
            } else {
                animatronicscamera[2] = 1;
            }
        } else {
            animatronicscamera[2] = 0;   
        }
    }
    if (chicalocation == 1) { //Dining area
        MovVectorchica.vx = 8;
        MovVectorchica.vy = -28;
        if (curcam[0] == '1' && curcam[1] == 'B') {
            if (blinkicon > 30 || radar == 1) {
                animatronicscamera[2] = 2;
            } else {
                animatronicscamera[2] = 1;
            }
        } else {
            animatronicscamera[2] = 0;   
        }
    }
    if (chicalocation == 2) { //Restrooms
        MovVectorchica.vx = 45;
        MovVectorchica.vy = -20;
        if (curcam[0] == '7' && curcam[1] == ' ') {
            if (blinkicon > 30 || radar == 1) {
                animatronicscamera[2] = 2;
            } else {
                animatronicscamera[2] = 1;
            }
        } else {
            animatronicscamera[2] = 0;   
        }
    }
    if (chicalocation == 3) { //Dining area (closer to cam)
        MovVectorchica.vx = -15;
        MovVectorchica.vy = -31;
        if (curcam[0] == '1' && curcam[1] == 'B') {
            if (blinkicon > 30 || radar == 1) {
                animatronicscamera[2] = 2;
            } else {
                animatronicscamera[2] = 1;
            }
        } else {
            animatronicscamera[2] = 0;   
        }
    }
    if (chicalocation == 4) { //Kitchen
        MovVectorchica.vx = 35;
        MovVectorchica.vy = 10;
        if (curcam[0] == '6' && curcam[1] == ' ') {
            animatronicscamera[2] = 0;                  // You can't see her !
        } else {
            animatronicscamera[2] = 0;            
        }
    }
    if (chicalocation == 5){ //East Hall
        MovVectorchica.vx = 16;
        MovVectorchica.vy = 14;
        if (curcam[0] == '4' && curcam[1] == 'A') {
            if (blinkicon > 30 || radar == 1) {
                animatronicscamera[2] = 2;
            } else {
                animatronicscamera[2] = 1;
            }
        } else {
            animatronicscamera[2] = 0;   
        }
    }
    if (chicalocation == 6){ //East Hall (closer)
        MovVectorchica.vx = 16;
        MovVectorchica.vy = 20;
        if (curcam[0] == '4' && curcam[1] == 'A') {
            if (blinkicon > 30 || radar == 1) {
                animatronicscamera[2] = 2;
            } else {
                animatronicscamera[2] = 1;
            }
        } else {
            animatronicscamera[2] = 0;   
        }
    }
    if (chicalocation == 7) { //E. Hall corner
        MovVectorchica.vx = 19;
        MovVectorchica.vy = 40;
        if (curcam[0] == '4' && curcam[1] == 'B') {
            if (blinkicon > 30 || radar == 1) {
                animatronicscamera[2] = 2;
            } else {
                animatronicscamera[2] = 1;
            }
        } else {
            animatronicscamera[2] = 0;   
        }
    }
    if (chicalocation == 8) { //Door
        MovVectorchica.vx = 999; //So that we can't see her in cam
        MovVectorchica.vy = 999;
        chicaDoor = 1;
    }

    if (foxylocation == 0) { //Pirate Cove
        MovVectorfoxy.vx = -45;
        MovVectorfoxy.vy = -9;
        if (curcam[0] == '1' && curcam[1] == 'C') {
            if (blinkicon > 30 || radar == 1) {
                animatronicscamera[3] = 2;
            } else {
                animatronicscamera[3] = 1;
            }
        } else {
            animatronicscamera[3] = 0;   
        }
    }
    if (foxylocation == 1) { //Pirate Cove
        MovVectorfoxy.vx = -40;
        MovVectorfoxy.vy = -9;
        if (curcam[0] == '1' && curcam[1] == 'C') {
            if (blinkicon > 30 || radar == 1) {
                animatronicscamera[3] = 2;
            } else {
                animatronicscamera[3] = 1;
            }
        } else {
            animatronicscamera[3] = 0;   
        }
    }
    if (foxylocation == 2) { //Pirate Cove (out)
        MovVectorfoxy.vx = -30;
        MovVectorfoxy.vy = -6;
        if (curcam[0] == '1' && curcam[1] == 'C') {
            if (blinkicon > 30 || radar == 1) {
                animatronicscamera[3] = 2;
            } else {
                animatronicscamera[3] = 1;
            }
        } else {
            animatronicscamera[3] = 0;   
        }
    }
    if (foxylocation == 3) { //West Hall
        if (curcam[0] == '2' && curcam[1] == 'A') {
            if (blinkicon > 30 || radar == 1) {
                animatronicscamera[3] = 2;
            } else {
                animatronicscamera[3] = 1;
            }
        } else {
            animatronicscamera[3] = 0;   
        }
        if (charge > 0 && AM != 6) {
            if (foxyrunningframes == 0) {
                MovVectorfoxy.vx = -17;
                MovVectorfoxy.vy = 11;
            }
            foxywaiting--;
            if (curcam[0] == '2' && curcam[1] == 'A' || foxywaiting == 0) {
                if (foxyrunningframes == 0) {
                    foxyrunningframes++;
                    SpuSetKey(SPU_ON, SPU_10CH);
                }
            }   
            if (foxyrunningframes != 0) { //For not having to put the cam on for foxy to move 
                if (MovVectorfoxy.vy < 36) {
                    foxyrunningframes++;
                    if (foxyrunningframes%2 == 0)
                    MovVectorfoxy.vy++;
                } else {
                    if (!(doorclosedL == 1 && MovVectorleftdoor.vy < -61))  {

                    }
                    if (doorclosedL == 1) {
                        if (!(MovVectorleftdoor.vy < -61)) {
                            foxylocation = 0;
                            blockedanimatronic++;
                            foxywaiting = 500;
                            foxyrunningframes = 0;
                            foxysknock = 1;
                            charge = charge - foxydrainpower;
                            foxydrainpower = foxydrainpower + 5;   
                        }
                    } else {
                        dead = 1;
                        deadfrom = 4;
                    }
                }
            }
        }
    }
    if (sparkylocation == 0) {
        MovVectorsparky.vx = 999;
        MovVectorsparky.vy = 999;
    }
    if (sparkylocation == 1) {
        MovVectorsparky.vx = -42;
        MovVectorsparky.vy = -39;
    }
}