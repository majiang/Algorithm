//いろいろ乱雑

//nCk
ll comb(int n, int k) {
    if (n < k) return 0;
    ll result = 1;
    for (int i = 1; i <= k; i++) {
        result *= n - i + 1;
        result /= i;
    }
    return result;
}

//nCk % md
ll comb_pmod(int n, int k, ll md) {
	if (n < k || k < 0) return 0;
	ll r = 1;
	for (int i = 1; i <= k; i++) {
		r *= i;
		r %= md;
	}
	r = invp(r, md);
	for (int i = n-k+1; i <= n; i++) {
		r = (r * i) % md;
	}
	return r;
}

//fact[i]:i! invfact[i]:i!の逆元 という配列が用意されている前提でのnCkの計算
ll comb_st(int n, int k) {
    if (n < k || k < 0) return 0;
    return fact[n]*invfact[k]%MD*invfact[n-k]%MD;
}

//P=pair<ll, ll> sからgへ移動する経路数を求める
ll grid_num(P s, P g) {
    if (g.first < s.first || g.second < g.first) return 0;
    return comb_st(g.fist+g.second-(s.first+s.second), g.first-s.first);
}

//P=pair<ll, ll> sからgへと対角線をまたがずに行ける経路数
ll katran_num(P s, P g) {
    ll res = grid_num(s, g);
    g = P(g.second, g.first);
    res += MD-grid_num(s, g);
    return res % MD;
}

template<int N, int K>
struct Combinations {
    ll data[N][K] = {};
    Combinations() {
        data[0][0] = 1;
        for (int i = 1; i < N; i++) {
            data[i][0] = 1;
            for (int j = 1; j < K; j++) {
                data[i][j] = data[i-1][j]+data[i-1][j-1];
            }
        }
    }
    ll* operator[](int n) {
        return data[n];
    }
    const ll* operator[](int n) const {
        return data[n];
    }
};
