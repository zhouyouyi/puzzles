import sys
from sys import stdin,stdout
import math

def gcd_ext(a, b):
    if b == 0:
        return (int(a),int(1),int(0))
    else:
        g,x,y = gcd_ext(b, a%b)
        t = x;
        x = y;
        y = t - a/b*y
        return int(g),int(x),int(y)

a1,b1,a2,b2,L,R = [ int(x) for x in stdin.readline().rstrip().split() ]

A = int(a1)
B = int(a2)
C = int(b2 - b1)

G,X,Y = gcd_ext( A, B )

if C % G != 0:
    print(0)
    sys.exit(0)

X = int(X*C/G)
Y = int(Y*C/G)

K = int(max( [ math.ceil( -X*G/float(B) ), math.ceil( Y*G/float(A) ) ] ))

# print("A",A,"B",B)
# print("G",G)
# print("X",X,"Y",Y)
# print("K",K)

# print("LOWER", (L - b1 - a1 * X) * G / float( B * a1 ), (L - b2 + a2 * Y) * G / float( A * a2 ))
# print("UPPER", (R - b1 - a1 * X) * G / float( B * a1 ), (R - b2 + a2 * Y) * G / float( A * a2 ))
# print("S", a1 * (X + B*K/G) + b1, "T", a2 * (-Y + A*K/G) + b2)

K = max( [ K, int(math.ceil( (L - b1 - a1 * X) * G / float( B * a1 ) )) ] )

U = math.floor( (R - b1 - a1 * X) * G / float( B * a1 ) + 0.00001 )

# print(K,U)

while a1 * (X + B*K/G) + b1 < L:
    K = K + 1

# print(K, a1 * (X + B*K/G) + b1)

if K > U or a1 * (X + B*K/G) + b1 > R:
    ANS = 0;
else:
    ANS = U - K + 1

print(max( [ 0, int(ANS) ] ))
