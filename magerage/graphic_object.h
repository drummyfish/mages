﻿#ifndef GRAPHIC_OBJECT_H
#define GRAPHIC_OBJECT_H

/**
 * Graphic object class header file.
 *
 * Copyright 2013 Miloslav Číž
 *
 * This file is part of Mage Rage.
 *
 * Mage Rage is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Mage Rage is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Foobar. If not, see <http://www.gnu.org/licenses/>.
 */

#include "general.h"

using namespace std;

class c_graphic_object
  {
	/**
	  This class represents an object that is able to
	  draw itself on the screen. It can also play
	  animations.
	*/

    protected:
	  t_animation_type playing_animation;  /** type of animation being played or looped */
	  long int started_playing;            /** time when the animation started playing to count the animation frame */
	  long int *global_time;               /** reference to a global time counter variable (for animations) */
	  long int animation_frame;            /** current animation frame */
	  bool looping_animation;              /** true if the animation is looping, false otherwise */
	  int animation_period;                /** number of frames of the current animation */
	  bool succesfully_loaded;             /** stores information about errors */
	  bool playing_sound;                  /** whether a sound is playing for this object */
	  double sound_gain;                   /** sound gain */
	  ALLEGRO_SAMPLE_ID playing_sound_id;  /** an ID of the sound being played */
	  ALLEGRO_SAMPLE *sound;               /** sound played during animation */

    public:

      virtual void draw(int x, int y);

	    /**
	      Tells the object to draw itself at given
	  	  coordinations on the screen.

		  @param x x coordination of the screen
		  @param y y coordination of the screen
	    */

	  virtual void play_animation(t_animation_type animation);

	    /**
		  Plays given animation.

		  @param animation animation to be played
		*/

	  virtual void loop_animation(t_animation_type animation);

	    /**
		  Loops the given animation untill it's
		  stopped by stop_animation().

		  @param animation animation to be looped
		*/

	  virtual void stop_animation();
	    
	    /**
		  Stops playing the current animation.
		*/

	  bool is_animating();

	    /**
		  Checks if any animation is playing.

		  @return true if any animation is
		    playing or looping, false otherwise
		*/

	  virtual void update_animation_period();

	    /**
		  Depending on current animation sets
		  the animation period attribute.
		*/

	  t_animation_type get_playing_animation();

	    /**
		  Returns a type of animation being
		  played or looped.

		  @return type of animation
		*/

	  bool is_succesfully_loaded();

	    /**
		  Checks if the map has been loaded
		  succesfully.

		  @return true if the map is loaded
		    succesfully, false otherwise
		*/

	  int get_animation_frame();

	    /**
		  Returns the number of animation
		  frame being currently displayed.

		  @return number of the animation
		    frame being displayed
		*/
  };

#endif