#ifndef YAUI_VECTOR2_H
#define YAUI_VECTOR2_H


#include <utility>

namespace yaui {
    template<typename Type>
    class Vector2 {

        /** constants **/
        private:
        protected:
        public:

        /** data **/
        private:
        protected:
        public:
            Type mX;
            Type mY;

        /** methods **/
        private:
        protected:
        public:
            Vector2(Type x = Type(0), Type y = Type(0)) noexcept
                : mX(x)
                , mY(y) {

            }
            ~Vector2() {};
    };
}


#endif // YAUI_VECTOR2_H
