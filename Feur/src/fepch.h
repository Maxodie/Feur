
#pragma once

#if defined(__linux) || defined(FE_PLATFORM_LINUX)
#	define HAVE_POSIX_TIMER
#	include <time.h>
#	ifdef CLOCK_MONOTONIC
#		define CLOCKID CLOCK_MONOTONIC
#	else
#		define CLOCKID CLOCK_REALTIME
#	endif
#	
#	include <unistd.h>
#elif defined(__APPLE__) || defined(FE_PLATFORM_MACOS)
#	define HAVE_MACH_TIMER
#	include <mach/mach_time.h>
#elif defined(_WIN32) || defined(FE_PLATFORM_WINDOWS)
#	define WIN32_LEAN_AND_MEAN
#	include <windows.h>
#endif

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include <limits.h>
//#include <time.h>

#include "ILDA_utils/ILDA_utils.h"
#include "ILDA_vector/ILDA_vector.h"
#include "ILDA_matrix/ILDA_matrix.h"
#include "ILDA_trigo/ILDA_trigo.h"

#include "Feur/Core/Core.h"
#include "Feur/Core/Log/Log.h"

#include "Feur/Debug/Benchmark.h"

#include "Feur/Core/Memory/MemoryAllocator.h"

#include "Feur/Core/Utils/List.h"
#include "Feur/Core/Utils/ByteFlag.h"
#include "Feur/Core/Utils/Optional.h"
#include "Feur/Core/Utils/FeurSort.h"
#include "Feur/Core/Utils/FeString.h"
#include "Feur/Core/Utils/FileSystem.h"

#include "Feur/Core/Input/KeyCode.h"
#include "Feur/Core/Window/Window.h"
#include "Feur/Event/Event.h"
#include "Feur/Core/Layer.h"

#include "Feur/Core/LayerStack.h"
#include "Feur/Nuklear/NuklearLayer.h"

#include "Feur/Renderer/Camera.h"
#include "Feur/Renderer/Mesh.h"
#include "Feur/Renderer/Buffers.h"
#include "Feur/Renderer/RendererAPI.h"
#include "Feur/Renderer/GraphicsContext.h"
#include "Feur/Renderer/Renderer.h"
#include "Feur/Renderer/Renderer2D.h"

#include "Feur/Core/Utils/ECS/ECS.h"
#include "Feur/Core/Utils/ECS/ECSSystems.h"

#include "Feur/Core/Application.h"