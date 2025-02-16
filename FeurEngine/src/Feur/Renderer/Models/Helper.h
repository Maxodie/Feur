#pragma once

struct aiVector3D;
struct aiColor4D;
struct aiQuaternion;
struct aiMatrix4x4;

ILDA_vector3f FE_AssimpToVec3(const struct aiVector3D* v);

ILDA_vector4f FE_AssimpToVec4(const struct aiColor4D* c);

ILDA_quat FE_AssimpToQuat(const struct aiQuaternion* q);

ILDA_matrix4x4 FE_AssimpToMat4(const struct aiMatrix4x4* from);
