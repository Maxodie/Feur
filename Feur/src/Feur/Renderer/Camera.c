#include "fepch.h"
#include "Feur/Renderer/Camera.h"

void FE_DECL FE_CameraInit(FE_Camera3D* cam, const ILDA_vector3f* pos, const ILDA_vector3f* worldUp, Float32 aspect, Float32 fov, Float32 zNear, Float32 zFar)
{
	cam->position = *pos;
	cam->rotation = ILDA_matrix4x4_identity;
	cam->perspective = ILDA_perspective(ILDA_radians(fov), aspect, zNear, zFar);
	cam->perspective.data[1][1] *= -1;

	cam->worldUp = *worldUp;
	//ILDA_vector3f target = { 0 };
	//cam->view = ILDA_look_at(pos, &target, worldUp);
	cam->view = ILDA_matrix4x4_identity;
	cam->view.data[0][0] = -1;
	cam->view.data[3][2] = pos->z;
}

void FE_DECL FE_CameraRotate(FE_Camera3D* cam, const ILDA_vector3f* axis, Float32 deg)
{
	ILDA_matrix4x4 rot = ILDA_rotation(ILDA_radians(deg), axis);
	ILDA_matrix4x4_mul_same(&cam->rotation, &rot);
}

void FE_DECL FE_CameraMove(FE_Camera3D* cam, const ILDA_vector3f* movement)
{
	ILDA_vector3f_add(&cam->position, movement);
	FE_CameraCalculeView(cam, &cam->position, &cam->worldUp);
}

void FE_DECL FE_CameraCalculeView(FE_Camera3D* cam, const ILDA_vector3f* pos, const ILDA_vector3f* worldUp)
{
	//ILDA_vector3f target = { .z = 0 };
	//cam->view = ILDA_look_at(pos, &target, worldUp);
	cam->view = ILDA_matrix4x4_identity;
	cam->view.data[0][0] = -1;
	cam->view.data[3][2] = pos->z;
}
