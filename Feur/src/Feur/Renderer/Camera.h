#pragma once

typedef struct FE_Camera3D
{
	Float32 aspect;
	Float32 zNear;
	Float32 zFar;
	Float32 fov;

	ILDA_vector3f position;

	ILDA_vector3f worldUp;

	ILDA_matrix4x4 view;
	ILDA_matrix4x4 perspective;
	ILDA_matrix4x4 model;
	ILDA_matrix4x4 mvp;
} FE_Camera3D;

void FE_DECL FE_CameraInit(FE_Camera3D* cam, const ILDA_vector3f* pos, const ILDA_vector3f* worldUp, Float32 aspect, Float32 fov, Float32 zNear, Float32 zFar);
void FE_DECL FE_CameraRotate(FE_Camera3D* cam, const ILDA_vector3f* axis, Float32 deg);
void FE_DECL FE_CameraMove(FE_Camera3D* cam, const ILDA_vector3f* movement);

void FE_DECL FE_CameraSetPerspective(FE_Camera3D* cam, Float32 aspect, Float32 fov, Float32 zNear, Float32 zFar);

void FE_DECL FE_CameraCalculeView(FE_Camera3D* cam, const ILDA_vector3f* pos, const ILDA_vector3f* worldUp); 

void FE_DECL FE_CameraUpdateMVP(FE_Camera3D* cam);