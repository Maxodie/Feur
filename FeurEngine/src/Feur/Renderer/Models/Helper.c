#include "fepch.h"
#include "Feur/Renderer/Models/Helper.h"

#include <assimp/mesh.h>
#include <assimp/quaternion.h>
#include <assimp/matrix4x4.h>
#include <assimp/color4.h>

#include "ILDA_vector/ILDA_vector.h"
#include "ILDA_quaternion/ILDA_quaternion.h"
#include "ILDA_matrix/ILDA_matrix.h"

ILDA_vector3f FE_AssimpToVec3(const struct aiVector3D* v)
{
    return (ILDA_vector3f) { v->x, v->y, v->z };
}

ILDA_vector4f FE_AssimpToVec4(const struct aiColor4D* c)
{
    return (ILDA_vector4f) { c->r, c->g, c->b, c->a };
}

ILDA_quat FE_AssimpToQuat(const struct aiQuaternion* q)
{
    return (ILDA_quat) { q->w, q->x, q->y, q->w };
}

ILDA_matrix4x4 FE_AssimpToMat4(const struct aiMatrix4x4* from)
{
    ILDA_matrix4x4 to = { 0 };

    // the a, b, c, d in assimp is the row; the 1, 2, 3, 4 is the colomn
    to.data[0][0] = from->a1;
    to.data[1][0] = from->a2;
    to.data[2][0] = from->a3;
    to.data[3][0] = from->a4;

    to.data[0][1] = from->b1;
    to.data[1][1] = from->b2;
    to.data[2][1] = from->b3;
    to.data[3][1] = from->b4;

    to.data[0][2] = from->c1;
    to.data[1][2] = from->c2;
    to.data[2][2] = from->c3;
    to.data[3][2] = from->c4;

    to.data[0][3] = from->d1;
    to.data[1][3] = from->d2;
    to.data[2][3] = from->d3;
    to.data[3][3] = from->d4;

    return to;
}
