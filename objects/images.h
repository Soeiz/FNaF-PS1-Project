#include "createTIMandVECTOR.h"

// This function makes it so that if global_alpha is NOT 128, it will set every other alpha vars to its value.
// If 128, will let them be
void imageAlphaControl(void) {
    if (global_alpha != 128) {
        menu_alpha = global_alpha;

        office_alpha = global_alpha;

        //InAndOut_alpha will not be instant

        if (InAndOut_alpha < global_alpha) {InAndOut_alpha += 2;}

        if (InAndOut_alpha > global_alpha) {InAndOut_alpha -= 2;}
    }
}

void ChangeFontColor(int R, int G, int B) {
    RECT rectTL;

    setRECT(&rectTL, 961, 128, 1, 1);  
    ClearImage2(&rectTL, R, G, B);
    DrawSync(0);
}

void LoadTexture(u_long * tim, TIM_IMAGE * tparam){     // This part is from Lameguy64's tutorial series : lameguy64.net/svn/pstutorials/chapter1/3-textures.html login/pw: annoyingmous
    OpenTIM(tim);                                   // Open the tim binary data, feed it the address of the data in memory
    ReadTIM(tparam);                                // This read the header of the TIM data and sets the corresponding members of the TIM_IMAGE structure
    
    LoadImage(tparam->prect, tparam->paddr);        // Transfer the data from memory to VRAM at position prect.x, prect.y
    DrawSync(0);                                    // Wait for the drawing to end

    if (tparam->mode & 0x8){ // check 4th bit       // If 4th bit == 1, TIM has a CLUT
        LoadImage(tparam->crect, tparam->caddr);    // Load it to VRAM at position crect.x, crect.y
        DrawSync(0);                                // Wait for drawing to end
    }
}

//This function loads an image, linked with an object.
//Example : Freddy 
//Image: "FREDDY"
//Object: "freddy"
void LoadImageObject(char * image, TIM_IMAGE * object) {
    
    char loadFile[80];
    strcpy(loadFile, "\\");
    strcat(loadFile, image);
    strcat(loadFile, ".TIM;1");

    CdSearchFile(&filePos, loadFile);
    dataBuffer = malloc( BtoS(filePos.size) * CD_SECTOR_SIZE );
    CdControl(CdlSetloc, (u_char *)&filePos.pos, CtrlResult);
    // Read data and load it to dataBuffer
    CDreadOK = CdRead( (int)BtoS(filePos.size), (u_long *)dataBuffer, CdlModeSpeed );
    CDreadResult = CdReadSync(0, 0);
    LoadTexture(dataBuffer, object); 
    free(dataBuffer);
}

void loadTextureNightAnnouncement(void) {
    LoadTexture(_binary_tim_menus_night_NIGHT_tim_start,&nightannouncement);

    LoadTexture(_binary_tim_load_tim_start, &load);

    if (inCustomNight || hellNight) {LoadTexture(_binary_tim_menus_night_7TH_tim_start,&nightnumber); return;}

    if (isOnNight6) {LoadTexture(_binary_tim_menus_night_6TH_tim_start,&nightnumber); return;}

    switch(night) {
        case 1:
            LoadTexture(_binary_tim_menus_night_1ST_tim_start,&nightnumber);
        break;
        case 2:
            LoadTexture(_binary_tim_menus_night_2ND_tim_start,&nightnumber);
        break;
        case 3:
            LoadTexture(_binary_tim_menus_night_3RD_tim_start,&nightnumber);
        break;
        case 4:
            LoadTexture(_binary_tim_menus_night_4TH_tim_start,&nightnumber);
        break;
        case 5:
            LoadTexture(_binary_tim_menus_night_5TH_tim_start,&nightnumber);
        break;
        default:
            LoadTexture(_binary_tim_menus_night_1ST_tim_start,&nightnumber);
        break;
    }
}

void lineFlicker(void) {
    linesframes++;
    if (linesframes == 4) {
        LoadTexture(_binary_tim_menus_lines_1_tim_start, &lines);
        setUV4(polylines, 0, 0, 0, 142, 128, 0, 128, 142);
    }
    if (linesframes == 8) {
        LoadTexture(_binary_tim_menus_lines_2_tim_start, &lines);
    }
    if (linesframes == 12) {
        LoadTexture(_binary_tim_menus_lines_3_tim_start, &lines);
    }
    if (linesframes == 16) {
        LoadTexture(_binary_tim_menus_lines_4_tim_start, &lines);
    }
    if (linesframes == 20) {
        LoadTexture(_binary_tim_menus_lines_5_tim_start, &lines);
    }
    if (linesframes >= 24) {
        linesactive = false;
        linesframes = 0;
        setUV4(polylines, 0, 0, 0, 0, 0, 0, 0, 0);
    }
}

void doorsMove(void) {

    if (doorClosedL && MovVectorleftdoor.vy < -61) {

        leftdoorhello++;
        MovVectorleftdoor.vy += leftdoorhello;

    } else {leftdoorhello = 1;}

    if (!doorClosedL && MovVectorleftdoor.vy > -190) {

        leftdoorgoodbye--;
        MovVectorleftdoor.vy += leftdoorgoodbye;

    } else {leftdoorgoodbye = -1;}

    if (doorClosedR && MovVectorrightdoor.vy < -61) {

        rightdoorhello++;
        MovVectorrightdoor.vy += rightdoorhello;

    } else {rightdoorhello = 1;}

    if (!doorClosedR && MovVectorrightdoor.vy > -190) {

        rightdoorgoodbye--;
        MovVectorrightdoor.vy += rightdoorgoodbye;

    } else {rightdoorgoodbye = -1;}
}

void lightFlicker(void) {

    Ran(100);

    if (lightR) {

        if (RAN <= 20) {
            LoadTexture(_binary_tim_office_officeRIGHT_tim_start, &officeRIGHT);

            SpuSetKey(SPU_OFF, SPU_01CH);

            clearVRAM(4);
        } else {

            if (SpuGetKeyStatus(SPU_01CH) == SPU_OFF) {SpuSetKey(SPU_ON, SPU_01CH);}

            LoadTexture(_binary_tim_office_officeRIGHTlight_tim_start, &officeRIGHTlight);


            LoadTexture(_binary_tim_office_littlechica_tim_start, &officeRIGHTlightchica);
        }

    }

    if (lightL) {

        if (RAN <= 20) {
            LoadTexture(_binary_tim_office_officeLEFT_tim_start, &officeLEFT);

            SpuSetKey(SPU_OFF, SPU_01CH);
        } else {

            if (SpuGetKeyStatus(SPU_01CH) == SPU_OFF) {SpuSetKey(SPU_ON, SPU_01CH);}

            if (!(BonnieIsAtDoor)) {LoadTexture(_binary_tim_office_officeLEFTlight_tim_start, &officeLEFTlight);} else {LoadTexture(_binary_tim_office_officeLEFTlightbonnie_tim_start, &officeLEFTlight);}
        }
    }
}

void displayHUD(void) {

    //AM text 
        polyAMoffice = (POLY_FT4 *)nextpri;                 
                
        RotMatrix(&RotVectorAMoffice, &PolyMatrixAMoffice); 
        TransMatrix(&PolyMatrixAMoffice, &MovVectorAMoffice);  
        ScaleMatrix(&PolyMatrixAMoffice, &ScaleVectorAMoffice);
        
        SetRotMatrix(&PolyMatrixAMoffice);              
        SetTransMatrix(&PolyMatrixAMoffice);       

        setClut(polyAMoffice, 0, 484); 

        setPolyFT4(polyAMoffice);                         

        setRGB0(polyAMoffice,255,255,255);
        
        polyAMoffice->tpage = getTPage(AMoffice.mode&0x3, 0, 832, 256);
        
        RotTransPers4(
                    &VertPosAMoffice[0],      &VertPosAMoffice[1],      &VertPosAMoffice[2],      &VertPosAMoffice[3],
                    (long*)&polyAMoffice->x0, (long*)&polyAMoffice->x1, (long*)&polyAMoffice->x2, (long*)&polyAMoffice->x3,
                    &polydepth,
                    &polyflag
                    );                               
        
        setUV4(polyAMoffice, 0, 202, 0, 228, 92, 202, 92, 228); 

        addPrim(ot[db], polyAMoffice);                     
        
        nextpri += sizeof(POLY_FT4);      

    //Night text 
        polyNightoffice = (POLY_FT4 *)nextpri;                 
                
        RotMatrix(&RotVectorNightoffice, &PolyMatrixNightoffice); 
        TransMatrix(&PolyMatrixNightoffice, &MovVectorNightoffice);  
        ScaleMatrix(&PolyMatrixNightoffice, &ScaleVectorNightoffice);
        
        SetRotMatrix(&PolyMatrixNightoffice);              
        SetTransMatrix(&PolyMatrixNightoffice);     

        setClut(polyNightoffice, 0, 485); 

        setPolyFT4(polyNightoffice);                         

        setRGB0(polyNightoffice,255,255,255);
        
        polyNightoffice->tpage = getTPage(AMoffice.mode&0x3, 0, 832, 256);
        
        RotTransPers4(
                    &VertPosNightoffice[0],      &VertPosNightoffice[1],      &VertPosNightoffice[2],      &VertPosNightoffice[3],
                    (long*)&polyNightoffice->x0, (long*)&polyNightoffice->x1, (long*)&polyNightoffice->x2, (long*)&polyNightoffice->x3,
                    &polydepth,
                    &polyflag
                    );                               
        
        setUV4(polyNightoffice, 0, 181, 0, 202, 64, 181, 64, 202); 

        addPrim(ot[db], polyNightoffice);                     
        
        nextpri += sizeof(POLY_FT4);      

    //Night Number text 
        polyNightNumberoffice = (POLY_FT4 *)nextpri;                 
                
        RotMatrix(&RotVectorNightNumberoffice, &PolyMatrixNightNumberoffice); 
        TransMatrix(&PolyMatrixNightNumberoffice, &MovVectorNightNumberoffice);  
        ScaleMatrix(&PolyMatrixNightNumberoffice, &ScaleVectorNightNumberoffice);
        
        SetRotMatrix(&PolyMatrixNightNumberoffice);              
        SetTransMatrix(&PolyMatrixNightNumberoffice);

        setClut(polyNightNumberoffice, 0, 486); 

        setPolyFT4(polyNightNumberoffice);                         

        setRGB0(polyNightNumberoffice,255,255,255);
        
        polyNightNumberoffice->tpage = getTPage(AMoffice.mode&0x3, 0, 832, 256);
        
        RotTransPers4(
                    &VertPosNightNumberoffice[0],      &VertPosNightNumberoffice[1],      &VertPosNightNumberoffice[2],      &VertPosNightNumberoffice[3],
                    (long*)&polyNightNumberoffice->x0, (long*)&polyNightNumberoffice->x1, (long*)&polyNightNumberoffice->x2, (long*)&polyNightNumberoffice->x3,
                    &polydepth,
                    &polyflag
                    );                               
        
        if (!inCustomNight) {
            if (isOnNight6) {
                setUV4(polyNightNumberoffice, 19*6 - 19, 158, 19*6 - 19, 181, 19*6, 158, 19*6, 181);
            } else {
                setUV4(polyNightNumberoffice, 19*night - 19, 158, 19*night - 19, 181, 19*night, 158, 19*night, 181);
            }
        } else {
            setUV4(polyNightNumberoffice, 19*7 - 19, 158, 19*7 - 19, 181, 19*7, 158, 19*7, 181);
        }

        addPrim(ot[db], polyNightNumberoffice);                     
        
        nextpri += sizeof(POLY_FT4);      


    //Power left text 
        polypowerleft = (POLY_FT4 *)nextpri;                 
                
        RotMatrix(&RotVectorpowerleft, &PolyMatrixpowerleft); 
        TransMatrix(&PolyMatrixpowerleft, &MovVectorpowerleft);  
        ScaleMatrix(&PolyMatrixpowerleft, &ScaleVectorpowerleft);
        
        SetRotMatrix(&PolyMatrixpowerleft);              
        SetTransMatrix(&PolyMatrixpowerleft);   

        setClut(polypowerleft, 0, 482); 

        setPolyFT4(polypowerleft);                         

        setRGB0(polypowerleft,255,255,255);
        
        polypowerleft->tpage = getTPage(powerleft.mode&0x3, 0, 832, 256);
        
        RotTransPers4(
                    &VertPospowerleft[0],      &VertPospowerleft[1],      &VertPospowerleft[2],      &VertPospowerleft[3],
                    (long*)&polypowerleft->x0, (long*)&polypowerleft->x1, (long*)&polypowerleft->x2, (long*)&polypowerleft->x3,
                    &polydepth,
                    &polyflag
                    );                               
        
        setUV4(polypowerleft, 0, 242, 0, 255, 140, 242, 140, 255); 

        addPrim(ot[db], polypowerleft);                     
        
        nextpri += sizeof(POLY_FT4);      

    //Usage text 
        polyusage = (POLY_FT4 *)nextpri;                 
                
        RotMatrix(&RotVectorusage, &PolyMatrixusage); 
        TransMatrix(&PolyMatrixusage, &MovVectorusage);  
        ScaleMatrix(&PolyMatrixusage, &ScaleVectorusage);
        
        SetRotMatrix(&PolyMatrixusage);              
        SetTransMatrix(&PolyMatrixusage);

        setClut(polyusage, 0, 481); 

        setPolyFT4(polyusage);                         
        
        setRGB0(polyusage,255,255,255);

        polyusage->tpage = getTPage(usage.mode&0x3, 0, 832, 256);
        
        RotTransPers4(
                    &VertPosusage[0],      &VertPosusage[1],      &VertPosusage[2],      &VertPosusage[3],
                    (long*)&polyusage->x0, (long*)&polyusage->x1, (long*)&polyusage->x2, (long*)&polyusage->x3,
                    &polydepth,
                    &polyflag
                    );                               
        
        setUV4(polyusage, 0, 228, 0, 242, 140, 228, 140, 242); 

        addPrim(ot[db], polyusage);                     
        
        nextpri += sizeof(POLY_FT4);      

    //Usage bars 
        polyusagebar = (POLY_FT4 *)nextpri;                 
                
        RotMatrix(&RotVectorusagebar, &PolyMatrixusagebar); 
        TransMatrix(&PolyMatrixusagebar, &MovVectorusagebar);  
        ScaleMatrix(&PolyMatrixusagebar, &ScaleVectorusagebar);
        
        SetRotMatrix(&PolyMatrixusagebar);              
        SetTransMatrix(&PolyMatrixusagebar);  

        setClut(polyusagebar, 0, 483); 

        setRGB0(polyusagebar,128,128,128);

        setPolyFT4(polyusagebar);                         
        
        polyusagebar->tpage = getTPage(usagebars.mode&0x3, 0, 832, 256);
        
        RotTransPers4(
                    &VertPosusagebar[0],      &VertPosusagebar[1],      &VertPosusagebar[2],      &VertPosusagebar[3],
                    (long*)&polyusagebar->x0, (long*)&polyusagebar->x1, (long*)&polyusagebar->x2, (long*)&polyusagebar->x3,
                    &polydepth,
                    &polyflag
                    );                               
        
        //UV4 gets changed in 'otherFunctions.h'

        addPrim(ot[db], polyusagebar);                     
        
        nextpri += sizeof(POLY_FT4);      

}

//Display the green thing's location and the isOnCamera title. (the controls of the camera are on another function)
void CameraSelectionDisplay(void) {

    //Gosh, This is gonna be long
    if (curCam[0] == '1') {

        if (curCam[1] == 'A') {
            MovVectorpolycamgreyogreen.vx = -35;
            MovVectorpolycamgreyogreen.vy = -103;  
            sprintf(curCamName, "Show Room");
        }

    }
    if (curCam[0] == '1' && curCam[1] == 'B') {
        MovVectorpolycamgreyogreen.vx = -40;
        MovVectorpolycamgreyogreen.vy = -83;  

        sprintf(curCamName, "Dining Area");

    }
    if (curCam[0] == '1' && curCam[1] == 'C') {
        MovVectorpolycamgreyogreen.vx = -65;
        MovVectorpolycamgreyogreen.vy = -35;  

        sprintf(curCamName, "Pirate Cove");

        if (FoxyLocation == 3 && ITSME_PirateCove) {

            sprintf(curCamName, "ITS ME");

        }
    }
    if (curCam[0] == '3' && curCam[1] == ' ') {   
        MovVectorpolycamgreyogreen.vx = -70;
        MovVectorpolycamgreyogreen.vy = 20;  

        sprintf(curCamName, "Supply Closet");

    }
    if (curCam[0] == '2' && curCam[1] == 'A') {      
        MovVectorpolycamgreyogreen.vx = -35;
        MovVectorpolycamgreyogreen.vy = 52;   

        sprintf(curCamName, "West Hall");

    }
    if (curCam[0] == '2' && curCam[1] == 'B') { 
        MovVectorpolycamgreyogreen.vx = -35;
        MovVectorpolycamgreyogreen.vy = 67;      

        sprintf(curCamName, "W. Hall Corner");

        if (BonnieLocation != 6 && ITSME_WestHallCorner) {

            sprintf(curCamName, "ITS ME");
        }

        if (goldenFreddyPoster) {
            goldenFreddyActivated = true;
        }

    }
    if (curCam[0] == '5' && curCam[1] == ' ') {  
        MovVectorpolycamgreyogreen.vx = -89;
        MovVectorpolycamgreyogreen.vy = -54;    

        sprintf(curCamName, "Back Stage");

    }
    if (curCam[0] == '4' && curCam[1] == 'A') {    
        MovVectorpolycamgreyogreen.vx = 37;
        MovVectorpolycamgreyogreen.vy = 52;   

        sprintf(curCamName, "East Hall");

        if (FreddyLocation != 4 && ChicaLocation != 5 && ChicaLocation != 6 && ITSME_EastHall) {

            sprintf(curCamName, "ITS ME");
        }
        /*
        if (isOnCamera == 1) {
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
        */

    }
    if (curCam[0] == '4' && curCam[1] == 'B') {       
        MovVectorpolycamgreyogreen.vx = 37;
        MovVectorpolycamgreyogreen.vy = 67;  

        sprintf(curCamName, "E. Hall Corner");

    }
    if (curCam[0] == '6' && curCam[1] == ' ') {
        MovVectorpolycamgreyogreen.vx = 50520;
        MovVectorpolycamgreyogreen.vy = -5028;  

        sprintf(curCamName, "Kitchen");

    }
    if (curCam[0] == '7' && curCam[1] == ' ') {
        MovVectorpolycamgreyogreen.vx = 100;
        MovVectorpolycamgreyogreen.vy = -60;  

        sprintf(curCamName, "Restrooms");

    }
}

//This function take in charge a specific polygon OR a set of polygon with related elements, depending on the var "num". 
//(1 is for freddy on the menu for example)
void makepoly(int num) {
    switch(num) {
        //Title warning
        case 0:
            
            polywarning = (POLY_FT4 *)nextpri;                 
                    
            RotMatrix(&RotVectorwarning, &PolyMatrixwarning);    
            TransMatrix(&PolyMatrixwarning, &MovVectorwarning);  
            ScaleMatrix(&PolyMatrixwarning, &ScaleVectorwarning);
            
            SetRotMatrix(&PolyMatrixwarning);                  
            SetTransMatrix(&PolyMatrixwarning);                
            
            setClut(polywarning, 960, 68);
        
            setRGB0(polywarning, InAndOut_alpha, InAndOut_alpha, InAndOut_alpha); 

            setPolyFT4(polywarning);                           
            
            polywarning->tpage = getTPage(warning.mode&0x3, 0, 896, 0); 
            
            
            RotTransPers4(
                        &VertPoswarning[0],      &VertPoswarning[1],      &VertPoswarning[2],      &VertPoswarning[3],
                        (long*)&polywarning->x0, (long*)&polywarning->x1, (long*)&polywarning->x2, (long*)&polywarning->x3,
                        &polydepth,
                        &polyflag
                        );                               
            
            setUV4(polywarning, 0, 0, 0, 55, 240, 0, 240, 55);
                
            addPrim(ot[db], polywarning);                       
            
            nextpri += sizeof(POLY_FT4); 

        break;
        //Title menu (freddy)
        case 1:

            if (currentMenu[0] == 0) {
                if (bestNight > 4) {

                    polystar = (POLY_FT4 *)nextpri;          

                    RotMatrix(&RotVectorstar, &PolyMatrixstar);    
                    TransMatrix(&PolyMatrixstar, &MovVectorstar);  
                    ScaleMatrix(&PolyMatrixstar, &ScaleVectorstar);
                    
                    SetRotMatrix(&PolyMatrixstar);                 
                    SetTransMatrix(&PolyMatrixstar);   
                    setClut(polystar, 0, 488);
                    
                    setPolyFT4(polystar);                          
                    
                    polystar->tpage = getTPage(star.mode&0x3, 0, 384, 256); 
                    
                    RotTransPers4(
                                &VertPosstar[0],      &VertPosstar[1],      &VertPosstar[2],      &VertPosstar[3],
                                (long*)&polystar->x0, (long*)&polystar->x1, (long*)&polystar->x2, (long*)&polystar->x3,
                                &polydepth,
                                &polyflag
                                );                                
                    
                    setRGB0(polystar, 128, 128, 128);

                    setUV4(polystar, 196, 0, 196, 56, 255, 0, 255, 56);
                        
                    addPrim(ot[db], polystar);                       
                    nextpri += sizeof(POLY_FT4);      

                }
                if (Night6State == 2) {

                    polystar = (POLY_FT4 *)nextpri;          

                    RotMatrix(&RotVectorstar, &PolyMatrixstar);    
                    TransMatrix(&PolyMatrixstar, &MovVectorstar2);  
                    ScaleMatrix(&PolyMatrixstar, &ScaleVectorstar);
                    
                    SetRotMatrix(&PolyMatrixstar);                 
                    SetTransMatrix(&PolyMatrixstar);   
                    setClut(polystar, 0, 488);
                    
                    setPolyFT4(polystar);                          
                    
                    polystar->tpage = getTPage(star.mode&0x3, 0, 384, 256); 
                    
                    RotTransPers4(
                                &VertPosstar[0],      &VertPosstar[1],      &VertPosstar[2],      &VertPosstar[3],
                                (long*)&polystar->x0, (long*)&polystar->x1, (long*)&polystar->x2, (long*)&polystar->x3,
                                &polydepth,
                                &polyflag
                                );                                
                    
                    setRGB0(polystar, 128, 128, 128);

                    setUV4(polystar, 196, 0, 196, 56, 255, 0, 255, 56);
                        
                    addPrim(ot[db], polystar);                       
                    nextpri += sizeof(POLY_FT4);      

                }
                if (fourTwentyDone) {

                    polystar = (POLY_FT4 *)nextpri;          

                    RotMatrix(&RotVectorstar, &PolyMatrixstar);    
                    TransMatrix(&PolyMatrixstar, &MovVectorstar3);  
                    ScaleMatrix(&PolyMatrixstar, &ScaleVectorstar);
                    
                    SetRotMatrix(&PolyMatrixstar);                 
                    SetTransMatrix(&PolyMatrixstar);   
                    setClut(polystar, 0, 488);
                    
                    setPolyFT4(polystar);                          
                    
                    polystar->tpage = getTPage(star.mode&0x3, 0, 384, 256); 
                    
                    RotTransPers4(
                                &VertPosstar[0],      &VertPosstar[1],      &VertPosstar[2],      &VertPosstar[3],
                                (long*)&polystar->x0, (long*)&polystar->x1, (long*)&polystar->x2, (long*)&polystar->x3,
                                &polydepth,
                                &polyflag
                                );                                
                    
                    setRGB0(polystar, 128, 128, 128);

                    setUV4(polystar, 196, 0, 196, 56, 255, 0, 255, 56);
                        
                    addPrim(ot[db], polystar);                       
                    nextpri += sizeof(POLY_FT4);      

                }
                
            }

            polytitlestatic = (POLY_FT4 *)nextpri;             
                    
            RotMatrix(&RotVectortitlestatic, &PolyMatrixtitlestatic);    
            TransMatrix(&PolyMatrixtitlestatic, &MovVectortitlestatic);  
            ScaleMatrix(&PolyMatrixtitlestatic, &ScaleVectortitlestatic);
            
            SetRotMatrix(&PolyMatrixtitlestatic);                    
            SetTransMatrix(&PolyMatrixtitlestatic);                  
            
            setPolyFT4(polytitlestatic);                             
            setRGB0(polytitlestatic, 128,128,128);
            
            setClut(polytitlestatic, 256, 491);       

            polytitlestatic->tpage = getTPage(statictitle.mode&0x3, 0, 576, 256);
            
            RotTransPers4(
                        &VertPostitlestatic[0],      &VertPostitlestatic[1],      &VertPostitlestatic[2],      &VertPostitlestatic[3],
                        (long*)&polytitlestatic->x0, (long*)&polytitlestatic->x1, (long*)&polytitlestatic->x2, (long*)&polytitlestatic->x3,
                        &polydepth,
                        &polyflag
                        );                                
                
            addPrim(ot[db], polytitlestatic);                       
            nextpri += sizeof(POLY_FT4);     //SetUV4 is somewhere else

            if (linesactive) {
                
                lineFlicker();

                polylines = (POLY_FT4 *)nextpri;          
                
                RotMatrix(&RotVectorlines, &PolyMatrixlines);    
                TransMatrix(&PolyMatrixlines, &MovVectorlines);  
                ScaleMatrix(&PolyMatrixlines, &ScaleVectorlines);
                
                SetRotMatrix(&PolyMatrixlines);                  
                SetTransMatrix(&PolyMatrixlines);    
                
                setPolyFT4(polylines);                    
                setRGB0(polylines, 128, 128, 128);                       
                
                setClut(polylines, 256, 489);
                
                polylines->tpage = getTPage(lines.mode&0x3, 0, 320, 256);
                
                RotTransPers4(
                            &VertPoslines[0],      &VertPoslines[1],      &VertPoslines[2],      &VertPoslines[3],
                            (long*)&polylines->x0, (long*)&polylines->x1, (long*)&polylines->x2, (long*)&polylines->x3,
                            &polydepth,
                            &polyflag
                            );                              
                   
                addPrim(ot[db], polylines);                        
                
                nextpri += sizeof(POLY_FT4);   
            }

            if (timingFreddyLightFrame%3 == 0) {
                Ran(400);
                
                if (RAN > 393) {linesactive = true;}

                if (RAN > 290 && RAN < 340 && !linesactive) {
                    setUV4(polytitlestatic, 0, 0, 0, 126, 159, 0, 159, 126);
                } else {
                    setUV4(polytitlestatic, 0, 0, 0, 0, 0, 0, 0, 0);

                    if (MovVectortitlestatic.vx > 40) {
                        MovVectortitlestatic.vx = MovVectortitlestatic.vx = -40;
                    } else {
                        MovVectortitlestatic.vx = MovVectortitlestatic.vx + RAN / 4;
                    }
                }


                Ran(freddyFaceChangedChances);

            }


            if (newGameSelected == false) {

                if (menu_alpha == 0) { //Mainly when it boots 
                    timingFreddyLightFrame = 0;
                }

                if (timingFreddyLightFrame > 0) {
                    timingFreddyLightFrame--;
                    
                } else {
                    
                    timingFreddyLightFrame = 30 + Ran(120); // From 30 to 150 frames to try again

                    Ran(100);

                    menu_alpha = 28 + RAN ; //To make it 128 max
                }
            }

            if (returnedInGame) {return;}

            freddyFaceChangedChances = 75; //Will get changed if default

            switch(RAN) {
                case 1:
                    polyf->tpage = getTPage(freddy.mode&0x3, 0, 704, 256); 
                    setClut(polyf, 0, 505);
                break;
                case 2:
                    polyf->tpage = getTPage(freddy.mode&0x3, 0, 832, 256); 
                    setClut(polyf, 0, 505);
                break;
                case 3:
                    polyf->tpage = getTPage(freddy.mode&0x3, 0, 832, 0);
                    setClut(polyf, 0, 504);
                break;
                default:
                    polyf->tpage = getTPage(freddy.mode&0x3, 0, 704, 0); 
                    setClut(polyf, 0, 504);
                    freddyFaceChangedChances = 400;
                break;
            }
            

            polyf = (POLY_FT4 *)nextpri;          
                    
            RotMatrix(&RotVectorf, &PolyMatrixf);     
            TransMatrix(&PolyMatrixf, &MovVectorf);   
            ScaleMatrix(&PolyMatrixf, &ScaleVectorf); 
            
            SetRotMatrix(&PolyMatrixf);    
            SetTransMatrix(&PolyMatrixf);  
            
            setPolyFT4(polyf);  
            RotTransPers4(
                        &VertPosf[0],      &VertPosf[1],      &VertPosf[2],      &VertPosf[3],
                        (long*)&polyf->x0, (long*)&polyf->x1, (long*)&polyf->x2, (long*)&polyf->x3,
                        &polydepth,
                        &polyflag
                        );                                 
            
            setRGB0(polyf, menu_alpha, menu_alpha, menu_alpha);

            setUV4(polyf, 46, 0, 46, 255, 252, 0, 255, 252);
                
            addPrim(ot[db], polyf);                         
            nextpri += sizeof(POLY_FT4);           




        break;
        //Help Wanted
        case 2:   
            polyhelpwanted = (POLY_FT4 *)nextpri;          

            RotMatrix(&RotVectorhelpwanted, &PolyMatrixhelpwanted);    
            TransMatrix(&PolyMatrixhelpwanted, &MovVectorhelpwanted);  
            ScaleMatrix(&PolyMatrixhelpwanted, &ScaleVectorhelpwanted);
            
            SetRotMatrix(&PolyMatrixhelpwanted);                 
            SetTransMatrix(&PolyMatrixhelpwanted);   
            setClut(polyhelpwanted, 0, 495);
            
            setPolyFT4(polyhelpwanted);                          
            
            polyhelpwanted->tpage = getTPage(helpwanted.mode&0x3, 0, 512, 0); 
            
            RotTransPers4(
                        &VertPoshelpwanted[0],      &VertPoshelpwanted[1],      &VertPoshelpwanted[2],      &VertPoshelpwanted[3],
                        (long*)&polyhelpwanted->x0, (long*)&polyhelpwanted->x1, (long*)&polyhelpwanted->x2, (long*)&polyhelpwanted->x3,
                        &polydepth,
                        &polyflag
                        );                                
            
            setRGB0(polyhelpwanted, InAndOut_alpha, InAndOut_alpha, InAndOut_alpha);

            setUV4(polyhelpwanted, 0, 0, 0, 222, 255, 0, 255, 222);
                
            addPrim(ot[db], polyhelpwanted);                       
            nextpri += sizeof(POLY_FT4);      

        break;
        //Night Announcement (Number + Other)
        case 3:   
            polynightannouncement = (POLY_FT4 *)nextpri;          

            RotMatrix(&RotVectornightannouncement, &PolyMatrixnightannouncement);    
            TransMatrix(&PolyMatrixnightannouncement, &MovVectornightannouncement);  
            ScaleMatrix(&PolyMatrixnightannouncement, &ScaleVectornightannouncement);
            
            SetRotMatrix(&PolyMatrixnightannouncement);                 
            SetTransMatrix(&PolyMatrixnightannouncement);   
            setClut(polynightannouncement, 960, 148);     
            
            setPolyFT4(polynightannouncement);                          
            
            polynightannouncement->tpage = getTPage(nightannouncement.mode&0x3, 0, 960, 256); 
            
            RotTransPers4(
                        &VertPosnightannouncement[0],      &VertPosnightannouncement[1],      &VertPosnightannouncement[2],      &VertPosnightannouncement[3],
                        (long*)&polynightannouncement->x0, (long*)&polynightannouncement->x1, (long*)&polynightannouncement->x2, (long*)&polynightannouncement->x3,
                        &polydepth,
                        &polyflag
                        );                                
            
            setRGB0(polynightannouncement, InAndOut_alpha -10, InAndOut_alpha -10, InAndOut_alpha -10);

            setUV4(polynightannouncement, 0, 198, 0, 255, 132, 198, 132, 255);
                
            addPrim(ot[db], polynightannouncement);                       

            nextpri += sizeof(POLY_FT4);      

            polynightannouncementNUMBER = (POLY_FT4 *)nextpri;          

            RotMatrix(&RotVectornightannouncementNUMBER, &PolyMatrixnightannouncementNUMBER);    
            TransMatrix(&PolyMatrixnightannouncementNUMBER, &MovVectornightannouncementNUMBER);  
            ScaleMatrix(&PolyMatrixnightannouncementNUMBER, &ScaleVectornightannouncementNUMBER);
            
            SetRotMatrix(&PolyMatrixnightannouncementNUMBER);                 
            SetTransMatrix(&PolyMatrixnightannouncementNUMBER);   
            setClut(polynightannouncementNUMBER, 960, 149);     
            
            setPolyFT4(polynightannouncementNUMBER);                          
            
            polynightannouncementNUMBER->tpage = getTPage(nightnumber.mode&0x3, 0, 960, 256); 
            
            RotTransPers4(
                        &VertPosnightannouncementNUMBER[0],      &VertPosnightannouncementNUMBER[1],      &VertPosnightannouncementNUMBER[2],      &VertPosnightannouncementNUMBER[3],
                        (long*)&polynightannouncementNUMBER->x0, (long*)&polynightannouncementNUMBER->x1, (long*)&polynightannouncementNUMBER->x2, (long*)&polynightannouncementNUMBER->x3,
                        &polydepth,
                        &polyflag
                        );                                
            
            setRGB0(polynightannouncementNUMBER, InAndOut_alpha -10, InAndOut_alpha -10, InAndOut_alpha -10);

            setUV4(polynightannouncementNUMBER, 211, 237, 211, 255, 255, 237, 255, 255);
                
            addPrim(ot[db], polynightannouncementNUMBER);             

            nextpri += sizeof(POLY_FT4);      

        break;
        //Loading Image
        case 4:   
            polyloadingicon = (POLY_FT4 *)nextpri;               
                    
            RotMatrix(&RotVectorloadingicon, &PolyMatrixloadingicon);    
            TransMatrix(&PolyMatrixloadingicon, &MovVectorloadingicon);  
            ScaleMatrix(&PolyMatrixloadingicon, &ScaleVectorloadingicon);
            
            SetRotMatrix(&PolyMatrixloadingicon);                 
            SetTransMatrix(&PolyMatrixloadingicon); 

            setPolyFT4(polyloadingicon);                          
            
            setRGB0(polyloadingicon, 128, 128, 128); 

            polyloadingicon->tpage = getTPage(load.mode&0x3, 0, 960, 0); 
            
            RotTransPers4(
                        &VertPosloadingicon[0],      &VertPosloadingicon[1],      &VertPosloadingicon[2],      &VertPosloadingicon[3],
                        (long*)&polyloadingicon->x0, (long*)&polyloadingicon->x1, (long*)&polyloadingicon->x2, (long*)&polyloadingicon->x3,
                        &polydepth,
                        &polyflag
                        );                                
            
            setUV4(polyloadingicon, 0, 216, 0, 255, 40, 216, 40, 255);
                
            addPrim(ot[db], polyloadingicon);                       
            nextpri += sizeof(POLY_FT4);         

        break;

        //Office
        case 5:


            if (goldenFreddyActivated) {
                polyofficegolden = (POLY_FT4 *)nextpri;                    
                
                RotMatrix(&RotVectorofficegolden, &PolyMatrixofficegolden);    
                TransMatrix(&PolyMatrixofficegolden, &MovVectorofficegolden);  
                ScaleMatrix(&PolyMatrixofficegolden, &ScaleVectorofficegolden);
                
                SetRotMatrix(&PolyMatrixofficegolden);                  
                SetTransMatrix(&PolyMatrixofficegolden);    
         
                setRGB0(polyofficegolden, 158, 158, 158);
                setPolyFT4(polyofficegolden);                           
                
                setClut(polyofficegolden, 0, 509);
         
                polyofficegolden->tpage = getTPage(officegoldenfreddy.mode&0x3, 0, 320, 256);
                
                RotTransPers4(
                            &VertPosofficegolden[0],      &VertPosofficegolden[1],      &VertPosofficegolden[2],      &VertPosofficegolden[3],
                            (long*)&polyofficegolden->x0, (long*)&polyofficegolden->x1, (long*)&polyofficegolden->x2, (long*)&polyofficegolden->x3,
                            &polydepth,
                            &polyflag
                            );                              

                setUV4(polyofficegolden, 0, 0, 0, 239, 218, 0, 218, 239);
                   
                addPrim(ot[db], polyofficegolden);                        
                
                nextpri += sizeof(POLY_FT4);               
            }

            if (kaboom) {
                polyofficegolden = (POLY_FT4 *)nextpri;                    
                
                RotMatrix(&RotVectorofficegolden, &PolyMatrixofficegolden);    
                TransMatrix(&PolyMatrixofficegolden, &MovVectorofficegolden2);  
                ScaleMatrix(&PolyMatrixofficegolden, &ScaleVectorofficegolden2);
                
                SetRotMatrix(&PolyMatrixofficegolden);                  
                SetTransMatrix(&PolyMatrixofficegolden);    
         
                setRGB0(polyofficegolden, 158, 158, 158);
                setPolyFT4(polyofficegolden);                           
                
                setClut(polyofficegolden, 0, 509);
         
                polyofficegolden->tpage = getTPage(officegoldenfreddy.mode&0x3, 0, 320, 256);
                
                RotTransPers4(
                            &VertPosofficegolden[0],      &VertPosofficegolden[1],      &VertPosofficegolden[2],      &VertPosofficegolden[3],
                            (long*)&polyofficegolden->x0, (long*)&polyofficegolden->x1, (long*)&polyofficegolden->x2, (long*)&polyofficegolden->x3,
                            &polydepth,
                            &polyflag
                            );                              

                setUV4(polyofficegolden, 0, 0, 0, 239, 218, 0, 218, 239);
                   
                addPrim(ot[db], polyofficegolden);                        
                
                nextpri += sizeof(POLY_FT4);               
            }

            if (MusicBoxInit && !BlackOutInit) {

                polyfreddylightsout = (POLY_FT4 *)nextpri;      
                        
                RotMatrix(&RotVectorfreddylightsout, &PolyMatrixfreddylightsout);    
                TransMatrix(&PolyMatrixfreddylightsout, &MovVectorfreddylightsout);  
                ScaleMatrix(&PolyMatrixfreddylightsout, &ScaleVectorfreddylightsout);
                
                SetRotMatrix(&PolyMatrixfreddylightsout);                   
                SetTransMatrix(&PolyMatrixfreddylightsout);                 
                
                setPolyFT4(polyfreddylightsout);                            
                
                setClut(polyfreddylightsout, 0, 504);

                polyfreddylightsout->tpage = getTPage(freddysneak.mode&0x3, 0, 832, 256);
                
                setRGB0(polyfreddylightsout, glowVar, glowVar, glowVar);                 
                
                RotTransPers4(
                            &VertPosfreddylightsout[0],      &VertPosfreddylightsout[1],      &VertPosfreddylightsout[2],      &VertPosfreddylightsout[3],
                            (long*)&polyfreddylightsout->x0, (long*)&polyfreddylightsout->x1, (long*)&polyfreddylightsout->x2, (long*)&polyfreddylightsout->x3,
                            &polydepth,
                            &polyflag
                            );                                 
                
                setUV4(polyfreddylightsout, 60, 31, 60, 87, 128, 31, 128, 87);
                    
                addPrim(ot[db], polyfreddylightsout);                  
                
                nextpri += sizeof(POLY_FT4);                
            }

            if (battery > 0 && !nightWon) {
                    //Fan

                    polyfan = (POLY_FT4 *)nextpri;                  
                            
                    RotMatrix(&RotVectorfan, &PolyMatrixfan);    
                    TransMatrix(&PolyMatrixfan, &MovVectorfan);  
                    ScaleMatrix(&PolyMatrixfan, &ScaleVectorfan);
                    
                    SetRotMatrix(&PolyMatrixfan);            
                    SetTransMatrix(&PolyMatrixfan);          
                    
                    setPolyFT4(polyfan);                         
                    
                    setClut(polyfan, 0, 500);    
                    polyfan->tpage = getTPage(fan.mode&0x3, 0, 640, 256);
                    
                    RotTransPers4(
                                &VertPosfan[0],      &VertPosfan[1],      &VertPosfan[2],      &VertPosfan[3],
                                (long*)&polyfan->x0, (long*)&polyfan->x1, (long*)&polyfan->x2, (long*)&polyfan->x3,
                                &polydepth,
                                &polyflag
                                );                                 
                    
                    setUV4(polyfan, 0, 126, 0, 196, 58, 126, 58, 196);
                        
                    addPrim(ot[db], polyfan);                     
                    
                    nextpri += sizeof(POLY_FT4);        
            }
            //Door left
                leftdoor = (POLY_FT4 *)nextpri;                  
                        
                RotMatrix(&RotVectorleftdoor, &PolyMatrixleftdoor);    
                TransMatrix(&PolyMatrixleftdoor, &MovVectorleftdoor);  
                ScaleMatrix(&PolyMatrixleftdoor, &ScaleVectorleftdoor);
                
                SetRotMatrix(&PolyMatrixleftdoor);            
                SetTransMatrix(&PolyMatrixleftdoor);          
                
                setPolyFT4(leftdoor);                         
                
                setClut(leftdoor, 960, 195);    
                leftdoor->tpage = getTPage(doors.mode&0x3, 0, 320, 0);
                

                setRGB0(leftdoor, 128, 128, 128);

                //if (doorclosedL == 1) {setRGB0(leftdoor, 76, 76, 76);} //For preventing things to blink fast asf
                
                RotTransPers4(
                            &VertPosleftdoor[0],      &VertPosleftdoor[1],      &VertPosleftdoor[2],      &VertPosleftdoor[3],
                            (long*)&leftdoor->x0, (long*)&leftdoor->x1, (long*)&leftdoor->x2, (long*)&leftdoor->x3,
                            &polydepth,
                            &polyflag
                            );                                 
                
                setUV4(leftdoor, 0, 0, 0, 255, 76, 0, 76, 255);
                    
                addPrim(ot[db], leftdoor);                     
                
                nextpri += sizeof(POLY_FT4);        

            //Door right
                rightdoor = (POLY_FT4 *)nextpri;               
                        
                RotMatrix(&RotVectorrightdoor, &PolyMatrixrightdoor);      
                TransMatrix(&PolyMatrixrightdoor, &MovVectorrightdoor);    
                ScaleMatrix(&PolyMatrixrightdoor, &ScaleVectorrightdoor);  
                
                SetRotMatrix(&PolyMatrixrightdoor);                 
                SetTransMatrix(&PolyMatrixrightdoor);               
                
                setPolyFT4(rightdoor);         

                setClut(rightdoor, 960, 195); 
                rightdoor->tpage = getTPage(doors.mode&0x3, 0, 320, 0);   
                
                //if (doorclosedR == 1) {setRGB0(rightdoor, 76, 76, 76);} //For preventing things to blink fast asf again
                
                RotTransPers4(
                            &VertPosrightdoor[0],      &VertPosrightdoor[1],      &VertPosrightdoor[2],      &VertPosrightdoor[3],
                            (long*)&rightdoor->x0, (long*)&rightdoor->x1, (long*)&rightdoor->x2, (long*)&rightdoor->x3,
                            &polydepth,
                            &polyflag
                            );                           
                
                setUV4(rightdoor, 79, 0, 79, 255, 147, 0, 147, 255); //+55X bcs of where the door is on VRAM
                    
                addPrim(ot[db], rightdoor);                         
                
                nextpri += sizeof(POLY_FT4);          

            //Middle office
                polyofficemiddle = (POLY_FT4 *)nextpri;                 
                        
                RotMatrix(&RotVectorofficeall, &PolyMatrixofficemiddle);    
                TransMatrix(&PolyMatrixofficemiddle, &MovVectorofficemiddle);  
                ScaleMatrix(&PolyMatrixofficemiddle, &ScaleVectorofficeall);
                
                SetRotMatrix(&PolyMatrixofficemiddle);                  
                SetTransMatrix(&PolyMatrixofficemiddle);                
             
                if (battery > 0) {
                        setClut(polyofficemiddle, 0, 508);
                        polyofficemiddle->tpage = getTPage(officeMIDDLE.mode&0x3, 0, 832, 0);
                } else {
                        setClut(polyofficemiddle, 0, 503);
                        polyofficemiddle->tpage = getTPage(officeMIDDLE.mode&0x3, 0, 704, 256);
                }

                setPolyFT4(polyofficemiddle);                           
                 
                RotTransPers4(
                            &VertPosofficemiddle[0],      &VertPosofficemiddle[1],      &VertPosofficemiddle[2],      &VertPosofficemiddle[3],
                            (long*)&polyofficemiddle->x0, (long*)&polyofficemiddle->x1, (long*)&polyofficemiddle->x2, (long*)&polyofficemiddle->x3,
                            &polydepth,
                            &polyflag
                            );                               
                
                setUV4(polyofficemiddle, 0, 0, 0, 255, 222, 0, 222, 255);
                    

                addPrim(ot[db], polyofficemiddle);                       
                
                nextpri += sizeof(POLY_FT4);       


            if (ChicaIsAtDoor && lightR) {

                //Chica at window 
                    polychicawindow = (POLY_FT4 *)nextpri;                   
                    
                    RotMatrix(&RotVectorchicawindow, &PolyMatrixchicawindow);
                    TransMatrix(&PolyMatrixchicawindow, &MovVectorchicawindow);  
                    ScaleMatrix(&PolyMatrixchicawindow, &ScaleVectorchicawindow);
                    
                    SetRotMatrix(&PolyMatrixchicawindow);                
                    SetTransMatrix(&PolyMatrixchicawindow);              
                     
                    setClut(polychicawindow, 0, 490); 

                    setPolyFT4(polychicawindow);                          
        
                    polychicawindow->tpage = getTPage(officeRIGHTlightchica.mode&0x3, 0, 320, 0);
                    
                    RotTransPers4(
                                &VertPoschicawindow[0],      &VertPoschicawindow[1],      &VertPoschicawindow[2],      &VertPoschicawindow[3],
                                (long*)&polychicawindow->x0, (long*)&polychicawindow->x1, (long*)&polychicawindow->x2, (long*)&polychicawindow->x3,
                                &polydepth,
                                &polyflag
                                );                                 
                    
                    setUV4(polychicawindow, 74, 0, 74, 134, 108, 0, 108, 134);
                        

                    addPrim(ot[db], polychicawindow);                       
                    
                    nextpri += sizeof(POLY_FT4);                

            }

            //Right office 
                polyofficeright = (POLY_FT4 *)nextpri;                   
                
                RotMatrix(&RotVectorofficeright, &PolyMatrixofficeright);
                TransMatrix(&PolyMatrixofficeright, &MovVectorofficeright);  
                ScaleMatrix(&PolyMatrixofficeright, &ScaleVectorofficeright);
                
                SetRotMatrix(&PolyMatrixofficemiddle);                
                SetTransMatrix(&PolyMatrixofficemiddle);              
                 
                setClut(polyofficeright, 0, 506); 

                setPolyFT4(polyofficeright);                          
                
                polyofficeright->tpage = getTPage(officeRIGHT.mode&0x3, 0, officeRIGHT.prect->x, officeRIGHT.prect->y);
                
                RotTransPers4(
                            &VertPosofficeright[0],      &VertPosofficeright[1],      &VertPosofficeright[2],      &VertPosofficeright[3],
                            (long*)&polyofficeright->x0, (long*)&polyofficeright->x1, (long*)&polyofficeright->x2, (long*)&polyofficeright->x3,
                            &polydepth,
                            &polyflag
                            );                                 
                
                setUV4(polyofficeright, 0, 0, 0, 252, 220, 0, 220, 252);
                    

                addPrim(ot[db], polyofficeright);                       
                
                nextpri += sizeof(POLY_FT4);                

            //Left office 
                polyofficeleft = (POLY_FT4 *)nextpri;                 
                        
                RotMatrix(&RotVectorofficeleft, &PolyMatrixofficeleft); 
                TransMatrix(&PolyMatrixofficeleft, &MovVectorofficeleft);  
                ScaleMatrix(&PolyMatrixofficeleft, &ScaleVectorofficeleft);
                
                SetRotMatrix(&PolyMatrixofficemiddle);              
                SetTransMatrix(&PolyMatrixofficemiddle);      

                setClut(polyofficeleft, 0, 507); 

                setPolyFT4(polyofficeleft);                         
                
                polyofficeleft->tpage = getTPage(officeLEFT.mode&0x3, 0, 704, 0);
                
                RotTransPers4(
                            &VertPosofficeleft[0],      &VertPosofficeleft[1],      &VertPosofficeleft[2],      &VertPosofficeleft[3],
                            (long*)&polyofficeleft->x0, (long*)&polyofficeleft->x1, (long*)&polyofficeleft->x2, (long*)&polyofficeleft->x3,
                            &polydepth,
                            &polyflag
                            );                               
                
                setUV4(polyofficeleft, 0, 0, 0, 255, 220, 0, 220, 255); 

                addPrim(ot[db], polyofficeleft);                     
                
                nextpri += sizeof(POLY_FT4);      

        break; //Office

        case 6:
            //isOnCamera's grey or green
            polycamgreyogreen = (POLY_F4 *)nextpri;     
                    
            RotMatrix(&RotVectorpolycamgreyogreen, &PolyMatrixpolycamgreyogreen);    
            TransMatrix(&PolyMatrixpolycamgreyogreen, &MovVectorpolycamgreyogreen);
            ScaleMatrix(&PolyMatrixpolycamgreyogreen, &ScaleVectorpolycamgreyogreen);  
            
            SetRotMatrix(&PolyMatrixpolycamgreyogreen);            
            SetTransMatrix(&PolyMatrixpolycamgreyogreen);          
            
            setPolyF4(polycamgreyogreen);                          
            
            RotTransPers4(
                        &VertPospolycamgreyogreen[0],      &VertPospolycamgreyogreen[1],      &VertPospolycamgreyogreen[2],      &VertPospolycamgreyogreen[3],
                        (long*)&polycamgreyogreen->x0, (long*)&polycamgreyogreen->x1, (long*)&polycamgreyogreen->x2, (long*)&polycamgreyogreen->x3,
                        &polydepth,
                        &polyflag
                        );                               

            addPrim(ot[db], polycamgreyogreen);        

            setRGB0(polycamgreyogreen, 157, 184, 3);    
            
            nextpri += sizeof(POLY_F4);                

            polylayout = (POLY_FT4 *)nextpri;              
                    
            RotMatrix(&RotVectorlayout, &PolyMatrixlayout);
            TransMatrix(&PolyMatrixlayout, &MovVectorlayout);  
            ScaleMatrix(&PolyMatrixlayout, &ScaleVectorlayout);
            
            SetRotMatrix(&PolyMatrixlayout);                   
            SetTransMatrix(&PolyMatrixlayout);                 
            
            setPolyFT4(polylayout);                     

            setClut(polylayout,960,196);       
            
            polylayout->tpage = getTPage(layout.mode&0x3, 0, 640, 0); 
            
            setRGB0(polylayout, 128, 128, 128);         
            
            RotTransPers4(
                        &VertPoslayout[0],      &VertPoslayout[1],      &VertPoslayout[2],      &VertPoslayout[3],
                        (long*)&polylayout->x0, (long*)&polylayout->x1, (long*)&polylayout->x2, (long*)&polylayout->x3,
                        &polydepth,
                        &polyflag
                        );                               
            
            setUV4(polylayout, 0, 0, 0, 229, 229, 0, 229, 229);  
                

            addPrim(ot[db], polylayout);                  
            
            nextpri += sizeof(POLY_FT4);             

            //icon for isOnCamera
            if (animatronicsPresenceOnCamera[0] == 2) {
                polyfreddy = (POLY_F4 *)nextpri;      

                setRGB0(polyfreddy, 36, 14, 3);
                        
                RotMatrix(&RotVectoreveryone, &PolyMatrixfreddy);
                TransMatrix(&PolyMatrixfreddy, &MovVectorfreddy);  
                ScaleMatrix(&PolyMatrixfreddy, &ScaleVectoreveryone);
                
                SetRotMatrix(&PolyMatrixfreddy);                   
                SetTransMatrix(&PolyMatrixfreddy);                 
                
                setPolyF4(polyfreddy);                             
                
                RotTransPers4(
                            &VertPoseveryone[0],      &VertPoseveryone[1],      &VertPoseveryone[2],      &VertPoseveryone[3],
                            (long*)&polyfreddy->x0, (long*)&polyfreddy->x1, (long*)&polyfreddy->x2, (long*)&polyfreddy->x3,
                            &polydepth,
                            &polyflag
                            );                                 
                addPrim(ot[db], polyfreddy);                   
                
                nextpri += sizeof(POLY_F4);                    
            }
            if (animatronicsPresenceOnCamera[1] == 2) {
                //BONNIE 
                polybonnie = (POLY_F4 *)nextpri;        

                setRGB0(polybonnie, 0, 21, 90); 

                RotMatrix(&RotVectoreveryone, &PolyMatrixbonnie);
                TransMatrix(&PolyMatrixbonnie, &MovVectorbonnie);  
                ScaleMatrix(&PolyMatrixbonnie, &ScaleVectoreveryone);
                
                SetRotMatrix(&PolyMatrixbonnie);                   
                SetTransMatrix(&PolyMatrixbonnie);                 
                
                setPolyF4(polybonnie);                             
                
                RotTransPers4(
                            &VertPoseveryone[0],      &VertPoseveryone[1],      &VertPoseveryone[2],      &VertPoseveryone[3],
                            (long*)&polybonnie->x0, (long*)&polybonnie->x1, (long*)&polybonnie->x2, (long*)&polybonnie->x3,
                            &polydepth,
                            &polyflag
                            );                                 
                
                addPrim(ot[db], polybonnie);                   
                
                nextpri += sizeof(POLY_F4);               
            }

            if (animatronicsPresenceOnCamera[2] == 2) {     
                //CHICA
                polychica = (POLY_F4 *)nextpri;    

                setRGB0(polychica, 128, 115, 41);
                        
                RotMatrix(&RotVectoreveryone, &PolyMatrixchica);  
                TransMatrix(&PolyMatrixchica, &MovVectorchica);
                ScaleMatrix(&PolyMatrixchica, &ScaleVectoreveryone);
                
                SetRotMatrix(&PolyMatrixchica);                  
                SetTransMatrix(&PolyMatrixchica);                
                
                setPolyF4(polychica);                            
                
                RotTransPers4(
                            &VertPoseveryone[0],      &VertPoseveryone[1],      &VertPoseveryone[2],      &VertPoseveryone[3],
                            (long*)&polychica->x0, (long*)&polychica->x1, (long*)&polychica->x2, (long*)&polychica->x3,
                            &polydepth,
                            &polyflag
                            );                                 
                
                addPrim(ot[db], polychica);                    
                
                nextpri += sizeof(POLY_F4);                    
            }

            if (animatronicsPresenceOnCamera[3] == 2) {
                //FOXY
                polyfoxy = (POLY_F4 *)nextpri;

                setRGB0(polyfoxy, 97, 20, 20);       

                RotMatrix(&RotVectoreveryone, &PolyMatrixfoxy);    
                TransMatrix(&PolyMatrixfoxy, &MovVectorfoxy);  
                ScaleMatrix(&PolyMatrixfoxy, &ScaleVectoreveryone);
                
                SetRotMatrix(&PolyMatrixfoxy);                 
                SetTransMatrix(&PolyMatrixfoxy);               
                
                setPolyF4(polyfoxy);                           
                
                OTz = RotTransPers4(
                            &VertPoseveryone[0],      &VertPoseveryone[1],      &VertPoseveryone[2],      &VertPoseveryone[3],
                            (long*)&polyfoxy->x0, (long*)&polyfoxy->x1, (long*)&polyfoxy->x2, (long*)&polyfoxy->x3,
                            &polydepth,
                            &polyflag
                            );                                 
                
                addPrim(ot[db], polyfoxy);                     
                
                nextpri += sizeof(POLY_F4);                    
            }

            if (goldenFreddyActivated) {
                //Golden freddy
                polygoldenf = (POLY_F4 *)nextpri;              
                        
                RotMatrix(&RotVectoreveryone, &PolyMatrixgoldenf);    
                TransMatrix(&PolyMatrixgoldenf, &MovVectorgoldenf);  
                ScaleMatrix(&PolyMatrixgoldenf, &ScaleVectoreveryone);
                
                SetRotMatrix(&PolyMatrixgoldenf);                    
                SetTransMatrix(&PolyMatrixgoldenf);                  
                
                setPolyF4(polygoldenf);                          
                setRGB0(polygoldenf,204,204,0);
                OTz = RotTransPers4(
                            &VertPoseveryone[0],      &VertPoseveryone[1],      &VertPoseveryone[2],      &VertPoseveryone[3],
                            (long*)&polygoldenf->x0, (long*)&polygoldenf->x1, (long*)&polygoldenf->x2, (long*)&polygoldenf->x3,
                            &polydepth,
                            &polyflag
                            );                                 
                
                addPrim(ot[db], polygoldenf);                  
                
                nextpri += sizeof(POLY_F4);                 
            }   

            if (animatronicsPresenceOnCamera[5] == 2) {
                //sparky
                polysparky = (POLY_F4 *)nextpri;               
                        
                RotMatrix(&RotVectoreveryone, &PolyMatrixsparky);
                TransMatrix(&PolyMatrixsparky, &MovVectorsparky);  
                ScaleMatrix(&PolyMatrixsparky, &ScaleVectoreveryone);
                
                SetRotMatrix(&PolyMatrixsparky);                   
                SetTransMatrix(&PolyMatrixsparky);                 
                
                setPolyF4(polysparky);                             
                setRGB0(polysparky,77,59,45);
                OTz = RotTransPers4(
                            &VertPoseveryone[0],      &VertPoseveryone[1],      &VertPoseveryone[2],      &VertPoseveryone[3],
                            (long*)&polysparky->x0, (long*)&polysparky->x1, (long*)&polysparky->x2, (long*)&polysparky->x3,
                            &polydepth,
                            &polyflag
                            );                                 
                
                addPrim(ot[db], polysparky);                   
                
                nextpri += sizeof(POLY_F4);                    
            }   
    
        break; //Camera

        case 7:
            polyjump = (POLY_FT4 *)nextpri;             
                    
            RotMatrix(&RotVectorjump, &PolyMatrixjump);    
            TransMatrix(&PolyMatrixjump, &MovVectorjump);  
            ScaleMatrix(&PolyMatrixjump, &ScaleVectorjump);
            
            SetRotMatrix(&PolyMatrixjump);                    
            SetTransMatrix(&PolyMatrixjump);                  
            
            setPolyFT4(polyjump);                             
            setRGB0(polyjump, office_alpha,office_alpha,office_alpha);
            
            setClut(polyjump, jumpscare.crect->x, jumpscare.crect->y);       

            polyjump->tpage = getTPage(jumpscare.mode&0x3, 0, 576, 256);
            
            RotTransPers4(
                        &VertPosjump[0],      &VertPosjump[1],      &VertPosjump[2],      &VertPosjump[3],
                        (long*)&polyjump->x0, (long*)&polyjump->x1, (long*)&polyjump->x2, (long*)&polyjump->x3,
                        &polydepth,
                        &polyflag
                        );                                
            
            setUV4(polyjump, 40, 0, 40, 125, 146, 0, 145, 126);
                
            addPrim(ot[db], polyjump);                       
            nextpri += sizeof(POLY_FT4);                 
        break; //Jumpscare !!!!!!

        case 8:
            polystatic = (POLY_FT4 *)nextpri;             
                    
            RotMatrix(&RotVectorstatic, &PolyMatrixstatic);    
            TransMatrix(&PolyMatrixstatic, &MovVectorstatic);  
            ScaleMatrix(&PolyMatrixstatic, &ScaleVectorstatic);
            
            SetRotMatrix(&PolyMatrixstatic);                    
            SetTransMatrix(&PolyMatrixstatic);                  
            
            setPolyFT4(polystatic);        

            setRGB0(polystatic, 128,128,128);
            
            setClut(polystatic, 960, 197);       

            polystatic->tpage = getTPage(statics.mode&0x3, 0, 576, 256);
            
            RotTransPers4(
                        &VertPosstatic[0],      &VertPosstatic[1],      &VertPosstatic[2],      &VertPosstatic[3],
                        (long*)&polystatic->x0, (long*)&polystatic->x1, (long*)&polystatic->x2, (long*)&polystatic->x3,
                        &polydepth,
                        &polyflag
                        );                                
            
            setUV4(polystatic, 0, 130, 53, 130, 0, 255, 53, 255);
                
            addPrim(ot[db], polystatic);                       
            nextpri += sizeof(POLY_FT4);          
        break; //Static thing when you die

        case 9:

            polygameover = (POLY_FT4 *)nextpri;               
                    
            RotMatrix(&RotVectorgameover, &PolyMatrixgameover);    
            TransMatrix(&PolyMatrixgameover, &MovVectorgameover);  
            ScaleMatrix(&PolyMatrixgameover, &ScaleVectorgameover);
            
            SetRotMatrix(&PolyMatrixgameover);                 
            SetTransMatrix(&PolyMatrixgameover); 

            setClut(polygameover, 0, 510);

            setPolyFT4(polygameover);                          
            
            setRGB0(polygameover, 128, 128, 128);              

            polygameover->tpage = getTPage(gameover.mode&0x3, 0, 448, 256); 
            
            RotTransPers4(
                        &VertPosgameover[0],      &VertPosgameover[1],      &VertPosgameover[2],      &VertPosgameover[3],
                        (long*)&polygameover->x0, (long*)&polygameover->x1, (long*)&polygameover->x2, (long*)&polygameover->x3,
                        &polydepth,
                        &polyflag
                        );                                
            
            setUV4(polygameover, 13, 0, 13, 222, 244, 0, 244, 222);
                
            addPrim(ot[db], polygameover);                       
            nextpri += sizeof(POLY_FT4);   
        break; //Gameover Image

        case 10:
            //five am OR six am tim (it's marked five am but sixam.tim go into the fiveam.tim emplacement)
            if (office_alpha < 1) {
                polyrect = (POLY_FT4 *)nextpri;     
                        
                RotMatrix(&RotVectorrect, &PolyMatrixrect);    
                TransMatrix(&PolyMatrixrect, &MovVectorrect);  
                ScaleMatrix(&PolyMatrixrect, &ScaleVectorrect);
                
                SetRotMatrix(&PolyMatrixrect);                   
                SetTransMatrix(&PolyMatrixrect);                 
                
                setPolyFT4(polyrect);                            
                
                setRGB0(polyrect, 0,0,0);
                
                setClut(polyrect, 960, 192);     

                polyrect->tpage = getTPage(rect.mode&0x3, 0, 832, 256); 
                
                RotTransPers4(
                            &VertPosrect[0],      &VertPosrect[1],      &VertPosrect[2],      &VertPosrect[3],
                            (long*)&polyrect->x0, (long*)&polyrect->x1, (long*)&polyrect->x2, (long*)&polyrect->x3,
                            &polydepth,
                            &polyflag
                            );                               
                
                setUV4(polyrect, 0, 111, 0, 158, 36, 111, 36, 158);
                    
                addPrim(ot[db], polyrect);                     
                nextpri += sizeof(POLY_FT4);     

                polyrect2 = (POLY_FT4 *)nextpri;     
                        
                RotMatrix(&RotVectorrect, &PolyMatrixrect2);    
                TransMatrix(&PolyMatrixrect2, &MovVectorrect2);  
                ScaleMatrix(&PolyMatrixrect2, &ScaleVectorrect);
                
                SetRotMatrix(&PolyMatrixrect2);                   
                SetTransMatrix(&PolyMatrixrect2);                 
                
                setPolyFT4(polyrect2);                            
                
                setRGB0(polyrect2, 0,0,0);
                
                setClut(polyrect2, 960, 192);      
                polyrect2->tpage = getTPage(rect.mode&0x3, 0, 768, 256); 
                
                RotTransPers4(
                            &VertPosrect[0],      &VertPosrect[1],      &VertPosrect[2],      &VertPosrect[3],
                            (long*)&polyrect2->x0, (long*)&polyrect2->x1, (long*)&polyrect2->x2, (long*)&polyrect2->x3,
                            &polydepth,
                            &polyflag
                            );                               
                
                setUV4(polyrect2, 0, 0, 0, 47, 36, 0, 36, 47);
                    
                addPrim(ot[db], polyrect2);                     
                nextpri += sizeof(POLY_FT4);      
            }
            //five am OR six am tim (it's marked five am but sixam.tim go into the fiveam.tim emplacement)
            polyfiveam = (POLY_FT4 *)nextpri;     
                    
            RotMatrix(&RotVectorfiveam, &PolyMatrixfiveam);    
            TransMatrix(&PolyMatrixfiveam, &MovVectorfiveam);  
            ScaleMatrix(&PolyMatrixfiveam, &ScaleVectorfiveam);
            
            SetRotMatrix(&PolyMatrixfiveam);                   
            SetTransMatrix(&PolyMatrixfiveam);                 
            
            setPolyFT4(polyfiveam);                            
            
            setRGB0(polyfiveam, 128,128,128);
            
            setClut(polyfiveam, 960, 193);      
            polyfiveam->tpage = getTPage(fiveam.mode&0x3, 0, 832, 256); 
            
            RotTransPers4(
                        &VertPosfiveam[0],      &VertPosfiveam[1],      &VertPosfiveam[2],      &VertPosfiveam[3],
                        (long*)&polyfiveam->x0, (long*)&polyfiveam->x1, (long*)&polyfiveam->x2, (long*)&polyfiveam->x3,
                        &polydepth,
                        &polyflag
                        );                               
            
            setUV4(polyfiveam, 0, 0, 0, 48, 40, 0, 40, 48);
                
            addPrim(ot[db], polyfiveam);                     
            nextpri += sizeof(POLY_FT4);     

            polyam = (POLY_FT4 *)nextpri;     
                    
            RotMatrix(&RotVectoram, &PolyMatrixam);    
            TransMatrix(&PolyMatrixam, &MovVectoram);  
            ScaleMatrix(&PolyMatrixam, &ScaleVectoram);
            
            SetRotMatrix(&PolyMatrixam);                   
            SetTransMatrix(&PolyMatrixam);                 
            
            setPolyFT4(polyam);                            
            
            setRGB0(polyam, 128,128,128);
            
            setClut(polyam, 960, 193);      
            polyam->tpage = getTPage(fiveam.mode&0x3, 0, 832, 256); 
            
            RotTransPers4(
                        &VertPosam[0],      &VertPosam[1],      &VertPosam[2],      &VertPosam[3],
                        (long*)&polyam->x0, (long*)&polyam->x1, (long*)&polyam->x2, (long*)&polyam->x3,
                        &polydepth,
                        &polyflag
                        );                               
            
            setUV4(polyam, 40, 0, 40, 48, 120, 0, 120, 48);
                
            addPrim(ot[db], polyam);                    
            nextpri += sizeof(POLY_FT4);    
        break; //5AM > 6AM

        case 11:

            //If music is normal
            if (!funky) {
                setRGB0(polygoodjob, global_alpha,global_alpha,global_alpha);
            }
            
            //If music is NOT Normal (funky)
            if (funky) {
                setRGB0(polygoodjob, rgbRed,rgbGreen,rgbBlue);


                if (nextNightFrame > 1220 && nextNightFrame < 6166) {

                    FntPrint("        credits : Harvey Rothman \n"); //Gonna give credits to this person ! ;)

                    switch(rgbIndicator) {
                        case 0:
                            rgbBlue++; 
                            if (rgbBlue == 135) {rgbIndicator = 1;} 
                        break;
                        case 1:
                            rgbRed--;
                            if (rgbRed == 79) {rgbIndicator = 2;} 
                        break;
                        case 2:
                            rgbGreen++;
                            if (rgbGreen == 135) {rgbIndicator = 3;}
                        break;
                        case 3:
                            rgbBlue--;
                            if (rgbBlue == 79) {rgbIndicator = 4;}
                        break;
                        case 4:
                            rgbRed++;
                            if (rgbRed == 135) {rgbIndicator = 5;}
                        break;
                        case 5:
                            rgbGreen--;
                            if (rgbGreen == 79) {rgbIndicator = 0;} 
                        break;
                    }

                    if (nextNightFrame == 5766) {
                        rgbRed = 128;
                        rgbGreen = 128;
                        rgbBlue = 128;
                    } //No more!

                }

            }

            polygoodjob = (POLY_FT4 *)nextpri;             
                    
            RotMatrix(&RotVectorgoodjob, &PolyMatrixgoodjob);    
            TransMatrix(&PolyMatrixgoodjob, &MovVectorgoodjob);  
            ScaleMatrix(&PolyMatrixgoodjob, &ScaleVectorgoodjob);
            
            SetRotMatrix(&PolyMatrixgoodjob);                    
            SetTransMatrix(&PolyMatrixgoodjob);                  
            
            setPolyFT4(polygoodjob);                             
            
            setClut(polygoodjob, 0, 511);       

            polygoodjob->tpage = getTPage(goodjob.mode&0x3, 0, 384, 0);
            
            RotTransPers4(
                        &VertPosgoodjob[0],      &VertPosgoodjob[1],      &VertPosgoodjob[2],      &VertPosgoodjob[3],
                        (long*)&polygoodjob->x0, (long*)&polygoodjob->x1, (long*)&polygoodjob->x2, (long*)&polygoodjob->x3,
                        &polydepth,
                        &polyflag
                        );                                
            
            setUV4(polygoodjob, 0, 0, 0, 231, 254, 0, 254, 231);
                
            addPrim(ot[db], polygoodjob);                       
            nextpri += sizeof(POLY_FT4);       
        break; //Good Job! Image
    }
}