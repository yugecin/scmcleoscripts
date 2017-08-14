
// from plugin-sdk https://github.com/DK22Pac/plugin-sdk
#define VALIDATE_SIZE(struc, size) static_assert(sizeof(struc) == size, "Invalid structure size of " #struc)