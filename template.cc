#include "config.hh"

template <typename E>
class ArrayExpression {
public:
    typedef std::vector<real>           container_type;
    typedef container_type::size_type   size_type;
    typedef container_type::value_type  value_type;
    typedef container_type::reference   reference;

    size_type xsize() const
    {return static_cast<E const&>(*this).xsize();}

    size_type ysize() const
    {return static_cast<E const&>(*this).ysize();}

    value_type operator()(size_type ix, size_type iy) const
    {return static_cast<E const&>(*this)(ix, iy);}

    operator E&()             { return static_cast<      E&>(*this); }
    operator E const&() const { return static_cast<const E&>(*this); }
};


class Array : public ArrayExpression<Array> {
    container_type *data;
public:
    size_type  xsize() const {return columns;}
    size_type  ysize() const {return rows;}

    Array(container_type *data) {}

    template <typename E>
    const Array& operator=(const Array& other) {
        for(size_t iy = 1; iy < ysize() - 1; ++iy) {
            for(size_t ix = 1; ix < xsize() - 1; ++ix) {
                size_t index = iy * columns + ix;
            }
        }
    }
};

void run(std::vector<real> &src_vec, std::vector<real> &dest_vec) {
    real *src  =  src_vec.data();
    real *dest = dest_vec.data();

    Array<rows, columns> S()
    //D = w * (N + S + W + E);
}
