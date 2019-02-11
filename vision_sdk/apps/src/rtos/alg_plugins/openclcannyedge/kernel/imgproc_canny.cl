/*
 *******************************************************************************
 *
 * Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 *
 *******************************************************************************
 */
// Smoothing perpendicular to the derivative direction with a triangle filter
// only support 3x3 Sobel kernel
// h (-1) =  1, h (0) =  2, h (1) =  1
// h'(-1) = -1, h'(0) =  0, h'(1) =  1
// thus sobel 2D operator can be calculated as:
// h'(x, y) = h'(x)h(y) for x direction
//
// src		input 8bit single channel image data
// dx_buf	output dx buffer
// dy_buf	output dy buffer

__kernel
void
//__attribute__((reqd_work_group_size(16,16,1)))
calcSobelRowPass
(
    __global const uchar16 * restrict src,
    __global  short16 * restrict dx_buf,
    __global  short16 * restrict dy_buf,
    int src_step,
    int dx_buf_step,
    int dy_buf_step
)
{

    src_step  /= sizeof(*src);
    dx_buf_step   /= sizeof(*dx_buf);
    dy_buf_step   /= sizeof(*dy_buf);


    int gidx = get_global_id(0);
    int gidy = get_global_id(1);
	char4 mask0 = (char4)(-1,0,1,0);
	char4 mask1 = (char4)(1,2,1,0);

	__global short16 *dx = dx_buf + gidx + gidy * (dx_buf_step);
	__global short16 *dy = dy_buf + gidx + gidy * (dy_buf_step);
	__global const uchar16 *in = src+ gidx + gidy * (src_step);
	uchar16 in1 = *(in+1);
    short16 src00,src01,src02;
	uchar16 src0 = *in;
	uchar16 src1;

    short s0,s1,s2,s3,s4,s5,s6,s7,s8,s9,s10,s11,s12,s13,s14,s15;

    s0 = _dotpsu4((int)mask0,(uint)src0.s0123);
    s1 = _dotpsu4((int)mask0,(uint)src0.s1234);
    s2 = _dotpsu4((int)mask0,(uint)src0.s2345);
    s3 = _dotpsu4((int)mask0,(uint)src0.s3456);
    s4 = _dotpsu4((int)mask0,(uint)src0.s4567);
    s5 = _dotpsu4((int)mask0,(uint)src0.s5678);
    s6 = _dotpsu4((int)mask0,(uint)src0.s6789);
    s7 = _dotpsu4((int)mask0,(uint)src0.s789a);
    s8 = _dotpsu4((int)mask0,(uint)src0.s89ab);
    s9 = _dotpsu4((int)mask0,(uint)src0.s9abc);
    s10 = _dotpsu4((int)mask0,(uint)src0.sabcd);
    s11 = _dotpsu4((int)mask0,(uint)src0.sbcde);
    s12 = _dotpsu4((int)mask0,(uint)src0.scdef);
    s13 = _dotpsu4((int)mask0,(uint)((uchar4)(src0.sdef,in1.s0)));
    s14 = _dotpsu4((int)mask0,(uint)((uchar4)(src0.sef,in1.s01)));
    s15 = _dotpsu4((int)mask0,(uint)((uchar4)(src0.sf,in1.s012)));

    *dx = (short16)(s0,s1,s2,s3,s4,s5,s6,s7,s8,s9,s10,s11,s12,s13,s14,s15);

    s0 = _dotpsu4((uint)mask1,(uint)src0.s0123);
    s1 = _dotpsu4((int)mask1,(uint)src0.s1234);
    s2 = _dotpsu4((int)mask1,(uint)src0.s2345);
    s3 = _dotpsu4((int)mask1,(uint)src0.s3456);
    s4 = _dotpsu4((int)mask1,(uint)src0.s4567);
    s5 = _dotpsu4((int)mask1,(uint)src0.s5678);
    s6 = _dotpsu4((int)mask1,(uint)src0.s6789);
    s7 = _dotpsu4((int)mask1,(uint)src0.s789a);
    s8 = _dotpsu4((int)mask1,(uint)src0.s89ab);
    s9 = _dotpsu4((int)mask1,(uint)src0.s9abc);
    s10 = _dotpsu4((int)mask1,(uint)src0.sabcd);
    s11 = _dotpsu4((int)mask1,(uint)src0.sbcde);
    s12 = _dotpsu4((int)mask1,(uint)src0.scdef);
    s13 = _dotpsu4((int)mask1,(uint)((uchar4)(src0.sdef,in1.s0)));
    s14 = _dotpsu4((int)mask1,(uint)((uchar4)(src0.sef,in1.s01)));
    s15 = _dotpsu4((int)mask1,(uint)((uchar4)(src0.sf,in1.s012)));

    *dy = (short16)(s0,s1,s2,s3,s4,s5,s6,s7,s8,s9,s10,s11,s12,s13,s14,s15);
}

// calculate the magnitude of the filter pass combining both x and y directions
// This is the buffered version(3x3 sobel)
//
// dx_buf		dx buffer, calculated from calcSobelRowPass
// dy_buf		dy buffer, calculated from calcSobelRowPass
// dx			direvitive in x direction output
// dy			direvitive in y direction output
// mag			magnitude direvitive of xy output
__kernel
void
//__attribute__((reqd_work_group_size(16,16,1)))
calcMagnitude_buf
(
    __global const short8 * restrict dx_buf,
    __global const short8 * restrict dy_buf,
    __global short8 * restrict dx,
    __global short8 * restrict dy,
    __global short8 * restrict mag,
    int dx_buf_step,
    int dy_buf_step,
    int dx_step,
    int dy_step,
    int mag_step

)
{
    dx_buf_step    /= sizeof(*dx_buf);
    dy_buf_step    /= sizeof(*dy_buf);
    dx_step    /= sizeof(*dx);
    dy_step    /= sizeof(*dy);
    mag_step   /= sizeof(*mag);


    int gidx = get_global_id(0);
    int gidy = get_global_id(1);

    int lidx = get_local_id(0);
    int lidy = get_local_id(1);
    short2 masky = (short2)(-1,1);

    short8 temp = (short8)0x02;
	__global short8 *Dx = dx + gidx + gidy * (dx_step);
	__global short8 *Dy = dy + gidx + gidy * (dy_step);
	__global short8 *magnitude = mag + gidx + (gidy+1) * mag_step;
    __global short8 *srcX0 = dx_buf + gidx + gidy * (dx_buf_step);
    __global short8 *srcX1 = dx_buf + gidx + (gidy +1) * (dx_buf_step);
	__global short8 *srcX2 = dx_buf + gidx  + (gidy +2) * (dx_buf_step);

	__global short8 *srcY0 = dy_buf + gidx + gidy * (dy_buf_step);
	__global short8 *srcY2 = dy_buf + gidx + (gidy +2) * (dy_buf_step);


   // if(gidx < cols && gidy < rows -2)
    {

	    short8 x1 =(*srcX0 + temp*(*srcX1) + *srcX2);

        short8 y1 = (-*srcY0 + *srcY2);

        *Dx = x1;
		*Dy = y1;

		short2 z0 = _abs2((int)(x1.s01)) + _abs2((int)(y1.s01));
		short2 z1 = _abs2((int)(x1.s23)) + _abs2((int)(y1.s23));
		short2 z2 = _abs2((int)(x1.s45)) + _abs2((int)(y1.s45));
		short2 z3 = _abs2((int)(x1.s67)) + _abs2((int)(y1.s67));

	    short8 z = (short8)(z0,z1,z2,z3);
		*(magnitude)  = z;

    }


}

//////////////////////////////////////////////////////////////////////////////////////////
// 0.4142135623730950488016887242097 is tan(22.5)
#define CANNY_SHIFT 7

#ifdef DOUBLE_SUPPORT
    #define TG22        (short)(0.4142135623730950488016887242097*(1<<CANNY_SHIFT) + 0.5)
#else
    #define TG22        (short)(0.4142135623730950488016887242097f*(1<<CANNY_SHIFT) + 0.5f)
#endif

//First pass of edge detection and non-maximum suppression
// edgetype is set to for each pixel:
// 0 - below low thres, not an edge
// 1 - maybe an edge
// 2 - is an edge, either magnitude is greater than high thres, or
//     Given estimates of the image gradients, a search is then carried out
//     to determine if the gradient magnitude assumes a local maximum in the gradient direction.
//     if the rounded gradient angle is zero degrees (i.e. the edge is in the north-south direction) the point will be considered to be on the edge if its gradient magnitude is greater than the magnitudes in the west and east directions,
//     if the rounded gradient angle is 90 degrees (i.e. the edge is in the east-west direction) the point will be considered to be on the edge if its gradient magnitude is greater than the magnitudes in the north and south directions,
//     if the rounded gradient angle is 135 degrees (i.e. the edge is in the north east-south west direction) the point will be considered to be on the edge if its gradient magnitude is greater than the magnitudes in the north west and south east directions,
//     if the rounded gradient angle is 45 degrees (i.e. the edge is in the north west-south east direction)the point will be considered to be on the edge if its gradient magnitude is greater than the magnitudes in the north east and south west directions.
//
// dx, dy		direvitives of x and y direction
// mag			magnitudes calculated from calcMagnitude function
// map			output containing raw edge types
__kernel
void
//__attribute__((reqd_work_group_size(16,16,1)))
calcMap
(
    __global const short * restrict dx,
    __global const short * restrict dy,
    __global short * restrict mag,
    __global char * restrict map,
    __global ushort2 *st,
    __global int *counter,
    short low_thresh,
    short high_thresh,
    int dx_step,
    int dy_step,
    int mag_step,
    int map_step
 )
{
    dx_step    /= sizeof(*dx);
    dy_step    /= sizeof(*dy);
    mag_step   /= sizeof(*mag);
    map_step   /= sizeof(*map);

    int gidx = get_global_id(0);
    int gidy = get_global_id(1);


	__global short *Dx=dx+gidx + gidy * dx_step;
	__global short *Dy=dy+gidx + gidy * dx_step;

	short magC =*(mag + 1 + gidx +(gidy+1)*mag_step);
	short magT =*(mag + 1 + gidx +(gidy)*mag_step);
	short magB =*(mag + 1 + gidx +(gidy+2)*mag_step);
	short magL =*(mag + gidx +(gidy+1)*mag_step);
	short magR =*(mag + 2 + gidx +(gidy+1)*mag_step);
	__global char *Map = map + 2 + gidx +(gidy+2)*map_step;
    int ind;
    int numedge;
    *counter = (gidx==0 &&  gidy ==0) ?0:*counter;

//	if(gidy < rows && gidx < cols)
	{
	short x = *Dx;
	short y = *Dy;
	x = abs(x);
	y = abs(y);
	char edge;
	char edge_type = 0;
	const short tg22x = x * TG22;
    const short tg67x = tg22x + (x << (1 + CANNY_SHIFT));
    y <<= CANNY_SHIFT;
    edge = (magC>low_thresh);
    char hor_edge = (y < tg22x) * (magC>magL) *(magC>=magR)*(edge + (magC>high_thresh));
    char ver_edge = (y > tg67x) * (magC>magT) *(magC>=magB)*(edge + (magC>high_thresh));
    edge_type = (hor_edge>0) ? hor_edge:ver_edge;
    st[*counter] = (ushort2)((gidy),(gidx));
    *counter+=(edge_type ==2)?1:0;

    *Map = edge_type;

  }

}

//////////////////////////////////////////////////////////////////////////////////////////
// do Hysteresis for pixel whose edge type is 1
//
// If candidate pixel (edge type is 1) has a neighbour pixel (in 3x3 area) with type 2, it is believed to be part of an edge and
// marked as edge. Each thread will iterate for 16 times to connect local edges.
// Candidate pixel being identified as edge will then be tested if there is nearby potiential edge points. If there is, counter will
// be incremented by 1 and the point location is stored. These potiential candidates will be processed further in next kernel.
//
// map		raw edge type results calculated from calcMap.
// st		the potiential edge points found in this kernel call
// counter	the number of potiential edge points
#if 0
#define POSSIBLE_EDGE 1
#define EDGE  2 //;0xff
__kernel
void
__attribute__((reqd_work_group_size(1,1,1)))
edgesblob
(
  __global uchar * pEdgeMap,
  __global ushort * restrict pStrongEdgeList,
  __global uint * restrict pNumStrongEdges,
  int width
)
{
  uchar addTL;
  uchar addTC;
  uchar addTR;
  uchar addLC;
  uchar addRC;
  uchar addBL;
  uchar addBC;
  uchar addBR;

  short offsetTL;
  short offsetTC;
  short offsetTR;
  short offsetRC;
  short offsetBR;
  short offsetBC;
  short offsetBL;
  short offsetLC;

  __global uchar *restrict mapTL;
  __global uchar *restrict mapTC;
  __global uchar *restrict mapTR;
  __global uchar *restrict mapLC;
  __global uchar *restrict mapRC;
  __global uchar *restrict mapBL;
  __global uchar *restrict mapBC;
  __global uchar *restrict mapBR;
  __global uchar *restrict mapC;

  int i = 0;
  ushort x, y;

  int gidx = get_global_id(0);
  int gidy = get_global_id(1);
  ushort *pEdgeListStart;
  ushort *pEdgeListEnd;
  int  newItems = 0, totalItems;
  int activeItems = *pNumStrongEdges;
  int count = 1;

  offsetTL = -1 - width;
  offsetTC = -width;
  offsetTR = +1 - width;
  offsetRC = +1;
  offsetBR = +1 + width;
  offsetBC = -0 + width;
  offsetBL = -1 + width;
  offsetLC = -1;

  pEdgeListStart = (ushort *)pStrongEdgeList;
  totalItems = activeItems;

  while(count!=0)
  {
    pEdgeListEnd = (ushort *)pEdgeListStart + 2*activeItems;
    for(i=0; i<activeItems; i++)
    {
      y = pEdgeListStart[2*i];
      x = pEdgeListStart[2*i + 1];

      mapC = pEdgeMap + (y+2)*width + x +2;

      mapTL = mapC + offsetTL;
      mapTC = mapC + offsetTC;
      mapTR = mapC + offsetTR;
      mapLC = mapC + offsetLC;
      mapRC = mapC + offsetRC;
      mapBR = mapC + offsetBR;
      mapBC = mapC + offsetBC;
      mapBL = mapC + offsetBL;

      addTL = (*mapTL == POSSIBLE_EDGE);
      addTC = (*mapTC == POSSIBLE_EDGE);
      addTR = (*mapTR == POSSIBLE_EDGE);
      addRC = (*mapRC == POSSIBLE_EDGE);
      addBR = (*mapBR == POSSIBLE_EDGE);
      addBC = (*mapBC == POSSIBLE_EDGE);
      addBL = (*mapBL == POSSIBLE_EDGE);
      addLC = (*mapLC == POSSIBLE_EDGE);

      *mapTL += addTL;// << 7;
      *mapTC += addTC;// << 7;
      *mapTR += addTR;// << 7;
      *mapRC += addRC;// << 7;
      *mapBR += addBR;// << 7;
      *mapBC += addBC;// << 7;
      *mapBL += addBL;// << 7;
      *mapLC += addLC;// << 7;

      if(addTL)
      {
        pEdgeListEnd[2*newItems+1] = (x-1);
        pEdgeListEnd[2*newItems] = (y-1);
        newItems += addTL;
        *mapTL = EDGE;
      }
      if(addTC)
      {
        pEdgeListEnd[2*newItems+1] = x;
        pEdgeListEnd[2*newItems] = (y-1);
        newItems += addTC;
        *mapTC = EDGE;
      }
      if(addTR)
      {
        pEdgeListEnd[2*newItems+1] = (x+1);
        pEdgeListEnd[2*newItems] = (y-1);
        newItems += addTR;
        *mapTR = EDGE;
      }
      if(addRC)
      {
        pEdgeListEnd[2*newItems+1] = (x+1);
        pEdgeListEnd[2*newItems] = y;
        newItems += addRC;
        *mapRC = EDGE;
      }
      if(addBR)
      {
        pEdgeListEnd[2*newItems+1] = (x+1);
        pEdgeListEnd[2*newItems] = (y+1);
        newItems += addBR;
        *mapBR = EDGE;
      }
      if(addBC)
      {
        pEdgeListEnd[2*newItems+1] = x;
        pEdgeListEnd[2*newItems] = (y+1);
        newItems += addBC;
        *mapBC = EDGE;
      }
      if(addBL)
      {
       pEdgeListEnd[2*newItems+1] = (x-1);
       pEdgeListEnd[2*newItems] = (y+1);
       newItems += addBL;
       *mapBL = EDGE;
      }
      if(addLC)
      {
        pEdgeListEnd[2*newItems+1] = (x-1);
        pEdgeListEnd[2*newItems] = y;
        newItems += addLC;
        *mapLC = EDGE;
      }

    }

    activeItems = newItems;
    totalItems += newItems;
    newItems = 0;
	//count --;
    if(activeItems == 0)
    {
      break;
    }
    pEdgeListStart = (ushort *)pEdgeListEnd;
  }

  *pNumStrongEdges = totalItems;

}
#else
__kernel
void
__attribute__((reqd_work_group_size(1,1,1)))
edgesblob
(
  __global  uchar * pEdgeMap,
  __global  ushort * restrict pStrongEdgeList,
   __global uint * restrict pNumStrongEdges,
   ushort width
)
{
  short offsetTL;
  short offsetBL;
  short offsetLC;

  __global uchar *restrict mapTL;
  __global uchar *restrict mapLC;
  __global uchar *restrict mapBL;
  __global uchar *restrict mapC;

  uint topRow;
  uint midRow;
  uint botRow;

  uint topMask = 0x80010101;
  uint midMask = 0x80020101;
  uint botMask = 0x80010101;

  uint addT;
  uint addC;
  uint addB;

  uint topOut;
  uint midOut;
  uint botOut;

  int activeItems = *pNumStrongEdges;
  int i = 0;
  uint xy;
  uint status = 0;
  ushort *pEdgeListStart;
  ushort *pEdgeListEnd;
  int  newItems = 0, totalItems;
  uint newWidth = 0;

  pEdgeListStart = (ushort *)pStrongEdgeList;
  totalItems = activeItems;

  offsetTL = -1 - width;
  offsetBL = -1 + width;
  offsetLC = -1;

  newWidth = (1 << 16) + width;

  while(1)
  {
    pEdgeListEnd = (ushort *)pEdgeListStart + 2*activeItems;
    for(i=0; i<activeItems; i++)
    {
      xy = _mem4(pEdgeListStart + 2*i);

      mapC = pEdgeMap + _dotp2(xy, newWidth);

      mapTL = mapC + offsetTL;
      mapLC = mapC + offsetLC;
      mapBL = mapC + offsetBL;

      topRow = _mem4((uint *)mapTL);
      midRow = _mem4((uint *)mapLC);
      botRow = _mem4((uint *)mapBL);

      addT = _cmpeq4(topRow, topMask);
      addC = _cmpeq4(midRow, midMask);
      addB = _cmpeq4(botRow, botMask);

      topOut = _xpnd4(addT);
      midOut = _xpnd4(addC);
      botOut = _xpnd4(addB);

      topOut |= topRow;
      midOut |= midRow;
      botOut |= botRow;

      _mem4((void*)mapTL) = topOut;
      _mem4((void*)mapLC) = midOut;
      _mem4((void*)mapBL) = botOut;

      if(addT & 1)
      {
        _mem4(pEdgeListEnd + 2*newItems) = xy - (1 << 16) - 1;
        newItems++;
      }

      if(addT & 2)
      {
        _mem4(pEdgeListEnd + 2*newItems) = xy - (1);
        newItems++;
      }

      if(addT & 4)
      {
        _mem4(pEdgeListEnd + 2*newItems) = xy + (1 << 16) - 1;
        newItems++;
      }

      if(addC & 4)
      {
         _mem4(pEdgeListEnd + 2*newItems) = xy + (1 << 16);
         newItems++;
      }

      if(addC & 1)
      {
        _mem4(pEdgeListEnd + 2*newItems) = xy - (1 << 16);
        newItems++;
      }

      if(addB & 4)
      {
        _mem4(pEdgeListEnd + 2*newItems) = xy + (1 << 16) + 1;
        newItems++;
      }

      if(addB & 1)
      {
        _mem4(pEdgeListEnd + 2*newItems) = xy - (1 << 16) + 1;
        newItems++;
      }

      if(addB & 2)
      {
        _mem4(pEdgeListEnd + 2*newItems) = xy + 1;
        newItems++;
      }

    }

    activeItems = newItems;
    totalItems += newItems;
    newItems = 0;
    if(activeItems == 0)
    {
      break;
    }
    pEdgeListStart = (ushort *)pEdgeListEnd;
  }

  *pNumStrongEdges = totalItems;

}
#endif

//Get the edge result. egde type of value 2 will be marked as an edge point and set to 255. Otherwise 0.
// map		edge type mappings
// dst		edge output
__kernel
void getEdges
(
    __global const uchar4 * map,
    __global uchar4 * dst,
    int map_step,
    int dst_step
)
{
    map_step   /= sizeof(*map);
    dst_step   /=sizeof(*dst);
    int gidx = get_global_id(0);
    int gidy = get_global_id(1);
    __global const uchar4 *in =  map+ gidx +2 + (gidy+2) * ( map_step);
    __global uchar4 *out =  dst+ gidx + (gidy) * ( dst_step);
    //uchar16 mask = (uchar16)(0x2,0x2,0x2,0x2,0x2,0x2,0x2,0x2,0x2,0x2,0x2,0x2,0x2,0x2,0x2,0x2);
    uchar4 mask = (uchar4)(0x2,0x2,0x2,0x2);




 //   if(gidy < rows && gidx < cols)
    {

        *out = -(*in & mask);
    }
}

