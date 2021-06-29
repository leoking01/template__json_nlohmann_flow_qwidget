#ifndef QTLIB_GLOBAL_H
#define QTLIB_GLOBAL_H



#ifdef __cplusplus
#  include <type_traits>
#  include <cstddef>
#  include <utility>
#endif
#ifndef __ASSEMBLER__
#  include <assert.h>
#  include <stddef.h>
#endif

#ifdef   PLATFORM_MSVC
#define WMSVISION_DECL_EXPORT     __declspec(dllexport)
#define WMSVISION_DECL_IMPORT     __declspec(dllimport)
#else
#define WMSVISION_DECL_EXPORT
#define WMSVISION_DECL_IMPORT
#endif

#if defined(WMSVISION_LIBRARY)
#define WMSVISION_EXPORT WMSVISION_DECL_EXPORT
#else
#define WMSVISION_EXPORT WMSVISION_DECL_IMPORT
#endif



#endif // QTLIB_GLOBAL_H
