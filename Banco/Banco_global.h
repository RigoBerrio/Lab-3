#ifndef BANCO_GLOBAL_H
#define BANCO_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(BANCO_LIBRARY)
#  define BANCO_EXPORT Q_DECL_EXPORT
#else
#  define BANCO_EXPORT Q_DECL_IMPORT
#endif

#endif // BANCO_GLOBAL_H
