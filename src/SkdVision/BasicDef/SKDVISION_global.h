#ifndef QTLIB_GLOBAL_H
#define QTLIB_GLOBAL_H

//#include <QtCore/qglobal.h>

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
#define SKDVISION_DECL_EXPORT     __declspec(dllexport)
#define SKDVISION_DECL_IMPORT     __declspec(dllimport)
#else
#define SKDVISION_DECL_EXPORT
#define SKDVISION_DECL_IMPORT
#endif

#if defined(SKDVISION_LIBRARY)
#define SKDVISION_EXPORT SKDVISION_DECL_EXPORT
#else
#define SKDVISION_EXPORT SKDVISION_DECL_IMPORT
#endif


//#define  USE_INTERFACE_CV_OR_CPP
//#define  USE_INTERFACE_CV_OR_CPP




#endif // QTLIB_GLOBAL_H
