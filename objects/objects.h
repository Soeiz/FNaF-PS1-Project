//TIM
extern unsigned long _binary_tim_officeMIDDLEnolight_tim_start[];
extern unsigned long _binary_tim_officeMIDDLEnolight_tim_end[];
extern unsigned long _binary_tim_officeMIDDLEnolight_tim_length;

extern unsigned long _binary_tim_officeRIGHT_tim_start[];
extern unsigned long _binary_tim_officeRIGHT_tim_end[];
extern unsigned long _binary_tim_officeRIGHT_tim_length;

extern unsigned long _binary_tim_officeRIGHTlight_tim_start[];
extern unsigned long _binary_tim_officeRIGHTlight_tim_end[];
extern unsigned long _binary_tim_officeRIGHTlight_tim_length;

extern unsigned long _binary_tim_officeRIGHTnolight_tim_start[];
extern unsigned long _binary_tim_officeRIGHTnolight_tim_end[];
extern unsigned long _binary_tim_officeRIGHTnolight_tim_length;

extern unsigned long _binary_tim_officeRIGHTlightchica_tim_start[];
extern unsigned long _binary_tim_officeRIGHTlightchica_tim_end[];
extern unsigned long _binary_tim_officeRIGHTlightchica_tim_length;

extern unsigned long _binary_tim_officeLEFT_tim_start[];
extern unsigned long _binary_tim_officeLEFT_tim_end[];
extern unsigned long _binary_tim_officeLEFT_tim_length;

extern unsigned long _binary_tim_officeLEFTlight_tim_start[];
extern unsigned long _binary_tim_officeLEFTlight_tim_end[];
extern unsigned long _binary_tim_officeLEFTlight_tim_length;

extern unsigned long _binary_tim_officeLEFTnolight_tim_start[];
extern unsigned long _binary_tim_officeLEFTnolight_tim_end[];
extern unsigned long _binary_tim_officeLEFTnolight_tim_length;

extern unsigned long _binary_tim_officeLEFTlightbonnie_tim_start[];
extern unsigned long _binary_tim_officeLEFTlightbonnie_tim_end[];
extern unsigned long _binary_tim_officeLEFTlightbonnie_tim_length;

extern unsigned long _binary_tim_CAMERAMONITOR_tim_start[];
extern unsigned long _binary_tim_CAMERAMONITOR_tim_end[];
extern unsigned long _binary_tim_CAMERAMONITOR_tim_length;

extern unsigned long _binary_tim_gameover_tim_start[];
extern unsigned long _binary_tim_gameover_tim_end[];
extern unsigned long _binary_tim_gameover_tim_length;

extern unsigned long _binary_tim_freddysneak_tim_start[];
extern unsigned long _binary_tim_freddysneak_tim_end[];
extern unsigned long _binary_tim_freddysneak_tim_length;

extern unsigned long _binary_tim_FAM_tim_start[];
extern unsigned long _binary_tim_FAM_tim_end[];
extern unsigned long _binary_tim_FAM_tim_length;

extern unsigned long _binary_tim_SAM_tim_start[];
extern unsigned long _binary_tim_SAM_tim_end[];
extern unsigned long _binary_tim_SAM_tim_length;

extern unsigned long _binary_tim_officeMIDDLE_tim_start[];
extern unsigned long _binary_tim_officeMIDDLE_tim_end[];
extern unsigned long _binary_tim_officeMIDDLE_tim_length;

extern unsigned long _binary_tim_doors_tim_start[];
extern unsigned long _binary_tim_doors_tim_end[];
extern unsigned long _binary_tim_doors_tim_length;

extern unsigned long _binary_tim_GJFIV_tim_start[];
extern unsigned long _binary_tim_GJFIV_tim_end[];
extern unsigned long _binary_tim_GJFIV_tim_length;

extern unsigned long _binary_tim_GJSEV_tim_start[];
extern unsigned long _binary_tim_GJSEV_tim_end[];
extern unsigned long _binary_tim_GJSEV_tim_length;

extern unsigned long _binary_tim_GJSIX_tim_start[];
extern unsigned long _binary_tim_GJSIX_tim_end[];
extern unsigned long _binary_tim_GJSIX_tim_length;

extern unsigned long _binary_tim_load_tim_start[];
extern unsigned long _binary_tim_load_tim_end[];
extern unsigned long _binary_tim_load_tim_length;
/*
extern unsigned long _binary_tim_fnt_tim_start[];
extern unsigned long _binary_tim_fnt_tim_end[];
extern unsigned long _binary_tim_fnt_tim_length;
*/
TIM_IMAGE freddy;
TIM_IMAGE freddy2;
TIM_IMAGE freddy3;
TIM_IMAGE freddy4;
TIM_IMAGE helpwanted;
TIM_IMAGE freddysneak;
TIM_IMAGE officeMIDDLE;
TIM_IMAGE officeMIDDLEnolight;
TIM_IMAGE officeRIGHT;
TIM_IMAGE officeRIGHTlight;
TIM_IMAGE officeRIGHTnolight;
TIM_IMAGE officeRIGHTlightchica;
TIM_IMAGE officeLEFT;
TIM_IMAGE officeLEFTlight;
TIM_IMAGE officeLEFTnolight;
TIM_IMAGE officeLEFTlightbonnie;
TIM_IMAGE doors;
TIM_IMAGE CAMERAMONITOR;
TIM_IMAGE layout;
TIM_IMAGE gameover;
TIM_IMAGE goodjob;
TIM_IMAGE fiveam;
TIM_IMAGE sixam;
TIM_IMAGE goldenfreddy;
TIM_IMAGE officegoldenfreddy;
TIM_IMAGE bonniestare;
TIM_IMAGE load;
//TIM_IMAGE fontface;

long polydepth;
long polyflag;
long OTz;

//freddy bg
POLY_FT4 *polyf = {0};                        

SVECTOR RotVectorf = {0, 0, 0};               
VECTOR  MovVectorf = {10, 2, CENTERX/2-10, 0};
VECTOR  ScaleVectorf = {ONE, ONE, ONE};       

SVECTOR VertPosf[4] = {                       
        {-45, -68, 1 },                       
        {-45,  68, 1 },                       
        { 67, -68, 1 },                       
        { 67,  68, 1  }                        
    };        

MATRIX PolyMatrixf = {0};  

//loading icon
POLY_FT4 *polyicon = {0};                        

SVECTOR RotVectoricon = {0, 0, 0};               
VECTOR  MovVectoricon = {40, 30, CENTERX/2-10, 0};
VECTOR  ScaleVectoricon = {ONE, ONE, ONE};       

SVECTOR VertPosicon[4] = {                       
        {0, 0, 1 },                       
        {0,  40, 1 },                       
        { 40, 0, 1 },                       
        { 40,  40, 1  }                        
    };        

MATRIX PolyMatrixicon = {0};  

//Freddy's Icon 
POLY_FT4 *polyficon = {0};                        

SVECTOR RotVectorficon = {0, 0, 0};               
VECTOR  MovVectorficon = {-70, -50, CENTERX/2-10, 0}; 
VECTOR  ScaleVectorficon = {2048, 2048, 2048}; 

SVECTOR VertPosficon[4] = {                    
        {-0, -0, 1 },                      
        {-0,  75, 1 },                         
        { 75, -0, 1 },                         
        { 75,  75, 1  }                        
    };        

MATRIX PolyMatrixficon = {0};    

//Bonnie's Icon 
POLY_FT4 *polybicon = {0};                           

SVECTOR RotVectorbicon = {0, 0, 0};                  
VECTOR  MovVectorbicon = {-40, -50, CENTERX/2-10, 0};
VECTOR  ScaleVectorbicon = {2048, 2048, 2048};       

SVECTOR VertPosbicon[4] = {                          
        {-0, -0, 1 },                         
        {-0,  75, 1 },                        
        { 75, -0, 1 },                        
        { 75,  75, 1  }                       
    };        

MATRIX PolyMatrixbicon = {0};    

//Chica's Icon 
POLY_FT4 *polycicon = {0};                           

SVECTOR RotVectorcicon = {0, 0, 0};                  
VECTOR  MovVectorcicon = {0, 0, CENTERX/2-10, 0};    
VECTOR  ScaleVectorcicon = {2048, 2048, 2048};       

SVECTOR VertPoscicon[4] = {                    
        {-60, -25, 1 },                        
        {-60,  26, 1 },                        
        { 61, -25, 1 },                        
        { 61,  26, 1  }                        
    };        

MATRIX PolyMatrixcicon = {0};    

//Foxy's Icon 
POLY_FT4 *polyfoicon = {0};                       

SVECTOR RotVectorfoicon = {0, 0, 0};              
VECTOR  MovVectorfoicon = {0, 0, CENTERX/2-10, 0};
VECTOR  ScaleVectorfoicon = {2048, 2048, 2048};   

SVECTOR VertPosfoicon[4] = {                      
        {-60, -25, 1 },                      
        {-60,  26, 1 },                      
        { 61, -25, 1 },                      
        { 61,  26, 1  }                      
    };        

MATRIX PolyMatrixfoicon = {0};    

//help wanted bg
POLY_FT4 *polyhelpwanted = {0};                           

SVECTOR RotVectorhelpwanted = {0, 0, 0};                  
VECTOR  MovVectorhelpwanted = {10, -6, CENTERX/2-10, 0};  
VECTOR  ScaleVectorhelpwanted = {ONE, ONE, ONE};          

SVECTOR VertPoshelpwanted[4] = {               
        {-90, -68, 1 },                        
        {-90,  68, 1 },                        
        { 90, -68, 1 },                        
        { 90,  68, 1  }                        
    };        

MATRIX PolyMatrixhelpwanted = {0};     

//TIM
POLY_FT4 *polyofficemiddle = {0};                         
POLY_FT4 *polyofficeright = {0};                          
POLY_FT4 *polyofficeleft = {0};                           
POLY_FT4 *poly4 = {0};                        
SVECTOR RotVectorofficemiddle = {0, 0, 0};                
VECTOR  MovVectorofficemiddle = {10, 2, CENTERX/2-10, 0}; 
VECTOR  ScaleVectorofficemiddle = {ONE, ONE, ONE};        

SVECTOR RotVectorofficeright = {0, 0, 0};                 
VECTOR  MovVectorofficeright = {10, 2, CENTERX/2-10, 0};  
VECTOR  ScaleVectorofficeright = {ONE, ONE, ONE};         

SVECTOR RotVectorofficeleft = {0, 0, 0};                  
VECTOR  MovVectorofficeleft = {10, 2, CENTERX/2-10, 0};   
VECTOR  ScaleVectorofficeleft = {ONE, ONE, ONE};          

SVECTOR RotVector4 = {0, 0, 0};                
VECTOR  MovVector4 = {10, 2, CENTERX/2-10, 0}; 
VECTOR  ScaleVector4 = {ONE, ONE, ONE};        

SVECTOR VertPosofficemiddle[4] = {             
        {-67, -68, 1 },                        
        {-67,  68, 1 },                        
        { 67, -68, 1 },                        
        { 67,  68, 1  }                        
    };                                         

SVECTOR VertPosofficeright[4] = {              
        {65, -68, 1 },                         
        {65,  68, 1 },                         
        { 215, -68, 1 },                       
        { 215,  68, 1  }                       
    };

SVECTOR VertPosofficeleft[4] = {               
        {-164, -68, 1 },                       
        {-164,  68, 1 },                       
        { -48, -68, 1 },                       
        { -48,  68, 1  }                       
    };                      

SVECTOR VertPos4[4] = {                        
        {-170, -68, 1 },                       
        {-170,  68, 1 },                       
        { -54,-68, 1 },                        
        { -54,  68, 1  }                       
    };                                   
               
MATRIX PolyMatrixofficemiddle = {0};                   
MATRIX PolyMatrixofficeright = {0};                   
MATRIX PolyMatrixofficeleft = {0};                   
MATRIX PolyMatrix4 = {0};                   
    
//Doors
//left
POLY_FT4 *leftdoor = {0};                          

SVECTOR RotVectorleftdoor = {0, 0, 0};             
VECTOR  MovVectorleftdoor = {-135, -60, CENTERX/2-10, 0};
VECTOR  ScaleVectorleftdoor = {ONE, ONE, ONE};


SVECTOR VertPosleftdoor[4] = {                
        {0, 0, 1 },                        
        {0,  118, 1 },                     
        { 42,0, 1 },                       
        { 41,  118, 1  }                   
    };                                        

MATRIX PolyMatrixleftdoor = {0};  

//right
POLY_FT4 *rightdoor = {0};                           

SVECTOR RotVectorrightdoor = {0, 0, 0};                  
VECTOR  MovVectorrightdoor = {144, -180, CENTERX/2-10, 0};
VECTOR  ScaleVectorrightdoor = {ONE, ONE, ONE};          


SVECTOR VertPosrightdoor[4] = {              
        {-0, -0, 1 },                        
        {-0,  122, 1 },                      
        { 44, -0, 1 },                       
        { 44,  122, 1  }                     
    };                                          

MATRIX PolyMatrixrightdoor = {0};                   

//Freddy during lightsout
POLY_FT4 *polyfreddylightsout = {0};                           

SVECTOR RotVectorfreddylightsout = {0, 0, 0};                  
VECTOR  MovVectorfreddylightsout = {-105, 0, CENTERX/2-10, 0}; 
VECTOR  ScaleVectorfreddylightsout = {1024, 1024, 1024};       

SVECTOR VertPosfreddylightsout[4] = {                          
        {-60, -60, 1 },                        
        {-60,  60, 1 },                        
        { 60,-60, 1 },                         
        { 60,  60, 1  }                        
    };                
MATRIX PolyMatrixfreddylightsout = {0};    

//icons of the animatronics
POLY_F4 *polyfreddy = {0};                        
POLY_F4 *polybonnie = {0};                        
POLY_F4 *polychica = {0};                         
POLY_F4 *polyfoxy = {0};                          
POLY_F4 *polygoldenf = {0};                           

SVECTOR RotVectorfreddy = {0, 0, 0};                  
VECTOR  MovVectorfreddy = {5, -37, CENTERX/2-10, 0};  
VECTOR  ScaleVectorfreddy = {1024, 1024, 1024};       

SVECTOR RotVectorbonnie = {0, 0, 0};                  
VECTOR  MovVectorbonnie = {-10, -44, CENTERX/2-10, 0};
VECTOR  ScaleVectorbonnie = {1024, 1024, 1024};       

SVECTOR RotVectorchica = {0, 0, 0};                 
VECTOR  MovVectorchica = {10, -44, CENTERX/2-10, 0};  
VECTOR  ScaleVectorchica = {1024, 1024, 1024};        

SVECTOR RotVectorfoxy = {0, 0, 0};                  
VECTOR  MovVectorfoxy = {-45, -6, CENTERX/2-10, 0};   
VECTOR  ScaleVectorfoxy = {1024, 1024, 1024};         

SVECTOR RotVectorgoldenf = {0, 0, 0};                 
VECTOR  MovVectorgoldenf = {999, 999, CENTERX/2-10, 0};
VECTOR  ScaleVectorgoldenf = {1024, 1024, 1024};      

SVECTOR VertPosfreddy[4] = {               
        {-10, -10, 1 },                    
        {-10,  10, 1 },                    
        {10, -10, 1 },                     
        {10,  10, 1  }                     
    };            
SVECTOR VertPosbonnie[4] = {               
        {-10, -10, 1 },                    
        {-10,  10, 1 },                    
        {10, -10, 1 },                     
        {10,  10, 1  }                     
    };            
SVECTOR VertPoschica[4] = {                
        {-10, -10, 1 },                    
        {-10,  10, 1 },                    
        {10, -10, 1 },                     
        {10,  10, 1  }                     
    };            
SVECTOR VertPosfoxy[4] = {                 
        {-10, -10, 1 },                    
        {-10,  10, 1 },                    
        {10, -10, 1 },                     
        {10,  10, 1  }                     
    };                
SVECTOR VertPosgoldenf[4] = {              
        {-10, -10, 1 },                    
        {-10,  10, 1 },                    
        {10, -10, 1 },                     
        {10,  10, 1  }                     
    };                                     
MATRIX PolyMatrixfreddy = {0};    
MATRIX PolyMatrixbonnie = {0};    
MATRIX PolyMatrixchica = {0};    
MATRIX PolyMatrixfoxy = {0};     
MATRIX PolyMatrixgoldenf = {0};    

POLY_F4 *polysparky = {0};                           

SVECTOR RotVectorsparky = {0, 0, 0};                  
VECTOR  MovVectorsparky = {999, 999, CENTERX/2-10, 0};
VECTOR  ScaleVectorsparky = {1024, 1024, 1024};       


SVECTOR VertPossparky[4] = {                          
        {-10, -10, 1 },                        
        {-10,  10, 1 },                        
        {10, -10, 1 },                         
        {10,  10, 1  }                         
    };                                         

MATRIX PolyMatrixsparky = {0};    

//Cam layout
POLY_FT4 *polylayout = {0};                           

SVECTOR RotVectorlayout = {0, 0, 0};                  
VECTOR  MovVectorlayout = {4, 10, CENTERX/2-10, 0};   
VECTOR  ScaleVectorlayout = {ONE, ONE, ONE};          

SVECTOR VertPoslayout[4] = {                     
        {-57, -65, 1 },                     
        {-57,  48, 1 },                     
        { 58,-65, 1 },                      
        { 58,  48, 1  }                     
    };                
MATRIX PolyMatrixlayout = {0};    

//gameover bg
POLY_FT4 *polygameover = {0};                       

SVECTOR RotVectorgameover = {0, 0, 0};              
VECTOR  MovVectorgameover = {0, 0, CENTERX/2-10, 0};
VECTOR  ScaleVectorgameover = {ONE, ONE, ONE};      

SVECTOR VertPosgameover[4] = {                      
        {-80, -58, 1 },                        
        {-80,  58, 1 },                        
        { 80, -58, 1 },                        
        { 80,  58, 1  }                        
    };        

MATRIX PolyMatrixgameover = {0};     

//good job bg
POLY_FT4 *polygoodjob = {0};                          

SVECTOR RotVectorgoodjob = {0, 0, 0};                 
VECTOR  MovVectorgoodjob = {0, 0, CENTERX/2-10, 0};   
VECTOR  ScaleVectorgoodjob = {ONE, ONE, ONE};         

SVECTOR VertPosgoodjob[4] = {                         
        {-79, -56, 1 },                        
        {-80,  56, 1 },                        
        { 79, -56, 1 },                        
        { 80,  56, 1  }                        
    };        

MATRIX PolyMatrixgoodjob = {0};    

//5AM bg
POLY_FT4 *polyfiveam = {0};                       

SVECTOR RotVectorfiveam = {0, 0, 0};              
VECTOR  MovVectorfiveam = {0, 0, CENTERX/2-10, 0};
VECTOR  ScaleVectorfiveam = {2048, 2048, 2048};   

SVECTOR VertPosfiveam[4] = {                      
        {-60, -25, 1 },                         
        {-60,  26, 1 },                         
        { 61, -25, 1 },                         
        { 61,  26, 1  }                         
    };        

MATRIX PolyMatrixfiveam = {0};    

//Icons for camera 
POLY_F4 *polycamWoutline = {0};                            

VECTOR  ScaleVectorpolycamWoutline ={ONE, ONE, ONE};       

POLY_F4 *polycamgreyogreen1A,*polycamgreyogreen1B,*polycamgreyogreen1C,*polycamgreyogreen5,*polycamgreyogreen3,*polycamgreyogreen2A,*polycamgreyogreen2B,*polycamgreyogreen4A,*polycamgreyogreen4B,*polycamgreyogreen6,*polycamgreyogreen7 = {0};   
SVECTOR RotVectorpolycamgreyogreen = {0, 0, 0};            

VECTOR  MovVectorpolycamgreyogreen1A = {0, 0, CENTERX, 0}; 
VECTOR  MovVectorpolycamgreyogreen1B = {0, 0, CENTERX, 0}; 
VECTOR  MovVectorpolycamgreyogreen1C = {0, 0, CENTERX, 0}; 
VECTOR  MovVectorpolycamgreyogreen5 = {0, 0, CENTERX, 0};  
VECTOR  MovVectorpolycamgreyogreen3 = {0, 0, CENTERX, 0};  
VECTOR  MovVectorpolycamgreyogreen2A = {0, 0, CENTERX, 0}; 
VECTOR  MovVectorpolycamgreyogreen2B = {0, 0, CENTERX, 0}; 
VECTOR  MovVectorpolycamgreyogreen4A = {0, 0, CENTERX, 0}; 
VECTOR  MovVectorpolycamgreyogreen4B = {0, 0, CENTERX, 0}; 
VECTOR  MovVectorpolycamgreyogreen6 = {0, 0, CENTERX, 0};  
VECTOR  MovVectorpolycamgreyogreen7 = {0, 0, CENTERX, 0};  

VECTOR  ScaleVectorpolycamgreyogreen ={ONE, ONE, ONE};     
SVECTOR VertPospolycamgreyogreen[4] = {                    
        {-11, -6, 1 },                        
        {-11,  6, 1 },                        
        { 6, -6, 1 },                         
        { 6,  6, 1  }                         
    };                                          
MATRIX PolyMatrixpolycamgreyogreen1A,PolyMatrixpolycamgreyogreen1B,PolyMatrixpolycamgreyogreen1C,PolyMatrixpolycamgreyogreen5,PolyMatrixpolycamgreyogreen3,PolyMatrixpolycamgreyogreen2A,PolyMatrixpolycamgreyogreen2B,PolyMatrixpolycamgreyogreen4A,PolyMatrixpolycamgreyogreen4B,PolyMatrixpolycamgreyogreen6,PolyMatrixpolycamgreyogreen7 = {0};      
//Longest line ever, takes 3 lines in terminal

POLY_FT4 *polygolden = {0};                           

SVECTOR RotVectorgolden = {0, 0, 0};                  
VECTOR  MovVectorgolden = {-132, -60, CENTERX/2-10, 0};
VECTOR  ScaleVectorgolden = {3570, 3570, 3570};       

SVECTOR VertPosgolden[4] = {                          
        {0, 0, 1 },                        
        {0,  114, 1 },                     
        { 258, 0, 1 },                     
        { 258,  114, 1  }                  
    };                                          

MATRIX PolyMatrixgolden = {0};    

POLY_FT4 *polyofficegolden = {0}; 

SVECTOR RotVectorofficegolden = {0, 0, 0};                  
VECTOR  MovVectorofficegolden = {-20, -30, CENTERX/2-10, 0};
VECTOR  ScaleVectorofficegolden = {2048, 2048, 2048};       

SVECTOR VertPosofficegolden[4] = {                          
        {0, 0, 1 },                     
        {0,  210, 1 },                  
        { 218, 0, 1 },                  
        { 218,  210, 1  }               
    };                                          

MATRIX PolyMatrixofficegolden = {0};    

//This function take in charge a specific polygon OR a set of polygon with related elements, depending on the var "num". (1 is for freddy on the menu for example)
//Why ? It's Simple, because the game.c was LONG ASF. Longer than my lifetime I'd say. 
//(and also because it was harder to look for a specific thing and having to scroll like 100000 times to pass by the thing we want. Here, you know you have to look at num 10 for ex.)
void makepoly(int num) {
	if (num == 1) { 
        freddylightframe++;
        if (freddylightframe%3 == 0) {
            Ran(freddyfacechangedchances);
        }
        if (RAN < 4) {
            if (RAN == 1) {
                polyf->tpage = getTPage(freddy.mode&0x3, 0, 704, 256); 
                setClut(polyf, 320, 505);
            }
            if (RAN == 2) {
                polyf->tpage = getTPage(freddy.mode&0x3, 0, 832, 256); 
                setClut(polyf, 320, 505);
            } 
            if (RAN == 3) {
                polyf->tpage = getTPage(freddy.mode&0x3, 0, 832, 0);
                setClut(polyf, 320, 504);
            } 
            freddyfacechangedchances = 75; //For having more chance of freddy FREAKING out
        } else {
            polyf->tpage = getTPage(freddy.mode&0x3, 0, 704, 0); 
            setClut(polyf, 320, 504);
            freddyfacechangedchances = 400;
        }
        
        //I can leave it like that

        //Kinda long 
        if (freddylightframe < 10) {
            setRGB0(polyf, 128, 128, 128);            
        }
        if (freddylightframe > 20) {
            setRGB0(polyf, 100, 100, 100);        
        }
        if (freddylightframe > 40) {
            setRGB0(polyf, 80, 80, 80);          
        }
        if (freddylightframe > 60) {
            setRGB0(polyf, 128, 128, 128);          
        }
        if (freddylightframe > 140) {
            setRGB0(polyf, 80, 80, 80);            
        }
        if (freddylightframe > 150) {
            setRGB0(polyf, 70, 70, 70);               
        }
        if (freddylightframe > 170) {
            setRGB0(polyf, 110, 110, 110);          
        }
        if (freddylightframe > 181) {
            setRGB0(polyf, 85, 85, 85);          
        }
        if (freddylightframe > 195) {
            setRGB0(polyf, 100, 100, 100);            
        }
        if (freddylightframe > 210) {
            setRGB0(polyf, 70, 70, 70);               
        }
        if (freddylightframe > 215) {
            setRGB0(polyf, 110, 110, 110);              
        }
        if (freddylightframe > 225) {
            setRGB0(polyf, 50, 50, 50);               
        }
        if (freddylightframe > 240) {
            setRGB0(polyf, 70, 70, 70);                
        }
        if (freddylightframe > 248) {
            setRGB0(polyf, 105, 105, 105);             
        }
        if (freddylightframe > 256) {
            setRGB0(polyf, 128, 128, 128);                 
        }
        if (freddylightframe > 262) {
            setRGB0(polyf, 75, 75, 75);           
        }
        if (freddylightframe > 268) {
            setRGB0(polyf, 60, 60, 60);              
        }
        if (freddylightframe > 272) {
            setRGB0(polyf, 128, 128, 128);             
        }
        if (freddylightframe > 277) {
            setRGB0(polyf, 120, 120, 120);           
        }
        if (freddylightframe > 285) {
            setRGB0(polyf, 70, 70, 70);              
        }
        if (freddylightframe > 290) {
            setRGB0(polyf, 105, 105, 105);               
        }
        if (freddylightframe > 295) {
            setRGB0(polyf, 128, 128, 128);
        }     
        if (freddylightframe > 298) {
            setRGB0(polyf, 80, 80, 80);              
        }
        if (freddylightframe > 309) {
            setRGB0(polyf, 70, 70, 70);               
        }
        if (freddylightframe > 315) {
            setRGB0(polyf, 100, 100, 100);
        }     
        if (freddylightframe > 322) {
            setRGB0(polyf, 128, 128, 128);
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
    	
    	setUV4(polyf, 46, 0, 46, 255, 252, 0, 255, 252);
    	    
    	addPrim(ot[db], polyf);                         
    	nextpri += sizeof(POLY_FT4);                    
	}//Freddy's face (menu)

	if (num == 2) {
        polyhelpwanted = (POLY_FT4 *)nextpri;          

        RotMatrix(&RotVectorhelpwanted, &PolyMatrixhelpwanted);    
        TransMatrix(&PolyMatrixhelpwanted, &MovVectorhelpwanted);  
        ScaleMatrix(&PolyMatrixhelpwanted, &ScaleVectorhelpwanted);
        
        SetRotMatrix(&PolyMatrixhelpwanted);                 
        SetTransMatrix(&PolyMatrixhelpwanted);          

        setClut(polyhelpwanted, 320, 507);     
        
        setPolyFT4(polyhelpwanted);                          
        
        polyhelpwanted->tpage = getTPage(helpwanted.mode&0x3, 0, 512, 0); 
        
        RotTransPers4(
                    &VertPoshelpwanted[0],      &VertPoshelpwanted[1],      &VertPoshelpwanted[2],      &VertPoshelpwanted[3],
                    (long*)&polyhelpwanted->x0, (long*)&polyhelpwanted->x1, (long*)&polyhelpwanted->x2, (long*)&polyhelpwanted->x3,
                    &polydepth,
                    &polyflag
                    );                                
        
        setUV4(polyhelpwanted, 0, 0, 0, 222, 255, 0, 255, 222);
            
        addPrim(ot[db], polyhelpwanted);                       
        nextpri += sizeof(POLY_FT4);      
	}//help wanted bg

	if (num == 3) { 
        polygolden = (POLY_FT4 *)nextpri;                   
        
        RotMatrix(&RotVectorgolden, &PolyMatrixgolden);           
        TransMatrix(&PolyMatrixgolden, &MovVectorgolden);         
        ScaleMatrix(&PolyMatrixgolden, &ScaleVectorgolden);       
        
        SetRotMatrix(&PolyMatrixgolden);                   
        SetTransMatrix(&PolyMatrixgolden);                 
        
        setPolyFT4(polygolden);                            
        
        polygolden->tpage = getTPage(goldenfreddy.mode&0x3, 0, 320, 256);   
        
        setRGB0(polygolden, 128, 128, 128);            
        
        RotTransPers4(
                    &VertPosgolden[0],      &VertPosgolden[1],      &VertPosgolden[2],      &VertPosgolden[3],
                    (long*)&polygolden->x0, (long*)&polygolden->x1, (long*)&polygolden->x2, (long*)&polygolden->x3,
                    &polydepth,
                    &polyflag
                    );                                 
        
        setUV4(polygolden, 0, 0, 0, 255, 146, 0, 255, 146); 
            
        addPrim(ot[db], polygolden);                        
        
        nextpri += sizeof(POLY_FT4);                  
	}//golden freddy's face (screamer)

	if (num == 4) { 
        polyfreddylightsout = (POLY_FT4 *)nextpri;      
                
        RotMatrix(&RotVectorfreddylightsout, &PolyMatrixfreddylightsout);    
        TransMatrix(&PolyMatrixfreddylightsout, &MovVectorfreddylightsout);  
        ScaleMatrix(&PolyMatrixfreddylightsout, &ScaleVectorfreddylightsout);
        
        SetRotMatrix(&PolyMatrixfreddylightsout);                   
        SetTransMatrix(&PolyMatrixfreddylightsout);                 
        
        setPolyFT4(polyfreddylightsout);                            
        
        setClut(polyfreddylightsout, freddysneak.crect->x, freddysneak.crect->y);

        polyfreddylightsout->tpage = getTPage(freddysneak.mode&0x3, 0, 832, 256);
        
        setRGB0(polyfreddylightsout, glowvar, glowvar, glowvar);                 
        
        RotTransPers4(
                    &VertPosfreddylightsout[0],      &VertPosfreddylightsout[1],      &VertPosfreddylightsout[2],      &VertPosfreddylightsout[3],
                    (long*)&polyfreddylightsout->x0, (long*)&polyfreddylightsout->x1, (long*)&polyfreddylightsout->x2, (long*)&polyfreddylightsout->x3,
                    &polydepth,
                    &polyflag
                    );                                 
        
        setUV4(polyfreddylightsout, 121, 0, 121, 56, 188, 0, 188, 56);
            
        addPrim(ot[db], polyfreddylightsout);                  
        
        nextpri += sizeof(POLY_FT4);                
	}//Freddy's face when lights out

	if (num == 5) { 
	    polyofficegolden = (POLY_FT4 *)nextpri;                    
	    
	    RotMatrix(&RotVectorofficegolden, &PolyMatrixofficegolden);    
	    TransMatrix(&PolyMatrixofficegolden, &MovVectorofficegolden);  
	    ScaleMatrix(&PolyMatrixofficegolden, &ScaleVectorofficegolden);
	    
	    SetRotMatrix(&PolyMatrixofficegolden);                  
	    SetTransMatrix(&PolyMatrixofficegolden);    
 
	    setRGB0(polyofficegolden, 128, 128, 128);
	    setPolyFT4(polyofficegolden);                           
	    
	    setClut(polyofficegolden, 320, 509);
 
	    polyofficegolden->tpage = getTPage(officegoldenfreddy.mode&0x3, 0, 320, 256);
	    
	    RotTransPers4(
	                &VertPosofficegolden[0],      &VertPosofficegolden[1],      &VertPosofficegolden[2],      &VertPosofficegolden[3],
	                (long*)&polyofficegolden->x0, (long*)&polyofficegolden->x1, (long*)&polyofficegolden->x2, (long*)&polyofficegolden->x3,
	                &polydepth,
	                &polyflag
	                );                              
 
	    setUV4(polyofficegolden, 0, 8, 0, 218, 218, 0, 218, 218);
	       
	    addPrim(ot[db], polyofficegolden);                        
	    
	    nextpri += sizeof(POLY_FT4);               
	}//Golden freddy on the office

	if (num == 6) {
         //Door left
         leftdoor = (POLY_FT4 *)nextpri;                  
                 
         RotMatrix(&RotVectorleftdoor, &PolyMatrixleftdoor);    
         TransMatrix(&PolyMatrixleftdoor, &MovVectorleftdoor);  
         ScaleMatrix(&PolyMatrixleftdoor, &ScaleVectorleftdoor);
         
         SetRotMatrix(&PolyMatrixleftdoor);            
         SetTransMatrix(&PolyMatrixleftdoor);          
         
         setPolyFT4(leftdoor);                         
         
         setClut(leftdoor, doors.crect->x, doors.crect->y);    
         leftdoor->tpage = getTPage(doors.mode&0x3, 0, 320, 0);
         
         if (doorclosedL == 1) {setRGB0(leftdoor, 76, 76, 76);} //For preventing things to blink fast asf
         
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
         
         setClut(rightdoor, doors.crect->x, doors.crect->y); 
         rightdoor->tpage = getTPage(doors.mode&0x3, 0, 320, 0);   
         
         if (doorclosedR == 1) {setRGB0(rightdoor, 76, 76, 76);} //For preventing things to blink fast asf again
         
         RotTransPers4(
                     &VertPosrightdoor[0],      &VertPosrightdoor[1],      &VertPosrightdoor[2],      &VertPosrightdoor[3],
                     (long*)&rightdoor->x0, (long*)&rightdoor->x1, (long*)&rightdoor->x2, (long*)&rightdoor->x3,
                     &polydepth,
                     &polyflag
                     );                           
         
         setUV4(rightdoor, 79, 0, 79, 255, 147, 0, 147, 255); //+55X bcs of where the door is on VRAM
             
         addPrim(ot[db], rightdoor);                         
         
         nextpri += sizeof(POLY_FT4);          

         //second 
         polyofficeright = (POLY_FT4 *)nextpri;                   
        
         RotMatrix(&RotVectorofficeright, &PolyMatrixofficeright);
         TransMatrix(&PolyMatrixofficeright, &MovVectorofficeright);  
         ScaleMatrix(&PolyMatrixofficeright, &ScaleVectorofficeright);
         
         SetRotMatrix(&PolyMatrixofficemiddle);                
         SetTransMatrix(&PolyMatrixofficemiddle);              
         
         setClut(polyofficeright, 320, 506); 

         setPolyFT4(polyofficeright);                          
         
         polyofficeright->tpage = getTPage(officeRIGHT.mode&0x3, 0, officeRIGHT.prect->x, officeRIGHT.prect->y);
         
         setRGB0(polyofficeright, 128, 128, 128);              
         
         RotTransPers4(
                     &VertPosofficeright[0],      &VertPosofficeright[1],      &VertPosofficeright[2],      &VertPosofficeright[3],
                     (long*)&polyofficeright->x0, (long*)&polyofficeright->x1, (long*)&polyofficeright->x2, (long*)&polyofficeright->x3,
                     &polydepth,
                     &polyflag
                     );                                 
         
         setUV4(polyofficeright, 0, 0, 0, 252, 220, 0, 220, 252);
             

         addPrim(ot[db], polyofficeright);                       
         
         nextpri += sizeof(POLY_FT4);                

         //third 
         polyofficeleft = (POLY_FT4 *)nextpri;                 
        
                 
         RotMatrix(&RotVectorofficeleft, &PolyMatrixofficeleft); 
         TransMatrix(&PolyMatrixofficeleft, &MovVectorofficeleft);  
         ScaleMatrix(&PolyMatrixofficeleft, &ScaleVectorofficeleft);
         
         SetRotMatrix(&PolyMatrixofficemiddle);              
         SetTransMatrix(&PolyMatrixofficemiddle);            
         
         setClut(polyofficeleft, 320, 507); 

         setPolyFT4(polyofficeleft);                         
         
         polyofficeleft->tpage = getTPage(officeLEFT.mode&0x3, 0, 704, 0);
         
         setRGB0(polyofficeleft, 128, 128, 128);            
         
         RotTransPers4(
                     &VertPosofficeleft[0],      &VertPosofficeleft[1],      &VertPosofficeleft[2],      &VertPosofficeleft[3],
                     (long*)&polyofficeleft->x0, (long*)&polyofficeleft->x1, (long*)&polyofficeleft->x2, (long*)&polyofficeleft->x3,
                     &polydepth,
                     &polyflag
                     );                               
         
         setUV4(polyofficeleft, 0, 0, 0, 255, 220, 0, 220, 255); 

         addPrim(ot[db], polyofficeleft);                     
         
         nextpri += sizeof(POLY_FT4);      

         //first
         polyofficemiddle = (POLY_FT4 *)nextpri;                 
                 
         RotMatrix(&RotVectorofficemiddle, &PolyMatrixofficemiddle);    
         TransMatrix(&PolyMatrixofficemiddle, &MovVectorofficemiddle);  
         ScaleMatrix(&PolyMatrixofficemiddle, &ScaleVectorofficemiddle);
         
         SetRotMatrix(&PolyMatrixofficemiddle);                  
         SetTransMatrix(&PolyMatrixofficemiddle);                
         
         setClut(polyofficemiddle, 320, 508);

         setPolyFT4(polyofficemiddle);                           
         
         polyofficemiddle->tpage = getTPage(officeMIDDLE.mode&0x3, 0, 832, 0); 
         
         setRGB0(polyofficemiddle, 128, 128, 128);      
         
         RotTransPers4(
                     &VertPosofficemiddle[0],      &VertPosofficemiddle[1],      &VertPosofficemiddle[2],      &VertPosofficemiddle[3],
                     (long*)&polyofficemiddle->x0, (long*)&polyofficemiddle->x1, (long*)&polyofficemiddle->x2, (long*)&polyofficemiddle->x3,
                     &polydepth,
                     &polyflag
                     );                               
         
         setUV4(polyofficemiddle, 0, 0, 0, 255, 255, 0, 255, 255);
             

         addPrim(ot[db], polyofficemiddle);                       
         
         nextpri += sizeof(POLY_FT4);                            
	}//Office with doors

	if (num == 7) { 
	} //Icon's grey or green rectangle

	if (num == 8) {
	}//icon for camera

	if (num == 9) {

        polylayout = (POLY_FT4 *)nextpri;              
                
        RotMatrix(&RotVectorlayout, &PolyMatrixlayout);
        TransMatrix(&PolyMatrixlayout, &MovVectorlayout);  
        ScaleMatrix(&PolyMatrixlayout, &ScaleVectorlayout);
        
        SetRotMatrix(&PolyMatrixlayout);                   
        SetTransMatrix(&PolyMatrixlayout);                 
        
        setPolyFT4(polylayout);                     

        setClut(polylayout,960,196);       
        
        polylayout->tpage = getTPage(layout.mode&0x3, 0, 448, 256); 
        
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
	}//camera's layout

	if (num == 10) {
        //five am OR six am tim (it's marked five am but sixam.tim go into the fiveam.tim emplacement)
        polyfiveam = (POLY_FT4 *)nextpri;     
        
        
                
        RotMatrix(&RotVectorfiveam, &PolyMatrixfiveam);    
        TransMatrix(&PolyMatrixfiveam, &MovVectorfiveam);  
        ScaleMatrix(&PolyMatrixfiveam, &ScaleVectorfiveam);
        
        SetRotMatrix(&PolyMatrixfiveam);                   
        SetTransMatrix(&PolyMatrixfiveam);                 
        
        setPolyFT4(polyfiveam);                            
        setRGB0(polyfiveam, 128,128,128);
        
        setClut(polyfiveam, fiveam.crect->x, fiveam.crect->y);      
        polyfiveam->tpage = getTPage(fiveam.mode&0x3, 0, 832, 256); 
        
        RotTransPers4(
                    &VertPosfiveam[0],      &VertPosfiveam[1],      &VertPosfiveam[2],      &VertPosfiveam[3],
                    (long*)&polyfiveam->x0, (long*)&polyfiveam->x1, (long*)&polyfiveam->x2, (long*)&polyfiveam->x3,
                    &polydepth,
                    &polyflag
                    );                               
        
        setUV4(polyfiveam, 0, 0, 0, 48, 121, 0, 121, 48);
            
        addPrim(ot[db], polyfiveam);                     
        nextpri += sizeof(POLY_FT4);           
	}//5am or 6am image

	if (num == 11) {
        if (nextnightframes > 400 && nextnightframes < 5766 && customnextnightactivation == 1)
        { //YIPEEEEEEEEEEEEEEEEEEEEEEEEEEEE
            FntPrint("        credits : Harvey Rothman"); //Gonna give credits to this person ! ;)


            if (rgbindicator == 0) {
                rgbblue++; //
                if (rgbblue == 135) {rgbindicator = 1;} //WAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
            }
            if (rgbindicator == 1){
                rgbred--;
                if (rgbred == 79) {rgbindicator = 2;} //EEEEEEEEEEEEE
            }
            if (rgbindicator == 2) {
                rgbgreen++;
                if (rgbgreen == 135) {rgbindicator = 3;} //YAHOUU OUUUUUUUUUUUUUUUUUU
            }
            if (rgbindicator == 3) {
                rgbblue--;
                if (rgbblue == 79) {rgbindicator = 4;} //YHGTJKRFEDZSOAQPBNGFVCJDX
            }
            if (rgbindicator == 4){
                rgbred++;
                if (rgbred == 135) {rgbindicator = 5;} //WAAAAAAAAAAAAOOOOOOOOOOOOO
            }
            if (rgbindicator == 5) {//NOnoOooOO already done :'c
                rgbgreen--;
                if (rgbgreen == 79) {rgbindicator = 0;} //WE'RE SO BACK
            }
        }
        if (nextnightframes == 5766) {
            rgbred = 128;
            rgbgreen = 128;
            rgbblue = 128;
        }

        polygoodjob = (POLY_FT4 *)nextpri;             
                
        RotMatrix(&RotVectorgoodjob, &PolyMatrixgoodjob);    
        TransMatrix(&PolyMatrixgoodjob, &MovVectorgoodjob);  
        ScaleMatrix(&PolyMatrixgoodjob, &ScaleVectorgoodjob);
        
        SetRotMatrix(&PolyMatrixgoodjob);                    
        SetTransMatrix(&PolyMatrixgoodjob);                  
        
        setPolyFT4(polygoodjob);                             
        setRGB0(polygoodjob, rgbred,rgbgreen,rgbblue);
        
        setClut(polygoodjob, goodjob.crect->x, goodjob.crect->y);       

        polygoodjob->tpage = getTPage(goodjob.mode&0x3, 0, 384, goodjob.prect->y);
        
        RotTransPers4(
                    &VertPosgoodjob[0],      &VertPosgoodjob[1],      &VertPosgoodjob[2],      &VertPosgoodjob[3],
                    (long*)&polygoodjob->x0, (long*)&polygoodjob->x1, (long*)&polygoodjob->x2, (long*)&polygoodjob->x3,
                    &polydepth,
                    &polyflag
                    );                                
        
        setUV4(polygoodjob, 0, 0, 0, 231, 254, 0, 254, 231);
            
        addPrim(ot[db], polygoodjob);                       
        nextpri += sizeof(POLY_FT4);                 
	}//good job BG

	if (num == 12) {
        polygameover = (POLY_FT4 *)nextpri;               
                
        RotMatrix(&RotVectorgameover, &PolyMatrixgameover);    
        TransMatrix(&PolyMatrixgameover, &MovVectorgameover);  
        ScaleMatrix(&PolyMatrixgameover, &ScaleVectorgameover);
        
        SetRotMatrix(&PolyMatrixgameover);                 
        SetTransMatrix(&PolyMatrixgameover); 

        setClut(polygameover, 320, 510);

        setPolyFT4(polygameover);                          
        
        setRGB0(polygameover, 128, 128, 128);              

        polygameover->tpage = getTPage(gameover.mode&0x3, 0, 832, 0); 
        
        RotTransPers4(
                    &VertPosgameover[0],      &VertPosgameover[1],      &VertPosgameover[2],      &VertPosgameover[3],
                    (long*)&polygameover->x0, (long*)&polygameover->x1, (long*)&polygameover->x2, (long*)&polygameover->x3,
                    &polydepth,
                    &polyflag
                    );                                
        
        setUV4(polygameover, 0, 0, 0, 222, 230, 0, 230, 222);
            
        addPrim(ot[db], polygameover);                       
        nextpri += sizeof(POLY_FT4);                 
	}//Game over BG

	if (num == 13) {
        polyicon = (POLY_FT4 *)nextpri;               
                
        RotMatrix(&RotVectoricon, &PolyMatrixicon);    
        TransMatrix(&PolyMatrixicon, &MovVectoricon);  
        ScaleMatrix(&PolyMatrixicon, &ScaleVectoricon);
        
        SetRotMatrix(&PolyMatrixicon);                 
        SetTransMatrix(&PolyMatrixicon); 

        setPolyFT4(polyicon);                          
        
        setRGB0(polyicon, 128, 128, 128);              

        polyicon->tpage = getTPage(load.mode&0x3, 0, 640, 256); 
        
        RotTransPers4(
                    &VertPosicon[0],      &VertPosicon[1],      &VertPosicon[2],      &VertPosicon[3],
                    (long*)&polyicon->x0, (long*)&polyicon->x1, (long*)&polyicon->x2, (long*)&polyicon->x3,
                    &polydepth,
                    &polyflag
                    );                                
        
        setUV4(polyicon, 0, 0, 0, 80, 80, 0, 80, 80);
            
        addPrim(ot[db], polyicon);                       
        nextpri += sizeof(POLY_FT4);         
	} //Loading icon
}