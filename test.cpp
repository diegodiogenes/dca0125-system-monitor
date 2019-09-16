#include <string>
#include <iostream>
#include <curses.h>

std::string name_key( int c ) {
  // This function takes a keycode and turns it into a string.
  // I'm pretty sure there is a curses function to do this,
  // but I'm not going to look it up right now... (sorry)
  std::string result;
  if (c < 32) {  // control keys
    result = "^";
    result += (char)c +'A' -1;
    }
  else if (c == 127) result = "^?";
  else if (c > 127) result = "FN";  // any function key (arrows, F1, Cut, etc)
  else result = c;  // normal alphanumeric key
  return result;
}

int main() {
  std::string s = "Press the 'any' key...";
  int c;
  int option;

  // Initialze
  initscr();
//   raw();			  // line-buffering off, echo off, etc.
//   nonl();			  // NL conversions off
  intrflush( stdscr, FALSE );	  // we want ^C, etc...
  (void) keypad( stdscr, TRUE );  // extended keys ON

//   curs_set( 1 );		  // make sure the cursor is visible

//   // clear the screen
//   wclear( stdscr );

//   // move the cursor to (x, y) = (10, 5)
//   wmove( stdscr, 5, 10 );

//   // display our message (curses routines are not prototyped with const)
//   waddstr( stdscr, const_cast<char*>(s.c_str()) );

//   // update the screen so that our changes are visible
//   wrefresh( stdscr );

  // wait for the user to press a single key
  c = wgetch( stdscr );

  std::cout << name_key(c);

  // complain that the user did not press the 'any' key
//   wmove( stdscr, 7, 10 );
//   s = std::string( "Hey, you pressed the '" ) +name_key( c ) +"' key!";
//   waddstr( stdscr, const_cast<char*>(s.c_str()) );

//   // wait for the user to quit
//   wmove( stdscr, 20, 0 );
//   waddstr( stdscr, "Press any key to quit..." );
//   wrefresh( stdscr );
//   wgetch( stdscr );

//   // restore the terminal to its proper state and quit
   endwin();
   
   printf("to aqui");
   std::cin >> option;
   printf("%d", option);

   return EXIT_SUCCESS;
  }