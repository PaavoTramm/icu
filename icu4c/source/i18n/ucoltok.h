#ifndef UCOL_TOKENS_H
#define UCOL_TOKENS_H

#include "ucolimp.h"

#define UCOL_TOK_POLARITY_NEGATIVE 0
#define UCOL_TOK_POLARITY_POSITIVE 1

typedef struct UColToken UColToken;

typedef struct  {
  UColToken* first[2];
  UColToken* last[2];
/*
  UColToken* firstPositive;
  UColToken* lastPositive;
  UColToken* firstNegative;
  UColToken* lastNegative;
*/
  UColToken* reset;
  uint32_t baseCE;
  uint32_t baseContCE;
  uint32_t nextCE;
  uint32_t nextContCE;
  uint32_t previousCE;
  uint32_t previousContCE;
/*  uint32_t strongest[2];*/
  int32_t pos[UCOL_STRENGTH_LIMIT];
  uint32_t gapsLo[3*UCOL_CE_STRENGTH_LIMIT];
  uint32_t gapsHi[3*UCOL_CE_STRENGTH_LIMIT];
  uint32_t numStr[UCOL_CE_STRENGTH_LIMIT];
  UColToken* fStrToken[UCOL_CE_STRENGTH_LIMIT];
  UColToken* lStrToken[UCOL_CE_STRENGTH_LIMIT];

/*
  UColAttributeValue strongestP;
  UColAttributeValue strongestN;
*/
} UColTokListHeader;

struct UColToken {
  UChar debugSource;
  UChar debugExpansion;
  uint32_t CEs[128];
  uint32_t noOfCEs;
  uint32_t expCEs[128];
  uint32_t noOfExpCEs;
  uint32_t source;
  uint32_t expansion;
  uint32_t strength;
  uint32_t toInsert;
  uint32_t polarity; /* 1 for <, <<, <<<, , ; and -1 for >, >>, >>> */
  UColTokListHeader *listHeader;
  UColToken* previous;
  UColToken* next;
};

typedef struct {
  const UChar *source;
  const UChar *end;
  const UChar *current;
  const InverseTableHeader *invUCA;
  const UCollator *UCA;
  UCATableHeader *image;
  uint32_t resultLen;
  UColTokListHeader *lh;
} UColTokenParser;


#define ucol_tok_isSpecialChar(ch)              \
    (((((ch) <= 0x002F) && ((ch) >= 0x0020)) || \
      (((ch) <= 0x003F) && ((ch) >= 0x003A)) || \
      (((ch) <= 0x0060) && ((ch) >= 0x005B)) || \
      (((ch) <= 0x007E) && ((ch) >= 0x007B))))


U_CFUNC UColToken *ucol_tok_parse_next_token(UColTokenParser *src, UErrorCode *status);
U_CFUNC uint32_t ucol_tok_assembleTokenList(UColTokenParser *src, UErrorCode *status);

int32_t uhash_hashTokens(const void *k);
UBool uhash_compareTokens(const void *key1, const void *key2);
void ucol_tok_initTokenList(UColTokenParser *src, UErrorCode *status);
void ucol_tok_closeTokenList(void);
uint32_t ucol_uprv_tok_assembleTokenList(UColTokenParser *src, UErrorCode *status);

#endif



