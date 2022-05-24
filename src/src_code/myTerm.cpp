#include "../src_headers/myTerm.h"
//
using namespace std;

int mt_getscreensize(int *rows, int *cols) {
  struct winsize size;
  if (!ioctl(1, TIOCGWINSZ, &size)) {
    *rows = size.ws_row;
    *cols = size.ws_col;
    return 0;
  }
  return -1;
}

int mt_gotoxy(int x, int y) {
  int r = 0, c = 0;
  mt_getscreensize(&r, &c);
  if (x >= 0 && x <= r && y >= 0 && y < c) {
    cout << "\E[" << x << ";" << y << "H";
    return 0;
  }
  return -1;
}

int mt_clrscr() {
  cout << "\E[H\E[J";
  mt_gotoxy(1, 1);
  return 0;
}

int mt_setfgcolor(COLORS color) {
  if (color >= BLACK && color <= GREEN) {
    cout << "\E[3" << color << "m";
    return 0;
  }
  return -1;
}

int mt_setbgcolor(COLORS color) {
  if (color >= BLACK && color <= GREEN) {
    cout << "\E[4" << color << "m";
    return 0;
  }
  return -1;
}
