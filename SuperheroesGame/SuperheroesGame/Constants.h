#pragma once

namespace StringConstants {
	const int BUFF_SIZE = 24; //sizeof(heapString)
	const int DEF_CAPACITY = 32; 
}
namespace VectorConstants {
	const int DEF_CAPACITY = 16; 
}
namespace FileConstants {
	const char SYS_FILE_NAME[8] = "sys.dat";
	const char GAME_FILE_NAME[9] = "game.dat";
}

namespace GameConstants {
	const size_t START_MONEY = 50;
	const size_t TURN_CRITERIA = 5;
	const double MONEY_GAIN = 0.7;
}