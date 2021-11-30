// conditional statements


int max(int x, int y) 
{
   int ans;
   ans = x < y ? y : x; // ternery
   return ans;
}

int min(int x, int y) 
{
   int ans;
   if(x<y)  // if-else
   	ans=x;
   else
   	ans=y;

   return ans;
}

int a;

int cal(int a, int b){
	int i, j, d;
	i = min(a, b);
	j = max(a, b);
	d = j - i;
	return d;
}

int main(){
	int a, b, d;
	a = 10, b = 5;
	d = cal(a,b);
	return 0;
}
