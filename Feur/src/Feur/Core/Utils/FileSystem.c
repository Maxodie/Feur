#include "fepch.h"
#include "Feur/Core/Utils/FileSystem.h"
#include <sys/stat.h>

Bool FE_API FE_FileSystemExist(const char* path)
{
	struct stat fileInfo;
	return stat(path, &fileInfo) == 0;
}

Bool FE_API FE_FileSystemOpen(const char* path, FE_FileMode mode, FE_File* outFile)
{
	outFile->path = path;
	const char* cmode;

	switch (mode)
	{
	case FILE_MODE_READ:
		cmode = "r";
		break;
	case FILE_MODE_READ_BINARY:
		cmode = "rb";
		break;
	case FILE_MODE_WRITE:
		cmode = "w";
		break;
	case FILE_MODE_WRITE_BINARY:
		cmode = "wb";
		break;
	default:
		FE_CORE_LOG_ERROR("failed to use the file mode, 'FILE_MODE_READ' mode will be used by default");
		cmode = "r";
		break;
	}

	FILE* file = fopen(path, cmode);
	if (file == NULL)
	{
		FE_CORE_LOG_ERROR("failed to open file : '%s'", path);
		return FALSE;
	}

	outFile->handle = file;
	return TRUE;
}

Bool FE_API FE_FileSystemClose(FE_File* file)
{
	if (file != NULL && file->handle != NULL)
	{
		fclose(file->handle);
		file->handle = NULL;
		return TRUE;
	}

	FE_CORE_LOG_ERROR("file or file handle does not exist");
	return FALSE;
}

Bool FE_API FE_FileSystemGetSize(FE_File* file, SizeT* outSize)
{
	if (file != NULL && file->handle != NULL)
	{
		struct stat fileInfo;
		if (stat(file->path, &fileInfo) == 0)
		{
			*outSize = fileInfo.st_size;
			return TRUE;
		}
		else
		{
			FE_CORE_LOG_ERROR("failed to get file size");
		}

		/*if (fseek(file->handle, 0, SEEK_END) < 0)
		{
			FE_CORE_LOG_ERROR("failed to get file size");
			return FALSE;
		}
		*outSize = ftell(file->handle);

		rewind(file->handle);*/
		return TRUE;
	}

	FE_CORE_LOG_ERROR("file or file handle does not exist");
	return FALSE;
}

Bool FE_API FE_FileSystemReadLine(FE_File* file, Int32 maxLength, char** lbuff, Uint64* outLineLength)
{
	if (file != NULL && file->handle != NULL && lbuff && *lbuff && outLineLength > 0)
	{
		char* buff = *lbuff;
		if (fgets(buff, maxLength, file->handle) != 0)
		{
			*outLineLength = strlen(buff);
			return TRUE;
		}
	}

	FE_CORE_LOG_ERROR("failed to read line");
	return FALSE;
}

Bool FE_API FE_FileSystemWriteLine(FE_File* file, const char* text)
{
	if (file != NULL && file->handle != NULL)
	{
		Bool result = fputs(text + '\n', file->handle) != EOF;

		fflush(file->handle);
		return result;
	}

	FE_CORE_LOG_ERROR("failed to write line");
	return FALSE;
}

Bool FE_API FE_FileSystemRead(FE_File* file, SizeT dataSize, void* outData, SizeT* outBytesRead)
{
	if (file != NULL && file->handle != NULL && outBytesRead)
	{
		*outBytesRead = fread(outData, 1, dataSize, file->handle);
		if (*outBytesRead != dataSize)
		{ 
			FE_CORE_LOG_ERROR("failed to read file");
			return FALSE;
		}

		return TRUE;
	}

	FE_CORE_LOG_ERROR("failed to write line");
	return FALSE;
}

Bool FE_API FE_FileSystemReadAllBytes(FE_File* file, Byte* outBytes, SizeT* outBytesRead)
{
	if (file != NULL && file->handle != NULL)
	{
		SizeT fileSize = 0;
		if (!FE_FileSystemGetSize(file, &fileSize))
		{
			FE_CORE_LOG_ERROR("failed to read all bytes");
			return FALSE;
		}

		*outBytesRead = fread(outBytes, sizeof(Byte), fileSize, file->handle);

		//return *outBytesRead == fileSize;
		return TRUE;
	}

	FE_CORE_LOG_ERROR("failed to write line");
	return FALSE;
}

Bool FE_API FE_FileSystemReadAllText(FE_File* file, char* outText, SizeT* outBytesRead)
{
	if (file != NULL && file->handle != NULL && outBytesRead)
	{
		SizeT fileSize = 0;
		if (!FE_FileSystemGetSize(file, &fileSize))
		{
			FE_CORE_LOG_ERROR("failed to read all bytes");
			return FALSE;
		}

		*outBytesRead = fread(outText, 1, fileSize, file->handle);

		return *outBytesRead == fileSize;
	}

	FE_CORE_LOG_ERROR("failed to write line");
	return FALSE;
}
