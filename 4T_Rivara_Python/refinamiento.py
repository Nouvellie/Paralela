#The demonstration of improved face based data structure

from numpy import array

triangles = array([[ 1,  2, 3],
                  [ 1,  3,  4],
                  [ 1,  4,  5],
                  [ 1,  5,  6],
                  [ 1,  6,  7],
                  [ 1,  7,  8],
                  [ 1,  8,  9],
                  [ 1,  9, 10],
                  [ 1, 10, 11],
                  [ 1, 11, 12],
                  [ 1, 12, 13],
                  [ 1, 13,  2],
                  [ 2, 13, 14],
                  [ 2, 14, 15],
                  [ 2, 15,  3]], dtype=int)

points = array([[ -0.416,  0.909],
                [ -1.350,  0.436],
                [ -1.640, -0.549],
                [ -1,310,  1.510],
                [ -0.532, -2.170],
                [  0.454, -2.410],
                [  1.450, -2.210],
                [  2.290, -1.660],
                [  2.880, -0.838],
                [  3.160,  0.131],
                [  3.120,  1.140],
                [  2.770,  2.080],
                [  2.160,  2.890],
                [  1.360,  3.490]])


import matplotlib.pyplot as plt

fig = plt.figure()
pylab.triplot(points[:,0],points[:,1],triangles)

for i,tri in enumerate(triangles):
    v1,v2,v3 = points[tri]
    vavg = (v1 + v2 + v3)/3
    plt.text(vavg[0],vavg[1],i)

#plt.show()

## constructing improved face based data structure

def edge_search(v1,v2,skip):
    """
    Which triangle has edge with verticies i and j and aren't triangle <skip>?
    """
    neigh = -1
    for i,tri in enumerate(triangles):
        if (v1 in tri) and (v2 in tri):
            if i is skip:
                continue
            else:
                neigh = i
                break

    return(neigh)


def triangle_search(i):
    """
    For given vertex with index i return any triangle from neigberhood
    """
    for i,tri in enumerate(triangles):
        if i in tri:
            return(i)

neighberhood = []
for i,tri in enumerate(triangles):

    v1, v2, v3 = tri

    t3 = edge_search(v1,v2,i)
    t1 = edge_search(v2,v3,i)
    t2 = edge_search(v3,v1,i)

    neighberhood.append([t1,t2,t3])

neighberhood = array(neighberhood,dtype=int)

faces = []
for vi,_ in enumerate(points):
    faces.append(triangle_search(vi))

## Now walking over first ring can be implemented
def triangle_ring(vertex):

    tri_start = faces[vertex]
    tri = tri_start

    ## with asumption that vertex is not on the boundary
    for i in range(10):

        yield tri

        boolindx = triangles[tri]==vertex

        # permutating to next and previous vertex
        w = boolindx[[0,1,2]]
        cw = boolindx[[2,0,1]]
        ccw = boolindx[[1,2,0]]

        ct = neighberhood[tri][cw][0]

        if ct==tri_start:
            break
        else:
            tri=ct

for i in triangle_ring(6):
    print(i)

## Using it for drawing lines on plot

vertex = 6
ring_points = []

for i in triangle_ring(vertex):
    vi = triangles[i]
    cw = (vi==vertex)[[2,0,1]] 
    print("v={}".format(vi[cw][0]))
    ring_points.append(vi[cw][0])

data = array([points[i] for i in ring_points])
plt.plot(data[:,0],data[:,1],"ro")
#plt.savefig("topology.png")
plt.show()

input("Press Enter to continue...")
plt.close("all")