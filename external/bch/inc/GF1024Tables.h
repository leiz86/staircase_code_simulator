#ifndef INC_GF1024TABLES_H_
#define INC_GF1024TABLES_H_

#define GFQ 1024
#define GFq 1023
#define GFm 10
typedef unsigned int GFel;
#define PLUS(x,y) ((x)^(y))
#define TIMES(x,y) ((x)==0?0:((y)==0?0:EXP[(LOG[x]+LOG[y])%(GFq)]))

extern GFel DepCubicRoot[2048];
extern GFel CubeRoot[2048];
extern GFel DepQuadRoot[2048];
extern GFel SquareRoot[1024];
extern GFel Pow2[1024];
extern GFel Pow3[1024];
extern GFel Pow5[1024];
extern GFel Reciprocal[1024];
extern GFel EXP[1023];
extern GFel LOG[1024];

#endif
