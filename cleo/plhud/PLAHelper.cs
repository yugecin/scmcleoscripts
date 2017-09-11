using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;

namespace PLAHConsole
{
	class PLAHelper
	{

		static void Main( string[] args )
		{
			StreamReader i = new StreamReader("savedpositions.txt");
			StreamWriter o = new StreamWriter( "plhudairports.txt", false );
			o.Write(":AIRPORTS\r\nhex\r\n");
			o.Write( convert( i.ReadToEnd() ) );
			o.Write("\r\nend");
			i.Close();
			o.Close();
		}

		static string convert(string savedpositions) {
			string res = "";
			string[] lines = savedpositions.Split('\n', '\r');
			string __l = "";
			try {
				bool skip = false;
				foreach(string line in lines) {
					if( skip )
					{
						skip = false;
						continue;
					}
					if( line.Length < 10 )
					{
						continue;
					}
					if( line.StartsWith(";") )
					{
						skip = true;
						continue;
					}
					__l = line;
					string[] parts = line.Split( ',' );
					float x = float.Parse(parts[1].Replace('.', ','));
					float y = float.Parse(parts[2].Replace('.', ','));
					float z = float.Parse(parts[3].Replace('.', ',')) - 1.7f;
					string comment = line.Split( '/' )[2].Substring(1);
					res += f2h( x ) + " " + f2h(y) + " " + f2h(z);
					if( comment.Length == 0 )
					{
						res += " ";
					}
					else
					{
						comment = comment + " (" + (int) z + " FT)";
						res += " " + b2h( new byte[] { BitConverter.GetBytes( comment.Length + 1 )[0] } );
						res += " \"" + comment.Replace(' ', '_') + "\"";
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

		static string f2h(float fNum)
		{
			return b2h(BitConverter.GetBytes( fNum ));
		}

		static string b2h( byte[] b )
		{
			StringBuilder sb = new StringBuilder();

			for( int i = 0; i < b.Length; i++ ) {
				sb.Append( b[i].ToString( "X2" ) );
			}

			return sb.ToString();
		}
	}
}
