﻿/**
 * Map object class implementation file.
 *
 * authors: Miloslav Číž, Martin Gabriel
 * year: 2013
 */

#include "map_object.h"

//-----------------------------------------------

c_map_object::c_map_object(t_object_type object_type, int link_id,  int link_id2, long int *global_time)
  {
	int i, number_of_bitmaps;

	this->link_id = link_id;
	this->link_id2 = link_id2;
	this->playing_sound = false;
	this->sound = NULL;
	this->global_time = global_time;
	this->input = false;
	this->type = object_type;
	this->object_state = OBJECT_STATE_OFF;
	this->stepable = false;
	this->animation_frame = 0;
	this->playing_animation = ANIMATION_NONE;
	this->sound = NULL;
	this->sound_gain = 1.0;
	 
	for (i = 0; i < 5; i++)
      this->bitmaps[i] = NULL;

	number_of_bitmaps = 1;

	switch (this->type)
	  {
	    case OBJECT_LEVER:
          this->bitmaps[0] = al_load_bitmap("resources/object_lever_1.png");
		  this->bitmaps[1] = al_load_bitmap("resources/object_lever_2.png");
          this->bitmaps[2] = al_load_bitmap("resources/object_lever_3.png");
		  this->bitmaps[3] = al_load_bitmap("resources/object_lever_4.png");
		  this->bitmaps[4] = al_load_bitmap("resources/object_lever_5.png");
		  this->sound = al_load_sample("resources/switch.wav");
		  this->sound_gain = 0.5;
		  number_of_bitmaps = 5;

		  this->input = true;
		  break;

		case OBJECT_ELEVATOR:
          this->bitmaps[0] = al_load_bitmap("resources/object_elevator_1.png");
		  this->bitmaps[1] = al_load_bitmap("resources/object_elevator_2.png");
          this->bitmaps[2] = al_load_bitmap("resources/object_elevator_3.png");
		  this->bitmaps[3] = al_load_bitmap("resources/object_elevator_4.png");
		  this->stepable = true;
		  number_of_bitmaps = 4;

		  break;

	    case OBJECT_CRATE:
		  this->bitmaps[0] = al_load_bitmap("resources/object_crate.png");
		  this->sound = al_load_sample("resources/crate_shift.wav");
		  this->sound_gain = 0.2;
		  this->stepable = true;
		  break;

		case OBJECT_TREE:
		  this->bitmaps[0] = al_load_bitmap("resources/object_tree.png");
		  break;

		case OBJECT_STAIRS_NORTH:
		  this->stepable = true;
		  this->bitmaps[0] = al_load_bitmap("resources/object_stairs_north.png");
		  break;

		case OBJECT_STAIRS_EAST:
		  this->stepable = true;
		  this->bitmaps[0] = al_load_bitmap("resources/object_stairs_east.png");
		  break;

		case OBJECT_STAIRS_SOUTH:
		  this->stepable = true;
		  this->bitmaps[0] = al_load_bitmap("resources/object_stairs_south.png");
		  break;

		case OBJECT_STAIRS_WEST:
		  this->stepable = true;
		  this->bitmaps[0] = al_load_bitmap("resources/object_stairs_west.png");
		  break; 

        case OBJECT_DOOR_HORIZONTAL:
		  this->stepable = true;
		  this->bitmaps[0] = al_load_bitmap("resources/object_door_horizontal_1.png");
		  this->bitmaps[1] = al_load_bitmap("resources/object_door_horizontal_2.png");
		  this->bitmaps[2] = al_load_bitmap("resources/object_door_horizontal_3.png");
		  this->bitmaps[3] = al_load_bitmap("resources/object_door_horizontal_4.png");
		  this->sound = al_load_sample("resources/door.wav");
		  this->sound_gain = 0.5;
		  number_of_bitmaps = 4;
		  break; 

		case OBJECT_DOOR_VERTICAL:
		  this->stepable = true;
		  this->bitmaps[0] = al_load_bitmap("resources/object_door_vertical_1.png");
		  this->bitmaps[1] = al_load_bitmap("resources/object_door_vertical_2.png");
		  this->bitmaps[2] = al_load_bitmap("resources/object_door_vertical_3.png");
		  this->bitmaps[3] = al_load_bitmap("resources/object_door_vertical_4.png");
		  this->sound = al_load_sample("resources/door.wav");
		  this->sound_gain = 0.3;
		  number_of_bitmaps = 4;
		  break; 

		case OBJECT_BUTTON:
		  this->stepable = true;
		  this->input = true;
		  this->bitmaps[0] = al_load_bitmap("resources/object_button_1.png");
		  this->bitmaps[1] = al_load_bitmap("resources/object_button_2.png");
		  this->sound = al_load_sample("resources/click.wav");
		  this->sound_gain = 0.3;
		  number_of_bitmaps = 2;
		  break; 

		case OBJECT_FOUNTAIN:
		  this->bitmaps[0] = al_load_bitmap("resources/object_fountain_1.png");
		  this->bitmaps[1] = al_load_bitmap("resources/object_fountain_2.png");
		  this->bitmaps[2] = al_load_bitmap("resources/object_fountain_2.png");
		  this->loop_animation(ANIMATION_IDLE);
		  number_of_bitmaps = 3;
		  break;

		case OBJECT_TREE_WINTER:
		  this->bitmaps[0] = al_load_bitmap("resources/object_tree_winter.png");
		  break;

		case OBJECT_ROCK:
		  this->bitmaps[0] = al_load_bitmap("resources/object_rock.png");
		  break;
	  }

	for (i = 0; i < number_of_bitmaps; i++)
	  if (!this->bitmaps[i])
	    {
		  this->succesfully_loaded = false;
		  break;
		}
  }

//-----------------------------------------------

t_object_type c_map_object::get_type()
  {
	return this->type;
  }

//-----------------------------------------------

bool c_map_object::is_input()
  {
	return this->input;
  }

//-----------------------------------------------

t_object_state c_map_object::get_state()
  {
	return this->object_state;
  }

//-----------------------------------------------

int c_map_object::get_link_id()
  {
	return this->link_id;
  }

//-----------------------------------------------

int c_map_object::get_link_id2()
  {
	return this->link_id2;
  }

//-----------------------------------------------

void c_map_object::switch_state()
  { 
	if (this->object_state == OBJECT_STATE_OFF)
	  this->object_state = OBJECT_STATE_ON;
	else
      this->object_state = OBJECT_STATE_OFF;
	
	switch (this->type)
	  {
	    case OBJECT_DOOR_HORIZONTAL:
		case OBJECT_DOOR_VERTICAL:
		case OBJECT_ELEVATOR:
		  if (this->object_state == OBJECT_STATE_OFF)
		    {
			  this->play_animation(ANIMATION_SWITCH_ON);
		    }
		  else
			{
              this->play_animation(ANIMATION_SWITCH_OFF);
		    }
			
		  break;
	  }

	if (this->is_input())
      this->update_controlled_objects();
  }

//-----------------------------------------------

void c_map_object::update_animation_period()
  {
	switch (this->type)
	  {
	    case OBJECT_LEVER:
		  this->animation_period = 5;
		  break;

		case OBJECT_FOUNTAIN:
		  this->animation_period = 3;
		  break;

		case OBJECT_DOOR_HORIZONTAL:
		case OBJECT_DOOR_VERTICAL:
		  this->animation_period = 4;
		  break;

		case OBJECT_ELEVATOR:
		  this->animation_period = 4;
	      break;

		default:
		  this->animation_period = 1;
	  }
  }

//-----------------------------------------------

void c_map_object::draw(int x, int y)
  {
	int offset_x, offset_y;
	ALLEGRO_BITMAP *bitmap_to_draw;

	if (this->is_animating())
	  {
		this->animation_frame = *this->global_time - this->started_playing;

	    if (this->looping_animation)
			this->animation_frame = this->animation_frame % this->animation_period;

		if (this->animation_frame < 0) // handle overflow
		  this->animation_frame = 0;
	  }

	offset_x = 0;
	offset_y = 0;

	switch (this->type)
	  {
	    case OBJECT_CRATE:
		  bitmap_to_draw = this->bitmaps[0];

		  switch (this->playing_animation)
		    {
		      case ANIMATION_NONE:
			    break;

			  case ANIMATION_SHIFT_EAST:
				if (this->animation_frame < 3)
				  offset_x = (2 - this->animation_frame) * -21;
				else
				  this->stop_animation();			
				break;

			  case ANIMATION_SHIFT_WEST:
				if (this->animation_frame < 3)
				  offset_x = (2 - this->animation_frame) * 21;
				else
				  this->stop_animation();
				break;

			  case ANIMATION_SHIFT_NORTH:
				if (this->animation_frame < 2)
				  return;
				else
				  this->stop_animation();
				break;

			  case ANIMATION_SHIFT_SOUTH:
				if (this->animation_frame < 2)
				  offset_y = (2 - this->animation_frame) * -13;
				else
				  {
				    this->stop_animation();
				  }
				break;
		    }

		  break;  

	    case OBJECT_LEVER:

		  switch (this->playing_animation)
		    {
		      case ANIMATION_NONE:
				if (this->object_state == OBJECT_STATE_OFF)
			      bitmap_to_draw = this->bitmaps[0];
			    else
			      bitmap_to_draw = this->bitmaps[4];
			    break;
		     
			  case ANIMATION_SWITCH_ON:
				if (this->animation_frame <= 4)
				  bitmap_to_draw = this->bitmaps[this->animation_frame % 5];
				else
				  {
				    this->stop_animation();
				    bitmap_to_draw = this->bitmaps[4];
				  }
				break;

			  case ANIMATION_SWITCH_OFF:
				if (this->animation_frame <= 4)
				  bitmap_to_draw = this->bitmaps[4 - (this->animation_frame % 5)];
				else
				  {
				    this->stop_animation();
				    bitmap_to_draw = this->bitmaps[0];
				  }
				break;
				
			  default:
			    break;
		    }
		  break;

		case OBJECT_DOOR_HORIZONTAL:
		case OBJECT_DOOR_VERTICAL:
		case OBJECT_ELEVATOR:
		  switch (this->playing_animation)
		    {
		      case ANIMATION_NONE:
				if (this->object_state == OBJECT_STATE_OFF)
			      bitmap_to_draw = this->bitmaps[0];
				else
			      bitmap_to_draw = this->bitmaps[this->animation_period - 1];
			    break;
		     
			  case ANIMATION_SWITCH_ON: 
				if (this->animation_frame < this->animation_period)
				  bitmap_to_draw = this->bitmaps[this->animation_period - 1 - (this->animation_frame % this->animation_period)];
				else if (!this->looping_animation)
				  {
					bitmap_to_draw = this->bitmaps[0];
				    this->stop_animation();
				  }

				break;

			  case ANIMATION_SWITCH_OFF:
				if (this->animation_frame < this->animation_period)
				  bitmap_to_draw = this->bitmaps[this->animation_frame % this->animation_period];
				else if (!this->looping_animation)
				  {
					bitmap_to_draw = this->bitmaps[this->animation_period - 1];
				    this->stop_animation();
				  }
				break;

			  default:
				bitmap_to_draw = this->bitmaps[0];
                this->stop_animation();
				break;
		    }

		  break;

		case OBJECT_BUTTON:
		  if (this->object_state == OBJECT_STATE_ON)
		    bitmap_to_draw = this->bitmaps[1];
		  else
            bitmap_to_draw = this->bitmaps[0];
		  break;

	    default:                             // default behavior
		  if (this->playing_animation)
		    { 
			  if (this->animation_frame < this->animation_period)
		        bitmap_to_draw = this->bitmaps[this->animation_frame % (this->animation_period)];
			  else
			    {
				  bitmap_to_draw = this->bitmaps[this->animation_period - 1];

				  if (!this->looping_animation)
					this->stop_animation();
			    }
		    }
		  else
            bitmap_to_draw = this->bitmaps[0];
		  
		  break;
	  }

	al_draw_bitmap(bitmap_to_draw,offset_x + x,offset_y + y - 27,0);
  }

//-----------------------------------------------

void c_map_object::set_state(t_object_state object_state)
  {
	this->object_state = object_state;
  }

//-----------------------------------------------

bool c_map_object::is_stepable()
  {
	return this->stepable;
  }

//-----------------------------------------------

void c_map_object::use()
  {
	if (this->is_animating())
	  return;
	
	switch(this->type)
	  {
	    case OBJECT_LEVER:
		  if (this->object_state == OBJECT_STATE_OFF)
		    {
			  this->play_animation(ANIMATION_SWITCH_ON);
			  this->object_state = OBJECT_STATE_ON;
		    }
		  else
		    {
			  this->play_animation(ANIMATION_SWITCH_OFF);
              this->object_state = OBJECT_STATE_OFF;
		    }

		default:
		  break;
	  } 

	this->update_controlled_objects();
  }

//-----------------------------------------------

void c_map_object::add_controlled_objects(int number_of_objects, c_map_object *objects[])
  {
	int i;
	
	this->number_of_controlled = number_of_objects;

	this->controlling = new c_map_object*[number_of_objects];
	
	for (i = 0; i < number_of_objects; i++)
	  this->controlling[i] = objects[i];
  }

//-----------------------------------------------

void c_map_object::update_controlled_objects()
  {
	int i;
	
	for (i = 0; i < this->number_of_controlled; i++)
	  this->controlling[i]->switch_state();
  }

//-----------------------------------------------

bool c_map_object::compare_link_ids(c_map_object *another_object)
  {
	if (this->link_id == another_object->get_link_id())
	  return true;

	if (this->link_id2 >= 0 &&
	  this->link_id2 == another_object->get_link_id())
	  return true;

	if (another_object->get_link_id2() >= 0 &&
	  this->link_id == another_object->get_link_id2())
	  return true;

	if (this->link_id2 >= 0 && another_object->get_link_id2() >=0
	  && this->link_id2 == another_object->get_link_id2())
	  return true;

	return false;
  }

//-----------------------------------------------