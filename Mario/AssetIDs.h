#pragma once

//
// This file contains all IDs of game assets 
//

#define ID_TEX_MARIO 0
#define ID_TEX_ENEMY 10
#define ID_TEX_MISC 20
#define ID_TEX_STAGE_TILES 30


#define OBJECT_TYPE_MARIO	0
#define OBJECT_TYPE_BRICK	1
#define OBJECT_TYPE_GOOMBA	2
#define OBJECT_TYPE_KOOPAS	3
#define OBJECT_TYPE_COIN 4
#define OBJECT_TYPE_PLATFORM 5
#define OBJECT_TYPE_GROUND 6
#define OBJECT_TYPE_BACKGROUNDS 7
#define OBJECT_TYPE_BOX 8
#define OBJECT_TYPE_COIN_BOX 9

#define OBJECT_TYPE_PORTAL	50


#pragma region MARIO 

#define ID_SPRITE_MARIO 10000
#define ID_SPRITE_MARIO_BIG (ID_SPRITE_MARIO + 1000)
#define ID_SPRITE_MARIO_BIG_IDLE (ID_SPRITE_MARIO_BIG + 100)
#define ID_SPRITE_MARIO_BIG_IDLE_LEFT (ID_SPRITE_MARIO_BIG_IDLE + 10)
#define ID_SPRITE_MARIO_BIG_IDLE_RIGHT (ID_SPRITE_MARIO_BIG_IDLE + 20)

#define ID_SPRITE_MARIO_BIG_WALKING (ID_SPRITE_MARIO_BIG + 200)
#define ID_SPRITE_MARIO_BIG_WALKING_LEFT (ID_SPRITE_MARIO_BIG_WALKING + 10)
#define ID_SPRITE_MARIO_BIG_WALKING_RIGHT (ID_SPRITE_MARIO_BIG_WALKING + 20)
#define ID_SPRITE_MARIO_BIG_RUNNING (ID_SPRITE_MARIO_BIG + 300)
#define ID_SPRITE_MARIO_BIG_RUNNING_LEFT (ID_SPRITE_MARIO_BIG_RUNNING + 10)
#define ID_SPRITE_MARIO_BIG_RUNNING_RIGHT (ID_SPRITE_MARIO_BIG_RUNNING + 20)
#define ID_SPRITE_MARIO_BIG_JUMP (ID_SPRITE_MARIO_BIG + 400)
#define ID_SPRITE_MARIO_BIG_JUMP_WALK (ID_SPRITE_MARIO_BIG_JUMP + 10)
#define ID_SPRITE_MARIO_BIG_JUMP_WALK_LEFT (ID_SPRITE_MARIO_BIG_JUMP_WALK + 2)
#define ID_SPRITE_MARIO_BIG_JUMP_WALK_RIGHT (ID_SPRITE_MARIO_BIG_JUMP_WALK + 6)
#define ID_SPRITE_MARIO_BIG_JUMP_RUN (ID_SPRITE_MARIO_BIG_JUMP + 20)
#define ID_SPRITE_MARIO_BIG_JUMP_RUN_LEFT (ID_SPRITE_MARIO_BIG_JUMP_RUN + 2)
#define ID_SPRITE_MARIO_BIG_JUMP_RUN_RIGHT (ID_SPRITE_MARIO_BIG_JUMP_RUN + 6)
#define ID_SPRITE_MARIO_BIG_SIT (ID_SPRITE_MARIO_BIG + 500)
#define ID_SPRITE_MARIO_BIG_SIT_LEFT (ID_SPRITE_MARIO_BIG_SIT + 10)
#define ID_SPRITE_MARIO_BIG_SIT_RIGHT (ID_SPRITE_MARIO_BIG_SIT + 20)
#define ID_SPRITE_MARIO_BIG_BRACE (ID_SPRITE_MARIO_BIG + 600)
#define ID_SPRITE_MARIO_BIG_BRACE_LEFT (ID_SPRITE_MARIO_BIG_BRACE + 10)
#define ID_SPRITE_MARIO_BIG_BRACE_RIGHT (ID_SPRITE_MARIO_BIG_BRACE + 20)

#define ID_SPRITE_MARIO_DIE (ID_SPRITE_MARIO + 3000)

#define ID_SPRITE_MARIO_SMALL (ID_SPRITE_MARIO + 2000)
#define ID_SPRITE_MARIO_SMALL_IDLE (ID_SPRITE_MARIO_SMALL + 100)
#define ID_SPRITE_MARIO_SMALL_IDLE_LEFT (ID_SPRITE_MARIO_SMALL_IDLE + 10)
#define ID_SPRITE_MARIO_SMALL_IDLE_RIGHT (ID_SPRITE_MARIO_SMALL_IDLE + 20)

#define ID_SPRITE_MARIO_SMALL_WALKING (ID_SPRITE_MARIO_SMALL + 200)
#define ID_SPRITE_MARIO_SMALL_WALKING_LEFT (ID_SPRITE_MARIO_SMALL_WALKING + 10)
#define ID_SPRITE_MARIO_SMALL_WALKING_RIGHT (ID_SPRITE_MARIO_SMALL_WALKING + 20)
#define ID_SPRITE_MARIO_SMALL_RUNNING (ID_SPRITE_MARIO_SMALL + 300)
#define ID_SPRITE_MARIO_SMALL_RUNNING_LEFT (ID_SPRITE_MARIO_SMALL_RUNNING + 10)
#define ID_SPRITE_MARIO_SMALL_RUNNING_RIGHT (ID_SPRITE_MARIO_SMALL_RUNNING + 20)
#define ID_SPRITE_MARIO_SMALL_JUMP (ID_SPRITE_MARIO_SMALL + 400)
#define ID_SPRITE_MARIO_SMALL_JUMP_WALK (ID_SPRITE_MARIO_SMALL_JUMP + 10)
#define ID_SPRITE_MARIO_SMALL_JUMP_WALK_LEFT (ID_SPRITE_MARIO_SMALL_JUMP_WALK + 2)
#define ID_SPRITE_MARIO_SMALL_JUMP_WALK_RIGHT (ID_SPRITE_MARIO_SMALL_JUMP_WALK + 6)
#define ID_SPRITE_MARIO_SMALL_JUMP_RUN (ID_SPRITE_MARIO_SMALL_JUMP + 20)
#define ID_SPRITE_MARIO_SMALL_JUMP_RUN_LEFT (ID_SPRITE_MARIO_SMALL_JUMP_RUN + 2)
#define ID_SPRITE_MARIO_SMALL_JUMP_RUN_RIGHT (ID_SPRITE_MARIO_SMALL_JUMP_RUN + 6)

#define ID_SPRITE_MARIO_SMALL_SIT (ID_SPRITE_MARIO_SMALL + 500)
#define ID_SPRITE_MARIO_SMALL_SIT_LEFT (ID_SPRITE_MARIO_SMALL_SIT + 10)
#define ID_SPRITE_MARIO_SMALL_SIT_RIGHT (ID_SPRITE_MARIO_SMALL_SIT + 20)

#define ID_SPRITE_MARIO_SMALL_BRACE (ID_SPRITE_MARIO_SMALL + 500)
#define ID_SPRITE_MARIO_SMALL_BRACE_LEFT (ID_SPRITE_MARIO_SMALL_BRACE + 10)
#define ID_SPRITE_MARIO_SMALL_BRACE_RIGHT (ID_SPRITE_MARIO_SMALL_BRACE + 20)

#pragma endregion 

#define ID_SPRITE_BRICK 20000

#define ID_SPRITE_GOOMBA 30000
#define ID_SPRITE_GOOMBA_WALK (ID_SPRITE_GOOMBA + 1000)
#define ID_SPRITE_GOOMBA_DIE (ID_SPRITE_GOOMBA + 2000)

#define ID_SPRITE_COIN 40000
#define ID_SPRITE_COIN_1 (ID_SPRITE_COIN + 1000)
#define ID_SPRITE_COIN_2 (ID_SPRITE_COIN + 2000)
#define ID_SPRITE_COIN_3 (ID_SPRITE_COIN + 3000)
#define ID_SPRITE_COIN_4 (ID_SPRITE_COIN + 4000)
#define ID_SPRITE_COIN_5 (ID_SPRITE_COIN + 5000)

#define ID_SPRITE_CLOUD 50000
#define ID_SPRITE_CLOUD_BEGIN (ID_SPRITE_CLOUD+1000)
#define ID_SPRITE_CLOUD_MIDDLE (ID_SPRITE_CLOUD+2000)
#define ID_SPRITE_CLOUD_END (ID_SPRITE_CLOUD+3000)

#define ID_SPRITE_GROUND 60000
#define ID_SPRITE_GROUND_TOP_LEFT (ID_SPRITE_GROUND+1000)
#define ID_SPRITE_GROUND_TOP_MIDDLE (ID_SPRITE_GROUND+2000)
#define ID_SPRITE_GROUND_TOP_RIGHT (ID_SPRITE_GROUND+3000)
#define ID_SPRITE_GROUND_BOTTOM_LEFT (ID_SPRITE_GROUND+4000)
#define ID_SPRITE_GROUND_BOTTOM_MIDDLE (ID_SPRITE_GROUND+5000)
#define ID_SPRITE_GROUND_BOTTOM_RIGHT (ID_SPRITE_GROUND+6000)

#define ID_SPRITE_BACKGROUNDS_BIG_TREE_TOP_LEFT 71100
#define ID_SPRITE_BACKGROUNDS_BIG_TREE_TOP_RIGHT 71200
#define ID_SPRITE_BACKGROUNDS_BIG_TREE_BOTTOM_LEFT 71300
#define ID_SPRITE_BACKGROUNDS_BIG_TREE_BOTTOM_RIGHT 71400
#define ID_SPRITE_BACKGROUNDS_BIG_TREE_TOP_LEFT2 71500
#define ID_SPRITE_BACKGROUNDS_BIG_TREE_TOP_RIGHT2 71600
#define ID_SPRITE_BACKGROUNDS_BIG_TREE_MIDDLE 71700
#define ID_SPRITE_BACKGROUNDS_SMALL_TREE 72100
#define ID_SPRITE_BACKGROUNDS_CLOUD_TOP_LEFT 73100
#define ID_SPRITE_BACKGROUNDS_CLOUD_TOP_MIDDLE 73200
#define ID_SPRITE_BACKGROUNDS_CLOUD_TOP_RIGHT 73300
#define ID_SPRITE_BACKGROUNDS_CLOUD_BOTTOM_LEFT 73400
#define ID_SPRITE_BACKGROUNDS_CLOUD_BOTTOM_MIDDLE 73500
#define ID_SPRITE_BACKGROUNDS_CLOUD_BOTTOM_RIGHT 73600

#define ID_SPRITE_BOX 80000
#define ID_SPRITE_BOX_PINK (ID_SPRITE_BOX+1000)
#define ID_SPRITE_BOX_BLUE (ID_SPRITE_BOX+2000)
#define ID_SPRITE_BOX_GREEN (ID_SPRITE_BOX+3000)
#define ID_SPRITE_BOX_WHITE (ID_SPRITE_BOX+4000)
#define ID_SPRITE_BOX_SHADOW (ID_SPRITE_BOX+5000)

#define ID_SPRITE_BOX_PINK_TOP_LEFT (ID_SPRITE_BOX_PINK+100)
#define ID_SPRITE_BOX_PINK_TOP_MIDDLE (ID_SPRITE_BOX_PINK+200)
#define ID_SPRITE_BOX_PINK_TOP_RIGHT (ID_SPRITE_BOX_PINK+300)
#define ID_SPRITE_BOX_PINK_MIDDLE_LEFT (ID_SPRITE_BOX_PINK+400)
#define ID_SPRITE_BOX_PINK_MIDDLE_MIDDLE (ID_SPRITE_BOX_PINK+500)
#define ID_SPRITE_BOX_PINK_MIDDLE_RIGHT (ID_SPRITE_BOX_PINK+600)
#define ID_SPRITE_BOX_PINK_BOTTOM_LEFT (ID_SPRITE_BOX_PINK+700)
#define ID_SPRITE_BOX_PINK_BOTTOM_MIDDLE (ID_SPRITE_BOX_PINK+800)
#define ID_SPRITE_BOX_PINK_BOTTOM_RIGHT (ID_SPRITE_BOX_PINK+900)

#define ID_SPRITE_BOX_BLUE_TOP_LEFT (ID_SPRITE_BOX_BLUE+100)
#define ID_SPRITE_BOX_BLUE_TOP_MIDDLE (ID_SPRITE_BOX_BLUE+200)
#define ID_SPRITE_BOX_BLUE_TOP_RIGHT (ID_SPRITE_BOX_BLUE+300)
#define ID_SPRITE_BOX_BLUE_MIDDLE_LEFT (ID_SPRITE_BOX_BLUE+400)
#define ID_SPRITE_BOX_BLUE_MIDDLE_MIDDLE (ID_SPRITE_BOX_BLUE+500)
#define ID_SPRITE_BOX_BLUE_MIDDLE_RIGHT (ID_SPRITE_BOX_BLUE+600)
#define ID_SPRITE_BOX_BLUE_BOTTOM_LEFT (ID_SPRITE_BOX_BLUE+700)
#define ID_SPRITE_BOX_BLUE_BOTTOM_MIDDLE (ID_SPRITE_BOX_BLUE+800)
#define ID_SPRITE_BOX_BLUE_BOTTOM_RIGHT (ID_SPRITE_BOX_BLUE+900)

#define ID_SPRITE_BOX_GREEN_TOP_LEFT (ID_SPRITE_BOX_GREEN+100)
#define ID_SPRITE_BOX_GREEN_TOP_MIDDLE (ID_SPRITE_BOX_GREEN+200)
#define ID_SPRITE_BOX_GREEN_TOP_RIGHT (ID_SPRITE_BOX_GREEN+300)
#define ID_SPRITE_BOX_GREEN_MIDDLE_LEFT (ID_SPRITE_BOX_GREEN+400)
#define ID_SPRITE_BOX_GREEN_MIDDLE_MIDDLE (ID_SPRITE_BOX_GREEN+500)
#define ID_SPRITE_BOX_GREEN_MIDDLE_RIGHT (ID_SPRITE_BOX_GREEN+600)
#define ID_SPRITE_BOX_GREEN_BOTTOM_LEFT (ID_SPRITE_BOX_GREEN+700)
#define ID_SPRITE_BOX_GREEN_BOTTOM_MIDDLE (ID_SPRITE_BOX_GREEN+800)
#define ID_SPRITE_BOX_GREEN_BOTTOM_RIGHT (ID_SPRITE_BOX_GREEN+900)

#define ID_SPRITE_BOX_WHITE_TOP_LEFT (ID_SPRITE_BOX_WHITE+100)
#define ID_SPRITE_BOX_WHITE_TOP_MIDDLE (ID_SPRITE_BOX_WHITE+200)
#define ID_SPRITE_BOX_WHITE_TOP_RIGHT (ID_SPRITE_BOX_WHITE+300)
#define ID_SPRITE_BOX_WHITE_MIDDLE_LEFT (ID_SPRITE_BOX_WHITE+400)
#define ID_SPRITE_BOX_WHITE_MIDDLE_MIDDLE (ID_SPRITE_BOX_WHITE+500)
#define ID_SPRITE_BOX_WHITE_MIDDLE_RIGHT (ID_SPRITE_BOX_WHITE+600)
#define ID_SPRITE_BOX_WHITE_BOTTOM_LEFT (ID_SPRITE_BOX_WHITE+700)
#define ID_SPRITE_BOX_WHITE_BOTTOM_MIDDLE (ID_SPRITE_BOX_WHITE+800)
#define ID_SPRITE_BOX_WHITE_BOTTOM_RIGHT (ID_SPRITE_BOX_WHITE+900)

#define ID_SPRITE_BOX_SHADOW_TOP_RIGHT (ID_SPRITE_BOX_SHADOW+100)
#define ID_SPRITE_BOX_SHADOW_BOTTOM_LEFT (ID_SPRITE_BOX_SHADOW+200)
#define ID_SPRITE_BOX_SHADOW_BOTTOM_RIGHT (ID_SPRITE_BOX_SHADOW+300)
#define ID_SPRITE_BOX_SHADOW_MIDDLE (ID_SPRITE_BOX_SHADOW+400)

#define ID_SPRITE_COIN_BOX 90000
#define ID_SPRITE_COIN_BOX_ALIVE (ID_SPRITE_COIN_BOX+1000)
#define ID_SPRITE_COIN_BOX_ALIVE_1 (ID_SPRITE_COIN_BOX_ALIVE+100)
#define ID_SPRITE_COIN_BOX_ALIVE_2 (ID_SPRITE_COIN_BOX_ALIVE+200)
#define ID_SPRITE_COIN_BOX_ALIVE_3 (ID_SPRITE_COIN_BOX_ALIVE+300)
#define ID_SPRITE_COIN_BOX_ALIVE_4 (ID_SPRITE_COIN_BOX_ALIVE+400)
#define ID_SPRITE_COIN_BOX_DEAD (ID_SPRITE_COIN_BOX+2000)
#define ID_SPRITE_COIN_BOX_DEAD_1 (ID_SPRITE_COIN_BOX_DEAD+100)