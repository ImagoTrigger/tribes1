#==============================================================================
#      
#    $Workfile:   makefile.mak  $
#    $Version$
#    $Revision:   1.1  $
#      
#    DESCRIPTION:
#      
#    (c) Copyright 1995, Dynamix Inc.   All rights reserved.
#      
#==============================================================================

LIBdest    =.
OBJdest    =obj

%if !%exists($(PhoenixMake)\Builtins.Mak)
   %abort 1 Error: Environment var "PhoenixMake" not set. Set to Phoenix\Makes directory
   @-md $(var)
%endif
%include <$(PHOENIXMAKE)\builtins.mak>

%set PRECOMPILED_HEADER=

TexMix : TexMix.exe

#==============================================================================

%ifdef CG32
CPPFLAGS += -vG
%endif

TexMix.exe:                         \
%ifdef CG32
   c:\bc5\lib\cg32.lib              \
%endif
   $(BuildPrefix)Core.lib           \
   $(BuildPrefix)gfxio.lib          \
   $(BuildPrefix)ml.lib          \
   \
   TexMix.obj                    
   %do %.exe CONSOLE=yes
   %if %exist($(PhoenixTool))
      @xcopy /Q $(.TARGET) $(PhoenixTool)
   %endif

