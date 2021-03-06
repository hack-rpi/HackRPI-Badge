// size_t
#include <stddef.h>
// uint8_t
#include <stdint.h>

/// The first character represented in the typeset.
const char TYPESET_FIRST_CHAR = ' ';
/// The last character represented in the typeset.
const char TYPESET_LAST_CHAR  = '~';
/// A list of column offsets per character.
const size_t TYPESET_OFFSETS[] = 
{
	0,   /*   */
	2,   /* ! */
	3,   /* " */
	6,   /* # */
	13,  /* $ */
	18,  /* % */
	25,  /* & */
	31,  /* ' */
	32,  /* ( */
	35,  /* ) */
	38,  /* * */
	43,  /* + */
	48,  /* , */
	50,  /* - */
	55,  /* . */
	57,  /* / */
	60,  /* 0 */
	65,  /* 1 */
	70,  /* 2 */
	75,  /* 3 */
	80,  /* 4 */
	85,  /* 5 */
	90,  /* 6 */
	95,  /* 7 */
	100, /* 8 */
	105, /* 9 */
	110, /* : */
	112, /* ; */
	114, /* < */
	118, /* = */
	122, /* > */
	126, /* ? */
	131, /* @ */
	137, /* A */
	142, /* B */
	146, /* C */
	150, /* D */
	154, /* E */
	158, /* F */
	162, /* G */
	166, /* H */
	170, /* I */
	173, /* J */
	176, /* K */
	180, /* L */
	183, /* M */
	188, /* N */
	192, /* O */
	196, /* P */
	200, /* Q */
	204, /* R */
	208, /* S */
	212, /* T */
	215, /* U */
	219, /* V */
	224, /* W */
	229, /* X */
	234, /* Y */
	239, /* Z */
	243, /* [ */
	246, /* \ */
	249, /* ] */
	252, /* ^ */
	255, /* _ */
	258, /* ` */
	260, /* a */
	264, /* b */
	268, /* c */
	271, /* d */
	275, /* e */
	279, /* f */
	283, /* g */
	287, /* h */
	291, /* i */
	292, /* j */
	294, /* k */
	298, /* l */
	301, /* m */
	306, /* n */
	310, /* o */
	314, /* p */
	318, /* q */
	322, /* r */
	326, /* s */
	330, /* t */
	333, /* u */
	337, /* v */
	340, /* w */
	345, /* x */
	350, /* y */
	354, /* z */
	358, /* { */
	361, /* | */
	362, /* } */
	365, /* ~ */
	370, /*end*/
};

/// An 8 pixel tall bitmap of the typeset. Every byte is a column in the bitmap.
const uint8_t TYPESET_BITMAP[] = {
	0x00,
	0x00,
	0xbf,
	0x03,
	0x00,
	0x03,
	0x20,
	0xe4,
	0x3c,
	0xe7,
	0x3c,
	0x27,
	0x04,
	0x44,
	0x4a,
	0xff,
	0x52,
	0x22,
	0x02,
	0xc5,
	0x22,
	0x18,
	0x44,
	0xa3,
	0x40,
	0x76,
	0x89,
	0x99,
	0x66,
	0xa0,
	0x10,
	0x06,
	0x3c,
	0x42,
	0x81,
	0x81,
	0x42,
	0x3c,
	0x0a,
	0x04,
	0x1f,
	0x04,
	0x0a,
	0x10,
	0x10,
	0x7c,
	0x10,
	0x10,
	0x80,
	0x60,
	0x10,
	0x10,
	0x10,
	0x10,
	0x10,
	0xc0,
	0xc0,
	0xe0,
	0x3c,
	0x07,
	0x7e,
	0x87,
	0x99,
	0xe1,
	0x7e,
	0x84,
	0x82,
	0xff,
	0x80,
	0x80,
	0xc6,
	0xa1,
	0x91,
	0x89,
	0x86,
	0x66,
	0x81,
	0x89,
	0x89,
	0x76,
	0x18,
	0x14,
	0x12,
	0xff,
	0x10,
	0x4f,
	0x89,
	0x89,
	0x89,
	0x71,
	0x7e,
	0x89,
	0x89,
	0x89,
	0x72,
	0x01,
	0xc1,
	0x31,
	0x0d,
	0x03,
	0x76,
	0x89,
	0x89,
	0x89,
	0x76,
	0x4e,
	0x91,
	0x91,
	0x91,
	0x7e,
	0x66,
	0x66,
	0xa6,
	0x66,
	0x10,
	0x28,
	0x28,
	0x44,
	0x28,
	0x28,
	0x28,
	0x28,
	0x44,
	0x28,
	0x28,
	0x10,
	0x02,
	0x01,
	0xb1,
	0x09,
	0x06,
	0x7e,
	0x81,
	0xb9,
	0xa5,
	0xb9,
	0x3e,
	0xf8,
	0x16,
	0x11,
	0x16,
	0xf8,
	0xff,
	0x89,
	0x89,
	0x76,
	0x7e,
	0x81,
	0x81,
	0x81,
	0xff,
	0x81,
	0x81,
	0x7e,
	0xff,
	0x89,
	0x89,
	0x81,
	0xff,
	0x09,
	0x09,
	0x01,
	0x7e,
	0x81,
	0x91,
	0xf1,
	0xff,
	0x08,
	0x08,
	0xff,
	0x81,
	0xff,
	0x81,
	0x40,
	0x80,
	0x7f,
	0xff,
	0x18,
	0x24,
	0xc3,
	0xff,
	0x80,
	0x80,
	0xff,
	0x06,
	0x18,
	0x06,
	0xff,
	0xff,
	0x0c,
	0x30,
	0xff,
	0x7e,
	0x81,
	0x81,
	0x7e,
	0xff,
	0x11,
	0x11,
	0x0e,
	0x3e,
	0x41,
	0xc1,
	0xbe,
	0xff,
	0x11,
	0x31,
	0xce,
	0x86,
	0x89,
	0x91,
	0x61,
	0x01,
	0xff,
	0x01,
	0x7f,
	0x80,
	0x80,
	0x7f,
	0x1f,
	0x60,
	0x80,
	0x60,
	0x1f,
	0xff,
	0x60,
	0x18,
	0x60,
	0xff,
	0xc3,
	0x24,
	0x18,
	0x24,
	0xc3,
	0x07,
	0x08,
	0xf0,
	0x08,
	0x07,
	0xc1,
	0xb1,
	0x8d,
	0x83,
	0xff,
	0x81,
	0x81,
	0x07,
	0x3c,
	0xe0,
	0x81,
	0x81,
	0xff,
	0x02,
	0x01,
	0x02,
	0x80,
	0x80,
	0x80,
	0x01,
	0x02,
	0x40,
	0xa8,
	0xa8,
	0xf0,
	0xff,
	0x88,
	0x88,
	0x70,
	0x70,
	0x88,
	0x88,
	0x70,
	0x88,
	0x88,
	0xff,
	0x70,
	0xa8,
	0xa8,
	0x90,
	0x08,
	0xfe,
	0x09,
	0x09,
	0x98,
	0xa4,
	0xa4,
	0x78,
	0xff,
	0x08,
	0x08,
	0xf0,
	0xf4,
	0x90,
	0x74,
	0xff,
	0x20,
	0x50,
	0x88,
	0x81,
	0xff,
	0x80,
	0xf0,
	0x08,
	0x30,
	0x08,
	0xf0,
	0xf8,
	0x08,
	0x08,
	0xf0,
	0x70,
	0x88,
	0x88,
	0x70,
	0xfc,
	0x24,
	0x24,
	0x18,
	0x18,
	0x24,
	0x24,
	0xfc,
	0xf8,
	0x10,
	0x08,
	0x08,
	0x90,
	0xa8,
	0xa8,
	0x48,
	0x04,
	0xff,
	0x04,
	0x78,
	0x80,
	0x80,
	0xf8,
	0x78,
	0x80,
	0x78,
	0x78,
	0x80,
	0x60,
	0x80,
	0x78,
	0x88,
	0x50,
	0x20,
	0x50,
	0x88,
	0x98,
	0xa0,
	0xa0,
	0x78,
	0x88,
	0xc8,
	0xa8,
	0x98,
	0x08,
	0x76,
	0x81,
	0xff,
	0x81,
	0x76,
	0x08,
	0x10,
	0x08,
	0x10,
	0x20,
	0x10
};