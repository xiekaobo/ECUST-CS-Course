using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;
using System.Text.RegularExpressions;
using System.Configuration;
using System.Xml.Linq;

namespace DBMS_C_
{
    public struct TableMode
    {
        public string sFieldName;  //字段名
        public string sType;  //字段类型
        public int iSize;  //字长
        public char bKey;  //该字段是否为KEY键
        public char bNullFlag;  //该字段是否允许为空
        public char bValidFlag;  //该字段是否有效，可用于以后对表中该字段的删除
    }


    public partial class Form4 : Form
    {
        public Form4()
        {
            InitializeComponent();
            this.Load += new EventHandler(Form4_Load);
        }
        string pathtb = @"D:\DBMS\Table.dbf";
        string pathdata = @"D:\DBMS\Data.dat";
        string pathtmp = @"D:\DBMS\tmp.dbf";
        int num_table;  //表的数目
        string[,] table = new string[20, 2];   //数组存放每张表的名称和字段数目


        TableMode[][] mode = new TableMode[20][];
        private void Form4_Load(object sender, EventArgs e)
        {
            BinaryReader br;
            FileStream fs = new FileStream(pathtb, FileMode.Open, FileAccess.Read);
            br = new BinaryReader(fs);
            br.BaseStream.Seek(0, SeekOrigin.Begin);

            int i = 0;
            while (br.BaseStream.Position < br.BaseStream.Length) //当字符为表的分割符时
            {
                char x = br.ReadChar(); //从二进制文件读入一个字符
                if (x != '~') return;
                string name = br.ReadString(); //读入表的名称
                table[i, 0] = name;
                int n = br.ReadInt32();//读入表的字段数目
                table[i, 1] = n.ToString();
                mode[i] = new TableMode[n]; //长度为n的结构体数组
                
                for (int j = 0; j < n; j++) //处理每个表的字段
                {
                    mode[i][j].sFieldName = br.ReadString();
                    mode[i][j].sType = br.ReadString();
                    mode[i][j].iSize = br.ReadInt32();
                    string tmp1 = br.ReadString();
                    tmp1 = Regex.Replace(tmp1, @"\s", "");
                    mode[i][j].bKey = tmp1[0];
                    mode[i][j].bNullFlag = tmp1[1];
                    mode[i][j].bValidFlag = tmp1[2];
                }
                i++;


            }
            br.Close();
            num_table = i;
            listBox1.Items.Clear();  //对listbox1进行处理
            for (int j = 0; j < num_table; j++)  //显示所有的表的名称
                listBox1.Items.Add(table[j, 0]);
            //对datagridview1进行操作
            DataTable dt = new DataTable();
            listBox1.SelectedIndex = 0;
            string current = listBox1.SelectedItem.ToString();//listbox中选中的选项
            current = Regex.Replace(current, @"\s", "");
            int line = 0;
            for (int j = 0; j < num_table; j++)
            {
                string nameoftable = Regex.Replace(table[j, 0], @"\s", "");
                bool s = current.Equals(nameoftable);
                if (s) { line = j; }

            }
            int z = 0;
            do
            {
                dt.Columns.Add(mode[line][z].sFieldName, typeof(string));
                z++;
            } while (z < mode[line].Length);

            StreamReader sr = new StreamReader(pathdata);

            string str = sr.ReadToEnd();
            string[] arrstr = Regex.Split(str, "\r\n");
            sr.Close();
            int lno = 0;
            for (int j = 0; j < arrstr.Length - 1; j++)
            {
                string s1 = Regex.Replace(arrstr[j], @"\s", "");
                string s2 = Regex.Replace(arrstr[j + 1], @"\s", "");
                if (s1 == "~")
                    if (current.Equals(s2))
                    { lno = j; }
            }
            int num = Convert.ToInt32(arrstr[lno + 2]);
            int clnm = Convert.ToInt32(arrstr[lno + 3]);
            lno = lno + 4;

            while (lno < arrstr.Length && arrstr[lno] == "#")
            {
                string tmp = Regex.Replace(arrstr[lno], @"\s", "");
                if (tmp != "#") { MessageBox.Show("Data表故障！"); }
                DataRow dr = dt.NewRow();
                for (int j = 0; j < clnm; j++)
                { lno++; dr[j] = arrstr[lno]; }
                dt.Rows.Add(dr);
                lno++;

            }
            this.dataGridView1.DataSource = dt;


        }
        public static int ReplaceLine(string filePath, string name1, string name2)
        {
            // 读取文件的所有行
            string[] lines = File.ReadAllLines(filePath);
            int r=0;
            // 遍历行，查找满足条件的行
            for (int i = 1; i < lines.Length; i++) // 从第二行开始，因为需要检查前一行
            {
                if (lines[i] == name1 && lines[i - 1] == "~")
                {
                    // 满足条件，将当前行替换为 name2
                    lines[i] = name2;
                    r = 1;
                }
            }

            // 将修改后的行写回文件
            File.WriteAllLines(filePath, lines);
            return r;
        }
        public int CREATE_TABLE(string[,]create,int i_tmp,string name)
        {
            //首先看是否存在一个name表
            for (int i = 0; i < num_table; i++)
            {
                string cmp = Regex.Replace(table[i, 0], @"\s", "");
                if (cmp.Equals(name))
                { return 0; MessageBox.Show("表格已存在，无法新建！"); }
            }
            BinaryWriter bw;
            FileStream fs = new FileStream(pathtb, FileMode.Append, FileAccess.Write);
            bw = new BinaryWriter(fs);
            bw.Seek(0, SeekOrigin.End); //向二进制文件追加内容
            bw.Write('~'); //表分隔符
            bw.Write(name); //表名
            
            bw.Write(i_tmp); //字段数目
            for(int i=0;i<i_tmp;i++)
            {
                bw.Write(create[i,0]);
                bw.Write(create[i, 1]);
                bw.Write(10);
                int n1 = Convert.ToInt32(create[i, 2]);
                int n2= Convert.ToInt32(create[i, 3]);
                int n3= Convert.ToInt32(create[i, 4]);
                int n = n1 * 100 + n2 * 10 + n3;
                string s = n.ToString().PadLeft(3,'0');
                bw.Write(s);
            }
            MessageBox.Show("更新完成！");
            StreamWriter writer = new StreamWriter(pathdata,true,System.Text.Encoding.Default);
            writer.WriteLine("~");
            writer.WriteLine(name);
            writer.WriteLine("0");
            writer.WriteLine(i_tmp);

            bw.Close();
            writer.Close();
            this.Hide(); //先隐藏主窗体
            Form4 form4 = new Form4(); //重新实例化此窗体
            form4.ShowDialog();//已模式窗体的方法重新打开
            this.Close();//原窗体关闭
            return 1;
             }
        public static void RemoveContent(string filePath, string targetLine)
        {
            // 读取文件的所有行
            string[] lines = File.ReadAllLines(filePath);

            // 遍历行，查找满足条件的行
            for (int i = 1; i < lines.Length; i++) // 从第二行开始，因为需要检查前一行
            {
                if (lines[i] == targetLine && lines[i - 1] == "~")
                {
                    // 找到目标行，删除从前一行 "~" 到下一个 "~" 之间的内容，保留目标行的下一个 "~"
                    int startIndex = i - 1;
                    int endIndex = FindNextTildeIndex(lines, i + 1);

                    if (endIndex != -1)
                    {
                        // 删除内容
                        Array.Clear(lines, startIndex + 1, endIndex - startIndex);
                    }
                    else
                    {
                        // 目标行没有下一个 "~"，删除从目标行前一行 "~" 到文件末尾的内容
                        Array.Clear(lines, startIndex + 1, lines.Length - startIndex - 1);
                    }

                    break; // 只删除第一次出现的匹配行
                }
            }

            // 将修改后的行写回文件
            File.WriteAllLines(filePath, lines);
        }

        private static int FindNextTildeIndex(string[] lines, int startIndex)
        {
            for (int i = startIndex; i < lines.Length; i++)
            {
                if (lines[i] == "~")
                {
                    return i;
                }
            }

            return -1; // 没有找到下一个 "~"
        }
        public int DROP(string tb)
        {   //首先看是否存在一个tb表
            bool judge = false;
            for (int i = 0; i < num_table; i++)
            {
                string cmp = Regex.Replace(table[i, 0], @"\s", "");
                if (cmp.Equals(tb))
                { judge = true; }
            }
            if (judge == false) { MessageBox.Show("不存在该表！"); return 0; }
            //将Table.dbf的内容复制一份到tmp.dbf
            FileInfo file = new FileInfo(pathtb);
            if (file.Exists)
                file.CopyTo(pathtmp, true);
            File.Delete(pathtb); //删除Table.dbf
            bool isrename1 = false;
            FileStream fs = new FileStream(pathtb, FileMode.Create, FileAccess.Write);
            BinaryWriter writer = new BinaryWriter(fs);
            FileStream fs2 = new FileStream(pathtmp, FileMode.Open, FileAccess.Read);
            BinaryReader reader = new BinaryReader(fs2);
            reader.BaseStream.Position = 0;
            writer.BaseStream.Position = 0;

            for (int i = 0; i < num_table; i++)
            {

                char c1 = reader.ReadChar(); //'~'
                string name = reader.ReadString();//表名
                name = Regex.Replace(name, @"\s", "");
                tb = Regex.Replace(tb, @"\s", "");

                if (name.Equals(tb))
                {
                    int nx = reader.ReadInt32(); //字段数目

                    for (int j = 0; j < nx; j++)
                    {
                        string s1 = reader.ReadString();//字段名

                        string s2 = reader.ReadString();//字段类型

                        int s3 = reader.ReadInt32();  //字长

                        string s4 = reader.ReadString(); //Others

                    }
                    isrename1 = true;
                }
                else
                {
                    writer.Write(c1);
                    writer.Write(name);
                    int n = reader.ReadInt32(); //字段数目
                    writer.Write(n);
                    for (int j = 0; j < n; j++)
                    {
                        string s1 = reader.ReadString();//字段名
                        writer.Write(s1);
                        string s2 = reader.ReadString();//字段类型
                        writer.Write(s2);
                        int s3 = reader.ReadInt32();  //字长
                        writer.Write(s3);
                        string s4 = reader.ReadString(); //Others
                        writer.Write(s4);
                    }


                }
            }
            writer.Close();
            reader.Close();
            if (isrename1 == false)
            { MessageBox.Show("DROP第一阶段失败！"); return 0; }
            RemoveContent(pathdata, tb);
            MessageBox.Show("更新完成！");
            this.Hide(); //先隐藏主窗体
            Form4 form4 = new Form4(); //重新实例化此窗体
            form4.ShowDialog();//已模式窗体的方法重新打开
            this.Close();//原窗体关闭
            return 1;
        }
        public int INSERT(string[]combox,int i_tmp,string tb_name)
        {

            return 1;
        }
        public int RENAME(string name1,string name2)
        {   //首先看是否存在一个name1表
            bool judge=false;
            for (int i = 0; i < num_table; i++)
            {
                string cmp = Regex.Replace(table[i, 0], @"\s", "");
                if (cmp.Equals(name1))
                { judge = true; }
            }
            if (judge == false) { MessageBox.Show("不存在该表！"); return 0; }
            //将Table.dbf的内容复制一份到tmp.dbf
            FileInfo file=new FileInfo(pathtb);
            if (file.Exists)
                file.CopyTo(pathtmp, true);
            File.Delete(pathtb); //删除Table.dbf
            bool isrename1=false;
            FileStream fs = new FileStream(pathtb, FileMode.Create, FileAccess.Write);
            BinaryWriter writer= new BinaryWriter(fs);
            FileStream fs2 = new FileStream(pathtmp, FileMode.Open, FileAccess.Read);
            BinaryReader reader= new BinaryReader(fs2);
            reader.BaseStream.Position = 0;
            writer.BaseStream.Position = 0;
            for (int i=0;i<num_table;i++)
            {
                char c1=reader.ReadChar(); //'~'
                writer.Write(c1);
                string name=reader.ReadString();//表名
                name = Regex.Replace(name, @"\s", "");
                name1 = Regex.Replace(name1, @"\s","");

                if (name.Equals(name1))
                {
                    name2 = Regex.Replace(name2, @"\s", "");
                    writer.Write(name2); //对名字进行替换
                    isrename1=true;
                }
                else { writer.Write(name); }
                int n=reader.ReadInt32(); //字段数目
                writer.Write(n);
                for(int j=0;j<n;j++)
                {
                    string s1=reader.ReadString();//字段名
                    writer.Write(s1);
                    string s2 = reader.ReadString();//字段类型
                    writer.Write(s2);
                    int s3=reader.ReadInt32();  //字长
                    writer.Write(s3);
                    string s4=reader.ReadString(); //Others
                    writer.Write(s4);
                }
               
               
            } 
            writer.Close();
            reader.Close();
            if (isrename1 == false)
            { MessageBox.Show("改名第一阶段失败！"); return 0; }
            //RENAME 第二阶段
            int r = ReplaceLine(pathdata, name1, name2);
            if (r == 0) { MessageBox.Show("改名第二阶段失败！"); return 0; }
            MessageBox.Show("更新完成！");
            this.Hide(); //先隐藏主窗体
            Form4 form4 = new Form4(); //重新实例化此窗体
            form4.ShowDialog();//已模式窗体的方法重新打开
            this.Close();//原窗体关闭
            return 1;
        }
        public int SQL(string[]command) {  //对一个语句进行操作
            int j = 0; //第一个单词
            string current = Regex.Replace(command[j], @"\s", "");
            switch(current)
                {
                case "CREATE":
                    string[,] create = new string[20, 5]; //新表的信息
                    j++; //取下一个单词
                    current = Regex.Replace(command[j], @"\s", "");
                    if (current != "TABLE") { MessageBox.Show("语句错误：在CREATE后缺少TABLE！"); return 0; }
                    j++; //取下一个单词
                    current = Regex.Replace(command[j], @"\s", "");
                    if (current.EndsWith("("))  //当name和(合在一起写的时候
                    current = current.Substring(0, current.LastIndexOf("(")); //此时current代表新建表的表名
                        string name = current;
                        int i_tmp=0; //表相数
                        bool judge = true;
                        string jd = Regex.Replace(command[j + 1], @"\s", ""); 
                        if(jd.Equals(")")) { judge = false;  MessageBox.Show("语句错误：未获取到表项的相关数据！");return 0; }
                        while (judge)
                        {
                            j++;  //取下一个单词
                            current = Regex.Replace(command[j], @"\s", "");
                            create[i_tmp,0]=current;
                            j++;  //取下一个单词
                            current = Regex.Replace(command[j], @"\s", "");
                            create[i_tmp, 1] = current;
                            j++;  //取下一个单词
                            current = Regex.Replace(command[j], @"\s", "");
                            create[i_tmp, 2] = current;
                            j++;  //取下一个单词
                            current = Regex.Replace(command[j], @"\s", "");
                            create[i_tmp, 3] = current;
                            j++;  //取下一个单词
                            current = Regex.Replace(command[j], @"\s", "");
                            if(current.EndsWith(","))
                            current=current.Substring(0,current.LastIndexOf(","));
                            create[i_tmp, 4] = current;
                            jd = Regex.Replace(command[j + 1], @"\s", "");
                            i_tmp++;
                            if (jd.Equals(")")) { judge = false; }
                        }
                        j++; //取下一个单词 ")"
                        current = Regex.Replace(command[j], @"\s", "");
                        if (!current.Equals(")")) { MessageBox.Show("语法错误！未看到)"); return 0; }
                        j++; //取下一个单词 "INTO"
                        current = Regex.Replace(command[j], @"\s", "");
                        if (!current.Equals("INTO")) { MessageBox.Show("语法错误！未看到INTO"); return 0; }
                        //此时语法分析通过，执行相应的语义
                        int v = CREATE_TABLE(create, i_tmp,name);
                        if (v == 0) { MessageBox.Show("执行错误！"); return 0; }
                        else return 1;

                    break;
                
                case "RENAME": //更改表名
                    string name1, name2; //name1为原表名 name2为新表名
                    j++; //取下一个单词
                    current = Regex.Replace(command[j], @"\s", "");
                    if (current != "TABLE") { MessageBox.Show("语句错误：在RENAME后缺少TABLE！"); return 0; }
                    j++; //取下一个单词
                    current = Regex.Replace(command[j], @"\s", "");
                    name1 = current;
                    j++; //取下一个单词
                    current = Regex.Replace(command[j], @"\s", "");
                    name2 = current;
                    j++; //取下一个单词 IN
                    current = Regex.Replace(command[j], @"\s", "");
                    if (current != "IN") { MessageBox.Show("语句错误"); return 0; }
                    int respond = RENAME(name1, name2);
                    if (Convert.ToBoolean(respond)) return 1;
                    return 0;
                    break;
                case "DROP":
                    j++; //取下一个单词
                    current = Regex.Replace(command[j], @"\s", "");
                    if (current != "TABLE") { MessageBox.Show("语句错误：在DROP后缺少TABLE！"); return 0; }
                    j++; //取下一个单词
                    current = Regex.Replace(command[j], @"\s", "");
                    string tb_del = current; //要删除表的名称
                    j++; //取下一个单词 
                    current = Regex.Replace(command[j], @"\s", "");
                    if (current != "IN") { MessageBox.Show("语句错误"); return 0; }
                    int r = DROP(tb_del);
                    if (r == 0) { MessageBox.Show("更新失败！"); return 0; }
                    return 1;
                    break;
                case "INSERT": //插入元组
                    string[] combox = new string[20];
                    int i_tmp1 = 0;
                    j++;
                    current = Regex.Replace(command[j], @"\s", "");
                    if (current != "INTO") { MessageBox.Show("语句错误：在INSERT后缺少INTO！"); return 0; }
                    j++;
                    current = Regex.Replace(command[j], @"\s", "");
                    string tb_name=current;  //对应要插入元组的表
                    j++;
                    current = Regex.Replace(command[j], @"\s", "");//VALUES(
                    j++;
                    bool jud2 = true;
                    while (jud2)
                    { current = Regex.Replace(command[j], @"\s", "");
                        if (current.EndsWith(")"))
                        { jud2 = false; current = current.Substring(0, current.LastIndexOf(")")); }
                        if (current.EndsWith(","))
                            current = current.Substring(0, current.LastIndexOf(","));
                        combox[i_tmp1] = current;
                        i_tmp1++;
                    }
                    j++;
                    current = Regex.Replace(command[j], @"\s", "");// IN
                    return 1;
                    break;
                default:    return 0;
            }

                
               
            

        }

        private void button1_Click(object sender, EventArgs e)
        {
            BinaryWriter bw;
            BinaryReader br;
            FileStream fs = new FileStream(pathtb, FileMode.OpenOrCreate, FileAccess.Write);

            bw = new BinaryWriter(fs);
            string s1 = "Name"; string s2 = "char"; int s3 = 8; string s4 = "101";
            string s5 = "Stu"; int s6 = 1;

            bw.Write(s5); bw.Write(s6);
            bw.Write(s1); bw.Write(s2); bw.Write(s3); bw.Write(s4);
            bw.Close();
            FileStream fr = new FileStream(pathtb, FileMode.Open, FileAccess.Read);
            br = new BinaryReader(fr);
            string s = br.ReadString();
            listBox1.Items.Clear();
            listBox1.Items.Add(s);
        }

        string[][] command = new string[20][];  //单条指令数组
        string[] order_tmp= new string[20]; //中间数组，用于存放一条指令（单指令）
        private void button2_Click(object sender, EventArgs e)
        {
            int lines = richTextBox1.Lines.Length;
            string[] order = new string[lines];
            for (int i = 0; i < lines; i++)
            {
                string value = string.Empty;
                if (i == lines - 1)
                {
                    int startIndex = richTextBox1.GetFirstCharIndexFromLine(i);
                    value = richTextBox1.Text.Substring(startIndex, richTextBox1.Text.Length - startIndex);
                }
                else
                {
                    int startIndex = richTextBox1.GetFirstCharIndexFromLine(i);
                    int endIndex = richTextBox1.GetFirstCharIndexFromLine(i + 1) - 1;
                    value = richTextBox1.Text.Substring(startIndex, endIndex - startIndex + 1);
                }
                order[i] = value;

            }
            for (int i = 0; i < lines; i++)
                order[i] = new Regex("[\\s]+").Replace(order[i], " ");
            int i_tmp = 0;
            for (int i = 0; i < lines; i++)
            {
                string[] tmp = order[i].Split( ';' ); //将指令以分号进行分割
                for (int j = 0; j < tmp.Length; j++)
                {
                    order_tmp[i_tmp] = tmp[j];
                    i_tmp++;
                }
            }
            for(int i=0;i<i_tmp;i++) //将单指令以空格分割取出每个单词
            {
                string[] tmp = order_tmp[i].Split(' ');
                command[i]=new string[tmp.Length];
                for(int j=0;j<tmp.Length;j++)
                    command[i][j] = tmp[j];
            }
            //现在command中存放的就是每条单指令的每个单词了
            //对每一个语句进行分析
            for (int i = 0; i < i_tmp; i++)
                SQL(command[i]);
                
           
            
        }
            private void tabPage1_Click(object sender, EventArgs e)
        {
            this.Hide(); //先隐藏主窗体
            Form4 form4 = new Form4(); //重新实例化此窗体
            form4.ShowDialog();//已模式窗体的方法重新打开
            this.Close();//原窗体关闭
        }

        private void listBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            //对datagridview1进行操作
            DataTable dt = new DataTable();
            string current = listBox1.SelectedItem.ToString();//listbox中选中的选项
            current = Regex.Replace(current, @"\s", "");
            int line = 0;
            for (int j = 0; j < num_table; j++)
            {
                string nameoftable = Regex.Replace(table[j, 0], @"\s", "");
                bool s = current.Equals(nameoftable);
                if (s) { line = j; }

            }
            int z = 0;
            do
            {
                dt.Columns.Add(mode[line][z].sFieldName, typeof(string));
                z++;
            } while (z < mode[line].Length);

            StreamReader sr = new StreamReader(pathdata);

            string str = sr.ReadToEnd();
            string[] arrstr = Regex.Split(str, "\r\n");
            sr.Close();
            int lno = 0;
            for (int j = 0; j < arrstr.Length - 1; j++)
            {
                string s1 = Regex.Replace(arrstr[j], @"\s", "");
                string s2 = Regex.Replace(arrstr[j + 1], @"\s", "");
                if (s1 == "~")
                    if (current.Equals(s2))
                    { lno = j; }
            }
            int num = Convert.ToInt32(arrstr[lno + 2]);
            int clnm = Convert.ToInt32(arrstr[lno + 3]);
            lno = lno + 4;

            while (lno < arrstr.Length && Regex.Replace(arrstr[lno],@"\s","")=="#")
            {
                string tmp = Regex.Replace(arrstr[lno], @"\s", "");
                if (tmp != "#") { MessageBox.Show("Data表故障！"); }
                DataRow dr = dt.NewRow();
                for (int j = 0; j < clnm; j++)
                { lno++; dr[j] = arrstr[lno]; }
                dt.Rows.Add(dr);
                lno++;

            }
            this.dataGridView1.DataSource = dt;
        }
    }
}
