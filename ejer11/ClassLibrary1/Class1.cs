using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ClassLibrary1
{
    public class Class1
    {
        public string InsertarEspacios(string input)
        {
            if (string.IsNullOrEmpty(input))
            {
                return input; // Si la entrada es null o vacía, devolver tal cual
            }

            // Crear un arreglo de caracteres con espacio adicional para los espacios
            char[] resultado = new char[input.Length * 2 - 1];

            for (int i = 0, j = 0; i < input.Length; i++, j += 2)
            {
                resultado[j] = input[i];
                if (j + 1 < resultado.Length)
                {
                    resultado[j + 1] = ' ';
                }
            }

            return new string(resultado);
        }
        public string EliminarUltimoCaracter(string cadena)
        {
            // Verificar si la cadena tiene al menos un carácter
            if (!string.IsNullOrEmpty(cadena))
            {
                // Devolver una subcadena que excluya el último carácter
                return cadena.Substring(0, cadena.Length - 1);
            }
            else
            {
                // Si la cadena está vacía, devolverla tal cual
                return cadena;
            }
        }
        public string EliminarCeroInicial(string cadena)
        {
            // Verificar si la cadena comienza con "0"
            if (cadena.StartsWith("0"))
            {
                // Devolver la subcadena que empieza desde el segundo carácter
                return cadena.Substring(1);
            }
            else
            {
                // Si no comienza con "0", devolver la cadena original
                return cadena;
            }
        }

        public double EvaluatePostfix(string expression)
        {
            Stack<double> stack = new Stack<double>();
            string[] tokens = expression.Split(' ');

            foreach (string token in tokens)
            {
                if (double.TryParse(token, out double number))
                {
                    stack.Push(number);
                }
                else
                {
                    double operand2 = stack.Pop();
                    double operand1 = stack.Pop();
                    double result = 0;

                    switch (token)
                    {
                        case "+":
                            result = operand1 + operand2;
                            break;
                        case "-":
                            result = operand1 - operand2;
                            break;
                        case "*":
                            result = operand1 * operand2;
                            break;
                        case "/":
                            if (operand2 != 0)
                            {
                                result = operand1 / operand2;
                            }
                            else
                            {
                                throw new DivideByZeroException("No se puede dividir por cero.");
                            }
                            break;
                        default:
                            throw new InvalidOperationException($"Operador desconocido: {token}");
                    }

                    stack.Push(result);
                }
            }

            if (stack.Count != 1)
            {
                throw new InvalidOperationException("Expresión inválida.");
            }

            return stack.Pop();
        }

        public string InfixToPostfix(string expression)
        {
            Stack<string> stack = new Stack<string>();
            Queue<string> output = new Queue<string>();
            string[] tokens = expression.Split(' ');

            Dictionary<string, int> precedence = new Dictionary<string, int>
            {
                { "+", 1 },
                { "-", 1 },
                { "*", 2 },
                { "/", 2 },
                { "(", 0 }
            };

            foreach (string token in tokens)
            {
                if (double.TryParse(token, out _))
                {
                    output.Enqueue(token);
                }
                else if (token == "(")
                {
                    stack.Push(token);
                }
                else if (token == ")")
                {
                    while (stack.Count > 0 && stack.Peek() != "(")
                    {
                        output.Enqueue(stack.Pop());
                    }
                    stack.Pop(); // Remove the '(' from the stack
                }
                else
                {
                    while (stack.Count > 0 && precedence[stack.Peek()] >= precedence[token])
                    {
                        output.Enqueue(stack.Pop());
                    }
                    stack.Push(token);
                }
            }

            while (stack.Count > 0)
            {
                output.Enqueue(stack.Pop());
            }

            string[] miArray = output.ToArray();

            return string.Join(" ", miArray);
        }
    }
}
