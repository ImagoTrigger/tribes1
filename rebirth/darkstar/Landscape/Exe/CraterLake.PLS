?   seed	1006
push           256
clr	0
dup
fill_n	0.75
fft	1
pop
normalize	0.0 0.7
load	..\art\doughnut.bmp
sub_stack 0
normalize 0.0 1.0
floor	0.4 0.0 0.4
normalize	0.0 1200

 