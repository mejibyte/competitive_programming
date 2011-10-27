point center(const point &p, const point &q, const point &r) {
    double ax = q.x - p.x;
    double ay = q.y - p.y;
    double bx = r.x - p.x;
    double by = r.y - p.y;
    double d = ax*by - bx*ay;
    
    if (cmp(d, 0) == 0) {
        printf("Points are collinear!\n");
        assert(false);
    }
    
    double cx = (q.x + p.x) / 2;
    double cy = (q.y + p.y) / 2;
    double dx = (r.x + p.x) / 2;
    double dy = (r.y + p.y) / 2;
    
    double t1 = bx*dx + by*dy;
    double t2 = ax*cx + ay*cy;
    
    double x = (by*t2 - ay*t1) / d;
    double y = (ax*t1 - bx*t2) / d;

    return point(x, y);
}