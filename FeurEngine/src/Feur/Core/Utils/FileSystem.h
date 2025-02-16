#pragma once

typedef enum FE_FileMode 
{
	FILE_MODE_READ,
	FILE_MODE_READ_BINARY,
	FILE_MODE_WRITE,
	FILE_MODE_WRITE_BINARY,
} FE_FileMode;

typedef struct FE_File
{
	void* handle;
	const char* path;
} FE_File;

Bool FE_DECL FE_FileSystemExist(const char* path);
Bool FE_DECL FE_FileSystemOpen(const char* path, FE_FileMode mode, FE_File* outFile);
Bool FE_DECL FE_FileSystemClose(FE_File* file);

Bool FE_DECL FE_FileSystemGetSize(FE_File* file, SizeT* outSize);
Bool FE_DECL FE_FileSystemReadLine(FE_File* file, Int32 maxLength, char** lbuff, Uint64* outLineLength);
Bool FE_DECL FE_FileSystemWriteLine(FE_File* file, const char* text);

Bool FE_DECL FE_FileSystemRead(FE_File* file, SizeT dataSize, void* outData, SizeT* outBytesRead);
Bool FE_DECL FE_FileSystemReadAllBytes(FE_File* file, Byte* outBytes, SizeT* outBytesRead);
Bool FE_DECL FE_FileSystemReadAllText(FE_File* file, char* outText, SizeT* outBytesRead);