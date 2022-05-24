#pragma once

#include <iterator>

#include "myTerm.h"

inline const unsigned int bigchars[19][2] = {
    {3'890'741'118, 2'130'700'263}, // 0
    {943'602'744, 943'208'504},     // 1
    {1'894'252'414, 4'294'903'580}, // 2
    {2'145'451'903, 2'147'475'680}, // 3
    {4'286'019'447, 1'886'417'151}, // 4
    {2'131'230'719, 2'130'698'495}, // 5
    {2'131'230'590, 2'130'700'287}, // 6
    {1'893'793'791, 471'604'280},   // 7
    {2'129'133'438, 2'129'127'399}, // 8
    {4'293'394'302, 2'130'698'494}, // 9
    {3'890'741'118, 3'890'741'247}, // A
    {2'145'910'655, 2'145'904'615}, // B
    {1'32'644'734, 2'130'700'039},  // C
    {3'890'741'119, 2'147'477'479}, // D
    {1'057'488'895, 4'294'903'615}, // E
    {1'057'488'895, 117'901'119},   // F
    {2'115'508'224, 1'579'134},     // +
    {2'113'929'216, 126},           // -
    {507'410'150, 3'866'508'830}    // K
};

enum BIGCHAR {
  ZERO,
  ONE,
  TWO,
  THREE,
  FOUR,
  FIVE,
  SIX,
  SEVEN,
  EIGHT,
  NINE,
  A,
  B,
  C,
  D,
  E,
  F,
  PLUS,
  MINUS,
  K,
};

int bc_printA(char *str); // Out a string with simbols from extra code table
int bc_box(int x1, int y1, int x2, int y2); // psevdo ramka
int bc_printbigchar(BIGCHAR chindex, int x, int y, COLORS color,
                    COLORS color1);                       // vivod big simbol
int bc_setbigcharpos(int *big, int x, int y, int value);  // zna4 big simbol
int bc_getbigcharpos(int *big, int x, int y, int *value); // get pos value
int bc_bigcharwrite(int fd, int *big, int count); // zapis big simbol in file
int bc_bigcharread(int fd, int *big, int need_count,
                   int *count); // read big char from file
