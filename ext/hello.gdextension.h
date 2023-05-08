#ifndef HELLO_GDEXTENSION_H
#define HELLO_GDEXTENSION_H

typedef void* GDExtensionString;
typedef void* GDExtensionStringName;

// GDExtension interface pointer
extern const GDExtensionInterface* INTERFACE;
// GDExtension API pointers
extern GDExtensionPtrConstructor StringName_from_String;
extern GDExtensionPtrDestructor destroy_StringName;
extern GDExtensionPtrDestructor destroy_String;
// Library Functions
extern GDExtensionPtrUtilityFunction global_print;

void* CString2StringName(const char* string);

GDExtensionBool hello_gdextension_main(
  const GDExtensionInterface *p_interface,
  GDExtensionClassLibraryPtr p_library,
  GDExtensionInitialization *r_initialization
);

#endif
