﻿/**
 * The main game file.
 *
 * authors: Miloslav Číž, Martin Gabriel
 * year: 2013
 */

#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_native_dialog.h"
#include "associative_array.h"
#include "general.h"
#include "game.h"
 
int main(int argc, char **argv)
  {
    /*c_game *game;
	game = new c_game();
	game->run();
	delete game;
	al_rest(5);*/

	  c_associative_array* pole;
	  pole = new c_associative_array();

	  pole->set_text("ahoj", "vole");
	  pole->set_text("necum", "sem");

	  cout<< pole->get_text("ahoj")<< " " << pole->get_text("necum") << " " << pole->get_text("hehe") << endl;
  }