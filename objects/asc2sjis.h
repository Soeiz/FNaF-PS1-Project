/*
 * $PSLibId: Runtime Library Release 3.6$
 */
/*****************************************************************
 *
 * file: ascii2sjis.c
 *
 *      Copyright (C) 1995 by Sony Computer Entertainment Inc.
 *                                        All Rights Reserved.
 *
 *      Sony Computer Entertainment Inc. Development Department
 *
 *****************************************************************/

/* 
 * ASCII code to Shift-JIS code transfer table
 */
static unsigned short ascii_table[3][2] = {
	{0x824f, 0x30},	/* 0-9  */
	{0x8260, 0x41},	/* A-Z  */
	{0x8281, 0x61},	/* a-z  */
};

/* 
 * ASCII code to Shift-JIS code transfer table (kigou)
 */
static unsigned short ascii_k_table[] = {
	0x8140,		/*   */
	0x8149,		/* ! */
	0x8168,		/* " */
	0x8194,		/* # */
	0x8190,		/* $ */
	0x8193,		/* % */
	0x8195,		/* & */
	0x8166,		/* ' */
	0x8169,		/* ( */
	0x816a,		/* ) */
	0x8196,		/* * */
	0x817b,		/* + */
	0x8143,		/* , */
	0x817c,		/* - */
	0x8144,		/* . */
	0x815e,		/* / */
	0x8146,		/* : */
	0x8147,		/* ; */
	0x8171,		/* < */
	0x8181,		/* = */
	0x8172,		/* > */
	0x8148,		/* ? */
	0x8197,		/* @ */
	0x816d,		/* [ */
	0x818f,		/* \ */
	0x816e,		/* ] */
	0x814f,		/* ^ */
	0x8151,		/* _ */
	0x8165,		/* ` */
	0x816f,		/* { */
	0x8162,		/* | */
	0x8170,		/* } */
	0x8150,		/* ~ */
};

/* 
 * ASCII code to Shift-JIS code transfer function 
  */
unsigned short ascii2sjis(unsigned char ascii_code) {
	int sjis_code = 0;
	unsigned char stmp = 0;
	unsigned char stmp2 = 0;

	if ((ascii_code >= 0x20) && (ascii_code <= 0x2f))
		stmp2 = 1;
	else
	if ((ascii_code >= 0x30) && (ascii_code <= 0x39))
		stmp = 0;
	else
	if ((ascii_code >= 0x3a) && (ascii_code <= 0x40))
		stmp2 = 11;
	else
	if ((ascii_code >= 0x41) && (ascii_code <= 0x5a))
		stmp = 1;
	else
	if ((ascii_code >= 0x5b) && (ascii_code <= 0x60))
		stmp2 = 37;
	else
	if ((ascii_code >= 0x61) && (ascii_code <= 0x7a))
		stmp = 2;
	else
	if ((ascii_code >= 0x7b) && (ascii_code <= 0x7e))
		stmp2 = 63;
	else {
		// printf("bad ASCII code 0x%x\n", ascii_code);
		return(0);
	}

	if (stmp2)
		sjis_code = ascii_k_table[ascii_code - 0x20 - (stmp2 - 1)];
	else
		sjis_code = ascii_table[stmp][0] + ascii_code - ascii_table[stmp][1];

	return(sjis_code);
}
