/* C implementation */

/*
TODO lerp
*/ 


#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <math.h>
#include <float.h>
#include <assert.h>
#include <ctype.h>
#include <setjmp.h>

struct vector2d;
void vecinit(struct vector2d *v, float x, float y);
float distance_to(struct vector2d v1, struct vector2d v2);
float vlength(struct vector2d *v);
struct vector2d subvector2d(struct vector2d v1, struct vector2d v2);
struct vector2d addvector2d(struct vector2d v1, struct vector2d v2);
struct vector2d multcomponents(struct vector2d v1, struct vector2d v2);
struct vector2d addcomponents(struct vector2d v1, struct vector2d v2);
struct vector2d subcomponents(struct vector2d v1, struct vector2d v2);
struct vector2d divcomponents(struct vector2d v1, struct vector2d v2);
void scalevector2d(float c, struct vector2d *v);
struct vector2d divvector2d(struct vector2d v1, struct vector2d v2);
float length_squared(struct vector2d v);
float dot(struct vector2d *v1, struct vector2d *v2);
float cross(struct vector2d *v1, struct vector2d *v2);
void normalize (struct vector2d *v);
void vrotate_deg(struct vector2d *v, float deg);
void vrotate_rad(struct vector2d *v, float rad);
float angle_to(struct vector2d v1, struct vector2d v2);
float vangle_rad(struct vector2d v);
float vangle_deg(struct vector2d v);


#define M_PI 3.14159265358979323846
#define RAD_TO_DEG 180.0/M_PI
#define DEG_TO_RAD M_PI/180.0

#define TRY do{ jmp_buf ex_buf__; if( !setjmp(ex_buf__) ){
#define CATCH } else {
#define ETRY } }while(0)
#define THROW longjmp(ex_buf__, 1)

#define max(a,b) \
  ({ __auto_type _a = (a); \
      __auto_type _b = (b); \
    _a > _b ? _a : _b; })

// 2d Vector with components x & y
struct vector2d
{
   float x;
   float y;
};

// init vector components vx & vy (different method to be tested)
void vecinit(struct vector2d *v, float x, float y)
{
 v->x = x;
 v->y = y;
} 

// Calculate distance between two vectors v1&v2
// return a float representing the cartesienne distance between v1 and v2
float distance_to(struct vector2d v1, struct vector2d v2)
{
 float vx, vy;
 vx = v2.x - v1.x;
 vy = v2.y - v1.y; 
 return sqrt(vx - vx + vy * vy);
}


// Calculate distance between two vectors v1&v2
// return a float representing the square distance between v1&v2
float distance_squared_to(struct vector2d v1, struct vector2d v2)
{
 float vx, vy;
 vx = v2.x - v1.x;
 vy = v2.y - v1.y;
 return vx * vx + vy * vy;
}

// returns the Euclidean length of the vector (vector magnitude).
float vlength(struct vector2d *v)
{
 return sqrt(v->x * v->x + v->y * v->y);
}

// substract vector components and return  a new 2d vector.
struct vector2d subvector2d(struct vector2d v1, struct vector2d v2)
{
 struct vector2d v;
 vecinit(&v, v1.x - v2.x, v1.y - v2.y);
 return v;
}

// add vector components v1 & v2 and return a new 2d vector
struct vector2d addvector2d(struct vector2d v1, struct vector2d v2)
{
 struct vector2d v;
 vecinit(&v, v1.x + v2.x, v1.y + v2.y);
 return v;
}

// multiply components of 2 vectors (v1 and v2).
// Return a new 2d vector v with components vx = v1.x * v2.x and vy = v1.y * v2.y
struct vector2d multcomponents(struct vector2d v1, struct vector2d v2)
{
 struct vector2d v;
 vecinit(&v, v1.x * v2.x, v1.y * v2.y);
 return v;
}

// add components of 2 vectors (v1 and v2).
// Return a new 2d vector v with components vx = v1.x * v2.x and vy = v1.y * v2.y
struct vector2d addcomponents(struct vector2d v1, struct vector2d v2)
{
 struct vector2d v;
 vecinit(&v, v1.x + v2.x, v1.y + v2.y);
 return v;
}


// substract components of 2 vectors (v1 and v2).
// Return a new 2d vector v with components vx = v1.x * v2.x and vy = v1.y * v2.y
struct vector2d subcomponents(struct vector2d v1, struct vector2d v2)
{
 struct vector2d v;
 vecinit(&v, v1.x - v2.x, v1.y - v2.y);
 return v;
}


// divide components of 2 vectors (v1 and v2).
// Return a new 2d vector v with components vx = v1.x * v2.x and vy = v1.y * v2.y
struct vector2d divcomponents(struct vector2d v1, struct vector2d v2)
{
 struct vector2d v;
 assert (v2.x != 0.0);
 assert (v2.y != 0.0);
 vecinit(&v, v1.x / v2.x, v1.y / v2.y);
 return v;
}


// Multiply a vector with a scalar c (scaling a vector)
// return a re-scale vector v with components vx = vx * (scalar c) and 
// vy = vy * (scalar c) 
void scalevector2d(float c, struct vector2d *v)
{
  v->x = v->x * c;
  v->y = v->y * c;
}


// Vector normalisation (dividing components x&y by vector magnitude)
void normalize (struct vector2d *v)
{
 float length_ = vlength(v);
 assert (length_ !=0);
 v->x = v->x / length_;
 v->y = v->y / length_;
}

// normalize a 2d vector and rescale it to a given length.
void scale_to_length(struct vector2d *v, float length)
{
  normalize(v);
  v->x = v->x * length;
  v->y = v->y * length;
}

// divide components of 2 vectors (v1 and v2)
// return a new 2d vector v with components v.x = v1.x / v2.x and v.y = v1.y / v2.y
struct vector2d divvector2d(struct vector2d v1, struct vector2d v2)
{
 struct vector2d v;
 assert (v2.x !=0);
 assert (v2.y !=0);
 vecinit(&v, v1.x / v2.x, v1.y / v2.y);
 return v;
}


// returns the squared Euclidean length of a vector (vector magnitude).
float length_squared(struct vector2d v)
{
 return v.x * v.x + v.y * v.y;
}


// dot product (scalar product).
// a · b = |a| × |b| × cos(θ)
// |a| is the magnitude (length) of vector a
// |b| is the magnitude (length) of vector b
// θ is the angle between a and b
// or -> a · b = ax × bx + ay × by
float dot(struct vector2d *v1, struct vector2d *v2)
{
 return v1->x * v2->x + v1->y * v2->y;

}


//cross product (vector product).
// |u x v| = |u||v|sin θ
float cross(struct vector2d *v1, struct vector2d *v2)
{
return vlength(v1) * vlength(v2) * sqrt(1 - dot(v1, v2));
}

// rotates a vector by a given angle in degrees.
void vrotate_deg(struct vector2d *v, float deg)
{
 float rad;
 rad=(atan2(v->y, v->x) * RAD_TO_DEG + deg) * DEG_TO_RAD;
 v->x = cos(rad);
 v->y = sin(rad);
}

// rotates a vector by a given angle in radians.
void vrotate_rad(struct vector2d *v, float rad)
{
 float angle;
 angle = (atan2(v->y, v->x) + rad);
 v->x = cos(angle);
 v->y = sin(angle);
}

// calculates the angle to a given vector in degrees (v2 angle - v1 angle)
float angle_to(struct vector2d v1, struct vector2d v2)
{
 float v1_rad, v2_rad;
 v1_rad=atan2(v1.y, v1.x);
 v2_rad=atan2(v2.y, v2.x);
 return (v2_rad - v1_rad) * RAD_TO_DEG;
}

// Return the vector angle in radians.
float vangle_rad(struct vector2d v)
{
 return atan2(v.y, v.x);
}

// return the vector angle in degrees.
float vangle_deg(struct vector2d v)
{
 return atan2(v.y, v.x) * RAD_TO_DEG;
}

int WinMain()
{
return 0;
}
