#ifndef QRK_ANGLE_H
#define QRK_ANGLE_H

/*!
  \file
  \brief �p�x�̌^�Ǘ�

  \author Satofumi KAMIMURA

  $Id: Angle.h 1811 2010-04-30 16:12:05Z satofumi $
*/


namespace qrk
{
    /*!
      \brief �p�x�̌^�Ǘ�
    */
    class Angle
    {
    public:
        Angle(void);
        Angle(const Angle& rhs);

        Angle& operator = (const Angle& rhs);
        Angle& operator += (const Angle& rhs);
        const Angle operator + (const Angle& rhs) const;
        Angle& operator -= (const Angle& rhs);
        const Angle operator - (const Angle& rhs) const;
        Angle& operator *= (const double rhs);
        Angle operator * (const double rhs) const;
        friend const Angle operator * (const double lhs, const Angle& rhs);

        void normalize(void);


        /*!
          \brief degree �p�x�ւ̕ϊ�

          \return degree �p�x
        */
        int to_deg(void) const;


        /*!
          \brief radian �p�x�ւ̕ϊ�

          \return radian �p�x
        */
        double to_rad(void) const;

    private:
        double radian_angle_;

        friend Angle rad(double radian);
        friend Angle deg(int degree);
    };


    /*!
      \brief radian �p�x�� Angle �ɕϊ�

      \param[in] radian radian �p�x
      \return Angle �I�u�W�F�N�g
    */
    extern Angle rad(double radian);


    /*!
      \brief degree �p�x�� Angle �ɕϊ�

      \param[in] degree degree �p�x
      \return Angle �I�u�W�F�N�g
    */
    extern Angle deg(int degree);
}

#endif /* !QRK_ANGLE__H */
