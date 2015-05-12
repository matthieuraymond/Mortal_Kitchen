#pragma once


#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <cmath>


#include <al.h>
#include <alc.h>

#include <sndfile.h>

ALuint LoadSound(const std::string& Filename);
void play_sound();
void rewind_sound();
void init_sound();
