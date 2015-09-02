#include "bitencode.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "ed_lib.h"


const char* Digits = "0123456789ABCDEF";

/*------------------------------------------------------------------------------
	Returns true if given character is a separator
------------------------------------------------------------------------------*/
#define ISSEP(a) ((a)=='\0' || (a)=='\r' || (a)=='\n' || (a)==' ' || (a)=='\t' || (a)=='-' || (a)==',')
#define SEP ' '

/*------------------------------------------------------------------------------
	Prints a syntax error and aborts
------------------------------------------------------------------------------*/
const char* BitEncodeError (const char* string, int errorPosition, const char* description, int* LengthInBits)
{
	static char Buffer [8192];
	int i;
	
	memset (Buffer, 0, sizeof (Buffer));
	Buffer [0] = '\0';
	sprintf (Buffer+strlen (Buffer), "Syntax error at character %d parsing binary string.\n", errorPosition+1);
	sprintf (Buffer+strlen (Buffer), "Description: %s\n", description);
	sprintf (Buffer+strlen (Buffer), "String: ");
	i=errorPosition-10;
	if (i<0) i=0;
	for (; string [i]!='\0' && i < errorPosition+4; i++) {
		if (strlen (string) > sizeof (Buffer)-80) {
			strcat (Buffer, "...");
			break;
		}
		if (i==errorPosition) sprintf (Buffer+strlen (Buffer), "-->[%c]<--", string[i]);
		else sprintf (Buffer+strlen (Buffer), "%c", string[i]);
	}
	if (i==errorPosition) sprintf (Buffer+strlen (Buffer), "-->EOF<--");
	sprintf (Buffer+strlen (Buffer), "\n");

	(*LengthInBits) = -1;
	return Buffer;
}

/*------------------------------------------------------------------------------
	Given a buffer and a pointer inside it, it reads a numeric value written
	in requested base and returns it in decimal form.
	Returned value is always >= 0; if <0, an error occurred.
	"currPos" will be pointing first non-read character.
	It does not read more than "maxLengthInBits" characters and less than "minLengthInBits".
	"LengthInBits" is set to BE_ERROR_LEN and errText to the error text in case of error.
------------------------------------------------------------------------------*/
int ParseNumber (const char* string, int* currPos, int base, int minLengthInBits, int maxLengthInBits, int* LengthInBits, const char** errText)
{
	char buffer [20];
	int i, j;
	char c, *p;
	for (i=0; i<(int)sizeof (buffer)-1 && i<(int)maxLengthInBits; i++) {
		if (ISSEP (string [i+*currPos])) break;
		c = (char)toupper (string [i+*currPos]);
		for (j=0; j<base; j++) if (Digits [j] == c) break;
		if (j < base) {
			buffer [i] = c;
		}
		else break;
	}
	buffer [i] = '\0';
	if (i<minLengthInBits) {
		(*errText) = BitEncodeError (string, i+*currPos, "unexpected character while reading number", LengthInBits);
		return 0;
	}
	(*currPos) += i;
	return (int)strtoul (buffer, &p, base);
}

/*------------------------------------------------------------------------------
	Encodes a text string written with the syntax described below.
	It returns a pointer to a static buffer encoded as described; it writes into
	"LengthInBits" the number of bits used in returned buffer.
------------------------------------------------------------------------------*/
const char* BitEncode (const char* string, int* LengthInBits)
{
	static char buffer [8192];
	int state = 0;
	int i, base=0, bits=0, value, stringLengthInBits;
	const char* errText = "";

	if (string == NULL) {(*LengthInBits)=0; return "";}
	(*LengthInBits) = 0;
	stringLengthInBits = (int)(strlen (string));

	memset (buffer, 0, sizeof (buffer));

	for (i=0; i < stringLengthInBits; i++) {
		char curr = string [i];
		if (curr == '<') {
			while (curr != '>') {
				i++;
				curr = string [i];
				if (curr == '\0') {
					return BitEncodeError (string, i-1, "string terminated inside a comment", LengthInBits);
				}
			}
		}
		else {
			if (ISSEP(curr)) curr = SEP;
			switch (state) {
				/* Normal operation: recognise begin of non terminals */
				case 0: {
					switch (curr) {
						case SEP: break; /* Skip separators */
						case '$': state = 4; break;
						case '1':
						case '0': {
							EDIntToBits (buffer, *LengthInBits, (curr=='1'?1:0), 1);
							(*LengthInBits)++;
							break;
						}
						case '?': {
							printf ("USED BITS: %u\n", (unsigned)(*LengthInBits));
							break;
						}
						case '|': {
							int ofs=((*LengthInBits) & 7);
							if (ofs != 0) {
								static char Buffer [120];
								sprintf (Buffer, "alignment check failed: it's between bit %d and bit %d", 9-ofs, 8-ofs);
								return BitEncodeError (string, i, Buffer, LengthInBits);
							}
							break;
						}
						case 'd': base=10; state=1; break;
						case 'x': base=16; state=1; break;
						default: return BitEncodeError (string, i, "expected separator, 'd', 'x', '1' or '0'", LengthInBits);
					}
					break;
				}
				/* Recognised x or d: needs to read '{' */
				case 1: {
					if (curr == '{') state = 2;
					else {i--; state=3; bits=8;}
					break;
				}
				/* Read content of '{' */
				case 2: {
					bits = ParseNumber (string, &i, 10, 1, 6, LengthInBits, &errText);
					if ((*LengthInBits) == BE_ERROR_LEN) return errText;
					if (string [i] != '}') return BitEncodeError (string, i, "expected '}'", LengthInBits);
					state = 3;
					break;
				}
				/* Read numeric value */
				case 3: {
					value = ParseNumber (string, &i, base, 1, 10, LengthInBits, &errText);
					if ((*LengthInBits) == BE_ERROR_LEN) return errText;
					EDIntToBits (buffer, *LengthInBits, value, bits);
					(*LengthInBits)+= bits;
					state = 0;
					break;
				}
				/* Read hex string */
				case 4: {
					if (curr == '$') {
						state = 0;
						break;
					}
					if (curr == SEP) break;
					value = ParseNumber (string, &i, 16, 1, 1, LengthInBits, &errText);
					if ((*LengthInBits) == BE_ERROR_LEN) return errText;
					i--;
					EDIntToBits (buffer, *LengthInBits, value, 4);
					(*LengthInBits)+=4;
					break;
				}
			}
		}
	}
	return buffer;
}

/*------------------------------------------------------------------------------
	It dumps on a TEDOStream the BinaryBuffer in a human readable form.
	Useful for debugging.
------------------------------------------------------------------------------*/
extern void BinaryDump (TEDOStream* OStream, const char* Description, const char* BinaryBuffer, int LengthInBits)
{
	char Buffer [512];
	int i, j;
	OStream->WriteString (OStream, "/*---------------------------------------------\n");
	sprintf (Buffer, "  %s LengthInBits=%d\n", Description, LengthInBits);
	OStream->WriteString (OStream, Buffer);
	OStream->WriteString (OStream, "---------------------------------------------*/\n");

	for (i=0; LengthInBits>0; i++) {
		sprintf (Buffer, "/* 0x%08X: */ '\\x%02X'%c /* (%03d) - ", (unsigned int)i, (unsigned int)((unsigned char)(BinaryBuffer[i])), (LengthInBits>7?',':' '), (unsigned int)((unsigned char)(BinaryBuffer[i])));

		for (j=0; j<8; j++) {
			if (LengthInBits == 0) break;
			if (BinaryBuffer[i] & (1 << (7-j))) strcat (Buffer, "1");
			else strcat (Buffer, "0");
			LengthInBits --;
		}
		strcat (Buffer, "*/\n");
		OStream->WriteString (OStream, Buffer);
	}
	OStream->WriteString (OStream, "/*-------------------------------------------*/\n");
}
