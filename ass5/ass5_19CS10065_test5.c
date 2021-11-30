//loops, unary operators, global vars, arrays
int x = 0;

int main()
{
	int i, j, n;
	int sum=0;
	char a='a';
	int p[5]; 
	n=5;
	j=100;
	i=0;

	while(i<5) 
	{
		i++;
		++j;
		p[i]=i*j;
	}

	do 
	{
		sum = sum + p[i];
	}while(i<n);
	return 0;
}
