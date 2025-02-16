#include "fepch.h"
#include "Feur/Renderer/Camera.h"

void FE_DECL FE_CameraInit(FE_Camera3D* cam, const ILDA_vector3f* pos, const ILDA_vector3f* worldUp, Float32 aspect, Float32 fov, Float32 zNear, Float32 zFar)
{
	cam->position = *pos;
	cam->model = ILDA_matrix4x4_identity;

	//cam->perspective.data[1][1] *= -1;

	cam->worldUp = *worldUp;
	//ILDA_vector3f target = { 0 };
	ILDA_vector3f target = { .x = pos->x, .y = pos->y, .z = pos->z + 1 };
	cam->view = ILDA_look_at(pos, &target, worldUp);
	//cam->view = ILDA_matrix4x4_identity;
	//am->view.data[0][0] = -1;
	//cam->view.data[3][2] = pos->z;

	FE_CameraSetPerspective(cam, aspect, fov, zNear, zFar);
}

void FE_DECL FE_CameraRotate(FE_Camera3D* cam, const ILDA_vector3f* axis, Float32 deg)
{
	ILDA_matrix4x4 rot = ILDA_rotation(ILDA_radians(deg), axis);
	ILDA_matrix4x4_mul_same(&cam->model, &rot);

	FE_CameraUpdateMVP(cam);
}

void FE_DECL FE_CameraMove(FE_Camera3D* cam, const ILDA_vector3f* movement)
{
	ILDA_vector3f_add(&cam->position, movement);
	FE_CameraCalculeView(cam, &cam->position, &cam->worldUp);

	FE_CameraUpdateMVP(cam);
}

void FE_DECL FE_CameraSetPerspective(FE_Camera3D* cam, Float32 aspect, Float32 fov, Float32 zNear, Float32 zFar)
{
	cam->fov = fov;
	cam->aspect = aspect;
	cam->zNear = zNear;
	cam->zFar = zFar;

	cam->perspective = ILDA_perspective(ILDA_radians(fov), aspect, zNear, zFar);

	FE_CameraUpdateMVP(cam);
}

void FE_DECL FE_CameraCalculeView(FE_Camera3D* cam, const ILDA_vector3f* pos, const ILDA_vector3f* worldUp)
{
	//ILDA_vector3f target = { .z = 0 };
	//cam->view = ILDA_look_at(pos, &target, worldUp);
	ILDA_vector3f target = { .x = pos->x, .y = pos->y, .z = pos->z + 1 };
	cam->view = ILDA_look_at(pos, &target, worldUp);/*
	cam->view = ILDA_matrix4x4_identity;
	cam->view.data[0][0] = -1;
	cam->view.data[3][2] = pos->z;
	cam->view.data[3][0] = -pos->x;*/

	FE_CameraUpdateMVP(cam);
}

void FE_DECL FE_CameraUpdateMVP(FE_Camera3D* cam)
{
	cam->mvp = ILDA_matrix4x4_identity;

	ILDA_matrix4x4_mul_same(&cam->mvp, &cam->model);
	ILDA_matrix4x4_mul_same(&cam->mvp, &cam->view);
	ILDA_matrix4x4_mul_same(&cam->mvp, &cam->perspective);
}
