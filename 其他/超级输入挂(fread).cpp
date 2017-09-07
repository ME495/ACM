#define  PARSE_INT( x ) do{ \  
                x = 0; \  
                int  sgn = 1; \  
                while( *ptr < '0' || *ptr > '9' ) { if( *ptr == '-' ) sgn = -1; ++ptr; } \  
                while( *ptr >= '0' && *ptr <= '9' ) { x = x*10 + *ptr - '0'; ++ptr; }  \  
                x = x * sgn; \  
        }while(0)  

#define  OUTPUT( x ) do { \  
                int  x0 = x; \  
                char  num[32], *digit_pos = num + 31; \  
                num[31] = '\n'; \  
                while( x0 > 0 ) { \  
                        *--digit_pos = x0 % 10 + '0'; \  
                        x0 /= 10; \  
                } \  
                int  sz = num + 32 - digit_pos; \  
                memcpy( optr, digit_pos, sz ); \  
                optr += sz; \  
        }while(0)  
  
// 这是输入输出缓冲区，确保足够大  
char  buff[MAXN*12];  
char  obuff[MAXN*12];

//输入输出指针
char *ptr,*optr;  
……  
  
// 一口气将所有输入全部读入缓冲区  
n = fread( buff, 1, sizeof( buff ), stdin );  
ptr=buff;optr=obuff;
PARSE_INT( n );  
while( n-- ) {  
    PARSE_INT( x );  
    .....  
    OUTPUT( y );  
}  
// 一口气将所有输出  
fwrite( obuff, 1, optr - obuff, stdout );

----------------------------我是分割线

namespace IO {
    const int MX = 4e7; //1e7占用内存11000kb
    char buf[MX]; int c, sz;
    void begin() {
        c = 0;
        sz = fread(buf, 1, MX, stdin);
    }
    inline bool read(int &t) {
        while(c < sz && buf[c] != '-' && (buf[c] < '0' || buf[c] > '9')) c++;
        if(c >= sz) return false;
        bool flag = 0; if(buf[c] == '-') flag = 1, c++;
        for(t = 0; c < sz && '0' <= buf[c] && buf[c] <= '9'; c++) t = t * 10 + buf[c] - '0';
        if(flag) t = -t;
        return true;
    }
}  