﻿using EspMon.Properties;
using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace EspMon
{
    public class IconContainer
    {
        public static ImageList Icons = new ImageList();

        static IconContainer()
        {
            var entryAssembly = Assembly.GetEntryAssembly();
            var results = entryAssembly.GetManifestResourceNames();
            foreach (var result in results)
            {
                if (!result.StartsWith("EspMon.Icons") || !result.EndsWith(".png"))
                {
                    continue;
                }

                var iconName = result.Replace("EspMon.Icons.", "").Replace(".png", "").ToLower();
                Icons.Images.Add(iconName, Image.FromStream(entryAssembly.GetManifestResourceStream(result)));
            }
        }
    }
}
