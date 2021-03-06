#ifndef __TDG_H__
#define __TDG_H__

#include <nds.h>
#include "Globals.h"
#include "ColMap.h"
#include "CFx.h"
#include "CFxManager.h"
#include "CItem.h"
#include "CItemCache.h"
#include "CMenu.h"
#include "CDoor.h"
#include "CRoom.h"
#include "CSprite.h"
#include "CCharacter.h"
#include "CTimer.h"
#include "CEvent.h"
#include "CWatch.h"
#include "CConsole.h"
#include "CKeyboard.h"
#include "CPathFinder.h"
#include "CPointer.h"

#include "map_angus_landing.h"
#include "map_angus_room1.h"
#include "map_angus_room2.h"
#include "map_angus_secret.h"
#include "map_angus_stairs.h"
#include "map_cellar.h"
#include "map_clock.h"
#include "map_courtyard.h"
#include "map_dining.h"
#include "map_drawing.h"
#include "map_garden.h"
#include "map_graveyard.h"
#include "map_hall1.h"
#include "map_hall2.h"
#include "map_hall3.h"
#include "map_hall4.h"
#include "map_kitchen.h"
#include "map_landing.h"
#include "map_library.h"
#include "map_outside1.h"
#include "map_outside2.h"
#include "map_passage1.h"
#include "map_passage2.h"
#include "map_bentley.h"
#include "map_cook.h"
#include "map_cynthia.h"
#include "map_dingle.h"
#include "map_doctor.h"
#include "map_gabriel.h"
#include "map_major.h"
#include "map_professor.h"
#include "map_reverend.h"
#include "map_snide.h"
#include "map_stairs.h"
#include "map_study.h"
#include "map_laundry.h"
#include "map_sewers.h"

#include "map_angus_landing_front.h"
#include "map_angus_room_front.h"
#include "map_angus_secret_front.h"
#include "map_courtyard_front.h"
#include "map_dining_front.h"
#include "map_garden_front.h"
#include "map_graveyard_front.h"
#include "map_landing_front1.h"
#include "map_landing_front2.h"
#include "map_outside2_front.h"
#include "map_stairs_front.h"

#include "intro_blank.h"
#include "intro_headsoft.h"
#include "intro_infectuous.h"
#include "intro_proteus.h"
#include "intro_retrobytes.h"
#include "intro_retroremakes.h"
#include "intro_spacefractal.h"

#include "sprite_snide_head.h"
#include "sprite_snide_body.h"
#include "sprite_reverend_head.h"
#include "sprite_reverend_body.h"
#include "sprite_bentley_head.h"
#include "sprite_bentley_body.h"
#include "sprite_cook_head.h"
#include "sprite_cook_body.h"
#include "sprite_gabriel_head.h"
#include "sprite_gabriel_body.h"
#include "sprite_cynthia_head.h"
#include "sprite_cynthia_body.h"
#include "sprite_professor_head.h"
#include "sprite_professor_body.h"
#include "sprite_doctor_head.h"
#include "sprite_doctor_body.h"
#include "sprite_major_head.h"
#include "sprite_major_body.h"
#include "sprite_dingle_head.h"
#include "sprite_dingle_body.h"
#include "sprite_angus_head.h"
#include "sprite_angus_body.h"
#include "sprite_question_head.h"
#include "sprite_question_body.h"

#include "sprite_misc.h"

#include "sprite_fx_leak.h"
#include "sprite_fx_rain.h"
#include "sprite_fx_rat.h"
#include "sprite_fx_hourglass.h"
#include "sprite_fx_skull.h"

#include "sprite_col.h"

#include "sprite_watch.h"

#include "watch.h"

#include "paused.h"

#include "menu_top.h"
#include "menu_bottom.h"
#include "menu_questions.h"

#include "end_top_lose.h"
#include "end_top_win.h"
#include "end_bottom.h"

#include "keyboard.h"

#include "font.h"
#include "font_large.h"

#include "icons.h"
#include "items.h"

#define INTRO_BG0_MAP_BASE			28
#define INTRO_BG0_MAP_BASE_SUB		28

#define INTRO_BG1_MAP_BASE			30
#define INTRO_BG1_MAP_BASE_SUB		30

#define INTRO_BG0_TILE_BASE			0
#define INTRO_BG0_TILE_BASE_SUB		0

#define INTRO_BG1_TILE_BASE			5
#define INTRO_BG1_TILE_BASE_SUB		5

#define BG0_MAP_BASE				26
#define BG0_MAP_BASE_SUB			26

#define BG1_MAP_BASE				27
#define BG1_MAP_BASE_SUB			27

#define BG2_MAP_BASE				28
#define BG2_MAP_BASE_SUB			28

#define BG3_MAP_BASE				30
#define BG3_MAP_BASE_SUB			30

#define BG0_TILE_BASE				7
#define BG0_TILE_BASE_SUB			7

#define BG1_TILE_BASE				5
#define BG1_TILE_BASE_SUB			5

#define BG2_TILE_BASE				3
#define BG2_TILE_BASE_SUB			3

#define BG3_TILE_BASE				0
#define BG3_TILE_BASE_SUB			0

enum Background
{
	BG0 = BIT(0),
	BG1 = BIT(1),
	BG2 = BIT(2),
	BG3 = BIT(3),
	SPRITE = BIT(4),
	BG0_SUB = BIT(5),
	BG1_SUB = BIT(6),
	BG2_SUB = BIT(7),
	BG3_SUB = BIT(8),
	SPRITE_SUB = BIT(9)
};

#define ARRAY_LENGTH(x)		(sizeof(x) / sizeof(x[0]))

#define PI 3.1415926536

#define ASSERT(expr)	(if(!expr) fprintf(stderr, "Error!");)

#endif
