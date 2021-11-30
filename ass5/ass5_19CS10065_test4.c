// recursive functions  
int fac(int a) 
{ 
    if (a <= 1) 
        return a; 
    int ans = a;
    return ans*fac(a-1); 
} 

int main()  
{  
    int a, g;
    a = 5;
    g = fac(a);   // recursive function call
    return 0;  
}  
