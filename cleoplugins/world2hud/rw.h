#pragma once

struct RwV3D {
	float x;
	float y;
	float z;
};

struct CMATRIX {
	RwV3D one;
	float pad0;
	RwV3D two;
	float pad1;
	RwV3D three;
	float pad2;
	RwV3D four;
	float pad3;
};
