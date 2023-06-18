using OpenHardwareMonitor.Hardware;

using System;
using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;

namespace EspMon
{
    public partial class EditLabel : Form
	{
		int _label;
		Computer _computer;
		public EditLabel(int label, Computer computer)
		{
			_label = label;
			_computer = computer;
			InitializeComponent();
			ValueTree.ImageList = IconContainer.Icons;
			UpdateHueStartLabel();
			UpdateHueEndLabel();
			UpdateTree();
		}
		void UpdateSensorNode(TreeNode parent)
		{
			var sensor = parent.Tag as ISensor;
			parent.Nodes.Clear();
			foreach(var value in sensor.Values)
			{
				var newNode = parent.Nodes.Add($"{value.Value} {sensor.SensorType}");
				newNode.Tag = value;
				newNode.EnsureVisible();
			}
		}
		void UpdateHardwareNode(TreeNode parent)
		{
			var hardware = parent.Tag as IHardware;
			var toRemove = new List<TreeNode>();
			foreach (TreeNode node in parent.Nodes)
			{
				if(node.Tag is IHardware)
				{
					toRemove.Add(node);
				}
			}
			foreach(TreeNode node in toRemove)
			{
				parent.Nodes.Remove(node);
			}
			toRemove = null;
			foreach (var sensor in hardware.Sensors)
			{
				var newNode = parent.Nodes.Add($"{sensor.Name} {sensor.Value}");
				newNode.Tag = sensor;
				newNode.ImageKey = sensor.SensorType.ToString().ToLower();
				newNode.EnsureVisible();
				UpdateSensorNode(newNode);

			}
			foreach (var subhardware in hardware.SubHardware)
			{
				var newNode = parent.Nodes.Add(subhardware.Name);
				newNode.Tag = subhardware;
				newNode.EnsureVisible();
				UpdateHardwareNode(newNode);
			}
			
		}
		void UpdateTree()
		{
			ValueTree.Nodes.Clear();
			var compNode = ValueTree.Nodes.Add("Computer");
			compNode.Tag = _computer;
			foreach(var hardware in _computer.Hardware)
			{
				var newNode = compNode.Nodes.Add(hardware.Name);
				newNode.Tag = hardware;
				newNode.EnsureVisible();
				UpdateHardwareNode(newNode);
			}
			compNode.EnsureVisible();
		}
		public static Color ColorFromHSV(double hue, double saturation, double value)
		{
			int hi = Convert.ToInt32(Math.Floor(hue / 60)) % 6;
			double f = hue / 60 - Math.Floor(hue / 60);

			value *= 255;
			int v = Convert.ToInt32(value);
			int p = Convert.ToInt32(value * (1 - saturation));
			int q = Convert.ToInt32(value * (1 - f * saturation));
			int t = Convert.ToInt32(value * (1 - (1 - f) * saturation));

			if (hi == 0)
				return Color.FromArgb(255, v, t, p);
			else if (hi == 1)
				return Color.FromArgb(255, q, v, p);
			else if (hi == 2)
				return Color.FromArgb(255, p, v, t);
			else if (hi == 3)
				return Color.FromArgb(255, p, q, v);
			else if (hi == 4)
				return Color.FromArgb(255, t, p, v);
			else
				return Color.FromArgb(255, v, p, q);
		}

		void UpdateHueEndLabel()
		{
			HueEndLabel.BackColor = ColorFromHSV((HueEndBar.Value / 100.0)*60,1,1);
		}
		void UpdateHueStartLabel()
		{
			HueStartLabel.BackColor = ColorFromHSV((HueStartBar.Value / 100.0)*60, 1, 1);
		}
		private void HueEndBar_Scroll(object sender, EventArgs e)
		{
			UpdateHueEndLabel();
		}

		private void HueStartBar_Scroll(object sender, EventArgs e)
		{
			UpdateHueStartLabel();
		}

		private void EditLabel_Load(object sender, EventArgs e)
		{

		}

		private void treeView1_AfterSelect(object sender, TreeViewEventArgs e)
		{

		}
	}
}
