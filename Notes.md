#Notes

## 2/3/16
##### Image File Formats

Compressed vs Uncompressed

Compressed
 - smaller
 - processing involved
 - ex: jpg/jpeg, webp, png, gif

Uncompressed
 - raw image data
 - ex: bitmap, tiff, raw(nef)

Lossy vs Lossless
 - Lossy loses some original info
 - Loseless retains all original info
 - Lossy ex: jpg/jpeg,
 - Lossless ex: bitmap, tiff, png

Compression Algorithm Example:
 - image GGGGGYYYYYYRRR
 - Each color is 1 byte
 - Total size: 14B
 - Compression: 5G6Y3R, size: 6B
 - This is known as run length compression
 - This type of compression doesnt work for everything

Raster vs Vector
 - Raster image is represented as a grid of pixels
 - Vector image format is a list of drawing instructions
 - Vector format ex: svg

## 2/4/16
####NetPBM
 - a family of image file formats
 - extension: .ppm
 - losseless raster format
 - format:

P3

XRES YRES MAX_COLOR_VALUE

R G B R G B ...

[0,0] [0,1] ...

R G B R G B ...

[1,1] [1,1] ...


Commands:
 - display <file>.ppm
 - convert <file>.ppm <file>.png

DO NOT ADD PPM TO GITHUB

##2/5/16 - 2/9/16
####Github
 - Use .gitignore
 - Use submodules (aliases for repos)

####Line Algorithm
######Bresenham's Line Algorithm
y=mx+b

y=(dy/dx)x+b (d=delta)

(dx)y=(dy)x+(dx)b

0=(dy)x-(dx)y+(dx)b

let A=dy, B=-dx, C=(dx)b

0=Ax+By+c

f(x,y)=Ax+By+C

if( f(x,y)==0 ) then (x,y) on line

if( f(x,y) is in Octant I ) then its slope is positive &&
	if( f(x, y) > 0 ) then (x,y) is below the line
	if( f(x, y) < 0 ) then (x,y) is above the line

Magnitude gives distance; sign gives direction

line in octant I (0 < slope of line < 1)
 - given equation Ax+By+C=0 and point (p,q) [or both end points...]
 - next point is either (p+1,q) or (p+1,q+1)
 - calculate midpoint (m,n) = (p+1,q+1/2)
 - compute A(m)+B(n)+C = S
 - if( S==0 ) midpoint is on line, color either pixel
 - else if( S<0 ) midpoint is above line, color lower pixel (p+1,q)
 - else draw upper pixel (p+1,q+1)

Code Algorithm (first draft)

given: (x0,y0) -> (x1,y1)

x=x0, y=y0

while( x<x1 ) {

	plot(x,y); // color_point(x,y);

        d = line_eq(x+1,y+1/2); //solve for equation A, B, C

	if( d>0 ) y++;

	x++;

}

line_eq(x+1,y+1/2) is most burdensome calculation and can be optimized!!!

if( x==x0 && y==y0 ) {line_eq(x+1,y+1/2) = line_eq(x,y)+A+(1/2)B = A+(1/2)B}

Code Algorithm (second draft)

given: (x0,y0) -> (x1,y1)

x=x0, y=y0, d=A+(1/2)B

while( x<x1 ) {

	plot(x,y); // color_point(x,y);

        d = line_eq(x+1,y+1/2); //solve for equation A, B, C

	if( d>0 ) y++;

	x++;

}


Code Algorithm (Third draft)

given: (x0,y0) -> (x1,y1)

x=x0, y=y0, d=A+(1/2)B

while( x<x1 ) {

	plot(x,y); // color_point(x,y);

        if( d>0 ) += B;
	d += A;

	if( d>0 ) y++;

	x++;

}

##2/10/16
####Line Algorithm (Octant I)

to draw line from (x0,y0) to (x1,y1)

x=x0, y=y0;

A=y1-y0, B=x1-x0;

d=2A+B

while(x<=x1) {

	plot(x,y)

	if( d>0 ) {

		y+=1; d+=2B;

	}

	x+=1; d+= 2A

}

####Octant II
1 < slope of line

for point (x,y) next possible point (x,y+1) or (x+1,y+1)

next possible points' midpoint changes, changing d

other stuff changes too

####Line Algorithm (Octant II)

to draw line from (x0,y0) to (x1,y1)

x=x0, y=y0;

A=y1-y0, B=x1-x0;

d=A+2B

while(x<=x1) {

	plot(x,y)

	if( d<0 ) {

		x+=1; d+=2A;

	}

	y+=1; d+=2B;

}

##2/22/16
####Using Matrices

######Point Matrix
 - [P_0 P_1 P_2 P_3 P_4 ...]
 - Draw line between each adjacent point
 - FAILS

######Shape Matrix
 - [[P_0 P_1 P_2] [P_3 P_4 P_5]]
 - Draws closed shapes only
 - 3D array

###### (?) "Null Matrix flavor/variant of edge matrix"
 - [P_0 P_1 P_2 P_0 NUL P_3 P_4 P_5 P_3 NUL]
 - 

######Edge Matrix
 - [P_0 P_1 P_1 P_2 P_2 P_3 ...]
 - More Space Extensive
 - Draw every pair of points

#######Connection Matrix
 - Array of Points
 - Boolean matrix where element (i,j) is true of Points i and j have a line

NOTE: Points are Arrays themselves

Points Will be: [X, Y, Z, 1]

##Matrix Math
 - Scalar Multiplication
 - Matrix Multiplication
 - Matrix Multiplication Identity

####Scalar Multiplication
```
foo(scalar s, matrix M) {
	for(i=0; i<rows; i++) {
		for(j=0; j<cols; j++) {
			M[i][j] *= s;
		}
	}
}
```

####Matrix Multiplication
 - non commutative
 - number of cols in first matrix must equal number of rows of second matrix
```

```

####Matrix Multiplication Identity
######Identity Matrix
 - All diagonal values are 1; all other values are 0
 - Square Matrix
 - Any matrix times an identity matrix is the former matrix

####Graphics Matrics

A set of points is always a 4xN matrix, where N is number of points

##2/24/16 - 2/25/16

#####Scaling
(x,y,z) ---Scale(a,b,c)---> (ax,by,cz)

[a000][x]    [ax]

[0b00][y] -- [by]

[00c0][z] -- [cz]

[000d][1]    [dy]

Note: dilates _from center_

####Translation

(x,y,z)---Translate(a,b,c)-->(x+a,b+y,c+z)

[100a][x]   [x+a]
[010b][y] --[y+b]
[001c][z] --[c+z]
[0001][1]   [ 1 ]

####Rotation

(x,y,z)---Rotate(a,b,c,o)-->

3D rotations require _axis of rotation_ and angle

A 2d rotation of point (x,y) by o degrees is xcos(o)-ysin(o),xsin(o)+ycos(o);

For 3d rotation about x, y, _or_ z-axis, use 2d rotation on plane yz, xz, xy

####Applying (affine) transformations
let E_0 be an Edge matrix

let S be Scale matrix

let T be Translation matrix

let R  be Rotation matrix



Translation: T*E0 = E1 translated

Scale Image: S*E1 = E2 translated & scaled

A Rotation : R*E2 = E3 translated & scaled & rotated

E3 = R*S*T*E0 = (R*S*T)*E0 _Matrix multiplication is associative_


##3/3/2016

####Parametric Equations
 - Non-parameterized equation: y=f(x); if x changes, y changes, and vice-versa
 - Parametric Equation: x=f(t), y=g(t); x and y are no longer related; t is a parameter off of which x and y are based
 - In graphics, we generate a bunch of xs and ys by taking t from 0 to 1 (t:0->1) (t=[0,1])

Create a param_x and param_y function, then use a for-loop to get and add (x,y) coordinates

Can make param functions piece wise and make a bunch of shapes.
 
##3/8/16

####Hermit Curves & Splines
