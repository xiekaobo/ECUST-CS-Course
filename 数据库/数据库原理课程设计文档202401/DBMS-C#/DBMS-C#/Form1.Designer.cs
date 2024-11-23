namespace DBMS_C_
{
    partial class Form1
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            label1 = new Label();
            label2 = new Label();
            textBox1 = new TextBox();
            label3 = new Label();
            textBox2 = new TextBox();
            button1 = new Button();
            menuStrip1 = new MenuStrip();
            登录管理员账户AToolStripMenuItem = new ToolStripMenuItem();
            退出EToolStripMenuItem = new ToolStripMenuItem();
            button2 = new Button();
            menuStrip1.SuspendLayout();
            SuspendLayout();
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Font = new Font("黑体", 15.8571434F, FontStyle.Bold, GraphicsUnit.Point);
            label1.Location = new Point(292, 80);
            label1.Name = "label1";
            label1.Size = new Size(149, 33);
            label1.TabIndex = 0;
            label1.Text = "登录DBMS";
            label1.Click += label1_Click;
            // 
            // label2
            // 
            label2.AutoSize = true;
            label2.Location = new Point(72, 196);
            label2.Name = "label2";
            label2.Size = new Size(64, 24);
            label2.TabIndex = 1;
            label2.Text = "用户名";
            // 
            // textBox1
            // 
            textBox1.Location = new Point(173, 196);
            textBox1.Name = "textBox1";
            textBox1.Size = new Size(402, 30);
            textBox1.TabIndex = 2;
            // 
            // label3
            // 
            label3.AutoSize = true;
            label3.Location = new Point(72, 272);
            label3.Name = "label3";
            label3.Size = new Size(46, 24);
            label3.TabIndex = 3;
            label3.Text = "密码";
            label3.Click += label3_Click;
            // 
            // textBox2
            // 
            textBox2.Location = new Point(173, 267);
            textBox2.Name = "textBox2";
            textBox2.PasswordChar = '*';
            textBox2.Size = new Size(402, 30);
            textBox2.TabIndex = 4;
            // 
            // button1
            // 
            button1.Location = new Point(463, 379);
            button1.Name = "button1";
            button1.Size = new Size(111, 34);
            button1.TabIndex = 5;
            button1.Text = "登录";
            button1.UseVisualStyleBackColor = true;
            button1.Click += button1_Click;
            // 
            // menuStrip1
            // 
            menuStrip1.ImageScalingSize = new Size(28, 28);
            menuStrip1.Items.AddRange(new ToolStripItem[] { 登录管理员账户AToolStripMenuItem, 退出EToolStripMenuItem });
            menuStrip1.Location = new Point(0, 0);
            menuStrip1.Name = "menuStrip1";
            menuStrip1.Padding = new Padding(5, 2, 0, 2);
            menuStrip1.Size = new Size(699, 32);
            menuStrip1.TabIndex = 6;
            menuStrip1.Text = "menuStrip1";
            // 
            // 登录管理员账户AToolStripMenuItem
            // 
            登录管理员账户AToolStripMenuItem.Name = "登录管理员账户AToolStripMenuItem";
            登录管理员账户AToolStripMenuItem.Size = new Size(177, 28);
            登录管理员账户AToolStripMenuItem.Text = "登录管理员账户(&A)";
            登录管理员账户AToolStripMenuItem.Click += 登录管理员账户AToolStripMenuItem_Click;
            // 
            // 退出EToolStripMenuItem
            // 
            退出EToolStripMenuItem.Name = "退出EToolStripMenuItem";
            退出EToolStripMenuItem.Size = new Size(84, 28);
            退出EToolStripMenuItem.Text = "退出(&E)";
            退出EToolStripMenuItem.Click += 退出EToolStripMenuItem_Click;
            // 
            // button2
            // 
            button2.Location = new Point(173, 379);
            button2.Name = "button2";
            button2.Size = new Size(209, 34);
            button2.TabIndex = 7;
            button2.Text = "登录到非关系型数据库";
            button2.UseVisualStyleBackColor = true;
            button2.Click += button2_Click;
            // 
            // Form1
            // 
            AutoScaleDimensions = new SizeF(11F, 24F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(699, 475);
            Controls.Add(button2);
            Controls.Add(button1);
            Controls.Add(textBox2);
            Controls.Add(label3);
            Controls.Add(textBox1);
            Controls.Add(label2);
            Controls.Add(label1);
            Controls.Add(menuStrip1);
            MainMenuStrip = menuStrip1;
            Name = "Form1";
            Text = "Log In";
            Load += Form1_Load;
            menuStrip1.ResumeLayout(false);
            menuStrip1.PerformLayout();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private Label label1;
        private Label label2;
        private TextBox textBox1;
        private Label label3;
        private TextBox textBox2;
        private Button button1;
        private MenuStrip menuStrip1;
        private ToolStripMenuItem 登录管理员账户AToolStripMenuItem;
        private ToolStripMenuItem 退出EToolStripMenuItem;
        private Button button2;
    }
}