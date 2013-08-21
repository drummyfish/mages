﻿/**
 * Game class implementation file.
 *
 * authors: Miloslav Číž
 * year: 2013
 */

#include "game.h"

//-----------------------------------------------

c_game::c_game()
  {   
	string help_array[1];
	ALLEGRO_DISPLAY_MODE display_data;

	if (!al_init())                                // initialise allegro
	  {
	    cerr << "ERROR: failed to initialize allegro." << endl;
	  }
 
	if (!al_init_image_addon())                    // initialise image addon
	  {
		cerr << "ERROR: failed to initialize al_init_image_addon." << endl; 
	  }
 
	if (!al_install_keyboard())                    // initialise keyboard
	  {
        cerr << "ERROR: failed to initialize the keyboard." << endl;
      }

	if (!al_install_audio())                       // initialise audio
	  {
        cerr << "ERROR: failed to initialize audio." << endl;
      }
 
	if (!al_reserve_samples(10))                   // reserve audio samples
	  {
        cerr << "ERROR: failed to reserve samples." << endl;
      }

    if (!al_init_acodec_addon())                   // initialise audio codec addon
	  {
        cerr << "ERROR: failed to initialize audio codecs." << endl;
      }

    if (!al_init_primitives_addon())               // initialise primitives addon
	  {
		cerr << "ERROR: failed to initialize primitives addon." << endl;
	  }

	al_init_font_addon();                          // initialise the font addon
    al_init_ttf_addon();                           // initialise the ttf addon

	if(!al_install_mouse())
	  {
        cerr << "ERROR: failed to initialize mouse." << endl;
      }
	
	this->load();                                  // load the progress and settings from the data file

	if (this->settings.fullscreen)
	  {
		al_get_display_mode(al_get_num_display_modes() - 1,&display_data);
		al_set_new_display_flags(ALLEGRO_FULLSCREEN);
		this->input_output_state.screen_x = display_data.width;
		this->input_output_state.screen_y = display_data.height;
	  }
	else
	  {
		this->input_output_state.screen_x = 800;
		this->input_output_state.screen_y = 600;
	  }

    display = al_create_display(this->input_output_state.screen_x,this->input_output_state.screen_y);  // initialise screen

	if(!this->display)
	  {
		cerr << "ERROR: failed to initialize display." << endl; 
	  }
	
	this->event_queue = al_create_event_queue();   // initialise event queue

	if(!this->event_queue)
	  {
        cerr << "ERROR: failed to create event_queue." << endl;
      }

	this->global_timer = al_create_timer(0.05);    // initialise the timer
	
	if(!this->global_timer)
	  {
        cerr << "ERROR: failed to create global timer." << endl;
      }

	this->local_texts = new c_associative_array();      // set the language
	this->set_language(this->settings.language);

	al_register_event_source(this->event_queue,al_get_display_event_source(display));
	al_register_event_source(this->event_queue,al_get_timer_event_source(this->global_timer));
	al_register_event_source(this->event_queue,al_get_keyboard_event_source());
//	al_register_event_source(this->event_queue,al_get_mouse_event_source());
	this->global_time = 0;
	
	this->cursor_bitmap = al_load_bitmap("resources/cursor.png");
	this->cursor = al_create_mouse_cursor(this->cursor_bitmap,1,1);
	al_set_mouse_cursor(display,this->cursor);
	
	this->input_output_state.key_down = false;            // set keyboard/mouse state
	this->input_output_state.key_up = false;
	this->input_output_state.key_left = false;
	this->input_output_state.key_right = false;
	this->input_output_state.key_1 = false;
	this->input_output_state.key_2 = false;
	this->input_output_state.key_3 = false;
	this->input_output_state.mouse_x = 0;
	this->input_output_state.mouse_y = 0;
	this->input_output_state.key_use = false;
	this->input_output_state.key_cast_1 = false;
	this->input_output_state.key_cast_2 = false;
	this->input_output_state.key_cast_3 = false;
	this->input_output_state.mouse_1 = false; 
	this->input_output_state.key_map_explore = false;
  }

//-----------------------------------------------

void c_game::set_language(string language)
  {
	this->settings.language = language;

	if (this->settings.language.compare("english") == 0)
	  this->local_texts->load_from_file("resources/local_texts_english");
	else
	  this->local_texts->load_from_file("resources/local_texts_czech");

    this->main_menu_title = this->local_texts->get_text("main_menu_title");
	this->main_menu_items[0] = this->local_texts->get_text("main_menu_0");
	this->main_menu_items[1] = this->local_texts->get_text("main_menu_1");
	this->main_menu_items[2] = this->local_texts->get_text("main_menu_2");
	this->main_menu_items[3] = this->local_texts->get_text("main_menu_3");
	this->settings_menu_title = this->local_texts->get_text("settings_menu_title");
	this->settings_menu_items[0] = this->local_texts->get_text("settings_menu_0");
	this->settings_menu_items[1] = this->local_texts->get_text("settings_menu_1");
	this->settings_menu_items[2] = this->local_texts->get_text("settings_menu_2");
	this->settings_menu_items[3] = this->local_texts->get_text("settings_menu_3");
	this->settings_menu_items[4] = this->local_texts->get_text("settings_menu_4");
	this->about_lines[0] = this->local_texts->get_text("about_0") + VERSION;         // append the program version number
	this->about_lines[1] = this->local_texts->get_text("about_1");
	this->about_lines[2] = this->local_texts->get_text("about_2");
	this->intro_lines_1[0] = this->local_texts->get_text("intro_0");
	this->intro_lines_1[1] = this->local_texts->get_text("intro_1");
	this->intro_lines_1[2] = this->local_texts->get_text("intro_2");
	this->intro_lines_1[3] = this->local_texts->get_text("intro_3");
	this->intro_lines_1[4] = this->local_texts->get_text("intro_4");
	this->intro_lines_1[5] = this->local_texts->get_text("intro_5");
	this->intro_lines_1[6] = this->local_texts->get_text("intro_6");
	this->intro_lines_1[7] = this->local_texts->get_text("intro_7");
	this->intro_lines_1[8] = this->local_texts->get_text("intro_8");
	this->intro_lines_1[9] = this->local_texts->get_text("intro_9");
	this->intro_lines_2[0] = this->local_texts->get_text("intro_10");
	this->intro_lines_2[1] = this->local_texts->get_text("intro_11");
	this->intro_lines_2[2] = this->local_texts->get_text("intro_12");
	this->intro_lines_2[3] = this->local_texts->get_text("intro_13");
	this->intro_lines_2[4] = this->local_texts->get_text("intro_14");
	this->intro_lines_2[5] = this->local_texts->get_text("intro_15");
	this->intro_lines_2[6] = this->local_texts->get_text("intro_16");
	this->intro_lines_2[7] = this->local_texts->get_text("intro_17");
	this->intro_lines_2[8] = this->local_texts->get_text("intro_18");
	this->intro_lines_2[9] = this->local_texts->get_text("intro_19");
  }

//-----------------------------------------------

c_game::~c_game()
  {
	al_stop_samples();                           // stop all sounds	
	delete this->map;
	delete this->menu;
	delete this->local_texts;
	al_uninstall_keyboard();
	al_uninstall_mouse(); 
	al_shutdown_primitives_addon();
	al_shutdown_image_addon();
	al_shutdown_font_addon();
	al_destroy_timer(this->global_timer); 
	al_destroy_display(this->display);
	al_destroy_event_queue(this->event_queue);
	al_uninstall_audio();
  }

//-----------------------------------------------

void c_game::load()
  {
    c_associative_array *associate_array;

	associate_array = new c_associative_array();

	if (associate_array == NULL)
	  return;

	associate_array->load_from_file("data");
	this->settings.fullscreen = (associate_array->get_text("fullscreen").compare("1") == 0);
	this->settings.music_on = (associate_array->get_text("music_on").compare("1") == 0);
	this->settings.sound_volume = atoi(associate_array->get_text("sound_volume").c_str());
	this->settings.last_level = atoi(associate_array->get_text("last_level").c_str());
	this->settings.language = associate_array->get_text("language");

	delete associate_array;
  }

//-----------------------------------------------

void c_game::save()
  {
    c_associative_array *associate_array;

	associate_array = new c_associative_array();

	if (associate_array == NULL)
	  return;

	if (this->settings.fullscreen)
	  associate_array->set_text("fullscreen","1");
	else
	  associate_array->set_text("fullscreen","0");

	if (this->settings.music_on)
	  associate_array->set_text("music_on","1");
	else
	  associate_array->set_text("music_on","0");

	associate_array->set_text("sound_volume",to_string((long long) this->settings.sound_volume));
	associate_array->set_text("last_level",to_string((long long) this->settings.last_level));
	associate_array->set_text("language",this->settings.language);

	associate_array->save_to_file("data");

	delete associate_array;
  }

//-----------------------------------------------

void c_game::update_settings_menu_items()
  {
	if (this->settings.fullscreen)
	  this->settings_menu_items_done[0] = this->settings_menu_items[0] + ": " + this->local_texts->get_text("option_on");
	else
      this->settings_menu_items_done[0] = this->settings_menu_items[0] + ": " + this->local_texts->get_text("option_off");

	if (this->settings.music_on)
	  this->settings_menu_items_done[1] = this->settings_menu_items[1] + ": " + this->local_texts->get_text("option_on");
	else
      this->settings_menu_items_done[1] = this->settings_menu_items[1] + ": " + this->local_texts->get_text("option_off");

	this->settings_menu_items_done[2] = this->settings_menu_items[2] + ": " + to_string((long long) this->settings.sound_volume);

	if (this->settings.language.compare("english") == 0)
	  this->settings_menu_items_done[3] = this->settings_menu_items[3] + ": EN";
	else
	  this->settings_menu_items_done[3] = this->settings_menu_items[3] + ": CZ";

	this->settings_menu_items_done[4] = this->settings_menu_items[4];
  }
 
//-----------------------------------------------

void c_game::run()
  {
	string help_str;
	int menu_return_value;
	bool quit_program;
	bool event_occured;
	ALLEGRO_EVENT program_event;
	ALLEGRO_TIMEOUT timeout;

	this->map = new c_map("resources/map5",&this->input_output_state,&this->global_time,0);
	
	this->menu = new c_menu(&this->input_output_state);

	this->menu_state = MENU_STATE_FIRST_SCREEN;
	this->menu->set_menu_info_screen("resources/introduction.png",NULL,0,5.0,255,255,255);

	if (!map->is_succesfully_loaded())
	  {
		cerr << "ERROR: the map couldn't be loaded." << endl;
	  }

	al_start_timer(this->global_timer);

	al_init_timeout(&timeout, 0.05);

	quit_program = false;
	
	while (true)                   // main loop
	  {  /*
		switch (map->update())
		  {
		    case GAME_STATE_PLAYING:
			  break;

			case GAME_STATE_LOSE:
			  cout << "lost" << endl;
			  break;

			case GAME_STATE_WIN:
			  cout << "won" << endl;
			  break;

			case GAME_STATE_PAUSE:
			  cout << "pause" << endl;
			  break;
		  }

		al_rest(0.01);
		*/
		
		switch (this->menu_state)
		  {
		    case MENU_STATE_FIRST_SCREEN:
			case MENU_STATE_ABOUT:
              menu_return_value = this->menu->update();

			  if (menu_return_value > 0)
			    {
				  this->menu_state = MENU_STATE_MAIN_MENU;
				  this->menu->set_menu_items(this->main_menu_items,4,this->main_menu_title,false);
			    }

			  break;

			case MENU_STATE_INTRO:
			  menu_return_value = this->menu->update();

			  if (menu_return_value >= 0)
			    {
				  this->menu_state = MENU_STATE_INTRO2;
				  this->menu->set_menu_info_screen("resources/characters.png",this->intro_lines_2,10,-1,255,255,255);
			    }

			  break;

			case MENU_STATE_INTRO2:
			  menu_return_value = this->menu->update();	

			  if (menu_return_value >= 0)
			    {
			  	  this->menu->set_menu_choose_level(this->settings.last_level);
				  this->menu_state = MENU_STATE_LEVEL_CHOOSING;
			    }

			  break;

			case MENU_STATE_LEVEL_CHOOSING:
			  menu_return_value = this->menu->update();
			  break;

			case MENU_STATE_MAIN_MENU:
			  menu_return_value = this->menu->update();

			  switch (menu_return_value)
			    {
			      case 0:
					if (this->settings.last_level == 0)
					  {
						this->settings.last_level = 1;        // set information that the intro has been played
						this->save();
						this->menu_state = MENU_STATE_INTRO;
						this->menu->set_menu_info_screen("resources/characters.png",this->intro_lines_1,10,-1,255,255,255);
					  }
					else
					  { 
						this->menu->set_menu_choose_level(this->settings.last_level);
						this->menu_state = MENU_STATE_LEVEL_CHOOSING;
					  }

					break;

				  case 1:
					this->menu_state = MENU_STATE_SETTINGS_MENU;
					this->update_settings_menu_items();
					this->menu->set_menu_items(this->settings_menu_items_done,5,this->settings_menu_title,false);
					break;

				  case 2:
					this->menu_state = MENU_STATE_ABOUT;
					this->menu->set_menu_info_screen("",this->about_lines,3,-1.0,253,221,91);
					break;

				  case 3:
					quit_program = true;
					break;
			    }

			  break;

			case MENU_STATE_SETTINGS_MENU:

			  menu_return_value = this->menu->update();

			  switch (menu_return_value)
			    {
			      case 0:
					this->settings.fullscreen = !this->settings.fullscreen;
					this->update_settings_menu_items();
					this->menu->set_menu_items(this->settings_menu_items_done,5,this->settings_menu_title,true);
				    break;

				  case 1:
					this->settings.music_on = !this->settings.music_on;
					this->update_settings_menu_items();
					this->menu->set_menu_items(this->settings_menu_items_done,5,this->settings_menu_title,true);
					break;

				  case 2:
					this->settings.sound_volume += 20;

					if (this->settings.sound_volume > 100)
					  this->settings.sound_volume = 0;
					
					this->update_settings_menu_items();
					this->menu->set_menu_items(this->settings_menu_items_done,5,this->settings_menu_title,true);
					break;

				  case 3:
					if (this->settings.language.compare("english") == 0)
					  this->settings.language = "czech";
					else
					  this->settings.language = "english";

					this->set_language(this->settings.language);
					this->update_settings_menu_items();
					this->menu->set_menu_items(this->settings_menu_items_done,5,this->settings_menu_title,true);
					break;

				  case 4:
					this->menu_state = MENU_STATE_MAIN_MENU;
				    this->menu->set_menu_items(this->main_menu_items,4,this->main_menu_title,false);
					this->save();
					break;
			    }

			  break;
		  }

		al_flip_display();
		
		this->input_output_state.key_use = false;      // we only want to detect one press

		event_occured = al_get_next_event(this->event_queue, &program_event);

		if (event_occured)                             // handle events
		  switch (program_event.type)
		    {
		      case ALLEGRO_EVENT_DISPLAY_CLOSE:        // program close
                quit_program = true;
				break;

			  case ALLEGRO_EVENT_TIMER:                // global timer event
				this->global_time++;
				break;

			  case ALLEGRO_EVENT_KEY_DOWN:             // key down event
				switch(program_event.keyboard.keycode)
				  {
					case ALLEGRO_KEY_UP:
					   this->input_output_state.key_up = true;
					   break;
 
					case ALLEGRO_KEY_DOWN:
					   this->input_output_state.key_down = true;
					   break;
 
					case ALLEGRO_KEY_LEFT: 
					   this->input_output_state.key_left = true;
					   break;
 
					case ALLEGRO_KEY_RIGHT:
					   this->input_output_state.key_right = true;
					   break;

					case ALLEGRO_KEY_1:
					   this->input_output_state.key_1 = true;
					   break;

					case ALLEGRO_KEY_2:
					   this->input_output_state.key_2 = true;
					   break;

					case ALLEGRO_KEY_3:
					   this->input_output_state.key_3 = true;
					   break;

					case ALLEGRO_KEY_8:
					   this->input_output_state.key_cast_1 = true;
					   break;

					case ALLEGRO_KEY_9:
					   this->input_output_state.key_cast_2 = true;
					   break;

					case ALLEGRO_KEY_0:
					   this->input_output_state.key_cast_3 = true;
					   break;

					case ALLEGRO_KEY_Q:
					  this->input_output_state.key_use = true;
					  break;

					case ALLEGRO_KEY_W:
					  this->input_output_state.key_map_explore = true;
					  break;
				  }
				break;

			  case ALLEGRO_EVENT_KEY_UP:               // key up event
				switch(program_event.keyboard.keycode)
				  {
					case ALLEGRO_KEY_UP:
					   this->input_output_state.key_up = false;
					   break;
 
					case ALLEGRO_KEY_DOWN:
					   this->input_output_state.key_down = false;
					   break;
 
					case ALLEGRO_KEY_LEFT: 
					   this->input_output_state.key_left = false;
					   break;
 
					case ALLEGRO_KEY_RIGHT:
					   this->input_output_state.key_right = false;
					   break;

					case ALLEGRO_KEY_1:
					   this->input_output_state.key_1 = false;
					   break;

					case ALLEGRO_KEY_2:
					   this->input_output_state.key_2 = false;
					   break;

					case ALLEGRO_KEY_3:
					   this->input_output_state.key_3 = false;
					   break;

					case ALLEGRO_KEY_8:
					   this->input_output_state.key_cast_1 = false;
					   break;

					case ALLEGRO_KEY_9:
					   this->input_output_state.key_cast_2 = false;
					   break;

					case ALLEGRO_KEY_0:
					   this->input_output_state.key_cast_3 = false;
					   break;

					case ALLEGRO_KEY_Q:
					  this->input_output_state.key_use = false;
					  break;

					case ALLEGRO_KEY_W:
					  this->input_output_state.key_map_explore = false;
					  break;
				  }
			  break;

			  case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
				this->input_output_state.mouse_1 = true;
				this->input_output_state.mouse_x = program_event.mouse.x;
				this->input_output_state.mouse_y = program_event.mouse.y;
			    break;

			  case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
			    this->input_output_state.mouse_1 = false;
				break;
		    }

		if (quit_program)
		  break; 
	  }
  }

//-----------------------------------------------