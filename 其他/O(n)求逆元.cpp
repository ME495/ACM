inv[1] = 1;  
for(int i=2;i<N;i++)  
{  
    if(i >= MOD) break;  
    inv[i] = (MOD - MOD / i) * inv[MOD % i] % MOD;  
}  