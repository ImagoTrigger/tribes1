?   seed	100
push           256
clr	0
dup
fill_n	0.60
fft	1
pop
normalize	0.0 1.0
curve         0.01 6
load          ..\art\mound.bmp
add_stack 1
floor	0.4 0.0 0.4
normalize 0.0 1200.0


 