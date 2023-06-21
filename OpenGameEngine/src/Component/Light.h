#ifndef __LIGHT_H__
#define __LIGHT_H__
#include <Core/tspch.h>
#include <Component/Component.h>

namespace openge {

    enum LightType {
        Point,
        Spot,
        Directional
    };


    class Light : public Component {
    private:
        LightType lightType_;

        Vector3 position_;
        Vector3 direction_;
        Vector3 ambient_;
        Vector3 diffuse_;
        Vector3 specular_;

        float cutOff_;
        float outerCutOff_;

        float constant_;
        float linear_;
        float quadratic_;

        Vector3 color_;

    public:
        // Construtor vazio
        Light() = default;
        Light(LightType lightType) : lightType_(lightType) {}
        // Construtor com parâmetros
        Light(const Vector3& pos, const Vector3& dir, const Vector3& amb, const Vector3& diff, const Vector3& spec,
            float cut, float outerCut, float con, float lin, float quad, const Vector3& col)
            : position_(pos), direction_(dir), ambient_(amb), diffuse_(diff), specular_(spec),
            cutOff_(cut), outerCutOff_(outerCut), constant_(con), linear_(lin), quadratic_(quad), color_(col) {}

        // Getters
        const Vector3& getPosition() const { return position_; }
        const Vector3& getDirection() const { return direction_; }
        const Vector3& getAmbient() const { return ambient_; }
        const Vector3& getDiffuse() const { return diffuse_; }
        const Vector3& getSpecular() const { return specular_; }
        float getCutOff() const { return cutOff_; }
        float getOuterCutOff() const { return outerCutOff_; }
        float getConstant() const { return constant_; }
        float getLinear() const { return linear_; }
        float getQuadratic() const { return quadratic_; }
        const Vector3& getColor() const { return color_; }
        LightType getLightType() const { return lightType_; }

        // Setters
        void setPosition(const Vector3& pos) { position_ = pos; }
        void setDirection(const Vector3& dir) { direction_ = dir; }
        void setAmbient(const Vector3& amb) { ambient_ = amb; }
        void setDiffuse(const Vector3& diff) { diffuse_ = diff; }
        void setSpecular(const Vector3& spec) { specular_ = spec; }
        void setCutOff(float cut) { cutOff_ = cut; }
        void setOuterCutOff(float outerCut) { outerCutOff_ = outerCut; }
        void setConstant(float con) { constant_ = con; }
        void setLinear(float lin) { linear_ = lin; }
        void setQuadratic(float quad) { quadratic_ = quad; }
        void setColor(const Vector3& col) { color_ = col; }
        void setLightType(const LightType& type) { lightType_ = type; }
    };

}

#endif // !__LIGHT_H__



