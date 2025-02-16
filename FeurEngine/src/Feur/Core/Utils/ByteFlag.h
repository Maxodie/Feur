#pragma once

typedef struct { FE_List_impl impl; Byte* data; } FE_ByteFlag;

void FE_DECL FE_FlagInit(FE_ByteFlag* flag);
void FE_DECL FE_FlagDestroy(FE_ByteFlag* flag);
void FE_DECL FE_FlagReset(FE_ByteFlag* flag);

void FE_DECL FE_FlagSet(FE_ByteFlag* flag, Uint64 newFlag);
Bool FE_DECL FE_FlagExist(FE_ByteFlag* flag, Uint64 searchedFlag);
void FE_DECL FE_FlagRemove(FE_ByteFlag* flag, Uint64 flagToRemove);

void FE_DECL FE_FlagPrint(FE_ByteFlag* flag); 