#include "geometry/Point2.hpp"
#include "scg/geometry/Point2.hpp"
#include <gtest/gtest.h>

TEST(Point2Test, Constructor_Accessor)
{
    ChibiCad::Point2 p({1, 1.0f, 2.0f});
    EXPECT_EQ(1, p.Id());
    EXPECT_EQ(1.0f, p.X());
    EXPECT_EQ(2.0f, p.Y());
    EXPECT_FALSE(p.IsSelected());
    EXPECT_TRUE(p.Location() == SCG::Point2(1.0f, 2.0f));
}

TEST(Point2Test, DistanceTo)
{
    ChibiCad::Point2 p1({1, 1.0f, 2.0f});
    ChibiCad::Point2 p2({2, 4.0f, 6.0f});
    EXPECT_FLOAT_EQ(5.0f, p1.DistanceTo(p2));
}

TEST(Point2Test, PointEpsilonEqual)
{
    ChibiCad::Point2 p1({1, 1.0f, 2.0f});
    ChibiCad::Point2 p2({2, 2.0f, 3.0f});
    ChibiCad::Point2 p3({3, 1.0f, 2.0f});
    EXPECT_TRUE(p1.EpsilonEqual(p3, 1e-6f));
    EXPECT_FALSE(p1.EpsilonEqual(p2, 1e-6f));
}

TEST(Point2Test, CoodinateEpsilonEqual)
{
    ChibiCad::Point2 p1({1, 1.0f, 2.0f});
    EXPECT_TRUE(p1.EpsilonEqual(1.0f, 2.0f, 1e-6f));
    EXPECT_FALSE(p1.EpsilonEqual(1.1f, 2.0f, 1e-6f));
}

TEST(Point2Test, EqualOperator)
{
    ChibiCad::Point2 p1({1, 1.0f, 2.0f});
    ChibiCad::Point2 p2({1, 1.0f, 2.0f});
    ChibiCad::Point2 p3({2, 1.0f, 2.0f});
    ChibiCad::Point2 p4({1, 2.0f, 2.0f});
    EXPECT_EQ(p1, p2);
    EXPECT_NE(p1, p3);
    EXPECT_NE(p1, p4);
}

TEST(Point2Test, Select_UnSelect)
{
    ChibiCad::Point2 p({1, 1.0f, 2.0f});
    EXPECT_FALSE(p.IsSelected());
    p.Select();
    EXPECT_TRUE(p.IsSelected());
    p.UnSelect();
    EXPECT_FALSE(p.IsSelected());
}

TEST(Point2Test, Id_ChangeId)
{
    ChibiCad::Point2 p({2, 1.0f, 2.0f});
    EXPECT_EQ(2, p.Id());
    p.ChangeId(100);
    EXPECT_EQ(100, p.Id());
}