#include "collection/Point2Collection.hpp"
#include "geometry/Point2.hpp"
#include <gtest/gtest.h>

TEST(Point2Collection, Constructor)
{
    ChibiCad::Point2Collection collection;
    EXPECT_EQ(0, collection.Size());
}

TEST(Point2Collection, Add)
{
    ChibiCad::Point2Collection collection;
    collection.Add(1.0f, 2.0f);
    EXPECT_TRUE(collection[0] == ChibiCad::Point2(1, 1.0f, 2.0f));
    collection.Add(3.0f, 4.0f);
    EXPECT_TRUE(collection[1] == ChibiCad::Point2(2, 3.0f, 4.0f));
}

TEST(Point2Collection, Remove)
{
    ChibiCad::Point2Collection collection;
    collection.Add(1.0f, 2.0f);
    collection.Add(3.0f, 4.0f);
    collection.Add(5.0f, 7.0f);
    collection.Remove(5.0f, 7.0f, 1e-6f);
    EXPECT_TRUE(collection.Size() == 2);
    EXPECT_TRUE(collection[1] == ChibiCad::Point2(2, 3.0f, 4.0f));
}

TEST(Point2Collection, Clear_Size)
{
    ChibiCad::Point2Collection collection;
    collection.Add(1.0f, 2.0f);
    collection.Add(3.0f, 4.0f);
    collection.Add(5.0f, 7.0f);
    EXPECT_TRUE(collection.Size() == 3);
    collection.Clear();
    EXPECT_TRUE(collection.Size() == 0);
}

TEST(Point2Collection, Get)
{
    ChibiCad::Point2Collection collection;
    collection.Add(1.0f, 2.0f);
    collection.Add(3.0f, 4.0f);
    collection.Add(5.0f, 7.0f);
    std::optional<ChibiCad::Point2> point = collection.Get(2);
    EXPECT_TRUE(point.has_value());
    EXPECT_EQ(point.value(), ChibiCad::Point2(2, 3.0f, 4.0f));
}

TEST(Point2Collection, GetAll)
{
    ChibiCad::Point2Collection collection;
    collection.Add(1.0f, 2.0f);
    collection.Add(3.0f, 4.0f);
    collection.Add(5.0f, 7.0f);
    std::vector<ChibiCad::Point2> points = collection.GetAll();
    EXPECT_EQ(3, collection.Size());
    EXPECT_TRUE(points[0].EpsilonEqual(1.0f, 2.0f, 1e-6f));
    EXPECT_TRUE(points[1].EpsilonEqual(3.0f, 4.0f, 1e-6f));
    EXPECT_TRUE(points[2].EpsilonEqual(5.0f, 7.0f, 1e-6f));
}

TEST(Point2Collection, Select_UnSelect)
{
    ChibiCad::Point2Collection collection;
    collection.Add(1.0f, 2.0f);
    collection.Add(3.0f, 4.0f);
    collection.Add(5.0f, 7.0f);
    collection.Select(5.0f, 7.0f, 1e-6f);
    ChibiCad::Point2 point = collection.Get(3).value();
    EXPECT_TRUE(point.IsSelected());
    collection.UnSelect(5.0f, 7.0f, 1e-6f);
    point = collection.Get(3).value();
    EXPECT_FALSE(point.IsSelected());
}

TEST(Point2Collection, RenumberXAscending)
{
    ChibiCad::Point2Collection collection;
    collection.Add(3.0f, 4.0f);
    collection.Add(1.0f, 2.0f);
    collection.Add(5.0f, 7.0f);
    EXPECT_TRUE(collection.Get(1).value().EpsilonEqual(3.0f, 4.0f, 1e-6f));
    EXPECT_TRUE(collection.Get(2).value().EpsilonEqual(1.0f, 2.0f, 1e-6f));
    EXPECT_TRUE(collection.Get(3).value().EpsilonEqual(5.0f, 7.0f, 1e-6f));
    collection.Renumber(ChibiCad::CompareXAscending);
    EXPECT_TRUE(collection.Get(1).value().EpsilonEqual(1.0f, 2.0f, 1e-6f));
    EXPECT_TRUE(collection.Get(2).value().EpsilonEqual(3.0f, 4.0f, 1e-6f));
    EXPECT_TRUE(collection.Get(3).value().EpsilonEqual(5.0f, 7.0f, 1e-6f));
}

TEST(Point2Collection, RenumberXDescending)
{
    ChibiCad::Point2Collection collection;
    collection.Add(3.0f, 4.0f);
    collection.Add(1.0f, 2.0f);
    collection.Add(5.0f, 7.0f);
    EXPECT_TRUE(collection.Get(1).value().EpsilonEqual(3.0f, 4.0f, 1e-6f));
    EXPECT_TRUE(collection.Get(2).value().EpsilonEqual(1.0f, 2.0f, 1e-6f));
    EXPECT_TRUE(collection.Get(3).value().EpsilonEqual(5.0f, 7.0f, 1e-6f));
    collection.Renumber(ChibiCad::CompareXDescending);
    EXPECT_TRUE(collection.Get(1).value().EpsilonEqual(5.0f, 7.0f, 1e-6f));
    EXPECT_TRUE(collection.Get(2).value().EpsilonEqual(3.0f, 4.0f, 1e-6f));
    EXPECT_TRUE(collection.Get(3).value().EpsilonEqual(1.0f, 2.0f, 1e-6f));
}

TEST(Point2Collection, RenumberYAscending)
{
    ChibiCad::Point2Collection collection;
    collection.Add(1.0f, 4.0f);
    collection.Add(4.0f, 2.0f);
    collection.Add(5.0f, 7.0f);
    EXPECT_TRUE(collection.Get(1).value().EpsilonEqual(1.0f, 4.0f, 1e-6f));
    EXPECT_TRUE(collection.Get(2).value().EpsilonEqual(4.0f, 2.0f, 1e-6f));
    EXPECT_TRUE(collection.Get(3).value().EpsilonEqual(5.0f, 7.0f, 1e-6f));
    collection.Renumber(ChibiCad::CompareYAscending);
    EXPECT_TRUE(collection.Get(1).value().EpsilonEqual(4.0f, 2.0f, 1e-6f));
    EXPECT_TRUE(collection.Get(2).value().EpsilonEqual(1.0f, 4.0f, 1e-6f));
    EXPECT_TRUE(collection.Get(3).value().EpsilonEqual(5.0f, 7.0f, 1e-6f));
}

TEST(Point2Collection, RenumberYDescending)
{
    ChibiCad::Point2Collection collection;
    collection.Add(1.0f, 4.0f);
    collection.Add(4.0f, 2.0f);
    collection.Add(5.0f, 7.0f);
    EXPECT_TRUE(collection.Get(1).value().EpsilonEqual(1.0f, 4.0f, 1e-6f));
    EXPECT_TRUE(collection.Get(2).value().EpsilonEqual(4.0f, 2.0f, 1e-6f));
    EXPECT_TRUE(collection.Get(3).value().EpsilonEqual(5.0f, 7.0f, 1e-6f));
    collection.Renumber(ChibiCad::CompareYDescending);
    EXPECT_TRUE(collection.Get(1).value().EpsilonEqual(5.0f, 7.0f, 1e-6f));
    EXPECT_TRUE(collection.Get(2).value().EpsilonEqual(1.0f, 4.0f, 1e-6f));
    EXPECT_TRUE(collection.Get(3).value().EpsilonEqual(4.0f, 2.0f, 1e-6f));
}