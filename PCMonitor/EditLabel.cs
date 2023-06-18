using OpenHardwareMonitor.Hardware;

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
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
				var newNode = parent.Nodes.Add(value.Value.ToString()+" "+sensor.SensorType.ToString());
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
				var newNode = parent.Nodes.Add(sensor.Name+" "+sensor.Value.ToString());
				newNode.Tag = sensor;
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
		void UpdateHueEndLabel()
		{
			float chH = (float)(1.0 / (HueEndBar.Value/100.0));
			int i = (int)Math.Floor(chH * 6);
			double f = chH * 6 - i;
			double p = 0;// 1.0 * (1 - 1);
			double q = 1 * (1 - f * 1);
			double t = 1 * (1 - (1 - f) * 1);
			double r = 0, g = 0, b = 0;
			switch (i % 6)
			{
				case 0: r = 1; g = t; b = p; break;
				case 1: r = q; g = 1; b = p; break;
				case 2: r = p; g = 1; b = t; break;
				case 3: r = p; g = q; b = 1; break;
				case 4: r = t; g = p; b = 1; break;
				case 5: r = 1; g = p; b = q; break;
			}
			HueEndLabel.BackColor = Color.FromArgb((int)(r * 255), (int)(g * 255), (int)(b * 255));
		}
		void UpdateHueStartLabel()
		{
			float chH = (float)(1.0 / (HueStartBar.Value/100.0));
			int i = (int)Math.Floor(chH * 6);
			double f = chH * 6 - i;
			double p = 0;// 1.0 * (1 - 1);
			double q = 1 * (1 - f * 1);
			double t = 1 * (1 - (1 - f) * 1);
			double r = 0, g = 0, b = 0;
			switch (i % 6)
			{
				case 0: r = 1; g = t; b = p; break;
				case 1: r = q; g = 1; b = p; break;
				case 2: r = p; g = 1; b = t; break;
				case 3: r = p; g = q; b = 1; break;
				case 4: r = t; g = p; b = 1; break;
				case 5: r = 1; g = p; b = q; break;
			}
			HueStartLabel.BackColor = Color.FromArgb((int)(r * 255), (int)(g * 255), (int)(b * 255));
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
