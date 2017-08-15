
int simplestrval(const char *str, int startidx)
{
	int val = 0;
	char c;
	int iters = 0;
	while (true) {
		c = str[startidx];
		if (c < '0' || '9' < c) {
			break;
		}
		val *= 10;
		val += c - '0';
		startidx++;
		if (++iters > 10) {
			return 0;
		}
	}
	return val;
}
