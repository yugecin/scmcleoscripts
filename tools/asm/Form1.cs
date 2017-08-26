using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Globalization;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace asm {
	public partial class Form1 : Form {

		[STAThread]
		static void Main() {
			Application.SetCompatibleTextRenderingDefault(true);
			Application.Run(new Form1());
		}

		public Form1() {
			InitializeComponent();
		}

		private void button1_Click(object sender, EventArgs e) {
			var lines = textBox1.Text.Split('\n');
			var sb = new StringBuilder();
			string[] instr = new string[8];
			int instrc;
			int instrs = 0;
			int labels = 0;
			sb.Append(":ENTRY").AppendLine();
			sb.Append("hex").AppendLine();
			foreach (var line in lines) {
				instrc = 0;
				int c = 1;
				while (line[c - 1] != ':') c++;
				while (line[c] == ' ') c++;
				do {
					instr[instrc++] = new string(new char[] { line[c], line[c + 1] } );
					c += 3;
				} while (line[c] != ' ');
				while (line[c] == ' ') c++;
				string comment = line.Substring(c);
				
				int si = 0;
				if (comment.StartsWith("call") || comment.StartsWith("jmp") || comment.StartsWith("je ") || comment.StartsWith("jne ")) {
					si = 1;
					sb.Append(instr[0]).AppendLine();
					sb.Append("end").AppendLine();
					sb.Append(":OFF").Append(labels++).AppendLine();
					sb.Append("hex").AppendLine();
					instrs++;
					if (instrc == 5) {
						int idx = comment.IndexOf(' ') + 1;
						comment = comment.Substring(0, idx) + "0x" + realaddr(instr);
						patchinstr(instr, instrs);
					}
				}
				comment = comment.Trim();
				for (; si < instrc; si++) {
					sb.Append(instr[si]).Append(' ');
					instrs++;
				}
				sb.AppendLine().Append("// ").Append(comment).AppendLine();
			}
			sb.Append("end").AppendLine();
			var sb2 = new StringBuilder();
			sb2.Append("0AC6: 0@ = label @ENTRY offset").AppendLine();
			sb2.AppendLine();
			sb2.Append("0085: 1@ = 0@ // (int)").AppendLine();
			string[] hookadrs = new string[] {
				"",
				textBox2.Text.Substring(6, 2),
				textBox2.Text.Substring(4, 2),
				textBox2.Text.Substring(2, 2),
				textBox2.Text.Substring(0, 2),
			};
			sb2.Append("000E: 1@ -= 0x").Append(realaddr(hookadrs)).AppendLine();
			sb2.Append("0A8C: write_memory 0x").Append(textBox2.Text).Append(" size 4 value 1@ vp 0").AppendLine();
			sb2.AppendLine();
			for (int i = 0; i < labels; i++) {
				sb2.Append("0AC6: 1@ = label @OFF").Append(i).Append(" offset").AppendLine();
				sb2.Append("0A8D: 2@ = read_memory 1@ size 4 vp 0").AppendLine();
				sb2.Append("0062: 2@ -= 0@  // (int)").AppendLine();
				sb2.Append("0A8C: write_memory 1@ size 4 value 2@ vp 0").AppendLine();
			}
			sb2.AppendLine().Append("0A93: end_custom_thread").AppendLine().AppendLine();
			sb2.Append(":MAIN_LOOP").AppendLine();
			sb2.Append("0001: wait 250").AppendLine();
			sb2.Append("0002: jump @MAIN_LOOP").AppendLine();
			sb2.AppendLine();
			sb.Insert(0, sb2.ToString());
			textBox1.Text = sb.ToString();
		}

		private string realaddr(string[] instr) {
			int addr =
				(int.Parse(instr[4], NumberStyles.HexNumber) << 24) |
				(int.Parse(instr[3], NumberStyles.HexNumber) << 16) |
				(int.Parse(instr[2], NumberStyles.HexNumber) <<  8) |
				(int.Parse(instr[1], NumberStyles.HexNumber)      ) |
				0;
			addr += 4;
			string s = "";
			s += ((addr >> 24) & 0xff).ToString("x2");
			s += ((addr >> 16) & 0xff).ToString("x2");
			s += ((addr >>  8) & 0xff).ToString("x2");
			s += ((addr      ) & 0xff).ToString("x2");
			return s;
		}

		private void patchinstr(string[] instr, int instrs) {
			int addr =
				(int.Parse(instr[4], NumberStyles.HexNumber) << 24) |
				(int.Parse(instr[3], NumberStyles.HexNumber) << 16) |
				(int.Parse(instr[2], NumberStyles.HexNumber) <<  8) |
				(int.Parse(instr[1], NumberStyles.HexNumber)      ) |
				0;
			addr -= instrs;
			instr[1] = ((addr      ) & 0xff).ToString("x2");
			instr[2] = ((addr >>  8) & 0xff).ToString("x2");
			instr[3] = ((addr >> 16) & 0xff).ToString("x2");
			instr[4] = ((addr >> 24) & 0xff).ToString("x2");
		}

		private static string b2h(byte[] b, int offset, int len)
		{
			StringBuilder sb = new StringBuilder();
			for(int i = offset, j = offset + len; i < j; i++) {
				sb.Append(b[i].ToString("X2"));
			}
			return sb.ToString();
		}

		private void button2_Click(object sender, EventArgs e) {
			var lines = textBox1.Text.Split('\n');
			var sb = new StringBuilder();
			foreach (var line in lines) {
				int i = line.IndexOf(';');
				if (i == -1) {
					sb.Append(line).AppendLine();
					continue;
				}
				sb.Append(line.Substring(0, i)).AppendLine();
			}
			textBox1.Text = sb.ToString();
		}
	}
}
