#include <vector>

namespace world{
    //3 floats that represent a point in 3d space
    struct _3dpos{
        float x,y,z;
    };
    //2 _3dpos that represent a line in 3d space
    struct ray{
        _3dpos raypoint[2];
    };
    //a color of 3 values, red,green, and blue
    struct color{
        unsigned char r;
        unsigned char g;
        unsigned char b;
    };
    //array of three _3dpos that represents a triangle in 3d space, along with color
    struct tri{
        _3dpos tri[3];
        color col;
    };
    //one sphere with a location, radius, and color
    struct sphere{
        _3dpos pos;
        float radius;
        color col;
    };
    // source of light
    struct lightsource{
        _3dpos pos;
        color col;
        //brightness is distance to check for the lightsource for shading
        float brightness;
    };
    // camera view
    struct camera{
        int width,height;
        //distance rays go
        int distance;
        // field of view in radians
        float fov;
    };
    
    //vector of tris
    struct mesh{
        std::vector<tri> mesh;
    };
    //returns centrion of tri
    _3dpos centeroftri(tri current){
        _3dpos final;
        final.x = (current.tri[0].x+current.tri[1].x+current.tri[2].x)/3;
        final.y = (current.tri[0].y+current.tri[1].y+current.tri[2].y)/3;
        final.z = (current.tri[0].z+current.tri[1].z+current.tri[2].z)/3;
        return final;
    }
    //changes first paramenter to the sum of the first and second parameters
    void add_3dpos(_3dpos &fir, _3dpos &sec){
        fir.x += sec.x;
        fir.y += sec.y;
        fir.z += sec.z;
    }
    //changes first paramenter to the difference of the first and second parameters
    void sub_3dpos(_3dpos &fir, _3dpos &sec){
        fir.x -= sec.x;
        fir.y -= sec.y;
        fir.z -= sec.z;
    }
    //changes first paramenter to the product of the first and second parameters
    void mul_3dpos(_3dpos &fir, _3dpos &sec){
        fir.x *= sec.x;
        fir.y *= sec.y;
        fir.z *= sec.z;
    }
    //changes first paramenter to the quotient of the first and second parameters
    void div_3dpos(_3dpos &fir, _3dpos &sec){
        fir.x /= sec.x;
        fir.y /= sec.y;
        fir.z /= sec.z;
    }
    //returns median of centrion of all tris in a mesh
    _3dpos centerofmesh(mesh current){
        _3dpos final;
        for (tri curtri : current.mesh){
            final.x += centeroftri(curtri).x;
            final.y += centeroftri(curtri).y;
            final.z += centeroftri(curtri).z;
        }
        final.x /= current.mesh.size();
        final.y /= current.mesh.size();
        final.z /= current.mesh.size();
    }
    //class to be rendered onto screen
    class currentworld {
        std::vector<mesh,sphere>
            
    };
}