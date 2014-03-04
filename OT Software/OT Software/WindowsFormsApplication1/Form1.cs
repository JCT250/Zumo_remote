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
                btn_serial_connect.Enabled = false;
                lbl_serial.Text = (String.Format("Connected to '{0}'", comboBox1.SelectedItem));
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
                // MessageBox.Show(String.Format("Connecting to '{0}'", comboBox1.SelectedItem));
                Connect(comboBox1.SelectedItem.ToString());
            }
            else
            {
                MessageBox.Show("Please select a port first");
            }
        } //done

        private void btn_serial_disconnect_Click(object sender, EventArgs e)
        {
            if (serialPort1.IsOpen)
            {
                serialPort1.Close();
                lbl_serial.Text = ("Serial Connection Closed");
                // MessageBox.Show("Serial connection closed");
                btn_serial_connect.Enabled = true;
            }
            else if (!serialPort1.IsOpen)
            {
                MessageBox.Show("No connection currently open", "Alert");
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
    }
}
