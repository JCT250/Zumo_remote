using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO.Ports;
using System.Windows.Forms;

namespace WindowsFormsApplication1
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            var ports = SerialPort.GetPortNames();
            comboBox1.DataSource = ports;
            this.KeyPreview = true;
        }  

        private void Connect(string portName)
        {
            serialPort1 = new SerialPort(portName);
            if (!serialPort1.IsOpen)
            {
                serialPort1.BaudRate = 9600;
                serialPort1.Open();
                btn_serial_connect.Visible = false;
                btn_serial_refresh.Visible = false;
                comboBox1.Visible = false;
                btn_click.Location = new Point (16,16);
                btn_click.Size = new Size(256,238);
                Form1.ActiveForm.Text = (String.Format("Connected to '{0}'", comboBox1.SelectedItem)); 
            }
        } //done  

        private void serial_check()
        {
            MessageBox.Show("Please open Serial Connection");
        } //done

        private void btn_serial_connect_Click(object sender, EventArgs e)
        {
            if (comboBox1.SelectedIndex > -1)
            {
                Connect(comboBox1.SelectedItem.ToString());
            }
            else
            {
                MessageBox.Show("Please select a port first");
            }
        } //done

        private void btn_serial_refresh_Click(object sender, EventArgs e)
        {
            var ports = SerialPort.GetPortNames();
            comboBox1.DataSource = ports;

        }

        private void btn_click_MouseDown(object sender, MouseEventArgs e)
        {
            if (!serialPort1.IsOpen)
            {
                serial_check();
            }
            else
            {
                btn_click.BackColor = Color.Green;
                Byte[] down = {0x44};
                serialPort1.Write(down, 0, 1);
            }
        }

        private void btn_click_MouseUp(object sender, MouseEventArgs e)
        {
            if (!serialPort1.IsOpen)
            {
                serial_check();
            }
            else
            {
                btn_click.BackColor = Color.Yellow;
                Byte[] up = { 0x55 };
                serialPort1.Write(up, 0, 1);
            }
        }

        private void btn_click_KeyDown(object sender, KeyEventArgs e)
        {
            if (!serialPort1.IsOpen)
            {
                serial_check();
            }
            else
            {
                btn_click.BackColor = Color.Green;
                Byte[] down = { 0x44 };
                serialPort1.Write(down, 0, 1);
            }
        }

        private void btn_click_KeyUp(object sender, KeyEventArgs e)
        {
            if (!serialPort1.IsOpen)
            {
                serial_check();
            }
            else
            {
                btn_click.BackColor = Color.Yellow;
                Byte[] up = { 0x55 };
                serialPort1.Write(up, 0, 1);
            }
        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {

        }
    }
}
