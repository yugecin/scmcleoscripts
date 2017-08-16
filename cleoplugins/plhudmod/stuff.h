
/*
	from Plugin-SDK (Grand Theft Auto)
	Authors: GTA Community. See more here
	https://github.com/DK22Pac/plugin-sdk
*/

#define VALIDATE_SIZE(struc, size) static_assert(sizeof(struc) == size, "Invalid structure size of " #struc)

#define DrawBarChart(x, y, width, height, progress, progressAdd, drawPercentage, \
    drawBlackBorder, color, addColor) ((void (__cdecl *)(float, float, unsigned short,\
    unsigned char, float, signed char, unsigned char, unsigned char, int, int))0x728640)\
    (x, y, width, height, progress, progressAdd, drawPercentage, drawBlackBorder, color,\
    addColor);