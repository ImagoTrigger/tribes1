#ifndef __LOADER_H__
#define __LOADER_H__

#include "Sys.h"

void loader_init( );

void loader_startup_stub( );
void loader_cmdline_stub( );

void loader_startup( );
void loader_shutdown( );
void loader_startup_announce( );

void loader_endframe();

void loader_setstarted( bool started );
bool loader_started( );

#endif // __LOADER_H__
