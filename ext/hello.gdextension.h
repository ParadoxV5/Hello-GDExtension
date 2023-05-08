#ifndef HELLO_GDEXTENSION_H
#define HELLO_GDEXTENSION_H

typedef void* GDExtensionStringName;
void* CString2StringName(const char* string);

GDExtensionBool hello_gdextension_main(
  const GDExtensionInterface *p_interface,
  GDExtensionClassLibraryPtr p_library,
  GDExtensionInitialization *r_initialization
);

#endif
