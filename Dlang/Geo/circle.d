    return (conj(x)*y).im;
}

Cir circumCircle(in P[3] l) {
    P a = l[0], b = l[1], c = l[2];
    b -= a; c -= a;
    double s = 2*cross(b, c);
    double A = (b-c).norm(), B = c.norm(), C = b.norm();
    double S = A+B+C;
    P r = (B*(S-2*B)*b+C*(S-2*C)*c)/(s*s);
    return Cir(r + a, r.abs);
}

Cir smallestEnclosingCircle(P[] p) {
    static P[] pb;
    pb.length = 1;
    static P[3] q;
    const eps = 1e-9;
    int pbc = 1;
    int cnt = 0;
    Cir dfs(int pc, int qc) {
        Cir get() {
            final switch (qc) {
            case 3:
                return circumCircle(q);
            case 2:
                return Cir((q[0]+q[1])/2, abs(q[0]-q[1])/2);
            case 1:
                return Cir(q[0], 0);
            case 0:
                return Cir(P(0, 0), -1);
            }
        }
        Cir c = get();
        foreach_reverse (i; max(-pc+1, 1)..pbc) {
            if (abs(pb[i]-c[0]) <= c[1] + eps) {
                continue;
            }
            q[qc++] = pb[i];
            c = dfs(-i, qc);
            qc--;
        }
        foreach (int i; 0..pc) {
            if (p[i].re == p[i].re.infinity || abs(p[i]-c[0]) <= c[1] + eps) {
                continue;
            }
            q[qc++] = p[i];
            c = dfs(i, qc);
            qc--;
            pbc++;
            pb ~= p[i];
            p[i].re = double.infinity;
        }
        return c;
    }
    return dfs(cast(int)p.length, 0);
}