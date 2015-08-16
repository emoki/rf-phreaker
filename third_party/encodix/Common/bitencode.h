/*******************************************************************************
  bitencode.h  Developed by Dafocus - http://www.dafocus.com/
*******************************************************************************/
#ifndef __BITENCODE_H
#define __BITENCODE_H
#include "ed_dump.h"

#ifdef __cplusplus
extern "C" {
#endif
#define BE_ERROR_LEN  (-1)

/*------------------------------------------------------------------------------
	Encodes a text string written with the syntax described below.
	It returns a pointer to a static buffer encoded as described; it writes into
	"len" the number of bits used in returned buffer.
	
	SYNTAX DESCRIPTION

	One-char terminals:
		<EOF>    is the end of the input string.    
		<SEP>    is a separator: space, tab, hypen (-), comma (,), CR, LF or <EOF>.
		<DEC>    is a caracter in the following range: [0-9]
		<HEX>    is a caracter in the following range: [0-9A-Fa-f]
		<BIN>    is a caracter in the following range: [0-1]

	Comments can be inserted inside the string betweed '<' and '>'

	Productions:
		string ::= (dec|bin|hex|chk)*  -- Root production.
		dec ::= 'd'rep<DEC>+<SEP>  -- insert into curr pos rep-bit decimal number
		hex ::= 'x'rep<HEX>+<SEP>  -- insert into curr pos rep-bit hex number
		bin ::= <BIN>{n}<SEP>      -- insert into curr pos rep-bit binary value
		rep ::= ['{'<DEC>+'}']     -- tells num of bits to use; defaults to 8
		chk ::= '|'                -- checks that symbol is between octets

	Example:
		"x02 x{4}3 d{4}15 101 d{5}20"

	In case of error, "len" is set to BE_ERROR_LEN and it returns a string
	explaining the error.
------------------------------------------------------------------------------*/
extern const char* BitEncode (const char* sourceString, int* len);

/*------------------------------------------------------------------------------
	It dumps on a TEDOStream the BinaryBuffer in a human readable form.
	Useful for debugging.
------------------------------------------------------------------------------*/
extern void BinaryDump (TEDOStream* OStream, const char* Description, const char* BinaryBuffer, int LengthInBits);

#ifdef __cplusplus
}
#endif
#endif
