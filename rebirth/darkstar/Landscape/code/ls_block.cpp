//����������������������������������������������������������������������������
//��   
//��  $Workfile:   LS_Block.cpp  $
//��  $Version$
//��  $Revision:   1.00  $
//��    
//��  DESCRIPTION:
//��        Fills a grid block height map from stack(0) and sub-region
//��        
//��  (c) Copyright 1996, 1997, Dynamix Inc.   All rights reserved.
//�� 
//����������������������������������������������������������������������������

#include "ls.h"      // base class defined

// fills the grd height map from the sub region of stack[0] specified
// by _box.  this assumes that box is likely to be xy+1

void  LandScape::setGrdHeightMap( float *_pGrdHeightMap, Box2I& _box )
{
   if (!stack.size())
      return;

   int mask = stack[0]->size - 1;
   Point2I start = _box.fMin;
   Point2I end = _box.fMax;
   
   for ( int y=start.y; y < end.y; y++ )
   {
      float *basePtr = stack[0]->real + ((y-1) & mask) * stack[0]->size;

      for ( int x=start.x; x < end.x; x++ )
         *_pGrdHeightMap++ = *(basePtr + ((x) & mask));
   }
}
