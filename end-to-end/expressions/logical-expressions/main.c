int64_t main(){
    int64_t a, b, c, d;
    int64_t e = (a || b) || c;
    int64_t f = (a || b) && c;
    int64_t g = a || b && c;
    int64_t h = a && b && !c;
    int64_t i = !(a>b && b<c) || (a<=c && a>=b);
}
