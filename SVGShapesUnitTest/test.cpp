#include "pch.h"
#include <gtest/gtest.h>

#include <string>
#include <vector>

#include "../SVGFileProgram/Point.cpp"
#include "../SVGFileProgram/Rectangle.h"
#include "../SVGFileProgram/Circle.h"
#include "../SVGFileProgram/SVGShape.cpp"
#include "../SVGFileProgram/SVGCircle.cpp"
#include "../SVGFileProgram/SVGRectangle.cpp"
#include "../SVGFileProgram/SVGLine.cpp"
#include "../SVGFileProgram/IncorrectArgStrException.h"
#include "../SVGFileProgram/SVGShapeFactory.h"

class PointTest : public ::testing::Test {
protected:
    PointTest() {}
    virtual ~PointTest() {}
};
TEST_F(PointTest, TranslateTest) {
    Point our_point = Point(0, 1);
    our_point.Translate(5, 3);
    EXPECT_EQ(our_point.x, 5);
    EXPECT_EQ(our_point.y, 4);

    our_point.Translate(0, -5);
    EXPECT_EQ(our_point.x, 5);
    EXPECT_EQ(our_point.y, -1);
}
TEST_F(PointTest, IsInCircleTest) {
    Circle our_Circle = {1 ,1 ,5};
    Point center_point= Point(1, 1);
    Point inside_point = Point(-2, -1);
    Point border_point = Point(4, 5);
    Point outside_point = Point(7, 9);

    EXPECT_TRUE(center_point.IsInCircle(our_Circle));
    EXPECT_TRUE(inside_point.IsInCircle(our_Circle));
    EXPECT_TRUE(border_point.IsInCircle(our_Circle));
    EXPECT_FALSE(outside_point.IsInCircle(our_Circle));
}
TEST_F(PointTest, IsInRectangleTest) {
    Rectangle our_Rectangle = {7, 5, 5, 4};
    Point inside_point = Point(10, 7);
    Point edge_point = Point(12, 5);
    Point border_point1 = Point(8, 9);
    Point border_point2 = Point(12, 7);
    Point outside_point = Point(-1, -3);

    EXPECT_TRUE(inside_point.IsInRectangle(our_Rectangle));
    EXPECT_TRUE(edge_point.IsInRectangle(our_Rectangle));
    EXPECT_TRUE(border_point1.IsInRectangle(our_Rectangle));
    EXPECT_TRUE(border_point2.IsInRectangle(our_Rectangle));
    EXPECT_FALSE(outside_point.IsInRectangle(our_Rectangle));
}



class SVGShapeUtilityTest : public ::testing::Test {
protected:
    SVGShapeUtilityTest() {}
    virtual ~SVGShapeUtilityTest() {}
};

TEST_F(SVGShapeUtilityTest, PositionEqualsTest) {
    EXPECT_EQ(SVGShape::PositionEqualsSign("arg=12"), 3);
    EXPECT_EQ(SVGShape::PositionEqualsSign("argument="), 8);
    EXPECT_EQ(SVGShape::PositionEqualsSign(""), std::string::npos);
    EXPECT_EQ(SVGShape::PositionEqualsSign("arg"), std::string::npos);
}

TEST_F(SVGShapeUtilityTest, ArgumentHoldsTheGivenAttributeTest) {
    EXPECT_TRUE(SVGShape::ArgumentHoldsTheGivenAttributeName("att=\"12\"", "att"));
    EXPECT_TRUE(SVGShape::ArgumentHoldsTheGivenAttributeName("cx=\"5\"", "cx"));
    EXPECT_TRUE(SVGShape::ArgumentHoldsTheGivenAttributeName("cy=\"-7\"", "cy"));
    EXPECT_TRUE(SVGShape::ArgumentHoldsTheGivenAttributeName("r=\"2\"", "r"));
    EXPECT_TRUE(SVGShape::ArgumentHoldsTheGivenAttributeName("x1=\"0\"", "x1"));
    EXPECT_TRUE(SVGShape::ArgumentHoldsTheGivenAttributeName("y2=\"20\"", "y2"));;
    EXPECT_TRUE(SVGShape::ArgumentHoldsTheGivenAttributeName("fill=\"blue\"","fill"));

    EXPECT_FALSE(SVGShape::ArgumentHoldsTheGivenAttributeName("", "attribute"));
    EXPECT_FALSE(SVGShape::ArgumentHoldsTheGivenAttributeName("att=12", "attribute"));
    EXPECT_FALSE(SVGShape::ArgumentHoldsTheGivenAttributeName("attribute", "attribute")); 
}

TEST_F(SVGShapeUtilityTest, GetAttributeValueTest) {
    ASSERT_NO_THROW(SVGShape::GetAttributeValueStr("att=\"12\""));
    EXPECT_EQ(SVGShape::GetAttributeValueStr("att=\"12\""), "12");

    ASSERT_NO_THROW(SVGShape::GetAttributeValueStr("cx=\"-7\""));
    EXPECT_EQ(SVGShape::GetAttributeValueStr("cx=\"-7\""), "-7");

    ASSERT_NO_THROW(SVGShape::GetAttributeValueStr("ill=\"blue\""));
    EXPECT_EQ(SVGShape::GetAttributeValueStr("ill=\"blue\""), "blue");

    ASSERT_NO_THROW(SVGShape::GetAttributeValueStr("att=\"1abd2\""));
    EXPECT_EQ(SVGShape::GetAttributeValueStr("att=\"1abd2\""), "1abd2");

    EXPECT_THROW(SVGShape::GetAttributeValueStr(""), IncorrectArgStrException*);
    EXPECT_THROW(SVGShape::GetAttributeValueStr("att"), IncorrectArgStrException*);
    EXPECT_THROW(SVGShape::GetAttributeValueStr("att=12"), IncorrectArgStrException*);
    EXPECT_THROW(SVGShape::GetAttributeValueStr("att=12\""), IncorrectArgStrException*);
    EXPECT_THROW(SVGShape::GetAttributeValueStr("att=\"12"), IncorrectArgStrException*);  
}

TEST_F(SVGShapeUtilityTest, AssignAttributeTest) {
    int attribute_val;

    ASSERT_NO_THROW(SVGShape::AssignAttributeFromString("att=\"12\"", "att", attribute_val));
    EXPECT_EQ(attribute_val, 12);

    ASSERT_NO_THROW(SVGShape::AssignAttributeFromString("10", "att", attribute_val));
    EXPECT_EQ(attribute_val, 10);

    ASSERT_NO_THROW(SVGShape::AssignAttributeFromString("x1=\"-150\"", "x1", attribute_val));
    EXPECT_EQ(attribute_val, -150);

    EXPECT_THROW(SVGShape::AssignAttributeFromString("", "x1", attribute_val), IncorrectArgStrException*);
    EXPECT_THROW(SVGShape::AssignAttributeFromString("x1=20\"", "x1", attribute_val), IncorrectArgStrException*);
    EXPECT_THROW(SVGShape::AssignAttributeFromString("x1=\"-150\"", "x2", attribute_val), IncorrectArgStrException*);
    EXPECT_THROW(SVGShape::AssignAttributeFromString("x1=\"dgfgfg\"", "x1", attribute_val), IncorrectArgStrException*);    
}



class SVGCircleFunctionalityTest : public ::testing::Test {
protected:
    void SetUp() override {
        std::vector<std::string> arguments = { "5", "-5", "10", "blue" };
        ASSERT_NO_THROW(test_circle = new SVGCircle(arguments));
    }
    void TearDown() override {
        delete test_circle;
    }

    SVGCircle* test_circle;
};

TEST_F(SVGCircleFunctionalityTest, ConstructorTest) {
    Circle goal{ 5, -5, 10 };
    /*circle 5 -5 10 blue*/
    std::vector<std::string> correct_arguments_from_console = { "5", "-5", "10", "blue" };
    ASSERT_NO_THROW(
        SVGCircle c(correct_arguments_from_console);
        EXPECT_EQ(c.get_dimensions(), goal);
        EXPECT_EQ(c.get_color(), "blue");
    );
    correct_arguments_from_console.clear();

    std::vector<std::string> arguments_from_console_for_area = { "5", "-5", "10" };
    ASSERT_NO_THROW(
        SVGCircle c(arguments_from_console_for_area);
        EXPECT_EQ(c.get_dimensions(), goal);
        EXPECT_EQ(c.get_color(), "transparent"); 
    );
    arguments_from_console_for_area.clear();

    /*<circle cx="5" cy="-5" r="10" fill="blue" / >*/
    std::vector<std::string> correct_arguments_from_file = { "cx=\"5\"", "cy=\"-5\"", "r=\"10\"", "fill=\"blue\"" };
    ASSERT_NO_THROW(
        SVGCircle c(correct_arguments_from_file);
        EXPECT_EQ(c.get_dimensions(), goal);
        EXPECT_EQ(c.get_color(), "blue");
    );
    correct_arguments_from_file.clear();

    std::vector<std::string> incorrect_arguments_from_console = { "fdgdg", "-ddf", "" };
    ASSERT_THROW(SVGCircle c(incorrect_arguments_from_console), IncorrectArgStrException*);
    incorrect_arguments_from_console.clear();

    std::vector<std::string> incorrect_arguments_from_file = { "c=\"5\"", "cy=\"-5\"", "r=\"10\"", "fill=\"blue\"" };
    ASSERT_THROW(SVGCircle c(incorrect_arguments_from_file), IncorrectArgStrException*);
    incorrect_arguments_from_file.clear();
}

TEST_F(SVGCircleFunctionalityTest, TranslateTest) {
    Circle first_translate_goal{ 2, 0, 10 };
    Circle second_translate_goal{5, -22, 10};

    test_circle->Translate(-3, 5);
    EXPECT_EQ(test_circle->get_dimensions(), first_translate_goal);

    test_circle->Translate(3, -22);
    EXPECT_EQ(test_circle->get_dimensions(), second_translate_goal);
}

TEST_F(SVGCircleFunctionalityTest, ToStringTest) {
    EXPECT_EQ(test_circle->ToString(), "<circle cx=\"5\" cy=\"-5\" r=\"10\" fill=\"blue\" />");
}

TEST_F(SVGCircleFunctionalityTest, ToStringForConsoleTest) {
    EXPECT_EQ(test_circle->ToStringForConsole(), "circle 5 -5 10 blue");
}

TEST_F(SVGCircleFunctionalityTest, IsWithinCircleAreaTest) {
    Circle same{ 5, -5, 10 };
    EXPECT_TRUE(test_circle->IsWithinCircleArea(same));

    Circle surounding{ 6, -4, 12 };
    EXPECT_TRUE(test_circle->IsWithinCircleArea(surounding));

    Circle touching_internaly{ 6, -5, 11 };
    EXPECT_TRUE(test_circle->IsWithinCircleArea(touching_internaly));

    Circle crossing{ 3, 0, 8 };
    EXPECT_FALSE(test_circle->IsWithinCircleArea(crossing));

    Circle inside{ 3, 0, 4 };
    EXPECT_FALSE(test_circle->IsWithinCircleArea(inside));

    Circle no_crossing{ 20, 10, 3 };
    EXPECT_FALSE(test_circle->IsWithinCircleArea(no_crossing));
}

TEST_F(SVGCircleFunctionalityTest, IsWithinRectangleAreaTest) {
    Rectangle surounding{ -6, -16, 30, 50 };
    EXPECT_TRUE(test_circle->IsWithinRectangleArea(surounding));

    Rectangle touching_internaly{ -5, -15, 20, 20 };
    EXPECT_TRUE(test_circle->IsWithinRectangleArea(touching_internaly));

    Rectangle crossing{ 3, -4, 20, 10 };
    EXPECT_FALSE(test_circle->IsWithinRectangleArea(crossing));

    Rectangle inside{ 5, -5, 2, 2 };
    EXPECT_FALSE(test_circle->IsWithinRectangleArea(inside));

    Rectangle no_crossing{ 10, 9, 20, 2 };
    EXPECT_FALSE(test_circle->IsWithinRectangleArea(no_crossing));
}



class SVGRectangleFunctionalityTest : public ::testing::Test {
protected:
    void SetUp() override {
        std::vector<std::string> arguments = { "-1", "5", "10", "20", "red" };
        ASSERT_NO_THROW(test_rec = new SVGRectangle(arguments));
    }
    void TearDown() override {
        delete test_rec;
    }

    SVGRectangle* test_rec;
};

TEST_F(SVGRectangleFunctionalityTest, RectangleConstructorTest) {
    Rectangle goal{ -100, 60, 10, 20 };
    /*rectangle -100 60 10 20 red*/
    std::vector<std::string> correct_arguments_from_console = { "-100", "60", "10", "20", "red" };
    ASSERT_NO_THROW(
        SVGRectangle r(correct_arguments_from_console);
        EXPECT_EQ(r.get_dimensions(), goal);
        EXPECT_EQ(r.get_color(), "red");
    );
    correct_arguments_from_console.clear();

    std::vector<std::string> arguments_from_console_for_area = { "-100", "60", "10", "20" };
    ASSERT_NO_THROW(
        SVGRectangle r(arguments_from_console_for_area);
        EXPECT_EQ(r.get_dimensions(), goal);
        EXPECT_EQ(r.get_color(), "transparent");
    );
    arguments_from_console_for_area.clear();

    /*<rect x="-100" y="60" width="10" height="20" fill="red" />*/
    std::vector<std::string> correct_arguments_from_file = { "x=\"-100\"", "y=\"60\"", "width=\"10\"", "height=\"20\"", "fill=\"red\"" };
    ASSERT_NO_THROW(
        SVGRectangle r(correct_arguments_from_file);
        EXPECT_EQ(r.get_dimensions(), goal);
        EXPECT_EQ(r.get_color(), "red");
    );
    correct_arguments_from_file.clear();

    std::vector<std::string> incorrect_arguments_from_console = { "fdgdg", "-ddf", "", "fdgf" };
    ASSERT_THROW(SVGRectangle r(incorrect_arguments_from_console), IncorrectArgStrException*);
    incorrect_arguments_from_console.clear();

    std::vector<std::string> incorrect_arguments_from_file = { "d=\"5\"", "y=\"-5\"", "width=\"10\"", "height=\"20\"", "fill=\"blue\"" };
    ASSERT_THROW(SVGRectangle r(incorrect_arguments_from_file), IncorrectArgStrException*);
    incorrect_arguments_from_file.clear();
}

TEST_F(SVGRectangleFunctionalityTest, TranslateTest) {
    Rectangle first_translate_goal{ 2, 0, 10, 20 };
    Rectangle second_translate_goal{ -7, 7, 10, 20 };

    test_rec->Translate(3, -5);
    EXPECT_EQ(test_rec->get_dimensions(), first_translate_goal);

    test_rec->Translate(-9, 7);
    EXPECT_EQ(test_rec->get_dimensions(), second_translate_goal);
}

TEST_F(SVGRectangleFunctionalityTest, ToStringTest) {
    EXPECT_EQ(test_rec->ToString(), "<rect x=\"-1\" y=\"5\" width=\"10\" height=\"20\" fill=\"red\" />");
}

TEST_F(SVGRectangleFunctionalityTest, ToStringForConsoleTest) {
    EXPECT_EQ(test_rec->ToStringForConsole(), "rectangle -1 5 10 20 red");
}

TEST_F(SVGRectangleFunctionalityTest, IsWithinCircleAreaTest) {
    Circle surounding{ 7, 15, 15 };
    EXPECT_TRUE(test_rec->IsWithinCircleArea(surounding));

    Circle one_point_in{ 0, 4, 4 };
    EXPECT_FALSE(test_rec->IsWithinCircleArea(one_point_in));

    Circle crossing{ 3, 0, 7 };
    EXPECT_FALSE(test_rec->IsWithinCircleArea(crossing));

    Circle no_crossing{ 15, -3, 5 };
    EXPECT_FALSE(test_rec->IsWithinCircleArea(no_crossing));

    Circle inside{ 4, 12, 3 };
    EXPECT_FALSE(test_rec->IsWithinCircleArea(inside));
}

TEST_F(SVGRectangleFunctionalityTest, IsWithinRectangleAreaTest) {
    Rectangle surounding{ -3, 3, 18, 25 };
    EXPECT_TRUE(test_rec->IsWithinRectangleArea(surounding));

    Rectangle touching_internaly{ -1, 2, 14, 27 };
    EXPECT_TRUE(test_rec->IsWithinRectangleArea(touching_internaly));

    Rectangle crossing{ 6, 8, 7, 11 };
    EXPECT_FALSE(test_rec->IsWithinRectangleArea(crossing));

    Rectangle inside{ 1, 9, 5, 3 };
    EXPECT_FALSE(test_rec->IsWithinRectangleArea(inside));

    Rectangle no_crossing{ 2, -8, 16, 8 };
    EXPECT_FALSE(test_rec->IsWithinRectangleArea(no_crossing));
}



class SVGLineFunctionalityTest : public ::testing::Test {
protected:
    void SetUp() override {
        std::vector<std::string> arguments = { "-1", "5", "4", "7", "black" };
        ASSERT_NO_THROW(test_line = new SVGLine(arguments));
    }
    void TearDown() override {
        delete test_line;
    }

    SVGLine* test_line;
};

TEST_F(SVGLineFunctionalityTest, LineConstructorTest) {
    Point first_point_goal{ 5, 3 };
    Point second_point_goal{ 10, -5 };
    /*line 5 3 10 -5 blue*/
    std::vector<std::string> correct_arguments_from_console = { "5", "3", "10", "-5", "blue" };
    ASSERT_NO_THROW(
        SVGLine l(correct_arguments_from_console);
    EXPECT_EQ(l.get_first_point(), first_point_goal);
    EXPECT_EQ(l.get_second_point(), second_point_goal);
    EXPECT_EQ(l.get_color(), "blue");
    );
    correct_arguments_from_console.clear();

    /*<line x1="5" y1="3" x2="10" y2="-5" fill="blue" / >*/
    std::vector<std::string> correct_arguments_from_file = { "x1=\"5\"", "y1=\"3\"", "x2=\"10\"", "y2=\"-5\"", "fill=\"blue\"" };
    ASSERT_NO_THROW(
        SVGLine l(correct_arguments_from_file);
    EXPECT_EQ(l.get_first_point(), first_point_goal);
    EXPECT_EQ(l.get_second_point(), second_point_goal);
    EXPECT_EQ(l.get_color(), "blue");
    );
    correct_arguments_from_file.clear();

    std::vector<std::string> incorrect_arguments_from_console = { "fdgdg", "-ddf", "", "fdgf", "gfgfg" };
    ASSERT_THROW(SVGLine l(incorrect_arguments_from_console), IncorrectArgStrException*);
    incorrect_arguments_from_console.clear();

    std::vector<std::string> incorrect_arguments_from_file = { "x1=\"5\"", "y=\"-5\"", "x2=\"10\"", "y2=\"20\"", "fill=\"blue\"" };
    ASSERT_THROW(SVGLine l(incorrect_arguments_from_file), IncorrectArgStrException*);
    incorrect_arguments_from_file.clear();
}

TEST_F(SVGLineFunctionalityTest, TranslateTest) {
    Point first_point_translate_goal{ 2, -3 };
    Point second_point_translate_goal{ 7, -1 };
    
    test_line->Translate(3, -8);
    EXPECT_EQ(test_line->get_first_point(), first_point_translate_goal);
    EXPECT_EQ(test_line->get_second_point(), second_point_translate_goal);
}

TEST_F(SVGLineFunctionalityTest, ToStringTest) {
    EXPECT_EQ(test_line->ToString(), "<line x1=\"-1\" y1=\"5\" x2=\"4\" y2=\"7\" fill=\"black\" />");
}

TEST_F(SVGLineFunctionalityTest, ToStringForConsoleTest) {
    EXPECT_EQ(test_line->ToStringForConsole(), "line -1 5 4 7 black");
}

TEST_F(SVGLineFunctionalityTest, IsWithinCircleAreaTest) {
    Circle surounding{ 2, 4, 5 };
    EXPECT_TRUE(test_line->IsWithinCircleArea(surounding));

    Circle crossing{ 2, 4, 3 };
    EXPECT_FALSE(test_line->IsWithinCircleArea(crossing));

    Circle no_crossing{ 5, 2, 4 };
    EXPECT_FALSE(test_line->IsWithinCircleArea(no_crossing));

    Circle only_first_inside{ -2, 2, 5 };
    EXPECT_FALSE(test_line->IsWithinCircleArea(only_first_inside));

    Circle only_second_inside{ 5, 6, 4 };
    EXPECT_FALSE(test_line->IsWithinCircleArea(only_second_inside));
}

TEST_F(SVGLineFunctionalityTest, IsWithinRectangleAreaTest) {
    Rectangle surounding{ -4, 3, 11, 7 };
    EXPECT_TRUE(test_line->IsWithinRectangleArea(surounding));

    Rectangle touching_internaly{ -1, 5, 5, 2 };
    EXPECT_TRUE(test_line->IsWithinRectangleArea(touching_internaly));

    Rectangle crossing{ 0, 2, 5, 4 };
    EXPECT_FALSE(test_line->IsWithinRectangleArea(crossing));

    Rectangle only_first_inside{ -3, 4, 4, 3 };
    EXPECT_FALSE(test_line->IsWithinRectangleArea(only_first_inside));

    Rectangle only_second_inside{ 2, 6, 4, 3 };
    EXPECT_FALSE(test_line->IsWithinRectangleArea(only_second_inside));

    Rectangle no_crossing{ 3, -5, 4, 3 };
    EXPECT_FALSE(test_line->IsWithinRectangleArea(no_crossing));
}



class SVGShapeFactoryTest : public ::testing::Test {
protected:
    SVGShapeFactoryTest() {}
    virtual ~SVGShapeFactoryTest() {}
};

TEST_F(SVGShapeFactoryTest, LineConstructorTest) {
    SVGShape* new_object; 
    std::string goal_str = "<line x1=\"5\" y1=\"-2\" x2=\"4\" y2=\"7\" fill=\"black\" />";

    std::vector<std::string> correct_arguments_from_console = {"line", "5", "-2", "4", "7", "black" };
    ASSERT_NO_THROW(
        new_object = SVGShapeFactory::NewSVGShape(correct_arguments_from_console);
        EXPECT_EQ(new_object->ToString(), goal_str);
        delete new_object;
    );
    correct_arguments_from_console.clear();

    std::vector<std::string> correct_arguments_from_file = { "line", "x1=\"5\"", "y1=\"-2\"", "x2=\"4\"", "y2=\"7\"", "fill=\"black\"" };
    ASSERT_NO_THROW(
        new_object = SVGShapeFactory::NewSVGShape(correct_arguments_from_file);
        EXPECT_EQ(new_object->ToString(), goal_str);
        delete new_object;
    );
    correct_arguments_from_file.clear();

    std::vector<std::string> incorrect_arguments_from_console = {"line", "fdgdg", "-ddf", "", "fdgf", "gfgfg" };
    ASSERT_THROW(new_object = SVGShapeFactory::NewSVGShape(incorrect_arguments_from_console); , IncorrectArgStrException*);
    incorrect_arguments_from_console.clear();

    std::vector<std::string> incorrect_shape_name_from_console = { "ln", "5", "-2", "4", "7", "black" };
    ASSERT_THROW(new_object = SVGShapeFactory::NewSVGShape(incorrect_shape_name_from_console);, IncorrectArgStrException*);
    incorrect_shape_name_from_console.clear();
}

TEST_F(SVGShapeFactoryTest, CircleConstructorTest) {
    SVGShape* new_object;
    std::string goal_str = "<circle cx=\"8\" cy=\"-5\" r=\"7\" fill=\"blue\" />";

    std::vector<std::string> correct_arguments_from_console = { "circle", "8", "-5", "7", "blue" };
    ASSERT_NO_THROW(
        new_object = SVGShapeFactory::NewSVGShape(correct_arguments_from_console);
        EXPECT_EQ(new_object->ToString(), goal_str);
        delete new_object;
    );
    correct_arguments_from_console.clear();

    std::vector<std::string> arguments_from_console_for_area = { "circle", "8", "-5", "10" };
    ASSERT_NO_THROW(
        new_object = SVGShapeFactory::NewSVGShape(arguments_from_console_for_area);
        EXPECT_EQ(new_object->ToString(), "<circle cx=\"8\" cy=\"-5\" r=\"10\" fill=\"transparent\" />");
        delete new_object;
    );
    arguments_from_console_for_area.clear();

    std::vector<std::string> correct_arguments_from_file = { "circle", "cx=\"8\"", "cy=\"-5\"", "r=\"7\"", "fill=\"blue\"" };
    ASSERT_NO_THROW(
        new_object = SVGShapeFactory::NewSVGShape(correct_arguments_from_file);
        EXPECT_EQ(new_object->ToString(), goal_str);
        delete new_object;
    );
    correct_arguments_from_file.clear();

    std::vector<std::string> incorrect_arguments_from_console = { "circle", "fdgdg", "-ddf", "", "gfgfg" };
    ASSERT_THROW(new_object = SVGShapeFactory::NewSVGShape(incorrect_arguments_from_console);, IncorrectArgStrException*);
    incorrect_arguments_from_console.clear();

    std::vector<std::string> incorrect_shape_name_from_console = { "cir", "5", "-2", "7", "black" };
    ASSERT_THROW(new_object = SVGShapeFactory::NewSVGShape(incorrect_shape_name_from_console); , IncorrectArgStrException*);
    incorrect_shape_name_from_console.clear();
}

TEST_F(SVGShapeFactoryTest, RectangleConstructorTest) {
    SVGShape* new_object;
    std::string goal_str = "<rect x=\"-1\" y=\"5\" width=\"10\" height=\"20\" fill=\"red\" />";

    std::vector<std::string> correct_arguments_from_console = { "rectangle", "-1", "5", "10", "20", "red" };
    ASSERT_NO_THROW(
        new_object = SVGShapeFactory::NewSVGShape(correct_arguments_from_console);
        EXPECT_EQ(new_object->ToString(), goal_str);
        delete new_object;
    );
    correct_arguments_from_console.clear();

    std::vector<std::string> arguments_from_console_for_area = { "rectangle", "8", "-5", "10", "30"};
    ASSERT_NO_THROW(
        new_object = SVGShapeFactory::NewSVGShape(arguments_from_console_for_area);
        EXPECT_EQ(new_object->ToString(), "<rect x=\"8\" y=\"-5\" width=\"10\" height=\"30\" fill=\"transparent\" />");
        delete new_object;
    );
    arguments_from_console_for_area.clear();

    std::vector<std::string> correct_arguments_from_file = { "rect", "x=\"-1\"", "y=\"5\"", "width=\"10\"", "height=\"20\"", "fill=\"red\"" };
    ASSERT_NO_THROW(
        new_object = SVGShapeFactory::NewSVGShape(correct_arguments_from_file);
        EXPECT_EQ(new_object->ToString(), goal_str);
        delete new_object;
    );
    correct_arguments_from_file.clear();

    std::vector<std::string> incorrect_arguments_from_console = { "rectangle", "fdgdg", "-ddf", "", "gfgfg", "dfdfdg" };
    ASSERT_THROW(new_object = SVGShapeFactory::NewSVGShape(incorrect_arguments_from_console); , IncorrectArgStrException*);
    incorrect_arguments_from_console.clear();

    std::vector<std::string> incorrect_shape_name_from_console = { "rec", "5", "-2", "7", "6", "black" };
    ASSERT_THROW(new_object = SVGShapeFactory::NewSVGShape(incorrect_shape_name_from_console);, IncorrectArgStrException*);
    incorrect_shape_name_from_console.clear();
}

TEST_F(SVGShapeFactoryTest, UnknownShapeConstructorTest) {
    std::vector<std::string> incorrect_arguments_from_console = { "randomshape", "fdgdg", "-ddf", "", "fdgf", "gfgfg" };
    ASSERT_THROW(SVGShape * new_object = SVGShapeFactory::NewSVGShape(incorrect_arguments_from_console);,
        IncorrectArgStrException*);
    incorrect_arguments_from_console.clear();
}