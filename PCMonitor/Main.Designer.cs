
namespace EspMon
{
	partial class Main
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
            this.RefreshButton = new System.Windows.Forms.Button();
            this.UpdateTimer = new System.Windows.Forms.Timer(this.components);
            this.Notify = new System.Windows.Forms.NotifyIcon(this.components);
            this.StartedCheckBox = new System.Windows.Forms.CheckBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.CpuMaxUpDown = new System.Windows.Forms.NumericUpDown();
            this.GpuMaxUpDown = new System.Windows.Forms.NumericUpDown();
            this.label3 = new System.Windows.Forms.Label();
            this.panel1 = new System.Windows.Forms.Panel();
            this.PortBox = new System.Windows.Forms.CheckedListBox();
            this.button1 = new System.Windows.Forms.Button();
            this.button2 = new System.Windows.Forms.Button();
            this.button3 = new System.Windows.Forms.Button();
            this.button4 = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.CpuMaxUpDown)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.GpuMaxUpDown)).BeginInit();
            this.panel1.SuspendLayout();
            this.SuspendLayout();
            // 
            // RefreshButton
            // 
            this.RefreshButton.Location = new System.Drawing.Point(105, 8);
            this.RefreshButton.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.RefreshButton.Name = "RefreshButton";
            this.RefreshButton.Size = new System.Drawing.Size(97, 38);
            this.RefreshButton.TabIndex = 2;
            this.RefreshButton.Text = "Refresh";
            this.RefreshButton.UseVisualStyleBackColor = true;
            this.RefreshButton.Click += new System.EventHandler(this.RefreshButton_Click);
            // 
            // UpdateTimer
            // 
            this.UpdateTimer.Enabled = true;
            this.UpdateTimer.Tick += new System.EventHandler(this.UpdateTimer_Tick);
            // 
            // Notify
            // 
            this.Notify.BalloonTipText = "EspMon";
            this.Notify.BalloonTipTitle = "EspMon";
            this.Notify.Text = "EspMon";
            this.Notify.Click += new System.EventHandler(this.Notify_Click);
            // 
            // StartedCheckBox
            // 
            this.StartedCheckBox.AutoSize = true;
            this.StartedCheckBox.Location = new System.Drawing.Point(223, 16);
            this.StartedCheckBox.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.StartedCheckBox.Name = "StartedCheckBox";
            this.StartedCheckBox.Size = new System.Drawing.Size(88, 24);
            this.StartedCheckBox.TabIndex = 3;
            this.StartedCheckBox.Text = "Started";
            this.StartedCheckBox.UseVisualStyleBackColor = true;
            this.StartedCheckBox.CheckedChanged += new System.EventHandler(this.StartedCheckBox_CheckedChanged);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(15, 20);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(86, 20);
            this.label1.TabIndex = 5;
            this.label1.Text = "COM Ports";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(18, 60);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(119, 20);
            this.label2.TabIndex = 7;
            this.label2.Text = "CPU Temp Max";
            // 
            // CpuMaxUpDown
            // 
            this.CpuMaxUpDown.Location = new System.Drawing.Point(141, 51);
            this.CpuMaxUpDown.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.CpuMaxUpDown.Maximum = new decimal(new int[] {
            150,
            0,
            0,
            0});
            this.CpuMaxUpDown.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.CpuMaxUpDown.Name = "CpuMaxUpDown";
            this.CpuMaxUpDown.Size = new System.Drawing.Size(79, 26);
            this.CpuMaxUpDown.TabIndex = 8;
            this.CpuMaxUpDown.Value = new decimal(new int[] {
            100,
            0,
            0,
            0});
            // 
            // GpuMaxUpDown
            // 
            this.GpuMaxUpDown.Location = new System.Drawing.Point(141, 85);
            this.GpuMaxUpDown.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.GpuMaxUpDown.Maximum = new decimal(new int[] {
            150,
            0,
            0,
            0});
            this.GpuMaxUpDown.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.GpuMaxUpDown.Name = "GpuMaxUpDown";
            this.GpuMaxUpDown.Size = new System.Drawing.Size(79, 26);
            this.GpuMaxUpDown.TabIndex = 10;
            this.GpuMaxUpDown.Value = new decimal(new int[] {
            90,
            0,
            0,
            0});
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(18, 94);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(121, 20);
            this.label3.TabIndex = 9;
            this.label3.Text = "GPU Temp Max";
            // 
            // panel1
            // 
            this.panel1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.panel1.Controls.Add(this.PortBox);
            this.panel1.Location = new System.Drawing.Point(14, 120);
            this.panel1.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(290, 204);
            this.panel1.TabIndex = 11;
            // 
            // PortBox
            // 
            this.PortBox.Dock = System.Windows.Forms.DockStyle.Fill;
            this.PortBox.FormattingEnabled = true;
            this.PortBox.Location = new System.Drawing.Point(0, 0);
            this.PortBox.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.PortBox.Name = "PortBox";
            this.PortBox.Size = new System.Drawing.Size(290, 204);
            this.PortBox.TabIndex = 7;
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(227, 50);
            this.button1.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(28, 29);
            this.button1.TabIndex = 12;
            this.button1.Text = "1";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.ButtonLabel_Click);
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(262, 51);
            this.button2.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(28, 29);
            this.button2.TabIndex = 13;
            this.button2.Text = "2";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.ButtonLabel_Click);
            // 
            // button3
            // 
            this.button3.Location = new System.Drawing.Point(227, 84);
            this.button3.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(28, 29);
            this.button3.TabIndex = 14;
            this.button3.Text = "3";
            this.button3.UseVisualStyleBackColor = true;
            this.button3.Click += new System.EventHandler(this.ButtonLabel_Click);
            // 
            // button4
            // 
            this.button4.Location = new System.Drawing.Point(262, 84);
            this.button4.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.button4.Name = "button4";
            this.button4.Size = new System.Drawing.Size(28, 29);
            this.button4.TabIndex = 15;
            this.button4.Text = "4";
            this.button4.UseVisualStyleBackColor = true;
            this.button4.Click += new System.EventHandler(this.ButtonLabel_Click);
            // 
            // Main
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(316, 325);
            this.Controls.Add(this.button3);
            this.Controls.Add(this.button4);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.panel1);
            this.Controls.Add(this.GpuMaxUpDown);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.CpuMaxUpDown);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.StartedCheckBox);
            this.Controls.Add(this.RefreshButton);
            this.Margin = new System.Windows.Forms.Padding(3, 2, 3, 2);
            this.MinimumSize = new System.Drawing.Size(334, 291);
            this.Name = "Main";
            this.Text = "EspMon";
            this.Resize += new System.EventHandler(this.EspMon_Resize);
            ((System.ComponentModel.ISupportInitialize)(this.CpuMaxUpDown)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.GpuMaxUpDown)).EndInit();
            this.panel1.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

		}

		#endregion
		private System.Windows.Forms.Button RefreshButton;
		private System.Windows.Forms.Timer UpdateTimer;
		private System.Windows.Forms.NotifyIcon Notify;
		private System.Windows.Forms.CheckBox StartedCheckBox;
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.Label label2;
		private System.Windows.Forms.NumericUpDown CpuMaxUpDown;
		private System.Windows.Forms.NumericUpDown GpuMaxUpDown;
		private System.Windows.Forms.Label label3;
		private System.Windows.Forms.Panel panel1;
		private System.Windows.Forms.CheckedListBox PortBox;
		private System.Windows.Forms.Button button1;
		private System.Windows.Forms.Button button2;
		private System.Windows.Forms.Button button3;
		private System.Windows.Forms.Button button4;
	}
}

