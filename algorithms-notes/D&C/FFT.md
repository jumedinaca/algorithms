### Teorema de Moivre

$$
z = r\cdot\left(\cos(\theta) + i\sin(\theta)\right)
$$
$$
z^{n} = r^{n} \cdot (\cos(n\theta)  + i\sin(n\theta))
$$
### Representacion exponencial

$$
\begin{align}

z = a +bi &= r\cdot\left(\cos(\theta) + i\sin(\theta)\right) \\
&= r \cdot e^{i\theta}
\end{align}
$$

### Raices n-esimas de un complejo

$w$ es una n-ésima raiz de $z$ si $w^{n} = z$
Hay exactamente n raices n-ésimas

$$
\begin{align}
z &= r\cdot&\left(\cos(\theta) + i\sin(\theta)\right) \\
w &= s\cdot&\left(\cos(\alpha) + i\sin(\alpha)\right) \\
w^{n} &= s^n\cdot&\left(\cos(n\alpha) + i\sin(n\alpha)\right) \\

\end{align}
$$

$$
\theta = n \alpha \\
\theta + 2\pi k= n \alpha \\
\frac{\theta + 2\pi k}{n} = \alpha
$$

$$
w_k =  r^{\frac{1}{n}}\cdot\left(\cos\left(\frac{\theta + 2\pi k}{n}\right) + i\sin\left(\frac{\theta + 2\pi k}{n}\right)\right) \\

k  = 0,1,2,\dots,n-1
$$
Las n-esimas raices de unidad son
 $$
 w_k = 
    \cos \left(\frac{\theta + 2\pi k}{n} \right) + 
 i\ \sin \left(\frac{\theta + 2\pi k}{n} \right)
 $$
 $$
 z = 1, \theta = 0
 $$
$$
 w_k = 
    \cos \left(\frac{2\pi k}{n} \right) + 
 i\ \sin \left(\frac{2\pi k}{n} \right)
\ \ 
= e^{\frac{2\pi k}{n}} 
$$

Anotación

$w_n^{k}$ Raiz n-esima 



### 

$$
P(x) = \sum_{i=0}^{n-1} a_i x 
$$

### Cancellation lema

For any integers n > 0, , k >= 0, d > 0
$$
w_{dn}^{dn} = w_n^{k}
$$
 We can cancel out $d$
##

### Halving Lemma
if n > 0 is even, then the squares of the n complex n roots of unity are the n/2 roots of unity, where each appear exactly twice.

### Summation Lemma

For any non-zero integer k  not divisible by n  , and any integer n >= 1

$$
\sum_{j = 0}^{n-1} (w_n^k)^{j} = 0
$$
### Discrete Fourier Transform
Evaluate

$$
A(x) = \sum_{i = 0}^{n -1} a_i x^{i}\ \  \text{on roots of unity  } w_n^k , k=0,1,...,n-1
$$

$$
Y_k = A(w_n^{k}) \\
Y = (Y_0, Y_1, ... Y_{n-1}) \\
Y = DFT_n(A)
$$


```text

resursive_fft(A):
	n = A.lenght # must be power of 2
	
	if n == 1 return A[0]
	
	w_n = e^{2*pi*i/n}
	w = 1
	
	A0 = [A[0],A[2],...,A[n-2]] 
	A1 = [A[1],A[3],...,A[n-1]]
	
	Y0 = recursive_fft(A0)
	Y1 = recursive_fft(A1)
	
	Y = []*n
	
	for k=0 to n/2 - 1:
		Y[k] = Y0[k] + w*Y1[k]
		Y[k+n/2] = Y0[k] - w*Y1[k]
		w = w*w_n
	
	return Y
```

```text

inverse_fft(Y):
	n = Y.lenght # must be power of 2
	
	if n == 1 return Y[0]
	
	w_n = e^{2*pi*i/n}
	w = 1
	
	Y0 = [Y[0],Y[2],...,Y[n-2]] 
	Y1 = [Y[1],Y[3],...,Y[n-1]]
	
	A0 = inverse_fft(A0)
	A1 = inverse_fft(A1)
	
	A = []*n
	
	for k=0 to n/2 - 1:
		Y[k] = Y0[k] + w*Y1[k]
		Y[k+n/2] = Y0[k] - w*Y1[k]
		w = w*w_n
	
	return Y
```