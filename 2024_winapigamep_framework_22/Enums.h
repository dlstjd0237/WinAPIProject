#pragma once

enum class LAYER
{
	BACKGROUND,
	WarningPanel,
	Laser,
	GROUND,
	DEFAULT,
	PLAYER,
	ATTACKEFFECT,
	ENEMY,
	PROJECTILE,
	Effect,
	UI,
	LoadingPanel,
	END
};

enum class PEN_TYPE
{
	HOLLOW, RED, GREEN,
	BLUE, YELLOW, END
};

enum class BRUSH_TYPE
{
	HOLLOW, RED, GREEN,
	BLUE, YELLOW, END
};


enum class EVENT_TYPE
{
	CREATE_OBJECT,
	DELETE_OBJECT,
	SCENE_CHANGE,
	END,
};

enum class PLAYER_ANIM_TYPE
{
	IDLE,
	MOVE,
	JUMP,
	ATTACK
};

//enum class STATE
//{
//	IDLE,
//	MOVE,
//	JUMP,
//	ATTACK	
//};

