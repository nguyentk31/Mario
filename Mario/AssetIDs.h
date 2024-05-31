#pragma once

//
// This file contains all IDs of game assets 
//

#define ID_TEX_MARIO 0
#define ID_TEX_ENEMY 10
#define ID_TEX_MISC 20
#define ID_TEX_STAGE_TILES 30
#define ID_TEX_LEVEL_ITEMS 40

#define OBJECT_TYPE_BACKGROUNDS 0
#define OBJECT_TYPE_MARIO	1
#define OBJECT_TYPE_BRICK	2
#define OBJECT_TYPE_GOOMBA	3
#define OBJECT_TYPE_COIN 4
#define OBJECT_TYPE_VENUS_FIRE_TRAP 6
#define OBJECT_TYPE_BOX 8
#define OBJECT_TYPE_QUESTION_BLOCK 9
#define OBJECT_TYPE_MUSHROOM 10
#define OBJECT_TYPE_FIREBALL 11
#define OBJECT_TYPE_KOOPA_TROOPA 12

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

#define ID_SPRITE_GOOMBA 30000
#define ID_ANI_GOOMBA_WALK (ID_SPRITE_GOOMBA + 1000)
#define ID_ANI_GOOMBA_DIE (ID_SPRITE_GOOMBA + 2000)

#define ID_SPRITE_COIN 40000
#define ID_ANI_COIN 40000

#define ID_SPRITE_VENUS_FIRE_TRAP 60000
#define VFT_ANI_SPR_DOWN_LEFT 61100
#define VFT_ANI_SPR_UP_LEFT 61300
#define VFT_ANI_SPR_UP_RIGHT 61500
#define VFT_ANI_SPR_DOWN_RIGHT 61700

#define ID_SPRITE_BOX 80000
#define ID_SPRITE_BOX_PINK (ID_SPRITE_BOX+1000)
#define ID_SPRITE_BOX_BLUE (ID_SPRITE_BOX+2000)
#define ID_SPRITE_BOX_GREEN (ID_SPRITE_BOX+3000)
#define ID_SPRITE_BOX_WHITE (ID_SPRITE_BOX+4000)
#define ID_SPRITE_BOX_SHADOW (ID_SPRITE_BOX+9000)

#define ID_SPRITE_QUESTION_BLOCK 90000
#define ID_ANI_QUESTION_BLOCK_ALIVE (ID_SPRITE_QUESTION_BLOCK + 1000)
#define ID_ANI_QUESTION_BLOCK_DEAD (ID_SPRITE_QUESTION_BLOCK + 2000)

#define ID_SPRITE_MUSHROOM 11000

#define ID_ANI_FIREBALL 110000

#define ID_SPRITE_KOOPA_TROOPA 120000
#define ID_ANI_KOOPA_TROOPA_WALKING_RIGHT (ID_SPRITE_KOOPA_TROOPA + 100)
#define ID_ANI_KOOPA_TROOPA_WALKING_LEFT (ID_SPRITE_KOOPA_TROOPA + 200)
#define ID_ANI_KOOPA_TROOPA_SHELL (ID_SPRITE_KOOPA_TROOPA + 300)
#define ID_ANI_KOOPA_TROOPA_ROLLING (ID_SPRITE_KOOPA_TROOPA + 400)
#define ID_ANI_KOOPA_TROOPA_REVIVE (ID_SPRITE_KOOPA_TROOPA + 500)
