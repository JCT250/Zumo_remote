namespace WindowsFormsApplication1
{
    partial class Form1
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
            this.components = new System.ComponentModel.Container();
            this.btn_serial_connect = new System.Windows.Forms.Button();
            this.btn_serial_disconnect = new System.Windows.Forms.Button();
            this.btn_click = new System.Windows.Forms.Button();
            this.comboBox1 = new System.Windows.Forms.ComboBox();
            this.serialPort1 = new System.IO.Ports.SerialPort(this.components);
            this.lbl_serial = new System.Windows.Forms.Label();
            this.btn_serial_refresh = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // btn_serial_connect
            // 
            this.btn_serial_connect.Location = new System.Drawing.Point(12, 39);
            this.btn_serial_connect.Name = "btn_serial_connect";
            this.btn_serial_connect.Size = new System.Drawing.Size(127, 23);
            this.btn_serial_connect.TabIndex = 2;
            this.btn_serial_connect.Text = "Connect";
            this.btn_serial_connect.UseVisualStyleBackColor = true;
            this.btn_serial_connect.Click += new System.EventHandler(this.btn_serial_connect_Click);
            // 
            // btn_serial_disconnect
            // 
            this.btn_serial_disconnect.Location = new System.Drawing.Point(145, 39);
            this.btn_serial_disconnect.Name = "btn_serial_disconnect";
            this.btn_serial_disconnect.Size = new System.Drawing.Size(127, 23);
            this.btn_serial_disconnect.TabIndex = 3;
            this.btn_serial_disconnect.Text = "Disconnect";
            this.btn_serial_disconnect.UseVisualStyleBackColor = true;
            this.btn_serial_disconnect.Click += new System.EventHandler(this.btn_serial_disconnect_Click);
            // 
            // btn_click
            // 
            this.btn_click.BackColor = System.Drawing.Color.Yellow;
            this.btn_click.Location = new System.Drawing.Point(16, 98);
            this.btn_click.Name = "btn_click";
            this.btn_click.Size = new System.Drawing.Size(256, 152);
            this.btn_click.TabIndex = 6;
            this.btn_click.Text = "Click";
            this.btn_click.UseVisualStyleBackColor = false;
            this.btn_click.KeyDown += new System.Windows.Forms.KeyEventHandler(this.btn_click_KeyDown);
            this.btn_click.KeyUp += new System.Windows.Forms.KeyEventHandler(this.btn_click_KeyUp);
            this.btn_click.MouseDown += new System.Windows.Forms.MouseEventHandler(this.btn_click_MouseDown);
            this.btn_click.MouseUp += new System.Windows.Forms.MouseEventHandler(this.btn_click_MouseUp);
            // 
            // comboBox1
            // 
            this.comboBox1.FormattingEnabled = true;
            this.comboBox1.Location = new System.Drawing.Point(12, 12);
            this.comboBox1.Name = "comboBox1";
            this.comboBox1.Size = new System.Drawing.Size(260, 21);
            this.comboBox1.TabIndex = 1;
            // 
            // lbl_serial
            // 
            this.lbl_serial.Location = new System.Drawing.Point(13, 69);
            this.lbl_serial.Name = "lbl_serial";
            this.lbl_serial.Size = new System.Drawing.Size(127, 23);
            this.lbl_serial.TabIndex = 5;
            this.lbl_serial.Text = "Serial Connection Closed";
            this.lbl_serial.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // btn_serial_refresh
            // 
            this.btn_serial_refresh.Location = new System.Drawing.Point(146, 69);
            this.btn_serial_refresh.Name = "btn_serial_refresh";
            this.btn_serial_refresh.Size = new System.Drawing.Size(127, 23);
            this.btn_serial_refresh.TabIndex = 4;
            this.btn_serial_refresh.Text = "Refresh";
            this.btn_serial_refresh.UseVisualStyleBackColor = true;
            this.btn_serial_refresh.Click += new System.EventHandler(this.btn_serial_refresh_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(284, 262);
            this.Controls.Add(this.btn_serial_refresh);
            this.Controls.Add(this.lbl_serial);
            this.Controls.Add(this.comboBox1);
            this.Controls.Add(this.btn_click);
            this.Controls.Add(this.btn_serial_disconnect);
            this.Controls.Add(this.btn_serial_connect);
            this.Name = "Form1";
            this.Text = "ZumOT";
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button btn_serial_connect;
        private System.Windows.Forms.Button btn_serial_disconnect;
        private System.Windows.Forms.Button btn_click;
        private System.Windows.Forms.ComboBox comboBox1;
        private System.IO.Ports.SerialPort serialPort1;
        private System.Windows.Forms.Label lbl_serial;
        private System.Windows.Forms.Button btn_serial_refresh;
    }
}

