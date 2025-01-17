#pragma once

ILDA_vector3f FE_DECL FE_AssimpToVec3(const struct aiVector3D* v);
ILDA_vector4f FE_DECL FE_AssimpToVec4(const struct aiColor4D* c);
ILDA_quat FE_DECL FE_AssimpToQuat(const struct aiQuaternion* q);
ILDA_matrix4x4 FE_DECL FE_AssimpToMat4(const struct aiMatrix4x4* from);