#ifndef HELLO_GDEXTENSION_H
#define HELLO_GDEXTENSION_H

typedef void* GDExtensionString;
typedef void* GDExtensionStringName;
typedef void* GDExtensionVariant;

// GDExtension interface pointer
extern const GDExtensionInterface* INTERFACE;
// GDExtension API pointers
extern GDExtensionPtrConstructor stringName_from_String;
extern GDExtensionPtrDestructor destroy_StringName;
extern GDExtensionPtrDestructor destroy_String;
extern GDExtensionVariantFromTypeConstructorFunc variant_from_String;
// Library Functions
extern GDExtensionPtrUtilityFunction global_print;

GDExtensionStringName CString2StringName(const char* cstring);

void gdextension_print(const char* string);

GDExtensionBool hello_gdextension_main(
  const GDExtensionInterface *p_interface,
  GDExtensionClassLibraryPtr p_library,
  GDExtensionInitialization *r_initialization
);

#endif
