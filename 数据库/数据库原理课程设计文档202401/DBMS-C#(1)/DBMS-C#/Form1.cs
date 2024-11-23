using System.Diagnostics.Eventing.Reader;
using System.IO;
using System.Security.Principal;
using System.Text.RegularExpressions;
using System.Windows.Forms;

namespace DBMS_C_
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void label3_Click(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            string user_in = Regex.Replace(textBox1.Text, @"\s", "");
            string pswd_in = Regex.Replace(textBox2.Text, @"\s", "");
            bool log = false;
            for (int i = 0; i < Line; i++)
            {

                string user_tb = Regex.Replace(account[i, 0], @"\s", "");
                log = user_in.Equals(user_tb);
                if (log == true)
                {
                    string pswd_tb = Regex.Replace(account[i, 1], @"\s", "");
                    bool judge = pswd_in.Equals(pswd_tb);
                    if (judge == true)
                    {
                        Thread th = new Thread(delegate () { new Form4().ShowDialog(); });
                        th.Start();
                        this.Close();
                        return;

                    }
                    else { MessageBox.Show("密码错误，请重新输入！"); return; }

                }

            }
            if (log == false)
                MessageBox.Show("用户名不存在！");
        }
        int Line = 0;
        string[,] account = new string[20, 2];
        private void Form1_Load(object sender, EventArgs e)
        {
            string path = @"D:\DBMS\Account\account.txt";
            StreamReader rd = File.OpenText(path);
            string s = rd.ReadLine();
            int i = 0;

            while (s != null)
            {
                string[] tmp = Regex.Split(s, "\\s+", RegexOptions.IgnoreCase);
                account[i, 0] = tmp[0];
                account[i, 1] = tmp[1];
                i++;
                s = rd.ReadLine();
            }
            Line = i;
            rd.Close();
            //string pathtb = @"D:\DBMS\Table.dbf";

            //BinaryWriter bw;
            //BinaryReader br;
            //FileStream fs = new FileStream(pathtb, FileMode.OpenOrCreate, FileAccess.Write);

            //bw = new BinaryWriter(fs);
            //string s1 = "Name"; string s2 = "char"; int s3 = 8; string s4 = "101";
            //string s5 = "Stu"; int s6 = 1;
            //bw.Write('~');
            //bw.Write(s5); bw.Write(s6);
            //bw.Write(s1); bw.Write(s2); bw.Write(s3); bw.Write(s4);
            //bw.Write('~');
            //bw.Write("Teacher"); bw.Write(2); bw.Write("Age"); bw.Write("int");
            //bw.Write(8); bw.Write("011"); bw.Write("School"); bw.Write("string"); bw.Write(10);
            //bw.Write("011");
            //bw.Close();




        }

        private void 退出EToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Close();
        }

        private void 登录管理员账户AToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Form2 frm = new Form2();
            frm.ShowDialog();
        }
    }
}