#pragma once

//FE_Optional does not free any memory by himself, DO NOT modify value without FE_Optional functions
#define FE_Optional(type) struct { Bool hasValue; type value; }
//with 'fe_optional' an FE_Optional(type) and value of type 'type'
#define FE_OptionalSetValue(fe_optional, newValue) FE_OptionalSetValue_impl(&fe_optional.hasValue, (Byte*)&fe_optional.value, &newValue, sizeof(fe_optional.value))

void FE_API FE_OptionalSetValue_impl(Bool* hasValue, Byte* data, const void* value, SizeT dataSize);