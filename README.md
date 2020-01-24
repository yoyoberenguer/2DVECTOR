# 2D-VECTOR-LIBRARY-
2D vector library in C

Provides vector functions, similar to pygame.math.Vector2  library 

```

// Vector intialization
struct vector2d;
void vecinit(struct vector2d *v, float x, float y);

// Vector distance
float distance_to(struct vector2d v1, struct vector2d v2);
float distance_squared_to(struct vector2d v1, struct vector2d v2);

// Vector length
float vlength(struct vector2d *v);
float length_squared(struct vector2d v);

// Vectors operations inplace (similar to elementwise in pygame.math.Vector2 library)
// the result of the operation is assigned to the variable v1 (v2 remains unchanged)
void subv_inplace(struct vector2d *v1, struct vector2d v2);
void addv_inplace(struct vector2d *v1, struct vector2d v2);
void divv_inplace(struct vector2d *v1, struct vector2d v2);
void mulv_inplace(struct vector2d *v1, struct vector2d v2);

// Vector operations elementwise (similar to elementwise in pygame.math.Vector2 library)
// Return a new vector2d (v1 and v2 remains unchanged)
struct vector2d mulcomponents(struct vector2d v1, struct vector2d v2);
struct vector2d addcomponents(struct vector2d v1, struct vector2d v2);
struct vector2d subcomponents(struct vector2d v1, struct vector2d v2);
struct vector2d divcomponents(struct vector2d v1, struct vector2d v2);

// Scaling vectors 
void scalevector2d_self(float c, struct vector2d *v);
struct vector2d scalevector2d(float c, struct vector2d *v);

// Dot product 
float dot(struct vector2d *v1, struct vector2d *v2);

// Normalisation
void normalize (struct vector2d *v);

// Vector rotation
void vrotate_deg(struct vector2d *v, float deg);
void vrotate_rad(struct vector2d *v, float rad);

// Vector Angle
float angle_to(struct vector2d v1, struct vector2d v2);
float vangle_rad(struct vector2d v);
float vangle_deg(struct vector2d v);
```
