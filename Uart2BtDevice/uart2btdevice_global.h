#ifndef UART2BTDEVICE_GLOBAL_H
#define UART2BTDEVICE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(UART2BTDEVICE_LIBRARY)
#  define UART2BTDEVICESHARED_EXPORT Q_DECL_EXPORT
#else
#  define UART2BTDEVICESHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // UART2BTDEVICE_GLOBAL_H
