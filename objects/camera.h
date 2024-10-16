
//This function take in charge the cameras.
//Why ? It's Simple, because the game.c was LONG ASF. Longer than my life savings I'd say. (10 euros) 
//(and also because it was harder to look for a specific thing and having to scroll like 100000 times to pass by the thing we want. Here, you know you are at the cam func.)
// *copy-paste old comment and change three-four words* "Yeah, That'll work"
void cameraloc(void) {
    //Gosh, This is gonna be long
    if (curcam[0] == '1' && curcam[1] == 'A') {
        MovVectorpolycamgreyogreen.vx = -35;
        MovVectorpolycamgreyogreen.vy = -103;  
        sprintf(curcamname, "Show Room");
        if (limitercameraD == 0 && pad & PADLdown || limitercameraD == 0 && pad >> 16 & PADLdown && twoplayermode == 1) { 
            curcam[0] = '1';
            curcam[1] = 'B';
            SpuSetKey(SPU_ON, SPU_04CH);
            limitercameraD = 1;
        }
    }
    if (curcam[0] == '1' && curcam[1] == 'B') {
        MovVectorpolycamgreyogreen.vx = -40;
        MovVectorpolycamgreyogreen.vy = -83;  
        sprintf(curcamname, "Dining Area");
        if (limitercameraU == 0 && pad & PADLup || limitercameraU == 0 && pad >> 16 & PADLup && twoplayermode == 1) {
            curcam[0] = '1';
            curcam[1] = 'A';
            SpuSetKey(SPU_ON, SPU_04CH);
            limitercameraU = 1;
        }
        if (limitercameraD == 0 && pad & PADLdown || limitercameraD == 0 && pad >> 16 & PADLdown && twoplayermode == 1) { 
            curcam[0] = '1';
            curcam[1] = 'C';
            SpuSetKey(SPU_ON, SPU_04CH);
            limitercameraD = 1;
        }
        if (limitercameraL == 0 && pad & PADLleft || limitercameraL == 0 && pad >> 16 & PADLleft && twoplayermode == 1) { 
            curcam[0] = '5';
            curcam[1] = ' ';
            SpuSetKey(SPU_ON, SPU_04CH);
            limitercameraL = 1;
        }
        if (limitercameraR == 0 && pad & PADLright || limitercameraR == 0 && pad >> 16 & PADLright && twoplayermode == 1) { 
            curcam[0] = '7';
            curcam[1] = ' ';
            SpuSetKey(SPU_ON, SPU_04CH);
            limitercameraR = 1;
        }
        itsmepiratecove = 0;
    }
    if (curcam[0] == '1' && curcam[1] == 'C') {
        MovVectorpolycamgreyogreen.vx = -65;
        MovVectorpolycamgreyogreen.vy = -35;  
        if (itsmepiratecove) {
            sprintf(curcamname, "ITS ME");
        } else {
            sprintf(curcamname, "Pirate Cove");
        }
        if (camera == 1) {
            if (itsmepiratecovecooldown == 0) {
                if (foxylocation == 3) {
                    Ran(100);
                    if (RAN == 1 && itsmepiratecove == 0) {itsmepiratecove = 1;} else {itsmepiratecove = 0;}   
                    itsmepiratecovecooldown = 1;
                } else {itsmepiratecove = 0;}
            }
        }

        if (limitercameraU == 0 && pad & PADLup || limitercameraU == 0 && pad >> 16 & PADLup && twoplayermode == 1) { 
            curcam[0] = '1';
            curcam[1] = 'B';
            SpuSetKey(SPU_ON, SPU_04CH);
            limitercameraU = 1;
        }
        if (limitercameraD == 0 && pad & PADLdown || limitercameraD == 0 && pad >> 16 & PADLdown && twoplayermode == 1) { 
            curcam[0] = '3';
            curcam[1] = ' ';
            SpuSetKey(SPU_ON, SPU_04CH);
            limitercameraD = 1;
        }
        if (limitercameraL == 0 && pad & PADLleft || limitercameraL == 0 && pad >> 16 & PADLleft && twoplayermode == 1) { 
            curcam[0] = '5';
            curcam[1] = ' ';
            SpuSetKey(SPU_ON, SPU_04CH);
            limitercameraL = 1;
        }
    }
    if (curcam[0] == '3' && curcam[1] == ' ') {   
        MovVectorpolycamgreyogreen.vx = -70;
        MovVectorpolycamgreyogreen.vy = 20;  
        sprintf(curcamname, "Supply Closet");
        if (limitercameraU == 0 && pad & PADLup || limitercameraU == 0 && pad >> 16 & PADLup && twoplayermode == 1) { 
            curcam[0] = '1';
            curcam[1] = 'C';
            SpuSetKey(SPU_ON, SPU_04CH);
            limitercameraU = 1;
        }
        if (limitercameraD == 0 && pad & PADLdown || limitercameraD == 0 && pad >> 16 & PADLdown && twoplayermode == 1) { 
            curcam[0] = '2';
            curcam[1] = 'A';
            SpuSetKey(SPU_ON, SPU_04CH);
            limitercameraD = 1;
        }
        if (limitercameraR == 0 && pad & PADLright || limitercameraR == 0 && pad >> 16 & PADLright && twoplayermode == 1) { 
            curcam[0] = '6';
            curcam[1] = ' ';
            SpuSetKey(SPU_ON, SPU_04CH);
            limitercameraR = 1;
        }
        itsmepiratecove = 0;
    }
    if (curcam[0] == '2' && curcam[1] == 'A') {      
        MovVectorpolycamgreyogreen.vx = -35;
        MovVectorpolycamgreyogreen.vy = 52;   
        sprintf(curcamname, "West Hall");
        if (limitercameraU == 0 && pad & PADLup || limitercameraU == 0 && pad >> 16 & PADLup && twoplayermode == 1) { 
            curcam[0] = '3';
            curcam[1] = ' ';
            SpuSetKey(SPU_ON, SPU_04CH);
            limitercameraU = 1;
        }
        if (limitercameraD == 0 && pad & PADLdown || limitercameraD == 0 && pad >> 16 & PADLdown && twoplayermode == 1) { 
            curcam[0] = '2';
            curcam[1] = 'B';
            SpuSetKey(SPU_ON, SPU_04CH);
            limitercameraD = 1;
        }
        if (limitercameraR == 0 && pad & PADLright || limitercameraR == 0 && pad >> 16 & PADLright && twoplayermode == 1) { 
            curcam[0] = '4';
            curcam[1] = 'A';
            SpuSetKey(SPU_ON, SPU_04CH);
            limitercameraR = 1;
        }
        itsmeehallcorner = 0;
        itsmeehallcooldown = 0;
    }
    if (curcam[0] == '2' && curcam[1] == 'B') { 
        MovVectorpolycamgreyogreen.vx = -35;
        MovVectorpolycamgreyogreen.vy = 67;            
        if (itsmeehallcorner == 0) {
            sprintf(curcamname, "W. Hall Corner");
        } else {
            sprintf(curcamname, "ITS ME");
        }
        if (camera == 1) {
            if (itsmeehallcornercooldown == 0) {
                Ran(100);
                if (RAN == 1 && itsmeehallcorner == 0) {
                    itsmeehallcorner = 1;
                } else {
                    itsmeehallcorner = 0;
                }   
                itsmeehallcornercooldown = 1;
            }
        }
        if (limitercameraU == 0 && pad & PADLup || limitercameraU == 0 && pad >> 16 & PADLup && twoplayermode == 1) { 
            curcam[0] = '2';
            curcam[1] = 'A';
            SpuSetKey(SPU_ON, SPU_04CH);
            limitercameraU = 1;
        }
        if (limitercameraR == 0 && pad & PADLright || limitercameraR == 0 && pad >> 16 & PADLright && twoplayermode == 1) { 
            curcam[0] = '4';
            curcam[1] = 'B';
            SpuSetKey(SPU_ON, SPU_04CH);
            limitercameraR = 1;
        }
    }
    if (curcam[0] == '5' && curcam[1] == ' ') {  
        MovVectorpolycamgreyogreen.vx = -89;
        MovVectorpolycamgreyogreen.vy = -54;              
        sprintf(curcamname, "Back Stage");
        if (limitercameraR == 0 && pad & PADLright || limitercameraR == 0 && pad >> 16 & PADLright && twoplayermode == 1) { 
            curcam[0] = '1';
            curcam[1] = 'B';
            SpuSetKey(SPU_ON, SPU_04CH);
            limitercameraR = 1;
        }
        if (limitercameraD == 0 && pad & PADLdown || limitercameraD == 0 && pad >> 16 & PADLdown && twoplayermode == 1) { 
            curcam[0] = '1';
            curcam[1] = 'C';
            SpuSetKey(SPU_ON, SPU_04CH);
            limitercameraD = 1;
        }
        itsmepiratecove = 0;
    }
    if (curcam[0] == '4' && curcam[1] == 'A') {    
        MovVectorpolycamgreyogreen.vx = 37;
        MovVectorpolycamgreyogreen.vy = 52;   
        if (itsmeehall == 0) {             
            sprintf(curcamname, "East Hall");
        } else {
            sprintf(curcamname, "ITS ME");
        }
        if (camera == 1) {
            if (itsmeehallcooldown == 0) {
                Ran(100);
                if (RAN == 1 && itsmeehall == 0) {
                    itsmeehall = 1;
                } else {
                    itsmeehall = 0;
                }   
                itsmeehallcooldown = 1;
            }
        }
        if (limitercameraL == 0 && pad & PADLleft || limitercameraL == 0 && pad >> 16 & PADLleft && twoplayermode == 1) { 
            curcam[0] = '2';
            curcam[1] = 'A';
            SpuSetKey(SPU_ON, SPU_04CH);
            limitercameraL = 1;
        }
        if (limitercameraD == 0 && pad & PADLdown || limitercameraD == 0 && pad >> 16 & PADLdown && twoplayermode == 1) { 
            curcam[0] = '4';
            curcam[1] = 'B';
            SpuSetKey(SPU_ON, SPU_04CH);
            limitercameraD = 1;
        }
        if (limitercameraU == 0 && pad & PADLup || limitercameraU == 0 && pad >> 16 & PADLup && twoplayermode == 1) { 
            curcam[0] = '6';
            curcam[1] = ' ';
            SpuSetKey(SPU_ON, SPU_04CH);
            limitercameraU = 1;
        }
    }
    if (curcam[0] == '4' && curcam[1] == 'B') {       
        MovVectorpolycamgreyogreen.vx = 37;
        MovVectorpolycamgreyogreen.vy = 67;  
        sprintf(curcamname, "E. Hall Corner");
        if (limitercameraL == 0 && pad & PADLleft || limitercameraL == 0 && pad >> 16 & PADLleft && twoplayermode == 1) { 
            curcam[0] = '2';
            curcam[1] = 'B';
            SpuSetKey(SPU_ON, SPU_04CH);
            limitercameraL = 1;
        }
        if (limitercameraU == 0 && pad & PADLup || limitercameraU == 0 && pad >> 16 & PADLup && twoplayermode == 1) { 
            curcam[0] = '4';
            curcam[1] = 'A';
            SpuSetKey(SPU_ON, SPU_04CH);
            limitercameraU = 1;
        }
        itsmeehallcorner = 0;
        itsmeehall = 0;
    }
    if (curcam[0] == '6' && curcam[1] == ' ') {
        MovVectorpolycamgreyogreen.vx = 50520;
        MovVectorpolycamgreyogreen.vy = -5028;  
        sprintf(curcamname, "Kitchen (no video)");
        if (limitercameraL == 0 && pad & PADLleft || limitercameraL == 0 && pad >> 16 & PADLleft && twoplayermode == 1) { 
            curcam[0] = '3';
            curcam[1] = ' ';
            SpuSetKey(SPU_ON, SPU_04CH);
            limitercameraL = 1;
        }
        if (limitercameraU == 0 && pad & PADLup || limitercameraU == 0 && pad >> 16 & PADLup && twoplayermode == 1) { 
            curcam[0] = '7';
            curcam[1] = ' ';
            SpuSetKey(SPU_ON, SPU_04CH);
            limitercameraU = 1;
        }
        if (limitercameraD == 0 && pad & PADLdown || limitercameraD == 0 && pad >> 16 & PADLdown && twoplayermode == 1) { 
            curcam[0] = '4';
            curcam[1] = 'A';
            SpuSetKey(SPU_ON, SPU_04CH);
            limitercameraD = 1;
        }
        itsmeehallcooldown = 0;
    }
    if (curcam[0] == '7' && curcam[1] == ' ') {
        MovVectorpolycamgreyogreen.vx = 100;
        MovVectorpolycamgreyogreen.vy = -60;  
        sprintf(curcamname, "Restrooms");
        if (limitercameraL == 0 && pad & PADLleft || limitercameraL == 0 && pad >> 16 & PADLleft && twoplayermode == 1) { 
            curcam[0] = '1';
            curcam[1] = 'B';
            SpuSetKey(SPU_ON, SPU_04CH);
            limitercameraL = 1;
        }
        if (limitercameraD == 0 && pad & PADLdown || limitercameraD == 0 && pad >> 16 & PADLdown && twoplayermode == 1) { 
            curcam[0] = '6';
            curcam[1] = ' ';
            SpuSetKey(SPU_ON, SPU_04CH);
            limitercameraD = 1;
        }
    }

    if (!(pad & PADLdown || pad >> 16 & PADLdown) && limitercameraD == 1) {limitercameraD = 0;}
    if (!(pad & PADLup || pad >> 16 & PADLup) && limitercameraU == 1) {limitercameraU = 0;}
    if (!(pad & PADLright || pad >> 16 & PADLright) && limitercameraR == 1) {limitercameraR = 0;}
    if (!(pad & PADLleft || pad >> 16 & PADLleft) && limitercameraL == 1) {limitercameraL = 0;}
}