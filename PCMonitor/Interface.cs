using System.Runtime.InteropServices;
namespace EspMon
{
	// the data to send over serial
	// pack for 32-bit systems
	[StructLayout(LayoutKind.Sequential,Pack = 4,CharSet =CharSet.Ansi)]
	internal struct ReadStatus
	{
		// command = 1
		[MarshalAs(UnmanagedType.ByValTStr, SizeConst = 4)] 
		public string TopTitle;
		public char TopUnit1;
		public int Top1Hue1;
		public int Top1Hue2;
		public int TopValue1;
		public int TopValue1Max;
		public int TopValue1Div;
		public char TopUnit2;
		public int Top2Hue1;
		public int Top2Hue2;
		public int TopValue2;
		public int TopValue2Max;
		public int TopValue2Div;
		[MarshalAs(UnmanagedType.ByValTStr, SizeConst = 4)]
		public string BottomTitle;
		public char BottomUnit1;
		public int Bottom1Hue1;
		public int Bottom1Hue2;
		public int BottomValue1;
		public int BottomValue1Max;
		public int BottomValue1Div;
		public char BottomUnit2;
		public int Bottom2Hue1;
		public int Bottom2Hue2;
		public int BottomValue2;
		public int BottomValue2Max;
		public int BottomValue2Div;

	}
}
