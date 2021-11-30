//nested loops, function calls

int f(int a, int b){
    return a>>1 + b;
}

int fun(int x){
    f(x, x);
    {
        int y = 0;
        y = f(x, y);
        int yy = 1;
        yy = f(yy, y);
    }
}

int main(){
    int ar[10][10];
    int x = 10, r;

    for(int l=1;l<10;l++){
        for(int i=0;i<10;i++){                        
		ar[i][j] = l+i*2+x;
        }
    }
    r = 16;
    fun(r);
}
