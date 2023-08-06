#ifndef __VERTEX_H__
#define __VERTEX_H__
#define MAX_BONE_INFLUENCE 4
#include <Core/tspch.h>
namespace openge {

	class Vertex {
	private:
		Vector3 _pos;
		Vector3 _normal;
		Vector2 _tex;
        Vector3 _tangent;
        Vector3 _bitangent;
	public:
		Vertex() : _pos(Vector3()), _normal(Vector3()), _tex(Vector2()){
        }
        Vertex(const Vector3& pos, const Vector3& normal, const Vector2& tex) {
            _pos = pos;
            _normal = normal;
            _tex = tex;
        }
		
        // Getters
        Vector3 getPos() const {
            return _pos;
        }

        Vector3 getNormal() const {
            return _normal;
        }

        Vector2 getTex() const {
            return _tex;
        }


        Vector3 getTangent() const {
            return _tangent;
        }


        Vector3 getBitangent() const {
            return _bitangent;
        }
       

        // Setters
        void setPos(const Vector3& pos) {
            _pos = pos;
        }

        void setNormal(const Vector3& normal) {
            _normal = normal;
        }

        void setTex(const Vector2& tex) {
            _tex = tex;
        }

        void setTangent(const Vector3& tangent) {
            _tangent = tangent;
        }

        void setBitangent(const Vector3& bitangent) {
            _bitangent = bitangent;
        }
      
	};
}
#endif
