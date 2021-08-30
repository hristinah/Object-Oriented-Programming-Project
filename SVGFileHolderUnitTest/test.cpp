#include "pch.h"
#include <gtest/gtest.h>

#include <string>
#include <vector>
#include <stdio.h>

#include "../SVGFileProgram/Point.cpp"
#include "../SVGFileProgram/Rectangle.h"
#include "../SVGFileProgram/Circle.h"
#include "../SVGFileProgram/SVGShape.cpp"
#include "../SVGFileProgram/SVGCircle.cpp"
#include "../SVGFileProgram/SVGRectangle.cpp"
#include "../SVGFileProgram/SVGLine.cpp"
#include "../SVGFileProgram/SVGShapeFactory.h"
#include "../SVGFileProgram/SVGFileHolder.cpp"
#include "../SVGFileProgram/IncorrectArgStrException.h"

class SVGFileHolderConstructorTest : public ::testing::Test {
protected:
    SVGFileHolderConstructorTest() {}
    virtual ~SVGFileHolderConstructorTest() {}
};

TEST_F(SVGFileHolderConstructorTest, ConstructFromExistingFileTest) {
    SVGFileHolder* loaded_file;
    std::string file_name = "TestFiles/test.txt";
    std::string goal;
    goal += "1. rectangle 5 5 10 10 green\n"
        "2. circle 5 5 10 blue\n"
        "3. line 5 3 10 -5 blue\n";
    
    ASSERT_NO_THROW(
        loaded_file = new SVGFileHolder(file_name);
        EXPECT_EQ(loaded_file->Print(), goal);
        delete loaded_file;
    );
}

TEST_F(SVGFileHolderConstructorTest, ConstructFromNonExistentFileTest) {
    SVGFileHolder* loaded_file;
    std::string file_name = "TestFiles/NonExtest.txt";
    
    ASSERT_NO_THROW(
        loaded_file = new SVGFileHolder(file_name);
        EXPECT_TRUE(loaded_file->Print().empty());
        delete loaded_file;
        remove(file_name.c_str());
    );
}

TEST_F(SVGFileHolderConstructorTest, ConstructFromFileWithOnlyValidSVGShapesTest) {
    SVGFileHolder* loaded_file;
    std::string file_name = "TestFiles/test.txt";
    std::string goal;
    goal += "1. rectangle 5 5 10 10 green\n"
        "2. circle 5 5 10 blue\n"
        "3. line 5 3 10 -5 blue\n";

    ASSERT_NO_THROW(
        loaded_file = new SVGFileHolder(file_name);
        EXPECT_EQ(loaded_file->Print(), goal);
        delete loaded_file;
    );
}

TEST_F(SVGFileHolderConstructorTest, ConstructFromFileWithSomeInvalidSVGShapesTest) {
    SVGFileHolder* loaded_file;
    std::string file_name = "TestFiles/SomeInvalidSVGShapestest.txt";
    std::string goal;
    goal += "1. rectangle 5 5 10 10 green\n"
        "2. line 5 3 10 -5 blue\n";

    ASSERT_NO_THROW(
        loaded_file = new SVGFileHolder(file_name);
    EXPECT_EQ(loaded_file->Print(), goal);
    delete loaded_file;
    );
}

TEST_F(SVGFileHolderConstructorTest, ConstructFromFileWithNoValidSVGShapesTest) {
    SVGFileHolder* loaded_file;
    std::string file_name = "TestFiles/NoValidSVGShapestest.txt";

    ASSERT_NO_THROW(
        loaded_file = new SVGFileHolder(file_name);
        EXPECT_TRUE(loaded_file->Print().empty());
        delete loaded_file;
    );
}

TEST_F(SVGFileHolderConstructorTest, ConstructFromFileWithSomeTextOutsideOfLtGtTest) {
    SVGFileHolder* loaded_file;
    std::string file_name = "TestFiles/SomeTextOutsideLtGttest.txt";
    std::string goal;
    goal += "1. rectangle 5 5 10 10 green\n"
        "2. circle 5 5 10 blue\n";

    ASSERT_NO_THROW(
        loaded_file = new SVGFileHolder(file_name);
        EXPECT_EQ(loaded_file->Print(), goal);
        delete loaded_file;
    );
}

TEST_F(SVGFileHolderConstructorTest, ConstructFromFileWithOnlyTextOutsideOfLtGtTest) {
    SVGFileHolder* loaded_file;
    std::string file_name = "TestFiles/NoTextInsideLtGttest.txt";

    ASSERT_NO_THROW(
        loaded_file = new SVGFileHolder(file_name);
        EXPECT_TRUE(loaded_file->Print().empty());
        delete loaded_file;
    );
}

class SVGFileHolderFunctionalytyTest : public ::testing::Test {
protected:
    void SetUp() override {
        file_name = "TestFiles/test.txt";
        ASSERT_NO_THROW(loaded_file = new SVGFileHolder(file_name););
    }
    void TearDown() override {
        delete loaded_file;
    }

    std::string file_name;
    SVGFileHolder* loaded_file;
};

TEST_F(SVGFileHolderFunctionalytyTest, PrintTest) {
    std::string goal;
    goal += "1. rectangle 5 5 10 10 green\n"
        "2. circle 5 5 10 blue\n"
        "3. line 5 3 10 -5 blue\n";

    EXPECT_EQ(loaded_file->Print(), goal);

}

TEST_F(SVGFileHolderFunctionalytyTest, SaveSuccessTest) {
    std::string msg_goal = "Successfully saved TestFiles/test.txt.\n";
    EXPECT_EQ(loaded_file->Save(), msg_goal);
}

TEST_F(SVGFileHolderFunctionalytyTest, SaveWithNoChangesTest) {
    std::string msg_goal = "Successfully saved TestFiles/test.txt.\n";
    EXPECT_EQ(loaded_file->Save(), msg_goal);

	ASSERT_NO_THROW(
        SVGFileHolder * reloaded_file = new SVGFileHolder(file_name);
	    EXPECT_EQ(loaded_file->Print(), reloaded_file->Print());
        delete reloaded_file;
    );
}

TEST_F(SVGFileHolderFunctionalytyTest, SaveAsSuccessTest) {
    std::string new_file_name = "TestFiles/SaveAstest.txt";
    std::string msg_goal = "Successfully saved TestFiles/SaveAstest.txt.\n";
    EXPECT_EQ(loaded_file->SaveAs(new_file_name), msg_goal);
}

TEST_F(SVGFileHolderFunctionalytyTest, SaveAsWithNoChangesTest) {
    std::string new_file_name = "TestFiles/SaveAstest.txt";
    std::string msg_goal = "Successfully saved TestFiles/SaveAstest.txt.\n";
    EXPECT_EQ(loaded_file->SaveAs(new_file_name), msg_goal);

    ASSERT_NO_THROW(
        SVGFileHolder * new_loaded_file = new SVGFileHolder(new_file_name);
        EXPECT_EQ(loaded_file->Print(), new_loaded_file->Print());
        delete new_loaded_file;
    );
}

TEST_F(SVGFileHolderFunctionalytyTest, SaveAsAfterChangesTest) {
    std::string new_file_name = "TestFiles/SaveAsWithChangestest.txt";
    std::vector<std::string> arguments;
    arguments.push_back("2");
    std::string erase_msg_goal = "Erased a circle (2).\n";
    std::string save_msg_goal = "Successfully saved TestFiles/SaveAsWithChangestest.txt.\n";

    EXPECT_EQ(loaded_file->Erase(arguments), erase_msg_goal);
    arguments.clear();
    EXPECT_EQ(loaded_file->SaveAs(new_file_name), save_msg_goal);

    ASSERT_NO_THROW(
        SVGFileHolder * new_loaded_file = new SVGFileHolder(new_file_name);
    EXPECT_EQ(loaded_file->Print(), new_loaded_file->Print());
    delete new_loaded_file;
    );
}

TEST_F(SVGFileHolderFunctionalytyTest, EraseSuccessTest) {
    std::vector<std::string> arguments;
    arguments.push_back("2");
    std::string msg_goal = "Erased a circle (2).\n";
    std::string goal;
    goal += "1. rectangle 5 5 10 10 green\n"
        "2. line 5 3 10 -5 blue\n";
   
    EXPECT_EQ(loaded_file->Erase(arguments), msg_goal);
    EXPECT_EQ(loaded_file->Print(), goal);
    arguments.clear();
}

TEST_F(SVGFileHolderFunctionalytyTest, EraseNoSuchFigureTest) {
    std::vector<std::string> arguments;
    arguments.push_back("8");
    std::string msg_goal = "There is no figure number 8!\n";
    std::string goal;
    goal += "1. rectangle 5 5 10 10 green\n"
        "2. circle 5 5 10 blue\n"
        "3. line 5 3 10 -5 blue\n";

    EXPECT_EQ(loaded_file->Erase(arguments), msg_goal);
    EXPECT_EQ(loaded_file->Print(), goal);
    arguments.clear();
}

TEST_F(SVGFileHolderFunctionalytyTest, EraseIncorrectArgumentsTest) {
    std::vector<std::string> arguments;
    arguments.push_back("hfhfhfh");
    std::string msg_goal = "Incorrect arguments.\n";
    std::string goal;
    goal += "1. rectangle 5 5 10 10 green\n"
        "2. circle 5 5 10 blue\n"
        "3. line 5 3 10 -5 blue\n";

    EXPECT_EQ(loaded_file->Erase(arguments), msg_goal);
    EXPECT_EQ(loaded_file->Print(), goal);
    arguments.clear();
}

TEST_F(SVGFileHolderFunctionalytyTest, EraseIncorrectNumOfArgumentsTest) {
    std::vector<std::string> arguments;
    arguments.push_back("2");
    arguments.push_back("8");
    std::string msg_goal = "Incorrect number of arguments.\n";
    std::string goal;
    goal += "1. rectangle 5 5 10 10 green\n"
        "2. circle 5 5 10 blue\n"
        "3. line 5 3 10 -5 blue\n";

    EXPECT_EQ(loaded_file->Erase(arguments), msg_goal);
    EXPECT_EQ(loaded_file->Print(), goal);
    arguments.clear();
}

TEST_F(SVGFileHolderFunctionalytyTest, CreateSuccessTest) {
    std::vector<std::string> arguments{ "rectangle", "-1000", "-1000", "10", "20", "yellow" };
    std::string msg_goal = "Successfully created rectangle (4).\n";

    EXPECT_EQ(loaded_file->Create(arguments), msg_goal);
    arguments.clear();
}

TEST_F(SVGFileHolderFunctionalytyTest, CreateCircleTest) {
    std::vector<std::string> arguments{ "circle", "8", "7", "5", "pink" };
    std::string msg_goal = "Successfully created circle (4).\n";
    std::string goal;
    goal += "1. rectangle 5 5 10 10 green\n"
        "2. circle 5 5 10 blue\n"
        "3. line 5 3 10 -5 blue\n"
        "4. circle 8 7 5 pink\n";

    EXPECT_EQ(loaded_file->Create(arguments), msg_goal);
    EXPECT_EQ(loaded_file->Print(), goal);
    arguments.clear();
}

TEST_F(SVGFileHolderFunctionalytyTest, CreateLineTest) {
    std::vector<std::string> arguments{ "line", "8", "9", "6", "20", "red" };
    std::string msg_goal = "Successfully created line (4).\n";
    std::string goal;
    goal += "1. rectangle 5 5 10 10 green\n"
        "2. circle 5 5 10 blue\n"
        "3. line 5 3 10 -5 blue\n"
        "4. line 8 9 6 20 red\n";

    EXPECT_EQ(loaded_file->Create(arguments), msg_goal);
    EXPECT_EQ(loaded_file->Print(), goal);
    arguments.clear();
}

TEST_F(SVGFileHolderFunctionalytyTest, CreateRectangleTest) {
    std::vector<std::string> arguments{ "rectangle", "-1000", "-1000", "10", "20", "yellow" };
    std::string msg_goal = "Successfully created rectangle (4).\n";
    std::string goal;
    goal += "1. rectangle 5 5 10 10 green\n"
        "2. circle 5 5 10 blue\n"
        "3. line 5 3 10 -5 blue\n"
        "4. rectangle -1000 -1000 10 20 yellow\n";

    EXPECT_EQ(loaded_file->Create(arguments), msg_goal);
    EXPECT_EQ(loaded_file->Print(), goal);
    arguments.clear();
}

TEST_F(SVGFileHolderFunctionalytyTest, CreateIncorrectArgumentsTest) {
    std::vector<std::string> arguments{ "rec", "-1000", "-1000", "10", "20" };
    std::string msg_goal = "Incorrect arguments.\n";
    std::string goal;
    goal += "1. rectangle 5 5 10 10 green\n"
        "2. circle 5 5 10 blue\n"
        "3. line 5 3 10 -5 blue\n";

    EXPECT_EQ(loaded_file->Create(arguments), msg_goal);
    EXPECT_EQ(loaded_file->Print(), goal);
    arguments.clear();
}

TEST_F(SVGFileHolderFunctionalytyTest, CreateIncorrectNumOfArgumentsTest) {
    std::vector<std::string> arguments{ "rectangle", "-1000", "-1000", "10" };
    std::string msg_goal = "Incorrect arguments.\n";
    std::string goal;
    goal += "1. rectangle 5 5 10 10 green\n"
        "2. circle 5 5 10 blue\n"
        "3. line 5 3 10 -5 blue\n";
    ASSERT_NO_THROW(
        EXPECT_EQ(loaded_file->Create(arguments), msg_goal);
        EXPECT_EQ(loaded_file->Print(), goal);
    );
    arguments.clear();
}

TEST_F(SVGFileHolderFunctionalytyTest, TranslateSuccessTest) {
    std::vector<std::string> arguments{ "vertical=\"10\"", "horizontal=\"100\""};
    std::string msg_goal = "Translated all figures.\n";
    std::string goal;
    goal += "1. rectangle 105 15 10 10 green\n"
        "2. circle 105 15 10 blue\n"
        "3. line 105 13 110 5 blue\n";

    EXPECT_EQ(loaded_file->Translate(arguments), msg_goal);
    EXPECT_EQ(loaded_file->Print(), goal);
    arguments.clear();
}

TEST_F(SVGFileHolderFunctionalytyTest, TranslateIncorrectArgumentsTest) {
    std::vector<std::string> arguments{ "vertical=\"10", "horizontal=100" };
    std::string msg_goal = "Incorrect arguments.\n";
    std::string goal;
    goal += "1. rectangle 5 5 10 10 green\n"
        "2. circle 5 5 10 blue\n"
        "3. line 5 3 10 -5 blue\n";

    EXPECT_EQ(loaded_file->Translate(arguments), msg_goal);
    EXPECT_EQ(loaded_file->Print(), goal);
    arguments.clear();
}

TEST_F(SVGFileHolderFunctionalytyTest, TranslateIncorrectNumOfArgumentsTest1) {
    std::vector<std::string> arguments{ "vertical=\"10\"", "horizontal=\"100\"", "some comment" };
    std::string msg_goal = "Incorrect number of arguments.\n";
    std::string goal;
    goal += "1. rectangle 5 5 10 10 green\n"
        "2. circle 5 5 10 blue\n"
        "3. line 5 3 10 -5 blue\n";
    ASSERT_NO_THROW(
        EXPECT_EQ(loaded_file->Translate(arguments), msg_goal);
        EXPECT_EQ(loaded_file->Print(), goal);
    );
    arguments.clear();
}

TEST_F(SVGFileHolderFunctionalytyTest, TranslateIncorrectNumOfArgumentsTest2) {
    std::vector<std::string> arguments{ "2" };
    std::string msg_goal = "Incorrect number of arguments.\n";
    std::string goal;
    goal += "1. rectangle 5 5 10 10 green\n"
        "2. circle 5 5 10 blue\n"
        "3. line 5 3 10 -5 blue\n";
    ASSERT_NO_THROW(
        EXPECT_EQ(loaded_file->Translate(arguments), msg_goal);
        EXPECT_EQ(loaded_file->Print(), goal);
    );
    arguments.clear();
}

TEST_F(SVGFileHolderFunctionalytyTest, WithinCircleSuccessTest) {
    std::vector<std::string> arguments{ "circle", "5", "5", "10" };
    std::string goal;
    goal += "2. circle 5 5 10 blue\n";

    EXPECT_EQ(loaded_file->Within(arguments), goal);
    arguments.clear();
}

TEST_F(SVGFileHolderFunctionalytyTest, WithinRectangleSuccessTest) {
    std::vector<std::string> arguments{ "rectangle", "-5", "-5", "30", "30" };
    std::string goal;
    goal += "1. rectangle 5 5 10 10 green\n"
        "2. circle 5 5 10 blue\n"
        "3. line 5 3 10 -5 blue\n";

    EXPECT_EQ(loaded_file->Within(arguments), goal);
    arguments.clear();
}

TEST_F(SVGFileHolderFunctionalytyTest, WithinCircleNoShapesTest) {
    std::vector<std::string> arguments{ "circle", "0", "0", "8" };
    std::string goal_msg = "No shapes are located within circle 0 0 8.\n";

    EXPECT_EQ(loaded_file->Within(arguments), goal_msg);
    arguments.clear();
}

TEST_F(SVGFileHolderFunctionalytyTest, WithinRectangleNoShapesTest) {
    std::vector<std::string> arguments{ "rectangle", "-5", "-5", "10", "4" };
    std::string goal_msg = "No shapes are located within rectangle -5 -5 10 4.\n";

    EXPECT_EQ(loaded_file->Within(arguments), goal_msg);
    arguments.clear();
}

TEST_F(SVGFileHolderFunctionalytyTest, WithinIncorrectShapeTest) {
    std::vector<std::string> arguments{ "circl", "0", "0", "8" };
    std::string goal_msg = "Incorrect shape.\n";

    EXPECT_EQ(loaded_file->Within(arguments), goal_msg);
    arguments.clear();
}

TEST_F(SVGFileHolderFunctionalytyTest, WithinIncorrectArgumentsTest) {
    std::vector<std::string> arguments{ "circle", "dfd", "0", "8" };
    std::string goal_msg = "Incorrect arguments.\n";
    ASSERT_NO_THROW(
        EXPECT_EQ(loaded_file->Within(arguments), goal_msg);
    );
    arguments.clear();
}

TEST_F(SVGFileHolderFunctionalytyTest, WithinIncorrectNumOfArgumentsTest) {
    std::vector<std::string> arguments{ "circle", "2" };
    std::string goal_msg = "Incorrect number of arguments\n";
    ASSERT_NO_THROW(
        EXPECT_EQ(loaded_file->Within(arguments), goal_msg);
    );
    arguments.clear();
}

