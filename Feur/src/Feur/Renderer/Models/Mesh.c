#include "fepch.h"
#include "Feur/Renderer/Models/Mesh.h"
#include "Feur/Renderer/Models/Helper.h"

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

Bool FE_DECL FE_ModelLoad(const char* path, FE_Model3D* outModel)
{
	const struct aiScene* const scene = aiImportFile(path,
        aiProcess_Triangulate | aiProcess_GenSmoothNormals |
        aiProcess_CalcTangentSpace | aiProcess_OptimizeMeshes |
        aiProcess_OptimizeGraph | aiProcess_ValidateDataStructure |
        aiProcess_ImproveCacheLocality | aiProcess_FixInfacingNormals |
        aiProcess_GenUVCoords | aiProcess_FlipUVs
    );

    if (scene == NULL)
    {
        FE_CORE_LOG_ERROR("failed to load assimp scene : %s", path);
        outModel = NULL;
        return FALSE;
    }

    FE_CORE_LOG_DEBUG("Starting the loading of the model : %s", path);

    FE_ListInit(outModel->meshes);
    FE_ListReserve(outModel->meshes, scene->mNumMeshes);

    FE_Mesh meshToAdd = { 0 };
    FE_ListInit(meshToAdd.indices);
    FE_ListInit(meshToAdd.vertices);

    FE_Vertex3D vertexToAdd = { 0 };

    const struct aiMesh* mesh;
    struct aiVector3D vertex;
    struct aiFace face;

    for (Uint32 i = 0; i < scene->mNumMeshes; i++)
    {
         mesh = scene->mMeshes[i];

        // increase capacity if required
        if (meshToAdd.vertices.impl.capacity < meshToAdd.vertices.impl.count + mesh->mNumVertices)
        {
            FE_ListReserve(meshToAdd.vertices, (mesh->mNumVertices + meshToAdd.vertices.impl.count) - meshToAdd.vertices.impl.capacity);
        }

        // load vertices
        for (Uint32 j = 0; j < mesh->mNumVertices; j++) 
        {
            vertex = mesh->mVertices[j];

            // load normals
            if (mesh->mNormals != NULL)
            {
                vertexToAdd.normal = FE_AssimpToVec3(&mesh->mNormals[j]);
            }

            vertexToAdd.position = FE_AssimpToVec3(&vertex);

            FE_ListPush(meshToAdd.vertices, vertexToAdd);
        }

        // load indices
        for (Uint32 j = 0; j < mesh->mNumFaces; j++) 
        {
            face = mesh->mFaces[j];

            // increase capacity if required
            if (meshToAdd.indices.impl.capacity < meshToAdd.indices.impl.count + face.mNumIndices)
            {
                FE_ListReserve(meshToAdd.indices, (face.mNumIndices + meshToAdd.indices.impl.count) - meshToAdd.indices.impl.capacity);
            }

            for (Uint32 k = 0; k < face.mNumIndices; k++) 
            {
                FE_ListPush(meshToAdd.indices, face.mIndices[k]);
            }
        }

        FE_ListPush(outModel->meshes, meshToAdd);
        FE_ListRemoveAll(meshToAdd.indices);
        FE_ListRemoveAll(meshToAdd.vertices);
    }

    aiReleaseImport(scene);

    return TRUE;
}

void FE_DECL FE_ModelFree(FE_Model3D* outModel)
{ 
    for (SizeT i = 0; i < outModel->meshes.impl.count; i++)
    {
        FE_ListClear(outModel->meshes.data[i].indices);
        FE_ListClear(outModel->meshes.data[i].vertices);
    }

    FE_ListClear(outModel->meshes);
}