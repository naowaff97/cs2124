const char geo = '9';
const char qua = '7';
const char help = '6';


#define pi 2*acos(0)
#define cos(a) cos(a*pi/180)
#define sin(a) sin(a*pi/180)
#define tan(a) tan(a*pi/180)
#define cosi(a) acos(a)/(pi/180)
#define sini(a) asin(a)/(pi/180)
#define tani(a) atan(a)/(pi/180)
#define tanii(a,b) atan2(a,b)/(pi/180)//tan(90) = Infinity or a/0


//Extended Geometry
#define dis(x1,y1,x2,y2) ((x1-x2)*(x1-x2))+((y1-y2)*(y1-y2))
#define t_area(a,b,c,s) sqrt(s*(s-a)*(s-b)*(s-c))
#define t_angle(a,b,c) cosi((b*b+c*c-a*a)/(2*b*c))

#define exp 1e-9
