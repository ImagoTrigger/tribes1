�   seed	1002
push          256
clr	0
dup
fill_n	0.90
fft	1
pop
normalize	0.0 1.0
floor	0.3 0.00 0.3
ceil	0.8 0.01 0.2
normalize 0.0  1200.0
clamp	5 32.0
clamp        2 5.0
smooth      0.01 6 