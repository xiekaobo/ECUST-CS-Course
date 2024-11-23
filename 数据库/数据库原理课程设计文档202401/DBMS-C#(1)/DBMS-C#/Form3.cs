using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace DBMS_C_
{
    public partial class Form3 : Form
    {
        public Form3()
        {
            InitializeComponent();
        }

        private void Form3_Load(object sender, EventArgs e)
        {
            richTextBox1.Clear();
            richTextBox1.Text += "用户名                密码\n ";
            string path = @"D:\DBMS\Account\account.txt";
            StreamReader reader = new StreamReader(path, System.Text.Encoding.Default);
            reader.BaseStream.Seek(0, SeekOrigin.Begin);
            string line = reader.ReadLine();
            while (line != null)
            {
                richTextBox1.Text += line + "\n";
                line = reader.ReadLine();
            }
            reader.Close();
        }

        private void richTextBox1_TextChanged(object sender, EventArgs e)
        {

        }
    }
}
