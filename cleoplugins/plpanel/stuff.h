
/*
	from Plugin-SDK (Grand Theft Auto)
	Authors: GTA Community. See more here
	https://github.com/DK22Pac/plugin-sdk
*/

#define STATIC_ASSERT(E) typedef char __static_assert_[(E)?1:-1]
#define EXPECT_SIZE(S,SIZE) STATIC_ASSERT(sizeof(S)==(SIZE))

#define DrawBarChart(x, y, width, height, progress, progressAdd, drawPercentage, \
    drawBlackBorder, color, addColor) ((void (__cdecl *)(float, float, unsigned short,\
    unsigned char, float, signed char, unsigned char, unsigned char, int, int))0x728640)\
    (x, y, width, height, progress, progressAdd, drawPercentage, drawBlackBorder, color,\
    addColor);