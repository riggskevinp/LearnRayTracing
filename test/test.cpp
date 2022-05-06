#include <gtest/gtest.h>
#include "../vec3.h"
#include "../ray.h"

// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);
}

TEST(Vector3, Create){
    auto v = vec3(3,5,9);
    EXPECT_EQ(3.0, v.x());
}

TEST(Vector3, Add_Mult_Div){
    auto v = vec3(3,5,9);
    v += v;
    EXPECT_EQ(6.0, v.x());
    auto v2 = vec3(3, 5, 9) += v;
    EXPECT_EQ(27.0, v2.z());
    v *= 2;
    EXPECT_EQ(20.0, v.y());
    v /= 2;
    EXPECT_EQ(10.0, v.y());
}

TEST(Vector3, Length_LengthSquared){
    auto v = vec3(1,2,2);
    EXPECT_EQ(3.0, v.length());
    EXPECT_EQ(9.0, v.length_squared());
}

TEST(Vector3, Utilities){
    auto v = vec3(1, 2, 2);
    std::cout << v << std::endl;
    auto v2 = vec3(3, 4, 5);
    auto addv = v2 + v;
    EXPECT_EQ(4.0, addv.x());
    auto minusv = v2 - v;
    EXPECT_EQ(2.0, minusv.y());
    auto multv = v * v2;
    EXPECT_EQ(10.0, multv.z());

    auto v8 = v * 8;
    EXPECT_EQ(16.0, v8.y());
    v8 = 8 * v;
    EXPECT_EQ(16.0, v8.z());

    auto vdiv = v / 2;
    EXPECT_EQ(1.0, vdiv.y());

    EXPECT_EQ(9.0, dot(v, v));

    auto crossv = cross(v, v2);
    EXPECT_DOUBLE_EQ(2.0, crossv.x());
    std::cout << crossv << std::endl;

    auto unitv = unit_vector(v);
    EXPECT_LE(0.000001, abs(unitv.y() - 0.6666));
    std::cout << unitv << std::endl;

}

TEST(RAY, Happy_Path){
    auto pt = point3(1.0, 2.0, 3.0);
    auto dir = vector3(0.0, 0.0, 1.0);
    auto r = ray(pt, dir);

    EXPECT_EQ(4.0, r.at(1).z());
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}