#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct {
    int x, y, z;
} Point;

typedef struct {
    int u, v;
    double dist;
} Edge;

typedef struct {
    Edge *data;
    int size;
    int capacity;
} MinHeap;

void push(MinHeap *h, int u, int v, double dist) {
    int i = h->size++;
    while (i > 0) {
        int p = (i - 1) / 2;
        if (h->data[p].dist <= dist) break;
        h->data[i] = h->data[p];
        i = p;
    }
    h->data[i].u = u;
    h->data[i].v = v;
    h->data[i].dist = dist;
}

Edge pop(MinHeap *h) {
    Edge res = h->data[0];
    Edge last = h->data[--h->size];
    int i = 0;
    while (i * 2 + 1 < h->size) {
        int child = i * 2 + 1;
        if (child + 1 < h->size && h->data[child + 1].dist < h->data[child].dist) child++;
        if (last.dist <= h->data[child].dist) break;
        h->data[i] = h->data[child];
        i = child;
    }
    h->data[i] = last;
    return res;
}

double get_dist(Point a, Point b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    double dz = a.z - b.z;
    return sqrt(dx * dx + dy * dy + dz * dz);
}

int main() {
    Point pts[5000];
    int n = 0;
    char line[256];

    while (fgets(line, sizeof(line), stdin)) {
        if (sscanf(line, "%d,%d,%d", &pts[n].x, &pts[n].y, &pts[n].z) == 3) {
            n++;
        }
    }

    if (n < 2) return 0;

    int total_possible_edges = n * (n - 1) / 2;
    MinHeap h;
    h.capacity = total_possible_edges;
    h.data = malloc(sizeof(Edge) * h.capacity);
    h.size = 0;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            push(&h, i, j, get_dist(pts[i], pts[j]));
        }
    }

    int circuit_id[5000];
    for (int i = 0; i < n; i++) circuit_id[i] = i;

    int circuits_left = n;
    long long last_x_prod = 0;

    while (circuits_left > 1 && h.size > 0) {
        Edge e = pop(&h);
        int u = e.u;
        int v = e.v;

        if (circuit_id[u] != circuit_id[v]) {
            if (circuits_left == 2) {
                last_x_prod = (long long)pts[u].x * pts[v].x;
            }

            int old_id = circuit_id[v];
            int new_id = circuit_id[u];
            for (int k = 0; k < n; k++) {
                if (circuit_id[k] == old_id) circuit_id[k] = new_id;
            }
            circuits_left--;
        }
    }

    printf("%lld\n", last_x_prod);

    free(h.data);
    return 0;
}
