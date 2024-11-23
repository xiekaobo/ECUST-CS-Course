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
using System.Security.Policy;
using System.Reflection;
using static System.Windows.Forms.VisualStyles.VisualStyleElement;
using System.Diagnostics;

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
                dt.Columns.Add(mode[line][z].sFieldName + '(' + mode[line][z].bNullFlag+')', typeof(string));
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
        public static void InsertContent(string filePath, string targetLine, int numLines, string[] combox)
        {
            // 读取文件的所有行
            List<string> lines = new List<string>(File.ReadAllLines(filePath));

            // 查找满足条件的行
            int targetIndex = -1;
            for (int i = 1; i < lines.Count; i++) // 从第二行开始，因为需要检查前一行
            {
                if (lines[i] == targetLine && lines[i - 1] == "~")
                {
                    targetIndex = i;
                    break; // 只找第一次出现的匹配行
                }
            }

            // 如果找到了目标行
            if (targetIndex != -1)
            {
                // 找到目标行的下一个 "~" 或者文章的末尾作为TAG行
                int tagIndex = FindTagIndex(lines, targetIndex + 1);

                // 获取实际需要插入的行数（取 numLines 和 combox 数组长度的较小值）
                //int actualNumLines = Math.Min(numLines, combox.Length);

                // 插入指定行数的内容在TAG行的前面
                for (int i = 0; i < numLines; i++)
                {
                    lines.Insert(tagIndex, combox[i]);
                    tagIndex++; // 更新TAG行的位置
                }
                if (targetIndex + 1 < lines.Count)
                {
                    if (int.TryParse(lines[targetIndex + 1], out int nextLine))
                    {
                        nextLine += 1;
                        lines[targetIndex + 1] = nextLine.ToString();
                    }
                }
            }

            // 将修改后的行写回文件
            File.WriteAllLines(filePath, lines);
        }

        private static int FindTagIndex(List<string> lines, int startIndex)
        {
            for (int i = startIndex; i < lines.Count; i++)
            {
                if (lines[i] == "~")
                {
                    return i;
                }
            }
            return lines.Count; // 如果没有找到下一个 "~"，则返回文章的末尾
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
        public static int ProcessFileContent_UPDATE(string filePath, string tb_name, int column1, string field1, int column2, string field2)
        {
            // 读取文件的所有行
            List<string> lines = new List<string>(File.ReadAllLines(filePath));

            // 找到目标行的索引
            int index = FindTargetIndex2(lines, tb_name);
            if (index == -1)
            {
                return -1; // 未找到目标行
            }

            // 检查 index 下面一行是否为 0
            if (index + 1 < lines.Count && lines[index + 1].Trim() == "0")
            {
                return 0; // 下一行为 0，返回 0
            }

            // 找到 TAG 行的索引
            int tagIndex = FindTagIndex2(lines, index + 1);

            // 找到所有 "#" 行的索引
            List<int> start = new List<int>();
            for (int i = index + 1; i < tagIndex; i++)
            {
                if (lines[i].Trim() == "#")
                {
                    start.Add(i);
                }
            }

            // 遍历 start 数组并进行修改操作
            for (int i = 0; i < start.Count; i++)
            {
                int startIndex = start[i];
                int endIndex = (i == start.Count - 1) ? tagIndex : start[i + 1]; // 如果是最后一个元素，endIndex 为 tagIndex

                // 检查从 startIndex 后面 column2 行的内容是否与 field2 相等，如果相等则修改指定范围的内容为 field1
                if (startIndex + column2 < lines.Count && lines[startIndex + column2].Trim() == field2)
                {
                    for (int j = startIndex; j < startIndex + column1 && j < lines.Count; j++)
                    {
                        lines[j+1] = field1;
                    }
                }
            }

            // 将修改后的行写回文件
            File.WriteAllLines(filePath, lines);

            return 1; // 操作完成
        }

        private static int FindTargetIndex2(List<string> lines, string tb_name)
        {
            for (int i = 1; i < lines.Count; i++) // 从第二行开始，因为需要检查前一行
            {
                if (lines[i].Trim() == tb_name && lines[i - 1].Trim() == "~")
                {
                    return i; // 返回目标行的索引
                }
            }
            return -1; // 未找到目标行
        }

        private static int FindTagIndex2(List<string> lines, int startIndex)
        {
            for (int i = startIndex; i < lines.Count; i++)
            {
                if (lines[i].Trim() == "~")
                {
                    return i; // 返回 TAG 行的索引
                }
            }
            return lines.Count; // 如果没有找到下一个 "~"，则返回文章的末尾
        }
        public static int ProcessFileContent(string filePath, string tb_name, int column, string field)
        {
            // 读取文件的所有行
            List<string> lines = new List<string>(File.ReadAllLines(filePath));

            // 找到目标行的索引
            int index = FindTargetIndex(lines, tb_name);
            if (index == -1)
            {
                return -1; // 未找到目标行
            }

            // 检查 index 下面一行是否为 0
            if (index + 1 < lines.Count && lines[index + 1] == "0")
            {
                return 0; // 下一行为 0，返回 0
            }

            // 找到 TAG 行的索引
            int tagIndex = FindTagIndex1(lines, index + 1);

            // 找到所有 "#" 行的索引
            List<int> start = new List<int>();
            for (int i = index + 1; i < tagIndex; i++)
            {
                if (lines[i] == "#")
                {
                    start.Add(i);
                }
            }
            int count = 0;
            // 遍历 start 数组并进行删除操作
            for (int i = 0; i < start.Count; i++)
            {
                int startIndex = start[i];
                int endIndex = (i == start.Count - 1) ? tagIndex : start[i + 1]; // 如果是最后一个元素，endIndex 为 tagIndex

                // 检查从 startIndex 后面 column 行的内容是否与 field 相等，如果相等则删除指定范围的内容
                if (startIndex + column < lines.Count && lines[startIndex + column] == field)
                {
                    if (i == start.Count - 1)
                    {
                        // 如果 start[i] 是 start 中最后一个元素，并且后面 column 行的内容与 field 相等，则删除 start[i] 到下一个“~”之间的内容
                        lines.RemoveRange(startIndex, tagIndex-startIndex);
                    }
                    else
                    {
                        // 删除从 start[i] 到 start[i+1] 行的内容（不包含 start[i+1]）
                        lines.RemoveRange(startIndex, endIndex - startIndex);
                    }
                    count++;
                }
            }
            int num = Convert.ToInt32(lines[index + 1]);
            num = num - count;
            if (num == 0) MessageBox.Show("没有数据获得更新！");
            lines[index+1]=num.ToString();
            // 将修改后的行写回文件
            File.WriteAllLines(filePath, lines);
            MessageBox.Show("更新完成！");
            return 1; // 操作完成
        }

        private static int FindTargetIndex(List<string> lines, string tb_name)
        {
            for (int i = 1; i < lines.Count; i++) // 从第二行开始，因为需要检查前一行
            {
                if (lines[i] == tb_name && lines[i - 1] == "~")
                {
                    return i; // 返回目标行的索引
                }
            }
            return -1; // 未找到目标行
        }

        private static int FindTagIndex1(List<string> lines, int startIndex)
        {
            for (int i = startIndex; i < lines.Count; i++)
            {
                if (lines[i] == "~")
                {
                    return i; // 返回 TAG 行的索引
                }
            }
            return lines.Count; // 如果没有找到下一个 "~"，则返回文章的末尾
        }
        public int INSERT(string[]combox,int i_tmp,string tb_name)
        {
            string tb_name1 = Regex.Replace(tb_name, @"\s", "");
            string[] cmnw = new string[i_tmp + 1];
            cmnw[0] = "#";
            for (int i = 1; i < i_tmp + 1; i++)
                cmnw[i] = combox[i - 1];
            InsertContent(pathdata, tb_name1, i_tmp+1, cmnw);
            MessageBox.Show("更新完成!");
            this.Hide(); //先隐藏主窗体
            Form4 form4 = new Form4(); //重新实例化此窗体
            form4.ShowDialog();//已模式窗体的方法重新打开
            this.Close();//原窗体关闭
            return 1;
        }
        public int DELETE(string tb,string field,string content)
        {
            int lineno = 0;
            //首先看是否存在一个tb表
            bool judge = false;
            for (int i = 0; i < num_table; i++)
            {
                string cmp = Regex.Replace(table[i, 0], @"\s", "");
                if (cmp.Equals(tb))
                { judge = true; lineno = i; }
            }
            if (judge == false) { MessageBox.Show("不存在该表！"); return 0; }
            int columnno = 0;
            //检查是否有这个字段
            judge = false;
            int size = 0;
            for (int j = 0; j < mode[lineno].Length; j++)
            {
                string cmp = Regex.Replace(mode[lineno][j].sFieldName, @"\s", "");
                if (cmp.Equals(field))
                { judge = true; columnno = j; size = mode[lineno][j].iSize; }

            }
            if (judge == false) { MessageBox.Show("不存在该字段！"); return 0; }
            //对表进行删除操作
            content = Regex.Replace(content, @"\s", "");
            int re = ProcessFileContent(pathdata, tb, columnno + 1, content);
            if (re == 0) { MessageBox.Show("更新失败！"); return 0; }
            else 
            this.Hide(); //先隐藏主窗体
            Form4 form4 = new Form4(); //重新实例化此窗体
            form4.ShowDialog();//已模式窗体的方法重新打开
            this.Close();//原窗体关闭
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
        public int UPDATE(string tb_name, string field1, string cont1, string field2, string cont2)  //UPDATE
        {
            //检查表是否存在
            int lineno = 0;
            bool judge = false;
            for (int i = 0; i < num_table; i++)
            {
                string cmp = Regex.Replace(table[i, 0], @"\s", "");
                if (cmp.Equals(tb_name))
                { judge = true; lineno = i; }
            }
            if (judge == false) { MessageBox.Show("不存在该表！"); return 0; }

          
            //检查field1和field2是否存在
            bool f1 = false;
            bool f2 = false;
            int columnno1 = 0;
            int columnno2 = 0;
     
            for (int j = 0; j < mode[lineno].Length; j++)
            {
                string cmp = Regex.Replace(mode[lineno][j].sFieldName, @"\s", "");
                if (cmp.Equals(field1))
                { f1 = true; columnno1 = j;  }
                if (cmp.Equals(field2))
                { f2 = true; columnno2 = j;  }
            }
            if (!((f1==true)&&(f2==true))) { MessageBox.Show("不存在该字段！"); return 0; }

            //对文件进行修改
            int res1=ProcessFileContent_UPDATE(pathdata, tb_name, columnno1+1, cont1, columnno2+1, cont2);
            if (res1 == 0) { MessageBox.Show("更新失败！"); }
            else MessageBox.Show("更新成功！");
            this.Hide(); //先隐藏主窗体
            Form4 form4 = new Form4(); //重新实例化此窗体
            form4.ShowDialog();//已模式窗体的方法重新打开
            this.Close();//原窗体关闭
            return 1;
        }
        public void singalselect(string tb_name, string[]set,string field,string cont) //单表查询
        {
            int lineno = 0;
            for(int i=0;i<num_table;i++) //找到表的所在行数
            {
                string cmp = Regex.Replace(tb_name, @"\s", "");
                bool jud = cmp.Equals(tb_name);
                if (jud == true) { lineno = i; }
            }
            int[] colum = new int[set.Length];  //存放属性所在的列号
            for(int i=0;i<set.Length;i++)
                for(int j1 = 0; j1 < mode[lineno].Length;j1++)
                {
                    string cmp1 = Regex.Replace(mode[lineno][j1].sFieldName, @"\s", "");
                    if (set[i].Equals(cmp1))
                    { colum[i] = j1; }
                }
            dataGridView2.DataSource = null; //重置
            //对文件和datagridview2进行操作
            DataTable dt = new DataTable();
            for(int i=0;i<set.Length;i++)
                dt.Columns.Add(set[i].ToString());
            StreamReader sr = new StreamReader(pathdata);

            string str = sr.ReadToEnd();
            string[] arrstr = Regex.Split(str, "\r\n");
            sr.Close();
            //找到field所在的列号
            int linef = 0;
            for (int i = 0; i < mode[lineno].Length; i++)
                if (mode[lineno][i].sFieldName.Equals(field))
                    linef = i;
            int index = 0; //索引行 
            int tag = 0;   //tag行
            for(int i=0;i<arrstr.Length-1;i++)
            {
                if (arrstr[i].Equals("~") && arrstr[i+1].Equals(tb_name))
                {
                    index = i+1;
                }
            }
            for (int i = index; i < arrstr.Length; i++)//从索引行到下一个“~”处
            {
                if (arrstr[i] == "~") tag = i;
                else if (i == arrstr.Length - 1) tag = arrstr.Length - 1;
            }
            int[] searchnode = new int[Convert.ToInt32(index + 1)];
            int j = 0;
            //找到每个开始查找的起始点
            for (int i = index; i < tag; i++)
                if (arrstr[i].Equals("#"))
            { searchnode[j] = i; j++; }
            //对每个起始点进行操作：
            j = 0;
            while(j<searchnode.Length)
            {
                if (arrstr[searchnode[j]+linef+1].Equals(cont))  //满足条件的元组
                {
                    DataRow dr=dt.NewRow();
                    int x = 0;

                    for(x=0;x<colum.Length;x++)
                    {
                        dr[x] = arrstr[searchnode[j] + colum[x] + 1];
                    }
                    dt.Rows.Add(dr);
                        
                }
                j++;
            }

            this.dataGridView2.DataSource=dt;
        }
        public void multiplesearch(string[] tb, string[]set,string connect)  // 多表连接查询(LITE)
        {
            int d = set.Length;
            int lineno1 = 0; int lineno2 = 0; //分别存放两张表的行号
            bool j1 = false,j2 = false;
            for (int i = 0; i < 20; i++)
            {
                if (table[i, 0].Equals(tb[0]))
                { lineno1 = i; j1 = true; }
                if (table[i, 0].Equals(tb[1]))
                { lineno2 = i; j2 = true; }
                if (j1 == true && j2 == true) break;
                
            }
            dataGridView2.DataSource = null; //重置
            DataTable dt=new DataTable();
            for (int i = 0; i < set.Length; i++)
                dt.Columns.Add(set[i]);
            int cno1 = 0; int cno2 = 0; //存放两张表的属性个数
            cno1 = mode[lineno1].Length;
            cno2 = mode[lineno2].Length;
            string[,] t1 = new string[30, cno1];
            string[,]t2=new string[30, cno2];
            int j = 0;
            for(int i=0;i<30;i++)  //初始化
                for( j=0;j<cno1;j++)
            { t1[i, j] = "#"; }
            for (int i = 0; i < 30; i++)
                for ( j = 0; j < cno2; j++)
                { t2[i, j] = "#"; }
            StreamReader sr = new StreamReader(pathdata);
            string str = sr.ReadToEnd();
            string[] arrstr = Regex.Split(str, "\r\n");
            sr.Close();
            //找到第一个表的所有数据
            int index1 = 0;
            int tag1 = 0;

            for (int i = 0; i < arrstr.Length - 1; i++)
            {
                if (arrstr[i].Equals("~") && arrstr[i + 1].Equals(tb[0]))
                {
                    index1 = i + 1;
                }
            }
            for (int i = index1; i < arrstr.Length; i++)//从索引行到下一个“~”处
            {
                if (arrstr[i] == "~") { tag1 = i; break; }
                else if (i == arrstr.Length - 1) tag1 = arrstr.Length - 1;
            }
            int[] searchnode1 = new int[Convert.ToInt32(arrstr[index1 + 1])];

            //找到每个开始查找的起始点
            j = 0;
            for (int i = index1; i < tag1; i++)
                if (arrstr[i].Equals("#"))
                { searchnode1[j] = i; j++; }

            //找到第2个表的所有数据
            int index2 = 0;
            int tag2 = 0;

            for (int i = 0; i < arrstr.Length - 1; i++)
            {
                if (arrstr[i].Equals("~") && arrstr[i + 1].Equals(tb[1]))
                {
                    index2 = i + 1;
                }
            }
            for (int i = index2; i < arrstr.Length; i++)//从索引行到下一个“~”处
            {
                if (arrstr[i] == "~") { tag2 = i; break; }
                else if (i == arrstr.Length - 1) tag2 = arrstr.Length - 1;
            }
            int[] searchnode2 = new int[Convert.ToInt32(arrstr[index2 + 1])];
             j = 0;
            //找到每个开始查找的起始点
            for (int i = index2; i < tag2; i++)
                if (arrstr[i].Equals("#"))
                { searchnode2[j] = i; j++; }

            for (int i = 0; i < searchnode1.Length; i++)
            { for (int z = 0; z < cno1; z++)
                    t1[i, z] = arrstr[searchnode1[i] + z + 1];
            }
            for (int i = 0; i < searchnode2.Length; i++)
            {
                for (int z = 0; z < cno2; z++)
                    t2[i, z] = arrstr[searchnode2[i] + z + 1];
            }
            //找到connect对应的列号
            int conl1 = 0; int conl2 = 0;
            for (int i = 0; i < mode[lineno1].Length; i++)
            {
                if (mode[lineno1][i].sFieldName.Equals(connect)) { conl1 = i; }
            }
            for (int i = 0; i < mode[lineno2].Length; i++)
            {
                if (mode[lineno2][i].sFieldName.Equals(connect)) { conl2 = i; }
            }
            //将数组t1 t2进行处理，整合后的表保存在MAIN中
            bool[] setisselected = new bool[set.Length];
            //初始化
            for (int i = 0; i < set.Length; i++) setisselected[i] = false;
            int[] setint1= new int[set.Length];
            for (int i = 0; i < set.Length; i++) setint1[i] = -1;//初始化
            int[] setint2 = new int[set.Length];
            for (int i = 0; i < set.Length; i++) setint2[i] = -1;//初始化
            int nt1 = 0;
            for(int i = 0; i < mode[lineno1].Length;i++)
            {
                string cmp6 = mode[lineno1][i].sFieldName;
                for(int m=0;m<set.Length;m++)
                {
                    string cmp7 = Regex.Replace(set[m], @"\s", "");
                    if (cmp7.Equals(cmp6) && setisselected[m]==false) { setisselected[m] = true; setint1[nt1] = i; nt1++; }
                }
                
            }
            int nt2 = 0;
            for (int i = 0; i < mode[lineno2].Length; i++)
            {
                string cmp6 = mode[lineno2][i].sFieldName;
                for (int m = 0; m < set.Length; m++)
                {
                    string cmp7 = Regex.Replace(set[m], @"\s", "");
                    if (cmp7.Equals(cmp6) && setisselected[m] == false) { setisselected[m] = true; setint2[nt2] = i; nt2++; }
                }

            }
            string[,] MAIN = new string[30, set.Length];
            int i_main = 0; int p_main = 0;
            for(int i=0;i<searchnode1.Length;i++) //对于t1数组中的每一行进行处理
            {
                //看它的connect和t2中是否有相同的
                string cmp1 = Regex.Replace(t1[i, conl1], @"\s", "");
                for(int z=0;z<searchnode2.Length;z++)
                {
                    string cmp2 = Regex.Replace(t2[z, conl2],@"\s","");
                    bool jud = cmp2.Equals(cmp1);
                    if(jud==true) //对于比较成功的
                    {
                        for (int m = 0; m < nt1; m++)
                        {
                            MAIN[i_main, p_main] = t1[i, setint1[m]];
                            p_main++;
                                }
                        for (int m = 0; m < nt2; m++)
                        {
                            MAIN[i_main, p_main] = t2[i, setint2[m]];
                            p_main++;
                        }
                        p_main = 0;
                        i_main++;


                    }

                }

            }

            //将MAIN数组中的有效元组放到datagridview2内
            for(int i=0;i<i_main;i++)
            {
                DataRow dr = dt.NewRow();
                for (int m = 0; m < set.Length; m++)
                    dr[m] = MAIN[i, m];
                dt.Rows.Add(dr);
            }
            dataGridView2.DataSource = dt;
        }
        public int EDIT(string tb, string[] ordertag)  //EDIT操作
        {
            //首先看是否存在一个tb表
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
                    writer.Write(c1);
                    writer.Write(name);
                    int nx = reader.ReadInt32(); //字段数目
                    writer.Write(nx);
                    for (int j = 0; j < nx; j++)
                    {
                        string s1 = reader.ReadString();//字段名
                        string s2 = reader.ReadString();//字段类型
                        int s3 = reader.ReadInt32();  //字长
                        string s4 = reader.ReadString(); //Others
                        if (s1.Equals(ordertag[0])) //目标
                        {
                            writer.Write(s1);
                            writer.Write(ordertag[1]);
                            writer.Write(s3);
                            int n1 = Convert.ToInt32( ordertag[2]);
                            int n2 = Convert.ToInt32(ordertag[3]);
                            int n3 = Convert.ToInt32(ordertag[4]);
                            string n = n1.ToString().PadLeft(1, '0') +
                                n2.ToString().PadLeft(1, '0') +
                                n3.ToString().PadLeft(1, '0');
                            writer.Write(n);

                        }
                        else { 
                            writer.Write(s1);
                            writer.Write(s2);
                            writer.Write(s3);
                            writer.Write(s4);
                        }

                    }
                  
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
                        { jud2 = false; current = current.Substring(0, current.LastIndexOf(")"));
                            combox[i_tmp1]=current; i_tmp1++;
                        }
                        if (current.EndsWith(","))
                        {
                            current = current.Substring(0, current.LastIndexOf(","));
                            combox[i_tmp1] = current;
                            i_tmp1++;
                            j++;
                        }
                       
                    }
                    j++;
                    current = Regex.Replace(command[j], @"\s", "");// IN
                    int re = INSERT(combox, i_tmp1, tb_name);
                    if (re != 1) { MessageBox.Show("更新失败！"); return 0; }
                    return 1;
                    break;
                case "DELETE":  //DELETE
                    j++;
                    current = Regex.Replace(command[j], @"\s", "");//GET THE NEXT WORD "FROM"
                    j++;
                    current = Regex.Replace(command[j], @"\s", "");
                    string tbdel_name=Regex.Replace(current,@"\s","");  //要进行DELETE操作的表
                    j++;
                    current = Regex.Replace(command[j], @"\s", ""); //WHERE
                    j++;
                    current = Regex.Replace(command[j], @"\s", "");// field=content
                    Regex.Replace(current, @"\s", ""); //去掉空格
                    string[] inst = current.Split('=');  //以‘=’分割字符串
                    string field = inst[0];
                    string content = inst[1];
                    j++;
                    current = Regex.Replace(command[j], @"\s", "");//IN
                    int re1 = DELETE(tbdel_name, field, content);
                    if (re1 == 0)
                    {
                        MessageBox.Show("更新失败！"); return 0;
                    }
                    else return 1;
                    break;
                case "UPDATE":
                    j++;
                    current = Regex.Replace(command[j], @"\s", "");//取下一个单词
                    current=Regex.Replace(current, @"\s", "");  //要修改数据的表名(
                    if (!current.EndsWith("(")) { MessageBox.Show("格式错误！"); return 0; }
                    current=current.Substring(0, current.LastIndexOf('('));
                    string tb_name1 = current;       //要修改数据的表名
                    j++;
                    current = Regex.Replace(command[j], @"\s", "");//SET

                    j++;
                    current = Regex.Replace(command[j], @"\s", "");// field1=cont1
                    string []tp1 = current.Split("=");
                    string field1 = tp1[0];
                    string content1 = tp1[1];
                    j++;
                    current = Regex.Replace(command[j], @"\s", "");//WHERE

                    j++;
                    current = Regex.Replace(command[j], @"\s", "");//field2=cont2)
                    if (!current.EndsWith(")")) { MessageBox.Show("格式错误"); return 0; }
                    current=current.Substring(0,current.LastIndexOf(")"));
                    string[] tp2 = current.Split("=");
                    string field2 = tp2[0];
                    string content2 = tp2[1];

                    j++;
                    current = Regex.Replace(command[j], @"\s", "");//IN
                    int res1 = UPDATE(tb_name1, field1, content1, field2, content2);
                    if (res1 == 0) { MessageBox.Show("更新失败");  return 0; }
                    return 1;
                    break;
                case "SELECT":
                    j++;
                    current = Regex.Replace(command[j], @"\s", "");// A,B,C......元组
                    string[] set=current.Split(",");    //属性集合
                    j++;
                    current = Regex.Replace(command[j], @"\s", ""); //FROM
                    j++;
                    current = Regex.Replace(command[j], @"\s", "");//表名 A,B,C...
                    string[] tb = current.Split(',');  //表名
                    j++;
                    current = Regex.Replace(command[j], @"\s", "");//WHERE
                    if (tb.Length == 1)  //仅有一张表
                    {
                        j++;
                        current = Regex.Replace(command[j], @"\s", "");  //field=content
                        string[]tmp=current.Split("=");
                        string field3 = tmp[0];  //属性
                        string cont3 = tmp[1];  //属性值
                        singalselect(tb[0], set, field3, cont3);
                        
                        
                    }
                    else if (tb.Length > 1)  //多张表
                    {
                        j++;
                        current = Regex.Replace(command[j], @"\s", ""); // A.NO=B.NO
                        string[] tmp = current.Split(new char[2] { '=', '.' });
                        string[] connect = new string[2];
                        connect[0] = tmp[1];
                        connect[1] = tmp[3];
                        multiplesearch(tb, set, connect[0]);
                    }
                    else { MessageBox.Show("语法错误！"); }
                    
                    return 1;
                    break;
                    
                case "EDIT":
                    j++;
                    current = Regex.Replace(command[j], @"\s", ""); //取下一个单词 TABLE
                    j++;
                    current = Regex.Replace(command[j], @"\s", "");//name(
                    if (current.EndsWith("("))
                    { current = current.Substring(0, current.LastIndexOf("(")); }
                    else { MessageBox.Show("格式错误！"); }
                    string tb_name2 = current;  //要修改格式的表名
                    j++;
                    current = Regex.Replace(command[j], @"\s", ""); //fieldname
                    string[] ordertag = new string[5];
                    ordertag[0] = current;
                    j++;
                    current = Regex.Replace(command[j], @"\s", ""); //Type
                    ordertag[1]=current;
                    j++;
                    current = Regex.Replace(command[j], @"\s", "");//KEY_FLAG
                    ordertag[2]=current;
                    j++;
                    current = Regex.Replace(command[j], @"\s", "");//NULL_FLAG
                    ordertag[3] = current;
                    j++;
                    current = Regex.Replace(command[j], @"\s", "");//VALID_FLAG)
                    if(current.EndsWith(")"))
                    {
                        current=current.Substring(0,current.LastIndexOf(")"));
                        ordertag[4]=current;
                    }
                    else { MessageBox.Show("格式错误！"); return 0; }
                    j++;
                    current = Regex.Replace(command[j], @"\s", "");//IN

                    int re3 = EDIT(tb_name2, ordertag);
                    MessageBox.Show("更新完成！");



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
                dt.Columns.Add(mode[line][z].sFieldName + '(' + mode[line][z].bNullFlag + ')', typeof(string));
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
