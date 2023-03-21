#include "commonFunc.h"

uint8_t getGBType()
{
    switch (_cpu) {
	case 0x01:
		return 1; //DMG or SGB
		break;
	case 0xFF:
		return 2; //POCKET or SGB2
		break;
	case 0x11:
		return 3; //COLOR
		break;
	default:
		return 0; //OTHER
		break;
	}
}

// More CPU efficient delay
void PerformantDelay(uint8_t numLoops)
{
    for (uint8_t i = numLoops; i--;)
    {
        wait_vbl_done();
    }
}