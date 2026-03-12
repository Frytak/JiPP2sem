class Rectangle {
    private:
        double width;
        double height;

    public:
        Rectangle(double width, double height);
        double area() const;
        double perimeter() const;
        bool isSquare() const;
        void scale(double amount);
        static Rectangle createSquare(double side);
};
