#pragma once


#include <LibSL/LibSL.h>

#include <Box2D/Box2D.h>

void phy_init();
void phy_step();
void phy_terminate();

void phy_debug_draw();
