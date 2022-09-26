#pragma once
enum class GAME
{
	LOGO,
	INTRO,
	INGAME,
	END,
};
enum class PLAYER
{
	Idle_L,
	Idle_R,
	RUN_R,
	RUN_L,
	ATTACK_R,
	ATTACK_L,
	MOVE_ATTACK_L,
	MOVE_ATTACK_R,
	JUMP_UP_R,
	JUMP_UP_L,
	JUMP_DOWN_R,
	JUMP_DOWN_L,
	DEAD_R,
	DEAD_L
};
enum class SOUND
{
	BGM_MAIN,
	BGM_RAINY,
	BGM_TITLE,

	PLAYER_ATTACK,
	PLAYER_HIT,
	PLAYER_JUMP,
	PLAYER_RUN,
	PLAYER_SHADOW,
	PLAYER_SKILL,

	ENEMY_ATTACK,
	ENEMY_HIT1,
	ENEMY_HIT2,
	ENEMY_HIT3,
	ENEMY_READY 
};
enum  class MONSTER
{
	RUN_R,
	RUN_L,
	DEAD_R,
	DEAD_L,
	HIT_R,
	HIT_L,
	ATTACK_R,
	ATTACK_L,
	IDLE_R,
	IDLE_L,
	ATTACK_READY_R,
	ATTACK_READY_L,
};
enum class M_STATE
{
	RUN,
	IDLE,
	FIGHTIN,
	SEARCH,
	ATTACK,
	HIT,
	DEAD
};
enum class IMPACT
{
	Blood_01 = 0,
	Blood_02 = 1,
	Blood_03 = 2,
	Blood_R,
	Blood_L,

	HIT_01,
	HIT_02,
	HIT_03,

	DUST_R,
	DUST_L,

	Lightning01,
	Lightning02,
	Lightning03,
	Lightning04
};


