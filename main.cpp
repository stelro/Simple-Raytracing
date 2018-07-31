#include <iostream>
#include <fstream>

int main()
{
    int width = 200;
    int height = 100;

    std::ofstream file("image.ppm");

    file << "P3\n" << width << " " << height << "\n255\n";

    for ( int j = height - 1; j >= 0; j-- ) {
        for ( int i = 0; i < width; i++ ) {

            float r = float (i) / float (width);
            float g = float (j) / float (height);
            float b = 2.0f;

            int ir = int(255.99 * r);
            int ig = int(255.99 * g);
            int ib = int(255.99 * b);

            file << ir << " " << ig << " " << ib << "\n";
        }
    }

    file.close();

    return 0;
}