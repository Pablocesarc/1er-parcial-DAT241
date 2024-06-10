using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace WindowsFormsApplication11
{
    public partial class Form2 : Form
    {
        int n,d;
        static string InsertarEspacios(string input)
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
        static string EliminarUltimoCaracter(string cadena)
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
        static string EliminarCeroInicial(string cadena)
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

        static double EvaluatePostfix(string expression)
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

        static string InfixToPostfix(string expression)
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



        public Form2()
        {
            InitializeComponent();
        }

        private void button5_Click(object sender, EventArgs e)
        {
            d=Convert.ToInt16(((Button)sender).Text);
            String mm=d.ToString();
            textBox1.Text = textBox1.Text+mm;
            string aux = EliminarCeroInicial(textBox1.Text);
            textBox1.Text = aux;

        }

        private void button11_Click(object sender, EventArgs e)
        {

            textBox1.Text = textBox1.Text + "+";
        }

        private void button12_Click(object sender, EventArgs e)
        {
            textBox1.Text = textBox1.Text + "-";
        }

        private void button14_Click(object sender, EventArgs e)
        {
            textBox1.Text = textBox1.Text + "/";
        }

        private void button13_Click(object sender, EventArgs e)
        {
            textBox1.Text = textBox1.Text + "*";
        }

        private void button15_Click(object sender, EventArgs e)
        {
            string abc = textBox1.Text;
            string input = InsertarEspacios(abc);
            textBox1.Text = "";
            String res = "";
            try
            {
                string postfix = InfixToPostfix(input);
                textBox3.Text = postfix;
                double result = EvaluatePostfix(postfix);
                res = result.ToString();
                textBox2.Text = res;
            }
            catch (Exception ex)
            {
                textBox2.Text = "Math Error";
            }

        }

        private void button16_Click(object sender, EventArgs e)
        {
            
            string cadenaSinUltimoCaracter = EliminarUltimoCaracter(textBox1.Text);
            textBox1.Text = cadenaSinUltimoCaracter;
        }

        private void button17_Click(object sender, EventArgs e)
        {
            textBox1.Text = "";
            textBox2.Text = "";
        }

        private void button18_Click(object sender, EventArgs e)
        {
            String g=textBox2.Text;
            textBox1.Text = textBox1.Text + g;
        }

        private void Form2_Load(object sender, EventArgs e)
        {
            n = 0;
            textBox1.Text=n.ToString();
        }
    }
}
