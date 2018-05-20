#include <time.h>
#include <windows.h>
#include <stdio.h>
#include "Block.h"
#include "Util.h"
#include "Constant.h"

#define BLOCK_EXAMPLES_SIZE 6

const static Point blockExamples[BLOCK_EXAMPLES_SIZE][POSITIONS_SIZE][POSITIONS_SIZE] = {
	//けけけけ
	{
		{ { 0, 5 }, { 0, 6 }, { 0, 7 }, { 0, 8 } },
		{ { -2, 6 }, { -1, 6 }, { 0, 6 }, { 1, 6 } },
		{ { 0, 5 }, { 0, 6 }, { 0, 7 }, { 0, 8 } },
		{ { -2, 6 }, { -1, 6 }, { 0, 6 }, { 1, 6 } }
	},
	//    け
	//けけけ
	{
		{ { 0, 8 }, { 1, 6 }, { 1, 7 }, { 1, 8 } },
		{ { -1, 7 }, { 0, 7 }, { 1, 7 }, { 1, 8 } },
		{ { 0, 6 }, { 0, 7 }, { 0, 8 }, { 1, 6 } },
		{ { -1, 6 }, { -1, 7 }, { 0, 7 }, { 1, 7 } }
	},
	//  けけ
	//けけ
	{
		{ { 0, 7 }, { 0, 8 }, { 1, 6 }, { 1, 7 } },
		{ { -1, 6 }, { 0, 6 }, { 0, 7 }, { 1, 7 } },
		{ { 0, 7 }, { 0, 8 }, { 1, 6 }, { 1, 7 } },
		{ { -1, 6 }, { 0, 6 }, { 0, 7 }, { 1, 7 } }
	},
	//けけ
	//  けけ
	{
		{ { 0, 6 }, { 0, 7 }, { 1, 7 }, { 1, 8 } },
		{ { -1, 8 }, { 0, 8 }, { 0, 7 }, { 1, 7 } },
		{ { 0, 6 }, { 0, 7 }, { 1, 7 }, { 1, 8 } },
		{ { -1, 8 }, { 0, 8 }, { 0, 7 }, { 1, 7 } }
	},
	//け
	//けけけ
	{
		{ { 0, 6 }, { 1, 6 }, { 1, 7 }, { 1, 8 } },
		{ { -1, 8 }, { -1, 7 }, { 0, 7 }, { 1, 7 } },
		{ { 0, 6 }, { 0, 7 }, { 0, 8 }, { 1, 8 } },
		{ { -1, 7 }, { 0, 7 }, { 1, 7 }, { 1, 6 } }
	},
	//けけ
	//けけ
	{
		{ { 0, 6 }, { 0, 7 }, { 1, 6 }, { 1, 7 } },
		{ { 0, 6 }, { 0, 7 }, { 1, 6 }, { 1, 7 } },
		{ { 0, 6 }, { 0, 7 }, { 1, 6 }, { 1, 7 } },
		{ { 0, 6 }, { 0, 7 }, { 1, 6 }, { 1, 7 } }
	}
};

static Block _Block_MoveToDown(Block block);
static Block _Block_MoveToLeft(Block block);
static Block _Block_MoveToRight(Block block);
static Block _Block_RotateRight(Block block);

Block Block_Make(int isFirst, Block block){
	int i;
	int j;
	srand((unsigned int)time(NULL));
	if (isFirst){
		block.current = rand() % BLOCK_EXAMPLES_SIZE;
	}
	else{
		block.current = block.next;
	}
	for (i = 0; i < POSITIONS_SIZE; i++){
		for (j = 0; j < POSITIONS_SIZE; j++){
			block.positions[i][j] = blockExamples[block.current][i][j];
		}
	}
	block.next = rand() % BLOCK_EXAMPLES_SIZE;
	block.direction = UP;
	return block;
}

Block Block_Move(Block block, int direction){
	switch (direction){
	case LEFT:
		return _Block_MoveToLeft(block);
	case RIGHT:
		return _Block_MoveToRight(block);
	case DOWN:
		return _Block_MoveToDown(block);
	case UP:
		return _Block_RotateRight(block);
	}
	return _Block_MoveToDown(block);
}

Point* Block_GetPositions(Block block){
	return block.positions[block.direction];
}

void Block_PrintNext(Block block, int x, int y){
	CursorUtil_GotoXY(x, y);
	printf("Next block : ");
	x += 3;
	y += 2;
	CursorUtil_GotoXY(x, y++);
	switch (block.next){
	case 0:
		printf("＝＝＝＝");
		CursorUtil_GotoXY(x, y++);
		printf("        ");
		break;
	case 1:
		printf("      ＝");
		CursorUtil_GotoXY(x, y++);
		printf("  ＝＝＝");
		break;
	case 2:
		printf("    ＝＝");
		CursorUtil_GotoXY(x, y++);
		printf("  ＝＝  ");
		break;
	case 3:
		printf("  ＝＝  ");
		CursorUtil_GotoXY(x, y++);
		printf("    ＝＝");
		break;
	case 4:
		printf("＝      ");
		CursorUtil_GotoXY(x, y++);
		printf("＝＝＝  ");
		break;
	case 5:
		printf("  ＝＝  ");
		CursorUtil_GotoXY(x, y++);
		printf("  ＝＝  ");
		break;
	}
}

static Block _Block_MoveToDown(Block block){
	int i;
	int j;
	for (i = 0; i < POSITIONS_SIZE; i++){
		for (j = 0; j < POSITIONS_SIZE; j++){
			block.positions[i][j].y++;
		}
	}
	return block;
}

static Block _Block_MoveToLeft(Block block){
	int i;
	int j;
	for (i = 0; i < POSITIONS_SIZE; i++){
		for (j = 0; j < POSITIONS_SIZE; j++){
			block.positions[i][j].x--;
		}
	}
	return block;
}

static Block _Block_MoveToRight(Block block){
	int i;
	int j;
	for (i = 0; i < POSITIONS_SIZE; i++){
		for (j = 0; j < POSITIONS_SIZE; j++){
			block.positions[i][j].x++;
		}
	}
	return block;
}

static Block _Block_RotateRight(Block block){
	block.direction = (block.direction + 1) % POSITIONS_SIZE;
	return block;
}
