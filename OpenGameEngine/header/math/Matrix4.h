#ifndef __MATRIX4_H__
#define __MATRIX4_H__
namespace math {
	class Matrix4
	{
	public:
        Matrix4()
        {
            // Inicializa todos os elementos da matriz com zero
            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    m_elements[i][j] = 0.0f;
                }
            }
        }

        Matrix4(float elements[4][4])
        {
            // Copia os elementos fornecidos para a matriz
            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    m_elements[i][j] = elements[i][j];
                }
            }
        }
		~Matrix4() {}

        Matrix4 operator+(const Matrix4& mat) {
            Matrix4 result;
            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 4; j++) {
                    result.setElement(i, j, m_elements[i][j] + mat.m_elements[i][j]);
                }
            }
            return result;
        }

        Matrix4 operator-(const Matrix4& mat) {
            Matrix4 result;
            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 4; j++) {
                    result.setElement(i, j , m_elements[i][j] - mat.m_elements[i][j]);
                }
            }
            return result;
        }

        Matrix4 operator*(const Matrix4& mat) {
            Matrix4 result;
            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 4; j++) {
                    float sum = 0.0f;
                    for (int k = 0; k < 4; k++) {
                        sum += m_elements[i][k] * mat.m_elements[k][j];
                    }
                    result.setElement(i, j, sum);
                }
            }
        }

        Matrix4 operator/(const Matrix4& mat) {
            Matrix4 result;
            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 4; j++) {
                    result.setElement(i, j, m_elements[i][j] / mat.m_elements[i][j]);
                }
            }
            return result;
        }

        Matrix4 operator/(float scalar) {
            Matrix4 result;
            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 4; j++) {
                    result.setElement(i, j, m_elements[i][j] / scalar);
                }
            }
            return result;
        }

        float* operator[](int index)
        {
            return m_elements[index];
        }
        
        void setElement(int line, int column, float value) {
            m_elements[line][column] = value;
        }

        float getElement(int line, int column)
        {
            return m_elements[line][column];
        }

    private:
        float m_elements[4][4];
	};
}
#endif
