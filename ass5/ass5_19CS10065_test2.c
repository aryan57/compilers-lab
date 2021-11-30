// typecasting and pointers

int floor(float a, float b)
{
	int quotient;
	quotient = a/b; // type casting float -> int
	return quotient;
}

void pointer_test(int* a) //pointers
{
	*a = 10
	return;
}

int main()
{
	int q=0,r=0;
	float x=2.5;
	q = floor(x,1.2);
	r=10;
	pointer_test(&q);
	return;
}
