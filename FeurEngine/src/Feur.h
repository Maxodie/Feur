#pragma once


#include <stdint.h>
#include <time.h>

//Math
#include "ILDA_utils/ILDA_utils.h"
#include "ILDA_vector/ILDA_vector.h"
#include "ILDA_matrix/ILDA_matrix.h"
#include "ILDA_trigo/ILDA_trigo.h"

//Core
#include "Feur/Core/Core.h"
#include "Feur/Core/Log/Log.h"

//Memory
#include "Feur/Core/Memory/MemoryAllocator.h"

//Benchmark
#include "Feur/Debug/Benchmark.h" //maybe remove debug stuff from the header

//Window
#include "Feur/Core/Window/Window.h"

//Utils
#include "Feur/Core/Utils/List.h"
#include "Feur/Core/Utils/ByteFlag.h"
#include "Feur/Core/Utils/FeString.h"
#include "Feur/Core/Utils/FeurSort.h"
#include "Feur/Core/Utils/FileSystem.h"
#include "Feur/Core/Utils/Optional.h"

//Renderer
#include "Feur/Renderer/Camera.h"
#include "Feur/Renderer/Shader.h"
#include "Feur/Renderer/Models/Mesh.h"
#include "Feur/Renderer/Buffers.h"
#include "Feur/Renderer/RendererAPI.h"

//ECS
#include "Feur/Core/Utils/ECS/ECS.h"

//Renderer2D/3D
#include "Feur/Renderer/Renderer2D.h"
#include "Feur/Renderer/Renderer3D.h"


//Inputs
#include "Feur/Core/Input/KeyCode.h"
#include "Feur/Core/Input/Input.h"

//Event
#include "Feur/Event/Event.h"

//Layer
#include "Feur/Core/Layer.h"
#include "Feur/Core/LayerStack.h"
#include "Feur/Nuklear/NuklearLayer.h"

//ECS
#include "Feur/Core/Utils/ECS/ECSSystems.h"

//Application
#include "Feur/Core/Application.h"

//Entry point
#include "Feur/Core/EntryPoint.h"

