```python

def multiply_integers(x,y,n):
	if n == 1:
		return x*y
		
	'''
	x = a * 10^(n//2) + b
	y = c * 10^(n//2) + d
	'''
	ac = multiply_integers(x,y,n//2)
	ad = multiply_integers(x,y,n//2)
	bc = multiply_integers(x,y,n//2) 
	bd = multiply_integers(x,y,n//2)
	
	return ac 10^n + (ad + bc)^(n//2) + bd

```