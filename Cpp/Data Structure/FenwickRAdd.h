/*
範囲addが可能なFenwicktree
すこし拡張されている
initでまず配列を与える
すると、add(l, r, x)で[l, r)それぞれにd[i]*xを足す
つまりdとして1で埋められたものを渡せば範囲addになる
*/
template <int SIZE>
struct FenwickRAdd {
    FenwickTree<SIZE> b0, b1;
    ll ds[SIZE+1];
    void init(const ll d[]) {
        b0.init();
        b1.init();
        ds[0] = 0;
        for (int i = 1; i <= SIZE; i++) {
            ds[i] = d[i-1]+ds[i-1];
        }
    }

    void add(int i, ll x) {
        b0.add(i, x);
    }

    void add(int l, int r, ll x) {
        b1.add(l, x);
        b1.add(r, -x);
        b0.add(l, -ds[l]*x);
        b0.add(r, ds[r]*x);
    }

    //[0, i)
    ll sum(int i) {
        return b0.sum(i)+b1.sum(i)*ds[i];
    }

    //[a, b)
    ll sum(int a, int b) {
        return sum(b) - sum(a);
    }
};