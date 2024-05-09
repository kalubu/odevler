k = int(input())
a=0
b=1
c=1
x=1
y=a

while x < k:
    c = b + a
    a = b
    b = c
    y = a
    x = 0
    while y >= 1:
        y = y // 10
        x = x + 1
    
while x == k:
    print(a)
    c = b + a
    a = b
    b = c
    y = a
    x = 0
    while y >= 1:
        
        y = y // 10
        x = x + 1
        
