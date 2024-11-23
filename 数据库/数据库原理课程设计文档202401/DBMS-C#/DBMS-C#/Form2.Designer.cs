namespace DBMS_C_
{
    partial class Form2
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
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
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            label1 = new Label();
            label2 = new Label();
            label3 = new Label();
            label4 = new Label();
            textBox1 = new TextBox();
            textBox2 = new TextBox();
            button1 = new Button();
            SuspendLayout();
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Font = new Font("黑体", 15.8571434F, FontStyle.Regular, GraphicsUnit.Point);
            label1.Location = new Point(247, 96);
            label1.Name = "label1";
            label1.Size = new Size(283, 37);
            label1.TabIndex = 0;
            label1.Text = "数据库账户管理";
            // 
            // label2
            // 
            label2.AutoSize = true;
            label2.Location = new Point(66, 243);
            label2.Name = "label2";
            label2.Size = new Size(0, 28);
            label2.TabIndex = 1;
            // 
            // label3
            // 
            label3.AutoSize = true;
            label3.Location = new Point(72, 252);
            label3.Name = "label3";
            label3.Size = new Size(117, 28);
            label3.TabIndex = 2;
            label3.Text = "管理员账户";
            // 
            // label4
            // 
            label4.AutoSize = true;
            label4.Location = new Point(72, 334);
            label4.Name = "label4";
            label4.Size = new Size(117, 28);
            label4.TabIndex = 3;
            label4.Text = "管理员密钥";
            // 
            // textBox1
            // 
            textBox1.Location = new Point(273, 251);
            textBox1.Name = "textBox1";
            textBox1.Size = new Size(453, 34);
            textBox1.TabIndex = 4;
            // 
            // textBox2
            // 
            textBox2.Cursor = Cursors.IBeam;
            textBox2.Location = new Point(273, 334);
            textBox2.Name = "textBox2";
            textBox2.PasswordChar = '*';
            textBox2.Size = new Size(453, 34);
            textBox2.TabIndex = 5;
            // 
            // button1
            // 
            button1.Location = new Point(322, 456);
            button1.Name = "button1";
            button1.Size = new Size(131, 40);
            button1.TabIndex = 6;
            button1.Text = "登入";
            button1.UseVisualStyleBackColor = true;
            button1.Click += button1_Click;
            // 
            // Form2
            // 
            AutoScaleDimensions = new SizeF(13F, 28F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(810, 606);
            Controls.Add(button1);
            Controls.Add(textBox2);
            Controls.Add(textBox1);
            Controls.Add(label4);
            Controls.Add(label3);
            Controls.Add(label2);
            Controls.Add(label1);
            Name = "Form2";
            Text = "Admin";
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private Label label1;
        private Label label2;
        private Label label3;
        private Label label4;
        private TextBox textBox1;
        private TextBox textBox2;
        private Button button1;
    }
}