//This function take in charge the cameras.
//Why ? It's Simple, because the game.c was LONG ASF. Longer than my life savings I'd say. (10 euros) 
//(and also because it was harder to look for a specific thing and having to scroll like 100000 times to pass by the thing we want. Here, you know you are at the cam func.)
// *copy-paste old comment and change three-four words* "Yeah, That'll work"
void cameraloc(void) {
    //Gosh, This is gonna be long
    if (curcam[0] == '1' && curcam[1] == 'A') {
        MovVectorpolycamgreyogreen.vx = -35;
        MovVectorpolycamgreyogreen.vy = -103;  
        curcamname[0] = 'S';
        curcamname[1] = 'h';
        curcamname[2] = 'o';
        curcamname[3] = 'w';
        curcamname[4] = ' ';
        curcamname[5] = 'S';
        curcamname[6] = 't';
        curcamname[7] = 'a';
        curcamname[8] = 'g';
        curcamname[9] = 'e';
        curcamname[10] = ' '; //Need to put little spaces like that in case the old name is longer
        curcamname[11] = ' ';
        curcamname[12] = ' ';
        curcamname[13] = ' ';
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
        curcamname[0] = 'D';
        curcamname[1] = 'i';
        curcamname[2] = 'n';
        curcamname[3] = 'i';
        curcamname[4] = 'n';
        curcamname[5] = 'g';
        curcamname[6] = ' ';
        curcamname[7] = 'a';
        curcamname[8] = 'r';
        curcamname[9] = 'e';
        curcamname[10] = 'a';
        curcamname[11] = ' ';
        curcamname[12] = ' ';
        curcamname[13] = ' ';
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
        if (itsmepiratecove == 0) {
            curcamname[0] = 'P';
            curcamname[1] = 'i';
            curcamname[2] = 'r';
            curcamname[3] = 'a';
            curcamname[4] = 't';
            curcamname[5] = 'e';
            curcamname[6] = ' ';
            curcamname[7] = 'C';
            curcamname[8] = 'o';
            curcamname[9] = 'v';
            curcamname[10] = 'e';
            curcamname[11] = ' ';
            curcamname[12] = ' ';
            curcamname[13] = ' ';   
        } else {
            curcamname[0] = 'I';
            curcamname[1] = 'T';
            curcamname[2] = 'S';
            curcamname[3] = ' ';
            curcamname[4] = 'M';
            curcamname[5] = 'E';
            curcamname[6] = ' ';
            curcamname[7] = ' ';
            curcamname[8] = ' ';
            curcamname[9] = ' ';
            curcamname[10] = ' ';
            curcamname[11] = ' ';
            curcamname[12] = ' ';   
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
        curcamname[0] = 'S';
        curcamname[1] = 'u';
        curcamname[2] = 'p';
        curcamname[3] = 'p';
        curcamname[4] = 'l';
        curcamname[5] = 'y';
        curcamname[6] = ' ';
        curcamname[7] = 'C';
        curcamname[8] = 'l';
        curcamname[9] = 'o';
        curcamname[10] = 's';
        curcamname[11] = 'e';
        curcamname[12] = 't';
        curcamname[13] = ' ';
        curcamname[14] = ' ';
        curcamname[15] = ' ';
        curcamname[16] = ' ';
        curcamname[17] = ' ';
        curcamname[18] = ' ';
        curcamname[19] = ' ';
        curcamname[20] = ' ';
        curcamname[20] = ' ';
        curcamname[21] = ' ';
        curcamname[22] = ' ';
        curcamname[23] = ' ';
        curcamname[24] = ' ';
        curcamname[25] = ' ';
        curcamname[26] = ' ';
        curcamname[27] = ' ';
        curcamname[28] = ' ';
        curcamname[29] = ' ';
        curcamname[30] = ' ';
        curcamname[31] = ' ';
        curcamname[32] = ' ';
        curcamname[33] = ' ';
        curcamname[34] = ' ';
        curcamname[35] = ' ';
        curcamname[36] = ' ';
        curcamname[37] = ' ';
        curcamname[38] = ' ';
        curcamname[39] = ' ';
        curcamname[40] = ' ';
        curcamname[41] = ' ';
        curcamname[42] = ' ';
        curcamname[43] = ' ';
        curcamname[44] = ' ';
        curcamname[45] = ' ';
        curcamname[46] = ' ';
        curcamname[47] = ' ';
        curcamname[48] = ' ';
        curcamname[49] = ' ';
        curcamname[50] = ' ';
        curcamname[51] = ' '; // LE TRUC SONY QUI ME CASSE LES COUILLES LA PUTAIN
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
        curcamname[0] = 'W';
        curcamname[1] = 'e';
        curcamname[2] = 's';
        curcamname[3] = 't';
        curcamname[4] = ' ';
        curcamname[5] = 'H';
        curcamname[6] = 'a';
        curcamname[7] = 'l';
        curcamname[8] = 'l';
        curcamname[9] = ' ';
        curcamname[10] = ' ';
        curcamname[11] = ' ';
        curcamname[12] = ' ';
        curcamname[13] = ' ';
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
            curcamname[0] = 'W';
            curcamname[1] = '.';
            curcamname[2] = ' ';
            curcamname[3] = 'H';
            curcamname[4] = 'a';
            curcamname[5] = 'l';
            curcamname[6] = 'l';
            curcamname[7] = ' ';
            curcamname[8] = 'C';
            curcamname[9] = 'o';
            curcamname[10] = 'r';
            curcamname[11] = 'n';
            curcamname[12] = 'e';
            curcamname[13] = 'r'; 
        } else {
            curcamname[0] = 'I';
            curcamname[1] = 'T';
            curcamname[2] = 'S';
            curcamname[3] = ' ';
            curcamname[4] = 'M';
            curcamname[5] = 'E';
            curcamname[6] = ' ';
            curcamname[7] = ' ';
            curcamname[8] = ' ';
            curcamname[9] = ' ';
            curcamname[10] = ' ';
            curcamname[11] = ' ';
            curcamname[12] = ' ';   
            curcamname[13] = ' ';
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
        curcamname[0] = 'B';
        curcamname[1] = 'a';
        curcamname[2] = 'c';
        curcamname[3] = 'k';
        curcamname[4] = ' ';
        curcamname[5] = 'S';
        curcamname[6] = 't';
        curcamname[7] = 'a';
        curcamname[8] = 'g';
        curcamname[9] = 'e';
        curcamname[10] = ' ';
        curcamname[11] = ' ';
        curcamname[12] = ' ';
        curcamname[13] = ' ';
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
            curcamname[0] = 'E';
            curcamname[1] = 'a';
            curcamname[2] = 's';
            curcamname[3] = 't';
            curcamname[4] = ' ';
            curcamname[5] = 'H';
            curcamname[6] = 'a';
            curcamname[7] = 'l';
            curcamname[8] = 'l';
            curcamname[9] = ' ';
            curcamname[10] = ' ';
            curcamname[11] = ' ';
            curcamname[12] = ' ';
            curcamname[13] = ' ';
            curcamname[14] = ' ';
            curcamname[15] = ' ';
            curcamname[16] = ' ';
            curcamname[17] = ' ';
        } else {
            curcamname[0] = 'I';
            curcamname[1] = 'T';
            curcamname[2] = 'S';
            curcamname[3] = ' ';
            curcamname[4] = 'M';
            curcamname[5] = 'E';
            curcamname[6] = ' ';
            curcamname[7] = ' ';
            curcamname[8] = ' ';
            curcamname[9] = ' ';
            curcamname[10] = ' ';
            curcamname[11] = ' ';
            curcamname[12] = ' ';   
            curcamname[13] = ' ';
            curcamname[14] = ' ';
            curcamname[15] = ' ';
            curcamname[16] = ' ';
            curcamname[17] = ' ';
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
        curcamname[0] = 'E';
        curcamname[1] = '.';
        curcamname[2] = ' ';
        curcamname[3] = 'H';
        curcamname[4] = 'a';
        curcamname[5] = 'l';
        curcamname[6] = 'l';
        curcamname[7] = ' ';
        curcamname[8] = 'C';
        curcamname[9] = 'o';
        curcamname[10] = 'r';
        curcamname[11] = 'n';
        curcamname[12] = 'e';
        curcamname[13] = 'r';
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
        curcamname[0] = 'K';
        curcamname[1] = 'i';
        curcamname[2] = 't';
        curcamname[3] = 'c';
        curcamname[4] = 'h';
        curcamname[5] = 'e';
        curcamname[6] = 'n';
        curcamname[7] = ' ';
        curcamname[8] = '(';
        curcamname[9] = 'N';
        curcamname[10] = 'o';
        curcamname[11] = 'v';
        curcamname[12] = 'i';
        curcamname[13] = 'd';
        curcamname[14] = 'e';
        curcamname[15] = 'o';
        curcamname[16] = ')';
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
        curcamname[0] = 'R';
        curcamname[1] = 'e';
        curcamname[2] = 's';
        curcamname[3] = 't';
        curcamname[4] = 'r';
        curcamname[5] = 'o';
        curcamname[6] = 'o';
        curcamname[7] = 'm';
        curcamname[8] = 's';
        curcamname[9] = ' ';
        curcamname[10] = ' ';
        curcamname[11] = ' ';
        curcamname[12] = ' ';
        curcamname[13] = ' ';
        curcamname[14] = ' ';
        curcamname[15] = ' ';
        curcamname[16] = ' ';
        curcamname[17] = ' ';
        curcamname[13] = ' ';
        curcamname[14] = ' ';
        curcamname[15] = ' ';
        curcamname[16] = ' ';
        curcamname[17] = ' ';
        curcamname[18] = ' ';
        curcamname[19] = ' ';
        curcamname[20] = ' ';
        curcamname[21] = ' ';
        curcamname[22] = ' ';
        curcamname[23] = ' ';
        curcamname[24] = ' ';
        curcamname[25] = ' ';
        curcamname[26] = ' ';
        curcamname[27] = ' ';
        curcamname[28] = ' ';
        curcamname[29] = ' ';
        curcamname[30] = ' ';
        curcamname[31] = ' ';
        curcamname[32] = ' ';
        curcamname[33] = ' ';
        curcamname[34] = ' ';
        curcamname[35] = ' ';
        curcamname[36] = ' ';
        curcamname[37] = ' ';
        curcamname[38] = ' ';
        curcamname[39] = ' ';
        curcamname[40] = ' ';
        curcamname[41] = ' ';
        curcamname[42] = ' ';
        curcamname[43] = ' ';
        curcamname[44] = ' ';
        curcamname[45] = ' ';
        curcamname[46] = ' ';
        curcamname[47] = ' ';
        curcamname[48] = ' ';
        curcamname[49] = ' ';
        curcamname[50] = ' ';
        curcamname[51] = ' ';
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