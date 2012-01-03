#ifndef QRK_RING_BUFFER_H
#define QRK_RING_BUFFER_H

/*!
  \file
  \brief �����O�o�b�t�@

  \author Satofumi KAMIMURA

  $Id: RingBuffer.h 1811 2010-04-30 16:12:05Z satofumi $
*/

#include <deque>


namespace qrk
{
    //! �����O�o�b�t�@
    template <class T>
    class RingBuffer
    {
    public:
        explicit RingBuffer(void)
        {
        }


        /*!
          \brief �o�b�t�@�T�C�Y�̎擾
        */
        size_t size(void)
        {
            return ring_buffer_.size();
        }


        /*!
          \brief �o�b�t�@����

          \retval true �f�[�^�Ȃ�
          \retval false �f�[�^����
        */
        bool empty(void)
        {
            return ring_buffer_.empty();
        }


        /*!
          \brief �f�[�^�̊i�[

          \param[in] data �f�[�^
          \param[in] size �f�[�^��
        */
        void put(const T* data, size_t size)
        {
            const T* last_p = data + size;
            ring_buffer_.insert(ring_buffer_.end(), data, last_p);
        }


        /*!
          \brief �f�[�^�̎��o��

          \param[out] data �f�[�^���o���p�o�b�t�@
          \param[in] size ���o���f�[�^�̍ő��

          \return ���o�����f�[�^��
        */
        size_t get(T* data, size_t size)
        {
            size_t n = std::min(size, ring_buffer_.size());
            std::copy(ring_buffer_.begin(), ring_buffer_.begin() + n, data);
            ring_buffer_.erase(ring_buffer_.begin(), ring_buffer_.begin() + n);
            return n;
        }


        /*!
          \brief �f�[�^�̏����߂�

          \param[in] ch �����߂��f�[�^
        */
        void ungetc(const T ch)
        {
            ring_buffer_.push_front(ch);
        }


        /*!
          \brief �i�[�f�[�^�̃N���A
        */
        void clear(void)
        {
            ring_buffer_.clear();
        }


    private:
        RingBuffer(const RingBuffer& rhs);
        RingBuffer& operator = (const RingBuffer& rhs);

        std::deque<T> ring_buffer_;
    };
}

#endif /* !QRK_RING_BUFFER_H */
