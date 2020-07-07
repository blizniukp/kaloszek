// Created by http://oleddisplay.squix.ch/ Consider a donation
// In case of problems make sure that you are using the font file with the correct version!
const uint8_t Roboto_Black_25Bitmaps[] PROGMEM = {

	// Bitmap Data:
	0x00, // ' '
	0xFB,0xE7,0x9E,0x79,0xE7,0x9E,0x71,0xC7,0x1C,0x00,0x07,0x3E,0xF9,0xC0, // '!'
	0xE6,0xE6,0xE6,0xE6,0xE6,0xE6,0xE6, // '"'
	0x0E,0x60,0x39,0x80,0xCE,0x03,0x38,0x0C,0xE0,0x33,0x0F,0xFF,0xBF,0xFE,0x1D,0xC0,0x67,0x01,0x9C,0x3F,0xFC,0xFF,0xF0,0xE6,0x03,0x38,0x0C,0xE0,0x33,0x81,0xCC,0x00, // '#'
	0x02,0x00,0x10,0x00,0x80,0x3F,0x03,0xFE,0x3F,0xF1,0xE7,0xDF,0x1E,0xF8,0xF3,0xC0,0x1F,0x00,0x7F,0x01,0xFC,0x01,0xF0,0x07,0xDE,0x1E,0xF0,0xF7,0xC7,0x9F,0xFC,0xFF,0xC1,0xF8,0x03,0x00,0x18,0x00, // '$'
	0x3C,0x00,0x3F,0x00,0x39,0xC6,0x1C,0xE3,0x8E,0x73,0x87,0x3B,0x81,0xF9,0x80,0x79,0xC0,0x00,0xC0,0x00,0xE0,0x00,0xEF,0x80,0x6F,0xE0,0x77,0x70,0x73,0x18,0x31,0x8C,0x38,0xE6,0x08,0x7F,0x00,0x1F,0x00, // '%'
	0x0F,0x00,0x3F,0xC0,0x3F,0xE0,0x79,0xE0,0x78,0xE0,0x79,0xE0,0x3F,0xC0,0x3F,0x80,0x1F,0x00,0x3F,0x1C,0x7F,0x9C,0xF7,0xFC,0xF3,0xFC,0xF1,0xFC,0xF8,0xF8,0xFF,0xF8,0x7F,0xFC,0x1F,0xBE, // '&'
	0xEE,0xEC,0xCC,0xC0, // '''
	0x04,0x38,0x71,0xC7,0x0E,0x1C,0x70,0xE1,0xC3,0x87,0x0E,0x1C,0x38,0x70,0xE1,0xC3,0x83,0x87,0x0E,0x0E,0x0E,0x1C,0x08, // '('
	0x80,0xE0,0xE0,0x70,0x78,0x38,0x3C,0x1C,0x1C,0x1C,0x1E,0x1E,0x1E,0x1E,0x1E,0x1E,0x1C,0x1C,0x1C,0x3C,0x38,0x78,0x70,0xE0,0xE0,0x80, // ')'
	//18B
	0x00, 0x00, 0x1F, 0x01, 0xFC, 0x1C, 0x70, 0xC1, 0x86, 0x0C, 0x30, 0x61, 
	0xC7, 0x07, 0xF0, 0x1F, 0x00, 0x00,
	
	//0x06,0x00,0x30,0x01,0x80,0xCC,0xC7,0xFE,0x7F,0xF8,0x3C,0x03,0xE0,0x1B,0x81,0xCE,0x04,0x20, // '*'
	0x0F,0x00,0x78,0x03,0xC0,0x1E,0x00,0xF0,0x7F,0xFB,0xFF,0xDF,0xFE,0x0F,0x00,0x78,0x03,0xC0,0x1E,0x00,0xF0,0x00, // '+'
	0x73,0x9C,0xE7,0x7B,0x88, // ','
	0xFE,0xFE,0xFE, // '-'
	0x73,0xEF,0x9C, // '.'
	0x03,0x81,0xC0,0x70,0x1C,0x0E,0x03,0x80,0xE0,0x70,0x1C,0x07,0x01,0x80,0xE0,0x38,0x0E,0x07,0x01,0xC0,0x70,0x38,0x0E,0x03,0x80, // '/'
	0x1F,0x81,0xFE,0x1F,0xF9,0xF3,0xCF,0x0F,0x78,0x7B,0xC3,0xDE,0x1E,0xF0,0xF7,0x87,0xBC,0x3D,0xE1,0xEF,0x0F,0x78,0x7B,0xE7,0xCF,0xFC,0x3F,0xC0,0xFC,0x00, // '0'
	0x01,0x07,0x9F,0xDF,0xEF,0xF6,0x78,0x3C,0x1E,0x0F,0x07,0x83,0xC1,0xE0,0xF0,0x78,0x3C,0x1E,0x0F,0x07,0x80, // '1'
	0x0F,0xC0,0xFF,0x83,0xFF,0x1F,0x3E,0x78,0x7B,0xE1,0xE0,0x0F,0x80,0x3C,0x01,0xF0,0x0F,0x80,0x7C,0x01,0xE0,0x0F,0x00,0x7C,0x03,0xE0,0x1F,0xFE,0x7F,0xF9,0xFF,0xE0, // '2'
	0x0F,0xC0,0xFF,0x87,0xFF,0x1E,0x3E,0x78,0x78,0x01,0xE0,0x0F,0x81,0xFC,0x07,0xC0,0x1F,0xC0,0x0F,0x80,0x1E,0x00,0x7B,0xE1,0xE7,0x8F,0x9F,0xFC,0x3F,0xE0,0x3F,0x00, // '3'
	0x01,0xF0,0x07,0xC0,0x3F,0x01,0xFC,0x07,0xF0,0x3F,0xC0,0xEF,0x07,0x3C,0x3C,0xF0,0xE3,0xC7,0x8F,0x1F,0xFE,0xFF,0xF9,0xFF,0xE0,0x0F,0x00,0x3C,0x00,0xF0,0x03,0xC0, // '4'
	0x7F,0xF3,0xFF,0x9F,0xFC,0xE0,0x07,0x00,0x38,0x03,0xDE,0x1F,0xFC,0xFF,0xE1,0x8F,0x80,0x3C,0x01,0xE0,0x0F,0x78,0x7B,0xE7,0xCF,0xFC,0x7F,0xC0,0xFC,0x00, // '5'
	0x03,0xC0,0x3F,0x01,0xFC,0x0F,0x80,0x78,0x01,0xE0,0x0F,0x7C,0x3F,0xF8,0xFF,0xF3,0xE7,0xCF,0x0F,0x3C,0x3E,0xF0,0xFB,0xC3,0xC7,0x9F,0x1F,0xF8,0x3F,0xE0,0x3E,0x00, // '6'
	0xFF,0xF7,0xFF,0xBF,0xFC,0x01,0xE0,0x1E,0x00,0xF0,0x07,0x80,0x78,0x03,0xC0,0x3C,0x01,0xE0,0x1F,0x00,0xF0,0x0F,0x80,0x78,0x03,0xC0,0x3C,0x03,0xE0,0x00, // '7'
	0x1F,0x83,0xFE,0x1F,0xF9,0xF3,0xEF,0x0F,0x78,0x79,0xE7,0x8F,0xFC,0x3F,0xC3,0xFF,0x3E,0x7D,0xE1,0xEF,0x0F,0x78,0x7B,0xE7,0xDF,0xFC,0x7F,0xE0,0xFC,0x00, // '8'
	0x0F,0x81,0xFE,0x1F,0xF8,0xF3,0xEF,0x0F,0x78,0x7B,0xC3,0xDE,0x1E,0xF8,0xF3,0xFF,0x9F,0xFC,0x3D,0xE0,0x0F,0x00,0xF0,0x0F,0x83,0xF8,0x1F,0x80,0xE0,0x00, // '9'
	0x73,0xEF,0x9C,0x00,0x00,0x00,0x00,0x07,0x3E,0xF9,0xC0, // ':'
	0x73,0xEF,0x9C,0x00,0x00,0x00,0x00,0x07,0x1C,0x71,0xC7,0x3C,0xE1,0x00, // ';'
	0x00,0x40,0x38,0x3F,0x1F,0xEF,0xF1,0xF0,0x3E,0x07,0xF8,0x3F,0xC1,0xF8,0x07,0x00,0x20, // '<'
	0xFF,0xEF,0xFE,0xFF,0xE0,0x00,0x00,0x0F,0xFE,0xFF,0xEF,0xFE, // '='
	0xC0,0x0F,0x00,0xFC,0x0F,0xF8,0x1F,0xE0,0x3E,0x07,0xE1,0xFE,0xFF,0x8F,0xE0,0xF0,0x0C,0x00, // '>'
	0x3F,0x07,0xFC,0xFF,0xEF,0x3E,0xF1,0xE0,0x1E,0x03,0xE0,0x7C,0x0F,0x80,0xF0,0x1E,0x01,0xE0,0x00,0x00,0x00,0x0E,0x01,0xE0,0x1E,0x00,0xE0, // '?'
	0x01,0xFC,0x00,0x1F,0xFC,0x00,0xFF,0xFC,0x07,0xC0,0xF8,0x3C,0x00,0xE1,0xE1,0xF1,0xC7,0x1F,0xE7,0x1C,0x7F,0x8C,0xE3,0xCE,0x33,0x8E,0x38,0xCE,0x70,0xE3,0x39,0xC3,0x0C,0xE7,0x0C,0x73,0x9E,0x71,0xCE,0x7F,0xFE,0x38,0xFF,0xF8,0xE1,0xE7,0x81,0xC0,0x00,0x07,0x80,0x00,0x0F,0x81,0x00,0x1F,0xFC,0x00,0x3F,0xF0,0x00,0x3F,0x80,0x00, // '@'
	0x03,0xE0,0x00,0xF8,0x00,0x3E,0x00,0x1F,0xC0,0x07,0xF0,0x03,0xDE,0x00,0xF7,0x80,0x3D,0xE0,0x1E,0x3C,0x07,0x8F,0x01,0xE3,0xC0,0xFF,0xF8,0x3F,0xFE,0x0F,0xFF,0x87,0x80,0xF1,0xE0,0x3C,0x78,0x0F,0xBE,0x03,0xE0, // 'A'
	0xFF,0xC1,0xFF,0xE3,0xFF,0xE7,0xC3,0xCF,0x87,0xDF,0x0F,0xBE,0x1E,0x7F,0xFC,0xFF,0xE1,0xFF,0xF3,0xE1,0xF7,0xC1,0xEF,0x83,0xDF,0x07,0xBE,0x1F,0x7F,0xFC,0xFF,0xF1,0xFF,0xC0, // 'B'
	0x0F,0xC0,0x1F,0xF0,0x7F,0xF8,0x78,0x7C,0xF8,0x3C,0xF0,0x3C,0xF0,0x02,0xF0,0x00,0xF0,0x00,0xF0,0x00,0xF0,0x00,0xF0,0x00,0xF0,0x3E,0xF8,0x3C,0x78,0x7C,0x7F,0xF8,0x3F,0xF0,0x0F,0xC0, // 'C'
	0xFF,0x81,0xFF,0xC3,0xFF,0xC7,0xC7,0xCF,0x87,0x9F,0x0F,0xBE,0x0F,0x7C,0x1E,0xF8,0x3D,0xF0,0x7B,0xE0,0xF7,0xC1,0xEF,0x87,0xDF,0x0F,0x3E,0x3E,0x7F,0xF8,0xFF,0xE1,0xFF,0x00, // 'D'
	0xFF,0xFB,0xFF,0xEF,0xFF,0xBE,0x00,0xF8,0x03,0xE0,0x0F,0x80,0x3F,0xF8,0xFF,0xE3,0xFF,0x8F,0x80,0x3E,0x00,0xF8,0x03,0xE0,0x0F,0x80,0x3F,0xFE,0xFF,0xFB,0xFF,0xE0, // 'E'
	0xFF,0xF7,0xFF,0xBF,0xFD,0xF0,0x0F,0x80,0x7C,0x03,0xE0,0x1F,0xFE,0xFF,0xF7,0xFF,0xBE,0x01,0xF0,0x0F,0x80,0x7C,0x03,0xE0,0x1F,0x00,0xF8,0x07,0xC0,0x00, // 'F'
	0x07,0xE0,0x1F,0xF8,0x3F,0xFC,0x7C,0x3C,0x78,0x3E,0xF8,0x1E,0xF0,0x00,0xF0,0x00,0xF0,0xFE,0xF0,0xFE,0xF0,0xFE,0xF0,0x1E,0xF8,0x1E,0x78,0x1E,0x7C,0x3E,0x3F,0xFE,0x1F,0xFC,0x07,0xE0, // 'G'
	0xF8,0x1E,0xF8,0x1E,0xF8,0x1E,0xF8,0x1E,0xF8,0x1E,0xF8,0x1E,0xF8,0x1E,0xFF,0xFE,0xFF,0xFE,0xFF,0xFE,0xF8,0x1E,0xF8,0x1E,0xF8,0x1E,0xF8,0x1E,0xF8,0x1E,0xF8,0x1E,0xF8,0x1E,0xF8,0x1E, // 'H'
	0xF7,0xBD,0xEF,0x7B,0xDE,0xF7,0xBD,0xEF,0x7B,0xDE,0xF7,0x80, // 'I'
	0x00,0xF8,0x03,0xE0,0x0F,0x80,0x3E,0x00,0xF8,0x03,0xE0,0x0F,0x80,0x3E,0x00,0xF8,0x03,0xE0,0x0F,0x80,0x3E,0x00,0xFB,0xE3,0xE7,0x8F,0x1F,0xFC,0x3F,0xE0,0x3E,0x00, // 'J'
	0xF8,0x3E,0xF8,0x7C,0xF8,0xF8,0xF8,0xF8,0xF9,0xF0,0xFB,0xE0,0xFB,0xC0,0xFF,0xC0,0xFF,0xC0,0xFF,0xC0,0xFF,0xE0,0xFD,0xE0,0xF9,0xF0,0xF8,0xF8,0xF8,0xF8,0xF8,0x7C,0xF8,0x7C,0xF8,0x3E, // 'K'
	0xF8,0x07,0xC0,0x3E,0x01,0xF0,0x0F,0x80,0x7C,0x03,0xE0,0x1F,0x00,0xF8,0x07,0xC0,0x3E,0x01,0xF0,0x0F,0x80,0x7C,0x03,0xE0,0x1F,0xFE,0xFF,0xF7,0xFF,0x80, // 'L'
	0xFC,0x03,0xF7,0xE0,0x3F,0xBF,0x81,0xFD,0xFC,0x0F,0xEF,0xE0,0xFF,0x7F,0x87,0xFB,0xDC,0x3B,0xDE,0xE1,0xDE,0xF7,0x9F,0xF7,0x9C,0xEF,0xBC,0xE7,0x7D,0xF7,0xFB,0xEF,0x9F,0x9F,0x7C,0xFC,0xFB,0xE7,0xE7,0xDF,0x1E,0x3E,0xF8,0xF1,0xF7,0xC7,0x8F,0x80, // 'M'
	0xF0,0x3E,0xF8,0x3E,0xF8,0x3E,0xFC,0x3E,0xFC,0x3E,0xFE,0x3E,0xFF,0x3E,0xFF,0x3E,0xF7,0xBE,0xF7,0xBE,0xF3,0xFE,0xF1,0xFE,0xF1,0xFE,0xF0,0xFE,0xF0,0xFE,0xF0,0x7E,0xF0,0x7E,0xF0,0x3E, // 'N'
	0x07,0xC0,0x1F,0xF0,0x3F,0xF8,0x7C,0x7C,0xF8,0x3C,0xF0,0x3E,0xF0,0x1E,0xF0,0x1E,0xF0,0x1E,0xF0,0x1E,0xF0,0x1E,0xF0,0x1E,0xF0,0x3E,0xF8,0x3C,0x7C,0x7C,0x3F,0xF8,0x1F,0xF0,0x07,0xC0, // 'O'
	0xFF,0xC1,0xFF,0xE3,0xFF,0xE7,0x83,0xEF,0x03,0xDE,0x07,0xBC,0x0F,0x78,0x1E,0xF0,0x7D,0xFF,0xF3,0xFF,0xC7,0xFE,0x0F,0x00,0x1E,0x00,0x3C,0x00,0x78,0x00,0xF0,0x01,0xE0,0x00, // 'P'
	0x07,0xC0,0x1F,0xF0,0x3F,0xF8,0x7C,0x7C,0x78,0x3C,0xF0,0x1E,0xF0,0x1E,0xF0,0x1E,0xF0,0x1E,0xF0,0x1E,0xF0,0x1E,0xF0,0x1E,0xF0,0x3E,0x78,0x3E,0x7C,0x7C,0x3F,0xF8,0x1F,0xF0,0x07,0xF8,0x00,0x7E,0x00,0x1C,0x00,0x08, // 'Q'
	0xFF,0xC0,0xFF,0xF0,0xFF,0xF8,0xF0,0x7C,0xF0,0x7C,0xF0,0x3C,0xF0,0x7C,0xF0,0x78,0xFF,0xF8,0xFF,0xF0,0xFF,0xE0,0xF1,0xF0,0xF1,0xF0,0xF0,0xF0,0xF0,0xF8,0xF0,0x78,0xF0,0x7C,0xF0,0x3E, // 'R'
	0x0F,0xC0,0x7F,0xE1,0xFF,0xE3,0xE3,0xEF,0x83,0xCF,0x00,0x1F,0x00,0x3F,0x80,0x3F,0xC0,0x1F,0xE0,0x0F,0xE0,0x03,0xEF,0x03,0xDE,0x07,0xBE,0x1F,0x3F,0xFC,0x3F,0xF0,0x1F,0xC0, // 'S'
	0xFF,0xFE,0xFF,0xFE,0xFF,0xFE,0x03,0xC0,0x03,0xC0,0x03,0xC0,0x03,0xC0,0x03,0xC0,0x03,0xC0,0x03,0xC0,0x03,0xC0,0x03,0xC0,0x03,0xC0,0x03,0xC0,0x03,0xC0,0x03,0xC0,0x03,0xC0,0x03,0xC0, // 'T'
	0xF8,0x3D,0xF0,0x7B,0xE0,0xF7,0xC1,0xEF,0x83,0xDF,0x07,0xBE,0x0F,0x7C,0x1E,0xF8,0x3D,0xF0,0x7B,0xE0,0xF7,0xC1,0xE7,0x83,0xCF,0x07,0x9F,0x1F,0x1F,0xFC,0x1F,0xF0,0x1F,0xC0, // 'U'
	0xF8,0x0F,0x9E,0x03,0xC7,0xC1,0xF1,0xF0,0x7C,0x3C,0x1E,0x0F,0x07,0x83,0xE3,0xE0,0x78,0xF0,0x1E,0x3C,0x07,0xDF,0x00,0xF7,0x80,0x3D,0xE0,0x0F,0x78,0x01,0xFC,0x00,0x7F,0x00,0x1F,0xC0,0x03,0xE0,0x00,0xF8,0x00, // 'V'
	0xF8,0x78,0x7C,0xF0,0xF0,0xF1,0xE1,0xE1,0xE3,0xC7,0xE3,0xC7,0x8F,0xCF,0x87,0x9F,0x9E,0x0F,0x3F,0x3C,0x1E,0x7E,0x78,0x3D,0xFE,0xF0,0x7B,0xFD,0xE0,0x7F,0x3F,0x80,0xFE,0x7F,0x01,0xFC,0xFE,0x03,0xF9,0xFC,0x07,0xE1,0xF8,0x07,0xC3,0xE0,0x0F,0x87,0xC0,0x1F,0x0F,0x80, // 'W'
	0xF8,0x1F,0x3E,0x1F,0x0F,0x0F,0x07,0xCF,0x81,0xE7,0x80,0xFF,0xC0,0x3F,0xC0,0x1F,0xE0,0x07,0xE0,0x03,0xF0,0x03,0xFC,0x01,0xFE,0x01,0xFF,0x80,0xF3,0xC0,0xF9,0xF0,0xF8,0x7C,0x7C,0x3E,0x7C,0x0F,0x80, // 'X'
	0xF8,0x1F,0x3C,0x1F,0x1F,0x0F,0x87,0x87,0x83,0xC7,0xC0,0xF3,0xC0,0x7B,0xE0,0x1F,0xE0,0x0F,0xF0,0x03,0xF0,0x01,0xF8,0x00,0x78,0x00,0x3C,0x00,0x1E,0x00,0x0F,0x00,0x07,0x80,0x03,0xC0,0x01,0xE0,0x00, // 'Y'
	0xFF,0xFD,0xFF,0xFB,0xFF,0xE0,0x07,0xC0,0x1F,0x00,0x3C,0x00,0xF8,0x03,0xE0,0x07,0x80,0x1F,0x00,0x7C,0x00,0xF0,0x03,0xE0,0x0F,0x80,0x1E,0x00,0x7F,0xFE,0xFF,0xFD,0xFF,0xF8, // 'Z'
	0xFD,0xFB,0xF7,0x8F,0x1E,0x3C,0x78,0xF1,0xE3,0xC7,0x8F,0x1E,0x3C,0x78,0xF1,0xE3,0xC7,0x8F,0x1E,0x3F,0x7E,0xFC, // '['
	0xF0,0x0F,0x80,0x78,0x07,0x80,0x7C,0x03,0xC0,0x3C,0x01,0xE0,0x1E,0x01,0xF0,0x0F,0x00,0xF0,0x0F,0x80,0x78,0x07,0x80,0x7C,0x03,0xC0,0x3E,0x01,0xE0,0x1E, // '\'
	0xFD,0xFB,0xF1,0xE3,0xC7,0x8F,0x1E,0x3C,0x78,0xF1,0xE3,0xC7,0x8F,0x1E,0x3C,0x78,0xF1,0xE3,0xC7,0xBF,0x7E,0xFC, // ']'
	0x0E,0x01,0xF0,0x1F,0x01,0xB0,0x3B,0x83,0xB8,0x71,0xC7,0x1C,0xF1,0xE0, // '^'
	0xFF,0xEF,0xFE,0xFF,0xE0, // '_'
	0xF0,0xF0,0xF0,0xE0, // '`'
	0x1F,0x03,0xFE,0x3F,0xF9,0xE3,0xC0,0x1E,0x1F,0xF1,0xFF,0x9F,0xFC,0xF1,0xE7,0x8F,0x3F,0xF9,0xFF,0xC3,0xDF,0x00, // 'a'
	0xF0,0x07,0x80,0x3C,0x01,0xE0,0x0F,0x00,0x78,0x03,0xDF,0x1F,0xFC,0xFF,0xF7,0xCF,0xBC,0x3D,0xE1,0xEF,0x0F,0x78,0x7B,0xC3,0xDF,0x1E,0xFF,0xF7,0xFF,0x3D,0xF0, // 'b'
	0x1F,0x07,0xFC,0x7F,0xEF,0x1E,0xF1,0xEF,0x00,0xF0,0x0F,0x00,0xF0,0xEF,0x1E,0x7F,0xE7,0xFC,0x1F,0x00, // 'c'
	0x00,0xF0,0x07,0x80,0x3C,0x01,0xE0,0x0F,0x00,0x78,0xFB,0xCF,0xFE,0xFF,0xF7,0xCF,0xBC,0x3D,0xE1,0xEF,0x0F,0x78,0x7B,0xC3,0xDE,0x3E,0xFF,0xF3,0xFF,0x8F,0xBC, // 'd'
	0x1F,0x81,0xFE,0x1F,0xF9,0xF1,0xEF,0x0F,0x7F,0xFB,0xFF,0xDF,0xFE,0xF0,0x07,0xC2,0x1F,0xF8,0x7F,0xE0,0xF8,0x00, // 'e'
	0x07,0x87,0xE3,0xF8,0xF8,0x3C,0x0F,0x0F,0xFB,0xFE,0xFF,0x8F,0x03,0xC0,0xF0,0x3C,0x0F,0x03,0xC0,0xF0,0x3C,0x0F,0x03,0xC0, // 'f'
	0x0F,0x78,0xFF,0xE7,0xFF,0x9F,0x1E,0x78,0x79,0xE1,0xEF,0x87,0x9E,0x1E,0x78,0x79,0xF1,0xE7,0xFF,0x8F,0xFE,0x0F,0x78,0x01,0xE3,0x0F,0x8F,0xFC,0x7F,0xE0,0x3E,0x00, // 'g'
	0xF0,0x07,0x80,0x3C,0x01,0xE0,0x0F,0x00,0x78,0x03,0xDF,0x1F,0xFC,0xFF,0xF7,0x8F,0xBC,0x3D,0xE1,0xEF,0x0F,0x78,0x7B,0xC3,0xDE,0x1E,0xF0,0xF7,0x87,0xBC,0x3C, // 'h'
	0x73,0xEF,0x9C,0x03,0xEF,0xBE,0xFB,0xEF,0xBE,0xFB,0xEF,0xBE,0xFB,0xE0, // 'i'
	0x1C,0x3E,0x3E,0x1C,0x00,0x1E,0x1E,0x1E,0x1E,0x1E,0x1E,0x1E,0x1E,0x1E,0x1E,0x1E,0x1E,0x1E,0x1E,0x3E,0xFC,0xFC,0xF0, // 'j'
	0xF0,0x03,0xC0,0x0F,0x00,0x3C,0x00,0xF0,0x03,0xC0,0x0F,0x1F,0xBC,0x78,0xF3,0xE3,0xDF,0x0F,0xF8,0x3F,0xC0,0xFF,0x83,0xFF,0x0F,0xBC,0x3C,0xF8,0xF1,0xE3,0xC7,0xCF,0x0F,0x80, // 'k'
	0xFB,0xEF,0xBE,0xFB,0xEF,0xBE,0xFB,0xEF,0xBE,0xFB,0xEF,0xBE,0xFB,0xEF,0x80, // 'l'
	0xF3,0xC7,0xC7,0xBF,0x7F,0x3F,0xFF,0xF9,0xF1,0xF3,0xCF,0x8F,0x1F,0x7C,0x78,0xFB,0xE3,0xC7,0xDF,0x1E,0x3E,0xF8,0xF1,0xF7,0xC7,0x8F,0xBE,0x3C,0x7D,0xF1,0xE3,0xEF,0x8F,0x1F,0x00, // 'm'
	0xF7,0xC7,0xFF,0x3F,0xFD,0xF3,0xEF,0x0F,0x78,0x7B,0xC3,0xDE,0x1E,0xF0,0xF7,0x87,0xBC,0x3D,0xE1,0xEF,0x0F,0x00, // 'n'
	0x1F,0x81,0xFE,0x1F,0xF9,0xF3,0xEF,0x0F,0x78,0x7B,0xC3,0xDE,0x1E,0xF0,0xF7,0xCF,0x9F,0xF8,0x7F,0x81,0xF8,0x00, // 'o'
	0xF7,0xC7,0xFF,0x3F,0xFD,0xF3,0xEF,0x0F,0x78,0x7B,0xC3,0xDE,0x1E,0xF0,0xF7,0xCF,0xBF,0xFD,0xFF,0xCF,0x7C,0x78,0x03,0xC0,0x1E,0x00,0xF0,0x07,0x80,0x00, // 'p'
	0x3E,0xF3,0xFF,0xBF,0xFD,0xF3,0xEF,0x0F,0x78,0x7B,0xC3,0xDE,0x1E,0xF0,0xF7,0x8F,0xBF,0xFC,0xFF,0xE3,0xEF,0x00,0x78,0x03,0xC0,0x1E,0x00,0xF0,0x07,0x80, // 'q'
	0xF7,0x7F,0xBF,0xDF,0xEF,0x87,0x83,0xC1,0xE0,0xF0,0x78,0x3C,0x1E,0x0F,0x00, // 'r'
	0x1F,0x07,0xFC,0xFF,0xEF,0x1E,0xF1,0xEF,0xE0,0x7F,0xC1,0xFE,0xE1,0xEF,0x1E,0xFF,0xE7,0xFC,0x1F,0x00, // 's'
	0x3C,0x1E,0x0F,0x1F,0xEF,0xF7,0xF8,0xF0,0x78,0x3C,0x1E,0x0F,0x07,0x83,0xC1,0xF8,0x7C,0x1E, // 't'
	0xF0,0xF7,0x87,0xBC,0x3D,0xE1,0xEF,0x0F,0x78,0x7B,0xC3,0xDE,0x1E,0xF0,0xF7,0x8F,0xBF,0xFC,0xFF,0xE3,0xEF,0x00, // 'u'
	0xF8,0xF9,0xE3,0xC7,0x8F,0x1E,0x3C,0x3D,0xE0,0xF7,0x83,0xDE,0x07,0x70,0x1F,0xC0,0x7F,0x00,0xF8,0x03,0xE0,0x0F,0x80, // 'v'
	0xF1,0xE3,0xCE,0x3C,0x71,0xE7,0x9E,0x3C,0xF3,0xC7,0xBF,0x78,0xF7,0xEE,0x0E,0xFD,0xC1,0xD9,0xB8,0x3F,0x3F,0x07,0xE7,0xC0,0x7C,0xF8,0x0F,0x0F,0x01,0xE1,0xE0, // 'w'
	0xF8,0xF9,0xE3,0xC3,0xDE,0x0F,0x78,0x1F,0xC0,0x7F,0x00,0xF8,0x07,0xF0,0x1F,0xC0,0xF7,0x83,0xDE,0x1E,0x3C,0xF8,0xF8, // 'x'
	0xF8,0xFB,0xE3,0xE7,0x8F,0x1E,0x3C,0x3D,0xE0,0xF7,0x83,0xDE,0x07,0xF0,0x1F,0xC0,0x7F,0x00,0xF8,0x03,0xE0,0x0F,0x80,0x3C,0x00,0xF0,0x0F,0x80,0x3E,0x00,0xF0,0x00, // 'y'
	0xFF,0xEF,0xFE,0xFF,0xE0,0x7C,0x07,0x80,0xF0,0x1F,0x03,0xE0,0x3C,0x07,0x80,0xFF,0xEF,0xFE,0xFF,0xE0, // 'z'
	0x02,0x07,0x07,0xC3,0x81,0xC1,0xE0,0xF0,0x78,0x3C,0x1E,0x0F,0x1F,0x0F,0x07,0xC0,0xF0,0x78,0x3C,0x1E,0x0F,0x07,0x81,0xC0,0xF0,0x3C,0x0C, // '{'
	0xDB,0x6D,0xB6,0xDB,0x6D,0xB6,0xDB,0x6C, // '|'
	0x40,0x38,0x3E,0x07,0x03,0x81,0xE0,0xF0,0x78,0x3C,0x1E,0x0F,0x03,0xE0,0xF0,0xF8,0xF0,0x78,0x3C,0x1E,0x0F,0x07,0x83,0x83,0xC3,0xC0,0xC0 // '}'
};
const GFXglyph Roboto_Black_25Glyphs[] PROGMEM = {
// bitmapOffset, width, height, xAdvance, xOffset, yOffset
	  {     0,   1,   1,   7,    0,    0 }, // ' '
	  {     1,   6,  18,   8,    1,  -18 }, // '!'
	  {    15,   8,   7,   9,    0,  -19 }, // '"'
	  {    22,  14,  18,  16,    1,  -18 }, // '#'
	  {    54,  13,  23,  15,    1,  -21 }, // '$'
	  {    92,  17,  18,  20,    1,  -18 }, // '%'
	  {   131,  16,  18,  18,    1,  -18 }, // '&'
	  {   167,   4,   7,   5,    1,  -19 }, // '''
	  {   171,   7,  26,  10,    2,  -20 }, // '('
	  {   194,   8,  26,  10,    1,  -20 }, // ')'
	  {   220,  13,  11,  13,    -1,  -18 }, // '*'
	  {   238,  13,  13,  14,    1,  -15 }, // '+'
	  {   260,   5,   8,   8,    1,   -4 }, // ','
	  {   265,   8,   3,  12,    2,   -9 }, // '-'
	  {   268,   6,   4,   9,    1,   -4 }, // '.'
	  {   271,  10,  20,  10,    0,  -18 }, // '/'
	  {   296,  13,  18,  15,    1,  -18 }, // '0'
	  {   326,   9,  18,  15,    2,  -18 }, // '1'
	  {   347,  14,  18,  15,    0,  -18 }, // '2'
	  {   379,  14,  18,  15,    0,  -18 }, // '3'
	  {   411,  14,  18,  15,    0,  -18 }, // '4'
	  {   443,  13,  18,  15,    1,  -18 }, // '5'
	  {   473,  14,  18,  15,    1,  -18 }, // '6'
	  {   505,  13,  18,  15,    1,  -18 }, // '7'
	  {   535,  13,  18,  15,    1,  -18 }, // '8'
	  {   565,  13,  18,  15,    1,  -18 }, // '9'
	  {   595,   6,  14,   9,    1,  -14 }, // ':'
	  {   606,   6,  18,   8,    1,  -14 }, // ';'
	  {   620,  11,  12,  14,    1,  -13 }, // '<'
	  {   637,  12,   8,  16,    2,  -12 }, // '='
	  {   649,  12,  12,  14,    1,  -13 }, // '>'
	  {   667,  12,  18,  14,    1,  -18 }, // '?'
	  {   694,  22,  23,  23,    1,  -17 }, // '@'
	  {   758,  18,  18,  18,    0,  -18 }, // 'A'
	  {   799,  15,  18,  17,    1,  -18 }, // 'B'
	  {   833,  16,  18,  17,    1,  -18 }, // 'C'
	  {   869,  15,  18,  17,    1,  -18 }, // 'D'
	  {   903,  14,  18,  15,    1,  -18 }, // 'E'
	  {   935,  13,  18,  15,    1,  -18 }, // 'F'
	  {   965,  16,  18,  18,    1,  -18 }, // 'G'
	  {  1001,  16,  18,  19,    1,  -18 }, // 'H'
	  {  1037,   5,  18,   9,    2,  -18 }, // 'I'
	  {  1049,  14,  18,  15,    0,  -18 }, // 'J'
	  {  1081,  16,  18,  17,    1,  -18 }, // 'K'
	  {  1117,  13,  18,  15,    1,  -18 }, // 'L'
	  {  1147,  21,  18,  23,    1,  -18 }, // 'M'
	  {  1195,  16,  18,  19,    2,  -18 }, // 'N'
	  {  1231,  16,  18,  18,    1,  -18 }, // 'O'
	  {  1267,  15,  18,  17,    1,  -18 }, // 'P'
	  {  1301,  16,  21,  18,    1,  -18 }, // 'Q'
	  {  1343,  16,  18,  17,    1,  -18 }, // 'R'
	  {  1379,  15,  18,  17,    1,  -18 }, // 'S'
	  {  1413,  16,  18,  17,    0,  -18 }, // 'T'
	  {  1449,  15,  18,  18,    1,  -18 }, // 'U'
	  {  1483,  18,  18,  18,    0,  -18 }, // 'V'
	  {  1524,  23,  18,  23,    0,  -18 }, // 'W'
	  {  1576,  17,  18,  17,    0,  -18 }, // 'X'
	  {  1615,  17,  18,  17,    0,  -18 }, // 'Y'
	  {  1654,  15,  18,  16,    1,  -18 }, // 'Z'
	  {  1688,   7,  25,   8,    1,  -21 }, // '['
	  {  1710,  12,  20,  12,    0,  -18 }, // '\'
	  {  1740,   7,  25,   8,    0,  -21 }, // ']'
	  {  1762,  12,   9,  12,    0,  -18 }, // '^'
	  {  1776,  12,   3,  12,    0,    0 }, // '_'
	  {  1781,   7,   4,   9,    1,  -19 }, // '`'
	  {  1785,  13,  13,  14,    1,  -13 }, // 'a'
	  {  1807,  13,  19,  15,    1,  -19 }, // 'b'
	  {  1838,  12,  13,  14,    1,  -13 }, // 'c'
	  {  1858,  13,  19,  15,    1,  -19 }, // 'd'
	  {  1889,  13,  13,  15,    1,  -13 }, // 'e'
	  {  1911,  10,  19,  10,    0,  -19 }, // 'f'
	  {  1935,  14,  18,  15,    0,  -13 }, // 'g'
	  {  1967,  13,  19,  15,    1,  -19 }, // 'h'
	  {  1998,   6,  18,   8,    1,  -18 }, // 'i'
	  {  2012,   8,  23,   8,   -1,  -18 }, // 'j'
	  {  2035,  14,  19,  15,    1,  -19 }, // 'k'
	  {  2069,   6,  19,   8,    1,  -19 }, // 'l'
	  {  2084,  21,  13,  23,    1,  -13 }, // 'm'
	  {  2119,  13,  13,  15,    1,  -13 }, // 'n'
	  {  2141,  13,  13,  15,    1,  -13 }, // 'o'
	  {  2163,  13,  18,  15,    1,  -13 }, // 'p'
	  {  2193,  13,  18,  15,    1,  -13 }, // 'q'
	  {  2223,   9,  13,  10,    1,  -13 }, // 'r'
	  {  2238,  12,  13,  14,    1,  -13 }, // 's'
	  {  2258,   9,  16,  10,    0,  -16 }, // 't'
	  {  2276,  13,  13,  15,    1,  -13 }, // 'u'
	  {  2298,  14,  13,  14,    0,  -13 }, // 'v'
	  {  2321,  19,  13,  19,    0,  -13 }, // 'w'
	  {  2352,  14,  13,  14,    0,  -13 }, // 'x'
	  {  2375,  14,  18,  14,    0,  -13 }, // 'y'
	  {  2407,  12,  13,  14,    1,  -13 }, // 'z'
	  {  2427,   9,  24,   9,    0,  -20 }, // '{'
	  {  2454,   3,  21,   7,    2,  -18 }, // '|'
	  {  2462,   9,  24,   9,    0,  -20 } // '}'
};
const GFXfont Roboto_Black_25 PROGMEM = {
(uint8_t  *)Roboto_Black_25Bitmaps,(GFXglyph *)Roboto_Black_25Glyphs,0x20, 0x7E, 31};