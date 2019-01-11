using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Transform
{
    public partial class Form1 : Form
    {
        private Bitmap curBitmap;
        private string fileName;
        private Bitmap oriBitmap;
        private Bitmap souBitmap;
        private int num;

        public Form1()
        {
            InitializeComponent();
            comboBox1.SelectedIndex = 0;
        }

        private void buttonStart_Click(object sender, EventArgs e)
        {
            OpenFileDialog fileDialog = new OpenFileDialog();
            timer1.Stop();
            fileDialog.Title = "选择文件";
            fileDialog.Filter = "bmp files (*.bmp)|*.bmp";
            fileDialog.FilterIndex = 1;
            fileDialog.RestoreDirectory = true;

            if (fileDialog.ShowDialog() == DialogResult.OK)
            {
                fileName = fileDialog.FileName;
                oriBitmap = new Bitmap(fileName);
                pictureBox1.Image = oriBitmap;
                curBitmap = new Bitmap(fileName);
            }
        }

        private void buttonEnd_Click(object sender, EventArgs e)
        {
            timer1.Stop();
            OpenFileDialog fileDialog = new OpenFileDialog();
            fileDialog.Title = "选择文件";
            fileDialog.Filter = "bmp files (*.bmp)|*.bmp";
            fileDialog.FilterIndex = 1;
            fileDialog.RestoreDirectory = true;

            if (fileDialog.ShowDialog() == DialogResult.OK)
            {
                fileName = fileDialog.FileName;
                oriBitmap = new Bitmap(fileName);
                souBitmap = new Bitmap(fileName);
                pictureBox2.Image = oriBitmap;
            }
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            if (num == 0)
            {
                timer1.Stop();
            }
            else
            {
                if (curBitmap != null)
                {
                    curBitmap = (Bitmap)pictureBox1.Image;
                    //位图矩形
                    Rectangle rect = new Rectangle(0, 0, curBitmap.Width, curBitmap.Height);
                    Rectangle rect1 = new Rectangle(0, 0, souBitmap.Width, souBitmap.Height);
                    System.Drawing.Imaging.BitmapData bmpData = curBitmap.LockBits(rect, System.Drawing.Imaging.ImageLockMode.ReadWrite, curBitmap.PixelFormat);
                    System.Drawing.Imaging.BitmapData bmpData1 = souBitmap.LockBits(rect1, System.Drawing.Imaging.ImageLockMode.ReadWrite, souBitmap.PixelFormat);
                    //得到首地址
                    IntPtr ptr = bmpData.Scan0;
                    IntPtr ptr1 = bmpData1.Scan0;
                    //24为BMP位图字节数
                    int bytes = curBitmap.Width * curBitmap.Height * 3;
                    int bytes1 = curBitmap.Width * curBitmap.Height * 3;
                    //定义位图数组
                    byte[] rgbValues = new byte[bytes];
                    byte[] rgbValues1 = new byte[bytes1];
                    //复制被锁定的位图像素值到该数组内
                    System.Runtime.InteropServices.Marshal.Copy(ptr, rgbValues, 0, bytes);
                    System.Runtime.InteropServices.Marshal.Copy(ptr1, rgbValues1, 0, bytes1);

                    for (int i = 0; i < rgbValues.Length; i += 3)
                    {
                        int incre1, incre2, incre3;
                        incre1 = (int)(rgbValues1[i] - rgbValues[i]);
                        incre2 = (int)(rgbValues1[i + 1] - rgbValues[i + 1]);
                        incre3 = (int)(rgbValues1[i + 2] - rgbValues[i + 2]);
                        if (incre1 % num != 0)
                        {
                            incre1 = incre1 / num + incre1 % num;
                        }
                        else
                        {
                            incre1 /= num;
                        }
                        if (incre2 % num != 0)
                        {
                            incre2 = incre2 / num + incre2 % num;
                        }
                        else
                        {
                            incre2 /= num;
                        }
                        if (incre3 % num != 0)
                        {
                            incre3 = incre3 / num + incre3 % num;
                        }
                        else
                        {
                            incre3 /= num;
                        }
                        rgbValues[i] += (byte)incre1;
                        rgbValues[i + 1] += (byte)incre2;
                        rgbValues[i + 2] += (byte)incre3;
                    }
                    //把数组复制会位图
                    System.Runtime.InteropServices.Marshal.Copy(rgbValues, 0, ptr, bytes);
                    System.Runtime.InteropServices.Marshal.Copy(rgbValues1, 0, ptr1, bytes1);
                    //解锁位图像素
                    curBitmap.UnlockBits(bmpData);
                    souBitmap.UnlockBits(bmpData1);
                    pictureBox1.Image = curBitmap;
                    --num;
                }
            }
        }

        private void buttonTran_Click(object sender, EventArgs e)
        {
            timer1.Interval = 300;
            num = Convert.ToInt32(comboBox1.SelectedIndex.ToString());
            timer1.Start();
        }
    }
}
