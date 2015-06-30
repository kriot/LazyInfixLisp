#LazyInfixLisp

##Features

 * Lazy +
 * Infix operators +
 * Memorizing +
 * Long arithmetic on rational (language specified)
 * Hi-speed structs (vector, set, map) 
 * Math functions 

###Arithmetic
It will be:

  * Long
  * Rational
  * Eps-operations (interprating)

#Syntax

You can use infix notation by the brakets `{`, `}`.
```
(cnk 3 {3+3})
```


##Let
```
(let
	(key1 val1)
	(key2 10)
	(key3 'olo)

	your_code
)
```
Note: `'olo` is string (at interpritation it transforms to its hash) that can be checked for equaly. There is `<` operation based on hash.
At the time of defention the symbols are defened, so there can be recursive defenition. New defenition overrides older (with same name).

##Lambda

Defenition:
```
(\ (a b c) (+ a c))
```
You can write mem after `\` to turn on memorization (for lazy dynamic programming)

TODO: Seems like it doesnt work.
```
(let
  (cnk (\ mem (n k)
      (cond 
        ((< n 0) 0)
        ((< k 0) 0)
        ((< n k) 0)
        ((and (= n 0) (= k 0)) 1)
        (1 (+ (cnk {n-1} {k-1}) (cnk {n-1} {k})))
      )
    ) 
  )
  (cnk 10 3)
)
```
The only way to define a function is define a symbol with lambda function.

##Cond
```
(cond 
	(cond1 val1)
	(cond2 val2)
	...
	(condN valN)
)
```
Value of the first true (non zero) condition will be returned.
The `else` synonim is true (1):
```
(cond 
	(cond1 val1)
	(cond2 val2)
	(1 other)
)
```
Because `1` is always non-zero. 

##IO
There is `read` and `print` functions, but they will be run in order of evaluation (it's unpredictable). I hope monads will solve this problem.

#About
I hope, that main idea is done. Theoretically, I think, it's much better than clisp (explore lambdas: in clisp it's костыль). But threre is one language that is much better in this appications: Haskell. I have found out all my ideas and priciples in it (I was inspired by it). 

It was good work for me. There is way to make this better, but, I think, it will take a lot of time, so I advice to myself to use Haslkell. 
