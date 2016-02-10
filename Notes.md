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

##2/5/16 - 2/7/16
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

