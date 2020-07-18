#ifndef YAUI_DIRECTOR_H
#define YAUI_DIRECTOR_H


namespace yaui::system {
    class Director {
        /** constants **/
        private:
        protected:
        public:

        /** data **/
        private:
            bool mIsInitialised;
        protected:
        public:

        /** methods **/
        private:
            Director();
        protected:
        public:
            static Director* getInstance();
            ~Director();
            bool Init();
    };
}


#endif //YAUI_DIRECTOR_H
