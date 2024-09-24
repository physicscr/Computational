# calculator/calculations.py


"""Provide several sample math calculations.

This module allows the user to make mathematical calculations.

Examples:
    >>> from calculator import calculations
    >>> calculations.add(2, 4)
    6.0
    >>> calculations.multiply(2.0, 4.0)
    8.0
    >>> from calculator.calculations import divide
    >>> divide(4.0, 2)
    2.0


The module contains the following functions:

- `add(a, b)` - Returns the sum of two numbers.
- `subtract(a, b)` - Returns the difference of two numbers.
- `multiply(a, b)` - Returns the product of two numbers.
- `divide(a, b)` - Returns the quotient of two numbers.
"""


from typing import Union

def add(a: Union[float, int], b: Union[float, int]) -> float:

    """Calcula y retorna la suma de dos numeros
   
    Examples:
        >>> add(4.0, 2.0)
        6.0
        >>> add(4, 2)
        6.0

    Args:
        a : El numero a representa la primer entrada en la suma.
        b : El numero b representa la segunda entrada de la suma.

    Returns:
         El numero que representa la suma aritmetica de 'a' y  'b'
    """
    return float(a + b)

def subtract(a, b):
    """Calcula y retorna la resta de dos numeros
   
    Examples:
        >>> subtract(4.0, 2.0)
        2.0
        >>> subtract(4, 2)
        2.0
        
    Args:
        a (float): El numero a representa la primer entrada en la resta.
        b (float): El numero b representa la segunda entrada de la resta.

    Returns:
        float: El numero que representa la resta aritmetica de 'a' y  'b'
    """
    return float(a - b)

def multiply(a, b):
    """Calcula y retorna la multiplicacion de dos numeros
    
    Examples:
        >>> multiply(4.0, 2.0)
        8.0
        >>> multiply(4, 2)
        8.0

    Args:
        a (float): El numero a representa la primer entrada en la multiplicacion.
        b (float): El numero b representa la segunda entrada de la multiplicacion.

    Returns:
        float: El numero que representa la multiplicacion aritmetica de 'a' y  'b'
    """
    return float(a * b)

def divide(a, b):
    """Calcula y retorna la division de dos numeros
    
	Examples:
		>>> divide(4.0, 2.0)
		2.0
		>>> divide(4, 2)
		2.0

    Args:
        a (float): El numero a representa la primer entrada en la multiplicacion.
        b (float): El numero b representa la segunda entrada de la multiplicacion. Si b es igual a 0 se muestra una alerta.

    Returns:
        float: El numero que representa la multiplicacion aritmetica de 'a' y  'b'
    """
    if b == 0:
        raise ZeroDivisionError("division by zero")
    return float(a / b)
    
