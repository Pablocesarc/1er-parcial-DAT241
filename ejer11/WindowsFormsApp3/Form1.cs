using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApp3
{
    public partial class Form1 : Form
    {
        int n, d;
        ClassLibrary1.Class1 cl = new ClassLibrary1.Class1();
        public Form1()
        {
            InitializeComponent();
        }

        private void button12_Click(object sender, EventArgs e)
        {
            textBox1.Text = textBox1.Text + "+";

        }

        private void button11_Click(object sender, EventArgs e)
        {
            textBox1.Text = textBox1.Text + "-";
        }

        private void button13_Click(object sender, EventArgs e)
        {
            textBox1.Text = textBox1.Text + "*";
        }

        private void button14_Click(object sender, EventArgs e)
        {
            textBox1.Text = textBox1.Text + "/";
        }

        private void button15_Click(object sender, EventArgs e)
        {
            string abc = textBox1.Text;
            string input = cl.InsertarEspacios(abc);
            textBox4.Text = input;
            textBox1.Text = "0";
            String res = "";
            try
            {
                string postfix = cl.InfixToPostfix(input);
                textBox3.Text = postfix;
                double result = cl.EvaluatePostfix(postfix);
                res = result.ToString();
                textBox2.Text = res;
            }
            catch (Exception ex)
            {
                textBox2.Text = "Math Error";
            }
        }

        private void button18_Click(object sender, EventArgs e)
        {
            textBox1.Text = "0";
            textBox2.Text = "";
            textBox3.Text = "";
            textBox4.Text = "";
        }

        private void button17_Click(object sender, EventArgs e)
        {
            String g = textBox2.Text;
            textBox1.Text = textBox1.Text + g;
        }

        private void button16_Click(object sender, EventArgs e)
        {
            string cadenaSinUltimoCaracter = cl.EliminarUltimoCaracter(textBox1.Text);
            textBox1.Text = cadenaSinUltimoCaracter;
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            n = 0;
            textBox1.Text = n.ToString();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            d = Convert.ToInt16(((Button)sender).Text);
            String mm = d.ToString();
            textBox1.Text = textBox1.Text + mm;
            string aux = cl.EliminarCeroInicial(textBox1.Text);
            textBox1.Text = aux;
        }

   
        

       
    }
}
