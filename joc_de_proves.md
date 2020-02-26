# Jocs de proves

## Prova 1

### Input:

```
polygon p1 0 0 0 1 1 1 1 0
print p1
point_inside p1 0.5 0.5
point_inside p1 0 1
point_inside p1 2 2
vertices p1
edges p1
perimeter p1
area p1
regular p1
centroid p1
empty p1
monogon p1
digon p1
give_colors p1
save file.txt p1
setcol p1 0.5 1 0.8
give_colors p1
draw a p1
```

### Output:

```
ok
p1 0.000 0.000 0.000 1.000 1.000 1.000 1.000 0.000
yes
yes
no
4
4
4.000
1.000
yes
0.500 0.500
no
no
no
color red: 1.000
color gren: 1.000
color blue: 1.000
ok
ok
color red: 0.500
color gren: 1.000
color blue: 0.800
ok
```

## Prova 2

### Input:

```
polygon p1 0 0 0 2 2 2 2 0
polygon p2 1 1 1 3 3 3 3 1
polygon i
intersection i p1 p2
print i
setcol p1 1 0 0
setcol p2 0 1 0
setcol i 0 0 1
draw b p1 p2 i
```

### Output:

```
ok
ok
ok
ok
i 1.000 1.000 1.000 2.000 2.000 2.000 2.000 1.000
ok
ok
ok
ok
```

## Prova 3

### Input:

```
load file.txt
print p1

polygon p1 -37 20 -24 44 -12 44 -6 40 17 -17 -27 -44
polygon p2 -27 -30 -25 -16 -3 35 46 35 35 -33 -8 -39
polygon s
intersection s p1 p2
print s
setcol s 0.4 0.5 0.8
draw c p1 p2 s

bbox p3 p1 p2
print p3
union p1 p2
print p1
list
```

### Output:

```
ok
p1 0.000 0.000 0.000 1.000 1.000 1.000 1.000 0.000

ok
ok
ok
ok
s -27.000 -30.000 -25.000 -16.000 -3.508 33.823 17.000 -17.000 -14.124 -36.099
ok
ok

ok
p3 -37.000 -44.000 -37.000 44.000 46.000 44.000 46.000 -44.000
ok
p1 -37.000 20.000 -24.000 44.000 -12.000 44.000 46.000 35.000 35.000 -33.000 -27.000 -44.000
p1 p2 p3 s
```

## Prova 4

### Input:

```
polygon p1
print p1
empty p1
vertices p1
area p1
point_inside p1 0 0

polygon p2 1 1
print p2
monogon p2
digon p2
inside p1 p2
inside p2 p1
```

### Output:

```
ok
p1 is empty
yes
0
p1 is empty
p1 is empty, so it cannot contain a point
p2 1.000 1.000
yes
no
p1 is empty, so it cannot contain another polygon
p1 is empty, so it cannot be contained
```

## Prova 5

### Input:

```
polygon p1 0 0 0 1 0 2 0 3 0 4
print p1
digon p1
area p1
centroid p1
point_inside p1 0 1
point_inside p1 -1 1
```

### Output:

```
ok
p1 0.000 0.000 0.000 4.000
yes
p1 is empty
0.000 2.000
yes
no
```

## Prova 6

### Input:

```
# prova
polygon p1 0 0 1
polygon p1 0 0 1 1
print p2

hola
polgn p3
setcol p1 2 5 9
```

### Output:

```
#
error: command with wrong number or type of arguments
ok
error: polygon not defined yet
intersection p1 p2
error: polygon not defined yet

error: unrecognized command
error: unrecognized command
error: wrong format
```
## Prova 7

### Input:

```
polygon p1 3 5 6 4 4 7 3 3 7 5
print p1
polygon p2 1 3 2 2 5 3 3 1 9 5 8 8 5 8 2 8 4 5 7 6 2 5
print p2
polygon p3 1 1 3 3 5 8 2 2 -1 5 -1 -1 2 8
print p3
polygon p4 6 5 7 8 10 1 10 3 6 3 4 7 2 4 3 2 9 7 6 1
print p4
```

### Output:

```
ok
p1 3.000 3.000 3.000 5.000 4.000 7.000 7.000 5.000 6.000 4.000
ok
p2 1.000 3.000 2.000 8.000 8.000 8.000 9.000 5.000 3.000 1.000
ok
p3 -1.000 -1.000 -1.000 5.000 2.000 8.000 5.000 8.000 3.000 3.000
ok
p4 2.000 4.000 4.000 7.000 7.000 8.000 9.000 7.000 10.000 3.000 10.000 1.000 1.000 6.000 3.000 2.000
```
