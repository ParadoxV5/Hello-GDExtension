#include <gdextension_interface.h>

#ifndef HELLO_GDEXTENSION_H
#define HELLO_GDEXTENSION_H

typedef void* GDExtensionString;
typedef void* GDExtensionStringName;
typedef uint8_t GDExtensionVariant[24]; // Fetch size from `include/extension_api.json`

// GDExtension interface pointer
extern GDExtensionInterfaceGetProcAddress GetProcAddress;
// GDExtension API pointers
extern GDExtensionPtrConstructor stringName_from_String;
extern GDExtensionPtrDestructor destroy_StringName;
extern GDExtensionPtrDestructor destroy_String;
extern GDExtensionVariantFromTypeConstructorFunc variant_from_String;
// GDExtension pointers
extern GDExtensionInterfaceStringNewWithLatin1Chars string_new_with_latin1_chars;
extern GDExtensionInterfaceStringNewWithUtf8Chars string_new_with_utf8_chars;
extern GDExtensionInterfaceVariantDestroy variant_destroy;
// Library Functions
extern GDExtensionPtrUtilityFunction global_print;

GDExtensionStringName CString2StringName(const char* cstring);

void gdextension_print(const char* string);

__attribute__((unused)) GDExtensionBool hello_gdextension_main(
  GDExtensionInterfaceGetProcAddress p_get_proc_address,
  __attribute__((unused)) GDExtensionClassLibraryPtr p_library,
  GDExtensionInitialization* r_initialization
);

#endif
