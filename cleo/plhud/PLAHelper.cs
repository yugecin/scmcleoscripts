using System;
using System.Text;

namespace PLairporthelper
{
	class PLAHelper
	{

		public static string convert(string savedpositions) {
			string res = "";
			string[] lines = savedpositions.Split('\n', '\r');
			string __l = "";
			try {
				foreach(string line in lines) {
					if( line.Length < 10 )
					{
						continue;
					}
					__l = line;
					string[] parts = line.Split( ',' );
					float x = float.Parse(parts[1].Replace('.', ','));
					float y = float.Parse(parts[2].Replace('.', ','));
					float z = float.Parse(parts[3].Replace('.', ',')) - 2.0f;
					string comment = line.Split( '/' )[2].Substring(1);
					res += f2h( x ) + " " + f2h(y) + " " + f2h(z);
					if( comment.Length == 0 )
					{
						res += " ";
					}
					else
					{
						res += " " + b2h( new byte[] { BitConverter.GetBytes( comment.Length + 1 )[0] } );
						res += " \"" + comment + "\"";
						res += " 00";
						res += "\r\n";
					}
				}
			}
			catch( Exception r )
			{
				res = r.Message + "\r\n" + r.StackTrace + "\r\n" + __l;
			}
			res += "00000000";
			return res;
		}

		public static string f2h(float fNum)
		{
			return b2h(BitConverter.GetBytes( fNum ));
		}

		public static string b2h( byte[] b )
		{
			StringBuilder sb = new StringBuilder();

			for( int i = 0; i < b.Length; i++ ) {
				sb.Append( b[i].ToString( "X2" ) );
			}

			return sb.ToString();
		}

	}
}
