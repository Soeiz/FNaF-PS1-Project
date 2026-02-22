//SAVE SYSTEM

    #define SAVENAME    "FRFZBP-93FNAF"

    #define SAVETITLE   "Five Night at Freddy's"

    // Test save icon's CLUT (or color palette) data
        u_short saveIcon_clut[16] = {
            0x0000,0x0842,0x7FFF,0x0000,
            0x0000,0x0000,0x0000,0x0000,
            0x0000,0x0000,0x0000,0x0000,
            0x0000,0x0000,0x0000,0x0000
        };

    // Test save icon's image data (16x16 4-bit)
        u_short saveIcon_image[1][16][4] = {
            // First icon frame
            {{0x0000,0x0000,0x0000,0x0000 },
            { 0x0000,0x1110,0x0001,0x0000 },
            { 0x0000,0x2210,0x0001,0x0000 },
            { 0x0111,0x2210,0x1001,0x0011 },
            { 0x0121,0x1121,0x1012,0x0012 },
            { 0x1011,0x2222,0x0122,0x0011 },
            { 0x2100,0x2222,0x1222,0x0000 },
            { 0x2100,0x2222,0x1222,0x0000 },
            { 0x2100,0x2222,0x1222,0x0000 },
            { 0x2100,0x2222,0x1222,0x0000 },
            { 0x2210,0x2222,0x2222,0x0001 },
            { 0x2210,0x2222,0x2222,0x0001 },
            { 0x2210,0x2222,0x2222,0x0001 },
            { 0x2100,0x2222,0x1222,0x0000 },
            { 0x1000,0x1111,0x0111,0x0000 },
            { 0x0000,0x0000,0x0000,0x0000 }}
        };

    // Save block header structure
        typedef struct {
            char    id[2];      // Always 'SC'
            char    type;       // Number of icon frames (0x11 - one frame, 0x12 - two frames, 0x13 - three frames)
            char    size;       // Size of save file in blocks
            u_short title[32];  // Title of save file (encoded in Shift-JIS format)
            char    pad[28];    // Unused
            char    clut[32];   // Color palette of icon frames (16 RGB5X1 16-bit color entries)
        } SAVEHDR;

    short currentCard=0;    // Current card number
    long  cardCmd;          // Card command return value
    long  slotResult[2];    // Slot result value

    int MemoryCardState = 0;

    /*
        MemoryCardState :

        - 0 : Not present
        - 1 : Present (Formatted and good) + Save already present
        - 2 : Present (Formatted and good) - Save 
        - 3 : Bad Card
        - 4 : Not Formatted
        - 5 : Full


    */

void MemoryCardSave(void) {

    SAVEHDR header;

    header.id[0]='S'; header.id[1]='C'; // ID must always say SC
    header.type     = 0x11;                 // 1 frame icon
    header.size     = 1;                    // 1 block
        
    // Convert save title from ASCII to SJIS
    asc2sjis(SAVETITLE, header.title);
    
    // Copy icon's CLUT to the header
    memcpy(header.clut, saveIcon_clut, 32);

    // Open save block for writing. If it doesn't exist, create it.
    if (MemCardOpen(16*currentCard, SAVENAME, O_WRONLY) == McErrFileNotExist) {
        
        if (MemCardCreateFile(16*currentCard, SAVENAME, 1) == 0x07) { // Is memory card full?
            
            MemoryCardState = 5;

            return;

        }
    
    }

    // Open the (created) file
    MemCardOpen(16*currentCard, SAVENAME, O_WRONLY);

    // Write the header
    MemCardWriteData((u_long*)&header, 128*0, 128);
    while(MemCardSync(1, &cardCmd, &slotResult[0]) == 0);
    
    // Write the icon frames
    MemCardWriteData((u_long*)&saveIcon_image, 128*1, 256);
    while(MemCardSync(1, &cardCmd, &slotResult[0]) == 0);

    // Write thingies
    MemCardWriteData((u_long*)&night, 128*2, 128);
    while(MemCardSync(1, &cardCmd, &slotResult[0]) == 0);

    MemCardWriteData((u_long*)&rizzingFDone, 128*3, 128);
    while(MemCardSync(1, &cardCmd, &slotResult[0]) == 0);

    MemCardWriteData((u_long*)&hellNightDone, 128*4, 128);
    while(MemCardSync(1, &cardCmd, &slotResult[0]) == 0);

    MemCardWriteData((u_long*)&fourTwentyDone, 128*5, 128);
    while(MemCardSync(1, &cardCmd, &slotResult[0]) == 0);

    MemCardWriteData((u_long*)&goldenfredied, 128*6, 128);
    while(MemCardSync(1, &cardCmd, &slotResult[0]) == 0);

    MemCardWriteData((u_long*)&diedOnNight1, 128*7, 128);
    while(MemCardSync(1, &cardCmd, &slotResult[0]) == 0);

    MemCardWriteData((u_long*)&Night6State, 128*8, 128);
    while(MemCardSync(1, &cardCmd, &slotResult[0]) == 0);

    MemCardWriteData((u_long*)&bestNight, 128*9, 128);
    while(MemCardSync(1, &cardCmd, &slotResult[0]) == 0);

    //Close the created file
    MemCardClose();

}

void MemoryCardLoad(void) {

    // Open the created file
    MemCardOpen(16*currentCard, SAVENAME, O_RDONLY);

    // Read thingies
    MemCardReadData((u_long*)&night, 128*2, 128);
    while(MemCardSync(1, &cardCmd, &slotResult[0]) == 0);

    MemCardReadData((u_long*)&rizzingFDone, 128*3, 128);
    while(MemCardSync(1, &cardCmd, &slotResult[0]) == 0);

    MemCardReadData((u_long*)&hellNightDone, 128*4, 128);
    while(MemCardSync(1, &cardCmd, &slotResult[0]) == 0);

    MemCardReadData((u_long*)&fourTwentyDone, 128*5, 128);
    while(MemCardSync(1, &cardCmd, &slotResult[0]) == 0);

    MemCardReadData((u_long*)&goldenfredied, 128*6, 128);
    while(MemCardSync(1, &cardCmd, &slotResult[0]) == 0);

    MemCardReadData((u_long*)&diedOnNight1, 128*7, 128);
    while(MemCardSync(1, &cardCmd, &slotResult[0]) == 0);

    MemCardReadData((u_long*)&Night6State, 128*8, 128);
    while(MemCardSync(1, &cardCmd, &slotResult[0]) == 0);

    MemCardReadData((u_long*)&bestNight, 128*9, 128);
    while(MemCardSync(1, &cardCmd, &slotResult[0]) == 0);

    MemCardClose();

    for (int i = 1; i < bestNight && bestNight > 1; i++) {
        achievements[i-1] = true;
    }

    switch(Night6State) {

        case 1:
            achievements[4] = true;
            night6unlock = true;
            menuSelectionMax++;
        break;
        case 2:
            achievements[4] = true;
            achievements[5] = true;
            night6unlock = true;
            menuSelectionMax++;
        break;
    }

    if (fourTwentyDone) {achievements[6] = true;}

    if (hellNightDone) {achievements[7] = true;}

    if (goldenfredied) {achievements[8] = true;}

    if (rizzingFDone) {achievements[9] = true;}

    if (diedOnNight1) {achievements[10] = true;}

}

void MemoryCardCheck(void) {

    // Check if a card is present
    MemCardExist(16*currentCard);
    while(MemCardSync(1, &cardCmd, &slotResult[0]) == 0);
    
    // Check if card is properly formatted (if the card is present in the first place)
    if ((slotResult[0] == McErrNone) || (slotResult[0] == McErrNewCard)) {
        
        MemCardAccept(16*currentCard);
        while(MemCardSync(1, &cardCmd, &slotResult[0]) == 0);
        
    }

    switch(MemCardOpen(16*currentCard, SAVENAME, O_WRONLY)) { //Outputs as said in the LIBREF46.pdf page 204

        case 0x01: //McErrCardNotExist
            MemoryCardState = 0;
        break;

        case 0x00: //McErrNone
            MemoryCardState = 1;

            MemoryCardLoad();
        break;  

        case 0x05: //McErrFileNotExist
            MemoryCardState = 2;

            MemoryCardSave();
        break;

        case 0x02: //McErrCardInvalid
            MemoryCardState = 3;
        break;

        case 0x04: //McErrNotFormat
            MemoryCardState = 4;
        break;


    }

}